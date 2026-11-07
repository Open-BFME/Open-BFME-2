#!/usr/bin/env python3
"""Refuse changes that run the conversion direction backward: asm -> C++ only.

Usage:  conversion_gate.py OLD NEW
        OLD/NEW are git revisions; NEW may be ":" for the staged index.

Rule A: added lines under Code/ (outside Code/gen_small/) may not contain
        __declspec(naked) or _emit/__emit. Machine byte-dumps belong to
        tools/gen_dump.py in Code/gen_small/; a proven codegen blocker
        (x87, SEH) belongs in Code/masm_dumps/*.asm. Eighteen fleet commits
        titled "convert ... to exact C++" deleted real C++ bodies and added
        __emit thunks — byte-verification passes on those, so this is the
        only gate that can see them.

Rule B: a matched RVA that had at least one clean-C++ source in OLD must
        still have one in NEW. Retracting a wrong claim (row deleted or
        status changed) is legal and must be its own commit; repointing a
        live clean claim at a dump is never legal.

Rule C: Code/gen_asm/ is machine output and stays that way. C1 every added
        line there must match the generator's grammar, so a lift of a NAMED
        function cannot be expressed in the directory at all; C2 every added
        ledger row pointing there is anonymous (?d_<rva>@@YAXXZ, notes
        gen-dump), so a dump can never squat an identity byte-verification
        cannot falsify; C3 a wave commit may not touch any other file under
        Code/, so a deleted C++ body cannot ride inside a diff of 33,000
        unreadable `db` lines. Rule A needs no exemption here and gets none:
        a `db` dump matches neither NAKED_RE nor LIFT_RE, and source_kind
        scores a .asm file as assembly unconditionally, so the offence Rule A
        polices -- inflating the C++ lane with re-encoded binary -- is not
        expressible in this directory.

Rule D: an added `// cl:` line under Code/ holds compiler flags and nothing else.
        Git Bash rewrites a /I argument it hands to a Windows program into
        `C:/Program Files/Git/I...`; 573 headers landed that way in two days.
        `cl -c` warns and ignores the stray words, so bytes still match, but
        `cl -E` fails on them, which takes away the census's input proof.

Rule E: an added #include under Code/ names no absolute path. `W:/...` compiles on
        its author's machine and fails everywhere else, including verification;
        one such pair kept master red for 6.6 hours.

Rule F: an added `// cl:` line under Code/ carries only the flags tools/cl_flags.py
        allows, with include paths inside the checkout. cl.exe does what a flag says:
        /B1 loads another compiler DLL and /Fa writes a file anywhere, on every seat,
        worker and runner that builds the commit. build.source_extra_flags refuses the
        same flags at compile time.
"""

from collections import Counter
import csv
import io
import re
import subprocess
import sys
from pathlib import Path

from list_naked_candidates import NAKED_RE
from progress import CPP_SUFFIXES, naked_cpp_rows, source_kind

LIFT_RE = re.compile(r"\b__?emit\b")
LEDGER = "reverse/functions.csv"
# The diff the rules parse is a function of the two trees only: a working-tree
# .gitattributes (-diff, a textconv driver) or a user's diff settings (noprefix,
# color, relative, algorithm) must not hide added lines, since passing results are
# reused by tree.
DIFF_OPTS = ("--text", "--no-ext-diff", "--no-textconv", "--no-color", "--no-relative",
             "--diff-algorithm=myers", "--src-prefix=a/", "--dst-prefix=b/")
# git's default rename detection, its limit pinned (diff.renames, diff.renameLimit)
RENAMES = ("-M", "-l1000")


def run(*argv):
    # errors="replace": a diff of a Latin-1 source (debug_internal.cpp's (c) sign) must not crash the hook
    proc = subprocess.run(argv, capture_output=True, text=True, encoding="utf-8", errors="replace")
    if proc.returncode != 0:
        raise SystemExit("conversion_gate: %s failed: %s" % (" ".join(argv), proc.stderr.strip()))
    return proc.stdout


