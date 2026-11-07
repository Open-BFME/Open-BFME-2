#!/usr/bin/env python3
"""Refuse new private copies of classes that have a shared header.

reverse/canonical_classes.csv names the shared header for a class once one
exists. From then on a unit that declares its own body for that class
re-creates the problem the header solved: its inline members are COMDATs
that differ from everyone else's, and members it leaves out are unresolved
when the unit links. This gate stops that at commit time.

Only what the commit introduces is checked. A staged unit is checked
against HEAD's copy of its own path or, for a staged rename (git's R status,
never a copy), of the path it was moved from: a unit that did not declare a
body for the class there (a new unit, a copy, or an edit that adds the
declaration) is refused. Units that already carry a private copy are the
reconciliation backlog (tools/class_views.py --class NAME), not a reason to
refuse unrelated edits to them or a pure move of them.

A body that a unit deleted in the same commit carried verbatim (after comment
and whitespace normalisation outside literals) is moved, not introduced: a TU merge
(tools/tu_skeleton.py --merge) composes one unit from several deleted donors,
which git rarely rates as a rename. Each deleted unit's body credits at most
one staged unit, and an edited body gets no credit. Enclosing namespace/class paths must also
match, with anonymous namespaces recorded as `(anonymous)`. Ambiguous preprocessing,
raw strings and alternative brace/bracket tokens receive no move credit.

A unit that genuinely needs its own layout for a registered class (a
deliberately different codegen view, proved by its bytes) can say so on any
line:

    // class-gate: allow AsciiString <reason>

A registered class renamed by tools/rename.py respells its private views in
place, so a unit that declared `class OLD` at HEAD stages `class NEW`. That is
the same copy, not a new one, when the commit records an approved rename: its
reverse/name_basis.csv gains a `class,OLD,NEW` row, canonical_classes.csv
moves the one OLD key to NEW under the same header (recorded_class_renames),
and HEAD's own tools/rename.py `verify-record` accepts that record as the
approval for exactly this key and name -- the agreement recomputed from the
votes, a canonical citation re-checked, a revert proven the exact inverse
(approved_class_renames). HEAD's copy, not the commit's, so a commit cannot
loosen the check it is judged by. Only HEAD's copy of the same path is
credited, never a staged rename's old path or a deleted donor, and only for
the class whose key moved.

Registered keys are also matched by scope-qualified identity (class_layouts.class_identities):
`rts::hash` matches `namespace rts { template <...> struct hash {...}; }`, and every
specialization (`X<7>`, `X<N, 0>`) is its own identity, so a unit that already has the primary
still introduces a new specialization. A template body moved verbatim by a merge is credited the
same way as any other. reverse/class_gate_mode.txt (`# mode: shadow` or `# mode: enforce`, read
from the staged copy) decides what this identity check does: shadow prints `class_gate [shadow]`
lines and appends them to <git common dir>/class_gate_shadow.jsonl, enforce refuses them. A
commit cannot move the mode from enforce back to shadow. The name check above always enforces.

Usage:
  python3 tools/class_gate.py --staged     the commit gate
  python3 tools/class_gate.py FILE...      check files against HEAD
  python3 tools/class_gate.py --shadow-census [DIR]
                                           the identity check over the TU merge queue and every
                                           existing copy; a dated summary under DIR
                                           (default build/class_gate_shadow), nothing staged
"""
import argparse
import collections
import csv
import io
import re
import subprocess
import sys
import tarfile
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import class_layouts  # noqa: E402
import class_views  # noqa: E402

ALLOW = re.compile(r"//\s*class-gate:\s*allow\s+(\w+)\s+\S")


def git_text(spec):
    result = subprocess.run(["git", "show", spec], cwd=ROOT, capture_output=True)
    if result.returncode != 0:
        return None
    return result.stdout.decode("latin-1")


# ---------------------------------------------------------------- a registered class renamed

NAME_BASIS = "reverse/name_basis.csv"
CANONICAL = "reverse/canonical_classes.csv"
RECORD_FIELDS = ("kind", "old", "new", "basis", "evidence", "source", "rva")


def _csv_rows(text):
    return list(csv.DictReader(io.StringIO(text))) if text else []


