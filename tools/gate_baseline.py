#!/usr/bin/env python3
"""reverse/gate_baseline.txt may only shrink.

The file excuses named rows from named gate checks (build.gate_baselined):
`<check> 0x<RVA> <ledger name>`, one per line. Lines are removed when the row
is fixed. Adding one is how a check gets quietly switched off for a row, so no
commit may add a line. A widened detector reseeds the file from a full-ledger
shadow run, in a commit reviewed as a verifier change (hook bypass by an
operator, never by an agent).

  python3 tools/gate_baseline.py --assert-shrink-only [REF]   # index vs REF (default HEAD)
  python3 tools/gate_baseline.py --range OLD NEW              # pre-push
"""
import argparse
import subprocess
import sys

BASELINE = "reverse/gate_baseline.txt"


def lines_at(spec):
    # cwd, not __file__: the hooks pipe this checker in as of the BASE
    # revision (`git show HEAD:tools/gate_baseline.py | python3 -`), so an
    # edit to it cannot approve itself.
    out = subprocess.run(["git", "show", spec], capture_output=True)
    if out.returncode != 0:
        return set()
    text = out.stdout.decode("utf-8", errors="replace")
    return {line.strip() for line in text.splitlines()
            if line.strip() and not line.startswith("#")}


def grown(old_spec, new_spec):
    return sorted(lines_at(new_spec) - lines_at(old_spec))


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--assert-shrink-only", metavar="REF", nargs="?", const="HEAD")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    args = parser.parse_args(argv)
    if args.range:
        old, new = (f"{ref}:{BASELINE}" for ref in args.range)
    else:
        old, new = f"{args.assert_shrink_only}:{BASELINE}", f":{BASELINE}"
    added = grown(old, new)
    if added:
        print(f"{BASELINE}: FAIL {len(added)} line(s) added; the baseline only shrinks")
        for line in added[:20]:
            print(f"  + {line}")
        raise SystemExit(1)
    print(f"{BASELINE}: OK (no line added)")


if __name__ == "__main__":
    main()
