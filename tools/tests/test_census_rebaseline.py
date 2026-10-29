"""census_rebaseline.py: both rules on one commit and the same objects, the
previous tool never touching the real outputs, and refusal otherwise."""
import json
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import census_rebaseline as rb
import link_census

OLD_TOOL = '''
from pathlib import Path
COMDAT_EXEMPT_PREFIXES = ("??_H@",)
ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "build" / "link_census"
STATUS = ROOT / "reverse/link_status.csv"
HISTORY = ROOT / "reverse/link_census_history.csv"
def write_status(): pass
def record(): pass
def read_history():
    return HISTORY.read_text().splitlines()
def main(argv):
    (OUT / "census.json").write_text("{}")
    STATUS.write_text("status")
    HISTORY.write_text(HISTORY.read_text() + "row\\n")
'''


def _repo(tmp_path):
    root = tmp_path / "repo"
    (root / "tools").mkdir(parents=True)
    run = lambda *a: subprocess.run(["git", "-C", str(root), *a], check=True, capture_output=True, text=True)
    run("init", "-q")
    ported = "def keep_rule(copies): pass\n" + OLD_TOOL.replace("COMDAT_EXEMPT_PREFIXES", "_GONE")
    # legacy, the rule port, then the history tooling that adds RULES
    for text in (OLD_TOOL, ported, ported + f"\n{rb.MARKER}\n"):
        (root / "tools" / "link_census.py").write_text(text)
        run("add", "tools/link_census.py")
        run("-c", "user.name=T", "-c", "user.email=t@example.invalid", "commit", "-qm", "x")
    return root, run("rev-parse", "HEAD~2").stdout.strip(), run("rev-parse", "HEAD~1").stdout.strip()


def test_default_previous_tool_is_the_parent_of_the_rule_port(tmp_path, monkeypatch):
    root, old, new = _repo(tmp_path)
    monkeypatch.setattr(rb, "ROOT", root)
    assert rb.default_old_tools() == old  # not the parent of the RULES commit: that is the port
    assert "def record" in rb.old_source(old)
    for later in (new, "HEAD"):
        with pytest.raises(SystemExit, match="not the previous rules"):
            rb.old_source(later)


def test_previous_tool_runs_from_the_real_root_with_redirected_outputs(tmp_path, monkeypatch):
    root, old, _ = _repo(tmp_path)
    monkeypatch.setattr(rb, "ROOT", root)
    history = tmp_path / "history.csv"
    history.write_text("header\n")
    monkeypatch.setattr(link_census, "HISTORY", history)
    module = rb.load_old(old, tmp_path / "old")
    assert module.ROOT == root
    assert module.OUT == tmp_path / "old" and module.STATUS.parent == tmp_path / "old"
    module.main(["--history"])
    assert history.read_text() == "header\n"  # the real history is untouched
    assert module.read_history() == ["header", "row"]
    assert not (root / "reverse").exists() and not (root / "build").exists()


def test_preflight_refuses_dirty_moved_or_done(monkeypatch):
    answers = {}
    monkeypatch.setattr(rb, "git", lambda *a, check=True: answers[a[0] if a[0] != "rev-parse" else a[1]])
    monkeypatch.setattr(link_census, "read_history", lambda: [{"rules": ""}])
    answers.update({"status": " M Code/x.cpp", "HEAD": "a", "origin/master": "a"})
    with pytest.raises(SystemExit, match="uncommitted"):
        rb.preflight()
    answers["status"] = ""
    answers["origin/master"] = "b"
    with pytest.raises(SystemExit, match="not origin/master"):
        rb.preflight()
    assert rb.preflight(allow_any_commit=True) == "a"
    answers["origin/master"] = "a"
    monkeypatch.setattr(link_census, "read_history", lambda: [{"rules": link_census.RULES}])
    with pytest.raises(SystemExit, match="already records"):
        rb.preflight()


def _census_json(tmp_path, monkeypatch, **census):
    monkeypatch.setattr(link_census, "OUT", tmp_path)
    (tmp_path / "census.json").write_text(json.dumps({"rules": link_census.RULES, "commit": "c0ffee",
                                                      "objects_digest": "d1", "when": "2026-10-02 00:00",
                                                      "missing": 0, **census}))


