"""name_lane's route for a class registered in reverse/canonical_classes.csv.

A registered placeholder class has a canonical header and private views in other
units, so no unit alone decides its name. `name_lane.py next --registered CLASS`
serves its class key and its placeholder member keys from the canonical header (and
those keys only); a private view never serves them; name_evidence may grade a
registered placeholder but never a readable registered class. The miniature tree here
is also the fixture tools/tests/test_rename_canonical.py renames."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

OLD, NEW = "Rva00401000Base", "FXNugget"
HEADER = "Code/Game/Rva00401000Base.h"
BASIS = "kind,old,new,basis,evidence,source,rva\n"
REGISTRY = "class,header,notes\n"
OLD_KEY = f"{OLD},{HEADER},contract class_contracts/{OLD}.json\n"
QUEUE_HEAD = "class\tsource\tretail_rvas\theader\tfailure\tretry_budget\tacceptance\n"


def queue_row(cls, source, rvas):
    return f"{cls}\t{source}\t{rvas}\t{HEADER}\tfield renames: m_nuggetType\t3\tpython3 tools/header_adopt_lane.py\n"


def run(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, check=True)


def write(root, rel, text):
    path = root / rel
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode("latin-1"))


# ---------------------------------------------------------------- a registered class on a miniature tree
#
# Rva00401000Base is registered with a canonical header, a contract and a header_queue.tsv
# row; BaseCtor.cpp and BaseSlots.cpp adopt the header, SoundFXNugget.cpp keeps a private
# view that already spells the contract's m_nuggetType at +4.

CTOR = f"??0{OLD}@@QAE@XZ"
SLOT = f"?doFX@{OLD}@@UBEXXZ"
VFTABLE = f"??_7{OLD}@@6B@"
SOUND = "Code/Game/SoundFXNugget.cpp"
CONTRACT = f"reverse/class_contracts/{OLD}.json"
TREE = {
    "reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n"
                             f"{CTOR},,0x00401000,32,Code/Game/BaseCtor.cpp,matched,base ctor installs {VFTABLE}\n"
                             f"{SLOT},,0x00401040,16,Code/Game/BaseSlots.cpp,matched,slot 1\n"
                             f"??0SoundFXNugget@@QAE@XZ,,0x00401100,24,{SOUND},matched,calls {CTOR}\n",
    "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n"
                             f"{VFTABLE},0x00A01000,rva,8,.rdata,Code/Game/BaseCtor.cpp,matched,vtable,m\n",
    "reverse/symbols.csv": "name,address,notes\n",
    "reverse/deleted_rows.csv": "name,target_rva,reason\n",
    "reverse/exports.csv": "name,rva\n",
    "reverse/name_basis.csv": BASIS,
    "reverse/flag_overrides.csv": "source,flags,rows,default_lost,reason\n",
    "reverse/canonical_classes.csv": REGISTRY + OLD_KEY + "Coord3D,Code/Game/Coord3D.h,readable\n",
    CONTRACT: '{\n "class": "%s",\n "fields": [\n  {"kind": "VPTR", "name": "__vfptr", "offset": 0, "size": 4, '
              '"type": "void*"},\n'
              '  {"kind": "i4", "name": "m_nuggetType", "name_by": "majority", "offset": 4, "type": "int", "views": 2, '
              '"size": 4},\n'
              '  {"kind": "i4", "name": "m_08", "name_by": "majority", "offset": 8, "type": "int", "views": 3, '
              '"size": 4}\n ],\n'
              ' "size": 12,\n "vslots": {"1": "%s"}\n}\n' % (OLD, SLOT),
    "reverse/header_queue.tsv": QUEUE_HEAD + queue_row(OLD, SOUND, "0x00401100"),
    HEADER: f"#pragma once\n// {OLD}: constructor 0x00401000 installs {VFTABLE}.\n"
            f"class {OLD}\n{{\npublic:\n    {OLD}();\n    virtual void doFX() const;\n    int m_04;\n    int m_08;\n}};\n"
            "struct Rva00409000Local { int m_0C; };\n",
    "Code/Game/Coord3D.h": "#pragma once\nstruct Coord3D { float x, y, z; };\n",
    "Code/Game/BaseCtor.cpp": f'// cl: /O2\n#include "{OLD}.h"\n{OLD}::{OLD}() {{ m_04 = 0; m_08 = 2; }}\n',
    "Code/Game/BaseSlots.cpp": f'// cl: /O2\n#include "{OLD}.h"\nvoid {OLD}::doFX() const {{ (void)m_04; }}\n',
    SOUND: f"// cl: /O2\nclass {OLD}\n{{\npublic:\n    {OLD}();\n    virtual void doFX() const;\n"
           f"    int m_nuggetType;\n    int m_08;\n}};\n"
           f"class SoundFXNugget : public {OLD}\n{{\npublic:\n    SoundFXNugget();\n    int m_name;\n}};\n"
           f"SoundFXNugget::SoundFXNugget() {{ m_nuggetType = 3; m_name = 0; }}\n",
}


@pytest.fixture
def registered(tmp_path, monkeypatch):
    for rel, text in TREE.items():
        write(tmp_path, rel, text)
    run(tmp_path, "init", "-q")
    run(tmp_path, "config", "core.autocrlf", "false")
    run(tmp_path, "add", "-A")
    run(tmp_path, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "init")
    monkeypatch.setenv("BFME_CLAIM_OWNER", "seat-registered")
    monkeypatch.setenv("BFME_CLAIMS", "off")
    return tmp_path


def lane_of(root):
    import name_lane
    import rename
    return name_lane.Lane(root, rename.Context(root, object_scan=False))


def test_the_canonical_header_serves_its_registered_class_and_members(registered):
    lane = lane_of(registered)
    assert lane.registered_placeholders() == {HEADER: {OLD}}       # Coord3D is readable
    assert lane.servable(HEADER) and not lane.servable("Code/Game/Coord3D.h")
    items = [i[:3] for i in lane.owned(HEADER)]
    assert items == [("class", "", OLD), ("member", OLD, "m_04"), ("member", OLD, "m_08")]
    # Rva00409000Local is the header's own, unregistered class: not this route's
    assert all("Rva00409000Local" not in i for i in items)


def test_a_private_view_never_decides_the_registered_class(registered):
    items = [i[:3] for i in lane_of(registered).owned(SOUND)]
    assert ("class", "", OLD) not in items and not any(i[0] == "member" and i[1] == OLD for i in items)


def test_next_registered_serves_the_header_once(registered):
    import name_lane
    from types import SimpleNamespace
    args = SimpleNamespace(session="reg", model="claude-opus-5-5", count=1, file=None, list_only=False,
                           registered=OLD)
    assert name_lane.cmd_next(lane_of(registered), args) == 0
    import json
    record = json.loads((registered / "build/name_lane/sessions/reg.json").read_text())
    assert list(record["files"]) == [HEADER]
    assert [i[:3] for i in record["files"][HEADER]["items"]] == [
        ["class", "", OLD], ["member", OLD, "m_04"], ["member", OLD, "m_08"]]
    brief = (registered / "build/name_lane/briefs/reg.txt").read_text()
    assert f"## Registered class {OLD}" in brief and "+0x4 m_nuggetType int (majority, 2 view(s))" in brief


def test_next_registered_serves_one_member_key_alone(registered):
    """A member is voted and landed before (and without) any rename of its class."""
    import json
    import name_lane
    from types import SimpleNamespace
    key = f"{HEADER}|member|{OLD}|m_04"
    args = SimpleNamespace(session="mem", model="claude-opus-5-5", count=1, file=None, list_only=False,
                           registered=OLD, key=[key])
    assert name_lane.cmd_next(lane_of(registered), args) == 0
    record = json.loads((registered / "build/name_lane/sessions/mem.json").read_text())
    assert record["files"][HEADER]["items"] == [["member", OLD, "m_04", None]]


@pytest.mark.parametrize("cls", ["Coord3D", "Rva00409000Local", "Rva0040FFFFMissing"])
def test_next_registered_refuses_anything_but_a_registered_placeholder(registered, cls):
    import name_lane
    from types import SimpleNamespace
    args = SimpleNamespace(session="reg", model="m", count=1, file=None, list_only=False, registered=cls)
    with pytest.raises(SystemExit):
        name_lane.cmd_next(lane_of(registered), args)


def test_name_evidence_grades_a_registered_placeholder_but_never_a_readable_one(registered):
    import name_evidence
    tree = name_evidence.Tree(registered)
    assert tree.class_refusal(OLD) is None
    assert tree.class_refusal("Coord3D") == "protected class"


def spell_new_as_a_type(root, pin=None):
    """Another unit forward-declares NEW and takes NEW *; optionally a pin scoped by NEW."""
    write(root, "Code/Game/FXList.cpp", f"// cl: /O2\nclass {NEW};\nvoid addNugget({NEW} *n) {{ (void)n; }}\n")
    if pin:
        with open(root / "reverse/symbols.csv", "ab") as handle:
            handle.write(f"{pin},0x00403000,pin\n".encode("utf-8"))
    run(root, "add", "-A")


def test_a_name_spelled_only_as_a_type_is_voted_and_landed_as_a_merge(registered):
    import name_lane
    spell_new_as_a_type(registered)
    lane = lane_of(registered)
    assert lane.merges(HEADER, OLD, NEW)
    assert name_lane.rename_kwargs("class", "", OLD, NEW, None, HEADER, lane) == {"name": OLD, "new": NEW,
                                                                                    "merge": True}
    assert not lane.merges(SOUND, OLD, NEW)                       # only from the canonical header's key
    assert not lane.merges(HEADER, OLD, "Coord3D")               # Coord3D is a defined, registered class


@pytest.mark.parametrize("pin", [f"?run@{NEW}@@QAEXXZ", f"??_7{NEW}@@6B@"])
def test_a_name_that_owns_a_row_is_no_merge(registered, pin):
    import name_lane
    spell_new_as_a_type(registered, pin)
    lane = lane_of(registered)
    assert not lane.merges(HEADER, OLD, NEW)
    assert name_lane.rename_kwargs("class", "", OLD, NEW, None, HEADER, lane) == {"name": OLD, "new": NEW}


def test_a_merge_answer_passes_validation_and_others_still_refuse(registered, monkeypatch, tmp_path):
    import json
    import name_lane
    from types import SimpleNamespace
    spell_new_as_a_type(registered)
    monkeypatch.setenv("BFME_CLAIM_OWNER", "seat-merge")
    key = f"{HEADER}|class||{OLD}"
    args = SimpleNamespace(session="merge", model="claude-opus-5-5", count=1, file=None, list_only=False,
                           registered=OLD, key=[key])
    assert name_lane.cmd_next(lane_of(registered), args) == 0
    for answer, ok in ((NEW, True), ("Coord3D", False)):
        sheet = tmp_path / f"answer-{answer}.json"
        sheet.write_bytes(json.dumps({HEADER: {OLD: answer}}).encode("utf-8"))
        validate = SimpleNamespace(answer=str(sheet), session="merge", model="claude-opus-5-5")
        if ok:
            assert name_lane.cmd_validate(lane_of(registered), validate) == 0
        else:
            assert name_lane.cmd_validate(lane_of(registered), validate) != 0
