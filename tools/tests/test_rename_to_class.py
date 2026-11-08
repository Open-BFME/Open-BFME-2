"""tools/rename.py function --to-class on a miniature tree: moving a
placeholder-class member into the real class whose own retail vftable holds
its address, as that class's virtual. The retail image (rename.retail_vtables)
and the compiled installer objects (rename.compiled_vtables) are injected, and
so is verification, as in test_rename_virtual.py."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

OLD = "?rva00401000@Rva00401000@@QAEXXZ"
NEW = "?spin@Widget@@UAEXXZ"
EH = "__ehhandler$" + OLD
CTOR = "??0Widget@@QAE@XZ"
GDTOR = "??_GWidget@@UAEPAXI@Z"
STOP = "?stop@Widget@@UAEXXZ"
TABLE = 0x00800000          # retail table rva
CTOR_STORE = 0x00402010     # inside the ctor row: mov dword ptr [ecx], TABLE
OTHER_STORE = 0x00408010    # inside the unrelated Other ctor row

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD},,0x00401000,40,Code/Game/Bits.cpp,matched,vtable slot; address-derived class
{EH},,0x00790000,10,Code/Game/Bits.cpp,matched,gen-ehstub
$L100,,0x00790010,8,Code/Game/Bits.cpp,matched,gen-funclet;parent={OLD}
{CTOR},,0x00402000,64,Code/Game/Widget.cpp,matched,installs table 0x00C00000
{GDTOR},,0x00403040,28,Code/Game/Widget.cpp,matched,deleting dtor
{STOP},,0x00404000,8,Code/Game/Widget.cpp,matched,slot 2
?count@Gadget@@QAEXXZ,,0x00405000,12,Code/Game/Gadget.cpp,matched,a readable member
??0Other@@QAE@XZ,,0x00408000,64,Code/Game/Other.cpp,matched,unrelated ctor
"""
SYMBOLS = f"""name,address,notes
{OLD},0x00401000,pin
"""
DELETED = 'name,target_rva,reason\n?gone@@YAXXZ,0x00100000,"old, retired"\n'
BITS = f"""// cl: /O2
// {OLD} @ 0x00401000
class Rva00401000 {{ public: void rva00401000(); }};
void Rva00401000::rva00401000() {{}}
"""
BITS_PREPARED = f"""// cl: /O2
// {OLD} @ 0x00401000
class Widget {{ public: virtual void spin(); }};
void Widget::spin() {{}}
"""
WIDGET = """class Widget {
public:
    Widget();
    virtual ~Widget();
    virtual void spin();
    virtual void stop();
};
Widget::Widget() {}
void Widget::stop() {}
"""
GADGET = "struct Gadget { void count(); };\nvoid Gadget::count() {}\n"
OTHER = "class Other { public: Other(); };\nOther::Other() {}\n"
# the compiled Widget vftable: slot 0 deleting dtor, 1 spin, 2 stop
COMPILED = {"??_7Widget@@6B@": [GDTOR, NEW, STOP]}


def _git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/symbols.csv": SYMBOLS,
        "reverse/deleted_rows.csv": DELETED,
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "Code/Game/Bits.cpp": BITS,
        "Code/Game/Widget.cpp": WIDGET,
        "Code/Game/Gadget.cpp": GADGET,
        "Code/Game/Other.cpp": OTHER,
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "-c", "user.name=t", "-c", "user.email=t@t", "add", "-A")
    _git(tmp_path, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "tree")
    return tmp_path


def retail(monkeypatch, tables, compiled=None, jumps=None):
    """Inject the retail image {table rva: (slots, {store rva: this offset})},
    the installer objects' vftables {source: {??_7 symbol: [names]}} and the
    retail `jmp rel32` entries {rva: target} (none unless given)."""
    monkeypatch.setattr(rename, "retail_vtables", lambda ctx: tables)
    built = {"Code/Game/Widget.cpp": COMPILED} if compiled is None else compiled
    monkeypatch.setattr(rename, "compiled_vtables", lambda ctx, rel, current=True: built.get(rel))
    monkeypatch.setattr(rename, "retail_jump", lambda ctx, rva: (jumps or {}).get(rva))
    monkeypatch.setattr(rename, "external_vtables", lambda ctx, rel, current=True: set())


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def plan(root, rva=0x00401000, new="spin", cls="Widget", prepared=True, **overrides):
    edits = {"Code/Game/Bits.cpp": BITS_PREPARED.encode()} if prepared else None
    return rename.plan_rename("function", ctx=ctx_of(root), rva=rva, to_class=cls, new=new,
                              prepared=edits, **overrides)


GOOD = {TABLE: ([0x00403040, 0x00401000, 0x00404000], {CTOR_STORE: 0})}


# ------------------------------------------------------------ the decoration

@pytest.mark.parametrize("old,new,expected", [
    ("?rva1@Rva1@@QAEXXZ", "spin", "?spin@Widget@@UAEXXZ"),
    ("?name@Rva2Named@@QBEPBDXZ", "name", "?name@Widget@@UBEPBDXZ"),       # const kept
    ("?f@Rva3@@IAEHH@Z", "f", "?f@Widget@@MAEHH@Z"),                       # protected -> protected virtual
    ("?name@Rva2Named@@QBEPBDXZ", "?GetSnapshotName@Widget@@MBEPBDXZ",
     "?GetSnapshotName@Widget@@MBEPBDXZ"),                                  # full mangled, access chosen
    ("?is@Rva4@@QBE_NXZ", "?isConnected@Widget@@UAE_NXZ",
     "?isConnected@Widget@@UAE_NXZ"),                                       # `this` cv follows the class
    ("?rva0029AA62@Rva0029AA3F@@QAEXPBUCoord3D@@@Z", "slot49",
     "?slot49@Widget@@UAEXPBUCoord3D@@@Z"),                                 # a digit inside an identifier
    ("?get@Rva5@@QAE?AW4ObjectID@@XZ", "get", "?get@Widget@@UAE?AW4ObjectID@@XZ"),    # an enum's W4
    ("?set@Rva6@@QAEXV?$BitFlags@$0HF@@@@Z", "set",
     "?set@Widget@@UAEXV?$BitFlags@$0HF@@@@Z"),                             # an encoded template number
])
def test_to_class_symbol(old, new, expected):
    assert rename.to_class_symbol(old, "Widget", new) == expected


