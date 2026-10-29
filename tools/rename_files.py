#!/usr/bin/env python3
"""The mechanical file lane: rename address-named sources whose rows are real.

Code/ units are still called `Rva002A9DACGet.cpp`, `DrawableRva00278644.cpp`
or `Object_Rva0028AF65.cpp` while every row they own is already spelled
`?getSupplyBoxValue@Player@@QAEHXZ` (measured 2026-10-21: 13,225 address-named
units, 647 of them renameable; 11,946 refused because a row is still
placeholder-named, so the lane grows as the naming lanes land). The identity is
settled; only the file name still hides it. That makes this the one rename
lane with NO naming judgement in it, so it is a script rather than an agent at
minutes a file -- and a script refuses the ambiguous cases uniformly instead
of each agent inventing its own answer. It is a port of Open-BFME-1's
tools/rename_addressed_sources.py (same proposals, same refusals) onto BFME 2:
Code/ paths, reverse/ ledgers, and one placeholder definition shared with
tools/name_metric.py and tools/rename.py instead of BFME 1's own prefix list,
so `Va<hex>`, `Rva<hex><Suffix>`, `<Class>Rva<hex>` and `Bfme*` stems are
all "address-named" by the same rule the readability metric scores.

The proposal follows from the rows alone:

  one row               Class_method.cpp (a free function: method.cpp; a
                        constructor or destructor: Class.cpp)
  several, one class    Class.cpp
  ignored               __ehhandler$/__unwindfunclet$ rows whose parent the
                        file owns; ??_G/??_E glue counts for its class only

and is refused, as BFME 1 refuses it, when a row is still placeholder-named,
is an operator, a template or unparseable compiler glue, when the rows span
several classes or are several free functions, when the proposed stem is
itself a placeholder, and when the target exists (case-insensitively: the
pre-commit hook rejects paths differing only in case). It also refuses, up
front, what tools/rename.py's `file` kind would refuse (a vendored unit, one
keyed in a protected path-keyed register, one expanding __FILE__, one another
file #includes, an approved retail TU, a name recorded canonical), so the plan
counts are honest; rename.py remains the authority and re-checks every one.

It never invents a name, never merges files, and never touches a row's name:
each rename goes through tools/rename.py's library API (plan_file), so every
path-keyed column, the name_basis.csv record and the journal are rename.py's.

Basis. Every stem lands as `inferred` with `mechanical:<rows>` evidence, the
form tools/rename.py verifies (check_basis -> mechanical_stems: the stem must
be derived from a real-named row the unit owns). It is never canonical: a
file name is only as proven as the rows it is read from, most rows are
unverified names, and a canonical record is permanent -- nothing could
replace the stem even after the row it came from is renamed or disputed.
(An earlier `canonical:rows` basis, and an `auto` mode that switched to it as
soon as rename.py accepted it, were declined in review; `--basis auto` is
kept as a plain alias of `mechanical`.) When a function or class rename later
changes the row a stem was derived from, the stem should be re-derived by
this lane; that needs rename.py to let a mechanical stem replace a stem it
recorded as mechanical, which it does not yet.

Batches. `--apply --limit N` renames N files under one ledger lock, one
claim set and ONE journal in build/rename-journal/ (rename.py's format, so a
batch killed mid-way is undone by `python3 tools/rename.py recover`), then
verifies the batch with one ./build.sh over every renamed unit plus the
commit hooks' ledger checks. A failed batch is restored byte for byte and its
members retried one at a time, so one bad unit cannot hold the lane. Nothing
is committed: the renames stay staged (`git mv`), for the lander. A batch is
refused while check_csv already fails (AGENTS.md step 2); in a tree another
worker left dirty, `--tolerate-failing-checks` refuses only the check_csv
lines the batch adds.

  python3 tools/rename_files.py [--under DIR] [--show N] [--show-refusals]
  python3 tools/rename_files.py --apply --limit 20 [--batch 10]

`--json PATH` also writes the run as one JSON object (counts, refusal
reasons, the proposals taken, what landed, what was refused and why, the
claims kept, the paths to stage), so the daily renaming pass reads the
lane's result instead of scraping its prose.
"""
import argparse
import collections
import json
import posixpath
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import name_metric  # noqa: E402
import tu_map  # noqa: E402
import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

