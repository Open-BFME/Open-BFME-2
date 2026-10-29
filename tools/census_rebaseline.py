#!/usr/bin/env python3
"""Record the census rule change: one re-baseline row measured under both rules.

link_census.py measures LINKING under RULES. A row that only switched rules
would read as lost progress, so the first RULES row carries the previous
rules' figures for the very same objects in its *_prev_rule columns
(prev_rules = the last row's rules). This script measures both on one frozen
commit and appends that row; it never pushes. Which previous rules it
measures, and how, follows from the history's last row:

  IN_PROCESS_RULES (none since retail-truth-5; retail-truth-3 was RULES
    without keep_rule's `retail_first` exemption): measured in the same
    judgment as RULES, on the same link log, /MAP and objects
    (link_census.record(rebaseline=REBASELINE_IN_PROCESS)). Steps 1, 3, 4 and
    5 below; step 2 does not apply.
  OLD_TOOL_RULES, measured by the previous link_census.py (step 2):
    PREVIOUS_RULES (retail-truth-4: an object's lowest row places it in link
    order even when another object's row claims that address). Placement
    changes the link itself, so the previous rules cannot be judged on this
    census's log: the previous tool links the same objects in its own order.
    Its default is the parent of the commit that introduced RULES.
    LEGACY_RULES (majority-0): its default is the parent of the commit that
    ported Open-BFME-1's rules (keep_rule).

  python3 tools/census_rebaseline.py                 # build, measure both rules, append the row
  python3 tools/census_rebaseline.py --commit        # ... and commit it with the refreshed card
  python3 tools/census_rebaseline.py --old-tools REV # the previous link_census.py (default: found)

Run it, with every other census publisher paused, on a clean checkout of
origin/master after the tools that introduced RULES landed:

  1. link_census.py --build: compile what is not census-current (Open-BFME-1's
     receipts), link in retail order, write build/link_census/census.json.
  2. The previous link_census.py (git show REV:tools/link_census.py), run in
     a separate process against the same objects with its outputs redirected
     to build/link_census_rebaseline/old/: its link (in its own link order),
     its status and its history row, from which the previous rules' figures
     are read. It proves the objects current by step 1's compile receipts.
     The objects' digest must equal the census's before and after.
     link_check's index is the one output it cannot redirect; step 3
     rewrites it.
  3. link_census.record(census, rows, rebaseline=old): the selection link,
     the new status and the one RULES row (UTC), refused unless the commit,
     tools and objects are still those of steps 1 and 2.
  4. readme_progress.py and progress_site.py render the card, chart and map
     (docs/discord-progress.json and progress_history.csv are left alone).
  5. The reporting tests that read the real history must pass.
"""
import argparse
import json
import os
import subprocess
import sys
import types
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import link_census  # noqa: E402

WORK = ROOT / "build" / "link_census_rebaseline"
OLD_FIGURES = WORK / "old_rules.json"
ARTIFACTS = ("reverse/link_census_history.csv", "reverse/link_status.csv",
             "docs/progress.svg", "docs/progress_chart.svg", "docs/progress_map.svg")
MARKER = f'RULES = "{link_census.RULES}"'
# The port of Open-BFME-1's rules introduced keep_rule; the previous census
# had the majority keeper's STLport/array-helper exemption instead.
PORT_MARKER = "def keep_rule("
LEGACY_MARKER = "COMDAT_EXEMPT_PREFIXES"
PREVIOUS_MARKER = f'RULES = "{link_census.PREVIOUS_RULES}"'
# The previous rules a separate run of their own link_census.py measures:
# {rules: the text whose first appearance in tools/link_census.py introduced
# the rules after them (default_old_tools takes that commit's parent)}.
OLD_TOOL_RULES = {link_census.LEGACY_RULES: PORT_MARKER, link_census.PREVIOUS_RULES: MARKER}


def git(*args, check=True):
    done = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True)
    if check and done.returncode:
        raise SystemExit(f"census_rebaseline: git {' '.join(args)} failed: {done.stderr.strip()}")
    return done.stdout.strip()


def default_old_tools(previous=link_census.LEGACY_RULES):
    """The parent of the commit that introduced the rules after `previous`:
    for LEGACY_RULES the port of Open-BFME-1's rules (the first link_census.py
    defining keep_rule), for PREVIOUS_RULES the first naming RULES."""
    marker = OLD_TOOL_RULES[previous]
    found = git("log", "--format=%H", "--reverse", "-S", marker, "--", "tools/link_census.py").split()
    if not found:
        raise SystemExit(f"census_rebaseline: no commit introduces {marker}; pass --old-tools")
    return git("rev-parse", found[0] + "^")