@pytest.mark.parametrize("old,new", [
    ("?name@Rva2Named@@QBEPBDXZ", "?name@Widget@@UBEPBEXZ"),     # return type changed
    ("?name@Rva2Named@@QBEPBDXZ", "?name@Widget@@UBGPBDXZ"),     # convention changed
    ("?name@Rva2Named@@QBEPBDXZ", "?name@Widget@@QBEPBDXZ"),     # not virtual
    ("?name@Rva2Named@@QBEPBDXZ", "?name@Gadget@@UBEPBDXZ"),     # another class
    ("?f@Rva3@@QAEXPAV1@@Z", "f"),                               # back-reference in the parameters
    ("?f@Rva3@@QAEXPAV0@@Z", "f"),                               # name back-reference to the identifier
    ("?f@Rva3@@QAEXPAUCoord3D@@0@Z", "f"),                       # argument-type back-reference
    ("?f@Rva3@@QAEXPAVWidget@@@Z", "f"),                         # the new class is already spelled
    ("?f@Rva3@@QAEXPAVspin@@@Z", "spin"),                        # the new identifier is already spelled
])
def test_to_class_symbol_refusals(old, new):
    with pytest.raises(Refusal):
        rename.to_class_symbol(old, "Widget", new)


def test_back_references_read_positions_not_digits():
    names, types, spans = rename.back_references("?rva0029AA62@Rva0029AA3F@@QAEXPBUCoord3D@@@Z")
    assert (names, types) == ([], [])
    assert "Coord3D" in {"?rva0029AA62@Rva0029AA3F@@QAEXPBUCoord3D@@@Z"[a:b] for a, b in spans}
    assert rename.back_references("?f@Rva3@@QAEXPAV1@@Z")[:2] == ([1], [])
    assert rename.back_references("?f@Rva3@@QAEXPAUCoord3D@@0@Z")[:2] == ([], [0])


# ------------------------------------------------------------ evidence

def test_accepts_the_evidenced_case_and_applies(tree, monkeypatch):
    retail(monkeypatch, GOOD)
    p = plan(tree, evidence="ZH declaration order")
    assert p.new == NEW and p.basis == "to-class"
    assert "retail table 0x00C00000 slot 1, installed by ??0Widget@@QAE@XZ at 0x00402000" in p.evidence
    assert p.evidence.endswith("; ZH declaration order")
    assert p.to_class["slot"] == 1 and p.to_class["sources"] == ["Code/Game/Widget.cpp"]
    assert p.verify == ["Code/Game/Bits.cpp", "Code/Game/Widget.cpp"]
    assert p.subject() == f"Move {OLD} into Widget as {NEW} (retail vftable 0x00C00000 slot 1)"
    seen = []
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: seen.append(sources) or True)
    assert seen == [p.verify]
    bits = (tree / "Code/Game/Bits.cpp").read_text()
    assert "void Widget::spin() {}" in bits and f"// {NEW} @ 0x00401000" in bits
    functions = (tree / "reverse/functions.csv").read_text()
    assert f"{NEW},,0x00401000,40," in functions
    assert f"__ehhandler${NEW},,0x00790000," in functions and f"parent={NEW}" in functions
    assert OLD not in functions
    assert f"{NEW},0x00401000,pin" in (tree / "reverse/symbols.csv").read_text()
    deleted = (tree / "reverse/deleted_rows.csv").read_text()
    assert deleted.startswith(DELETED)
    assert (f'{OLD},0x00401000,"Renamed to {NEW} by tools/rename.py (to-class: retail vftable 0x00C00000 '
            'slot 1)"\n') in deleted
    assert not (tree / "reverse/name_basis.csv").exists()


def test_refuses_a_missing_slot(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00403040, 0x00409000, 0x00404000], {CTOR_STORE: 0})})
    with pytest.raises(Refusal, match="no retail vftable slot holds 0x00401000"):
        plan(tree)


def test_refuses_a_wrong_slot(tree, monkeypatch):
    # retail holds the address in slot 2, where Widget declares stop()
    retail(monkeypatch, {TABLE: ([0x00403040, 0x00404000, 0x00401000], {CTOR_STORE: 0})},
           compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, NEW, STOP]}})
    with pytest.raises(Refusal, match="does not prove the slot"):
        plan(tree)


def test_refuses_without_a_constructor_install(tree, monkeypatch):
    # the only table holding it is installed by the unrelated Other ctor
    retail(monkeypatch, {TABLE: ([0x00403040, 0x00401000, 0x00404000], {OTHER_STORE: 0})})
    with pytest.raises(Refusal, match="no constructor, destructor or deleting destructor row of Widget"):
        plan(tree)


def test_refuses_a_table_shared_with_an_unrelated_class(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00403040, 0x00401000, 0x00404000], {CTOR_STORE: 0}),
                         0x00810000: ([0x00401000], {OTHER_STORE: 0})})
    with pytest.raises(Refusal, match="unrelated to Widget"):
        plan(tree)


# Retail slot 2 holds THUNK, a 5-byte `jmp` that is the class's own empty
# override of stop() tail-calling the base body Widget's view inherits
# (0x00404000, STOP's row): retail 0x00497805 `jmp 0x0058B03E` in the
# UpdateModule tables (re_attempts 0x004B0876).
THUNK = 0x00406005
THUNKED = {TABLE: ([0x00403040, 0x00401000, THUNK], {CTOR_STORE: 0})}


def test_accepts_a_slot_reaching_the_same_body_through_one_jump(tree, monkeypatch):
    retail(monkeypatch, THUNKED, jumps={THUNK: 0x00404000})
    p = plan(tree)
    assert p.new == NEW and p.to_class["slot"] == 1


def test_accepts_both_sides_jumping_to_one_body(tree, monkeypatch):
    # STOP's row is itself a `jmp` to the body retail's thunk reaches
    retail(monkeypatch, THUNKED, jumps={THUNK: 0x00409000, 0x00404000: 0x00409000})
    assert plan(tree).new == NEW


def test_refuses_a_slot_jumping_to_a_different_body(tree, monkeypatch):
    # the thunk lands on another body: slot 2 is not the stop() Widget declares
    retail(monkeypatch, THUNKED, jumps={THUNK: 0x00409000})
    with pytest.raises(Refusal, match=r"does not prove the slot.*1 differ"):
        plan(tree)


def test_refuses_a_slot_reached_only_through_two_jumps(tree, monkeypatch):
    # one hop on each side only: THUNK -> 0x00406010 -> STOP proves nothing
    retail(monkeypatch, THUNKED, jumps={THUNK: 0x00406010, 0x00406010: 0x00404000})
    with pytest.raises(Refusal, match=r"does not prove the slot.*1 differ"):
        plan(tree)


def test_a_jump_never_moves_the_slot_itself(tree, monkeypatch):
    # retail slot 1 is a jmp to the placeholder's body, but the move's own
    # slot is found by exact address only: no retail slot holds 0x00401000
    retail(monkeypatch, {TABLE: ([0x00403040, THUNK, 0x00404000], {CTOR_STORE: 0})},
           jumps={THUNK: 0x00401000})
    with pytest.raises(Refusal, match="no retail vftable slot holds 0x00401000"):
        plan(tree)


