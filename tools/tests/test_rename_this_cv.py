"""`tools/rename.py function --respell` of `this`'s cv-qualifier alone, with no vote.

The shape is P24's: Rva007C454's Cull_Sphere (0x0007BEA7) is rowed non-const
(UAE), but retail's Rva007C454 table, installed by its constructor, holds it in
slot 129, which in CameraClass's own table holds the registered
`CameraClass::Cull_Sphere(const SphereClass &) const` (UBE). Declared non-const
the override would add a slot instead. So the const is proved by the base
virtual, and the respell changes nothing else:

  * the row sits in exactly one slot of a table its class's ctor installs, and
    retail's bytes of that install store the table through `this` at offset 0;
  * a base in the class's canonical ancestry (its canonical_classes.csv record:
    contract bases, else its registered header -- never a prepared declaration)
    installs, through `this` too, a table whose same slot holds a registered
    row with the same identifier, convention and parameters, whose `this` cv is
    the new one;
  * after ./build.sh the installers' rebuilt table names the row in that slot.

The retail tables and compiled objects are injected as in test_rename_to_class.py;
the installers' retail bytes are a synthetic image read by the real decoder.
"""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

RVA = 0x0007BEA7
OLD = "?Cull_Sphere@Rva007C454@@UAE_NABVSphereClass@@@Z"
NEW = "?Cull_Sphere@Rva007C454@@UBE_NABVSphereClass@@@Z"
BASE = "?Cull_Sphere@CameraClass@@UBE_NABVSphereClass@@@Z"
BASE_RVA = 0x00135960
BOX_RVA = 0x0007BEDA
OLD_BOX = "?Cull_Box@Rva007C454@@UAE_NABVAABoxClass@@@Z"
NEW_BOX = "?Cull_Box@Rva007C454@@UBE_NABVAABoxClass@@@Z"
BASE_BOX = "?Cull_Box@CameraClass@@UBE_NABVAABoxClass@@@Z"
BASE_BOX_RVA = 0x00135990
RENDER = "?Render@CameraClass@@UAEXXZ"          # slot 0 of both tables
CTOR = "??0Rva007C454@@QAE@XZ"
CAM_DTOR = "??1CameraClass@@UAE@XZ"
TABLE = 0x007C6C58          # Rva007C454's table (rva)
BASE_TABLE = 0x007D26E0     # CameraClass's table (rva)
CTOR_STORE = 0x0007C3D0     # inside the ctor row
CAM_STORE = 0x00133A10      # inside CameraClass's dtor row
OVERLAP = "Code/Game/Rva0007BEA7Overlap.cpp"
BOX_SRC = "Code/Game/Rva0007BEDAOverlap.cpp"
CTOR_SRC = "Code/Game/Rva007C454Ctor.cpp"
CAMERA = "Code/WW3D2/camera.cpp"
EVIDENCE = "signature-only: CameraClass declares Cull_Sphere const"

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD},,0x0007BEA7,51,{OVERLAP},matched,slot 129
{OLD_BOX},,0x0007BEDA,128,{BOX_SRC},matched,slot 130
{CTOR},,0x0007C3CD,43,{CTOR_SRC},matched,ctor
{RENDER},,0x00001000,16,{CAMERA},matched,slot 0
{BASE},,0x00135960,42,{CAMERA},matched,slot 129 of CameraClass
{BASE_BOX},,0x00135990,214,{CAMERA},matched,slot 130 of CameraClass
{CAM_DTOR},,0x00133A00,64,{CAMERA},matched,dtor
"""
CANONICAL = ("class,header,notes\nCameraClass,Code/WW3D2/CameraClass.h,existing header\n"
             "Rva007C454,Code/Game/Rva007C454.h,camera-derived class\n")
CLASS_HEADER = '#include "CameraClass.h"\nclass Rva007C454 : public CameraClass { };\n'
IMAGE_BASE = 0x00400000
# retail bytes from each installer row's start to its store: push esi; mov esi, ecx; then
# (CameraClass's dtor) padding; the store itself is `mov dword ptr [esi], table`
CTOR_START, CAM_START = 0x0007C3CD, 0x00133A00
HEADER = """struct SphereClass;
class CameraClass {
public:
    virtual void Render();
    virtual bool Cull_Sphere(const SphereClass &) const;
    virtual bool Cull_Box(const AABoxClass &) const;
};
"""
OVERLAP_SRC = f"""// {OLD}
#include "CameraClass.h"
struct Rva007C454 : public CameraClass {{ bool Cull_Sphere(const SphereClass &); }};
bool Rva007C454::Cull_Sphere(const SphereClass &) {{ return false; }}
"""
BOX_TEXT = f"""// {OLD_BOX}
#include "CameraClass.h"
struct Rva007C454 : public CameraClass {{ bool Cull_Box(const AABoxClass &); }};
bool Rva007C454::Cull_Box(const AABoxClass &) {{ return false; }}
"""
BOX_PREPARED = BOX_TEXT.replace(OLD_BOX, NEW_BOX).replace("&);", "&) const;").replace("&) {", "&) const {")
CTOR_TEXT = """#include "CameraClass.h"
struct Rva007C454 : public CameraClass { Rva007C454(); bool Cull_Sphere(const SphereClass &); };
Rva007C454::Rva007C454() {}
"""
OVERLAP_PREPARED = OVERLAP_SRC.replace(OLD, NEW).replace("&);", "&) const;").replace("&) {", "&) const {")
CTOR_PREPARED = CTOR_TEXT.replace("&); }", "&) const; }")
TABLES = {TABLE: ([0x00001000, RVA, BOX_RVA], {CTOR_STORE: 0}),
          BASE_TABLE: ([0x00001000, BASE_RVA, BASE_BOX_RVA], {CAM_STORE: 0})}
BUILT_BEFORE = {CTOR_SRC: {"??_7Rva007C454@@6B@": [RENDER, OLD, OLD_BOX]}}
BUILT_AFTER = {CTOR_SRC: {"??_7Rva007C454@@6B@": [RENDER, NEW, OLD_BOX]}}
BUILT_BOTH = {CTOR_SRC: {"??_7Rva007C454@@6B@": [RENDER, NEW, NEW_BOX]}}


def _git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/canonical_classes.csv": CANONICAL,
        "Code/WW3D2/CameraClass.h": HEADER,
        "Code/Game/Rva007C454.h": CLASS_HEADER,
        OVERLAP: OVERLAP_SRC,
        BOX_SRC: BOX_TEXT,
        CTOR_SRC: CTOR_TEXT,
        CAMERA: "void camera() {}\n",
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    _git(tmp_path, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "seed")
    return tmp_path


def store_bytes(table, base_reg=b"\x06"):
    """`mov dword ptr [reg], table` (C7 /0 imm32); 06 is [esi], 01 [ecx], 00 [eax], 46 04 [esi+4]."""
    import struct
    return b"\xc7" + base_reg + struct.pack("<I", table + IMAGE_BASE)


def retail_code():
    """{start: bytes} of the installers' retail code: the store sits at CTOR_STORE / CAM_STORE."""
    return {CTOR_START: b"\x56\x8b\xf1" + store_bytes(TABLE),
            CAM_START: b"\x56\x8b\xf1" + b"\x90" * 13 + store_bytes(BASE_TABLE)}


