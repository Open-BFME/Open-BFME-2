"""tools/wb_context.py: the shared WorldBuilder lead loader the queues read."""
import os
import sys
import time
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import wb_context  # noqa: E402

LEADS = (
    "target_rva,current_name,current_kind,wb_name,wb_file,score,evidence\n"
    "0x003CA4BE,,UNROWED,ScriptActions::executeAction,"
    "C:\\Projects\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\ScriptActions.cpp,"
    "16.0000,callgraph\n"
    "0x00257CB8,,UNROWED,,,25.5560,strings\n"
    "0x0011A040,Rva0011A040Target::rva0011A040,PIN_ONLY,,"
    "..\\Libraries\\Source\\WWVegas\\WWLib\\refcount.h,11.0000,callgraph\n"
    "0x00706A40,AptActionInterpreter::_createObject,PLACEHOLDER,"
    "AptActionInterpreter::_createObject,"
    "c:\\projects\\bfme2\\code\\libraries\\source\\Apt\\AptActionInterpreter.cpp,2.0,strings\n"
)
MEMBERS = (
    "class,member,offset,size,kind,occurrences,conflict,example_function,example_condition\n"
    "Object,m_pfPosAndGoal,0xac,dword,assert,5,,f@0x1,c\n"
    "Object,m_id,0x7c,dword,assert,1,,g@0x2,c\n"
    "?,m_x,0x10,dword,assert,1,n/a,h@0x3,c\n"
)


LEDGER_HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


@pytest.fixture
def files(tmp_path, monkeypatch):
    wb_context.clear_cache()
    leads, members = tmp_path / "leads.csv", tmp_path / "members.csv"
    leads.write_text(LEADS)
    members.write_text(MEMBERS)
    ledger = tmp_path / "functions.csv"
    ledger.write_text(LEDGER_HEADER)
    monkeypatch.setattr(wb_context, "FUNCTIONS_CSV", ledger)
    yield leads, members
    wb_context.clear_cache()


def _bump(path):
    later = time.time() + 5
    os.utime(path, (later, later))


def test_landed_leads_are_dropped_at_read_time(files):
    leads, _ = files
    ledger = wb_context.FUNCTIONS_CSV
    assert wb_context.lead(0x003CA4BE, path=leads) is not None
    ledger.write_text(
        LEDGER_HEADER
        # REAL name, matched, range covers the lead's address (not its start)
        + "?executeAction@ScriptActions@@QAEXPAVScriptAction@@@Z,,"
          "0x003CA400,512,Code/GameEngine/Source/GameLogic/ScriptEngine/"
          "ScriptActions.cpp,matched,\n"
        # still invented: a PLACEHOLDER row retires nothing
        + "?rva00706A40@Rva00706A40@@QAEXXZ,,0x00706A40,16,Code/X.cpp,matched,\n"
        # REAL but not matched: retires nothing
        + "?inc@RefCount@@QAEXXZ,,0x0011A040,8,Code/R.cpp,unmatched,\n")
    _bump(ledger)
    assert wb_context.lead(0x003CA4BE, path=leads) is None
    assert wb_context.landed(0x003CA4BE) == "ScriptActions::executeAction"
    assert 0x003CA4BE in wb_context.leads(path=leads, live=False), "snapshot unchanged"
    assert wb_context.lead(0x00706A40, path=leads) is not None
    assert wb_context.lead(0x0011A040, path=leads) is not None
    assert wb_context.landed(0x003CA400 + 512) is None, "range end is exclusive"
    # the queue grows back if the row is withdrawn
    ledger.write_text(LEDGER_HEADER)
    _bump(ledger)
    assert wb_context.lead(0x003CA4BE, path=leads) is not None


def test_refresh_marks_landed_leads_real(files):
    leads, _ = files
    ledger = wb_context.FUNCTIONS_CSV
    assert wb_context.refresh(path=leads) == 0
    assert leads.read_text() == LEADS, "nothing landed: file untouched"
    ledger.write_text(
        LEDGER_HEADER
        + "?_createObject@AptActionInterpreter@@SAXXZ,,0x00706A40,32,"
          "Code/Libraries/Source/Apt/AptActionInterpreter.cpp,matched,\n")
    _bump(ledger)
    assert wb_context.refresh(path=leads) == 1
    lines = leads.read_text().splitlines()
    before = LEADS.splitlines()
    assert lines[:-1] == before[:-1], "other rows kept byte for byte"
    assert lines[-1].startswith("0x00706A40,AptActionInterpreter::_createObject,REAL,")
    assert lines[-1].split(",", 3)[3] == before[-1].split(",", 3)[3]
    assert wb_context.lead(0x00706A40, path=leads) is None
    assert wb_context.refresh(path=leads) == 0, "idempotent"