@pytest.mark.parametrize("ours,theirs,jumps,same", [
    (0x10, 0x10, {}, True),
    (0x10, 0x20, {}, False),
    (0x10, 0x20, {0x20: 0x10}, True),                 # retail's word jumps to ours
    (0x10, 0x20, {0x10: 0x20}, True),                 # ours jumps to retail's word
    (0x10, 0x20, {0x10: 0x30, 0x20: 0x30}, True),     # both jump to one body
    (0x10, 0x20, {0x10: 0x30, 0x20: 0x40}, False),    # two jumps, two bodies
    (0x10, 0x20, {0x20: 0x30, 0x30: 0x10}, False),    # a chain: one hop only
])
def test_same_slot_body(monkeypatch, ours, theirs, jumps, same):
    monkeypatch.setattr(rename, "retail_jump", lambda ctx, rva: jumps.get(rva))
    assert rename.same_slot_body(None, ours, theirs) is same


def test_retail_jump_reads_one_bounded_e9(monkeypatch):
    import struct
    import build
    text = {"name": ".text", "rva": 0x1000, "size": 0x100, "raw_size": 0x100, "raw_pointer": 0}
    image = bytearray(b"\xcc" * 0x100)
    image[0x10:0x15] = b"\xe9" + struct.pack("<i", 0x40 - 0x15)       # 0x1010: jmp 0x1040
    image[0x20:0x25] = b"\xe9" + struct.pack("<i", 0x10000)           # 0x1020: jmp out of .text
    image[0x30:0x35] = b"\xe8" + struct.pack("<i", 0)                 # 0x1030: a call, not a jmp
    monkeypatch.setattr(build, "exe_image", lambda: (bytes(image), [text]))

    class Ctx:
        _cache = {}
    assert rename.retail_jump(Ctx, 0x1010) == 0x1040
    assert rename.retail_jump(Ctx, 0x1020) is None
    assert rename.retail_jump(Ctx, 0x1030) is None
    assert rename.retail_jump(Ctx, 0x0FFF) is None                   # outside .text


# An installer unit that stores the real table through an external reference
# (BloodthirstyUpdateCtor.cpp: extern ??_7BloodthirstyUpdate@@6BObjectModule@@@)
# defines no copy of it; the Dtor unit's copy is the one judged.
CTOR_UNIT = "Code/Game/WidgetCtor.cpp"


def slot_check(sources):
    return {"cls": "Widget", "table": TABLE, "slot": 1, "new": NEW,
            "retail": [0x00403040, 0x00401000, 0x00404000], "sources": sources}


def objects(monkeypatch, compiled, external):
    monkeypatch.setattr(rename, "compiled_vtables", lambda ctx, rel, current=True: compiled.get(rel))
    monkeypatch.setattr(rename, "external_vtables", lambda ctx, rel, current=True: external.get(rel))
    monkeypatch.setattr(rename, "retail_jump", lambda ctx, rva: None)


@pytest.mark.parametrize("current", [True, False])
def test_an_installer_referencing_the_table_another_unit_defines_is_passed_over(tree, monkeypatch, current):
    objects(monkeypatch, {"Code/Game/Widget.cpp": COMPILED, CTOR_UNIT: {}},
            {"Code/Game/Widget.cpp": set(), CTOR_UNIT: {"??_7Widget@@6B@"}})
    problems = rename.to_class_slot_problems(ctx_of(tree), slot_check(["Code/Game/Widget.cpp", CTOR_UNIT]),
                                             current=current)
    assert problems == []


def test_an_installer_with_no_table_at_all_still_refuses(tree, monkeypatch):
    # a dummy-vptr constructor (`&s_vtable`) neither defines nor references ??_7Widget
    objects(monkeypatch, {"Code/Game/Widget.cpp": COMPILED, CTOR_UNIT: {}},
            {"Code/Game/Widget.cpp": set(), CTOR_UNIT: {"??_7Other@@6B@"}})
    problems = rename.to_class_slot_problems(ctx_of(tree), slot_check(["Code/Game/Widget.cpp", CTOR_UNIT]),
                                             current=False)
    assert problems == [f"{CTOR_UNIT} compiles no Widget vftable that matches retail table 0x00C00000 "
                        "(no ??_7Widget at all)"]


def test_only_referencing_installers_prove_nothing_after_the_build(tree, monkeypatch):
    objects(monkeypatch, {CTOR_UNIT: {}}, {CTOR_UNIT: {"??_7Widget@@6B@"}})
    assert rename.to_class_slot_problems(ctx_of(tree), slot_check([CTOR_UNIT]), current=True) == []
    problems = rename.to_class_slot_problems(ctx_of(tree), slot_check([CTOR_UNIT]), current=False)
    assert problems == [f"no installer of Widget compiles its vftable ({CTOR_UNIT} only reference it)"]


def test_a_referencing_installer_does_not_excuse_a_wrong_copy(tree, monkeypatch):
    objects(monkeypatch, {"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, STOP, NEW]}, CTOR_UNIT: {}},
            {"Code/Game/Widget.cpp": set(), CTOR_UNIT: {"??_7Widget@@6B@"}})
    problems = rename.to_class_slot_problems(ctx_of(tree), slot_check(["Code/Game/Widget.cpp", CTOR_UNIT]),
                                             current=False)
    assert problems == [f"Code/Game/Widget.cpp's ??_7Widget@@6B@ slot 1 names {STOP}, not {NEW} "
                        "(it sits in slot 2: the declared virtual order differs from retail's)"]


def test_refuses_a_readable_source_class(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00403040, 0x00405000, 0x00404000], {CTOR_STORE: 0})})
    with pytest.raises(Refusal, match="readable name"):
        plan(tree, rva=0x00405000, prepared=False)


def test_rebuilt_vftable_must_name_the_slot(tree, monkeypatch):
    """A prepared view compiled into a table that names another symbol in
    the slot fails after ./build.sh: every file comes back."""
    retail(monkeypatch, GOOD, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, STOP, NEW]}})
    before = {p.relative_to(tree).as_posix(): p.read_bytes()
              for p in tree.rglob("*") if p.is_file() and ".git" not in p.parts}
    # planning skips nothing here (the installer is not prepared), so it refuses early
    with pytest.raises(Refusal, match="slot 1 names"):
        plan(tree)
    p = None
    retail(monkeypatch, GOOD)
    p = plan(tree)
    retail(monkeypatch, GOOD, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, STOP, NEW]}})
    with pytest.raises(VerifyFailed, match="rebuilt vftable"):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    after = {p.relative_to(tree).as_posix(): p.read_bytes()
             for p in tree.rglob("*") if p.is_file() and ".git" not in p.parts}
    assert after == before