def recorded_class_renames(base_basis, target_basis, base_registry, target_registry):
    """{OLD: NEW} candidates: target's name_basis.csv gains a `class,OLD,NEW` row base lacks,
    base's registry has exactly one row for OLD and none for NEW, and target's has none for
    OLD and exactly one for NEW under the header OLD had. An OLD recorded towards two names,
    or two OLDs towards one NEW, is neither. A candidate is credited only once
    approved_class_renames has verified its approval."""
    def key(row):
        return tuple(row.get(c) or "" for c in RECORD_FIELDS)
    before = {key(r) for r in _csv_rows(base_basis)}
    pairs = {(r.get("old") or "", r.get("new") or "") for r in _csv_rows(target_basis)
             if r.get("kind") == "class" and key(r) not in before}
    olds = collections.Counter(o for o, _n in pairs)
    news = collections.Counter(n for _o, n in pairs)

    def headers(text):
        rows = collections.defaultdict(list)
        for row in _csv_rows(text):
            rows[row.get("class") or ""].append(row.get("header") or "")
        return rows
    was, now = headers(base_registry), headers(target_registry)
    return {old: new for old, new in sorted(pairs)
            if old and new and old != new and olds[old] == 1 and news[new] == 1
            and len(was.get(old, ())) == 1 and not was.get(new) and not now.get(old) and now.get(new) == was[old]}


def base_verify_record(root, base, target, old, new):
    """(ok, message) from the BASE revision's tools/rename.py verify-record, run from a copy
    of base's tools/*.py, so the commit being judged cannot change the check. A base that
    predates verify-record, or any failure to run it, credits nothing."""
    archive = subprocess.run(["git", "archive", base or "HEAD", "--", ":(glob)tools/*.py"], cwd=root,
                             capture_output=True)
    if archive.returncode != 0:
        return False, f"cannot read {base}'s tools: {archive.stderr.decode('utf-8', 'replace').strip()[:200]}"
    with tempfile.TemporaryDirectory(prefix="class-rename-verify-") as tmp:
        with tarfile.open(fileobj=io.BytesIO(archive.stdout)) as tar:
            tar.extractall(tmp, filter="data")
        result = subprocess.run([sys.executable, str(Path(tmp) / "tools" / "rename.py"), "verify-record",
                                 "--root", str(root), "--base", base, "--target", target,
                                 "--old", old, "--new", new], cwd=root, capture_output=True, text=True)
    return result.returncode == 0, (result.stdout + result.stderr).strip()[-400:]


def approved_class_renames(base, target, verify=None):
    """{OLD: NEW} recorded renames whose approval base's verify-record accepts."""
    show = lambda rev, rel: git_text(f"{rev}:{rel}")  # noqa: E731
    candidates = recorded_class_renames(show(base, NAME_BASIS), show(target, NAME_BASIS),
                                        show(base, CANONICAL), show(target, CANONICAL))
    verify = verify or base_verify_record
    approved = {}
    for old, new in candidates.items():
        ok, message = verify(ROOT, base, target, old, new)
        if ok:
            approved[old] = new
        else:
            print(f"  class_gate: no rename credit for {old} -> {new}: {message}", file=sys.stderr)
    return approved


def gated(path):
    """A path this gate vets: a unit under Code/, never a generated one."""
    return (path.startswith("Code/") and path.lower().endswith((".cpp", ".c"))
            and not path.startswith(("Code/gen_asm/", "Code/gen_small/")))


def staged_sources():
    # -z: a path with a space or a non-ASCII byte must not be split or quoted,
    # or git show fails on it and the unit would go unchecked.
    out = subprocess.run(["git", "diff", "--cached", "--name-only", "-z", "--diff-filter=ACMR", "--", "Code/"],
                         cwd=ROOT, capture_output=True).stdout.decode("utf-8", "surrogateescape")
    return [p for p in out.split("\0") if p and gated(p)]


def staged_renames():
    """{new path: old path} for each gated unit the index moves from a gated path.

    Only git's R status counts, at its own 50% default made explicit so that
    diff.renames cannot change it. Never -C or -B: a copy leaves the old path
    in the index, so it is a new private view and gets no credit, and HEAD's
    one copy of a path is credited to at most the one path that replaced it.
    Any git failure (no HEAD) gives {}: no credit, as before this existed.
    """
    result = subprocess.run(["git", "diff", "--cached", "-M50%", "--name-status", "-z", "--diff-filter=R",
                             "HEAD", "--", "Code/"], cwd=ROOT, capture_output=True)
    if result.returncode != 0:
        return {}
    fields = result.stdout.decode("utf-8", "surrogateescape").split("\0")
    renames = {}
    for i in range(0, len(fields) - 2, 3):
        status, old, new = fields[i:i + 3]
        if status.startswith("R") and gated(old) and gated(new):
            renames[new] = old
    return renames