@pytest.fixture
def objects(monkeypatch):
    """The retail tables, the installers' retail bytes and their compiled tables
    (BUILT_BEFORE until a test swaps them)."""
    import build
    state = {"tables": dict(TABLES), "built": BUILT_BEFORE, "code": retail_code()}

    def exe_image():
        image = bytearray(b"\xcc" * 0x140000)
        for start, code in state["code"].items():
            image[start:start + len(code)] = code
        return bytes(image), [dict(name=".text", rva=0, size=len(image), raw_size=len(image), raw_pointer=0)]
    monkeypatch.setattr(build, "exe_image", exe_image)
    monkeypatch.setattr(rename, "retail_vtables", lambda ctx: state["tables"])
    monkeypatch.setattr(rename, "compiled_vtables", lambda ctx, rel, current=True: state["built"].get(rel))
    monkeypatch.setattr(rename, "retail_jump", lambda ctx, rva: None)
    monkeypatch.setattr(rename, "external_vtables", lambda ctx, rel, current=True: set())
    return state


def recommit(root, rel, text):
    (root / rel).parent.mkdir(parents=True, exist_ok=True)
    (root / rel).write_bytes(text.encode("utf-8"))      # LF on every host
    _git(root, "add", "-A")
    _git(root, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "edit")


def plan(root, **overrides):
    kwargs = dict(rva=RVA, new=NEW, respell=True, basis="inferred", evidence=EVIDENCE,
                  prepared={OVERLAP: OVERLAP_PREPARED.encode(), CTOR_SRC: CTOR_PREPARED.encode()})
    kwargs.update(overrides)
    return rename.plan_rename("function", ctx=rename.Context(root, object_scan=False), **kwargs)


# ------------------------------------------------------------------ the P24 shape