def test_cli_wiring(tree, monkeypatch):
    retail(monkeypatch, GOOD)
    prepared = tree / "prepared.cpp"
    prepared.write_text(BITS_PREPARED)
    assert rename.main(["function", "--rva", "0x00401000", "--to-class", "Widget", "--new", "spin",
                        "--prepared", f"Code/Game/Bits.cpp={prepared}", "--root", str(tree),
                        "--no-claim", "--no-object-scan", "--dry-run"]) == 0
    with pytest.raises(SystemExit):        # no --basis with --to-class
        rename.main(["function", "--rva", "0x00401000", "--to-class", "Widget", "--new", "spin",
                     "--basis", "inferred", "--root", str(tree), "--no-claim", "--dry-run"])
    with pytest.raises(SystemExit):        # --prepared only with --to-class
        rename.main(["function", "--rva", "0x00401000", "--new", "spin", "--basis", "inferred",
                     "--evidence", "x", "--prepared", f"Code/Game/Bits.cpp={prepared}", "--root", str(tree),
                     "--no-claim", "--dry-run"])


# ------------------------------------------------------------ an int-return placeholder override
#
# ObjectWeaponStatusHelper's update 0x0028F976 was rowed ?update@Rva0028F976@@UAEHXZ
# with a guessed int return; UpdateModuleInterface::update (registered,
# UpdateModule.h) returns the int-sized enum UpdateSleepTime, and C++ forbids
# an int override of it (re_attempts 0x0028F976, 0x0049520B, 0x004BF8DF). The
# move may respell the return type only as the registered header declares it.
SLEEP_OLD = "?update@Rva00401100@@UAEHXZ"
SLEEP_NEW = "?update@Widget@@UAE?AW4Sleep@@XZ"
SLEEP_TABLE = 0x00800100
SLEEP_STORE = 0x00402020    # inside the Widget ctor row: mov dword ptr [ecx+0x10], SLEEP_TABLE
UPDATE_H = """enum Sleep;
class UpdateIface
{
public:
    virtual Sleep update() = 0;
};
"""
SLEEP_BITS = f"""// cl: /O2
// {SLEEP_OLD} @ 0x00401100
class Rva00401100 {{ public: virtual int update(); }};
int Rva00401100::update() {{ return 1; }}
"""
SLEEP_PREPARED = f"""// cl: /O2
// {SLEEP_OLD} @ 0x00401100
#include "Update.h"
enum Sleep {{ SLEEP_NONE = 1 }};
class Widget : public UpdateIface {{ public: virtual Sleep update(); }};
Sleep Widget::update() {{ return SLEEP_NONE; }}
"""
SLEEP_WIDGET = '#include "Update.h"\n' + WIDGET.replace("class Widget {", "class Widget : public UpdateIface {")
SLEEP_TABLES = {**GOOD, SLEEP_TABLE: ([0x00401100, 0x00404000], {SLEEP_STORE: 0x10})}
SLEEP_COMPILED = {"Code/Game/Widget.cpp": dict(COMPILED, **{"??_7Widget@@6BUpdateIface@@@": [SLEEP_NEW, STOP]})}


def sleep_tree(root, *, registered=True, header=UPDATE_H, widget=SLEEP_WIDGET):
    files = {
        "reverse/functions.csv": FUNCTIONS + f"{SLEEP_OLD},,0x00401100,12,Code/Game/SleepBits.cpp,matched,int\n",
        "reverse/canonical_classes.csv": "class,header,notes\n" +
                                         ("UpdateIface,Code/Game/Update.h,registered\n" if registered else ""),
        "Code/Game/Update.h": header,
        "Code/Game/Widget.cpp": widget,
        "Code/Game/SleepBits.cpp": SLEEP_BITS,
    }
    for rel, text in files.items():
        (root / rel).parent.mkdir(parents=True, exist_ok=True)
        (root / rel).write_bytes(text.encode("utf-8"))
    _git(root, "-c", "user.name=t", "-c", "user.email=t@t", "add", "-A")
    _git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "sleep")
    return root


def sleep_plan(root, new=SLEEP_NEW):
    return rename.plan_rename("function", ctx=ctx_of(root), rva=0x00401100, to_class="Widget", new=new,
                              prepared={"Code/Game/SleepBits.cpp": SLEEP_PREPARED.encode()})


@pytest.mark.parametrize("tail,new_tail,enum", [
    ("AEHXZ", "AE?AW4Sleep@@XZ", "Sleep"),
    ("BEHXZ", "BE?AW4ObjectID@@XZ", "ObjectID"),           # const kept
    ("AEHH@Z", "AE?AW4Sleep@@H@Z", "Sleep"),                # parameters kept
    ("AEHXZ", "BE?AW4Sleep@@XZ", None),                     # cv changed too
    ("AE_NXZ", "AE?AW4Sleep@@XZ", None),                    # not an int return
    ("AEIXZ", "AE?AW4Sleep@@XZ", None),                     # unsigned is no int
    ("AEHXZ", "AE?AW4Sleep@@H@Z", None),                    # parameters changed
    ("AEHXZ", "AE?AW4Sleep@NS@@XZ", None),                  # a scoped enum is not read
    ("AEHXZ", "AE?AVSleep@@XZ", None),                      # a class return
    ("AGHXZ", "AG?AW4Sleep@@XZ", None),                     # not thiscall
])
def test_enum_return_respelling(tail, new_tail, enum):
    assert rename.enum_return_respelling(tail, new_tail) == enum


def test_to_class_symbol_respells_an_int_return_only_with_the_declared_enum():
    assert rename.to_class_symbol(SLEEP_OLD, "Widget", SLEEP_NEW, return_enum="Sleep") == SLEEP_NEW
    with pytest.raises(Refusal, match="changes the convention, return type or parameters"):
        rename.to_class_symbol(SLEEP_OLD, "Widget", SLEEP_NEW)
    with pytest.raises(Refusal, match="changes the convention, return type or parameters"):
        rename.to_class_symbol(SLEEP_OLD, "Widget", SLEEP_NEW, return_enum="Other")
    with pytest.raises(Refusal, match="changes the convention, return type or parameters"):
        rename.to_class_symbol(SLEEP_OLD, "Widget", "?update@Widget@@UAE?AW4Sleep@@H@Z", return_enum="Sleep")
    # the enum would be a back-reference when a parameter spells it again
    with pytest.raises(Refusal, match="back-reference"):
        rename.to_class_symbol("?f@Rva7@@QAEHW4Sleep@@@Z", "Widget", "?f@Widget@@UAE?AW4Sleep@@W4Sleep@@@Z",
                               return_enum="Sleep")
    with pytest.raises(Refusal, match="back-reference"):
        rename.to_class_symbol("?f@Rva7@@QAEHXZ", "Widget", "?f@Widget@@UAE?AW4Widget@@XZ", return_enum="Widget")