def test_new_rules_refuse_other_objects_or_commit(tmp_path, monkeypatch):
    figures = {"commit": "c0ffee", "objects_digest": "d1", "census_when": "2026-10-02 00:00", "game_code": 7,
               "rules": link_census.LEGACY_RULES}
    monkeypatch.setattr(link_census, "ledger", lambda: [])
    monkeypatch.setattr(link_census, "head", lambda: "c0ffee")
    monkeypatch.setattr(link_census, "record", lambda census, rows, rebaseline: {"game_code": 7})
    _census_json(tmp_path, monkeypatch)
    assert rb.record_new(figures) == {"game_code": 7}
    _census_json(tmp_path, monkeypatch, objects_digest="other")
    with pytest.raises(SystemExit, match="other objects"):
        rb.record_new(figures)
    _census_json(tmp_path, monkeypatch, commit="beef")
    with pytest.raises(SystemExit, match="not this commit"):
        rb.record_new(figures)
    _census_json(tmp_path, monkeypatch)
    monkeypatch.setattr(link_census, "head", lambda: "moved")
    monkeypatch.setattr(link_census, "record", lambda *a, **k: pytest.fail("published on a moved HEAD"))
    with pytest.raises(SystemExit, match="HEAD is not the commit"):
        rb.record_new(figures)


def test_previous_rules_refuse_objects_that_change_under_them(tmp_path, monkeypatch):
    _census_json(tmp_path, monkeypatch)
    monkeypatch.setattr(link_census, "ledger", lambda: [])
    monkeypatch.setattr(link_census, "objects", lambda rows: (["a.obj"], []))
    digests = iter(["d1", "d2"])
    monkeypatch.setattr(link_census, "objects_digest", lambda present: next(digests))

    class Old:
        rows = [{}]

        def read_history(self):
            return list(self.rows)

        def main(self, argv):
            self.rows.append({"commit": "c0ffee"})
    monkeypatch.setattr(rb, "load_old", lambda rev, out, previous=None: Old())
    with pytest.raises(SystemExit, match="changed while the previous rules"):
        rb.measure_old("rev", tmp_path / "old")


def test_previous_rules_refuse_objects_the_census_did_not_link(tmp_path, monkeypatch):
    _census_json(tmp_path, monkeypatch)
    monkeypatch.setattr(link_census, "ledger", lambda: [])
    monkeypatch.setattr(link_census, "objects", lambda rows: (["a.obj"], []))
    monkeypatch.setattr(link_census, "objects_digest", lambda present: "rebuilt since")
    monkeypatch.setattr(rb, "load_old", lambda rev, out, previous=None: pytest.fail("measured other objects"))
    with pytest.raises(SystemExit, match="not the ones the census linked"):
        rb.measure_old("rev", tmp_path / "old")


def test_previous_rules_are_judged_in_process_on_the_census_itself(tmp_path, monkeypatch):
    seen = []
    monkeypatch.setattr(link_census, "ledger", lambda: [])
    monkeypatch.setattr(link_census, "head", lambda: "c0ffee")
    monkeypatch.setattr(link_census, "record", lambda census, rows, rebaseline: seen.append(rebaseline) or {})
    _census_json(tmp_path, monkeypatch)
    rb.record_in_process()
    assert seen == [link_census.REBASELINE_IN_PROCESS]
    for other in ({"commit": "beef"}, {"rules": link_census.PREVIOUS_RULES}):  # a retail-truth-4 census.json
        _census_json(tmp_path, monkeypatch, **other)
        with pytest.raises(SystemExit, match="not this commit's RULES census"):
            rb.record_in_process()
    assert len(seen) == 1


def _main_harness(monkeypatch, previous):
    commands = []
    monkeypatch.setattr(rb, "preflight", lambda allow: "c0ffee")
    monkeypatch.setattr(rb, "previous_rules", lambda: previous)
    monkeypatch.setattr(rb, "git", lambda *a, check=True: "c0ffee" if a[0] == "rev-parse" else "")
    monkeypatch.setattr(rb, "run", lambda *command: commands.append(command[1:]))
    monkeypatch.setattr(rb, "default_old_tools", lambda previous=None: "oldrev")
    monkeypatch.setattr(rb, "old_source", lambda rev, previous=None: "")
    row = {"commit": "c0ffee", "files_linked": "2", "linked_authored": "20", "game_code": "100",
           "files_linked_prev_rule": "1", "linked_authored_prev_rule": "10"}
    monkeypatch.setattr(link_census, "read_history", lambda: [row])
    monkeypatch.setattr(rb, "OLD_FIGURES", Path(str(rb.OLD_FIGURES) + ".test-unused"))
    return commands