def added_lift_lines(old, new):
    diff_cmd = ["git", "diff", "--unified=0", *RENAMES, *DIFF_OPTS]
    diff_cmd += ["--cached", old] if new == ":" else [old, new]
    # Authored code only. A ledger row may name a file in the vendored
    # reference/ tree, and those rows sit outside this scan on purpose: nobody
    # authors that tree, nine of its files already contain __emit upstream, and
    # scanning it would fire on the next re-vendor rather than on a regression.
    # Rule B below reads whatever path a row names, so it covers them.
    diff_cmd += ["--", "Code/", ":(exclude)Code/gen_small/"]
    bad, path = {}, None
    for line in run(*diff_cmd).splitlines():
        if line.startswith("+++ b/"):
            path = line[6:]
        elif line.startswith("+") and not line.startswith("+++"):
            if NAKED_RE.search(line) or LIFT_RE.search(line):
                first, count = bad.get(path, (line[1:].strip()[:80], 0))
                bad[path] = (first, count + 1)
    return [(p, "%s  (%d such lines)" % (first, count)) for p, (first, count) in bad.items()]


ABSOLUTE_INCLUDE_RE = re.compile(r'^\s*#\s*include\s*[<"](?:[A-Za-z]:[/\\]|[/\\])')
CL_MARK = "// cl:"
CL_QUOTED_INCLUDE_RE = re.compile(r'[/-]I\s*"[^"]*"')


def cl_non_flags(line):
    """The words of one `// cl:` line that are not flags (build._source_flag_tokens' grammar)."""
    bad, operand = [], False
    for token in CL_QUOTED_INCLUDE_RE.sub(" ", line[len(CL_MARK):]).split():
        if operand:
            operand = False
        elif token in ("/I", "-I"):
            operand = True
        elif not token.startswith(("/", "-")):
            bad.append(token)
    return bad


def added_cl_unsafe(old, new):
    """[(path, refusal)] for each added `// cl:` line under Code/ with a flag cl_flags refuses
    (Rule D reports plain words that are not flags; this reports everything else)."""
    import build
    import cl_flags
    found, path = [], None
    for line in diff_lines(old, new, "Code/"):
        if line.startswith("+++ b/"):
            path = line[6:]
        elif line.startswith("+") and line[1:].lstrip("\ufeff").startswith(CL_MARK):
            text = line[1:].lstrip("\ufeff")
            try:
                tokens = build._source_flag_tokens(text[len(CL_MARK):])
            except SystemExit as malformed:
                found.append((path, str(malformed)))
                continue
            refused = [(token, reason) for token, reason in cl_flags.problems(tokens)
                       if reason != "is not a flag"]
            if refused:
                found.append((path, cl_flags.describe(refused)[:300]))
    return found


def added_cl_garbage(old, new):
    found, path = [], None
    for line in diff_lines(old, new, "Code/"):
        if line.startswith("+++ b/"):
            path = line[6:]
        elif line.startswith("+") and ABSOLUTE_INCLUDE_RE.match(line[1:].lstrip("\ufeff")):
            found.append((path, line[1:].strip()[:80]))
        elif line.startswith("+") and line[1:].lstrip("\ufeff").startswith(CL_MARK):
            bad = cl_non_flags(line[1:].lstrip("\ufeff"))
            if bad:
                found.append((path, " ".join(bad)[:80]))
    return found


GEN_ASM = "Code/gen_asm/"
# The generator's whole vocabulary. Anything else in a dump file is a hand edit.
GEN_ASM_LINE_RE = re.compile(
    r"^(?:\.386|\.model flat|_TEXT SEGMENT|_TEXT ENDS|END|;.*|"
    r"public \?d_[0-9a-f]{8}@@YAXXZ|"
    r"\?d_[0-9a-f]{8}@@YAXXZ (?:PROC|ENDP)|"
    r"    db (?:0?[0-9A-F]{2}h)(?:, 0?[0-9A-F]{2}h)*|)$")


def diff_lines(old, new, *paths):
    if old is None:
        return run("git", "diff-tree", "--root", "-p", "--unified=0", *DIFF_OPTS, new,
                   "--", *paths).splitlines()
    cmd = ["git", "diff", "--unified=0", *RENAMES, *DIFF_OPTS]
    cmd += ["--cached", old] if new == ":" else [old, new]
    return run(*cmd, "--", *paths).splitlines()


