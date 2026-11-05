"""Check linking regressions once for an outgoing push, using verified objects.

Exit 1 for proven regressions, 2 for inconclusive evidence. A census index at
the pushed base supplies the before state; the byte gate supplies current objects.
"""

import argparse
import collections
import csv
import subprocess
import sys
import json
import tempfile
import time
from pathlib import Path

import build
import link_census
import link_check
import exit_link


def git(*args):
    return subprocess.run(("git", *args), cwd=link_check.ROOT, check=True,
                          capture_output=True, text=True).stdout.strip()


def changed_sources(base, tip):
    names = git("diff", "--no-renames", "--name-only", base, tip, "--", "Code").splitlines()
    return {name for name in names if Path(name).suffix.lower() in (".cpp", ".c", ".asm")}


def changed_identities(base, tip):
    """Names whose address/owner may change, including ledger-only edits."""
    diff = git("diff", "--no-ext-diff", "--unified=0", base, tip, "--",
               "reverse/functions.csv", "reverse/symbols.csv",
               "reverse/data_rows.csv", "reverse/dir32_addresses.csv")
    names = set()
    for line in diff.splitlines():
        if line[:1] in ("+", "-") and not line.startswith(("+++", "---")):
            row = next(csv.reader([line[1:]]), [])
            if row and row[0] != "name":
                names.add(row[0])
            for field in row:
                for token in field.split(";"):
                    if token.strip().startswith("object-symbol="):
                        names.add(token.strip().split("=", 1)[1])
    return names


def affected_sources(index, names):
    """Definition owners and direct consumers, including unchanged sources."""
    touches = index.get("touches")
    if touches is None or any(obj not in touches for obj in index["objects"]
                              if obj not in index.get("forgotten", ())):
        raise ValueError("census index lacks per-object consumer names; fetch a current index")
    return {source for source, entry in index["blockers"].items()
            if names.intersection(touches.get(entry.get("object"), ()))}


def definitions(index, name, rank):
    """Link-order definitions of one name, with census retail verdicts."""
    objects = index["objects"]
    copies = {objects[i]: (digest, verdict) for i, digest, verdict in index["comdat"].get(name, ())
              if objects[i] in rank and objects[i] not in index.get("forgotten", ())}
    strong = {objects[i] for i in index["strong"].get(name, ())
              if objects[i] in rank and objects[i] not in index.get("forgotten", ())}
    return copies, strong


def selected(index, name, rank):
    copies, strong = definitions(index, name, rank)
    definers = set(copies) | strong
    if not definers:
        return None, None
    holder = min(definers, key=rank.__getitem__)
    exceptions = index["selection"]["exceptions"]
    if name in exceptions:
        position = exceptions[name]
        exception = index["objects"][position] if position is not None else None
        holder = exception if exception is None or exception in definers else holder
    verdict = link_census.judge_selected(holder, copies, definers, strong,
                                         index["selection"]["owners"].get(name, set()))
    return holder, verdict


def overlay(index, replacements, removed, truth):
    """Copy table containers, preserving the saved index for before comparisons."""
    updated = dict(index)
    for key in ("strong", "comdat", "common", "alternates", "blockers", "digests"):
        updated[key] = dict(index[key])
    if "touches" in index:
        updated["touches"] = dict(index["touches"])
    updated["objects"] = list(index["objects"])
    updated["forgotten"] = set(index.get("forgotten", ()))
    if "references" in index:
        graph = index["references"]
        updated["references"] = {**graph, "edges": dict(graph["edges"]),
                                 "referenced": set(graph["referenced"])}
    link_check.forget(updated, removed)
    for obj in replacements:
        if obj.name not in updated["objects"]:
            updated["objects"].append(obj.name)
        updated["forgotten"].discard(obj.name)
    link_check.refresh(updated, replacements, truth)
    return updated


