"""WorldBuilder lead hooks in the donor sweeps and the near-miss closer."""
import importlib.util
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import wb_context  # noqa: E402


def _load(name):
    spec = importlib.util.spec_from_file_location(name, ROOT / "tools" / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


LEADS = (
    "target_rva,current_name,current_kind,wb_name,wb_file,score,evidence\n"
    "0x0F000100,,PLACEHOLDER,Thing::candidate,C:\\Projects\\bfme2\\Code\\T.cpp,6.0,strings\n"
    "0x0F000200,,UNROWED,Other::name,C:\\Projects\\bfme2\\Code\\X.cpp,1.0,align\n"
)


@pytest.fixture
def leads(tmp_path, monkeypatch):
    path = tmp_path / "leads.csv"
    path.write_text(LEADS)
    wb_context.clear_cache()
    parsed = wb_context.leads(path=path)
    monkeypatch.setattr(wb_context, "leads", lambda path=None, ledger=None, live=True: parsed)
    yield parsed
    wb_context.clear_cache()


def test_bfme1_donor_agreement_summary(leads):
    sweep = _load("bfme1_sweep")
    bodies = [
        {"bfme2_rva": 0x0F000100, "name": "?candidate@Thing@@QAEXXZ", "source": "Code/T.cpp"},
        {"bfme2_rva": 0x0F000200, "name": "?f@Y@@QAEXXZ", "source": "Code/Z.cpp"},
        {"bfme2_rva": 0x0E000000, "name": "?g@Y@@QAEXXZ", "source": "Code/Z.cpp"},
    ]
    summary = sweep.wb_summary(bodies)
    assert summary == {"agree": "name", "name": 1, "file": 0, "leads": 2}
    assert sweep.wb_marker(summary) == "  [WB 2 lead(s); agree: name 1, file 0]"
    assert sweep.wb_marker(sweep.wb_summary(bodies[2:])) == ""
    lead, agree = sweep.wb_lead_for({"bfme2_rva": 0x0F000200, "name": "?q@R@@QAEXXZ",
                                     "source": "reference/x/X.cpp"})
    assert lead["wb_name"] == "Other::name" and agree == "file"


def test_zh_packet_wb_section(leads):
    zh = _load("zh_sweep")
    group = [{"sym": "?candidate@Thing@@QAEXXZ", "source": "GeneralsMD/Code/T.cpp"},
             {"sym": "?other@Thing@@QAEXXZ", "source": "GeneralsMD/Code/U.cpp"}]
    text = "\n".join(zh.wb_lines(0x0F000100, group))
    assert "WB: Thing::candidate  (T.cpp, score 6, strings)" in text
    assert "agrees (name) with candidate ?candidate@Thing@@QAEXXZ" in text
    assert "?other@Thing" not in text
    assert "python3 tools/wb_show.py 0x0F000100 --gd" in text
    assert zh.wb_lines(0x0E000000, group) == []


def test_permute_prefers_a_named_lead(leads, tmp_path, monkeypatch):
    permute = _load("permute")
    attempts = tmp_path / "attempts"
    attempts.mkdir()
    for rva, symbol in (("0x0f000100", "?a@A@@QAEXXZ"), ("0x0e000000", "?b@B@@QAEXXZ")):
        (attempts / f"{rva}.cpp").write_text(f"// {symbol} score=0.95\n")
    log = tmp_path / "re_attempts.log"
    # Same size and score: only the WB lead separates them.
    log.write_text("?a@A@@QAEXXZ\t0x0f000100\t100\tpartial\tx\n"
                   "?b@B@@QAEXXZ\t0x0e000000\t100\tpartial\tx\n")
    monkeypatch.setattr(permute, "ATTEMPTS", attempts)
    monkeypatch.setattr(permute, "LOG", log)
    assert [rva for _, _, rva, _ in permute.queue(0.9)] == ["0x0f000100", "0x0e000000"]
    assert permute.wb_note("0x0f000100").startswith("WB: Thing::candidate")
    assert permute.wb_note("0x0e000000") == ""
