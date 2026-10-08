"""next_work.py --wb: the WorldBuilder-lead tier, and the WB boost elsewhere."""
import json
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import next_work  # noqa: E402
import wb_context  # noqa: E402

# Addresses far past game.dat's .text, so no real re_attempts verdict or stash
# can sit on them.
LEADS = (
    "target_rva,current_name,current_kind,wb_name,wb_file,score,evidence\n"
    # band 0, file B, class Zed
    "0x0F000300,Rva0F000300::rva0F000300,PLACEHOLDER,Zed::go,"
    "C:\\Projects\\bfme2\\Code\\B.cpp,1.0,align\n"
    # band 0, file A, two classes
    "0x0F000200,Beta::rva0F000200,PARTIAL,Beta::run,C:\\Projects\\bfme2\\Code\\A.cpp,5.0,strings\n"
    "0x0F000100,,PIN_ONLY,Alpha::init,C:\\Projects\\bfme2\\Code\\A.cpp,2.0,callgraph\n"
    # band 0 with no file: last in its band
    "0x0F000050,Rva0F000050::x,PLACEHOLDER,Gamma::f,,3.0,vtable\n"
    # band 1: unrowed with a file, with and without a name
    "0x0F000400,,UNROWED,,C:\\Projects\\bfme2\\Code\\C.cpp,9.0,strings\n"
    "0x0F000500,,UNROWED,Delta::g,C:\\Projects\\bfme2\\Code\\A.cpp,1.0,callgraph\n"
    # never served: a rowed lead with no name, an unrowed lead with no file
    "0x0F000600,Rva0F000600::y,PLACEHOLDER,,C:\\Projects\\bfme2\\Code\\A.cpp,4.0,align\n"
    "0x0F000700,,UNROWED,Eps::h,,4.0,align\n"
    # retired live: a REAL matched row now holds it / a sourced row covers it
    "0x0F000800,Rva0F000800::z,PLACEHOLDER,Real::done,C:\\Projects\\bfme2\\Code\\A.cpp,4.0,align\n"
    "0x0F000910,,UNROWED,Inside::x,C:\\Projects\\bfme2\\Code\\A.cpp,4.0,align\n"
)
ROWS = [
    {"name": "?done@Real@@QAEXXZ", "target_rva": "0x0F000800", "target_size": "16",
     "source": "Code/A.cpp", "status": "matched", "notes": ""},
    {"name": "?big@Host@@QAEXXZ", "target_rva": "0x0F000900", "target_size": "64",
     "source": "Code/H.cpp", "status": "matched", "notes": ""},
    {"name": "?rva0F000200@Beta@@QAEXXZ", "target_rva": "0x0F000200", "target_size": "48",
     "source": "Code/A.cpp", "status": "matched", "notes": ""},
]


@pytest.fixture
def leads(tmp_path, monkeypatch):
    path = tmp_path / "leads.csv"
    path.write_text(LEADS)
    wb_context.clear_cache()
    parsed = wb_context.leads(path=path)
    monkeypatch.setattr(wb_context, "leads",
                        lambda path=None, ledger=None, live=True: parsed)
    yield parsed
    wb_context.clear_cache()


def served(leads):
    ranges = [(0x0F000900, 0x0F000940)]
    real = next_work.wb_real_rvas(ROWS)
    return next_work.wb_candidates(ranges, real, {0x0F000200: 48, 0x0F000400: 300})


def test_real_rows_are_recognised():
    assert next_work.wb_real_rvas(ROWS) == {0x0F000800, 0x0F000900}, \
        "Beta::rva0F000200 is an invented method name, so its row is not REAL"


def test_bands_and_grouping(leads):
    out = served(leads)
    order = [(c["band"], c["source"], c["function"]) for c in out]
    assert order == [
        (0, "Code/A.cpp", "Alpha::init"),
        (0, "Code/A.cpp", "Beta::run"),
        (0, "Code/B.cpp", "Zed::go"),
        (0, next_work.WB_NO_FILE, "Gamma::f"),
        (1, "Code/A.cpp", "Delta::g"),
        (1, "Code/C.cpp", "sub_0F000400"),
    ]
    by_rva = {c["target_rva"]: c for c in out}
    assert by_rva["0x0F000200"]["size"] == 48
    assert by_rva["0x0F000200"]["current_name"] == "Beta::rva0F000200"
    assert by_rva["0x0F000200"]["command"] == "python3 tools/wb_show.py 0x0F000200 --gd"