def reorder(index, rank):
    """check_object compares numeric positions; use the new link order."""
    old = index["objects"]
    positions = sorted((i for i, obj in enumerate(old) if obj in rank), key=lambda i: rank[old[i]])
    moved = {old_i: new_i for new_i, old_i in enumerate(positions)}
    for table in ("comdat", "common", "alternates"):
        index[table] = {name: sorted((moved[i], *rest) for i, *rest in entries if i in moved)
                        for name, entries in index[table].items()}
    index["strong"] = {name: sorted(moved[i] for i in entries if i in moved)
                       for name, entries in index["strong"].items()}
    index["selection"] = {**index["selection"], "exceptions": {
        name: moved[i] if i is not None else None
        for name, i in index["selection"]["exceptions"].items() if i is None or i in moved}}
    index["objects"] = [old[i] for i in positions]


def omitted_references(rows, objects):
    """[(object name, symbol)] the objects reference that the real link's omitted objects define.
    exit_link.py's omission proof refuses to link while any kept object does this."""
    omitted = set(exit_link.placement_objects(rows))
    names = {build.ledger_object_symbol(row) for row in exit_link.placement_rows(rows)}
    for path in omitted:
        if path.is_file():
            names |= exit_link.external_definitions(exit_link.coff_view(path)[1])
    if not names:
        return []
    found = []
    for path in objects:
        if path not in omitted:
            found.extend((path.name, name) for name in sorted(exit_link.coff_references(path, exit_link.coff_view(path)[2]) & names))
    return found


def definition_losses(before, after, unchecked=None):
    """Return (consumer, root, missing target) for newly orphaned base definitions.

    Facts are COFF object_symbols tuples, keyed by object/source. Follow global
    directives, weak defaults, chained aliases and local import bindings. A real
    definition takes precedence over its alias. Do not require census byte credit.
    """
    old = set().union(*(fact[0] for fact in before.values())) if before else set()
    defined = set().union(*(fact[0] for fact in after.values())) if after else set()
    removed = old - defined
    if not removed:
        return []
    aliases = collections.defaultdict(set)
    for _, _, weaks, alternates, _ in after.values():
        for alias, target in [*weaks, *alternates.items()]:
            aliases[alias].add(target)

    def walk(name, seen):
        if name in defined or name in link_census.LINKER_DEFINED or name in seen:
            return set()
        seen = seen | {name}
        targets = set(aliases.get(name, ()))
        if len(targets) > 1:
            raise ValueError("conflicting weak/alternate targets: " + name)
        if name.startswith(link_census.IMPORT_PREFIX):
            targets.add(name[len(link_census.IMPORT_PREFIX):])
        return ({name} & removed) | set().union(*(walk(t, seen) for t in targets))

    # A resolvable alternate route means this reference has not been lost.
    def resolves(name, seen):
        if name in defined or name in link_census.LINKER_DEFINED:
            return True
        if name in seen:
            return False
        targets = set(aliases.get(name, ()))
        if len(targets) > 1:
            raise ValueError("conflicting weak/alternate targets: " + name)
        if name.startswith(link_census.IMPORT_PREFIX):
            targets.add(name[len(link_census.IMPORT_PREFIX):])
        return any(resolves(t, seen | {name}) for t in targets)

    found = []
    for consumer, (_, refs, weaks, _, includes) in after.items():
        for root in sorted(refs | includes | {name for name, _ in weaks}):
            try:
                if not resolves(root, set()):
                    found.extend((consumer, root, target) for target in sorted(walk(root, set())))
            except ValueError as exc:
                if unchecked is not None:
                    unchecked.add(str(exc))
    return found


CACHE_SCHEMA = 2
CACHE_LIMIT = 96 * 1024 * 1024
ARTIFACT_LIMIT = 256 * 1024 * 1024
REPO = 'Open-BFME/Open-BFME-2'


def cache_root():
    common = Path(git('rev-parse', '--path-format=absolute', '--git-common-dir'))
    root = common / 'bfme-real-link-objects'
    root.mkdir(exist_ok=True)
    return root