# One token that is not code: a comment, or a string or character literal.
# A literal's bytes are the program's data, so they are kept as written and
# only whitespace between tokens is collapsed. A raw string is matched whole,
# before the ordinary string alternative could stop at an embedded quote.
LITERAL = re.compile(
    r'(?:u8|u|U|L)?R"(?P<delimiter>[^ ()\\\t\v\f\n]{0,16})\(.*?\)(?P=delimiter)"'
    r'|(?:u8|u|U|L)?"(?:\\.|[^"\\\n])*"?'
    r"|(?:u8|u|U|L)?'(?:\\.|[^'\\\n])*'?"
    r'|//[^\n]*|/\*.*?(?:\*/|\Z)', re.S)
COMMENT = ("//", "/*")


def collapsed(text):
    """`text` with comments dropped and whitespace collapsed outside literals."""
    segments, pos = [], 0
    for match in LITERAL.finditer(text):
        token = match.group()
        comment = token.startswith(COMMENT)
        segments.append((text[pos:match.start()], False))
        segments.append((" " if comment else token, not comment))
        pos = match.end()
    segments.append((text[pos:], False))
    merged = []
    for piece, literal in segments:
        if not literal and merged and not merged[-1][1]:
            merged[-1][0] += piece
        else:
            merged.append([piece, literal])
    return "".join(piece if literal else re.sub(r"\s+", " ", piece)
                   for piece, literal in merged).strip()


def normalised_body(text):
    """The body's code with comments dropped and whitespace collapsed, or None.

    Whitespace is collapsed only between tokens: a string or character
    literal's bytes are data, so `"a  b"` never equals `"a b"`. A body that
    contains a preprocessing directive or a splice is refused (None): both
    change what the text means without changing the tokens this can see (a
    spliced comment swallows the next line; a directive redefines a field),
    and modelling the preprocessor here would risk a wrong credit. The
    directive check masks literals first, then looks for `#` or its `%:`
    digraph at the start of a line after any preprocessing whitespace, or
    directly after a form feed or vertical tab (an implementation may treat
    either as a line break). The splice check covers backslash-newline and
    every trigraph: `??/` is a backslash that splices before comments are
    even recognised, so it is looked for in the raw text, as is `??=` (`#`)
    and the rest.
    """
    masked = LITERAL.sub(lambda m: re.sub(r"[^\n]", " ", m.group()), text)
    if (re.search(r"\\\r?\n", text) or re.search(r"\?\?[=/'()!<>-]", text)
            or re.search(r"(?:^|[\f\v])[ \t\f\v]*(?:#|%:)", masked, re.M)):
        return None
    return collapsed(text)


# The move proof needs every enclosing namespace/class, including nested heads.
# Reuse the existing class-head grammar without its survey-only line anchor.
MOVE_HEAD = re.compile(r'\b' + class_layouts.HEAD.pattern.removeprefix('^'), re.M)
MOVE_NAMESPACE = re.compile(r'\bnamespace\s*([A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)?\s*\{')


def declared_names(text):
    """Class heads including nested/inline ones the survey omits."""
    code = LITERAL.sub(lambda m: ' ' * len(m.group()), text)
    return {m.group('name') for m in MOVE_HEAD.finditer(code)}


def proven_scope_statement(statement):
    """A declaration, rather than a possible macro that opens hidden scope."""
    statement = re.sub(r'^(?:(?:public|protected|private)\s*:\s*)+', '', statement.strip())
    if not statement:
        return True
    if re.match(r'(?:class|struct|union|enum|namespace|typedef|using|template|extern|'
                r'static|const|volatile|inline|void|bool|char|wchar_t|char8_t|char16_t|'
                r'char32_t|short|int|long|float|double|signed|unsigned|__int(?:8|16|32|64))\b',
                statement):
        return True
    # Require a separate type and declarator: NAME or NAME(args) alone is not
    # a declaration. Keep this deliberately narrow; uncertain syntax refuses.
    return re.fullmatch(
        r'[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*(?:\s*<[^;{}()]*>)?'
        r'(?:\s+|\s*[*&]\s*)[*&\s]*[A-Za-z_]\w*\s*'
        r'(?:\[[^;{}]*\]\s*)*(?:\([^;{}]*\)\s*)?(?:=[^;{}]*)?', statement) is not None


