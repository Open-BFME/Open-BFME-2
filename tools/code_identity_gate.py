#!/usr/bin/env python3
"""Commit gate for code identity: what staged code binds to, not only its bytes.

The byte gate proves a call's displacement reproduces retail; it cannot see
that the name called is defined in the tree by different code, or by several
objects, so the linked image runs something else (research 20, 29). This gate,
on the rows of every staged or delta source (after the byte gate built them):

  1. every REL32/DIR32 reference into retail .text binds to a symbol in its
     target's allowed set (allowed_symbols.py: owner row, own label or EH
     funclet, certified fold, or an undefined name the tool aliases to the
     owner). Other bindings are keyed (source, row, symbol, target, class);
  2. no name the staged objects define is a new duplicate definition or a new
     divergent COMDAT whose kept copy is not retail's (dup_defs.py);
  3. an added `/alternatename:A=B` pragma must say what the tool would emit:
     A is referenced at one retail address and B owns it. Only the tool
     decides an alias (allowed_symbols.py --alternatenames); a hand-written
     pragma that binds A elsewhere is refused;
  4. reverse/name_tiers.csv, when staged, equals what the tool writes;
  5. the baselines only shrink against HEAD.

Keys already present are debt in reverse/code_identity_baseline.tsv and
reverse/dup_defs_baseline.tsv, shrink-only. The register starts in shadow mode
(`# mode: shadow` in code_identity_baseline.tsv): findings print, the commit
passes. Changing the line to `# mode: enforce` is the operator's switch.

  python3 tools/code_identity_gate.py --staged          the pre-commit hook
  python3 tools/code_identity_gate.py --full            whole ledger, report new keys
  python3 tools/code_identity_gate.py --write-baseline  (shrink-only once it exists)
"""
import argparse
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import allowed_symbols as allowed  # noqa: E402
import dup_defs  # noqa: E402

BASELINE = ROOT / "reverse" / "code_identity_baseline.tsv"
HEADER = ("# Wrong code bindings, keyed source<TAB>row<TAB>symbol<TAB>retail target<TAB>class.\n"
          "# Shrink-only: written by tools/code_identity_gate.py --write-baseline; lines may be\n"
          "# deleted by hand once fixed, never added. See tools/allowed_symbols.py for the classes.\n")


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True).stdout


def read_register(text):
    keys, mode = set(), "shadow"
    for line in text.splitlines():
        if line.startswith("# mode:"):
            mode = line.split(":", 1)[1].strip()
        elif line.strip() and not line.startswith("#"):
            keys.add(line.rstrip("\n"))
    return keys, mode


def staged_sources():
    names = git("diff", "--cached", "--name-only", "--diff-filter=ACMR").split()
    out = {p for p in names if p.startswith("Code/") and p.endswith((".cpp", ".c"))}
    delta = subprocess.run([sys.executable, str(ROOT / "tools" / "delta_sources.py"), "--staged"], cwd=ROOT,
                           capture_output=True, text=True).stdout.split()
    return sorted(out | set(delta)), names


def added_alternatenames():
    """[(path, alias, target)] on lines the staged diff adds."""
    out = []
    path = None
    for line in git("diff", "--cached", "-U0", "--", "Code", "reference/shims").splitlines():
        if line.startswith("+++ "):
            path = line[6:] if line.startswith("+++ b/") else None
        elif line.startswith("+") and path:
            for m in allowed.ALTERNATENAME.finditer(line):
                out.append((path, m.group(1), m.group(2)))
    return out