def test_this_cv_change_reads_only_the_this_qualifier():
    assert rename.this_cv_change(OLD, NEW)
    assert not rename.this_cv_change(OLD, NEW.replace("ABVSphere", "AAVSphere"))     # a parameter too
    assert not rename.this_cv_change(OLD, OLD.replace("@@UAE", "@@MBE"))              # the access too
    assert not rename.this_cv_change(OLD, OLD)


def test_respells_the_this_cv_proved_by_the_base_virtual(tree, objects):
    got = plan(tree)
    assert (OLD, NEW, RVA) in got.renamed_rows
    assert f"{NEW},,0x0007BEA7,51,{OVERLAP}," in got.after["reverse/functions.csv"].decode()
    assert got.this_cv["slot"] == 1 and got.this_cv["sources"] == [CTOR_SRC]
    assert CTOR_SRC in got.verify and OVERLAP in got.verify
    assert got.evidence.startswith(EVIDENCE + "; this-cv: 0x0007BEA7 fills retail table 0x00BC6C58 slot 1, "
                                   f"installed by {CTOR} at 0x0007C3CD (stored through `this`); ")
    assert f"overrides {BASE} (0x00135960, CameraClass's retail table 0x00BD26E0 slot 1)" in got.evidence
    basis = got.after["reverse/name_basis.csv"].decode()
    assert ",inferred," in basis and "agree:" not in basis and "this-cv:" in basis


def test_apply_passes_when_the_rebuilt_table_names_the_row_in_its_slot(tree, objects):
    got = plan(tree)

    def verify(c, sources):
        objects["built"] = BUILT_AFTER
        return True
    rename.apply_rename(got, ctx=rename.Context(tree, object_scan=False), verify=verify, checks=None)
    assert NEW in (tree / "reverse/functions.csv").read_text()
    assert (tree / CTOR_SRC).read_text() == CTOR_PREPARED


def test_refused_when_the_rebuilt_table_adds_a_slot_instead(tree, objects):
    """Declared so that it does not override, the row lands in a new slot 2."""
    got = plan(tree)

    def verify(c, sources):
        objects["built"] = {CTOR_SRC: {"??_7Rva007C454@@6B@": [RENDER, BASE, NEW]}}
        return True
    with pytest.raises(VerifyFailed) as error:
        rename.apply_rename(got, ctx=rename.Context(tree, object_scan=False), verify=verify, checks=None)
    assert "the rebuilt vftable does not prove" in str(error.value) and "every file restored" in str(error.value)
    assert OLD in (tree / "reverse/functions.csv").read_text()
    assert (tree / CTOR_SRC).read_text() == CTOR_TEXT


# ------------------------------------------------------------- what it refuses

def test_refused_when_the_base_virtual_has_another_cv(tree, objects):
    nonconst = BASE.replace("@@UBE", "@@UAE")
    recommit(tree, "reverse/functions.csv", FUNCTIONS.replace(BASE, nonconst))
    with pytest.raises(Refusal) as error:
        plan(tree)
    assert f"{nonconst} (CameraClass's retail table 0x00BD26E0 slot 1) has `this` cv 'A', not 'B'" \
        in str(error.value)


def test_refused_when_the_base_slot_is_no_registered_row(tree, objects):
    recommit(tree, "reverse/functions.csv", FUNCTIONS.replace(f"{BASE},,0x00135960,42,{CAMERA},matched,"
                                                              "slot 129 of CameraClass\n", ""))
    with pytest.raises(Refusal) as error:
        plan(tree)
    assert "0x00135960, which is no registered row" in str(error.value)


def test_refused_when_the_base_is_not_canonical(tree, objects):
    recommit(tree, "reverse/canonical_classes.csv",
             "class,header,notes\nRva007C454,Code/Game/Rva007C454.h,camera-derived class\n")
    with pytest.raises(Refusal) as error:
        plan(tree)
    assert "no canonical base in Rva007C454's canonical ancestry (CameraClass)" in str(error.value)


def test_refused_when_the_base_slot_holds_another_virtual(tree, objects):
    other = "?Cull_Box@CameraClass@@UBE_NABVAABoxClass@@@Z"
    recommit(tree, "reverse/functions.csv", FUNCTIONS.replace(BASE, other))
    with pytest.raises(Refusal) as error:
        plan(tree)
    assert "not the virtual this row overrides" in str(error.value)