def _gen_asm_diff_offences(old, new):
    """Rule C for one commit or the staged index."""
    offences = []
    path = None
    dump_rows, other_code_edits = [], set()
    removed_dump_rows = Counter()
    for line in diff_lines(old, new, "Code/", LEDGER):
        if line.startswith("--- a/"):
            # Deleted sources have +++ /dev/null, so retain their old path.
            path = line[6:]
            continue
        if line.startswith("+++ b/"):
            path = line[6:]
            continue
        if path is None or line.startswith("---") or line.startswith("+++"):
            continue
        added = line.startswith("+")
        if not added and not line.startswith("-"):
            continue
        body = line[1:]
        if path.startswith(GEN_ASM):
            if added and not GEN_ASM_LINE_RE.match(body):
                offences.append("C1 %s: not generator output: %s"
                                % (path, body.strip()[:80]))
        elif path == LEDGER:
            fields = next(csv.reader([body]), [])
            if len(fields) >= 5 and fields[4].startswith(GEN_ASM):
                if added:
                    dump_rows.append(fields)
                else:
                    removed_dump_rows[tuple(fields)] += 1
        elif path.startswith("Code/"):
            other_code_edits.add(path)

    for fields in dump_rows:
        name, rva, notes = fields[0], fields[2], fields[6] if len(fields) > 6 else ""
        expected = "?d_%08x@@YAXXZ" % int(rva, 16)
        if name != expected:
            offences.append("C2 %s claims identity %s; a dump proves bytes and "
                            "an extent, never what the function is (expected %s)"
                            % (rva, name, expected))
        if not notes.lstrip().startswith("gen-dump"):
            offences.append("C2 %s: a Code/gen_asm/ row must carry gen-dump "
                            "notes, or is_scaffold_row cannot see it" % rva)
    # A ledger normalization can move unchanged dump rows. Git represents
    # those moves as delete/add; they do not introduce a dump wave. Compare
    # complete parsed rows with multiplicity, retaining C2 checks above and
    # C3 for new, changed, or additionally duplicated rows.
    added_dump_rows = Counter(map(tuple, dump_rows)) - removed_dump_rows
    if added_dump_rows and other_code_edits:
        offences.append("C3 wave commit also edits %s — dumps-and-ledger only, "
                        "so a deleted C++ body cannot ride inside an unreadable "
                        "diff" % ", ".join(sorted(other_code_edits)))
    return offences


EMPTY_TREE = "4b825dc642cb6eb9a060e54bf8d69288fbee4904"
_TREES = {}


class _Found(Exception):
    """A non-empty result: shown, never kept."""

    def __init__(self, items):
        super().__init__(len(items))
        self.items = items


def _tree(rev):
    """The tree `rev` names: ":" is the index (git write-tree), None the empty
    tree. Only a full commit id is remembered: the index and refs can move."""
    if rev is None:
        return EMPTY_TREE
    if rev in _TREES:
        return _TREES[rev]
    tree = (run("git", "write-tree") if rev == ":" else
            run("git", "rev-parse", "--verify", "--end-of-options", rev + "^{tree}")).strip()
    if re.fullmatch(r"[0-9a-f]{40}", rev):
        _TREES[rev] = tree
    return tree


def _code_and_retail():
    """The hash of the code computing a result and the retail image it reads."""
    import hashlib
    import build
    import ledger_cache
    tools = Path(__file__).resolve().parent
    code = ledger_cache.code_hash(*(tools / name for name in (
        "conversion_gate.py", "list_naked_candidates.py", "progress.py", "build.py", "pe_imports.py",
        "cl_flags.py")))
    return code, hashlib.sha1(build.EXE.read_bytes()).hexdigest()


def by_trees(kind, old, new, compute):
    """compute(), a list of findings for the change from `old` to `new`, reused
    when it was empty for the same two trees under the same code and retail
    image (tools/ledger_cache.py): every rule reads only the two states' git
    objects and the retail image, and a diff of two commits is the diff of
    their trees (":" is the index, `git write-tree`). Findings are never kept."""
    import ledger_cache
    code, retail = _code_and_retail()

    def passing():
        found = compute()
        if found:
            raise _Found(found)
        return found
    try:
        return ledger_cache.memo(f"conversion_gate.{kind}", f"{_tree(old)}:{_tree(new)}:{retail}", passing, code)
    except _Found as found:
        return found.items


