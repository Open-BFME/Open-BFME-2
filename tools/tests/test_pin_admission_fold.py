"""Pin admission onto an address that already carries a real name.

"One address, one identity" refuses a second real name on a body, because a
pin naming the wrong function still reproduces its caller's bytes. But
/OPT:ICF folds identical COMDATs, so vector<int>::push_back and
vector<A*>::push_back legitimately share one retail body, and a unit that
calls the second needs it pinned there. Admission takes that only with proof
(`fold-proof=<ledger source>` in the pin's notes), and the proof checks what
ICF itself decides a fold by, for the pinned name and every callee its proof
places:

- identity: the name has no body elsewhere. An address of its own -- any
  ledger row naming it (gen-alias twins and alias rows included), a pin, or a
  candidate in the byte gate's symbol map -- means retail did NOT fold it.
- bytes: the name's body compiled from that source, with any same-type callee
  instantiation proven at the address retail calls, is retail's whole body.
- relocations: the byte compare copies every DIR32 slot from retail, so each
  relocation must also be the one every matched owner body there carries:
  same offset, type and addend, the same external or TU-local symbol.

The two holes an adversarial review found in the first port are pinned here
(money_put's constructor onto money_get's; View::setAngle onto its unfolded
twin SegLineRendererClass::Set_Merge_Abort_Factor), next to genuine folds that
must still be admitted.
"""
import csv
import importlib
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))

from test_gate_exploits import RDATA, TEXT, Gate, coff  # noqa: E402

OWNER, HELPER = 0x2000, 0x4000
NEW_PB, NEW_OV = "?pb@?$V@PAUA@@@@QAEXXZ", "?ov@?$V@PAUA@@@@QAEXXZ"
OLD_PB, OLD_OV = "?pb@?$V@H@@QAEXXZ", "?ov@?$V@H@@QAEXXZ"
# push_back-shaped body calling its overflow helper at offset 7
PB = b"\x55\x8b\xec\x51\x52\x53\xe8\x00\x00\x00\x00\x5b\x5a\x59\x5d\xc3"
OV = b"\x55\x8b\xec\x33\xc0\x40\x40\x40\x8b\xe5\x5d\xc3"
PROOF = "fold-proof=Code/x.cpp"


@pytest.fixture
def fold(monkeypatch, tmp_path):
    gate = Gate(monkeypatch, tmp_path)
    admission = importlib.import_module("pin_admission")
    monkeypatch.setattr(admission, "build", gate.build)
    monkeypatch.setattr(admission, "image_layout",
                        lambda: (0x6000, [(0x1000, 0x5000, True), (0x5000, 0x6000, False)]))
    monkeypatch.setattr(gate.build, "gate_baselined", lambda check, row: False)
    gate.memory[OWNER] = PB[:7] + struct.pack("<i", HELPER - (OWNER + 11)) + PB[11:]
    gate.memory[HELPER] = OV
    gate.row(OLD_PB, OWNER, len(PB))   # vector<int> owns both bodies
    gate.row(OLD_OV, HELPER, len(OV))
    write_pins(gate, [])
    gate.admission = admission
    gate.monkeypatch = monkeypatch
    return gate


def write_pins(gate, pins):
    """The working-tree symbols.csv the byte gate's symbol map reads."""
    with open(gate.build.SYMBOLS, "w", newline="") as handle:
        writer = csv.writer(handle)
        writer.writerow(["name", "address", "notes"])
        writer.writerows(pins)


def write_object(gate, pb=PB, ov=OV, pb_relocs=((7, 5, 0x14),)):
    # The owners' own bodies are in the object too: every ledger row compiles
    # to it, and the proof compares relocations with the owner's.
    # Symbol indices: .text 0(+aux), NEW_PB 2, .text 3, NEW_OV 5, .text 6,
    # OLD_PB 8, .text 9, OLD_OV 11.
    gate.obj.write_bytes(coff(
        [(".text", TEXT, pb, list(pb_relocs)), (".text", TEXT, ov, []),
         (".text", TEXT, PB, [(7, 11, 0x14)]), (".text", TEXT, OV, [])],
        [(".text", 0, 1, 0, 3, 1), (NEW_PB, 0, 1, 0x20, 2, 0),
         (".text", 0, 2, 0, 3, 1), (NEW_OV, 0, 2, 0x20, 2, 0),
         (".text", 0, 3, 0, 3, 1), (OLD_PB, 0, 3, 0x20, 2, 0),
         (".text", 0, 4, 0, 3, 1), (OLD_OV, 0, 4, 0x20, 2, 0)]))


