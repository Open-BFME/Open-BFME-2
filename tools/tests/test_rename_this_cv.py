"""`tools/rename.py function --respell` of `this`'s cv-qualifier alone, with no vote.

The shape is P24's: Rva007C454's Cull_Sphere (0x0007BEA7) is rowed non-const
(UAE), but retail's Rva007C454 table, installed by its constructor, holds it in
slot 129, which in CameraClass's own table holds the registered
`CameraClass::Cull_Sphere(const SphereClass &) const` (UBE). Declared non-const
the override would add a slot instead. So the const is proved by the base
virtual, and the respell changes nothing else:

  * the row sits in exactly one slot of a table its class's ctor installs;
  * a canonical base its views derive from installs a table whose same slot
    holds a registered row with the same identifier, convention and parameters,
    whose `this` cv is the new one;
  * after ./build.sh the installers' rebuilt table names the row in that slot.

The retail tables and compiled objects are injected as in test_rename_to_class.py.
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
CANONICAL = "class,header,notes\nCameraClass,Code/WW3D2/CameraClass.h,existing header\n"
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


@pytest.fixture
def objects(monkeypatch):
    """The retail tables and the installers' compiled tables (BUILT_BEFORE until a test swaps them)."""
    state = {"tables": dict(TABLES), "built": BUILT_BEFORE}
    monkeypatch.setattr(rename, "retail_vtables", lambda ctx: state["tables"])
    monkeypatch.setattr(rename, "compiled_vtables", lambda ctx, rel, current=True: state["built"].get(rel))
    monkeypatch.setattr(rename, "retail_jump", lambda ctx, rva: None)
    monkeypatch.setattr(rename, "external_vtables", lambda ctx, rel, current=True: set())
    return state


def recommit(root, rel, text):
    (root / rel).write_text(text)
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
                                   f"installed by {CTOR} at 0x0007C3CD; ")
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
    recommit(tree, "reverse/canonical_classes.csv", "class,header,notes\n")
    with pytest.raises(Refusal) as error:
        plan(tree)
    assert "no canonical base of Rva007C454 (CameraClass)" in str(error.value)


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