def old_source(rev, previous=link_census.LEGACY_RULES):
    """The previous rules' link_census.py: for LEGACY_RULES the majority
    keeper, no RULES; for PREVIOUS_RULES the census naming them, not RULES."""
    text = git("show", f"{rev}:tools/link_census.py")
    if previous == link_census.LEGACY_RULES:
        wrong = MARKER in text or PORT_MARKER in text or LEGACY_MARKER not in text
    else:
        wrong = MARKER in text or PREVIOUS_MARKER not in text or "def link_order" not in text
    if wrong or "def write_status" not in text or "def record" not in text:
        raise SystemExit(f"census_rebaseline: {rev}:tools/link_census.py is not the previous rules' census")
    return text


def preflight(allow_any_commit=False):
    """A clean tracked tree on origin/master whose history still ends in the
    previous rules."""
    dirty = git("status", "--porcelain", "-uno")
    if dirty:
        raise SystemExit(f"census_rebaseline: the checkout has uncommitted changes:\n{dirty}")
    head, origin = git("rev-parse", "HEAD"), git("rev-parse", "origin/master", check=False)
    if head != origin and not allow_any_commit:
        raise SystemExit(f"census_rebaseline: HEAD {head[:10]} is not origin/master {origin[:10]}; "
                         "fetch and check out the frozen master (or pass --any-commit)")
    history = link_census.read_history()
    if history and link_census.row_rules(history[-1]) == link_census.RULES:
        raise SystemExit(f"census_rebaseline: the history already records {link_census.RULES}; nothing to do")
    return head


def previous_rules():
    """The rules of the history's last row: what the re-baseline measures
    besides RULES."""
    history = link_census.read_history()
    return link_census.row_rules(history[-1]) if history else None


def load_old(rev, out, previous=link_census.LEGACY_RULES):
    """The previous link_census.py as a module of its own, run as if it were
    tools/link_census.py (its ROOT), but with every output redirected under
    `out`: it never writes the real status, history or link outputs. It
    proves its objects current by this census's compile receipts."""
    module = types.ModuleType("link_census_previous")
    module.__file__ = str(ROOT / "tools" / "link_census.py")
    # Its process pools (read_facts) pickle its functions by module name: the
    # parent and its forked workers must find the module in sys.modules.
    sys.modules[module.__name__] = module
    exec(compile(old_source(rev, previous), f"{rev}:tools/link_census.py", "exec"), module.__dict__)
    out.mkdir(parents=True, exist_ok=True)
    module.OUT = out
    module.STATUS = out / "link_status.csv"
    module.HISTORY = out / "link_census_history.csv"
    real = link_census.HISTORY
    module.HISTORY.write_bytes(real.read_bytes() if real.exists() else b"")
    for name in ("SELECTED", "DUPLICATES", "ALIASED", "SELECTION", "UNREFERENCED_COPIES"):
        if hasattr(module, name):
            setattr(module, name, out / Path(getattr(module, name)).name)
    if hasattr(module, "_INPUT_RECEIPTS"):
        module._INPUT_RECEIPTS = link_census.input_receipts()
    return module


def measure_old(rev, out=WORK / "old", previous=None):
    """Step 2, in its own process: the previous rules' figures (`previous`,
    default the history's last row's) for the objects the census linked."""
    previous = previous or previous_rules() or link_census.LEGACY_RULES
    census = json.loads((link_census.OUT / "census.json").read_text(encoding="utf-8"))
    rows = link_census.ledger()
    present, missing = link_census.objects(rows)
    if missing or census.get("missing"):
        raise SystemExit("census_rebaseline: objects are missing; build everything first")
    digest = link_census.objects_digest(present)
    if digest != census.get("objects_digest"):
        raise SystemExit("census_rebaseline: the objects are not the ones the census linked")
    old = load_old(rev, out, previous)
    before = old.read_history()
    old.main(["--history"])
    after = old.read_history()
    if len(after) != len(before) + 1:
        raise SystemExit("census_rebaseline: the previous census appended no row")
    if link_census.objects_digest(present) != digest:
        raise SystemExit("census_rebaseline: the objects changed while the previous rules measured them")
    row = after[-1]
    if previous != link_census.LEGACY_RULES and link_census.row_rules(row) != previous:
        raise SystemExit(f"census_rebaseline: the previous tool recorded {link_census.row_rules(row)}, not {previous}")
    figures = {"rules": previous, "old_tools": rev, "commit": row["commit"], "date": row["date"],
               "objects_digest": digest, "census_when": census["when"],
               **{key: int(row[key]) for key in ("files", "files_linked", "linked_bytes", "linked_authored",
                                                 "game_code", "objects")}}
    if figures["commit"] != link_census.head() or census.get("commit") != figures["commit"]:
        raise SystemExit("census_rebaseline: the previous rules measured another commit")
    OLD_FIGURES.parent.mkdir(parents=True, exist_ok=True)
    OLD_FIGURES.write_text(json.dumps(figures, indent=1), encoding="utf-8")
    print(f"census_rebaseline: {previous}: {figures['files_linked']:,} files, "
          f"authored {figures['linked_authored']:,} / {figures['game_code']:,}")
    return figures