def judge(gate, notes, address=OWNER, name=NEW_PB):
    pin = {"name": name, "address": f"0x{address:08X}", "notes": notes}
    return gate.admission.judge([], [pin], gate.rows, gate.rows)


# --- the fork's cases: bytes, callees, extent, source, renames ----------------------

def test_proven_template_fold_is_admitted(fold):
    # vector<A*>::push_back onto vector<int>'s body, with its same-type
    # overflow helper proven at the address retail calls.
    write_object(fold)
    assert judge(fold, "vector<A*> push_back fold; " + PROOF) == []


def test_fold_without_proof_token_is_still_refused(fold):
    write_object(fold)
    problems = judge(fold, "vector<A*> push_back fold")
    assert problems and "already carries the real name" in problems[0]


def test_wrong_body_on_a_named_address_is_refused(fold):
    write_object(fold, pb=PB[:3] + b"\x50" + PB[4:])   # one instruction differs
    problems = judge(fold, PROOF)
    assert problems and "differs from retail" in problems[0]


def test_wrong_callee_in_the_chain_is_refused(fold):
    write_object(fold, ov=OV[:5] + b"\x48" + OV[6:])   # helper is a different function
    problems = judge(fold, PROOF)
    assert problems and "differs from retail" in problems[0]


def test_extent_must_be_the_owner_rows(fold):
    write_object(fold, pb=PB + b"\xc3")   # a prefix match is not the same body
    problems = judge(fold, PROOF)
    assert problems and "17 bytes" in problems[0]


def test_proof_source_must_be_a_matched_ledger_unit(fold):
    write_object(fold)
    problems = judge(fold, "fold-proof=Code/scratch.cpp")
    assert problems and "no matched ledger row" in problems[0]


def test_tiny_identical_body_is_not_enough(fold):
    fold.memory[0x3000] = b"\x33\xc0\xc3"
    fold.row("?Other@@YAXXZ", 0x3000, 3)
    fold.obj.write_bytes(coff([(".text", TEXT, b"\x33\xc0\xc3", [])],
                              [(".text", 0, 1, 0, 3, 1), ("?Callee@@YAXXZ", 0, 1, 0x20, 2, 0)]))
    problems = judge(fold, PROOF, address=0x3000, name="?Callee@@YAXXZ")
    assert problems and "too few" in problems[0]


def test_renaming_a_pin_is_not_a_second_identity(fold):
    # The old pin line goes away in the same change: one name on the address.
    old = {"name": "?Callee@@YAXPAX@Z", "address": "0x00003000", "notes": "x"}
    new = {"name": "?Callee@@YA_NPBD@Z", "address": "0x00003000", "notes": "x"}
    assert fold.admission.judge([old], [new], fold.rows, fold.rows) == []


def test_keeping_the_old_pin_beside_a_new_name_is_still_refused(fold):
    old = {"name": "?Callee@@YAXPAX@Z", "address": "0x00003000", "notes": "x"}
    new = {"name": "?Callee@@YA_NPBD@Z", "address": "0x00003000", "notes": "x"}
    problems = fold.admission.judge([old], [old, new], fold.rows, fold.rows)
    assert problems and "already carries the real name" in problems[0]


def test_renaming_a_pin_onto_a_rowed_address_is_still_refused(fold):
    # Removing a pin does not remove the ledger row's identity.
    old = {"name": "?Callee@@YAXPAX@Z", "address": f"0x{OWNER:08X}", "notes": "x"}
    new = {"name": "?Callee@@YA_NPBD@Z", "address": f"0x{OWNER:08X}", "notes": "x"}
    problems = fold.admission.judge([old], [new], fold.rows, fold.rows)
    assert problems and "already carries the real name" in problems[0]


def test_renaming_a_fold_pin_in_place_is_one_fold(fold):
    # A signature fix of a proven fold: the old line is retired by the same
    # change, so neither the one-identity rule nor the fold's own identity
    # check counts it as a second name or a second address.
    write_object(fold)
    old = {"name": "?pb@?$V@PAUB@@@@QAEXXZ", "address": f"0x{OWNER:08X}", "notes": PROOF}
    new = {"name": NEW_PB, "address": f"0x{OWNER:08X}", "notes": PROOF}
    assert fold.admission.judge([old], [new], fold.rows, fold.rows) == []