FUNCLET = re.compile(r"(?:__ehhandler\$|__unwindfunclet\$)(\?.+?)(?:\$\d+)?$")
LABEL = re.compile(r"\$L\d+|Unwind@[0-9A-Fa-f]+")
PARENT = re.compile(r"(?:^|[\s;])parent=([^;\s]+)")
GLUE = re.compile(r"\?\?_[GE]([A-Za-z_]\w*)@@")
BASES = {"mechanical": "inferred"}
NOT_UNITS = ("Code/masm_dumps/",)


# ---------------------------------------------------------------- proposals

def identity(row, owned_names):
    """('row', scope parts) for a row that names the file, ('class', Class)
    for ??_G/??_E glue, ('skip', None) for an EH funclet (`__ehhandler$`,
    `__unwindfunclet$`, `$L<n>`, `Unwind@<va>`) whose `parent=` the file owns,
    or ('refuse', why). Operators, templates, nested scopes and other compiler
    labels are refused as BFME 1 refuses them: their spelling makes no file
    name anybody wants, and a guess there is silent."""
    name = row.get("name", "")
    parent = PARENT.search(row.get("notes", "") or "")
    funclet = FUNCLET.fullmatch(name)
    if parent or funclet or LABEL.fullmatch(name):
        parent = parent.group(1) if parent else (funclet.group(1) if funclet else None)
        if parent in owned_names:
            return "skip", None
        return "refuse", f"funclet {name} belongs to a parent this file does not own"
    glue = GLUE.match(name)
    if glue:
        return "class", glue.group(1)
    scope = rename.scope_of(name)
    if not scope:
        if any(rename.is_placeholder(word, "class") for word in rename.IDENT.findall(name)):
            return "refuse", f"row still placeholder-named: {name}"
        return "refuse", f"row {name} is an operator, template or compiler glue"
    parts = [p for p in scope.split("::") if p]
    if len(parts) > 2:
        if any(rename.is_placeholder(p.lstrip("~"), "function") for p in parts):
            return "refuse", f"row still placeholder-named: {name}"
        return "refuse", f"row {name} has a nested scope ({scope}): no single Class_method"
    return "row", parts


def proposal(rows):
    """(stem, None) for the basename these rows justify, or (None, reason)."""
    owned = {r.get("name", "") for r in rows}
    named, glue = [], set()
    for row in rows:
        kind, value = identity(row, owned)
        if kind == "refuse":
            return None, value
        if kind == "class":
            glue.add(value)
        elif kind == "row":
            named.append((row.get("name", ""), value))
    for name, parts in named:
        if any(rename.is_placeholder(p.lstrip("~"), "function") for p in parts):
            return None, f"row still placeholder-named: {name}"
    for cls in glue:
        if rename.is_placeholder(cls, "class"):
            return None, f"row still placeholder-named: ??_G/??_E of {cls}"
    if not named:
        return None, "no row names the file (compiler glue only)"
    classes = {parts[-2] for _name, parts in named if len(parts) > 1} | glue
    if len(classes) > 1:
        return None, "rows span %d classes (%s)" % (len(classes), ", ".join(sorted(classes)))
    if len(named) == 1 and not glue:
        parts = named[0][1]
        ident = parts[-1].lstrip("~")
        if len(parts) == 1:
            return ident, None
        return (parts[-2] if ident == parts[-2] else f"{parts[-2]}_{ident}"), None
    if not classes:
        return None, "several free functions with no shared owner"
    return classes.pop(), None


# ---------------------------------------------------------------- the tree

