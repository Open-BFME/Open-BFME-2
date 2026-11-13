"""StandInElementFamily read as a struct (W5, tools/retail_identity.py OPAQUE_REF_DEQUE_DESTROY and
OPAQUE_REF_DEQUE_DTOR): stand_in_swap keeps the class-key U and the struct back-references, the entries are what was
reviewed, and rename.py holds a struct reading to the class contract (stand_in_element_problem)."""
import json
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
import retail_identity as R  # noqa: E402

A, B = R.OPAQUE_REF_DEQUE_DESTROY, R.OPAQUE_REF_DEQUE_DTOR
C = R.Fact


def test_the_entries_are_what_was_reviewed():
    for fam in (A, B):
        assert fam in R.FAMILIES and isinstance(fam, R.StandInElementFamily)
        assert (fam.new, fam.new_key, fam.stride) == ("OpaqueRefElement4", "U", 4)
        assert all(R.family_of(at, fam.respell(old)) is fam for at, (old, _f) in fam.rows.items())
        assert not fam.pins and not fam.duplicates
    assert (A.old, A.copy, set(A.rows), set(A.members), set(A.retired)) == (
        "Rva00055880Element", 0x00055880, {0x00055880}, {0x00054FD9}, {0x00054FD9})
    assert (B.old, B.copy, set(B.rows), set(B.members), set(B.retired)) == (
        "Rva00056DEBElement", 0x000579DE, {0x00056DEB, 0x000579DE}, {0x00055880}, {0x00055880})
    # the second family's member is the first's respelled row
    assert B.members[0x00055880] == A.respell(A.rows[0x00055880][0])
    assert B.respell(B.rows[0x000579DE][0]) == ("??1?$deque@UOpaqueRefElement4@@V?$allocator@UOpaqueRefElement4@@@"
                                               "_STL@@@_STL@@QAE@XZ")


def test_the_real_image_states_them_all():
    if not R.build.EXE.exists():
        pytest.skip("no retail image here")
    for fam in (A, B):
        assert R.facts_problems(fam.facts()) == []


@pytest.mark.parametrize("name, key, want", [
    ("?f@@YAXPAUOld@@@Z", "U", "?f@@YAXPAUNew@@@Z"),
    ("?f@@YAXPAUOld@@@Z", "V", "?f@@YAXPAVNew@@@Z"),
    ("??4Old@@QAEAAU0@ABU0@@Z", "U", "??4New@@QAEAAU0@ABU0@@Z"),     # a struct's back-references stay struct
    ("??4Old@@QAEAAU0@ABU0@@Z", "V", "??4New@@QAEAAV0@ABV0@@Z"),     # P134's class reading, unchanged
])
def test_the_swap_follows_the_class_key(name, key, want):
    assert R.stand_in_swap(name, "Old", "New", key) == want


def test_the_default_key_is_the_class_one():
    assert R.stand_in_swap("?f@@YAXPAUOld@@@Z", "Old", "New") == "?f@@YAXPAVNew@@@Z"
    assert R.SCORED_KILL_TRACKER_VECTOR.new_key == "V"


def test_no_other_key():
    with pytest.raises(ValueError, match="no class-key"):
        R.stand_in_swap("?f@@YAXPAUOld@@@Z", "Old", "New", "T")


def kwargs(fam):
    return dict(old=fam.old, new=fam.new, new_key=fam.new_key, copy=fam.copy, stride=fam.stride,
                spellings=dict(fam.spellings), members=dict(fam.members), bindings=tuple(fam.bindings),
                rows=dict(fam.rows), pins=dict(fam.pins), duplicates=dict(fam.duplicates), retired=dict(fam.retired))


def test_the_real_kwargs_build():
    for fam in (A, B):
        R.StandInElementFamily(**kwargs(fam))


OLD_A = A.rows[0x00055880][0]


@pytest.mark.parametrize("label, change, message", [
    ("the entry read as a class", lambda k: k.update(new_key="V"), "stand-in swap alone"),
    ("a spelling with the class key", lambda k: k["spellings"].update(
        {OLD_A: R.stand_in_swap(OLD_A, A.old, A.new, "V")}), "stand-in swap alone"),
    ("another key", lambda k: k.update(new_key="T"), "no class-key"),
    ("a row reaching no member", lambda k: k["rows"].update({0x00055880: (OLD_A, (C("calls", 0x000558A1, 0x1000),))}),
     "reaches no member|which is not"),
])
def test_the_constructor_refuses(label, change, message):
    k = kwargs(A)
    change(k)
    with pytest.raises(ValueError, match=message):
        R.StandInElementFamily(**k)


# ---------------------------------------------------------------- rename.py's ledger tie for a struct reading

HEADER = "Code/Lib/OpaqueRefElement4.h"


class Ctx:
    """The parts of rename.Context stand_in_element_problem reads."""

    def __init__(self, contract):
        self.files = {HEADER: b"typedef char X[sizeof(OpaqueRefElement4)==4?1:-1];\n"}
        if contract is not None:
            self.files["reverse/class_contracts/OpaqueRefElement4.json"] = json.dumps(contract).encode()

    def dicts(self, rel):
        assert rel == rename.CANONICAL_CLASSES
        return [{"class": "OpaqueRefElement4", "header": HEADER}]

    def read(self, rel):
        return self.files.get(rel)


def rows():
    out = [dict(name=name, target_rva=f"0x{at:08X}", target_size="64", status="matched", source="Code/Lib/X.cpp")
           for at, name in A.members.items()]
    out += [dict(name=old, target_rva=f"0x{at:08X}", target_size="64", status="matched", source="Code/Lib/X.cpp")
            for at, (old, _f) in A.rows.items()]
    return out


def test_a_struct_reading_matching_its_contract_passes_the_key_check():
    assert rename.stand_in_element_problem(Ctx({"key": "struct"}), rows(), A) is None


@pytest.mark.parametrize("contract, says", [({"key": "class"}, "says class"), ({}, "says nothing"),
                                            (None, "says nothing")])
def test_a_struct_reading_against_its_contract_refuses(contract, says):
    assert says in rename.stand_in_element_problem(Ctx(contract), rows(), A)