def scoped_move_spans(text):
    """(name, start, end, enclosing path), or [] if scope proof is ambiguous.

    Unknown brace scopes cannot enclose a credited class. A bare macro before
    a scope head is likewise not evidence of global/namespace/class scope.
    Includes are accepted; other directives can manufacture or condition scope
    and are refused. Check the whole unit's balance, not only a class's prefix.
    """
    code = LITERAL.sub(lambda m: re.sub(r'[^\n]', ' ', m.group()), text)
    if re.search(r'^[ \t\f\v]*(?:#|%:)(?![ \t]*include\b)', code, re.M):
        return []
    code = re.sub(r'^[ \t]*#[ \t]*include\b[^\n]*',
                  lambda m: ' ' * len(m.group()), code, flags=re.M)
    heads = {m.end() - 1: m for m in MOVE_HEAD.finditer(code)}
    namespaces = {m.end() - 1: m for m in MOVE_NAMESPACE.finditer(code)}
    linkage = {m.end() - 1 for m in class_layouts.LINKAGE.finditer(text)
               if code[m.start():m.start() + 6] == 'extern'}
    stack, spans, boundary = [], [], 0
    unproven = [False]  # One persistent flag for each enclosing lexical level.
    for token in re.finditer(r'[{};]', code):
        pos, char = token.start(), token.group()
        if char == '{':
            head, namespace = heads.get(pos), namespaces.get(pos)
            if head or namespace:
                start = (head or namespace).start()
                prefix = code[boundary:start].strip()
                if (any(unproven) or any(frame[0] is None for frame in stack)
                        or not re.fullmatch(r'(?:(?:public|protected|private)\s*:\s*)*'
                                            r'(?:inline\s*)?', prefix)):
                    return []
            if namespace:
                path = tuple((namespace.group(1) or '(anonymous)').split('::'))
            elif head:
                path = tuple(head.group('name').split('::'))
            else:
                path = () if pos in linkage else None
            scope = tuple(part for frame in stack for part in (frame[0] or ()))
            stack.append((path, head, scope))
            unproven.append(False)
        elif char == '}':
            if not stack:
                return []
            _, head, scope = stack.pop()
            unproven.pop()
            # A template body is never credited, but it does not void the
            # unit's other spans: a TU merge that also composes a template
            # (an STLport specialization, a local container) still moves its
            # ordinary class bodies verbatim.
            if head and not head.group('template'):
                spans.append((head.group('name'), head.start(), pos + 1, scope))
        elif all(frame[0] is not None for frame in stack):
            # A semicolon ends text, not the uncertainty of a macro expansion.
            if not proven_scope_statement(code[boundary:pos]):
                unproven[-1] = True
        boundary = token.end()
    return [] if stack else sorted(spans, key=lambda span: span[1])


def moved_bodies(text):
    """Master's body keys, with conservative lexical checks for move credit.

    Raw strings, digraphs and translation-phase splices/trigraphs can corrupt
    class_body_spans before we ever see a body. Refuse the entire unit's move
    credit for those constructs. Ordinary existing-path/rename credit is
    unchanged; class_views' survey normalisation is not proof of a pure move.
    """
    if (re.search(r'(?:u8|u|U|L)?R"|<%|%>|<:|:>|\\\r?\n', text)
            or re.search(r"\?\?[=/'()!<>-]", text)):
        return {}
    found, seen = {}, set()
    for name, start, end, scope in scoped_move_spans(text):
        # Unqualified keys cannot prove which of multiple bodies moved.
        # Count even bodies whose normalisation would refuse credit.
        if name in seen:
            return {}
        seen.add(name)
        body = normalised_body(text[start:end])
        if body is not None:
            found[name] = (scope, body)
    return found


def staged_deletions(renames):
    """{(class name, (enclosing scope, normalised body)): [HEAD path, ...]} for gated units the index deletes.

    --no-renames lists every vanished path as D; a path a staged rename already
    credits is skipped so one body is never credited twice. Any git failure
    gives {}: no credit.
    """
    result = subprocess.run(["git", "diff", "--cached", "--no-renames", "--name-only", "-z",
                             "--diff-filter=D", "HEAD", "--", "Code/"], cwd=ROOT, capture_output=True)
    if result.returncode != 0:
        return {}
    credited = set(renames.values())
    bodies = {}
    for old in result.stdout.decode("utf-8", "surrogateescape").split("\0"):
        if not old or not gated(old) or old in credited:
            continue
        before = git_text(f"HEAD:{old}")
        if before:
            for item in moved_bodies(before).items():
                bodies.setdefault(item, []).append(old)
    return bodies