def save_cache(path, value):
    raw = json.dumps(value, separators=(',', ':')).encode()
    if len(raw) > CACHE_LIMIT:
        raise ValueError('parsed real-link manifest exceeds cache size cap')
    # Bounded shared cache. Evict before publishing; interrupted writes cannot
    # bless a partial summary. Metadata names the artifact and measured commit.
    files = sorted(path.parent.glob('*.json'), key=lambda p: p.stat().st_mtime_ns)
    total = sum(p.stat().st_size for p in files if p != path)
    for old in files:
        if total + len(raw) <= CACHE_LIMIT:
            break
        if old != path:
            size = old.stat().st_size
            old.unlink(missing_ok=True)
            total -= size
    with tempfile.NamedTemporaryFile(dir=path.parent, prefix='.pending-', suffix='.json', delete=False) as temp:
        temp.write(raw)
        temporary = Path(temp.name)
    temporary.replace(path)


def gh_api(endpoint):
    return subprocess.run(['gh', 'api', endpoint], check=True, capture_output=True,
                          timeout=10).stdout


def object_source(source, provider, sources):
    source = source.replace('\\', '/')
    if 'Code/' in source:
        return source[source.index('Code/'):]
    return sources.get(provider.replace('\\', '/').rsplit('/', 1)[-1], '')


def source_object_names(commit):
    # Pure build.obj_path spelling, without requiring a measured source to exist
    # in this seat. Library members remain provider-keyed, with unknown source.
    found = {}
    for source in git('ls-tree', '-r', '--name-only', commit, '--', 'Code').splitlines():
        if Path(source).suffix.lower() in ('.cpp', '.c', '.asm'):
            stem = str(Path(source).with_suffix('')).replace('\\', '/').replace('/', '_')
            name = ''.join('^' + c.lower() if c.isupper() else c for c in stem) + '.obj'
            found[name] = source
    return found


def parse_manifest_archive(raw, commit, kind='real'):
    """Verify content hashes once; retain facts, never an extracted object tree."""
    import zipfile
    import io
    import hashlib
    import posixpath
    with zipfile.ZipFile(io.BytesIO(raw)) as archive:
        names = archive.namelist()
        manifests = [n for n in names if n.endswith('/image_objects.json') or n == 'image_objects.json']
        if len(manifests) != 1:
            return dict(schema=CACHE_SCHEMA, commit=commit, kind=kind, objects=[],
                        warning='artifact has no unique image_objects.json')
        if sum(e.file_size for e in archive.infolist()) > ARTIFACT_LIMIT:
            raise ValueError('real-link artifact exceeds expanded size cap')
        manifest = manifests[0]
        receipt = json.loads(archive.read(manifest + '.receipt.json'))
        if not receipt.get('map_sha256'):
            raise ValueError('object manifest lacks MAP receipt')
        stubbed, excluded_stubs = set(), []
        if kind == 'diagnostic':
            image_receipt = json.loads(archive.read(posixpath.join(posixpath.dirname(manifest), 'image_receipt.json')))
            if image_receipt.get('kind') != kind or image_receipt.get('commit') != commit:
                raise ValueError('diagnostic receipt kind/commit mismatch')
            if image_receipt.get('map_sha256') != receipt['map_sha256']:
                raise ValueError('diagnostic receipt/manifest MAP mismatch')
            tables = [name for name in names if name == 'stubbed.tsv' or name.endswith('/stubbed.tsv')]
            if len(tables) != 1:
                raise ValueError('diagnostic artifact lacks unique stubbed.tsv')
            rows = list(csv.DictReader(io.StringIO(archive.read(tables[0]).decode('utf-8-sig')), delimiter='\t'))
            stubbed = set(image_receipt['stubbed'])
            if stubbed != {row['name'] for row in rows}:
                raise ValueError('diagnostic stub table/receipt mismatch')
            stubbed |= {row['trap_symbol'] for row in rows if row.get('trap_symbol')}
        entries = json.loads(archive.read(manifest))
        sources = source_object_names(commit)
        objects = []
        for entry in entries:
            path = posixpath.normpath(posixpath.join(posixpath.dirname(manifest), entry['path'].replace('\\', '/')))
            if path.startswith('../') or path.startswith('/'):
                raise ValueError('object path escapes artifact')
            data = archive.read(path)
            if hashlib.sha256(data).hexdigest() != entry['sha256']:
                raise ValueError('object manifest digest mismatch: ' + path)
            if data[:4] == b'\0\0\xff\xff':
                # Short import member: CODE defines a callable plus its IAT;
                # DATA provides only the IAT. Match the archive's real names.
                import struct
                name = data[20:].split(b'\0', 1)[0].decode('latin-1')
                kind = struct.unpack_from('<H', data, 18)[0] & 3
                facts = ({'__imp_' + name} | ({name} if kind == 0 else set()), set(), [], {}, set())
            else:
                facts = link_census.object_symbols(Path(path), data)
            provider_name = entry['provider'].replace('\\', '/').rsplit('/', 1)[-1].lower()
            if kind == 'diagnostic' and provider_name == 'diagnostic_stubs.obj':
                excluded_stubs.append(entry['provider'])
                continue
            # Receipt-listed unresolved names never count as measured providers,
            # even if a future diagnostic writer changes its stub object name.
            facts = (facts[0] - stubbed, *facts[1:])
            objects.append(dict(source=object_source(entry.get('source', ''), entry['provider'], sources),
                                provider=entry['provider'], facts=pack_facts(facts)))
        counts = receipt.get('counts', {})
        result = dict(schema=CACHE_SCHEMA, commit=commit, kind=kind, objects=objects, counts=counts,
                      excluded_stub_objects=excluded_stubs, excluded_stub_names=sorted(stubbed))
        if counts.get('providers_unresolved') or counts.get('archive_members_unresolved'):
            result['coverage_warning'] = 'manifest has unresolved object providers: ' + str(counts)
        return result


