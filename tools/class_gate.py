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
one staged unit, and an edited body gets no credit. Ambiguous preprocessing,
raw strings and alternative brace/bracket tokens receive no move credit.

A unit that genuinely needs its own layout for a registered class (a
deliberately different codegen view, proved by its bytes) can say so on any
line:

    // class-gate: allow AsciiString <reason>

Usage:
  python3 tools/class_gate.py --staged     the commit gate
  python3 tools/class_gate.py FILE...      check files against HEAD
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import class_views  # noqa: E402

ALLOW = re.compile(r"//\s*class-gate:\s*allow\s+(\w+)\s+\S")


def git_text(spec):
    result = subprocess.run(["git", "show", spec], cwd=ROOT, capture_output=True)
    if result.returncode != 0:
        return None
    return result.stdout.decode("latin-1")


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
    for name, start, end, _ in class_views.class_body_spans(text):
        # Unqualified keys cannot prove which of multiple bodies moved.
        # Count even bodies whose normalisation would refuse credit.
        if name in seen:
            return {}
        seen.add(name)
        body = normalised_body(text[start:end])
        if body is not None:
            found.setdefault(name, body)
    return found


def staged_deletions(renames):
    """{(class name, normalised body): [HEAD path, ...]} for gated units the index deletes.

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


def introduced(path, text, canon, renamed_from=None, moved=None):
    """Registered classes `text` declares a body for that HEAD's copy of `path` did not.

    `renamed_from` is the HEAD path the index moves to `path`: its bodies are
    the unit's own, not new ones (a rename plus an edit equals a pure rename
    then the in-place edit, both admitted). `moved` is staged_deletions()'s
    pool: a body found there verbatim is consumed from it and credited.
    """
    now = set(class_views.class_bodies(text)) & set(canon)
    if not now:
        return []
    had = set()
    # In a merge, a body either parent already carried is not introduced by
    # this commit: the other side's files are new to HEAD but not new code.
    for parent in ("HEAD", "MERGE_HEAD"):
        before = git_text(f"{parent}:{path}")
        if before:
            had |= set(class_views.class_bodies(before))
    if renamed_from:
        before = git_text(f"HEAD:{renamed_from}")
        if before:
            had |= set(class_views.class_bodies(before))
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


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--staged", action="store_true")
    parser.add_argument("files", nargs="*")
    args = parser.parse_args(argv)
    canon = class_views.canonical_classes()
    if not canon:
        return 0
    if args.staged:
        renames = staged_renames()
        moved = staged_deletions(renames)
        checks = [(p, git_text(f":{p}"), renames.get(p)) for p in staged_sources()]
    else:
        moved = None
        checks = [(p, (ROOT / p).read_text(encoding="latin-1"), None) for p in args.files]
    bad = 0
    for path, text, renamed_from in checks:
        if text is None:
            # An unreadable staged unit is unchecked, not clean.
            print(f"  {path}: staged content unreadable; refusing rather than skipping it", file=sys.stderr)
            bad = 1
            continue
        for name in introduced(path, text, canon, renamed_from, moved):
            print(f"  {path}: declares its own `{name}`; include {canon[name]} instead "
                  f"(or `// class-gate: allow {name} <reason>` for a proved codegen view)", file=sys.stderr)
            bad = 1
    return bad


if __name__ == "__main__":
    sys.exit(main())