def test_an_int_return_takes_the_enum_its_registered_base_declares(tree, monkeypatch):
    retail(monkeypatch, SLEEP_TABLES, compiled=SLEEP_COMPILED)
    root = sleep_tree(tree)
    p = sleep_plan(root)
    assert p.new == SLEEP_NEW and p.to_class["slot"] == 0 and p.to_class["table"] == SLEEP_TABLE
    assert ("return type: UpdateIface (registered, Code/Game/Update.h) declares virtual Sleep update()"
            in p.evidence)
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    functions = (root / "reverse/functions.csv").read_text()
    assert f"{SLEEP_NEW},,0x00401100,12,Code/Game/SleepBits.cpp," in functions and SLEEP_OLD not in functions
    deleted = (root / "reverse/deleted_rows.csv").read_text()
    assert (f'{SLEEP_OLD},0x00401100,"Renamed to {SLEEP_NEW} by tools/rename.py (to-class: retail vftable '
            "0x00C00100 slot 0; return type: UpdateIface (registered, Code/Game/Update.h) declares virtual "
            'Sleep update())"') in deleted


def test_an_int_return_is_kept_without_a_registered_declaration(tree, monkeypatch):
    retail(monkeypatch, SLEEP_TABLES, compiled=SLEEP_COMPILED)
    root = sleep_tree(tree, registered=False)
    with pytest.raises(Refusal, match="no class registered in reverse/canonical_classes.csv"):
        sleep_plan(root)


def test_an_int_return_needs_the_registered_virtual_to_return_that_enum(tree, monkeypatch):
    retail(monkeypatch, SLEEP_TABLES, compiled=SLEEP_COMPILED)
    root = sleep_tree(tree, header=UPDATE_H.replace("virtual Sleep update()", "virtual Other update()"))
    with pytest.raises(Refusal, match="no class registered"):
        sleep_plan(root)


def test_an_int_return_needs_a_virtual_declaration(tree, monkeypatch):
    retail(monkeypatch, SLEEP_TABLES, compiled=SLEEP_COMPILED)
    root = sleep_tree(tree, header=UPDATE_H.replace("virtual Sleep update() = 0;", "Sleep update();"))
    with pytest.raises(Refusal, match="no class registered"):
        sleep_plan(root)


def test_an_int_return_needs_the_declaration_in_a_base_of_the_class(tree, monkeypatch):
    # the registered header declares it, but Widget's views do not derive from it
    retail(monkeypatch, SLEEP_TABLES, compiled=SLEEP_COMPILED)
    root = sleep_tree(tree, widget='#include "Update.h"\n' + WIDGET)
    with pytest.raises(Refusal, match="no class registered"):
        sleep_plan(root)


def test_an_int_return_respelling_still_needs_the_compiled_slot(tree, monkeypatch):
    # the installer's table names the int spelling: the move is refused as any other
    wrong = {"Code/Game/Widget.cpp": dict(COMPILED, **{"??_7Widget@@6BUpdateIface@@@":
                                                      ["?update@Widget@@UAEHXZ", STOP]})}
    retail(monkeypatch, SLEEP_TABLES, compiled=wrong)
    root = sleep_tree(tree)
    with pytest.raises(Refusal, match=r"slot 0 names \?update@Widget@@UAEHXZ"):
        sleep_plan(root)


# ------------------------------------------------------------ a batch: the slots of one table
#
# Rva005C44A3's table 0x00C745D4 (ctor 0x005C44A3) holds 0x005C4537 (an ICF-shared
# deleting destructor), 0x005C44DF, 0x005C44C3 and 0x005C4352, each rowed under a
# different placeholder (re_attempts 0x005C44DF): no slot resolves to a row of the
# class yet, so a single move never shows an agreeing slot. --also moves them in
# one plan, each judged by the others.
B_A = OLD
B_B = "?getName@Rva00401100@@UBEPBDXZ"
B_C = "?rva00401200@Rva00401200@@QAEXH@Z"
N_A, N_B, N_C = "?create@Widget@@UAEXXZ", "?getName@Widget@@UBEPBDXZ", "?parse@Widget@@UAEXH@Z"
B_GDTOR = "??_EWidget@@UAEPAXI@Z"     # the compiler's own, no row (retail's slot 0 is ICF-shared)
B_TABLE = {TABLE: ([0x00406000, 0x00401000, 0x00401100, 0x00401200], {CTOR_STORE: 0})}
B_COMPILED = {"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [B_GDTOR, N_A, N_B, N_C]}}
B_SOURCES = {
    "Code/Game/Bits.cpp": (BITS, "class Widget { public: virtual void create(); };\nvoid Widget::create() {}\n"),
    "Code/Game/Names.cpp": ("class Rva00401100 { public: virtual const char *getName() const; };\n"
                            "const char *Rva00401100::getName() const { return \"w\"; }\n",
                            "class Widget { public: virtual const char *getName() const; };\n"
                            "const char *Widget::getName() const { return \"w\"; }\n"),
    "Code/Game/Parse.cpp": ("class Rva00401200 { public: void rva00401200(int); };\n"
                            "void Rva00401200::rva00401200(int) {}\n",
                            "class Widget { public: virtual void parse(int); };\nvoid Widget::parse(int) {}\n"),
}


def batch_tree(root):
    rows = FUNCTIONS + (f"{B_B},,0x00401100,8,Code/Game/Names.cpp,matched,name getter\n"
                        f"{B_C},,0x00401200,12,Code/Game/Parse.cpp,matched,field parse\n"
                        "??_GShared@@UAEPAXI@Z,,0x00406000,28,Code/Game/Gadget.cpp,matched,ICF-shared\n")
    (root / "reverse/functions.csv").write_bytes(rows.encode())
    for rel, (text, _prepared) in B_SOURCES.items():
        (root / rel).write_bytes(text.encode())
    _git(root, "-c", "user.name=t", "-c", "user.email=t@t", "add", "-A")
    _git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "batch")
    return root


def batch_plan(root, also=((0x00401100, N_B), (0x00401200, N_C))):
    return rename.plan_rename("function", ctx=ctx_of(root), rva=0x00401000, to_class="Widget", new=N_A,
                              prepared={rel: p.encode() for rel, (_t, p) in B_SOURCES.items()}, also=list(also))


def test_a_lone_slot_of_an_unresolved_table_is_refused(tree, monkeypatch):
    retail(monkeypatch, B_TABLE, compiled=B_COMPILED)
    root = batch_tree(tree)
    with pytest.raises(Refusal, match=r"0 slot\(s\) agree, 0 differ"):
        batch_plan(root, also=())


