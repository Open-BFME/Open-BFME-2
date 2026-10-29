"""link_census --dry: a whole census that records nothing."""
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