class Tree:
    """What the up-front refusals read, each loaded once for the whole plan
    (rename.plan_file reads them per call, which is fine for one file and too
    slow for ten thousand)."""

    def __init__(self, ctx):
        self.ctx = ctx
        self.tracked = set(ctx.git("ls-files", "--", "Code").splitlines())
        self.tracked_lower = {p.lower() for p in self.tracked}
        self.keyed = set()
        for rel in rename.PROTECTED_PATH_KEYED:
            raw = ctx.read(rel)
            if raw:
                for line in raw.decode("utf-8", errors="replace").splitlines():
                    self.keyed.update(re.split(r"[\t,]", line))
        self.approved = {r.get("tu") for r in ctx.dicts(rename.TU_MAP) if tu_map.canonical_tu(r)}
        self.canonical = {r.get("new") for r in ctx.dicts(rename.NAME_BASIS)
                          if (r.get("basis") or "").startswith("canonical")}
        included = ctx.git("grep", "-h", "-i", "-o", "-E", r"#[[:space:]]*include[[:space:]]*[<\"][^>\"]*[>\"]",
                           "--", *rename.SEARCH_ROOTS)
        self.included = {posixpath.basename(re.split(r"[<\"]", line, 1)[-1].rstrip('>"')).lower()
                         for line in included.splitlines()}

    def refusal(self, source, rows):
        """Why tools/rename.py's file kind would refuse `source`, or None."""
        return next(self.refusals(source, rows), None)

    def refusals(self, source, rows):
        """Every reason tools/rename.py's file kind would refuse `source`, in order."""
        ctx = self.ctx
        if source not in self.tracked:
            yield f"{source} is not tracked"
        if rename.is_vendored_path(ctx, source):
            yield "vendored or SDK source: its names are upstream's"
        if source in self.keyed:
            yield "keyed in a protected path-keyed register (needs a Verifier-Change commit)"
        if source in self.approved:
            yield "an approved retail TU path in tu_map.csv (canonical)"
        stem = posixpath.splitext(posixpath.basename(source))[0]
        if source in self.canonical or stem in self.canonical:
            yield "recorded canonical in name_basis.csv"
        if posixpath.basename(source).lower() in self.included:
            yield "#included by another file (phase 1 does not rewrite includes)"
        if self.expands_file(source):
            yield "expands __FILE__: the path reaches its bytes"

    def expands_file(self, source):
        """Whether `source` expands __FILE__ outside comments and literals (by content, from
        the shared picker cache in a picker run: tools/picker_cache.py)."""
        ctx = self.ctx

        def check(data):
            return "__FILE__" in name_metric.strip((data or b"").decode("utf-8", errors="surrogateescape"))
        import picker_cache
        key = picker_cache.blob_key(source, ctx.root)
        if key is None:
            return check(ctx.read(source))
        if _EXPANDS_FILE[0] is None:
            here = Path(__file__).resolve()
            _EXPANDS_FILE[0] = picker_cache.FileMemo("rename_files-expands-file",
                                                     [here, here.with_name("name_metric.py")])
        return _EXPANDS_FILE[0].get(key, lambda: check(ctx.read(source)))


_EXPANDS_FILE = [None]      # the picker cache's FileMemo, made on first use


def owned_rows(ctx):
    """source -> [row] for every Code/ .cpp/.c unit that owns a matched row."""
    owned = collections.defaultdict(list)
    for row in ctx.rows():
        owned[row.get("source", "")].append(row)
    return {s: rows for s, rows in owned.items()
            if s.startswith("Code/") and s.endswith(rename.SOURCE_SUFFIXES) and not rename.is_generated(s)
            and not s.startswith(NOT_UNITS) and any(r.get("status") == "matched" for r in rows)}


def candidates(ctx, under="", basis="rows"):
    """([(source, target, rows)], [(source, reason)]) over the whole ledger."""
    owned = owned_rows(ctx)
    tree = Tree(ctx)
    taken = set(tree.tracked_lower) | {s.lower() for s in owned}
    picked, refused = [], []
    for source in sorted(owned):
        if under and not source.startswith(under.rstrip("/") + "/"):
            continue
        stem = posixpath.splitext(posixpath.basename(source))[0]
        if not rename.is_placeholder(stem, "file"):
            continue
        rows = owned[source]
        new_stem, why = proposal(rows)
        if new_stem is None:
            refused.append((source, why))
            continue
        try:
            rename.check_new_identifier(new_stem, "file")
        except Refusal as error:
            refused.append((source, f"proposed name {new_stem}: {error}"))
            continue
        target = posixpath.join(posixpath.dirname(source), new_stem + posixpath.splitext(source)[1])
        if target.lower() in taken or ctx.path(target).exists():
            refused.append((source, f"target {target} already exists"))
            continue
        why = tree.refusal(source, rows)
        if why:
            refused.append((source, why))
            continue
        taken.add(target.lower())
        picked.append((source, target, rows))
    return picked, refused


def evidence_for(basis, rows):
    owned = {r.get("name", "") for r in rows}
    names = [r["name"] for r in rows if identity(r, owned)[0] != "skip"]
    shown = ";".join(names[:3]) + (f" +{len(names) - 3} more" if len(names) > 3 else "")
    return f"mechanical:{shown}"