def test_a_batch_moves_the_slots_of_one_table(tree, monkeypatch):
    retail(monkeypatch, B_TABLE, compiled=B_COMPILED)
    root = batch_tree(tree)
    p = batch_plan(root)
    assert p.to_class["slots"] == {1: N_A, 2: N_B, 3: N_C}
    assert p.subject() == "Move 3 members into Widget (retail vftable 0x00C00000 slots 1, 2, 3)"
    assert f"{B_B} -> {N_B}: retail table 0x00C00000 slot 2, installed by ??0Widget@@QAE@XZ" in p.evidence
    assert set(p.claims) >= {0x00401000, 0x00401100, 0x00401200}
    seen = []
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: seen.append(sources) or True)
    assert set(seen[0]) >= {"Code/Game/Bits.cpp", "Code/Game/Names.cpp", "Code/Game/Parse.cpp",
                            "Code/Game/Widget.cpp"}
    functions = (root / "reverse/functions.csv").read_text()
    for old, new in ((B_A, N_A), (B_B, N_B), (B_C, N_C)):
        assert old not in functions and new in functions
    assert f"__ehhandler${N_A},,0x00790000," in functions
    deleted = (root / "reverse/deleted_rows.csv").read_text().splitlines()
    for old, at, slot in ((B_A, "0x00401000", 1), (B_B, "0x00401100", 2), (B_C, "0x00401200", 3)):
        assert [line for line in deleted if line.startswith(f"{old},{at},")][0].endswith(f"slot {slot})\"")


def test_a_batch_refuses_swapped_slots(tree, monkeypatch):
    retail(monkeypatch, B_TABLE, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [B_GDTOR, N_A, N_C, N_B]}})
    root = batch_tree(tree)
    with pytest.raises(Refusal, match="differ"):
        batch_plan(root)


def test_a_batch_refuses_a_slot_the_class_declares_elsewhere(tree, monkeypatch):
    # two moved slots agree, but the third name is not where retail holds its row
    retail(monkeypatch, B_TABLE, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@":
                                                                    [B_GDTOR, N_A, N_B, "?other@Widget@@UAEXXZ"]}})
    root = batch_tree(tree)
    with pytest.raises(Refusal, match=r"slot 3 names \?other@Widget@@UAEXXZ"):
        batch_plan(root)


def test_a_batch_stays_in_one_table(tree, monkeypatch):
    tables = {TABLE: ([0x00406000, 0x00401000, 0x00401100], {CTOR_STORE: 0}),
              0x00800100: ([0x00401200], {0x00402020: 0x10})}
    retail(monkeypatch, tables, compiled=B_COMPILED)
    root = batch_tree(tree)
    with pytest.raises(Refusal, match="slots of one retail table"):
        batch_plan(root)


def test_a_batch_names_each_address_once(tree, monkeypatch):
    retail(monkeypatch, B_TABLE, compiled=B_COMPILED)
    root = batch_tree(tree)
    with pytest.raises(Refusal, match="names one address twice"):
        batch_plan(root, also=((0x00401000, "create2"),))


def test_a_batch_still_refuses_a_shared_body(tree, monkeypatch):
    # every member must pass the single move's checks: a pinned second name on
    # 0x00401200 makes it a shared body, and the whole batch is refused
    retail(monkeypatch, B_TABLE, compiled=B_COMPILED)
    root = batch_tree(tree)
    (root / "reverse/symbols.csv").write_bytes((SYMBOLS + "?twin@Rva00409999@@QAEXH@Z,0x00401200,fold\n").encode())
    with pytest.raises(Refusal, match="0x00401200 is a shared body"):
        batch_plan(root)


def test_a_batch_rebuilt_wrong_restores_everything(tree, monkeypatch):
    retail(monkeypatch, B_TABLE, compiled=B_COMPILED)
    root = batch_tree(tree)
    before = {q.relative_to(root).as_posix(): q.read_bytes()
              for q in root.rglob("*") if q.is_file() and ".git" not in q.parts}
    p = batch_plan(root)
    retail(monkeypatch, B_TABLE, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [B_GDTOR, N_A, N_C, N_B]}})
    with pytest.raises(VerifyFailed, match="rebuilt vftable"):
        rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    after = {q.relative_to(root).as_posix(): q.read_bytes()
             for q in root.rglob("*") if q.is_file() and ".git" not in q.parts}
    assert after == before


def test_cli_also_wiring(tree, monkeypatch, capsys):
    retail(monkeypatch, B_TABLE, compiled=B_COMPILED)
    root = batch_tree(tree)
    argv = ["function", "--rva", "0x00401000", "--to-class", "Widget", "--new", N_A,
            "--also", f"0x00401100={N_B}", "--also", f"0x00401200={N_C}"]
    for rel, (_text, prepared) in B_SOURCES.items():
        path = root.parent / (root.name + "-" + rel.rsplit("/", 1)[1] + ".prepared")
        path.write_bytes(prepared.encode())
        argv += ["--prepared", f"{rel}={path}"]
    assert rename.main(argv + ["--root", str(root), "--no-claim", "--no-object-scan", "--dry-run"]) == 0
    assert "Move 3 members into Widget" in capsys.readouterr().out
    with pytest.raises(SystemExit):        # --also only with --to-class
        rename.main(["function", "--rva", "0x00401000", "--new", "spin", "--basis", "inferred", "--evidence", "x",
                     "--also", f"0x00401100={N_B}", "--root", str(root), "--no-claim", "--dry-run"])
    with pytest.raises(SystemExit):        # not RVA=NEW
        rename.main(["function", "--rva", "0x00401000", "--to-class", "Widget", "--new", N_A,
                     "--also", "nothex", "--root", str(root), "--no-claim", "--dry-run"])


def test_an_int_return_reads_a_prepared_installers_bases(tree, monkeypatch):
    # the installer comes prepared onto the registered base: its prepared
    # bytes, not the tree's, decide which class declares the slot
    retail(monkeypatch, SLEEP_TABLES, compiled=SLEEP_COMPILED)
    root = sleep_tree(tree, widget='#include "Update.h"\n' + WIDGET)
    p = rename.plan_rename("function", ctx=ctx_of(root), rva=0x00401100, to_class="Widget", new=SLEEP_NEW,
                           prepared={"Code/Game/SleepBits.cpp": SLEEP_PREPARED.encode(),
                                     "Code/Game/Widget.cpp": SLEEP_WIDGET.encode()})
    assert "declares virtual Sleep update()" in p.evidence
    root2 = sleep_tree(tree)
    with pytest.raises(Refusal, match="no class registered"):
        rename.plan_rename("function", ctx=ctx_of(root2), rva=0x00401100, to_class="Widget", new=SLEEP_NEW,
                           prepared={"Code/Game/SleepBits.cpp": SLEEP_PREPARED.encode(),
                                     "Code/Game/Widget.cpp": ('#include "Update.h"\n' + WIDGET).encode()})