def test_callee_named_through_a_nonzero_addend_is_refused(fold):
    # The object calls ov+4, an interior target: retail calling HELPER proves
    # nothing about where ov itself starts, so the chain may not resolve there.
    write_object(fold, pb=PB[:7] + b"\x04\x00\x00\x00" + PB[11:])
    problems = judge(fold, PROOF)
    assert problems and "zero addend" in problems[0]


def test_unproven_pin_does_not_load_the_symbol_map(fold):
    # Only a pin that carries a proof pays for one; every other stacked pin is
    # refused as before without reading the ledger's symbol map.
    def boom():
        raise AssertionError("symbol map loaded for a pin with no fold-proof")
    fold.monkeypatch.setattr(fold.build, "load_symbol_map", boom)
    write_object(fold)
    problems = judge(fold, "vector<A*> push_back fold")
    assert problems and "already carries the real name" in problems[0]


# --- hole 2: retail must have ONE body for both names ------------------------------
#
# The port's addresses_of() skipped rows carrying gen-alias, which
# build.load_symbol_map keeps, so View::setAngle -- whose own (gen-alias) row is
# 0x0025EAFB -- was admitted onto SegLineRendererClass::Set_Merge_Abort_Factor at
# 0x0015DFE0. Both retail bodies are f30f10442404f30f114128c20400; retail did not
# fold them, and the extra candidate would let a Set_Merge_Abort_Factor caller be
# written as View::setAngle.

SET_ANGLE = "?setAngle@View@@UAEXM@Z"
MERGE_ABORT = "?Set_Merge_Abort_Factor@SegLineRendererClass@@QAEXM@Z"
SETTER = bytes.fromhex("f30f10442404f30f114128c20400")  # movss [ecx+28h] <- arg; ret 4
SEGLINE, VIEW = 0x3000, 0x3800   # retail 0x0015DFE0 and 0x0025EAFB


def twin_fixture(fold, notes):
    fold.memory[SEGLINE] = SETTER
    fold.memory[VIEW] = SETTER
    fold.row(MERGE_ABORT, SEGLINE, len(SETTER))
    fold.row(SET_ANGLE, VIEW, len(SETTER), notes)
    fold.obj.write_bytes(coff(
        [(".text", TEXT, SETTER, []), (".text", TEXT, SETTER, [])],
        [(".text", 0, 1, 0, 3, 1), (SET_ANGLE, 0, 1, 0x20, 2, 0),
         (".text", 0, 2, 0, 3, 1), (MERGE_ABORT, 0, 2, 0x20, 2, 0)]))
    return judge(fold, PROOF, address=SEGLINE, name=SET_ANGLE)


@pytest.mark.parametrize("notes", [
    f"gen-alias;object-symbol={SET_ANGLE};C++ alias",   # the reported row, verbatim
    "gen-alias",
    "",
    "object-symbol=?setAngle@OtherView@@UAEXM@Z",       # an alias row: still a claim there
], ids=["gen-alias-object-symbol", "gen-alias", "plain", "alias"])
def test_a_row_of_its_own_elsewhere_is_not_a_fold(fold, notes):
    problems = twin_fixture(fold, notes)
    assert problems and f"{SET_ANGLE} already has its own address 0x{VIEW:08X}" in problems[0]


def test_a_baselined_alias_row_is_an_address_of_its_own(fold):
    # A reviewed alias row resolves callers in load_symbol_map.
    fold.monkeypatch.setattr(fold.build, "gate_baselined", lambda check, row: check == "alias-row")
    problems = twin_fixture(fold, "object-symbol=?setAngle@OtherView@@UAEXM@Z")
    assert problems and f"already has its own address 0x{VIEW:08X}" in problems[0]


def test_the_unfolded_twin_without_a_row_elsewhere_is_admitted(fold):
    # Control: the same bytes with no address of setAngle's own anywhere are
    # what a genuine fold looks like to this proof.
    fold.memory[SEGLINE] = SETTER
    fold.row(MERGE_ABORT, SEGLINE, len(SETTER))
    fold.obj.write_bytes(coff(
        [(".text", TEXT, SETTER, []), (".text", TEXT, SETTER, [])],
        [(".text", 0, 1, 0, 3, 1), (SET_ANGLE, 0, 1, 0x20, 2, 0),
         (".text", 0, 2, 0, 3, 1), (MERGE_ABORT, 0, 2, 0x20, 2, 0)]))
    assert judge(fold, PROOF, address=SEGLINE, name=SET_ANGLE) == []