# ---------------------------------------------------------------- apply

def basis_supported(basis):
    """None when tools/rename.py accepts `basis`, else the reason it does not."""
    try:
        rename.basis_kind(BASES[basis])
    except Refusal as error:
        return f"tools/rename.py does not accept {BASES[basis]} ({error}); use --basis mechanical"
    return None


def resolve_basis(basis):
    """`auto` is an alias of `mechanical`: there is no other basis to upgrade to."""
    return "mechanical" if basis == "auto" else basis


def check_lines(ctx):
    """check_csv's full report as a set of lines (empty when it passes)."""
    if not ctx.path("tools/check_csv.py").exists():
        return set()
    result = subprocess.run([sys.executable, "tools/check_csv.py"], cwd=ctx.root, capture_output=True, text=True)
    if not result.returncode:
        return set()
    return {line.strip() for line in (result.stdout + result.stderr).splitlines() if line.strip()}


def tolerant_checks(ctx):
    """A `checks` callable that reports only check_csv lines the batch ADDS to
    the ones failing before it (find_declared_unmatched still has to be
    silent on every renamed unit). For a tree another worker left dirty
    (unstaged renames make check_csv fail on files this lane never touches):
    the lander still runs the full hooks before a commit."""
    before = check_lines(ctx)

    def csv_checks(ctx, plan):
        problems = [f"check_csv: {line}" for line in sorted(check_lines(ctx) - before)]
        units = sorted({rel for rel in plan.after if rel.startswith("Code/") and rel.endswith(rename.SOURCE_SUFFIXES)} |
                       {new for _old, new in plan.moves})
        if units and ctx.path("tools/find_declared_unmatched.py").exists():
            result = subprocess.run([sys.executable, "tools/find_declared_unmatched.py", "--fail", *units],
                                    cwd=ctx.root, capture_output=True, text=True)
            if result.returncode:
                problems.append("find_declared_unmatched: " +
                                " | ".join((result.stdout + result.stderr).strip().splitlines()[-5:]))
        return problems

    def checks(ctx, plan):
        # the hook's checks run beside these, and a signal cancels them as in rename.ledger_checks;
        # an unstaged ledger edit another worker left is the dirt this lane tolerates
        return rename.ledger_checks(ctx, plan, csv_checks=csv_checks, skip=("ledger_guard",))
    return checks


def dry_plan(ctx, source, target, rows, basis):
    """None when tools/rename.py would plan this rename, else its refusal."""
    try:
        rename.plan_rename("file", ctx=ctx, source=source, new=target, basis=BASES[basis],
                           evidence=evidence_for(basis, rows))
    except Refusal as error:
        return str(error)
    return None


def _journal(ctx, combined, claimed, previous):
    """Rewrite the batch journal (rename.py's format, so `rename.py recover`
    restores it): the new one is written before the old one goes."""
    path = rename.write_journal(ctx, combined, claimed)
    if previous is not None and previous.exists():
        previous.unlink()
    return path


def _merge_claims(into, more):
    into.new += [k for k in more.new if k not in into.new]
    into.tokens.update(more.tokens)
    into.unconfirmed += more.unconfirmed