def introduced(path, text, canon, renamed_from=None, moved=None, class_renames=None):
    """Registered classes `text` declares a body for that HEAD's copy of `path` did not.

    `renamed_from` is the HEAD path the index moves to `path`: its bodies are
    the unit's own, not new ones (a rename plus an edit equals a pure rename
    then the in-place edit, both admitted). `moved` is staged_deletions()'s
    pool: a body found there verbatim is consumed from it and credited.
    `class_renames` is {OLD: NEW}, the registered classes this commit renames
    (class_views.recorded_class_renames): a body of OLD that HEAD's copy of this
    very path declared is that unit's body of NEW, so it is not introduced.
    """
    now = declared_names(text) & set(canon)
    if not now:
        return []
    had = set()
    # In a merge, a body either parent already carried is not introduced by
    # this commit: the other side's files are new to HEAD but not new code.
    for parent in ("HEAD", "MERGE_HEAD"):
        before = git_text(f"{parent}:{path}")
        if before:
            had |= declared_names(before)
    if renamed_from:
        before = git_text(f"HEAD:{renamed_from}")
        if before:
            had |= declared_names(before)
    if class_renames:
        before = git_text(f"HEAD:{path}")
        if before:
            had |= {class_renames[name] for name in declared_names(before) if name in class_renames}
    allowed = set(ALLOW.findall(text))
    fresh = now - had - allowed
    if moved:
        bodies = moved_bodies(text)
        for name in sorted(fresh):
            donors = moved.get((name, bodies[name])) if name in bodies else None
            if donors:
                donors.pop()
                fresh.discard(name)
    return sorted(fresh)


# Step 2 of the class-template series (build/drift_review/swarm/template_tooling.md): registered
# keys matched by scope-qualified identity, every specialization its own identity, and template
# bodies credited when a merge moves them verbatim. It runs beside introduced(), never instead of
# it, in the mode reverse/class_gate_mode.txt names: `shadow` reports, `enforce` refuses.
MODE_FILE = "reverse/class_gate_mode.txt"
MODE = re.compile(r"^#\s*mode:\s*(shadow|enforce)\s*$", re.M)
ALLOW_KEY = re.compile(r"//\s*class-gate:\s*allow\s+(\S+)\s+\S")
SHADOW_LOG = "class_gate_shadow.jsonl"


def gate_mode(text):
    """`shadow` or `enforce` from a mode file's text; missing or unreadable is shadow, never off."""
    found = MODE.search(text or "")
    return found.group(1) if found else "shadow"


def registered_key(qualified, name, canon):
    """The registry key a class body is a copy of: its exact qualified identity, else today's
    head-spelling match, else None."""
    if qualified in canon:
        return qualified
    if name in canon:
        return name
    return None


def identity_bodies(text, canon):
    """{(key, args): [(scope, normalised body)]} for registered identities `text` defines a body
    for, or None when the reader cannot read the text (class_layouts.class_identities)."""
    found = class_layouts.class_identities(text)
    if found is None:
        return None
    out = {}
    for qualified, name, args, _is_template, start, end, _key in found:
        key = registered_key(qualified, name, canon)
        if key is None:
            continue
        scope = tuple(qualified.split("::")[:-len(name.split("::"))])
        out.setdefault((key, args), []).append((scope, normalised_body(text[start:end])))
    return out


def fallback_keys(text, canon):
    """For a text the reader refuses: every key whose last component is a declared head name."""
    names = declared_names(text)
    return {key for key in canon if key.split("::")[-1] in names}