def manifest_candidates():
    """Prefer the latest real run, then newest diagnostics from either workflow.

    The dedicated diagnostic workflow can build inputs.ref, not its head_sha;
    its artifact name supplies the source SHA, validated against the receipt.
    """
    import re
    candidates = []
    for workflow in ('real-link.yml', 'diagnostic-link.yml'):
        try:
            runs = json.loads(gh_api(f'repos/{REPO}/actions/workflows/{workflow}/runs'
                                     '?branch=master&status=completed&per_page=1'))['workflow_runs']
        except subprocess.CalledProcessError:
            if workflow == 'real-link.yml':
                raise
            continue  # Older repositories may not have the dedicated workflow.
        if not runs:
            continue
        run = runs[0]
        artifacts = json.loads(gh_api(f'repos/{REPO}/actions/runs/{run["id"]}/artifacts'))['artifacts']
        for artifact in artifacts:
            match = re.fullmatch(r'(real|diagnostic)-link-([0-9a-f]{40})', artifact['name'])
            if not match or artifact['expired']:
                continue
            kind, commit = match.groups()
            if workflow == 'diagnostic-link.yml' and kind != 'diagnostic':
                continue
            if artifact['size_in_bytes'] > ARTIFACT_LIMIT:
                continue
            candidates.append(dict(kind=kind, commit=commit, artifact=artifact['id'],
                                   created=artifact.get('created_at', run.get('created_at', ''))))
    return sorted(candidates, key=lambda c: (c['kind'] == 'real', c['created'], c['artifact']), reverse=True)