def test_rebaseline_from_in_process_rules_runs_no_previous_tool(monkeypatch, capsys):
    # No rule is in-process since retail-truth-5; the path stays for the next keep-rule-only change.
    monkeypatch.setattr(link_census, "IN_PROCESS_RULES", {link_census.RETAIL_TRUTH_3: {"retail_first": False}})
    commands = _main_harness(monkeypatch, link_census.RETAIL_TRUTH_3)
    assert rb.main([]) == 0
    steps = [c[0] if len(c) == 1 else " ".join(c[:2]) for c in commands]
    assert steps[:2] == ["tools/link_census.py --build", "tools/census_rebaseline.py --record-in-process"]
    assert not any("--measure-old" in c for c in commands)
    out = capsys.readouterr().out
    assert f"prev_rules={link_census.RETAIL_TRUTH_3}" in out and "not committed" in out
    with pytest.raises(SystemExit, match="does not apply"):
        rb.main(["--old-tools", "rev"])


def test_rebaseline_refuses_a_history_it_cannot_continue(monkeypatch):
    _main_harness(monkeypatch, "retail-truth-0")
    with pytest.raises(SystemExit, match="re-baselines"):
        rb.main([])


PREVIOUS_TOOL = OLD_TOOL.replace("COMDAT_EXEMPT_PREFIXES", "_GONE") + f'''
{rb.PREVIOUS_MARKER}
UNREFERENCED_COPIES = OUT / "unreferenced_copies.json"
_INPUT_RECEIPTS = None
def keep_rule(copies): pass
def link_order(rows, data=()): pass
'''


def _placement_repo(tmp_path):
    """retail-truth-4's tool, then the commit that introduces RULES."""
    root = tmp_path / "repo"
    (root / "tools").mkdir(parents=True)
    run = lambda *a: subprocess.run(["git", "-C", str(root), *a], check=True, capture_output=True, text=True)
    run("init", "-q")
    for text in (PREVIOUS_TOOL, PREVIOUS_TOOL.replace(rb.PREVIOUS_MARKER, rb.MARKER)):
        (root / "tools" / "link_census.py").write_text(text)
        run("add", "tools/link_census.py")
        run("-c", "user.name=T", "-c", "user.email=t@example.invalid", "commit", "-qm", "x")
    return root, run("rev-parse", "HEAD~1").stdout.strip(), run("rev-parse", "HEAD").stdout.strip()


def test_placement_change_measures_retail_truth_4_with_its_own_tool(tmp_path, monkeypatch):
    # retail-truth-5 changes link placement, so retail-truth-4 links the same
    # objects in its own order in its own process: the parent of the RULES commit.
    root, old, new = _placement_repo(tmp_path)
    monkeypatch.setattr(rb, "ROOT", root)
    assert link_census.PREVIOUS_RULES in rb.OLD_TOOL_RULES
    assert link_census.PREVIOUS_RULES not in link_census.IN_PROCESS_RULES
    assert rb.default_old_tools(link_census.PREVIOUS_RULES) == old
    assert rb.PREVIOUS_MARKER in rb.old_source(old, link_census.PREVIOUS_RULES)
    for wrong in ((new, link_census.PREVIOUS_RULES), (old, link_census.LEGACY_RULES)):
        with pytest.raises(SystemExit, match="not the previous rules"):
            rb.old_source(*wrong)


