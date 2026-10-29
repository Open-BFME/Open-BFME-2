"""link_census --dry: a whole census that records nothing."""
import json
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census  # noqa: E402
import link_check  # noqa: E402


@pytest.fixture
def real_outputs(tmp_path, monkeypatch):
    out = tmp_path / "link_census"
    out.mkdir()
    (out / "census.log").write_text("previous census log\n", encoding="utf-8")
    history = tmp_path / "reverse" / "link_census_history.csv"
    history.parent.mkdir()
    history.write_text("date,commit\n2026-10-29 12:00,abc\n", encoding="utf-8")
    monkeypatch.setattr(link_census, "OUT", out)
    monkeypatch.setattr(link_census, "HISTORY", history)
    monkeypatch.setattr(link_census, "STATUS", tmp_path / "reverse" / "link_status.csv")
    for name in ("UNREFERENCED_COPIES", "SELECTED", "DUPLICATES", "ALIASED", "SELECTION"):
        monkeypatch.setattr(link_census, name, out / Path(getattr(link_census, name)).name)
    monkeypatch.setattr(link_check, "INDEX", out / "link_index.pkl")
    return tmp_path, out, history


def test_dry_redirects_every_recorded_output(real_outputs):
    tmp_path, out, history = real_outputs
    dry = tmp_path / "dry"
    link_census.use_dry_outputs(dry)
    for path in (link_census.OUT, link_census.STATUS, link_census.HISTORY, link_census.UNREFERENCED_COPIES,
                 link_census.SELECTED, link_census.DUPLICATES, link_census.ALIASED, link_census.SELECTION,
                 link_check.INDEX):
        assert Path(path) == dry or Path(path).parent == dry, path
    # the row is appended to a copy: the real history is read, never written
    assert link_census.HISTORY.read_bytes() == history.read_bytes()
    link_census.write_history([{"date": "2026-10-29 13:00", "commit": "def", "rules": link_census.RULES}])
    assert history.read_text(encoding="utf-8") == "date,commit\n2026-10-29 12:00,abc\n"
    # the last real census's log seeds the selection link's prediction
    assert (dry / "census.log").read_text(encoding="utf-8") == "previous census log\n"


def test_dry_needs_history(real_outputs):
    with pytest.raises(SystemExit):
        link_census.main(["--dry"])
    with pytest.raises(SystemExit):
        link_census.main(["--dry", "--history", "--status"])


@pytest.fixture
def dry_census(tmp_path, monkeypatch):
    """A finished dry census of two objects: census.json, the plain log and the /MAP link's inputs."""
    monkeypatch.setattr(link_census, "ROOT", tmp_path)
    dry = tmp_path / "build" / "link_census_dry"
    dry.mkdir(parents=True)
    monkeypatch.setattr(link_census, "DRY_OUT", dry)
    monkeypatch.setattr(link_census, "OUT", dry)
    monkeypatch.setattr(link_census, "_REPLAY", {})
    present = []
    for name in ("a.obj", "b.obj"):
        (tmp_path / name).write_bytes(name.encode())
        present.append(tmp_path / name)
    log = "a.obj : error LNK2019: unresolved external symbol _f referenced in function _g\n"
    (dry / "census.json").write_text(json.dumps({"objects_digest": link_census.objects_digest(present),
                                                 "seconds": 12.5}), encoding="utf-8")
    (dry / "census.log").write_text(log, encoding="utf-8")
    (dry / "census.rsp").write_text(link_census._rsp_text(present), encoding="utf-8")
    (dry / "selected.rsp").write_text(link_census._rsp_text(present), encoding="utf-8")
    link_census.stub_object({"_f"}, dry / "selected_stubs.obj")
    (dry / "selected.map").write_text(" 0001:00000000       _f    00401000 f   a.obj\n", encoding="latin-1")
    return tmp_path, dry, present, log


def test_replay_reuses_the_dry_census_links_of_the_same_objects(dry_census):
    _, dry, present, log = dry_census
    assert link_census.replayed_link(present) == (log, 12.5)
    assert link_census.selection_link(present, log) == (dry / "selected.map").read_text(encoding="latin-1")
    assert not (dry / "replay_stubs.obj").exists()


def test_replay_refuses_other_objects_order_or_names(dry_census, monkeypatch):
    tmp_path, dry, present, log = dry_census
    with pytest.raises(SystemExit):
        link_census.replayed_link(present[::-1])  # another link order
    (tmp_path / "b.obj").write_bytes(b"recompiled")
    with pytest.raises(SystemExit):
        link_census.replayed_link(present)  # other bytes
    monkeypatch.setattr(link_census, "_REPLAY", {"census": True})
    with pytest.raises(SystemExit):
        link_census.selection_link(present, log + "b.obj : error LNK2001: unresolved external symbol _h\n")
    monkeypatch.setattr(link_census, "OUT", tmp_path / "build" / "link_census")
    with pytest.raises(SystemExit):
        link_census.replayed_link(present)  # never a real census's outputs