def load_real_manifest():
    """Real evidence first, diagnostic fallback with all trap providers excluded."""
    root = cache_root()
    latest = root / 'latest.json'
    selected = json.loads(latest.read_text()) if latest.exists() else {}
    if (selected.get('schema') != CACHE_SCHEMA or not latest.exists()
            or time.time() - latest.stat().st_mtime >= 300):
        selected = dict(schema=CACHE_SCHEMA, candidates=manifest_candidates())
        save_cache(latest, selected)
    last = None
    warnings = []
    for candidate in selected['candidates']:
        commit, kind, artifact = candidate['commit'], candidate['kind'], candidate['artifact']
        path = root / (kind + '-' + commit + '.json')
        data = json.loads(path.read_text()) if path.exists() else {}
        if (data.get('schema') != CACHE_SCHEMA or data.get('commit') != commit
                or data.get('kind') != kind or data.get('artifact') != artifact):
            try:
                data = parse_manifest_archive(gh_api(f'repos/{REPO}/actions/artifacts/{artifact}/zip'), commit, kind)
            except (ValueError, KeyError, OSError, subprocess.SubprocessError) as exc:
                data = dict(schema=CACHE_SCHEMA, commit=commit, kind=kind, objects=[], warning=str(exc))
            data['artifact'] = artifact
            save_cache(path, data)
        last = data
        if data.get('warning') or not data['objects']:
            warnings.append(f"{kind}-link {commit}: " + data.get('warning', 'empty object manifest'))
            continue
        if warnings:
            data = {**data, 'fallback_warnings': warnings}
        return data
    if last is None:
        raise ValueError('no available real-link or diagnostic-link artifact')
    return {**last, 'fallback_warnings': warnings}


def pack_facts(facts):
    defs, refs, weak, aliases, includes = facts
    return [sorted(defs), sorted(refs), list(weak), aliases, sorted(includes)]


def unpack_facts(facts):
    return set(facts[0]), set(facts[1]), facts[2], facts[3], set(facts[4])


def library_definitions(names):
    """Use exit_link's /MD archives and its generated retail-import routing."""
    import link_cycle
    defined = set(link_census.LINKER_DEFINED) | set(link_cycle.ABSOLUTE)
    for path in link_cycle.runtime_libraries():
        defined |= link_census.library_symbols(path)
    imported = link_census.retail_imports()
    for name in names - defined:
        request = name if name.startswith('__imp_') else '__imp_' + name
        entries, missing = link_cycle.import_def_entries({request}, imported)
        if entries and not missing:
            defined.add(name)
    return defined


def source_alternates(tip):
    """Committed directives only: unrelated dirty work cannot supply evidence.

    A source directive is a cheap conservative requirement, even if its alias
    has no observed object reference. A real definition of the alias overrides it.
    Multiline/macro/comment spellings stay unchecked rather than proving a loss.
    """
    import re
    done = subprocess.run(['git', 'grep', '-n', '-I', '-i', '-e', '/alternatename:',
                           tip, '--', 'Code', 'reference'], cwd=link_check.ROOT,
                          capture_output=True, text=True, timeout=5)
    if done.returncode not in (0, 1):
        raise ValueError('source alternatename grep failed')
    found, unchecked = {}, []
    pattern = re.compile(r'^\s*#\s*pragma\s+comment\s*\(\s*linker\s*,\s*"/alternatename:([^=\s"]+)=([^\s"]+)"\s*\)', re.I)
    for line in done.stdout.splitlines():
        _, source, number, text = line.split(':', 3)
        match = pattern.match(text)
        if match:
            alias, target = match.groups()
            found[source + ':' + number] = (set(), {alias}, [], {alias: target}, set())
        else:
            unchecked.append(source + ':' + number)
    return found, unchecked