def test_a_symbol_map_candidate_is_an_address_of_its_own(fold):
    # A candidate the byte gate's map holds (a working-tree pin) counts even
    # when the proposed pin set does not repeat it.
    fold.memory[SEGLINE] = SETTER
    fold.row(MERGE_ABORT, SEGLINE, len(SETTER))
    fold.obj.write_bytes(coff(
        [(".text", TEXT, SETTER, []), (".text", TEXT, SETTER, [])],
        [(".text", 0, 1, 0, 3, 1), (SET_ANGLE, 0, 1, 0x20, 2, 0),
         (".text", 0, 2, 0, 3, 1), (MERGE_ABORT, 0, 2, 0x20, 2, 0)]))
    write_pins(fold, [(SET_ANGLE, f"0x{VIEW:08X}", "callee")])
    problems = judge(fold, PROOF, address=SEGLINE, name=SET_ANGLE)
    assert problems and f"already has its own address 0x{VIEW:08X}" in problems[0]


def test_name_with_its_own_body_elsewhere_is_refused(fold):
    write_object(fold)
    fold.memory[0x4800] = fold.memory[OWNER]
    fold.row(NEW_PB, 0x4800, len(PB))
    problems = judge(fold, PROOF)
    assert problems and "already has its own address 0x00004800" in problems[0]


def test_name_with_its_own_pin_elsewhere_is_refused(fold):
    write_object(fold)
    pin = {"name": NEW_PB, "address": "0x00004800", "notes": "x"}
    fold_pin = {"name": NEW_PB, "address": f"0x{OWNER:08X}", "notes": PROOF}
    problems = fold.admission.judge([pin], [pin, fold_pin], fold.rows, fold.rows)
    assert problems and "already has its own address 0x00004800" in problems[0]


def test_a_thunk_into_the_folded_body_is_the_same_body(fold):
    # At commit time the working tree already holds the fold pin, and the map
    # gives it the address's incremental-link thunk too: one body, not two.
    write_object(fold)
    thunk = 0x1100
    fold.memory[thunk] = b"\xe9" + struct.pack("<i", OWNER - (thunk + 5))
    fold.monkeypatch.setattr(fold.build, "build_call_thunks", lambda: {OWNER: [thunk]})
    write_pins(fold, [(NEW_PB, f"0x{OWNER:08X}", PROOF)])
    assert judge(fold, PROOF) == []


def test_a_thunk_into_another_body_is_an_address_of_its_own(fold):
    write_object(fold)
    thunk = 0x1100
    fold.memory[thunk] = b"\xe9" + struct.pack("<i", 0x4800 - (thunk + 5))
    write_pins(fold, [(NEW_PB, f"0x{thunk:08X}", "pinned thunk")])
    problems = judge(fold, PROOF)
    assert problems and "already has its own address 0x00001100" in problems[0]


# --- hole 1: relocations, not just bytes --------------------------------------------
#
# compile_function copies every DIR32 slot from retail, so bodies that differ only
# in a vtable, global, string or float operand compared equal: money_put's
# constructor was "proven" at money_get's 0x000071C0, though the two differ in
# the vtable DIR32 at +0x17.

MONEY_GET = "??0?$money_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@QAE@I@Z"
MONEY_PUT = "??0?$money_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@QAE@I@Z"
GET_VTABLE = "??_7?$money_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@6B@"
PUT_VTABLE = "??_7?$money_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@6B@"
# mov eax,ecx; mov ecx,[esp+4]; test ecx,ecx; mov [eax+4],1; sete cl; mov [eax+8],cl;
# mov [eax],offset vtable; ret 4 -- the retail bodies, vtable operand at +0x17
MONEY_CTOR = bytes.fromhex("8bc18b4c240485c9c74004010000000f94c1884808c70000000000c20400")
GET_AT, PUT_AT = 0x31C0, 0x31E0   # retail 0x000071C0 and 0x000071E0


def money_fixture(fold, own_row):
    fold.memory[GET_AT] = MONEY_CTOR[:0x17] + struct.pack("<I", 0x00BBB9D8) + MONEY_CTOR[0x1B:]
    fold.memory[PUT_AT] = MONEY_CTOR[:0x17] + struct.pack("<I", 0x00BBB9E8) + MONEY_CTOR[0x1B:]
    fold.row(MONEY_GET, GET_AT, len(MONEY_CTOR))
    if own_row:
        fold.row(MONEY_PUT, PUT_AT, len(MONEY_CTOR))
    fold.obj.write_bytes(coff(
        [(".text", TEXT, MONEY_CTOR, [(0x17, 6, 0x06)]),
         (".text", TEXT, MONEY_CTOR, [(0x17, 7, 0x06)])],
        [(".text", 0, 1, 0, 3, 1), (MONEY_GET, 0, 1, 0x20, 2, 0),
         (".text", 0, 2, 0, 3, 1), (MONEY_PUT, 0, 2, 0x20, 2, 0),
         (GET_VTABLE, 0, 0, 0, 2, 0), (PUT_VTABLE, 0, 0, 0, 2, 0)]))
    return judge(fold, PROOF, address=GET_AT, name=MONEY_PUT)