def gen_asm_offences(old, new):
    """Check wave atomicity per commit, including when verifying a push range.

    A dump-only commit followed by a C++ recovery is a legal publication batch.
    Its aggregate diff must still satisfy C1/C2, but it is not one wave commit.
    Inspect every outgoing commit so a later edit or revert cannot hide an
    invalid wave. Merge commits use their first-parent delta, while commits
    brought in by the merge are also inspected individually.
    """
    if new == ":":
        return by_trees("gen_asm", old, new, lambda: _gen_asm_diff_offences(old, new))
    offences = [offence for offence in by_trees("gen_asm", old, new, lambda: _gen_asm_diff_offences(old, new))
                if not offence.startswith("C3 ")]
    commits = run("git", "rev-list", "--reverse", "--topo-order", "--parents",
                  new, "^" + old).splitlines()
    for entry in commits:
        commit, *parents = entry.split()
        parent = parents[0] if parents else None
        for offence in by_trees("gen_asm", parent, commit,
                                lambda parent=parent, commit=commit: _gen_asm_diff_offences(parent, commit)):
            if offence.startswith("C3 "):
                offence += " (commit %s)" % commit
            offences.append(offence)
    return list(dict.fromkeys(offences))


def show(rev, path):
    spec = (":%s" if rev == ":" else rev + ":%s") % path
    # Decode explicitly: with text=True alone Windows uses the locale code page
    # (cp1252), whose undefined bytes (0x9D in a UTF-8 quote) crash the reader
    # thread and leave stdout None.
    proc = subprocess.run(["git", "show", spec], capture_output=True, text=True,
                          encoding="utf-8", errors="replace")
    if proc.returncode != 0:
        raise SystemExit("conversion_gate: cannot read %s — a matched row's source "
                         "must exist at its revision (ledger corruption?)" % spec)
    return proc.stdout


def matched_by_rva(rev):
    rows = {}
    for row in csv.DictReader(io.StringIO(show(rev, LEDGER))):
        if row.get("status") == "matched":
            rows.setdefault(row["target_rva"], []).append(row)
    return rows


def ledger_blob(rev):
    spec = (":%s" if rev == ":" else rev + ":%s") % LEDGER
    return run("git", "rev-parse", spec).strip()


def naked_keys(rev, all_rows, sources):
    """Row keys naked at `rev`, judged by progress.py's per-row machinery.

    Feeds naked_cpp_rows every matched row of each affected source, not just
    the changed rows: its sole-row-sole-body proof is only valid on whole files.
    A source unreadable at `rev` (pre-existing ledger corruption: a matched
    row names a file absent from that tree) contributes no keys — its coverage
    cannot be proven clean, so Rule B cannot count it as lost. Warns loudly
    instead of crashing the gate, so the repair commit can land.
    """
    texts, missing = {}, []
    for s in sources:
        if Path(s).suffix.lower() not in CPP_SUFFIXES:
            continue
        try:
            texts[s] = show(rev, s)
        except SystemExit:
            missing.append(s)
    if missing:
        print("conversion gate: %s not readable at %s — a matched row names "
              "a file absent from that tree (pre-existing ledger corruption, "
              "not this commit). Its coverage is unverifiable and excluded "
              "from Rule B." % (", ".join(sorted(missing)), rev), file=sys.stderr)
    matched = {(r["name"], r["target_rva"]): (int(r["target_size"]), r["source"])
               for rows in all_rows.values() for r in rows if r["source"] in texts}
    return naked_cpp_rows(matched, texts)