def head_identities(text, canon):
    """{(key, args)} from every class head in `text`, read without scope proof, for comparing a
    unit the reader refuses: a key's head with new or different arguments still shows. A head whose
    argument list cannot be read is ("?"), which matches nothing, so it is reported, not hidden."""
    code = class_layouts._masked(text)
    by_last = {}
    for key in canon:
        by_last.setdefault(key.split("::")[-1], set()).add(key)
    found = set()
    for match in class_layouts.CLASS_KEY.finditer(code):
        try:
            head = class_layouts._class_head(code, match)
        except class_layouts.Ambiguous:
            name = re.match(r"\s*(\w+)", code[match.end():])
            head = (name.group(1), "?", None) if name else None
        if not head or head[0] is None:
            continue
        name, args = head[0].split("::")[-1].split("<")[0], head[1]
        for key in by_last.get(name, ()):
            found.add((key, args))
    for key in fallback_keys(text, canon):
        if not any(k == key for k, _a in found):
            found.add((key, None))
    return found


def identities(text, canon):
    """({(key, args)}, ambiguous) for a text; an unreadable text gives its head identities."""
    bodies = identity_bodies(text, canon)
    if bodies is None:
        return head_identities(text, canon), True
    return set(bodies), False


def staged_identity_deletions(renames, canon):
    """{(key, args, scope, normalised body): [HEAD path, ...]} for gated units the index deletes:
    the template-aware twin of staged_deletions(). An unreadable donor credits nothing."""
    result = subprocess.run(["git", "diff", "--cached", "--no-renames", "--name-only", "-z",
                             "--diff-filter=D", "HEAD", "--", "Code/"], cwd=ROOT, capture_output=True)
    if result.returncode != 0:
        return {}
    credited = set(renames.values())
    pool = {}
    for old in result.stdout.decode("utf-8", "surrogateescape").split("\0"):
        if not old or not gated(old) or old in credited:
            continue
        before = git_text(f"HEAD:{old}")
        bodies = identity_bodies(before, canon) if before else None
        for (key, args), items in (bodies or {}).items():
            for scope, body in items:
                if body is not None:
                    pool.setdefault((key, args, scope, body), []).append(old)
    return pool


def renamed_identities(path, canon, class_renames, heads=False):
    """({(NEW, args)}, unreadable) for the bodies of a renamed OLD (class_renames, {OLD: NEW})
    that HEAD's copy of this very path defined: read under OLD's registration, the key it
    had before the commit moved it, then respelled. Only global keys move."""
    before = git_text(f"HEAD:{path}") if class_renames else None
    if not before:
        return set(), False
    old_canon = {old: canon[new] for old, new in class_renames.items() if new in canon}
    if heads:
        found, unreadable = head_identities(before, old_canon), False
    else:
        found, unreadable = identities(before, old_canon)
    return {(class_renames[key], args) for key, args in found if key in class_renames}, unreadable


def introduced_identities(path, text, canon, renamed_from=None, moved=None, class_renames=None):
    """[(key, args, why)] registered identities `text` defines a body for that its prior copies
    (HEAD, MERGE_HEAD, a staged rename's old path) did not and no deleted donor carried verbatim.

    A specialization is its own identity, so a unit that already has the primary still
    introduces `X<7>`. When either side is unreadable, identities compare by key alone.
    `class_renames` credits HEAD's own body of a renamed OLD as this path's NEW (introduced()).
    """
    now, ambiguous = identities(text, canon)
    if not now:
        return []
    had, had_ambiguous = set(), False
    for spec in [f"{parent}:{path}" for parent in ("HEAD", "MERGE_HEAD")] + (
            [f"HEAD:{renamed_from}"] if renamed_from else []):
        before = git_text(spec)
        if before:
            found, unreadable = identities(before, canon)
            had |= found
            had_ambiguous |= unreadable
    found, unreadable = renamed_identities(path, canon, class_renames)
    had |= found
    had_ambiguous |= unreadable
    allowed = set(ALLOW_KEY.findall(text))
    if ambiguous or had_ambiguous:
        # Both sides by their heads, so a new or different specialization still shows.
        now_heads = now if ambiguous else head_identities(text, canon)
        had_heads = set()
        for spec in [f"{parent}:{path}" for parent in ("HEAD", "MERGE_HEAD")] + (
                [f"HEAD:{renamed_from}"] if renamed_from else []):
            before = git_text(spec)
            if before:
                had_heads |= head_identities(before, canon)
        had_heads |= renamed_identities(path, canon, class_renames, heads=True)[0]
        fresh = now_heads - had_heads
        why = "an unreadable unit, compared by heads"
    else:
        fresh = now - had
        why = "a new body"
    fresh = {item for item in fresh if item[0] not in allowed and item[0].split("::")[-1] not in allowed}
    if moved and not ambiguous:
        # A body a staged deletion carried verbatim is moved, not introduced, whichever unit it came
        # from: the credit checks identity, scope and body, not TU-merge provenance, which is safe
        # because each deleted copy credits at most one staged copy, so the count cannot grow.
        bodies = identity_bodies(text, canon)
        for key, args in sorted(fresh, key=str):
            items = bodies.get((key, args), [])
            need = collections.Counter((key, args, scope, body) for scope, body in items)
            if items and all(body is not None for _scope, body in items) and \
                    all(len(moved.get(item, ())) >= count for item, count in need.items()):
                for item, count in need.items():
                    del moved[item][:count]
                fresh.discard((key, args))
    return [(key, args, why) for key, args in sorted(fresh, key=str)]