def check(sources, staged_names, *, full=False):
    """(problems, notes) for the given sources (every matched row when full)."""
    t0 = time.time()
    ident, rows = allowed.load(None if full else sources or ["<none>"])
    found = allowed.scan(ident, rows)
    base, mode = read_register(BASELINE.read_text(encoding="utf-8") if BASELINE.exists() else "")
    problems = []
    keys = {allowed.key(rec) for rec in found if rec[5] in allowed.WRONG}
    for k in sorted(keys - base):
        problems.append("binding: " + k.replace("\t", " | "))
    # 2) duplicates / divergent COMDATs among names these objects define
    # A .lib source names no object by itself: row_object needs a row's member=
    # note to pick the extracted member, which load() put in ident.defs under the
    # same path. Its rows (in `rows` unless full) scope their members; only
    # non-library sources are scoped by path alone.
    objs = {str(allowed.row_object(r)) for r in rows} | {
        str(allowed.row_object({"source": s})) for s in sources
        if not s.lower().endswith(allowed.build.LIB_SUFFIX)}
    names = {n for n, copies in ident.defs.items() if full or any(c[0] in objs for c in copies)}
    sub = {n: ident.defs[n] for n in names}
    dkeys = dup_defs.debt(dup_defs.analyse(rows if full else allowed.census.ledger(), sub, ident.truth))
    for k in sorted(dkeys - dup_defs.read_baseline()):
        problems.append("definition: " + k.replace("\t", " | "))
    # 3) alternatename pragmas added by this commit
    alts = added_alternatenames() if not full else allowed.pragma_alternatenames(
        sorted({r["source"] for r in allowed.census.ledger()}))
    if alts:
        targets = {}
        everything = allowed.census.ledger()
        if not full:                         # only the rows whose objects reference an alias
            objs = set().union(*(ident.defs.referrers.get(a, set()) for _, a, _ in alts))
            everything = [r for r in everything if str(allowed.row_object(r)) in objs]
        for rec in allowed.scan(ident, everything):
            targets.setdefault(rec[3], set()).add(rec[4])
        for path, a, b in alts:
            verdict = allowed.judge_alternatename(ident, a, b, targets)
            if verdict != "ok":
                problems.append(f"alternatename ({verdict}): {path}: /alternatename:{a}={b}")
    # 4) name tiers are tool output
    if "reverse/name_tiers.csv" in staged_names:
        want = allowed.tiers_text(allowed.census.ledger())
        if (ROOT / "reverse" / "name_tiers.csv").read_text(encoding="utf-8") != want:
            problems.append("reverse/name_tiers.csv differs from tools/allowed_symbols.py --tiers")
    # 5) shrink-only registers
    for reg, reader in ((BASELINE, lambda t: read_register(t)[0]),
                        (dup_defs.BASELINE, lambda t: {line for line in t.splitlines()
                                                       if line.strip() and not line.startswith("#")})):
        rel = reg.relative_to(ROOT).as_posix()
        if rel in staged_names:
            head = git("show", f"HEAD:{rel}")
            if head:
                grown = reader(git("show", f":{rel}")) - reader(head)
                if grown:
                    problems.append(f"{rel} grew by {len(grown)} key(s); it may only shrink")
    return problems, mode, time.time() - t0, len(rows), found


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--staged", action="store_true")
    ap.add_argument("--full", action="store_true")
    ap.add_argument("--write-baseline", action="store_true")
    args = ap.parse_args(argv)
    if args.write_baseline:
        ident, rows = allowed.load()
        keys = {allowed.key(rec) for rec in allowed.scan(ident, rows) if rec[5] in allowed.WRONG}
        base, mode = read_register(BASELINE.read_text(encoding="utf-8") if BASELINE.exists() else "")
        if base and keys - base:
            print(f"refusing to add {len(keys - base)} key(s); fix them instead", file=sys.stderr)
            keys &= base
        BASELINE.write_text(HEADER + f"# mode: {mode}\n" + "".join(k + "\n" for k in sorted(keys)),
                            encoding="utf-8", newline="\n")
        print("code identity baseline:", len(keys))
        return 0
    if args.staged:
        sources, names = staged_sources()
        if not sources and not any(n in names for n in ("reverse/name_tiers.csv", "reverse/code_identity_baseline.tsv",
                                                         "reverse/dup_defs_baseline.tsv")):
            return 0
        # this hook line runs before the byte gate; compiling here leaves the
        # objects current, so the byte gate after it reuses them
        claimed = [r for r in allowed.census.ledger() if r["source"] in set(sources)]
        allowed.build.compile_rows(claimed, sorted({ROOT / r["source"] for r in claimed}))
    else:
        sources, names = [], []
    problems, mode, secs, nrows, _ = check(sources, names, full=args.full)
    for p in problems:
        print("  code identity: " + p, file=sys.stderr)
    print(f"code identity: {nrows} row(s), {len(problems)} new finding(s), {secs:.1f}s, mode {mode}", file=sys.stderr)
    if problems and mode == "enforce":
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