# ------------------------------------------------------------ a stand-in installer
#
# ObjectWeaponStatusHelper's destructor 0x004DF8A9 (Rva004DF7C2Derived.cpp, a
# scaffold whose view keeps placeholder bases) installs the class's tables in
# retail too, but compiles one-slot stand-ins under base names no constructor
# table uses (`??_7ObjectWeaponStatusHelper@@6BRva004DF8A9_B2@@@` = [f2]): no
# slot resolves, so there is nothing to agree or clash with, and no COMDAT
# competes with the constructor unit's real copies.
SCAFFOLD = "Code/Game/WidgetScaffold.cpp"
STANDIN = {"??_7Widget@@6BRva1_B2@@@": ["?f2@Rva1_B2@@UAEXXZ"], "??_7Widget@@6BBase@@@": ["??_EWidget@@UAEPAXI@Z"]}


@pytest.mark.parametrize("current", [True, False])
def test_a_stand_in_installer_is_passed_over(tree, monkeypatch, current):
    objects(monkeypatch, {"Code/Game/Widget.cpp": COMPILED, SCAFFOLD: STANDIN},
            {"Code/Game/Widget.cpp": set(), SCAFFOLD: set()})
    assert rename.to_class_slot_problems(ctx_of(tree), slot_check(["Code/Game/Widget.cpp", SCAFFOLD]),
                                         current=current) == []


def test_stand_in_installers_alone_prove_nothing_after_the_build(tree, monkeypatch):
    objects(monkeypatch, {SCAFFOLD: STANDIN}, {SCAFFOLD: set()})
    assert rename.to_class_slot_problems(ctx_of(tree), slot_check([SCAFFOLD]), current=True) == []
    assert rename.to_class_slot_problems(ctx_of(tree), slot_check([SCAFFOLD]), current=False) == [
        f"no installer of Widget compiles its vftable ({SCAFFOLD} only reference it or compile stand-in copies)"]


def test_a_stand_in_sharing_a_table_name_with_the_proof_is_refused(tree, monkeypatch):
    # an unresolved copy of the very table the constructor unit compiles: two
    # different COMDAT copies of one ??_7, so it is judged and refused
    objects(monkeypatch, {"Code/Game/Widget.cpp": COMPILED,
                          SCAFFOLD: {"??_7Widget@@6B@": ["??_EWidget@@UAEPAXI@Z", "?x@Rva1@@UAEXXZ"]}},
            {"Code/Game/Widget.cpp": set(), SCAFFOLD: set()})
    problems = rename.to_class_slot_problems(ctx_of(tree), slot_check(["Code/Game/Widget.cpp", SCAFFOLD]),
                                             current=False)
    assert problems and problems[0].startswith(f"{SCAFFOLD} compiles no Widget vftable that matches") \
        and "another installer compiles that table too" in problems[0]


@pytest.mark.parametrize("copy", [
    {"??_7Widget@@6BRva1_B2@@@": [STOP]},              # a rowed name in the wrong slot: it clashes
    {"??_7Widget@@6BRva1_B2@@@": [GDTOR, STOP, NEW]},  # the moved name in another slot
    {"??_7Widget@@6BRva1_B2@@@": [NEW]},               # the moved name itself is no stand-in
])
def test_a_copy_naming_anything_resolvable_is_judged(tree, monkeypatch, copy):
    objects(monkeypatch, {"Code/Game/Widget.cpp": COMPILED, SCAFFOLD: copy},
            {"Code/Game/Widget.cpp": set(), SCAFFOLD: set()})
    problems = rename.to_class_slot_problems(ctx_of(tree), slot_check(["Code/Game/Widget.cpp", SCAFFOLD]),
                                             current=False)
    assert problems and problems[0].startswith(SCAFFOLD)


# ------------------------------------------------------------ a one-slot table

# Widget's ctor also installs a one-slot interface table at +4 (retail
# SpawnUnitBehavior's +0x20 table 0x00C59120, re_attempts 0x004B8851): its
# only slot holds the placeholder, so no other slot can agree with the move.
IFACE = 0x00810000
IFACE_STORE = 0x00402020    # inside the ctor row: mov dword ptr [ecx+4], IFACE
ONE_SLOT = {TABLE: ([0x00403040, 0x00409000, 0x00404000], {CTOR_STORE: 0}),
            IFACE: ([0x00401000], {IFACE_STORE: 4})}
OTHER_SLOT = "?other@Widget@@UAEXXZ"


def one_slot(compiled_iface):
    return {"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, OTHER_SLOT, STOP],
                                     "??_7Widget@@6BIface@@@": compiled_iface}}


def test_a_one_slot_table_proves_its_only_slot(tree, monkeypatch):
    retail(monkeypatch, ONE_SLOT, compiled=one_slot([NEW]))
    p = plan(tree)
    assert p.new == NEW and p.to_class["slot"] == 0 and p.to_class["retail"] == [0x00401000]
    assert "retail table 0x00C10000 slot 0, installed by ??0Widget@@QAE@XZ" in p.evidence
    assert rename.to_class_slot_problems(ctx_of(tree), p.to_class, current=False) == []


def test_a_one_slot_table_naming_another_symbol_is_refused(tree, monkeypatch):
    retail(monkeypatch, ONE_SLOT, compiled=one_slot([OTHER_SLOT]))
    with pytest.raises(Refusal, match=r"does not prove the slot.*0 slot\(s\) agree"):
        plan(tree)


def test_a_one_slot_retail_table_needs_a_one_slot_copy(tree, monkeypatch):
    # the compiled interface grew a second slot: not retail's one-slot table
    retail(monkeypatch, ONE_SLOT, compiled=one_slot([NEW, OTHER_SLOT]))
    with pytest.raises(Refusal, match=r"does not prove the slot.*0 slot\(s\) agree"):
        plan(tree)


def test_a_one_slot_copy_does_not_excuse_a_multi_slot_retail_table(tree, monkeypatch):
    # retail's table has a second, unresolved slot: the lone move stays refused
    tables = {**ONE_SLOT, IFACE: ([0x00401000, 0x0040A000], {IFACE_STORE: 4})}
    retail(monkeypatch, tables, compiled=one_slot([NEW]))
    with pytest.raises(Refusal, match=r"does not prove the slot.*0 slot\(s\) agree"):
        plan(tree)