def test_refused_when_no_retail_table_installs_the_row(tree, objects):
    objects["tables"] = {TABLE: ([0x00001000, 0x00001000, BOX_RVA], {CTOR_STORE: 0}),
                         BASE_TABLE: ([0x00001000, BASE_RVA, BASE_BOX_RVA], {CAM_STORE: 0})}
    with pytest.raises(Refusal) as error:
        plan(tree)
    assert "no retail vftable slot holds 0x0007BEA7" in str(error.value)


def test_refused_when_an_installer_is_not_prepared(tree, objects):
    with pytest.raises(Refusal) as error:
        plan(tree, prepared={OVERLAP: OVERLAP_PREPARED.encode()})
    assert "installers compile does not put" in str(error.value)


@pytest.mark.parametrize("new", [
    NEW.replace("ABVSphere", "AAVSphere"),                  # a parameter's cv as well
    OLD.replace("@@UAE", "@@MBE"),                          # the access as well
    OLD.replace("Rva007C454@@UAE", "CameraClass@@UBE"),     # the class as well
])
def test_refused_when_more_than_this_cv_changes(tree, objects, new):
    with pytest.raises(Refusal) as error:
        plan(tree, new=new)
    assert "changes more than" in str(error.value) or "differs from" in str(error.value)


def test_refused_for_a_non_virtual_row(tree, objects):
    plain = OLD.replace("@@UAE", "@@QAE")
    recommit(tree, "reverse/functions.csv", FUNCTIONS.replace(OLD, plain))
    recommit(tree, OVERLAP, OVERLAP_SRC.replace(OLD, plain))
    with pytest.raises(Refusal) as error:
        plan(tree, new=plain.replace("@@QAE", "@@QBE"))
    assert "is not virtual" in str(error.value)


def test_still_a_labelled_inference(tree, objects):
    with pytest.raises(Refusal) as error:
        plan(tree, basis="canonical:zh")
    assert "--basis inferred" in str(error.value)



# ------------------------------------------------- --also: P24's two slots in one apply

def batch(root, **overrides):
    kwargs = dict(also=[(BOX_RVA, NEW_BOX)],
                  prepared={OVERLAP: OVERLAP_PREPARED.encode(), BOX_SRC: BOX_PREPARED.encode(),
                            CTOR_SRC: CTOR_PREPARED.replace("&); }", "&) const; }").encode()})
    kwargs.update(overrides)
    return plan(root, **kwargs)


def test_also_respells_both_slots_in_one_plan(tree, objects):
    recommit(tree, "reverse/name_basis.csv", "kind,old,new,basis,evidence,source,rva\n"
             f"function,?rva0007BEDA@Rva007C454@@UAE_NABVAABoxClass@@@Z,{OLD_BOX},inferred,agree:nl-x,{BOX_SRC},0x0007BEDA\n")
    got = batch(tree)
    assert (OLD, NEW, RVA) in got.renamed_rows and (OLD_BOX, NEW_BOX, BOX_RVA) in got.renamed_rows
    rows = got.after["reverse/functions.csv"].decode()
    assert f"{NEW},,0x0007BEA7,51,{OVERLAP}," in rows and f"{NEW_BOX},,0x0007BEDA,128,{BOX_SRC}," in rows
    assert got.this_cv["slots"] == {1: NEW, 2: NEW_BOX}
    assert got.this_cv["moved"] == {NEW: RVA, NEW_BOX: BOX_RVA}
    assert f"overrides {BASE} (0x00135960" in got.evidence and f"overrides {BASE_BOX} (0x00135990" in got.evidence
    basis = got.after["reverse/name_basis.csv"].decode()
    assert f"function,{OLD},{NEW}" in basis and f"function,{OLD_BOX},{NEW_BOX}" in basis
    assert f"carry,{OLD_BOX}," not in basis and not got.carried
    assert {OVERLAP, BOX_SRC, CTOR_SRC} <= set(got.verify)
    assert f"file:{BOX_SRC}" in got.claims and BOX_RVA in got.claims
    assert got.subject().startswith("Respell `this` cv of 2 Rva007C454 virtuals")


def test_also_apply_checks_every_slot_after_one_build(tree, objects):
    got = batch(tree)

    def verify(c, sources):
        objects["built"] = BUILT_BOTH
        return True
    rename.apply_rename(got, ctx=rename.Context(tree, object_scan=False), verify=verify, checks=None)
    text = (tree / "reverse/functions.csv").read_text()
    assert NEW in text and NEW_BOX in text