def removed_definition_guard(base, tip, verified):
    """Measured objects plus byte-gated tip replacements; missing proof warns."""
    started = time.monotonic()
    changes = changed_sources(base, tip)
    if not changes and not verified and not changed_identities(base, tip):
        return 0
    manifest = load_real_manifest()
    evidence = manifest.get('kind', 'real') + '-link ' + manifest['commit']
    for warning in manifest.get('fallback_warnings', ()):
        print('definition guard: UNCHECKED evidence: ' + warning)
    if manifest.get('coverage_warning'):
        print('definition guard: UNCHECKED [' + evidence + ']: ' + manifest['coverage_warning'])
    if manifest.get('warning') or not manifest['objects']:
        print('definition guard: UNCHECKED: ' + manifest.get('warning', 'empty real-link manifest')
              + ' [' + evidence + ']')
        return 0
    measured = manifest['commit']
    if subprocess.run(['git', 'merge-base', '--is-ancestor', measured, base],
                      cwd=link_check.ROOT, capture_output=True).returncode:
        print('definition guard: UNCHECKED [' + evidence + ']: measured commit is not an ancestor of outgoing base')
        return 0
    delta = set(git('diff', '--no-renames', '--name-only', measured, tip, '--',
                    *link_census.CENSUS_INPUTS, *('tools/' + n for n in link_census.TOOL_FILES)).splitlines())
    # Conservatively widen include/compiler drift. Only the byte gate can make
    # such consumers current; this guard never compiles or trusts a stale .obj.
    broad = any(not (p.startswith('reverse/') or Path(p).suffix.lower() in ('.cpp', '.c', '.asm')) for p in delta)
    changed = {p for p in delta if Path(p).suffix.lower() in ('.cpp', '.c', '.asm')}
    live = set(git('ls-tree', '-r', '--name-only', tip, '--', 'Code').splitlines())
    before, after, unchecked = {}, {}, set()
    unknown_sources = []
    for entry in manifest['objects']:
        source, provider = entry['source'], entry['provider']
        key = source or provider
        if not source:
            unknown_sources.append(provider)
        facts = unpack_facts(entry['facts'])
        before[provider] = facts
        if source and source not in live:
            continue
        if source in changed or (broad and source):
            # Keep unchecked providers as possible definitions, but never use
            # their old imports as current evidence. This cannot prove a loss.
            unchecked.add(source)
            after[key] = (facts[0], set(), [], {}, set())
        else:
            after[key] = facts if source else (facts[0], set(), [], {}, set())
    verified = set(verified)
    for source in sorted(verified):
        # The hook supplies only its completed byte-gated cohort. Never consult
        # another local object merely because it exists in build/match.
        obj = build.obj_path(link_check.ROOT / source)
        if not obj.is_file() or exit_link.is_placement_source(source):
            if not exit_link.is_placement_source(source):
                unchecked.add(source)
            after.pop(source, None)
            continue
        raw = obj.read_bytes()
        after[source] = link_census.object_symbols(obj, raw)
        unchecked.discard(source)
    unchecked |= (changed & live) - verified
    directives, unparsed = source_alternates(tip)
    after.update({'source directive ' + source: facts for source, facts in directives.items()})
    names = set().union(*(f[0] for f in before.values())) - set().union(*(f[0] for f in after.values()))
    names |= {name for f in after.values() for pair in [*f[2], *f[3].items()] for name in pair}
    try:
        supplied = library_definitions(names)
    except (OSError, ValueError, SystemExit) as exc:
        print(f'definition guard: UNCHECKED libraries [{evidence}]: {exc}')
        return 0
    after['real-link libraries'] = (supplied, set(), [], {}, set())
    ambiguous = set()
    losses = definition_losses(before, after, ambiguous)
    for warning in sorted(ambiguous):
        print(f'definition guard: UNCHECKED [{evidence}]: {warning}')
    for source in sorted(unchecked):
        print('definition guard: UNCHECKED tip object: ' + source + ' [' + evidence + ']')
    for provider in unknown_sources:
        print('definition guard: UNCHECKED manifest source: ' + provider + ' [' + evidence + ']')
    for source in unparsed:
        print('definition guard: UNCHECKED source directive: ' + source + ' [' + evidence + ']')
    # An unchecked changed unit could supply a replacement under a new name.
    # Do not turn unknown provider evidence into a proven absence.
    if unchecked and losses:
        for consumer, root, target in losses[:20]:
            print(f'  UNCHECKED possible loss {target}: {consumer} references {root} [{evidence}]')
        losses = []
    for consumer, root, target in losses[:30]:
        print(f'  LOST EXTERNAL {target}: {consumer} references {root} [{evidence}]')
    print(f'definition guard: {evidence}, {len(verified)} byte-gated tip units, '
          f'{len(losses)} proven losses ({time.monotonic() - started:.3f}s)')
    return 1 if losses else 0