def identity_failure(where, error, mode):
    """Report a failure of the identity check: shadow reports and passes, enforce refuses. The
    report itself cannot change that exit."""
    tag = "refused" if mode == "enforce" else "shadow"
    message = f"class_gate [{tag}] identity check failed on {where}: {type(error).__name__}: {error}"
    if mode == "enforce":
        try:
            print(message, file=sys.stderr)
        except Exception:  # noqa: BLE001 - enforce refuses whether or not the report prints
            pass
        return 1
    shadow_report(message, {"path": where, "key": None, "args": None,
                            "why": f"check failed: {type(error).__name__}"})
    return 0


def label(key, args):
    return key if args is None else f"{key}<{args}>"


def shadow_report(message, record):
    """Print and log one shadow finding. Never raises: shadow mode cannot change the gate's exit."""
    try:
        print(message, file=sys.stderr)
    except Exception:  # noqa: BLE001 - a shadow report must not break the gate
        pass
    shadow_log(record)


def shadow_log(record):
    """Append one finding to the clone's shadow log (<git common dir>/class_gate_shadow.jsonl).
    Never raises: a failing git, path or write loses the log line, not the commit."""
    import json
    try:
        result = subprocess.run(["git", "rev-parse", "--git-common-dir"], cwd=ROOT, capture_output=True, text=True)
        if result.returncode != 0:
            return
        common = Path(result.stdout.strip())
        common = common if common.is_absolute() else ROOT / common
        with open(common / SHADOW_LOG, "a", encoding="utf-8") as handle:
            handle.write(json.dumps(record, sort_keys=True) + "\n")
    except Exception:  # noqa: BLE001 - a shadow log line must not break the gate
        pass


def beyond_name_check(key, args):
    """An identity introduced() cannot see: a qualified key or a specialization. Bare-key primaries
    are decided by the name check, which the identity check never repeats."""
    return "::" in key or args is not None