def clean_coverage_lost(old, new):
    if ledger_blob(old) == ledger_blob(new):
        return []
    old_rows, new_rows = matched_by_rva(old), matched_by_rva(new)
    changed = [rva for rva, rows in new_rows.items()
               if rva in old_rows and
               {r["source"] for r in old_rows[rva]} != {r["source"] for r in rows}]
    if not changed:
        return []

    import build
    import pe_imports

    imports = None

    def retail_imports():
        nonlocal imports
        if imports is None:
            imports = pe_imports.read_imports(build.EXE.read_bytes())
        return imports

    source_text = {}

    def historical_source(rev, path):
        key = rev, path
        if key not in source_text:
            source_text[key] = show(rev, path)
        return source_text[key]

    def clean_sources(rev, rva, rows_by_rva, naked):
        # Share progress.py's classification: prebuilt archives and both
        # assembly suffixes own no clean C++ coverage. This also prevents a
        # live C++ row from retaining Rule B coverage by moving into a .lib.
        # A generated, retail-proven FF25 import placeholder owns linker glue,
        # not recovered C++. Its real ABI stub may be assembly. Neither a tag
        # nor another generated C++ family grants this narrow exception.
        return sorted({r["source"] for r in rows_by_rva[rva]
                       if source_kind(r["source"]) == "cpp"
                       and (r["name"], r["target_rva"]) not in naked
                       and not pe_imports.generated_import_scaffold(
                           r, build.read_target_bytes, retail_imports,
                           lambda path: historical_source(rev, path))})

    old_naked = naked_keys(old, old_rows, {r["source"] for rva in changed for r in old_rows[rva]})
    new_naked = naked_keys(new, new_rows, {r["source"] for rva in changed for r in new_rows[rva]})
    lost = []
    for rva in changed:
        before = clean_sources(old, rva, old_rows, old_naked)
        if before and not clean_sources(new, rva, new_rows, new_naked):
            lost.append((rva, old_rows[rva][0]["name"], ", ".join(before),
                         ", ".join(sorted({r["source"] for r in new_rows[rva]}))))
    return lost


def main():
    if len(sys.argv) != 3:
        raise SystemExit(__doc__.strip().splitlines()[2].strip())
    old, new = sys.argv[1], sys.argv[2]
    failed = False
    for path, line in by_trees("lift", old, new, lambda: added_lift_lines(old, new)):
        failed = True
        print("conversion gate: %s adds a naked/__emit body outside Code/gen_small/:\n"
              "    %s" % (path, line), file=sys.stderr)
    if failed:
        print("A lift is not a conversion: it deletes the C++ this project exists to\n"
              "produce and moves progress.py C++ exact by +0. Convert to real C++, or\n"
              "leave the .asm dump alone (codegen blockers: Code/masm_dumps/*.asm).",
              file=sys.stderr)
    for offence in gen_asm_offences(old, new):
        failed = True
        print("conversion gate: " + offence, file=sys.stderr)
    for path, words in by_trees("cl-flags", old, new, lambda: added_cl_garbage(old, new)):
        failed = True
        print("conversion gate: %s: not portable: %s\n"
              "An absolute #include fails on every other machine. Words in `// cl:` that are not\n"
              "flags make cl -E fail, which breaks the link census; if that is a mangled /I flag,\n"
              "your shell rewrote it: in Git Bash set MSYS_NO_PATHCONV=1 before the tool that\n"
              "writes the line." % (path, words), file=sys.stderr)
    for path, refusal in by_trees("cl-allowlist", old, new, lambda: added_cl_unsafe(old, new)):
        failed = True
        print("conversion gate: %s: a `// cl:` flag outside tools/cl_flags.py: %s\n"
              "A flag that loads code or writes files (/B1, /Fa, /Fo, /Yc, @file, /link, ...)\n"
              "would run on every machine that builds this commit, and an include path must stay\n"
              "inside the checkout. A new code-generation flag is a reviewed edit to cl_flags.py."
              % (path, refusal), file=sys.stderr)
    for rva, name, old_src, new_src in by_trees("coverage", old, new, lambda: clean_coverage_lost(old, new)):
        failed = True
        print("conversion gate: %s (%s) was clean C++ at %s, repointed to %s.\n"
              "C++ exact never goes backward: retract the row in its own commit if the\n"
              "claim is wrong; never swap a dump under a live claim."
              % (rva, name, old_src, new_src), file=sys.stderr)
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