def test_a_one_slot_table_rebuilt_wrong_restores_everything(tree, monkeypatch):
    retail(monkeypatch, ONE_SLOT, compiled=one_slot([NEW]))
    before = {p.relative_to(tree).as_posix(): p.read_bytes()
              for p in tree.rglob("*") if p.is_file() and ".git" not in p.parts}
    p = plan(tree)
    retail(monkeypatch, ONE_SLOT, compiled=one_slot([OTHER_SLOT]))
    with pytest.raises(VerifyFailed, match="rebuilt vftable"):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    after = {p.relative_to(tree).as_posix(): p.read_bytes()
             for p in tree.rglob("*") if p.is_file() and ".git" not in p.parts}
    assert after == before


# ------------------------------------------------------------ the method's local statics (P36, 0x005EFFA6)

STATIC = f"?table@?1?{OLD}@4PAUField@@A"
GUARD = f"?$S1@?1?{OLD}@4IA"
NEW_STATIC, NEW_GUARD = STATIC.replace(OLD, NEW), GUARD.replace(OLD, NEW)


def with_ledger(root, *rows):
    lines = ["address,size,section,kind,name,source,status,names,defs,refs"]
    lines += list(rows) or [f"0x00A00000,192,.data,global,{STATIC},Code/Game/Bits.cpp,owned,,1,1",
                            f"0x00A000C0,4,.data,global,{GUARD},Code/Game/Bits.cpp,owned,,1,1"]
    (root / "reverse/data_ledger.csv").write_bytes(("\n".join(lines) + "\n").encode("utf-8"))
    return root


def test_a_moved_methods_local_statics_move_with_it(tree, monkeypatch):
    with_ledger(tree)
    retail(monkeypatch, GOOD)
    p = plan(tree)
    ledger = p.after["reverse/data_ledger.csv"].decode()
    assert NEW_STATIC in ledger and NEW_GUARD in ledger and OLD not in ledger
    assert p.to_class["statics"] == {"Code/Game/Bits.cpp": {STATIC: NEW_STATIC, GUARD: NEW_GUARD}}
    monkeypatch.setattr(rename, "object_defined_symbols", lambda ctx, rel: {NEW_STATIC, NEW_GUARD})
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    assert NEW_STATIC in (tree / "reverse/data_ledger.csv").read_text()


@pytest.mark.parametrize("defined,why", [
    ({NEW_STATIC}, "does not define"),                          # the guard's name did not move
    ({NEW_STATIC, NEW_GUARD, STATIC}, "still defines"),         # the old one is still compiled
    (None, "has no object"),
])
def test_a_rebuilt_object_must_define_the_new_static_keys(tree, monkeypatch, defined, why):
    with_ledger(tree)
    retail(monkeypatch, GOOD)
    p = plan(tree)
    monkeypatch.setattr(rename, "object_defined_symbols", lambda ctx, rel: defined)
    with pytest.raises(VerifyFailed, match=why):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    assert STATIC in (tree / "reverse/data_ledger.csv").read_text()
    assert NEW_STATIC not in (tree / "reverse/data_ledger.csv").read_text()


def test_a_ledger_key_that_is_no_local_static_refuses(tree, monkeypatch):
    with_ledger(tree, f"0x00A00000,4,.data,global,?x@@3P6AXXZ{OLD},Code/Game/Bits.cpp,owned,{OLD},1,1")
    retail(monkeypatch, GOOD)
    with pytest.raises(Refusal, match="is no local static of it"):
        plan(tree)


def test_a_local_static_defined_elsewhere_refuses(tree, monkeypatch):
    with_ledger(tree, f"0x00A00000,192,.data,global,{STATIC},Code/Game/Other.cpp,owned,,1,1")
    retail(monkeypatch, GOOD)
    with pytest.raises(Refusal, match="is defined in Code/Game/Other.cpp"):
        plan(tree)


def test_a_baseline_key_still_refuses(tree, monkeypatch):
    with_ledger(tree)
    (tree / "reverse/data_check_baseline.txt").write_bytes((OLD + "\n").encode("utf-8"))
    _git(tree, "add", "-A")
    retail(monkeypatch, GOOD)
    with pytest.raises(Refusal, match="is a key in reverse/data_check_baseline.txt"):
        plan(tree)


def test_a_method_with_no_statics_leaves_the_ledger_alone(tree, monkeypatch):
    with_ledger(tree, "0x00A00000,4,.data,global,?g@@3HA,Code/Game/Bits.cpp,owned,,1,1")
    retail(monkeypatch, GOOD)
    p = plan(tree)
    assert "reverse/data_ledger.csv" not in p.after
    assert "statics" not in p.to_class


# ------------------------------------------------------------ a compiled ??_E against retail's ??_G row

VECTOR = "??_EWidget@@UAEPAXI@Z"
TWO_SLOTS = {TABLE: ([0x00403040, 0x00401000], {CTOR_STORE: 0})}


def test_a_compiled_e_agrees_with_retails_g_row_of_its_class(tree, monkeypatch):
    # P36's table: the deleting destructor and the moved slot, nothing else to agree with
    retail(monkeypatch, TWO_SLOTS, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [VECTOR, NEW]}})
    assert plan(tree).to_class["slot"] == 1


@pytest.mark.parametrize("slot_zero", [
    "??_EOther@@UAEPAXI@Z",             # another class's
    "??_EWidget@@QAEPAXI@Z",            # a different spelling: no ??_G row carries it
])
def test_an_e_that_is_not_this_classs_does_not_agree(tree, monkeypatch, slot_zero):
    retail(monkeypatch, TWO_SLOTS, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [slot_zero, NEW]}})
    with pytest.raises(Refusal, match="does not prove the slot"):
        plan(tree)


def test_an_e_does_not_agree_when_its_g_row_is_elsewhere(tree, monkeypatch):
    # retail's slot 0 holds some other body, not this class's ??_G row
    tables = {TABLE: ([0x00405000, 0x00401000], {CTOR_STORE: 0})}
    retail(monkeypatch, tables, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [VECTOR, NEW]}})
    with pytest.raises(Refusal, match="does not prove the slot"):
        plan(tree)


def test_an_e_with_its_own_row_is_judged_by_that_row(tree, monkeypatch):
    # a rowed ??_E elsewhere is a clash, whatever the ??_G row says
    functions = (tree / "reverse/functions.csv").read_text() + f"{VECTOR},,0x00405100,28,Code/Game/Widget.cpp,matched,\n"
    (tree / "reverse/functions.csv").write_text(functions)
    retail(monkeypatch, TWO_SLOTS, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [VECTOR, NEW]}})
    with pytest.raises(Refusal, match="does not prove the slot"):
        plan(tree)


def test_an_e_in_another_classs_table_is_not_judged(tree, monkeypatch):
    compiled = {"Code/Game/Widget.cpp": {"??_7Other@@6B@": ["??_EOther@@UAEPAXI@Z", NEW]}}
    retail(monkeypatch, TWO_SLOTS, compiled=compiled)
    with pytest.raises(Refusal, match="does not prove the slot"):
        plan(tree)