def test_money_put_constructor_with_its_own_row_is_not_folded(fold):
    problems = money_fixture(fold, own_row=True)
    assert problems and f"already has its own address 0x{PUT_AT:08X}" in problems[0]


def test_money_put_constructor_is_not_folded_onto_money_gets(fold):
    # With money_put's own row set aside, the vtable store alone refuses it.
    problems = money_fixture(fold, own_row=False)
    assert problems and (f"+0x17 binds {PUT_VTABLE} where {MONEY_GET} binds {GET_VTABLE}"
                         in problems[0])


CTOR = 0x3000
VTABLE_A, VTABLE_B = "??_7A@@6B@", "??_7B@@6B@"
# mov eax, ecx; mov dword ptr [eax], offset vtable; xor edx, edx; mov [eax+4], edx; ret 4
CTOR_BODY = b"\x8b\xc1\xc7\x00\x00\x00\x00\x00\x33\xd2\x89\x50\x04\xc2\x04\x00"


def ctor_fixture(fold, mine, theirs, my_addend=0, my_reloc=0x06, retail_vtable=0x405000):
    """Owner ??0A stores `theirs`; the pinned ??0B stores `mine` (None: no
    relocation, the address is a constant). Retail holds retail_vtable."""
    retail = bytearray(CTOR_BODY)
    retail[4:8] = struct.pack("<I", retail_vtable)
    fold.memory[CTOR] = bytes(retail)
    fold.row("??0A@@QAE@I@Z", CTOR, len(CTOR_BODY))
    pinned = bytearray(CTOR_BODY)
    pinned[4:8] = struct.pack("<I", retail_vtable if mine is None else my_addend)
    my_relocs = [] if mine is None else [(4, 6 if mine == theirs else 7, my_reloc)]
    fold.obj.write_bytes(coff(
        [(".text", TEXT, bytes(pinned), my_relocs),
         (".text", TEXT, CTOR_BODY, [(4, 6, 0x06)])],
        [(".text", 0, 1, 0, 3, 1), ("??0B@@QAE@I@Z", 0, 1, 0x20, 2, 0),
         (".text", 0, 2, 0, 3, 1), ("??0A@@QAE@I@Z", 0, 2, 0x20, 2, 0),
         (theirs, 0, 0, 0, 2, 0), (mine or "unused", 0, 0, 0, 2, 0)]))


def judge_ctor(fold):
    return judge(fold, PROOF, address=CTOR, name="??0B@@QAE@I@Z")


@pytest.mark.parametrize("mine, theirs", [
    (VTABLE_B, VTABLE_A),
    ("?g_put@@3PAXA", "?g_get@@3PAXA"),
    ("??_C@_05KJFLPDPA@money?$AA@", "??_C@_05PDJBBECF@hello?$AA@"),
    ("__real@7f7fffff", "__real@ff7fffff"),
    ("__imp__GetTickCount@0", "__imp__GetCurrentTime@0"),
], ids=["vtable", "global", "string", "float", "import"])
def test_a_dir32_operand_naming_another_symbol_is_not_a_fold(fold, mine, theirs):
    ctor_fixture(fold, mine, theirs)
    problems = judge_ctor(fold)
    assert problems and f"+0x4 binds {mine} where ??0A@@QAE@I@Z binds {theirs}" in problems[0]


def test_the_same_global_with_the_same_addend_is_a_fold(fold):
    ctor_fixture(fold, VTABLE_A, VTABLE_A)
    assert judge_ctor(fold) == []


def test_the_same_global_at_another_addend_is_refused(fold):
    ctor_fixture(fold, VTABLE_A, VTABLE_A, my_addend=4)
    problems = judge_ctor(fold)
    assert problems and f"binds {VTABLE_A}+4 where" in problems[0]


def test_a_constant_where_the_owner_has_a_relocation_is_refused(fold):
    # The pinned body hard-codes retail's address; ICF never folds a constant
    # with a relocation, and the constant names no symbol at all.
    ctor_fixture(fold, None, VTABLE_A)
    problems = judge_ctor(fold)
    assert problems and ("relocations at [] where ??0A@@QAE@I@Z has them at [+0x4/0x6]"
                         in problems[0])