def test_also_refused_after_the_build_when_one_slot_is_wrong(tree, objects):
    got = batch(tree)

    def verify(c, sources):
        objects["built"] = BUILT_AFTER          # slot 2 still names the non-const Cull_Box
        return True
    with pytest.raises(VerifyFailed) as error:
        rename.apply_rename(got, ctx=rename.Context(tree, object_scan=False), verify=verify, checks=None)
    assert f"slot 2 names {OLD_BOX}, not {NEW_BOX}" in str(error.value)
    assert OLD_BOX in (tree / "reverse/functions.csv").read_text()


def test_also_refused_when_a_sibling_fails_its_proof(tree, objects):
    """Each sibling needs its own base virtual with the new cv."""
    nonconst = BASE_BOX.replace("@@UBE", "@@UAE")
    recommit(tree, "reverse/functions.csv", FUNCTIONS.replace(BASE_BOX, nonconst))
    with pytest.raises(Refusal) as error:
        batch(tree)
    assert f"{nonconst} (CameraClass's retail table 0x00BD26E0 slot 2) has `this` cv 'A', not 'B'" \
        in str(error.value)


def test_also_refused_when_a_sibling_is_in_no_retail_table(tree, objects):
    objects["tables"] = {TABLE: ([0x00001000, RVA, 0x00001000], {CTOR_STORE: 0}),
                         BASE_TABLE: ([0x00001000, BASE_RVA, BASE_BOX_RVA], {CAM_STORE: 0})}
    with pytest.raises(Refusal) as error:
        batch(tree)
    assert "no retail vftable slot holds 0x0007BEDA" in str(error.value)


def test_also_refused_when_a_sibling_changes_more_than_this_cv(tree, objects):
    with pytest.raises(Refusal) as error:
        batch(tree, also=[(BOX_RVA, NEW_BOX.replace("ABVAABox", "AAVAABox"))])
    assert "with only `this`'s cv changed" in str(error.value)


def test_also_refused_when_a_siblings_unit_is_not_prepared(tree, objects):
    with pytest.raises(Refusal) as error:
        batch(tree, prepared={OVERLAP: OVERLAP_PREPARED.encode(),
                              CTOR_SRC: CTOR_PREPARED.replace("&); }", "&) const; }").encode()})
    assert f"{BOX_SRC} still spells {OLD_BOX}" in str(error.value)


def test_also_refused_when_a_sibling_repeats_the_row(tree, objects):
    with pytest.raises(Refusal) as error:
        batch(tree, also=[(RVA, NEW_BOX)])
    assert "each RVA and each new name once" in str(error.value)


def test_also_refused_without_a_this_cv_primary(tree, objects):
    pointer = OLD.replace("ABVSphere", "PBVSphere")     # a signature-only respell, not this-cv
    with pytest.raises(Refusal) as error:
        batch(tree, new=pointer)
    assert "adds rows to a this-cv respell only" in str(error.value)



# ------------------------------- a sibling gets the primary row's own checks (review of 8190d42b18)

def test_also_refused_when_a_sibling_carries_an_alias_pin(tree, objects):
    """An alias pin (the row mangled through another view) refuses a sibling as it refuses the primary."""
    alias = OLD_BOX.replace("ABVAABoxClass", "PBVAABoxClass")
    recommit(tree, "reverse/symbols.csv", f"name,address,notes\n{alias},0x{BOX_RVA:08X},alias\n")
    assert rename.alias_pins(rename.Context(tree, object_scan=False), OLD_BOX, BOX_RVA) == [alias]
    with pytest.raises(Refusal, match="alias pin") as as_sibling:
        batch(tree)
    with pytest.raises(Refusal, match="alias pin") as as_primary:
        plan(tree, rva=BOX_RVA, new=NEW_BOX, prepared={BOX_SRC: BOX_PREPARED.encode(),
                                                       CTOR_SRC: CTOR_PREPARED.encode()})
    assert str(as_sibling.value) == str(as_primary.value)


def test_also_refused_when_a_siblings_identifier_is_canonical(tree, objects):
    """A canonical record of the bare identifier refuses a sibling as it refuses the primary."""
    recommit(tree, "reverse/name_basis.csv", "kind,old,new,basis,evidence,source,rva\n"
             "function,Old,Cull_Box,canonical:zh,proof,Code/X.cpp,0x0007BEDA\n")
    with pytest.raises(Refusal, match="canonical name") as as_sibling:
        batch(tree)
    with pytest.raises(Refusal, match="canonical name") as as_primary:
        plan(tree, rva=BOX_RVA, new=NEW_BOX, prepared={BOX_SRC: BOX_PREPARED.encode(),
                                                       CTOR_SRC: CTOR_PREPARED.encode()})
    assert str(as_sibling.value) == str(as_primary.value)