def record_in_process():
    """Steps 3 for IN_PROCESS_RULES: one judgment of this census's log, /MAP and
    objects under both rules; record() refuses unless the commit, tools and
    objects are still those the census linked."""
    census = json.loads((link_census.OUT / "census.json").read_text(encoding="utf-8"))
    if census.get("rules") != link_census.RULES or census.get("commit") != link_census.head():
        raise SystemExit("census_rebaseline: census.json is not this commit's RULES census")
    return link_census.record(census, link_census.ledger(), rebaseline=link_census.REBASELINE_IN_PROCESS)


def record_new(figures):
    """Step 3: the RULES row, refused unless the objects are those step 2 measured."""
    census = json.loads((link_census.OUT / "census.json").read_text(encoding="utf-8"))
    if census.get("rules") != link_census.RULES or census.get("commit") != figures["commit"]:
        raise SystemExit("census_rebaseline: census.json is not this commit's RULES census")
    if census.get("objects_digest") != figures["objects_digest"] or census["when"] != figures["census_when"]:
        raise SystemExit("census_rebaseline: the previous rules measured other objects than this census")
    if census.get("commit") != link_census.head():
        raise SystemExit("census_rebaseline: HEAD is not the commit both rules measured")
    rows = link_census.ledger()
    # record() itself refuses, before writing anything, unless HEAD, the
    # objects and the game code are those of both measurements.
    return link_census.record(census, rows, rebaseline=figures)


def run(*command):
    print("+ " + " ".join(command), flush=True)
    done = subprocess.run(command, cwd=ROOT)
    if done.returncode:
        raise SystemExit(f"census_rebaseline: {' '.join(command)} exited {done.returncode}; nothing committed")


def message_in_process(new, previous=None):
    def pct(field):
        return 100 * int(new[field]) / int(new["game_code"])
    previous = previous or new.get("prev_rules") or link_census.PREVIOUS_RULES
    why = {"retail-truth-3": "an unproven COMDAT copy that differs from the proven one loses, even when "
                             "the copy the link keeps is retail's",
           "retail-truth-2": "every COMDAT copy proven not retail's loses, and so does an unproven one "
                             "that differs from the proven one"}.get(previous, "the previous keep rule")
    return (f"link_census: re-baseline LINKING under {link_census.RULES}\n\n"
            f"One census of {new['commit']} judged under both rules in one pass, on the same link "
            f"log, /MAP and objects ({previous}: {why}; {link_census.RULES}: neither loses when the "
            "link keeps a retail copy).\n\n"
            f"  {previous:<22} {int(new['files_linked_prev_rule']):>6,} files  "
            f"{int(new['linked_authored_prev_rule']):>10,} B  {pct('linked_authored_prev_rule'):6.2f}%\n"
            f"  {link_census.RULES:<22} {int(new['files_linked']):>6,} files  "
            f"{int(new['linked_authored']):>10,} B  {pct('linked_authored'):6.2f}%\n\n"
            "The row's *_prev_rule columns hold the previous rules' figures\n"
            f"(prev_rules={previous}); progress.py, the card and the chart\n"
            "report the step as a rule change, not as progress. Card, chart\n"
            "and map regenerated (no Discord post).\n")