def test_an_unprovable_relocation_type_is_refused(fold):
    # A DIR32NB the byte compare leaves alone: its in-place value happens to
    # equal retail's dword, so only the relocation check can see it.
    ctor_fixture(fold, VTABLE_A, VTABLE_A, my_addend=0x405000, my_reloc=0x07)
    problems = judge_ctor(fold)
    assert problems and "relocation type 0x0007 at +0x4 cannot be proven" in problems[0]


def second_owner(fold, vtable):
    """A second matched body claimed at CTOR, from Code/y.cpp, storing `vtable`."""
    fold.row("??0Rva00003000@@QAE@I@Z", CTOR, len(CTOR_BODY), source="Code/y.cpp")
    other = fold.tmp / "y.obj"
    other.write_bytes(coff(
        [(".text", TEXT, CTOR_BODY, [(4, 2, 0x06)])],
        [(".text", 0, 1, 0, 3, 1), (vtable, 0, 0, 0, 2, 0),
         ("??0Rva00003000@@QAE@I@Z", 0, 1, 0x20, 2, 0)]))
    objects = {"Code/x.cpp": fold.obj, "Code/y.cpp": other}
    fold.monkeypatch.setattr(fold.build, "row_object", lambda row: objects[row["source"]])


def test_a_second_owner_cannot_vouch_for_what_the_real_owner_lacks(fold):
    # Every matched owner of the extent is compared, not any one: a placeholder
    # row claimed beside ??0A, compiled with B's vtable, does not make B's
    # store A's.
    ctor_fixture(fold, VTABLE_B, VTABLE_A)
    second_owner(fold, VTABLE_B)
    problems = judge_ctor(fold)
    assert problems and f"+0x4 binds {VTABLE_B} where ??0A@@QAE@I@Z binds {VTABLE_A}" in problems[0]


def test_every_owner_agreeing_is_a_fold(fold):
    # 0x00211E58 carries three real-named _Vector_base constructors; a fourth
    # whose relocations they all share folds there.
    ctor_fixture(fold, VTABLE_A, VTABLE_A)
    second_owner(fold, VTABLE_A)
    assert judge_ctor(fold) == []


def test_a_call_with_another_addend_is_not_a_fold(fold):
    # The pinned body calls the rowed vector<int> helper through a REL32 whose
    # in-place addend is 4. compile_function resolves the name and ignores the
    # addend, so the bytes compare equal; the relocation does not.
    write_object(fold, pb=PB[:7] + b"\x04\x00\x00\x00" + PB[11:], pb_relocs=[(7, 11, 0x14)])
    problems = judge(fold, PROOF)
    assert problems and (f"+0x7 binds a call with addend 4 where {OLD_PB} binds a call with "
                         "addend 0") in problems[0]


GLOBAL_A, GLOBAL_B = "?g_count@@3HA", "?g_limit@@3HA"
# push ebp; mov ebp, esp; mov eax, [global]; mov esp, ebp; pop ebp; ret
OV_LOAD = b"\x55\x8b\xec\xa1\x00\x00\x00\x00\x8b\xe5\x5d\xc3"


def chain_fixture(fold, callee_global):
    """push_back's helper loads a global: vector<int>'s helper (the owner at
    HELPER) loads GLOBAL_A, the pinned chain's helper `callee_global`."""
    fold.memory[HELPER] = OV_LOAD[:4] + struct.pack("<I", 0x405010) + OV_LOAD[8:]
    mine = 12 if callee_global == GLOBAL_A else 13
    fold.obj.write_bytes(coff(
        [(".text", TEXT, PB, [(7, 5, 0x14)]), (".text", TEXT, OV_LOAD, [(4, mine, 0x06)]),
         (".text", TEXT, PB, [(7, 11, 0x14)]), (".text", TEXT, OV_LOAD, [(4, 12, 0x06)])],
        [(".text", 0, 1, 0, 3, 1), (NEW_PB, 0, 1, 0x20, 2, 0),
         (".text", 0, 2, 0, 3, 1), (NEW_OV, 0, 2, 0x20, 2, 0),
         (".text", 0, 3, 0, 3, 1), (OLD_PB, 0, 3, 0x20, 2, 0),
         (".text", 0, 4, 0, 3, 1), (OLD_OV, 0, 4, 0x20, 2, 0),
         (GLOBAL_A, 0, 0, 0, 2, 0), (GLOBAL_B, 0, 0, 0, 2, 0)]))
    return judge(fold, PROOF)