def test_previous_tool_sees_this_census_receipts_and_redirected_outputs(tmp_path, monkeypatch):
    root, old, _ = _placement_repo(tmp_path)
    monkeypatch.setattr(rb, "ROOT", root)
    history = tmp_path / "history.csv"
    history.write_text("header\n")
    monkeypatch.setattr(link_census, "HISTORY", history)
    receipts = object()
    monkeypatch.setattr(link_census, "input_receipts", lambda: receipts)
    module = rb.load_old(old, tmp_path / "old", link_census.PREVIOUS_RULES)
    assert module._INPUT_RECEIPTS is receipts
    assert module.UNREFERENCED_COPIES == tmp_path / "old" / "unreferenced_copies.json"
    module.main(["--history"])
    assert history.read_text() == "header\n"


def test_previous_figures_must_be_measured_under_the_previous_rules(tmp_path, monkeypatch):
    _census_json(tmp_path, monkeypatch)
    monkeypatch.setattr(link_census, "ledger", lambda: [])
    monkeypatch.setattr(link_census, "objects", lambda rows: (["a.obj"], []))
    monkeypatch.setattr(link_census, "objects_digest", lambda present: "d1")
    monkeypatch.setattr(link_census, "head", lambda: "c0ffee")
    figures = {"files": "3", "files_linked": "2", "linked_bytes": "9", "linked_authored": "8", "game_code": "10",
               "objects": "3", "commit": "c0ffee", "date": "2026-10-02 00:01"}

    class Old:
        def __init__(self, rules):
            self.rows, self.rules = [{}], rules

        def read_history(self):
            return list(self.rows)

        def main(self, argv):
            self.rows.append({**figures, "rules": self.rules})
    monkeypatch.setattr(rb, "OLD_FIGURES", tmp_path / "old_rules.json")
    monkeypatch.setattr(rb, "load_old", lambda rev, out, previous=None: Old(link_census.RULES))
    with pytest.raises(SystemExit, match="recorded retail-truth-5, not retail-truth-4"):
        rb.measure_old("rev", tmp_path / "old", link_census.PREVIOUS_RULES)
    monkeypatch.setattr(rb, "load_old", lambda rev, out, previous=None: Old(link_census.PREVIOUS_RULES))
    got = rb.measure_old("rev", tmp_path / "old", link_census.PREVIOUS_RULES)
    assert (got["rules"], got["files_linked"], got["linked_authored"]) == (link_census.PREVIOUS_RULES, 2, 8)
    text = rb.message(got, {"commit": "c0ffee", "files_linked": 3, "linked_authored": 9, "game_code": 10})
    assert f"prev_rules={link_census.PREVIOUS_RULES}" in text and "ICF fold" in text


def test_rebaseline_from_retail_truth_4_runs_the_previous_tool(monkeypatch, capsys, tmp_path):
    commands = _main_harness(monkeypatch, link_census.PREVIOUS_RULES)
    old = {"rules": link_census.PREVIOUS_RULES, "old_tools": "oldrev", "objects_digest": "d" * 64,
           "files_linked": 1, "linked_authored": 10, "game_code": 100}
    monkeypatch.setattr(rb, "OLD_FIGURES", tmp_path / "old_rules.json")
    rb.OLD_FIGURES.write_text(json.dumps(old))
    monkeypatch.setattr(rb.OLD_FIGURES.__class__, "unlink", lambda self, missing_ok=False: None)
    assert rb.main([]) == 0
    steps = [" ".join(c[:2]) for c in commands]
    assert steps[:3] == ["tools/link_census.py --build", "tools/census_rebaseline.py --measure-old",
                         "tools/census_rebaseline.py --record-new"]
    assert commands[1][2] == "oldrev"
    assert f"prev_rules={link_census.PREVIOUS_RULES}" in capsys.readouterr().out


def test_previous_tool_functions_pickle_for_its_process_pools(tmp_path, monkeypatch):
    # retail-truth-4's read_facts sends object_facts to a ProcessPoolExecutor.
    import pickle
    root, old, _ = _placement_repo(tmp_path)
    monkeypatch.setattr(rb, "ROOT", root)
    monkeypatch.setattr(link_census, "HISTORY", tmp_path / "history.csv")
    monkeypatch.setattr(link_census, "input_receipts", lambda: None)
    monkeypatch.delitem(sys.modules, "link_census_previous", raising=False)
    module = rb.load_old(old, tmp_path / "old", link_census.PREVIOUS_RULES)
    assert pickle.loads(pickle.dumps(module.link_order)) is module.link_order