def message(old, new):
    def pct(row, field="linked_authored"):
        return 100 * int(row[field]) / int(row["game_code"])
    previous = old.get("rules") or link_census.LEGACY_RULES
    why = {link_census.PREVIOUS_RULES: f".\n{previous} places an object by its lowest row even when another\n"
                                       f"object's row claims that address (an ICF fold); {link_census.RULES}\n"
                                       "by its own unshared rows, so each rule linked in its own order"}.get(previous, "")
    return (f"link_census: re-baseline LINKING under {link_census.RULES}\n\n"
            f"One census of {new['commit']} measured under both rules on the same objects\n"
            f"(objects digest {old['objects_digest'][:16]}); the previous rules by\n"
            f"{old['old_tools'][:10]}:tools/link_census.py, outputs redirected{why}.\n\n"
            f"  {previous:<22} {int(old['files_linked']):>6,} files  "
            f"{int(old['linked_authored']):>10,} B  {pct(old):6.2f}%\n"
            f"  {link_census.RULES:<22} {int(new['files_linked']):>6,} files  "
            f"{int(new['linked_authored']):>10,} B  {pct(new):6.2f}%\n\n"
            "The row's *_prev_rule columns hold the previous rules' figures\n"
            f"(prev_rules={previous}); progress.py, the card and the chart\n"
            "report the step as a rule change, not as lost progress. Card, chart\n"
            "and map regenerated (no Discord post).\n")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--old-tools", help="commit holding the previous link_census.py (default: found)")
    ap.add_argument("--commit", action="store_true", help="commit the row and the refreshed card (never pushes)")
    ap.add_argument("--any-commit", action="store_true", help="allow a HEAD other than origin/master (testing)")
    ap.add_argument("--measure-old", metavar="REV", help=argparse.SUPPRESS)
    ap.add_argument("--record-new", action="store_true", help=argparse.SUPPRESS)
    ap.add_argument("--record-in-process", action="store_true", help=argparse.SUPPRESS)
    args = ap.parse_args(argv)
    if args.record_in_process:
        record_in_process()
        return 0
    if args.measure_old:
        measure_old(args.measure_old)
        return 0
    if args.record_new:
        record_new(json.loads(OLD_FIGURES.read_text(encoding="utf-8")))
        return 0
    head = preflight(args.any_commit)
    previous = previous_rules()
    in_process = previous in link_census.IN_PROCESS_RULES
    if in_process and args.old_tools:
        raise SystemExit(f"census_rebaseline: {previous} is measured in the same judgment; --old-tools does not apply")
    if not in_process and previous not in OLD_TOOL_RULES:
        raise SystemExit(f"census_rebaseline: the history's last row is {previous}; this tool re-baselines "
                         f"{link_census.RULES} from "
                         f"{', '.join([*link_census.IN_PROCESS_RULES, *OLD_TOOL_RULES])} only")
    rev = None if in_process else args.old_tools or default_old_tools(previous)
    if rev:
        old_source(rev, previous)
    print(f"census_rebaseline: measuring {head[:10]}; previous rules ({previous}) "
          f"{'in the same judgment' if in_process else 'from ' + rev[:10]}. "
          "Every other census publisher must be paused.", flush=True)
    OLD_FIGURES.unlink(missing_ok=True)
    py = sys.executable
    def frozen():
        if git("rev-parse", "HEAD") != head or git("status", "--porcelain", "-uno", "--", *link_census.CENSUS_INPUTS,
                                                    "reverse/link_census_history.csv", "reverse/link_status.csv"):
            raise SystemExit("census_rebaseline: HEAD moved or the tree changed during the run; nothing committed")
    run(py, "tools/link_census.py", "--build")
    frozen()
    if in_process:
        run(py, "tools/census_rebaseline.py", "--record-in-process")
    else:
        run(py, "tools/census_rebaseline.py", "--measure-old", rev)
        frozen()
        run(py, "tools/census_rebaseline.py", "--record-new")
    run(py, "tools/readme_progress.py")
    run(py, "tools/progress_site.py", "render", "build/site/index.html", "--svg", "docs")
    run(py, "-m", "pytest", "-q", "-p", "no:cacheprovider", "tools/tests/test_link_census_history.py",
        "tools/tests/test_census_rules_reporting.py",
        "tools/tests/test_progress.py::test_readme_headline_is_a_recovered_figure")
    if git("rev-parse", "HEAD") != head:
        raise SystemExit("census_rebaseline: HEAD moved during the run; nothing committed")
    new = link_census.read_history()[-1]
    text = message_in_process(new, previous) if in_process else message(json.loads(OLD_FIGURES.read_text(encoding="utf-8")),
                                                                 new)
    print(text)
    if args.commit:
        git("add", "--", *ARTIFACTS)
        done = subprocess.run(["git", "commit", "-q", "-F", "-"], cwd=ROOT, input=text + "\n", text=True)
        if done.returncode:
            raise SystemExit("census_rebaseline: git commit failed (hooks?); the row is staged, nothing pushed")
        print("census_rebaseline: committed; push it yourself, then resume the publishers")
    else:
        print("census_rebaseline: not committed; review `git diff`, then commit "
              + " ".join(ARTIFACTS))
    return 0


if __name__ == "__main__":
    sys.exit(main())