def apply_batch(ctx, picks, basis, *, claim=True, verify=rename.build_verify, checks=rename.ledger_checks):
    """Rename every pick, verify once, restore everything on any failure.
    Returns (plans, claimed); raises Refusal or VerifyFailed."""
    rename.refuse_pending_journal(ctx)
    if checks:
        already = checks(ctx, rename.Plan("file", "batch", "batch", BASES[basis], "", None, None))
        if already:
            raise Refusal(f"the ledger checks already fail before the batch: {already[0][:300]}; "
                          "repair the ledger first (AGENTS.md step 2)")
    combined = rename.Plan("file", "batch", "batch", BASES[basis], "", None, None,
                           old_word=f"{len(picks)} address-named sources", new_word="their row names")
    claimed = rename.Claimed()
    journal, moved, plans = None, [], []
    try:
        for source, target, rows in picks:
            fresh = rename.Context(ctx.root, object_scan=ctx.object_scan)
            plan = rename.plan_rename("file", ctx=fresh, source=source, new=target, basis=BASES[basis],
                                      evidence=evidence_for(basis, rows))
            plan.claims = rename.claim_keys(plan)
            _merge_claims(claimed, rename.take_claims(plan.claims, claim, ctx.root))
            for rel, data in plan.before.items():
                combined.before.setdefault(rel, data)
            combined.moves += plan.moves
            combined.moved_bytes.update(plan.moved_bytes)
            journal = _journal(ctx, combined, claimed, journal)
            for old, new in plan.moves:
                result = subprocess.run(["git", "-C", str(ctx.root), "mv", "--", old, new],
                                        capture_output=True, text=True)
                if result.returncode:
                    raise Refusal(f"git mv {old} {new} failed: {result.stderr.strip()[:200]}")
                moved.append((old, new))
            for rel, data in plan.after.items():
                ctx.path(rel).parent.mkdir(parents=True, exist_ok=True)
                ctx.path(rel).write_bytes(data)
                combined.after[rel] = data
            plans.append(plan)
        combined.verify = [new for _old, new in combined.moves]
        if not verify(ctx, combined.verify):
            raise VerifyFailed(f"./build.sh refused the batch of {len(plans)}; every file restored")
        problems = checks(ctx, combined) if checks else []
        if problems:
            raise VerifyFailed(f"the commit hooks would refuse the batch [{rename.refusing(problems)}] "
                               f"({problems[0][:300]}); every file restored")
    except BaseException:
        rename.unmove(ctx, combined, moved)
        rename.restore(ctx, combined.before)
        if journal is not None and journal.exists():
            journal.unlink()
        claimed.release(ctx.root)
        raise
    if journal is not None and journal.exists():
        journal.unlink()
    ctx.kept |= combined.written()
    return plans, claimed


def run_batches(ctx, picks, basis, *, batch=10, claim=True, verify=rename.build_verify,
                checks=rename.ledger_checks, out=print):
    """Apply `picks` in batches; a failed batch is retried one unit at a time.
    Returns (landed plans, [(source, reason)] failures, claim labels kept)."""
    from portable_lock import lock, unlock
    landed, failed, kept = [], [], []
    handle = ctx.path(rename.LOCK).open("a")
    lock(handle, exclusive=True, wait_notice="rename_files: waiting for the ledger lock...")
    try:
        groups = [picks[i:i + batch] for i in range(0, len(picks), max(1, batch))]
        while groups:
            group = groups.pop(0)
            try:
                plans, claimed = apply_batch(ctx, group, basis, claim=claim, verify=verify, checks=checks)
            except (Refusal, VerifyFailed) as error:
                if len(group) > 1:
                    out(f"rename_files: batch of {len(group)} refused ({error}); retrying one at a time")
                    groups = [[pick] for pick in group] + groups
                else:
                    failed.append((group[0][0], str(error)))
                    out(f"rename_files: REFUSED {group[0][0]}: {error}")
                continue
            landed += plans
            kept += [rename.claim_label(k) for k in claimed.new]
            for plan in plans:
                out(f"rename_files: OK {plan.old} -> {plan.new}")
    finally:
        unlock(handle)
        handle.close()
    return landed, failed, kept


# ---------------------------------------------------------------- CLI