def test_band_serves_one_band_at_a_time(leads):
    first, aside = next_work.wb_band(served(leads))
    assert {c["band"] for c in first} == {0} and len(first) == 4 and aside == 2
    second, aside = next_work.wb_band([c for c in served(leads) if c["band"] == 1])
    assert len(second) == 2 and aside == 0
    assert next_work.wb_band([]) == ([], 0)


def test_high_score_lead_boosts_selection_weight(leads):
    plain = next_work.candidate_weight({"target_rva": "0x0F000100", "size": 200})
    boosted = next_work.candidate_weight({"target_rva": "0x0F000200", "size": 200})
    unled = next_work.candidate_weight({"target_rva": "0x0E000000", "size": 200})
    assert plain == unled, "a low-score lead is not boosted"
    assert boosted == round(unled * wb_context.BOOST)


def test_every_printed_candidate_gets_its_wb_line(leads, capsys):
    next_work._print_stash({"target_rva": "0x0F000200"})
    out = capsys.readouterr().out
    assert "WB: Beta::run  (A.cpp, score 5, strings)" in out
    assert "wb_show: python3 tools/wb_show.py 0x0F000200 --gd" in out
    assert "start:" not in out, "one `start:` per candidate is the existing contract"
    next_work._print_stash({"candidate_rva": "0x0E000000"})
    assert capsys.readouterr().out == ""


def _main(monkeypatch, argv, claim=None):
    monkeypatch.setattr(sys, "argv", ["next_work.py", *argv])
    monkeypatch.setattr(next_work, "check_ledger", lambda: "ledger healthy")
    monkeypatch.setattr(build, "load_claim_rows",
                        lambda *, counting_dumps, matched_only: list(ROWS))
    monkeypatch.setattr(next_work.claims, "busy_rvas", lambda: {0x0F000300})
    monkeypatch.setattr(next_work, "_ghidra_sizes", lambda: {})

    def unrelated(*args, **kwargs):
        raise AssertionError("the wb tier loaded an unrelated report")

    for name in ["drift_quick_wins", "structural_candidates", "ghidra_absent_candidates",
                 "reloc_named_candidates", "anchored_candidates", "packet_candidates"]:
        monkeypatch.setattr(next_work, name, unrelated)
    if claim:
        monkeypatch.setattr(next_work.claims, "claim", claim)
    next_work.main()


def test_wb_tier_json_selection(leads, monkeypatch, capsys):
    _main(monkeypatch, ["--wb", "--json"])
    out = json.loads(capsys.readouterr().out)
    assert out["tier"] == "WorldBuilder lead"
    selection = out["selection"]
    assert selection["band"] == 0
    assert selection["target_rva"] != "0x0F000300", "a live claim is never served"
    assert selection["wb"]["show"].startswith("python3 tools/wb_show.py ")
    assert out["selection_meta"]["pool"] == 3
    assert out["selection_meta"]["wb_set_aside"] == 2


def test_wb_tier_claims_its_draw(leads, monkeypatch, capsys):
    calls = []

    def claim(rvas, note=""):
        calls.append((list(rvas), note))
        return list(rvas), []

    _main(monkeypatch, ["--tier", "wb", "--claim"], claim=claim)
    out = capsys.readouterr().out
    assert len(calls) == 1 and calls[0][1] == "next_work WorldBuilder lead"
    rva = calls[0][0][0]
    assert f"claim: 0x{rva:08X} held on origin" in out
    assert "== selected work: WorldBuilder lead (drawn from 3) ==" in out
    assert f"start: python3 tools/wb_show.py 0x{rva:08X} --gd" in out
    assert out.count("       start:") == 1


def test_wb_tier_ranked_view(leads, monkeypatch, capsys):
    _main(monkeypatch, ["--wb", "--ranked", "--limit", "5"])
    out = capsys.readouterr().out
    assert "== WB band 0: rowed, needs its name (3 bodies in 2 WB file(s)) ==" in out
    assert "== WB band 1: unrowed, WB names its file (2 bodies in 2 WB file(s)) ==" in out
    assert out.index("-- Code/A.cpp") < out.index("-- (WB file unknown)")
    assert "Zed::go" not in out, "claimed by a peer"
    assert "Real::done" not in out and "Inside::x" not in out