def shadow_census(out_dir):
    """Run the identity check over every queued TU merge (tools/tu_skeleton.py --queue) and the
    existing private copies, for the identities only it sees (beyond_name_check); write a dated
    summary under out_dir. Read-only on the tree; nothing is staged or committed."""
    import datetime
    import json
    import tu_skeleton
    canon = class_views.canonical_classes()
    units = [p for p in (ROOT / "Code").rglob("*") if p.is_file() and gated(p.relative_to(ROOT).as_posix())]
    copies, unreadable, per_unit = {}, 0, {}
    for path in units:
        rel = path.relative_to(ROOT).as_posix()
        text = path.read_text(encoding="latin-1")
        bodies = identity_bodies(text, canon)
        if bodies is None:
            unreadable += 1
            keys = {key for key in fallback_keys(text, canon) if "::" in key}
            if keys:
                per_unit[rel] = {"fallback": sorted(keys)}
            continue
        bodies = {ident: items for ident, items in bodies.items() if beyond_name_check(*ident)}
        if bodies:
            per_unit[rel] = {label(k, a): [b for _s, b in items] for (k, a), items in bodies.items()}
            for (key, args), items in bodies.items():
                copies[label(key, args) if args is not None and "::" not in key else key] = \
                    copies.get(label(key, args) if args is not None and "::" not in key else key, 0) + len(items)
    refusals = []
    entries = tu_skeleton.queue_entries()
    for entry in entries:
        tu = entry["tu"]
        donors, _mixed, _refused = tu_skeleton.donors(tu, tu_skeleton.skeleton(tu))
        prior = per_unit.get(tu, {}) if (ROOT / tu).exists() else {}
        gathered = {}
        fallback = set()
        for donor in donors:
            if donor == tu or donor not in per_unit:
                continue
            for ident, value in per_unit[donor].items():
                if ident == "fallback":
                    fallback.update(value)
                else:
                    gathered.setdefault(ident, set()).update(value)
        for ident, bodies in sorted(gathered.items()):
            if ident in prior:
                continue
            if len(bodies) != 1 or None in bodies:
                # One verbatim copy is credited; the merge needs an edited body when donors differ.
                refusals.append({"tu": tu, "identity": ident, "why": "donors carry differing bodies, so the merge must edit one"})
        for key in sorted(fallback):
            if key not in prior and key not in {i.split("<")[0] for i in gathered}:
                refusals.append({"tu": tu, "identity": key, "why": "an unreadable donor, compared by key"})
    stamp = datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%dT%H%M%SZ")
    summary = {"when": stamp, "registered": sorted(canon), "units": len(units), "unreadable_units": unreadable,
               "copies_per_key": copies, "queued_merges": len(entries),
               "would_refuse": refusals}
    out_dir = Path(out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    target = out_dir / f"class_gate_shadow_{stamp}.json"
    target.write_text(json.dumps(summary, indent=1) + "\n", encoding="utf-8")
    return target, summary


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--staged", action="store_true")
    parser.add_argument("files", nargs="*")
    parser.add_argument("--shadow-census", nargs="?", const="build/class_gate_shadow", metavar="DIR")
    args = parser.parse_args(argv)
    if args.shadow_census:
        target, summary = shadow_census(ROOT / args.shadow_census)
        for item in summary["would_refuse"]:
            print(f"  would refuse {item['tu']}: {item['identity']} ({item['why']})")
        print(f"class_gate shadow census: {len(summary['would_refuse'])} would-refuse merge(s) of "
              f"{summary['queued_merges']}; copies per key {summary['copies_per_key']}; "
              f"{summary['unreadable_units']} unreadable unit(s); {target}")
        return 0
    canon = class_views.canonical_classes()
    if not canon:
        return 0
    bad = 0
    if args.staged:
        renames = staged_renames()
        moved = staged_deletions(renames)
        class_renames = approved_class_renames("HEAD", "")
        checks = [(p, git_text(f":{p}"), renames.get(p)) for p in staged_sources()]
        mode = gate_mode(git_text(f":{MODE_FILE}"))
        try:
            identity_moved = staged_identity_deletions(renames, canon)
        except Exception as error:  # noqa: BLE001 - the identity check must not break the gate
            identity_moved = {}
            bad |= identity_failure("move credit", error, mode)
        if gate_mode(git_text(f"HEAD:{MODE_FILE}")) == "enforce" and mode != "enforce":
            print(f"  {MODE_FILE}: the identity check never returns from enforce to shadow", file=sys.stderr)
            bad = 1
    else:
        moved = identity_moved = None
        class_renames = {}
        checks = [(p, (ROOT / p).read_text(encoding="latin-1"), None) for p in args.files]
        mode_path = ROOT / MODE_FILE
        mode = gate_mode(mode_path.read_text(encoding="latin-1") if mode_path.exists() else None)
    for path, text, renamed_from in checks:
        if text is None:
            # An unreadable staged unit is unchecked, not clean.
            print(f"  {path}: staged content unreadable; refusing rather than skipping it", file=sys.stderr)
            bad = 1
            continue
        refused = introduced(path, text, canon, renamed_from, moved, class_renames)
        for name in refused:
            print(f"  {path}: declares its own `{name}`; include {canon[name]} instead "
                  f"(or `// class-gate: allow {name} <reason>` for a proved codegen view)", file=sys.stderr)
            bad = 1
        try:
            found = introduced_identities(path, text, canon, renamed_from, identity_moved, class_renames)
        except Exception as error:  # noqa: BLE001 - the identity check must not break the gate
            found = []
            bad |= identity_failure(path, error, mode)
        for key, args, why in found:
            if key in refused:
                continue                     # the name check above already refuses this class here
            if mode == "enforce":
                print(f"class_gate [refused] {path}: defines its own `{label(key, args)}` ({why}); "
                      f"include {canon[key]} instead", file=sys.stderr)
                bad = 1
            else:
                shadow_report(f"class_gate [shadow] {path}: would refuse `{label(key, args)}` ({why})",
                              {"path": path, "key": key, "args": args, "why": why})
    return bad


if __name__ == "__main__":
    sys.exit(main())