def test_a_callee_in_the_chain_must_carry_its_owners_relocations(fold):
    problems = chain_fixture(fold, GLOBAL_B)
    assert problems and (f"{NEW_OV}'s relocations are not those of the ledger body at "
                         f"0x{HELPER:08X}: +0x4 binds {GLOBAL_B} where {OLD_OV} binds "
                         f"{GLOBAL_A}") in problems[0]


def test_a_chain_whose_callee_loads_the_same_global_is_a_fold(fold):
    assert chain_fixture(fold, GLOBAL_A) == []


def test_a_section_symbol_is_not_a_callee_to_prove(fold):
    # A REL32 bound to a section symbol names no function: "its body" would be
    # read from whichever section of that name comes first in the object.
    write_object(fold, pb_relocs=[(7, 3, 0x14)])
    problems = judge(fold, PROOF)
    assert problems and ("calls .text, which is not one external function this object "
                         "defines") in problems[0]


def local_fixture(fold, my_section):
    """Both constructors store the address of a TU-local .rdata section; the
    owner names section 3, the pinned body section `my_section`. Two COMDAT
    .rdata sections share the name `.rdata`, so names alone cannot tell them apart."""
    fold.memory[CTOR] = CTOR_BODY[:4] + struct.pack("<I", 0x405000) + CTOR_BODY[8:]
    fold.row("??0A@@QAE@I@Z", CTOR, len(CTOR_BODY))
    symbol = {3: 4, 4: 6}[my_section]
    fold.obj.write_bytes(coff(
        [(".text", TEXT, CTOR_BODY, [(4, symbol, 0x06)]),
         (".text", TEXT, CTOR_BODY, [(4, 4, 0x06)]),
         (".rdata", RDATA, b"\0" * 8, []), (".rdata", RDATA, b"\0" * 8, [])],
        [(".text", 0, 1, 0, 3, 0), ("??0B@@QAE@I@Z", 0, 1, 0x20, 2, 0),
         (".text", 0, 2, 0, 3, 0), ("??0A@@QAE@I@Z", 0, 2, 0x20, 2, 0),
         (".rdata", 0, 3, 0, 3, 1), (".rdata", 0, 4, 0, 3, 0)]))


def test_the_same_local_symbol_is_a_fold(fold):
    local_fixture(fold, 3)
    assert judge_ctor(fold) == []


def test_a_different_local_symbol_of_the_same_name_is_refused(fold):
    local_fixture(fold, 4)
    problems = judge_ctor(fold)
    assert problems and "+0x4 binds TU-local symbol #6 of x.obj where" in problems[0]


def jump_fixture(fold, retail_label):
    """push ebp; mov ebp, esp; mov eax, offset $L (the body's own +12); mov eax, [eax];
    pop ebp; ret; then four bytes of table at +12."""
    body = b"\x55\x8b\xec\xb8\x00\x00\x00\x00\x8b\x00\x5d\xc3\x11\x22\x33\x44"
    fold.memory[CTOR] = body[:4] + struct.pack("<I", 0x400000 + CTOR + retail_label) + body[8:]
    fold.row("?Old@@YAHXZ", CTOR, len(body))
    fold.obj.write_bytes(coff(
        [(".text", TEXT, body, [(4, 3, 0x06)]), (".text", TEXT, body, [(4, 7, 0x06)])],
        [(".text", 0, 1, 0, 3, 1), ("?New@@YAHXZ", 0, 1, 0x20, 2, 0), ("$L1", 12, 1, 0, 6, 0),
         (".text", 0, 2, 0, 3, 1), ("?Old@@YAHXZ", 0, 2, 0x20, 2, 0), ("$L1", 12, 2, 0, 6, 0)]))
    return judge(fold, PROOF, address=CTOR, name="?New@@YAHXZ")


def test_a_jump_table_into_the_body_itself_is_a_fold(fold):
    assert jump_fixture(fold, 12) == []


def test_a_jump_table_entry_retail_does_not_hold_is_refused(fold):
    problems = jump_fixture(fold, 8)
    assert problems and "+0x4 points at its own +0xc" in problems[0]


# --- the tool path -------------------------------------------------------------------

@pytest.fixture
def add_route(fold):
    import hatch_counters
    admitted = []
    fold.monkeypatch.setattr(fold.admission, "ROOT", fold.tmp)
    fold.monkeypatch.setattr(hatch_counters, "blob_id", lambda path, data: "blob")
    fold.monkeypatch.setattr(hatch_counters, "admit",
                             lambda path, reason, tokens=None, before=None: admitted.append(tokens))
    fold.admitted = admitted
    return fold