def audit(base, tip, verified):
    changes = changed_sources(base, tip)
    identities = changed_identities(base, tip)
    if not changes and not verified and not identities:
        print("link batch audit: no changed source objects")
        return 0
    try:
        guard = removed_definition_guard(base, tip, verified)
    except (OSError, ValueError, KeyError, SystemExit, subprocess.SubprocessError) as exc:
        print(f"definition guard: UNCHECKED: {exc}")
        guard = 0
    if guard:
        return guard
    if not link_check.INDEX.exists():
        print("link batch audit: INCONCLUSIVE: census index missing; fetch with link_check.py --fetch-index")
        return 2
    index = link_check.load_index()
    meta = index.get("meta", {})
    # Census publication changes status/history, not compiler inputs. Accept
    # those commits without requiring a new census of its own publication.
    exact_base = bool(meta.get("commit") and meta.get("clean_tree", True) and not git(
        "diff", "--name-only", meta["commit"], base, "--", *link_census.CENSUS_INPUTS,
        *("tools/" + name for name in link_census.TOOL_FILES)))
    if not exact_base:
        print(f"link batch audit: INCONCLUSIVE baseline: index at {meta.get('commit', '?')}, "
              f"outgoing base {base}; findings below are provisional since-index changes")
    try:
        link_check.require_common_index(index)
    except SystemExit as exc:
        print(f"link batch audit: INCONCLUSIVE: {exc}")
        return 2
    rows = link_census.ledger()
    truth = link_census.RetailTruth(rows)
    sources = {row["source"] for row in rows} | {row["source"] for row in link_census.data_ledger()}
    scope = (changes | set(verified)) & sources
    # Rejudge unchanged copies when a ledger/pin changes their own or a
    # relocation's identity. Their cached census verdict is no longer current.
    if identities:
        scope |= affected_sources(index, identities) & sources
    old_by_source = {source: entry["object"] for source, entry in index["blockers"].items()
                     if "object" in entry}
    removed = {old_by_source[source] for source in changes if source in old_by_source and source not in sources}
    replacements = []
    missing = []
    for source in sorted(scope):
        obj = build.obj_path(link_check.ROOT / source)
        if not obj.is_file() or not link_census.object_current(link_check.ROOT / source, obj):
            missing.append(source)
        else:
            replacements.append(obj)
    # Before the receipt check, which a byte-verified object can still fail. Only objects known to be
    # current: scope also holds consumers of a changed identity, whose object here may predate a fix.
    built = {build.obj_path(link_check.ROOT / source) for source in sorted(scope & set(verified))} | set(replacements)
    refused = omitted_references(rows, sorted(obj for obj in built if obj.is_file()))
    if refused:
        for obj, name in refused[:20]:
            print(f"  OMITTED {obj} references {name}, defined in a placement object the real link leaves out")
        print(f"link batch audit: FAILED: {len(refused)} reference(s) to omitted objects; "
              "exit_link.py would refuse to link. Reach the row the omitted thunk jumps to instead")
        return 1
    if missing:
        print(f"link batch audit: INCONCLUSIVE: {len(missing)} source object(s) lack current receipts; "
              f"first: {missing[0]}")
        return 2
    # A changed ledger may remove an object without deleting its source path.
    current_objects = {build.obj_path(link_check.ROOT / source).name for source in sources}
    removed |= {obj for source, obj in old_by_source.items() if source not in sources and obj not in current_objects}
    before_rank = {name: i for i, name in enumerate(index["objects"])
                   if name not in index.get("forgotten", ())}
    after_rank = link_check.link_rank(rows)
    updated = overlay(index, replacements, removed, truth)
    updated["selection"] = {**index["selection"], "owners": dict(link_census.ledger_owners(rows))}
    touched = set()
    changed_objects = removed | {obj.name for obj in replacements}
    for name, entries in index["comdat"].items():
        if any(index["objects"][i] in changed_objects for i, _, _ in entries):
            touched.add(name)
    for name, entries in index["strong"].items():
        if any(index["objects"][i] in changed_objects for i in entries):
            touched.add(name)
    for name, entries in index["common"].items():
        if any(index["objects"][i] in changed_objects for i, _ in entries):
            touched.add(name)
    for obj in replacements:
        copies, strong, _, _ = link_census.object_facts(obj, truth)
        touched.update(name for name, _, _, _ in copies)
        touched.update(strong)
        touched.update(link_census.common_definitions(obj))
    # A provider edit can break a caller whose source did not change. Read
    # those current objects too; never treat missing/stale consumers as clean.
    consumers = (affected_sources(index, touched) & sources) - scope if touched else set()
    for source in sorted(consumers):
        obj = build.obj_path(link_check.ROOT / source)
        if not obj.is_file() or not link_census.object_current(link_check.ROOT / source, obj):
            print(f"link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: {source}")
            return 2
    findings = []
    for name in sorted(touched):
        old_holder, old_verdict = selected(index, name, before_rank)
        new_holder, new_verdict = selected(updated, name, after_rank)
        if old_holder and old_verdict != "wrong" and new_verdict == "wrong":
            findings.append((name, old_holder, new_holder, "wrong selected provider"))
        elif old_holder and not new_holder and old_verdict != "wrong":
            findings.append((name, old_holder, None, "provider disappeared"))
    reorder(updated, after_rank)
    # A new destination must preserve the linked donors it absorbed too.
    retired_clean = {entry["object"]: source for source, entry in index["blockers"].items()
                     if source not in sources and entry.get("linked")}
    inherited = collections.defaultdict(set)
    if retired_clean:
        for row in rows:
            for owner in index["selection"]["owners"].get(row.get("name"), ()):
                if owner in retired_clean:
                    inherited[row["source"]].add(retired_clean[owner])
    lost = collections.Counter()
    for source in sorted(scope | consumers):
        prior = index["blockers"].get(source, {})
        if not prior.get("linked") and not inherited[source]:
            continue
        credited = inherited[source] | ({source} if prior.get("linked") else set())
        obj = build.obj_path(link_check.ROOT / source)
        result = link_check.check_object(obj, updated, truth, source)
        for kind in ("unresolved", "duplicates", "comdat", "selected", "addresses"):
            for entry in result.get(kind, ()):
                name = entry[0] if isinstance(entry, (tuple, list)) else entry
                before, _ = selected(index, name, before_rank)
                after, _ = selected(updated, name, after_rank)
                lost[(name, before, after, kind + " in " + source)] += sum(
                    index["bytes"].get(s, 0) for s in credited)
    print(f"link batch audit: {len(replacements)} current object(s), {len(removed)} retired; "
          f"index {meta.get('date', '?')} at {base}")
    for name, before, after, reason in findings:
        print(f"  REVIEW {reason}: {name}; selected {before or '(none)'} -> {after or '(none)'}; "
              "affected consumer bytes require census confirmation")
    for (name, before, after, reason), byte_count in sorted(lost.items()):
        label = "LOST" if exact_base else "POSSIBLE LOSS"
        print(f"  {label} {byte_count:,} previously linked source bytes: {reason}: {name}; "
              f"provider {before or '(none)'} -> {after or '(none)'}")
    if lost:
        print("link batch audit: " + ("FAILED" if exact_base else "INCONCLUSIVE") +
              "; verify affected consumers and record repairs")
        return 1 if exact_base else 2
    elif not exact_base:
        print("link batch audit: INCONCLUSIVE: no provisional finding from the older index")
    else:
        print("link batch audit: no linking regression found in the checked scope")
    return 0 if exact_base else 2


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", required=True)
    parser.add_argument("--tip", required=True)
    parser.add_argument("--sources-from", metavar="FILE", required=True,
                        help="NUL-delimited byte-verified source paths")
    args = parser.parse_args()
    try:
        raw = Path(args.sources_from).read_bytes()
        if raw and not raw.endswith(b"\0"):
            raise ValueError("unterminated verified source list")
        verified = [part.decode("utf-8") for part in raw.split(b"\0") if part]
        return audit(args.base, args.tip, verified)
    except (OSError, ValueError, KeyError, csv.Error, SystemExit, subprocess.CalledProcessError,
            link_census.MissingObject) as exc:
        print(f"link batch audit: INCONCLUSIVE: {exc}")
    return 2


if __name__ == "__main__":
    sys.exit(main())