def test_lead_fields_and_paths(files):
    leads, _ = files
    lead = wb_context.lead(0x003CA4BE, path=leads)
    assert lead["wb_name"] == "ScriptActions::executeAction"
    assert lead["wb_class"] == "ScriptActions"
    assert lead["wb_path"] == "Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp"
    assert lead["wb_base"] == "ScriptActions.cpp"
    assert lead["score"] == 16.0 and lead["evidence"] == "callgraph"
    assert lead["kind"] == "UNROWED"
    # string RVAs work the same as ints
    assert wb_context.lead("0x003ca4be", path=leads) is lead
    # relative and lower-case checkout prefixes normalise too
    assert wb_context.lead(0x0011A040, path=leads)["wb_path"] == \
        "Libraries/Source/WWVegas/WWLib/refcount.h"
    assert wb_context.lead(0x00706A40, path=leads)["wb_path"] == \
        "code/libraries/source/Apt/AptActionInterpreter.cpp"


def test_a_lead_naming_nothing_is_no_lead(files):
    leads, _ = files
    assert wb_context.lead(0x00257CB8, path=leads) is None
    assert wb_context.lead(0x1, path=leads) is None
    assert wb_context.lead("not-hex", path=leads) is None


def test_line_and_command(files):
    leads, _ = files
    lead = wb_context.lead(0x003CA4BE, path=leads)
    assert wb_context.line(lead) == \
        "WB: ScriptActions::executeAction  (ScriptActions.cpp, score 16, callgraph)"
    assert wb_context.line(wb_context.lead(0x0011A040, path=leads)).startswith(
        "WB: (unnamed)  (refcount.h, score 11,")
    assert wb_context.line(None) == ""
    assert wb_context.show_command(0x3CA4BE) == "python3 tools/wb_show.py 0x003CA4BE --gd"


def test_high_score_and_boost(files):
    leads, _ = files
    high = wb_context.lead(0x003CA4BE, path=leads)
    low = wb_context.lead(0x00706A40, path=leads)
    unnamed = wb_context.lead(0x0011A040, path=leads)
    assert wb_context.is_high(high) and wb_context.boost(high) == wb_context.BOOST
    assert not wb_context.is_high(low) and wb_context.boost(low) == 1.0
    assert not wb_context.is_high(unnamed), "a score without a name is not a named lead"
    assert wb_context.boost(None) == 1.0


def test_agreement(files):
    leads, _ = files
    lead = wb_context.lead(0x00706A40, path=leads)
    mangled = "?_createObject@AptActionInterpreter@@SAXXZ"
    assert wb_context.agreement(lead, name=mangled) == "name"
    assert wb_context.agreement(lead, name="AptActionInterpreter::_createObject") == "name"
    assert wb_context.agreement(lead, name="?other@AptActionInterpreter@@SAXXZ",
                                source="x/y/aptactioninterpreter.cpp") == "file"
    assert wb_context.agreement(lead, name="?other@X@@SAXXZ", source="Other.cpp") is None
    assert wb_context.agreement(None, name=mangled) is None


def test_members_sorted_by_offset(files):
    _, members = files
    rows = wb_context.members("Object", path=members)
    assert [r["member"] for r in rows] == ["m_id", "m_pfPosAndGoal"]
    assert wb_context.members("Nope", path=members) == []


def test_cache_reloads_when_the_file_changes(files):
    leads, _ = files
    assert wb_context.lead(0x00706A40, path=leads)["score"] == 2.0
    first = wb_context.leads(path=leads)
    assert wb_context.leads(path=leads) is first, "unchanged file is not re-parsed"
    leads.write_text(LEADS.replace("AptActionInterpreter.cpp,2.0,", "AptActionInterpreter.cpp,9.0,"))
    _bump(leads)
    assert wb_context.lead(0x00706A40, path=leads)["score"] == 9.0


def test_missing_file_is_empty(tmp_path):
    wb_context.clear_cache()
    assert wb_context.leads(path=tmp_path / "absent.csv") == {}
    assert wb_context.members("Object", path=tmp_path / "absent.csv") == []


def test_live_files_load():
    """The committed CSVs parse, and the documented example is in them."""
    wb_context.clear_cache()
    if not wb_context.LEADS_CSV.exists():
        pytest.skip("reverse/wb_name_leads.csv not present")
    assert len(wb_context.leads()) > 1000
    assert wb_context.lead(0x003CA4BE)["wb_name"] == "ScriptActions::executeAction"