def test_siblings_run_the_primary_rows_check_functions(tree, objects, monkeypatch):
    """One set of checks for both: each runs once per row, sibling included."""
    seen = {"owner": [], "identity": [], "collision": []}
    for name, key in (("function_owner", "owner"), ("function_identity_checks", "identity"),
                      ("function_collision_checks", "collision")):
        real = getattr(rename, name)

        def spy(ctx, rva, *args, real=real, key=key, **kwargs):
            seen[key].append(rva)
            return real(ctx, rva, *args, **kwargs)
        monkeypatch.setattr(rename, name, spy)
    batch(tree)
    assert {key: sorted(rvas) for key, rvas in seen.items()} == {
        "owner": [RVA, BOX_RVA], "identity": [RVA, BOX_RVA], "collision": [RVA, BOX_RVA]}



# ------------------------------- the install goes through `this` (review round 2, finding 3)

def install(objects, start, code, store_at, table=TABLE):
    """Retail bytes `code` at `start`, whose table store sits at `store_at`."""
    objects["code"][start] = code
    slots, _stores = objects["tables"][table]
    objects["tables"][table] = (slots, {store_at: 0})


def test_refused_when_the_store_goes_through_a_loaded_pointer(tree, objects):
    """review_installer_repro.py: `mov eax,[ecx+4]; mov [eax],table` installs a
    member object's table, not this class's."""
    install(objects, CTOR_START, b"\x8b\x41\x04" + store_bytes(TABLE, b"\x00"), CTOR_START + 3)
    with pytest.raises(Refusal, match=r"not proved Rva007C454's own: .*stores through `dword ptr \[eax\]`, "
                                      r"not `this`"):
        plan(tree)


def test_refused_when_a_base_table_store_goes_through_a_loaded_pointer(tree, objects):
    install(objects, CAM_START, b"\x8b\x41\x04" + store_bytes(BASE_TABLE, b"\x00"), CAM_START + 3,
            table=BASE_TABLE)
    with pytest.raises(Refusal, match="no canonical base in Rva007C454's canonical ancestry .* installs, "
                                      "through `this`"):
        plan(tree)


def test_a_store_straight_through_ecx_is_this(tree, objects):
    install(objects, CTOR_START, b"\x90\x90\x90" + store_bytes(TABLE, b"\x01"), CTOR_START + 3)
    assert plan(tree).this_cv["slot"] == 1


def test_a_this_copy_survives_a_call(tree, objects):
    """push esi; mov esi, ecx; call Base::Base; mov [esi], table: esi is callee-saved."""
    install(objects, CTOR_START, b"\x56\x8b\xf1\xe8\x00\x00\x00\x00" + store_bytes(TABLE), CTOR_START + 8)
    assert plan(tree).this_cv["slot"] == 1


def test_refused_when_ecx_is_used_after_a_call(tree, objects):
    install(objects, CTOR_START, b"\xe8\x00\x00\x00\x00" + store_bytes(TABLE, b"\x01"), CTOR_START + 5)
    with pytest.raises(Refusal, match="not `this`"):
        plan(tree)


def test_refused_when_this_is_reloaded_from_the_frame(tree, objects):
    """mov [ebp-4], ecx; mov eax, [ebp-4]; mov [eax], table: a load in between."""
    install(objects, CTOR_START, b"\x89\x4d\xfc\x8b\x45\xfc" + store_bytes(TABLE, b"\x00"), CTOR_START + 6)
    with pytest.raises(Refusal, match="not `this`"):
        plan(tree)


def test_refused_when_the_copy_is_overwritten(tree, objects):
    """mov esi, ecx; mov esi, [esi+4]: esi no longer holds this."""
    install(objects, CTOR_START, b"\x8b\xf1\x8b\x76\x04" + store_bytes(TABLE), CTOR_START + 5)
    with pytest.raises(Refusal, match="not `this`"):
        plan(tree)


def test_refused_when_the_store_is_off_the_primary_vfptr(tree, objects):
    install(objects, CTOR_START, b"\x8b\xf1\xc7\x46\x04" + (TABLE + IMAGE_BASE).to_bytes(4, "little"),
            CTOR_START + 2)
    with pytest.raises(Refusal, match=r"this\+0x4, not the primary vfptr"):
        plan(tree)


def test_refused_when_a_branch_precedes_the_store(tree, objects):
    install(objects, CTOR_START, b"\xeb\x00\x90" + store_bytes(TABLE, b"\x01"), CTOR_START + 3)
    with pytest.raises(Refusal, match="a branch at 0x0007C3CD precedes the store"):
        plan(tree)


