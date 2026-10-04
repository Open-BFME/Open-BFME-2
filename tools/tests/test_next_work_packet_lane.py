"""The requested reference packet lane must not require other queue reports."""
import json
import sys
from pathlib import Path
import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import next_work
import build


def test_packet_lane_is_independent_of_drift_reports(monkeypatch, capsys):
    def unrelated(*args, **kwargs):
        raise AssertionError("packet selection loaded an unrelated report")

    monkeypatch.setattr(sys, "argv", ["next_work.py", "--tier", "packet", "--json"])
    monkeypatch.setattr(next_work, "check_ledger", lambda: "ledger healthy")
    monkeypatch.setattr(build, "load_claim_rows", lambda **kwargs: [])
    monkeypatch.setattr(next_work.claims, "busy_rvas", lambda: set())
    for name in ["drift_quick_wins", "structural_candidates", "ghidra_absent_candidates",
                 "reloc_named_candidates", "anchored_candidates"]:
        monkeypatch.setattr(next_work, name, unrelated)
    seen = []
    def packets(claimed):
        seen.append(claimed)
        return []
    monkeypatch.setattr(next_work, "packet_candidates", packets)

    next_work.main()
    output = json.loads(capsys.readouterr().out)
    assert output["ledger"] == "ledger healthy"
    assert output["tier"] == "Zero Hour work packet"
    assert output["selection"] is None
    assert seen == [set()]


def test_packet_lane_still_refuses_an_invalid_ledger(monkeypatch):
    monkeypatch.setattr(sys, "argv", ["next_work.py", "--tier", "packet"])
    def invalid():
        raise SystemExit(2)
    def premature(*args, **kwargs):
        raise AssertionError("invalid ledger reached packet selection")
    monkeypatch.setattr(next_work, "check_ledger", invalid)
    monkeypatch.setattr(next_work, "packet_candidates", premature)
    with pytest.raises(SystemExit) as error:
        next_work.main()
    assert error.value.code == 2