def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--apply", action="store_true", help="perform the renames (default: print the plan)")
    parser.add_argument("--under", default="", metavar="DIR", help="only sources under this Code/ directory")
    parser.add_argument("--limit", type=int, default=0, metavar="N", help="take at most N files")
    parser.add_argument("--batch", type=int, default=10, metavar="N",
                        help="files per ./build.sh when applying (default 10)")
    parser.add_argument("--basis", choices=sorted(BASES) + ["auto"], default="mechanical",
                        help="mechanical (default; `auto` is an alias): inferred with mechanical:<rows> "
                             "evidence -- never canonical")
    parser.add_argument("--tolerate-failing-checks", action="store_true",
                        help="apply even though check_csv already fails, refusing only problems a batch adds")
    parser.add_argument("--show", type=int, default=20, metavar="N", help="proposals to print in plan mode")
    parser.add_argument("--show-refusals", action="store_true", help="list every refusal")
    parser.add_argument("--check", action="store_true",
                        help="plan mode: also plan each shown proposal through tools/rename.py (writes nothing)")
    parser.add_argument("--no-claim", action="store_true", help="skip tools/claims.py (tests, offline)")
    parser.add_argument("--json", metavar="PATH", help="also write the run as one JSON object to PATH")
    parser.add_argument("--no-object-scan", action="store_true", help=argparse.SUPPRESS)
    parser.add_argument("--root", default=str(rename.ROOT), help=argparse.SUPPRESS)
    args = parser.parse_args(argv)

    ctx = rename.Context(args.root, object_scan=not args.no_object_scan)
    args.basis = resolve_basis(args.basis)
    picked, refused = candidates(ctx, args.under, args.basis)
    total = len(picked)
    if args.limit:
        picked = picked[:args.limit]
    shown = picked if args.apply else picked[:args.show]
    checked, verdicts = collections.Counter(), {}
    for old, new, rows in shown:
        print("%s -> %s   (%d row%s)" % (old, posixpath.basename(new), len(rows), "" if len(rows) == 1 else "s"))
        if args.check and not args.apply:
            why = dry_plan(ctx, old, new, rows, args.basis)
            verdicts[old] = why
            checked[why is None] += 1
            if why:
                print(f"    rename.py refuses: {why}")
    reasons = collections.Counter(_reason_key(why) for _source, why in refused)
    print(f"\n{total} renameable, {len(refused)} refused" +
          ("" if args.show_refusals or not refused else " (--show-refusals to list)"))
    for key, count in reasons.most_common():
        print(f"  {count:6d}  {key}")
    if args.show_refusals:
        for source, why in refused:
            print(f"  REFUSED {source}: {why}")
    if checked:
        print(f"rename.py --check: {checked[True]} planned OK, {checked[False]} refused")
    unsupported = basis_supported(args.basis)
    print(f"\nbasis: {BASES[args.basis]}" + (f" (note: {unsupported})" if unsupported else ""))
    report = {"lane": "files", "mode": "apply" if args.apply else "plan", "basis": BASES[args.basis],
              "basis_note": unsupported, "under": args.under, "renameable": total, "refused": len(refused),
              "refusal_reasons": dict(reasons.most_common()),
              "proposals": [dict({"source": old, "target": new, "rows": len(rows)},
                                 **({"refused_by_rename_py": verdicts[old]} if old in verdicts else {}))
                            for old, new, rows in shown],
              "applied": [], "failed": [], "claims_kept": [], "stage": []}
    if not args.apply or not picked:
        return _report(args, report, 0)
    if unsupported:
        print(f"rename_files: {unsupported}", file=sys.stderr)
        report["failed"] = [{"source": old, "reason": unsupported} for old, _new, _rows in picked]
        return _report(args, report, 2)
    checks = tolerant_checks(ctx) if args.tolerate_failing_checks else rename.ledger_checks
    landed, failed, kept = run_batches(ctx, picked, args.basis, batch=args.batch, claim=not args.no_claim,
                                       verify=rename.build_verify, checks=checks)
    print(f"\napplied: {len(landed)} renamed, {len(failed)} refused")
    files = sorted({rel for plan in landed for rel in plan.after})
    if landed:
        print("stage: git add " + " ".join(files) + " (the git mv renames are already staged)")
        print("before the push: python3 tools/rename.py check --range origin/master..HEAD")
    if kept:
        print("claims kept until the push; then: python3 tools/claims.py release " + " ".join(kept))
    report.update(applied=[{"old": plan.old, "new": plan.new} for plan in landed],
                  failed=[{"source": source, "reason": why} for source, why in failed],
                  claims_kept=kept, stage=files)
    return _report(args, report, 1 if failed and not landed else 0)


def _report(args, report, code):
    """Write the --json report (when asked) and pass the exit code through."""
    report["exit"] = code
    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=1) + "\n", encoding="utf-8")
    return code


REASON_KEYS = (("row still placeholder", "row still placeholder-named"),
               ("nested scope", "nested scope"),
               ("operator, template", "operator, template or compiler glue"),
               ("rows span", "rows span several classes"),
               ("already exists", "target already exists"),
               ("proposed name", "proposed name refused"),
               ("funclet ", "funclet of a parent elsewhere"))


def _reason_key(why):
    """A refusal reason without its per-file detail, for the summary counts."""
    return next((key for needle, key in REASON_KEYS if needle in why), why)


if __name__ == "__main__":
    sys.exit(main())