# ------------------------------- ancestry from the canonical record (review round 2, finding 4)

def test_refused_when_the_class_has_no_canonical_record(tree, objects):
    """review_this_cv_repro.py: a prepared `: public CameraClass` proves nothing."""
    recommit(tree, "reverse/canonical_classes.csv", CANONICAL.split("Rva007C454,")[0])
    with pytest.raises(Refusal, match="Rva007C454 has no record in reverse/canonical_classes.csv"):
        plan(tree)


def test_refused_when_the_canonical_header_does_not_derive_from_the_base(tree, objects):
    """The prepared views say `: public CameraClass`; the registered header does not."""
    recommit(tree, "Code/Game/Rva007C454.h", "class Rva007C454 { };\n")
    with pytest.raises(Refusal, match=r"no canonical base in Rva007C454's canonical ancestry \(none\)"):
        plan(tree)


def test_a_private_base_view_in_a_prepared_unit_proves_nothing(tree, objects):
    """The review's shape: prepared units carry their own CameraClass copy and derive from it."""
    recommit(tree, "Code/Game/Rva007C454.h", "class Rva007C454 { };\n")
    private = "class CameraClass { public: virtual void Render(); virtual bool Cull_Sphere(const SphereClass &) const; };\n"
    prepared = {OVERLAP: OVERLAP_PREPARED.replace('#include "CameraClass.h"', private).encode(),
                CTOR_SRC: CTOR_PREPARED.replace('#include "CameraClass.h"', private).encode()}
    with pytest.raises(Refusal, match="canonical ancestry"):
        plan(tree, prepared=prepared)


def test_the_contract_bases_decide_before_the_header(tree, objects):
    recommit(tree, "Code/Game/Rva007C454.h", "class Rva007C454 { };\n")
    recommit(tree, "reverse/class_contracts/Rva007C454.json", '{"class": "Rva007C454", "bases": ["CameraClass"]}\n')
    assert plan(tree).this_cv["slot"] == 1
    recommit(tree, "Code/Game/Rva007C454.h", CLASS_HEADER)
    recommit(tree, "reverse/class_contracts/Rva007C454.json", '{"class": "Rva007C454", "bases": []}\n')
    with pytest.raises(Refusal, match="canonical ancestry"):
        plan(tree)


# ------------------------------------------------------------ an EH frame before the store
EH_PROLOG = 0x00629188
OTHER_CALL = 0x00629200
EH_START = 0x0007C404
EH_ROW = dict(name="??0Rva007C454@@QAE@ABV0@@Z", target_rva=f"0x{EH_START:08X}", target_size="80")


HELPER_ROW = dict(name="__EH_prolog", target_rva=f"0x{EH_PROLOG:08X}", target_size="31")
OTHER_ROW = dict(name="?other@@YAXXZ", target_rva=f"0x{OTHER_CALL:08X}", target_size="16")


class EhContext:
    def __init__(self, rows=(HELPER_ROW, OTHER_ROW)):
        self._rows = list(rows)

    def rows(self):
        return self._rows


def eh_frame(callee, after_call):
    """`mov eax,<FuncInfo>; call callee`, then `after_call`, then a vptr store through esi."""
    import struct
    head = b"\xb8" + struct.pack("<I", 0x00B00000)
    head += b"\xe8" + struct.pack("<i", callee - (EH_START + len(head) + 5))
    return head + after_call


def eh_problem(monkeypatch, code, ctx=None):
    """this_store_problem on `code` from EH_START, whose last instruction is the store."""
    import build
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: (code + b"\xcc" * size)[:size])
    return rename.this_store_problem(ctx or EhContext(), EH_ROW, EH_START + len(code) - 6)


COPY_THIS = b"\x51\x53\x56\x8b\xf1"                    # push ecx; push ebx; push esi; mov esi,ecx


def test_the_eh_prolog_call_leaves_this_in_ecx(monkeypatch):
    assert eh_problem(monkeypatch, eh_frame(EH_PROLOG, COPY_THIS + store_bytes(TABLE))) is None


def test_another_call_in_that_position_still_drops_ecx(monkeypatch):
    why = eh_problem(monkeypatch, eh_frame(OTHER_CALL, COPY_THIS + store_bytes(TABLE)))
    assert "stores through `dword ptr [esi]`" in why