def test_add_route_admits_a_proven_fold(add_route):
    write_object(add_route)
    assert add_route.admission.add_pins([(NEW_PB, f"0x{OWNER:X}")],
                                        "vector<A*> push_back; " + PROOF) == []
    pins = (add_route.tmp / "reverse" / "symbols.csv").read_text()
    assert f"{NEW_PB},0x{OWNER:08X},vector<A*> push_back; {PROOF}" in pins
    assert add_route.admitted == [{f"0x{OWNER:08X}"}]


@pytest.mark.parametrize("case", ["wrong-body", "gen-alias-twin", "other-vtable"])
def test_add_route_refuses_an_unproven_fold_and_writes_nothing(add_route, case):
    if case == "wrong-body":
        write_object(add_route, pb=PB[:3] + b"\x50" + PB[4:])
        name, address, why = NEW_PB, OWNER, "differs from retail"
    elif case == "gen-alias-twin":
        twin_fixture(add_route, "gen-alias")
        name, address, why = SET_ANGLE, SEGLINE, f"already has its own address 0x{VIEW:08X}"
    else:
        money_fixture(add_route, own_row=False)
        name, address, why = MONEY_PUT, GET_AT, f"+0x17 binds {PUT_VTABLE}"
    before = (add_route.tmp / "reverse" / "symbols.csv").read_bytes()
    problems = add_route.admission.add_pins([(name, f"0x{address:X}")], PROOF)
    assert problems and why in problems[0]
    assert (add_route.tmp / "reverse" / "symbols.csv").read_bytes() == before
    assert add_route.admitted == []


# --- the identity proof in the other order -------------------------------------------
#
# A fold admitted while its name had no body elsewhere stops being one when a later
# change gives the name a body of its own: landing View::setAngle's row after a
# setAngle fold pin onto its twin would rebuild what admission refuses.

FOLD_PIN = {"name": NEW_PB, "address": f"0x{OWNER:08X}", "notes": "vector<A*> fold; " + PROOF}


def test_a_row_elsewhere_for_a_fold_pinned_name_is_refused(fold):
    row = {**fold.rows[0], "name": NEW_PB, "target_rva": "0x00004800"}
    problems = fold.admission.judge([FOLD_PIN], [FOLD_PIN], fold.rows, fold.rows + [row])
    assert problems and f"{NEW_PB} is fold-pinned at 0x{OWNER:08X}" in problems[0]


def test_a_pin_elsewhere_for_a_fold_pinned_name_is_refused(fold):
    pin = {"name": NEW_PB, "address": "0x00004800", "notes": "callee"}
    problems = fold.admission.judge([FOLD_PIN], [FOLD_PIN, pin], fold.rows, fold.rows)
    assert problems and f"{NEW_PB} is fold-pinned at 0x{OWNER:08X}" in problems[-1]


def test_retiring_the_fold_pin_with_the_row_passes(fold):
    row = {**fold.rows[0], "name": NEW_PB, "target_rva": "0x00004800"}
    assert fold.admission.judge([FOLD_PIN], [], fold.rows, fold.rows + [row]) == []


def test_a_row_at_the_fold_address_itself_passes(fold):
    # Renaming the owner row to the folded name is one body, one address.
    row = {**fold.rows[0], "name": NEW_PB}
    assert fold.admission.judge([FOLD_PIN], [FOLD_PIN], fold.rows, fold.rows + [row]) == []


def test_a_token_on_an_unstacked_pin_is_not_a_fold(fold):
    # fold-proof= on a pin no other real name shares was never a proven fold,
    # and does not bind the name to that address.
    pin = {"name": NEW_PB, "address": "0x00003000", "notes": PROOF}
    row = {**fold.rows[0], "name": NEW_PB, "target_rva": "0x00004800"}
    assert fold.admission.judge([pin], [pin], fold.rows, fold.rows + [row]) == []


def test_add_route_refuses_a_pin_elsewhere_for_a_fold_pinned_name(add_route):
    write_pins(add_route, [(FOLD_PIN["name"], FOLD_PIN["address"], FOLD_PIN["notes"])])
    before = (add_route.tmp / "reverse" / "symbols.csv").read_bytes()
    problems = add_route.admission.add_pins([(NEW_PB, "0x4800")], "callee")
    assert problems and f"{NEW_PB} is fold-pinned at 0x{OWNER:08X}" in problems[0]
    assert (add_route.tmp / "reverse" / "symbols.csv").read_bytes() == before