def test_only_ecx_survives_the_eh_prolog_call(monkeypatch):
    import struct
    # mov edx,ecx; mov eax,<FuncInfo>; call __EH_prolog; mov dword ptr [edx],table
    code = b"\x8b\xd1\xb8" + struct.pack("<I", 0x00B00000)
    code += b"\xe8" + struct.pack("<i", EH_PROLOG - (EH_START + len(code) + 5))
    assert "stores through `dword ptr [edx]`" in eh_problem(monkeypatch, code + store_bytes(TABLE, b"\x02"))


def test_the_eh_prolog_call_does_not_bring_back_a_dropped_ecx(monkeypatch):
    import struct
    # call other; mov eax,<FuncInfo>; call __EH_prolog; mov esi,ecx; store
    code = b"\xe8" + struct.pack("<i", OTHER_CALL - (EH_START + 5))
    code += b"\xb8" + struct.pack("<I", 0x00B00000)
    code += b"\xe8" + struct.pack("<i", EH_PROLOG - (EH_START + len(code) + 5))
    assert "stores through `dword ptr [esi]`" in eh_problem(monkeypatch, code + b"\x8b\xf1" + store_bytes(TABLE))


def test_a_reload_after_the_eh_prolog_call_loses_this(monkeypatch):
    # mov ecx,[ebp+8]; mov esi,ecx: ecx no longer holds this
    why = eh_problem(monkeypatch, eh_frame(EH_PROLOG, b"\x8b\x4d\x08\x8b\xf1" + store_bytes(TABLE)))
    assert "stores through `dword ptr [esi]`" in why


# A second __EH_prolog row, wherever it sits, leaves no helper at all: neither address keeps ecx.
DUPLICATE_ELSEWHERE = (HELPER_ROW, OTHER_ROW, dict(name="__EH_prolog", target_rva=f"0x{OTHER_CALL:08X}", target_size="16"))
DUPLICATE_SAME = (HELPER_ROW, dict(HELPER_ROW), OTHER_ROW)


@pytest.mark.parametrize("callee", [OTHER_CALL, EH_PROLOG])
def test_a_duplicate_helper_row_elsewhere_gives_no_exception(monkeypatch, callee):
    why = eh_problem(monkeypatch, eh_frame(callee, COPY_THIS + store_bytes(TABLE)), EhContext(DUPLICATE_ELSEWHERE))
    assert "stores through `dword ptr [esi]`" in why


def test_a_duplicate_helper_row_at_its_address_gives_no_exception(monkeypatch):
    why = eh_problem(monkeypatch, eh_frame(EH_PROLOG, COPY_THIS + store_bytes(TABLE)), EhContext(DUPLICATE_SAME))
    assert "stores through `dword ptr [esi]`" in why


def test_no_helper_row_keeps_every_call_ordinary(monkeypatch):
    why = eh_problem(monkeypatch, eh_frame(EH_PROLOG, COPY_THIS + store_bytes(TABLE)), EhContext((OTHER_ROW,)))
    assert "stores through `dword ptr [esi]`" in why


# ------------------------------------------------------------ this_displacements reads the same one row

class DisplacementContext(EhContext):
    root = rename.ROOT.resolve()

    def __init__(self, rows):
        super().__init__(rows)
        self._cache = {}


def displacements(monkeypatch, callee, rows):
    """this_displacements on `mov eax,<FuncInfo>; call callee; mov esi,ecx; store` from EH_START."""
    import build
    code = eh_frame(callee, b"\x8b\xf1" + store_bytes(TABLE))
    monkeypatch.setattr(build, "exe_image", lambda: (code, []))
    monkeypatch.setattr(build, "rva_to_file_offset", lambda sections, rva: 0)
    row = dict(EH_ROW, target_size=str(len(code)))
    return rename.this_displacements(DisplacementContext(rows), row), EH_START + len(code) - 6


def test_this_displacements_keeps_this_past_the_one_helper_row(monkeypatch):
    found, store = displacements(monkeypatch, EH_PROLOG, (HELPER_ROW, OTHER_ROW))
    assert found == {store: 0}


@pytest.mark.parametrize("callee", [OTHER_CALL, EH_PROLOG])
def test_this_displacements_gets_no_exception_from_a_duplicate_row(monkeypatch, callee):
    found, _store = displacements(monkeypatch, callee, DUPLICATE_ELSEWHERE)
    assert found == {}


def test_this_displacements_gets_no_exception_from_a_duplicate_at_its_address(monkeypatch):
    found, _store = displacements(monkeypatch, EH_PROLOG, DUPLICATE_SAME)
    assert found == {}


def test_this_displacements_treats_another_call_as_ordinary(monkeypatch):
    found, _store = displacements(monkeypatch, OTHER_CALL, (HELPER_ROW, OTHER_ROW))
    assert found == {}

