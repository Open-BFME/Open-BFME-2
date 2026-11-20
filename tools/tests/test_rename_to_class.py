"""tools/rename.py function --to-class on a miniature tree: moving a
placeholder-class member into the real class whose own retail vftable holds
its address, as that class's virtual. The retail image (rename.retail_vtables)
and the compiled installer objects (rename.compiled_vtables) are injected, and
so is verification, as in test_rename_virtual.py."""
import re
import struct
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
import retail_identity  # noqa: E402
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


@pytest.fixture(autouse=True)
def _slot_votes(request, monkeypatch):
    """The slot's name is voted (to_class_name_problem); the tests below that predate it test every other check of
    the move, so the vote is taken as given for them. test_votes_* run the real check."""
    if not request.node.name.startswith("test_votes_"):
        monkeypatch.setattr(rename, "to_class_name_problem", lambda *args, **kwargs: None)


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
    monkeypatch.setattr(rename, "object_fresh", lambda ctx, rel: True)


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def plan(root, rva=0x00401000, new="spin", cls="Widget", prepared=True, **overrides):
    edits = {"Code/Game/Bits.cpp": BITS_PREPARED.encode()} if prepared else None
    overrides.setdefault("approval_base", "HEAD")
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
                              prepared={"Code/Game/SleepBits.cpp": SLEEP_PREPARED.encode()}, approval_base="HEAD")


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
                              prepared={rel: p.encode() for rel, (_t, p) in B_SOURCES.items()}, also=list(also),
                              approval_base="HEAD")


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
    (tree / "reverse/functions.csv").write_text(functions, newline="\n")
    retail(monkeypatch, TWO_SLOTS, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [VECTOR, NEW]}})
    with pytest.raises(Refusal, match="does not prove the slot"):
        plan(tree)


def test_an_e_in_another_classs_table_is_not_judged(tree, monkeypatch):
    compiled = {"Code/Game/Widget.cpp": {"??_7Other@@6B@": ["??_EOther@@UAEPAXI@Z", NEW]}}
    retail(monkeypatch, TWO_SLOTS, compiled=compiled)
    with pytest.raises(Refusal, match="does not prove the slot"):
        plan(tree)


# ------------------------------------------------------------ a reviewed shared slot
# 0x00810000 holds the moved body at slot 1, as Widget's table does, and no view relates its class to Widget. Only a
# reviewed entry in tools/retail_identity.py can, and only for the tables it names, at the facts it states.

OTHER_TABLE_VA = 0x00C10000
VPTR_VA = TABLE + retail_identity.IMAGE_BASE
SHARED = {TABLE: ([0x00403040, 0x00401000, 0x00404000], {CTOR_STORE: 0}),
          OTHER_TABLE_VA - retail_identity.IMAGE_BASE: ([0x00405000, 0x00401000], {OTHER_STORE: 0})}
ENTRY = retail_identity.SharedSlot(
    rva=0x00401000, cls="Widget", new=NEW, table=VPTR_VA, slot=1, vptr=VPTR_VA,
    own=(retail_identity.word(VPTR_VA, 1, 0x00401000),),
    tables={OTHER_TABLE_VA: (retail_identity.word(OTHER_TABLE_VA, 1, 0x00401000),
                             retail_identity.Fact("calls", 0x00405000, 0x00408000),
                             retail_identity.Fact("stores", 0x00408000, VPTR_VA, "c701"))},
    notes={})


def _holds(monkeypatch, entries, facts=None):
    """Retail holds exactly `facts` (default: every fact of the entries), over int3s."""
    held = {}
    for entry in entries:
        for fact in retail_identity.shared_slot_facts(entry) if facts is None else facts:
            held[fact.site] = retail_identity.expected(fact)

    def read(rva, size):
        out = bytearray(b"\xcc" * size)
        for site, data in held.items():
            for at, byte in enumerate(data):
                if rva <= site + at < rva + size:
                    out[site + at - rva] = byte
        return bytes(out)
    monkeypatch.setattr(retail_identity, "read_retail", read)
    monkeypatch.setattr(retail_identity, "SHARED_SLOTS", tuple(entries))


def test_a_listed_table_with_its_facts_holding_is_related(tree, monkeypatch):
    retail(monkeypatch, SHARED)
    _holds(monkeypatch, [ENTRY])
    done = plan(tree)
    assert "1 table(s) cleared by retail_identity's reviewed entry: 0x00C10000" in str(vars(done))


def test_with_no_entry_a_shared_slot_stays_a_fold(tree, monkeypatch):
    retail(monkeypatch, SHARED)
    _holds(monkeypatch, [])
    with pytest.raises(Refusal, match="unrelated to Widget"):
        plan(tree)


def test_a_table_the_entry_does_not_name_stays_a_fold(tree, monkeypatch):
    tables = dict(SHARED)
    tables[0x00820000] = ([0x00405000, 0x00401000], {OTHER_STORE + 8: 0})
    retail(monkeypatch, tables)
    _holds(monkeypatch, [ENTRY])
    with pytest.raises(Refusal, match="unrelated to Widget"):
        plan(tree)


def test_a_listed_table_at_another_slot_stays_a_fold(tree, monkeypatch):
    tables = dict(SHARED)
    tables[OTHER_TABLE_VA - retail_identity.IMAGE_BASE] = ([0x00401000, 0x00405000], {OTHER_STORE: 0})
    retail(monkeypatch, tables)
    _holds(monkeypatch, [ENTRY])
    with pytest.raises(Refusal, match="unrelated to Widget"):
        plan(tree)


@pytest.mark.parametrize("missing", ["calls", "stores", "word"])
def test_any_fact_retail_does_not_hold_refuses(tree, monkeypatch, missing):
    retail(monkeypatch, SHARED)
    facts = [f for f in retail_identity.shared_slot_facts(ENTRY) if f.kind != missing]
    _holds(monkeypatch, [ENTRY], facts)
    with pytest.raises(Refusal, match="reviewed entry"):
        plan(tree)


def test_an_entry_for_another_class_or_name_does_not_apply(tree, monkeypatch):
    retail(monkeypatch, SHARED)
    _holds(monkeypatch, [ENTRY._replace(cls="Gadget"), ENTRY._replace(new="?other@Widget@@UAEXXZ")])
    with pytest.raises(Refusal, match="unrelated to Widget"):
        plan(tree)


def test_an_entry_naming_another_own_table_refuses(tree, monkeypatch):
    retail(monkeypatch, SHARED)
    _holds(monkeypatch, [ENTRY._replace(table=VPTR_VA + 0x100)])
    with pytest.raises(Refusal, match="reviewed entry"):
        plan(tree)


def test_the_entry_is_read_only_by_the_to_class_plan(tree, monkeypatch):
    # function --respell's this-cv route reads the same evidence function and keeps the view-only test
    retail(monkeypatch, SHARED)
    _holds(monkeypatch, [ENTRY])
    with pytest.raises(Refusal, match="unrelated to Widget"):
        rename.to_class_evidence(ctx_of(tree), 0x00401000, "Widget", {"Code/Game/Bits.cpp"})


@pytest.mark.parametrize("change,why", [
    (lambda e: e._replace(tables={OTHER_TABLE_VA: e.tables[OTHER_TABLE_VA][1:]}), "does not open with word"),
    (lambda e: e._replace(tables={OTHER_TABLE_VA: e.tables[OTHER_TABLE_VA][:-1]}), "does not end at a store"),
    (lambda e: e._replace(vptr=VPTR_VA + 4), "does not end at a store"),
])
def test_a_badly_stated_table_is_a_problem(monkeypatch, change, why):
    entry = change(ENTRY)
    _holds(monkeypatch, [entry])
    assert any(why in line for line in retail_identity.shared_slot_problems(entry))


def test_the_refusal_counts_the_tables_it_does_not_print(tree, monkeypatch):
    tables = dict(SHARED)
    for extra in range(4):
        tables[0x00820000 + extra * 0x100] = ([0x00405000, 0x00401000], {OTHER_STORE + 8 + extra: 0})
    retail(monkeypatch, tables)
    _holds(monkeypatch, [])
    with pytest.raises(Refusal, match=r"and 2 more"):
        plan(tree)


def test_the_real_entry_is_well_stated():
    # every table opens at slot 0 with the shared body and ends at RefCountClass's vptr; retail's bytes are checked
    # by `python3 tools/retail_identity.py`, which the image's seats run
    entry = retail_identity.REFCOUNT_DELETE_THIS
    assert len(entry.tables) == 24
    for table, facts in entry.tables.items():
        assert facts[0] == retail_identity.word(table, 0, 0x0006CE57)
        assert facts[-1].kind == "stores" and facts[-1].value == 0x00BC650C and facts[-1].code in retail_identity.VPTR_STORES


# ------------------------------------------------------------ a reviewed base slot
# Widget installs no table holding the moved body: 0x00C10000, Other's, holds it at slot 1 and no view relates Other
# to Widget. A base entry (retail_identity.BASE_SLOTS) relates the tables it lists, each ending at a factory's push and
# a registration call, and its dead tables, which nothing in the image reaches.

REGISTER = 0x00409000
FACTORY = 0x00409800
PUSH, REG_CALL = 0x00409900, 0x00409905
DEAD_TABLE_VA = 0x00C20000
DEAD_INSTALLER = 0x0040A000
DEAD_STORE = 0x0040A002
BASE_TABLES = {OTHER_TABLE_VA - retail_identity.IMAGE_BASE: ([0x00405000, 0x00401000], {OTHER_STORE: 0})}
BASE_FACTS = (retail_identity.word(OTHER_TABLE_VA, 1, 0x00401000),
              retail_identity.Fact("stores", OTHER_STORE, OTHER_TABLE_VA, "c701"),
              retail_identity.Fact("stores", PUSH, FACTORY + retail_identity.IMAGE_BASE, "68"),
              retail_identity.Fact("calls", REG_CALL, REGISTER))
BASE = retail_identity.BaseSlot(rva=0x00401000, cls="Widget", new=NEW, slot=1, register=REGISTER,
                                tables={OTHER_TABLE_VA: ("Other", BASE_FACTS)}, dead={})
DEAD_FACTS = (retail_identity.word(DEAD_TABLE_VA, 1, 0x00401000),
              retail_identity.Fact("stores", DEAD_STORE, DEAD_TABLE_VA, "c700"))
OTHER_COMPILED = {"Code/Game/Other.cpp": {"??_7Other@@6B@": ["?count@Gadget@@QAEXXZ", NEW]}}


def _image(monkeypatch, extra=b"", at=0x0040B000):
    """A miniature image whose file offsets are rvas: int3s with the dead installer's store, plus `extra` at `at`."""
    data = bytearray(b"\xcc" * 0x00410000)
    store = retail_identity.expected(DEAD_FACTS[1])
    data[DEAD_STORE:DEAD_STORE + len(store)] = store
    data[at:at + len(extra)] = extra
    monkeypatch.setattr(retail_identity, "retail_image", lambda: (bytes(data), 0x00401000, 0x00410000, lambda rva: rva))


def _base(monkeypatch, entries, facts=None, tables=None, compiled=None):
    retail(monkeypatch, BASE_TABLES if tables is None else tables,
           compiled=OTHER_COMPILED if compiled is None else compiled)
    held = {}
    for entry in entries:
        for fact in retail_identity.base_slot_facts(entry) if facts is None else facts:
            held[fact.site] = retail_identity.expected(fact)

    def read(rva, size):
        out = bytearray(b"\xcc" * size)
        for site, data in held.items():
            for i, byte in enumerate(data):
                if rva <= site + i < rva + size:
                    out[site + i - rva] = byte
        return bytes(out)
    monkeypatch.setattr(retail_identity, "read_retail", read)
    monkeypatch.setattr(retail_identity, "BASE_SLOTS", tuple(entries))
    monkeypatch.setattr(retail_identity, "SHARED_SLOTS", ())


def test_a_base_entry_relates_its_tables(tree, monkeypatch):
    _base(monkeypatch, [BASE])
    done = plan(tree)
    assert done.to_class["bases"][0]["cls"] == "Other"
    assert "related by retail_identity's reviewed base entry" in str(vars(done))
    # the subject and the tombstone name the entry, not the first table it lists
    assert done.subject().endswith("(slot 1 of the 1 tables in retail_identity.a BASE_SLOTS entry)")
    assert "0x00C10000" not in done.subject()
    assert any("to-class: slot 1 of the 1 tables in retail_identity." in text.decode()
               for rel, text in done.after.items() if rel.endswith("deleted_rows.csv"))


def test_with_no_base_entry_the_move_is_refused(tree, monkeypatch):
    _base(monkeypatch, [])
    with pytest.raises(Refusal, match="no constructor, destructor or deleting destructor row of Widget"):
        plan(tree)


def test_a_table_the_base_entry_does_not_name_stays_a_fold(tree, monkeypatch):
    tables = dict(BASE_TABLES)
    tables[0x00820000] = ([0x00405000, 0x00401000], {OTHER_STORE + 8: 0})
    _base(monkeypatch, [BASE], tables=tables)
    with pytest.raises(Refusal, match="no constructor, destructor or deleting destructor row of Widget"):
        plan(tree)


@pytest.mark.parametrize("dropped", range(4))
def test_any_base_fact_retail_does_not_hold_refuses(tree, monkeypatch, dropped):
    _base(monkeypatch, [BASE], facts=[f for i, f in enumerate(BASE_FACTS) if i != dropped])
    with pytest.raises(Refusal, match="reviewed base entry"):
        plan(tree)


@pytest.mark.parametrize("facts,why", [
    (BASE_FACTS[1:], "does not open with word"),
    (BASE_FACTS[:1] + BASE_FACTS[2:], "states no store of itself"),
    (BASE_FACTS[:-1], "does not end at a factory's push"),
    (BASE_FACTS[:2] + (BASE_FACTS[3], BASE_FACTS[2]), "does not end at a factory's push"),
])
def test_a_badly_stated_base_table_is_a_problem(monkeypatch, facts, why):
    entry = BASE._replace(tables={OTHER_TABLE_VA: ("Other", facts)})
    _base(monkeypatch, [entry])
    assert any(why in line for line in retail_identity.base_slot_problems(entry))


def test_a_base_entry_naming_another_class_refuses(tree, monkeypatch):
    _base(monkeypatch, [BASE._replace(tables={OTHER_TABLE_VA: ("Gadget", BASE_FACTS)})])
    with pytest.raises(Refusal, match="names table 0x00C10000 Gadget's"):
        plan(tree)


def test_a_compiled_copy_naming_another_slot_refuses(tree, monkeypatch):
    # slot 0 agrees with retail and slot 1 reaches another body: a wrong identity, bridged or not
    compiled = {"Code/Game/Other.cpp": {"??_7Other@@6B@": ["?count@Gadget@@QAEXXZ", STOP]}}
    _base(monkeypatch, [BASE], compiled=compiled)
    monkeypatch.setattr(rename, "newest_real_link", lambda ctx: _link({OTHER_TABLE_VA - retail_identity.IMAGE_BASE}))
    with pytest.raises(Refusal, match=f"slot 1 names {re.escape(STOP)}.*a wrong identity"):
        plan(tree)


def test_a_prepared_installer_unit_is_judged_after_the_build(tree, monkeypatch):
    # Other.cpp's object still names another body at slot 1; --prepared corrects its view, so planning must not
    # judge the old object (the post-build check reads it once rebuilt)
    compiled = {"Code/Game/Other.cpp": {"??_7Other@@6B@": ["?count@Gadget@@QAEXXZ", STOP]}}
    _base(monkeypatch, [BASE], compiled=compiled)
    edits = {"Code/Game/Bits.cpp": BITS_PREPARED.encode(),
             "Code/Game/Other.cpp": b"class Widget { public: virtual void spin(); };\n"
                                    b"class Other : public Widget { public: Other(); };\nOther::Other() {}\n"}
    done = rename.plan_rename("function", ctx=ctx_of(tree), rva=0x00401000, to_class="Widget", new="spin",
                              prepared=edits)
    assert done.to_class["bases"][0]["sources"] == ["Code/Game/Other.cpp"]


def test_an_unprepared_installer_naming_another_body_refuses(tree, monkeypatch):
    compiled = {"Code/Game/Other.cpp": {"??_7Other@@6B@": ["?count@Gadget@@QAEXXZ", STOP]}}
    _base(monkeypatch, [BASE], compiled=compiled)
    with pytest.raises(Refusal, match=f"slot 1 names {re.escape(STOP)}"):
        plan(tree)


BROKEN = {"Code/Game/Other.cpp": {"??_7Other@@6B@": ["?count@Gadget@@QAEXXZ", STOP, STOP]}}


def test_a_copy_naming_the_placeholder_names_the_moved_body(tree, monkeypatch):
    # the old spelling is the moved row itself, which the rename respells in every source that names it
    compiled = {"Code/Game/Other.cpp": {"??_7Other@@6B@": ["?count@Gadget@@QAEXXZ", OLD]}}
    _base(monkeypatch, [BASE], compiled=compiled)
    plan(tree)


ALIAS = "?alias@Other@@UAEXXZ"


def _link(bridged, commit="abc", run=42):
    return {"commit": commit, "run": run, "bridged": set(bridged)}


def test_an_alias_never_makes_a_wrong_identity_pass(tree, monkeypatch):
    # slot 0 agrees with retail; slot 1 names an alias whose pragma points at the moved body: the alias is not
    # followed (it could reach a stub or another body), so the copy is a wrong identity and refuses, bridged or not
    (tree / "Code/Game/Other.cpp").write_text(OTHER + f'#pragma comment(linker, "/alternatename:{ALIAS}={OLD}")\n')
    compiled = {"Code/Game/Other.cpp": {"??_7Other@@6B@": ["?count@Gadget@@QAEXXZ", ALIAS]}}
    _base(monkeypatch, [BASE], compiled=compiled)
    monkeypatch.setattr(rename, "newest_real_link", lambda ctx: _link({OTHER_TABLE_VA - retail_identity.IMAGE_BASE}))
    # even were the object to emit it and a link map put both names at one address (an int3 stub can share it)
    monkeypatch.setattr(rename, "object_alternates", lambda ctx, rel, current=True: {ALIAS: OLD}, raising=False)
    monkeypatch.setattr(rename, "real_link_map", lambda ctx, link: {ALIAS: 0x02001000, OLD: 0x02001000}, raising=False)
    with pytest.raises(Refusal, match=f"slot 1 names {re.escape(ALIAS)}.*a wrong identity"):
        plan(tree)


def test_the_bridge_is_read_again_after_the_build(tree, monkeypatch):
    _base(monkeypatch, [BASE], compiled=BROKEN)
    calls = []
    monkeypatch.setattr(rename, "newest_real_link",
                        lambda ctx: calls.append(1) or _link({OTHER_TABLE_VA - retail_identity.IMAGE_BASE}))
    done = plan(tree)
    before = len(calls)
    # a newer real link no longer bridges the table: the rebuilt admission refuses
    monkeypatch.setattr(rename, "newest_real_link", lambda ctx: calls.append(1) or _link({0x00820000}, commit="def"))
    problems = rename.to_class_slot_problems(ctx_of(tree), done.to_class, current=False)
    assert len(calls) > before and any("real link def does not bridge it" in p for p in problems)


GADGET_TABLE_VA, GADGET_STORE = 0x00C11000, 0x0040C010
GADGET_FACTS = (retail_identity.word(GADGET_TABLE_VA, 1, 0x00401000),
                retail_identity.Fact("stores", GADGET_STORE, GADGET_TABLE_VA, "c701"),
                retail_identity.Fact("stores", PUSH + 0x20, FACTORY + 0x20 + retail_identity.IMAGE_BASE, "68"),
                retail_identity.Fact("calls", REG_CALL + 0x20, REGISTER))


def test_the_final_reports_are_warned_and_kept_in_the_tombstone(tree, monkeypatch, capsys):
    # planning reads sound copies; after the rebuild Other's copy is broken elsewhere (its table bridged) while
    # Gadget's still proves the move
    functions = (tree / "reverse/functions.csv").read_text() + "??0Gadget@@QAE@XZ,,0x0040C000,64,Code/Game/Gadget.cpp,matched,ctor\n"
    (tree / "reverse/functions.csv").write_text(functions, newline="\n")
    tables = dict(BASE_TABLES)
    tables[GADGET_TABLE_VA - retail_identity.IMAGE_BASE] = ([0x00405000, 0x00401000], {GADGET_STORE: 0})
    entry = BASE._replace(tables={OTHER_TABLE_VA: ("Other", BASE_FACTS), GADGET_TABLE_VA: ("Gadget", GADGET_FACTS)})
    gadget = {"??_7Gadget@@6B@": ["?count@Gadget@@QAEXXZ", NEW]}
    good = {"Code/Game/Other.cpp": {"??_7Other@@6B@": ["?count@Gadget@@QAEXXZ", NEW]}, "Code/Game/Gadget.cpp": gadget}
    rebuilt = dict(BROKEN, **{"Code/Game/Gadget.cpp": gadget})
    _base(monkeypatch, [entry], tables=tables, compiled=good)
    monkeypatch.setattr(rename, "compiled_vtables",
                        lambda ctx, rel, current=True: (good if current else rebuilt).get(rel))
    monkeypatch.setattr(rename, "newest_real_link",
                        lambda ctx: _link({OTHER_TABLE_VA - retail_identity.IMAGE_BASE}, commit="c0ffee1234", run=77))
    done = plan(tree)
    assert not any("reported" in w for w in done.warnings)
    rename.apply_rename(done, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    assert "rename: warning:" in capsys.readouterr().out
    deleted = (tree / "reverse/deleted_rows.csv").read_text()
    assert "; reported: Code/Game/Other.cpp's ??_7Other@@6B@ slot 1 names" in deleted
    assert "real link run 77 at c0ffee1234 bridges that table" in deleted and "at slot(s) 2" in deleted


def test_a_copy_broken_elsewhere_passes_with_a_report_while_its_table_is_bridged(tree, monkeypatch):
    _base(monkeypatch, [BASE], compiled=BROKEN)
    monkeypatch.setattr(rename, "newest_real_link", lambda ctx: _link({OTHER_TABLE_VA - retail_identity.IMAGE_BASE}))
    done = plan(tree)
    assert any("already differs from retail table 0x00C10000 at slot(s) 2" in w and "reported, not refused" in w
               and "run 42 at abc" in w for w in done.warnings)


def test_a_copy_broken_elsewhere_refuses_when_its_table_is_not_bridged(tree, monkeypatch):
    _base(monkeypatch, [BASE], compiled=BROKEN)
    monkeypatch.setattr(rename, "newest_real_link", lambda ctx: _link({0x00820000}))
    with pytest.raises(Refusal, match="real link abc does not bridge it"):
        plan(tree)


def test_a_copy_broken_elsewhere_refuses_when_the_bridge_queue_cannot_be_read(tree, monkeypatch):
    _base(monkeypatch, [BASE], compiled=BROKEN)
    monkeypatch.setattr(rename, "newest_real_link", lambda ctx: None)
    with pytest.raises(Refusal, match="bridge queue could not be read"):
        plan(tree)


UNRESOLVED = {"Code/Game/Other.cpp": {"??_7Other@@6B@": ["?a@Other@@UAEXXZ", "?b@Other@@UAEXXZ"]}}


def test_an_unresolvable_copy_passes_with_a_report_while_its_table_is_bridged(tree, monkeypatch):
    _base(monkeypatch, [BASE], compiled=UNRESOLVED)
    monkeypatch.setattr(rename, "newest_real_link", lambda ctx: _link({OTHER_TABLE_VA - retail_identity.IMAGE_BASE}))
    done = plan(tree)
    assert any("nothing else in it resolves against retail table 0x00C10000" in w and "reported, not refused" in w
               for w in done.warnings)


def test_an_unresolvable_copy_refuses_when_its_table_is_not_bridged(tree, monkeypatch):
    _base(monkeypatch, [BASE], compiled=UNRESOLVED)
    monkeypatch.setattr(rename, "newest_real_link", lambda ctx: _link({0x00820000}))
    with pytest.raises(Refusal, match="nothing else in it resolves.*does not bridge it"):
        plan(tree)


def test_a_base_move_takes_no_also(tree, monkeypatch):
    _base(monkeypatch, [BASE])
    with pytest.raises(Refusal):
        plan(tree, also=[(0x00404000, "stop")])


def _with_dead(monkeypatch, extra=b"", at=0x0040B000):
    tables = dict(BASE_TABLES)
    tables[DEAD_TABLE_VA - retail_identity.IMAGE_BASE] = ([0x00405000, 0x00401000], {DEAD_STORE: 0})
    entry = BASE._replace(dead={DEAD_TABLE_VA: (DEAD_INSTALLER, DEAD_FACTS)})
    _base(monkeypatch, [entry], tables=tables)
    _image(monkeypatch, extra, at)
    return entry


def test_a_dead_table_nothing_reaches_is_related(tree, monkeypatch):
    _with_dead(monkeypatch)
    assert "1 dead: 0x00C20000" in str(vars(plan(tree)))


@pytest.mark.parametrize("opcode", [b"\xe8", b"\xe9"])
def test_a_dead_table_whose_installer_a_rel32_reaches_refuses(tree, monkeypatch, opcode):
    at = 0x0040B000
    _with_dead(monkeypatch, opcode + struct.pack("<i", DEAD_INSTALLER - (at + 5)), at)
    with pytest.raises(Refusal, match="is a rel32 to its installer"):
        plan(tree)


def test_a_dead_table_whose_installer_a_stored_pointer_names_refuses(tree, monkeypatch):
    # a function table in .rdata holding the installer's VA, unaligned reads included
    _with_dead(monkeypatch, struct.pack("<I", DEAD_INSTALLER + retail_identity.IMAGE_BASE), 0x0040C001)
    with pytest.raises(Refusal, match="holds its installer's VA"):
        plan(tree)


def test_a_dead_table_referenced_elsewhere_refuses(tree, monkeypatch):
    _with_dead(monkeypatch, b"\xc7\x06" + struct.pack("<I", DEAD_TABLE_VA), 0x0040D000)
    with pytest.raises(Refusal, match="holds the table's VA"):
        plan(tree)


def test_an_unrelated_table_with_a_referenced_installer_stays_a_fold(tree, monkeypatch):
    # only a listed dead table is judged by its references; another unrelated table stays a fold
    tables = dict(BASE_TABLES)
    tables[DEAD_TABLE_VA - retail_identity.IMAGE_BASE] = ([0x00405000, 0x00401000], {DEAD_STORE: 0})
    _base(monkeypatch, [BASE], tables=tables)
    _image(monkeypatch, b"\xe8" + struct.pack("<i", DEAD_INSTALLER - (0x0040B000 + 5)))
    with pytest.raises(Refusal, match="no constructor, destructor or deleting destructor row of Widget"):
        plan(tree)


def test_the_base_entry_is_read_only_by_the_to_class_plan(tree, monkeypatch):
    _base(monkeypatch, [BASE])
    with pytest.raises(Refusal, match="no constructor, destructor or deleting destructor row of Widget"):
        rename.to_class_evidence(ctx_of(tree), 0x00401000, "Widget", {"Code/Game/Bits.cpp"})


def test_the_real_base_entry_is_well_stated():
    # retail's bytes are checked by `python3 tools/retail_identity.py`; here, its shape
    entry = retail_identity.MODULE_DATA_SLOT14
    assert (entry.rva, entry.cls, entry.slot, entry.register) == (0x000B69A1, "ModuleData", 14, 0x002573EE)
    assert len(entry.tables) == 107 and set(entry.dead) == {0x00C5AEB8}
    assert entry.dead[0x00C5AEB8][0] == 0x004BDCA3
    for table, (_cls, facts) in entry.tables.items():
        assert facts[0] == retail_identity.word(table, 14, 0x000B69A1)
        assert facts[-2].code == "68" and facts[-1].kind == "calls" and facts[-1].value == 0x002573EE


# ------------------------------------------- a module's name getter moved within its class (lk106)
#
# Getter units define each module's 6-byte `mov eax,"C"; ret` through a stub class, rowed as the class's own
# non-virtual `?name@C@@QBEPBDXZ`. Retail binds it to slot 2 of C's own table: Snapshot::GetSnapshotName's.
# The one same-class move: to `?GetSnapshotName@C@@MBEPBDXZ`, proved by C's own table's slot 2, the
# installers' views deriving C from Snapshot and the rebuilt table naming the override there.

GETTER_OLD = "?name@Widget@@QBEPBDXZ"
GETTER_NEW = "?GetSnapshotName@Widget@@MBEPBDXZ"
GETTER_RVA = 0x00406000
NAMES = f"""// cl: /O2
// {GETTER_OLD}
class Widget {{ public: const char *name() const; }};
const char *Widget::name() const {{ return "Widget"; }}
"""
NAMES_PREPARED = f"""// cl: /O2
// {GETTER_NEW}
class Widget {{ protected: virtual const char *GetSnapshotName() const; }};
const char *Widget::GetSnapshotName() const {{ return "Widget"; }}
"""
SNAPSHOT_WIDGET = """class Snapshot {
public:
    virtual ~Snapshot();
protected:
    virtual void loadPostProcess() = 0;
    virtual const char *GetSnapshotName() const = 0;
};
class Widget : public Snapshot {
public:
    Widget();
    virtual ~Widget();
protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
};
Widget::Widget() {}
void Widget::loadPostProcess() {}
"""
GETTER_TABLES = {TABLE: ([0x00403040, 0x00404000, GETTER_RVA], {CTOR_STORE: 0})}
GETTER_COMPILED = {"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, STOP, GETTER_NEW]}}


def getter_tree(tree, widget=SNAPSHOT_WIDGET):
    functions = (tree / "reverse/functions.csv").read_bytes().decode()
    (tree / "reverse/functions.csv").write_bytes(
        (functions + f"{GETTER_OLD},,0x00406000,6,Code/Game/Names.cpp,matched,literal name getter\n").encode())
    (tree / "Code/Game/Names.cpp").write_bytes(NAMES.encode())
    (tree / "Code/Game/Widget.cpp").write_bytes(widget.encode())
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "add", "-A")
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "getter")
    return tree


def getter_plan(root, new=GETTER_NEW, **overrides):
    kwargs = dict(rva=GETTER_RVA, to_class="Widget", new=new,
                  prepared={"Code/Game/Names.cpp": NAMES_PREPARED.encode()}, approval_base="HEAD")
    kwargs.update(overrides)
    return rename.plan_rename("function", ctx=ctx_of(root), **kwargs)


@pytest.mark.parametrize("name,cls,new,expected", [
    (GETTER_OLD, "Widget", GETTER_NEW, True),
    (GETTER_OLD, "Widget", "GetSnapshotName", False),                          # the whole spelling, always
    (GETTER_OLD, "Widget", "?GetSnapshotName@Widget@@UBEPBDXZ", False),        # public: not the override
    (GETTER_OLD, "Widget", "?getName@Widget@@MBEPBDXZ", False),                # another identifier
    ("?name@Widget@@QAEPBDXZ", "Widget", "?GetSnapshotName@Widget@@MAEPBDXZ", False),   # not const
    ("?label@Widget@@QBEPBDXZ", "Widget", GETTER_NEW, False),                  # not the name getter
    (GETTER_OLD, "Gadget", "?GetSnapshotName@Gadget@@MBEPBDXZ", False),        # another class
])
def test_snapshot_name_getter_shape(name, cls, new, expected):
    assert rename.snapshot_name_getter(name, cls, new) is expected


def test_a_name_getter_moves_within_its_class_to_the_snapshot_override(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled=GETTER_COMPILED)
    p = getter_plan(getter_tree(tree))
    assert p.new == GETTER_NEW and p.basis == "to-class"
    assert p.to_class["slot"] == 2 and p.to_class["sources"] == ["Code/Game/Widget.cpp"]
    assert "slot 2 is Snapshot::GetSnapshotName's" in p.evidence
    assert (GETTER_OLD, GETTER_NEW, GETTER_RVA) in p.renamed_rows
    assert p.subject() == f"Move {GETTER_OLD} into Widget as {GETTER_NEW} (retail vftable 0x00C00000 slot 2)"


@pytest.mark.parametrize("new", ["?GetSnapshotName@Widget@@UBEPBDXZ", "?getName@Widget@@MBEPBDXZ"])
def test_any_other_move_within_the_class_is_still_refused(tree, monkeypatch, new):
    retail(monkeypatch, GETTER_TABLES, compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, STOP, new]}})
    with pytest.raises(Refusal, match="is already a member of Widget"):
        getter_plan(getter_tree(tree), new=new)


def test_a_name_getter_outside_slot_2_is_refused(tree, monkeypatch):
    # retail holds the getter in slot 1 of the class's own table: not GetSnapshotName's slot
    retail(monkeypatch, {TABLE: ([0x00403040, GETTER_RVA, 0x00404000], {CTOR_STORE: 0})},
           compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, GETTER_NEW, STOP]}})
    with pytest.raises(Refusal, match="sits in slot 1 of Widget's retail table 0x00C00000, not slot 2"):
        getter_plan(getter_tree(tree))


def test_a_name_getter_in_no_retail_slot_is_refused(tree, monkeypatch):
    retail(monkeypatch, GOOD, compiled=GETTER_COMPILED)
    with pytest.raises(Refusal, match="no retail vftable slot holds 0x00406000"):
        getter_plan(getter_tree(tree))


def test_a_name_getter_whose_class_view_has_no_snapshot_base_is_refused(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled=GETTER_COMPILED)
    with pytest.raises(Refusal, match="no installer unit.s view of Widget derives from Snapshot"):
        getter_plan(getter_tree(tree, widget=SNAPSHOT_WIDGET.replace(" : public Snapshot", "")))


def test_a_name_getter_the_rebuilt_table_does_not_name_is_refused(tree, monkeypatch):
    # the installer still inherits the base's getter in slot 2
    retail(monkeypatch, GETTER_TABLES, compiled={"Code/Game/Widget.cpp": {
        "??_7Widget@@6B@": [GDTOR, STOP, "?GetSnapshotName@UpdateModule@@MBEPBDXZ"]}})
    with pytest.raises(Refusal, match="slot 2 names"):
        getter_plan(getter_tree(tree))


# ------------------------------------- a free placeholder getter moved into its class (lk106)
#
# The const-int getter units row the same 6-byte `mov eax,"C"; ret` as a free `int RvaNNNNNNNNGet()` (address-
# derived, no class witnessed). Retail binds it to slot 2 of C's own table: the same proof moves it into C as
# `?GetSnapshotName@C@@MBEPBDXZ`; the body is identical under both spellings (no argument, eax returned).

FREE_OLD = "?Rva00406000Get@@YAHXZ"
FREE_NAMES = f"""// cl: /O2
// {FREE_OLD}
int Rva00406000Get(void) {{ return (int)"Widget"; }}
"""


def free_getter_tree(tree, widget=SNAPSHOT_WIDGET, old=FREE_OLD):
    functions = (tree / "reverse/functions.csv").read_bytes().decode()
    (tree / "reverse/functions.csv").write_bytes(
        (functions + f"{old},,0x00406000,6,Code/Game/Names.cpp,matched,const-int getter\n").encode())
    (tree / "Code/Game/Names.cpp").write_bytes(FREE_NAMES.replace(FREE_OLD, old).encode())
    (tree / "Code/Game/Widget.cpp").write_bytes(widget.encode())
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "add", "-A")
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "free getter")
    return tree


@pytest.mark.parametrize("name,cls,new,expected", [
    (FREE_OLD, "Widget", GETTER_NEW, True),
    ("?Rva4599DFGet@@YAHXZ", "Widget", GETTER_NEW, True),                       # six hex digits
    (FREE_OLD, "Widget", "?GetSnapshotName@Widget@@UBEPBDXZ", False),           # public: not the override
    (FREE_OLD, "Widget", "?getName@Widget@@MBEPBDXZ", False),                   # another identifier
    ("?Rva00406000Get@@YAHH@Z", "Widget", GETTER_NEW, False),                   # takes an argument
    ("?Rva00406000Get@@YAPBDXZ", "Widget", GETTER_NEW, False),                  # another return type
    ("?countGet@@YAHXZ", "Widget", GETTER_NEW, False),                          # not a placeholder
    (FREE_OLD, "Gadget", GETTER_NEW, False),                                    # another class's spelling
])
def test_snapshot_free_getter_shape(name, cls, new, expected):
    assert rename.snapshot_free_getter(name, cls, new) is expected


def test_a_free_placeholder_getter_moves_into_its_class_as_the_snapshot_override(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled=GETTER_COMPILED)
    p = getter_plan(free_getter_tree(tree))
    assert p.new == GETTER_NEW and p.basis == "to-class"
    assert p.to_class["slot"] == 2 and "slot 2 is Snapshot::GetSnapshotName's" in p.evidence
    assert (FREE_OLD, GETTER_NEW, GETTER_RVA) in p.renamed_rows
    assert p.subject() == f"Move {FREE_OLD} into Widget as {GETTER_NEW} (retail vftable 0x00C00000 slot 2)"


def test_a_free_placeholder_getter_takes_only_the_snapshot_override(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled={"Code/Game/Widget.cpp": {
        "??_7Widget@@6B@": [GDTOR, STOP, "?getName@Widget@@MBEPBDXZ"]}})
    with pytest.raises(Refusal, match="not a method"):
        getter_plan(free_getter_tree(tree), new="?getName@Widget@@MBEPBDXZ")


def test_a_free_placeholder_getter_outside_slot_2_is_refused(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00403040, GETTER_RVA, 0x00404000], {CTOR_STORE: 0})},
           compiled={"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, GETTER_NEW, STOP]}})
    with pytest.raises(Refusal, match="sits in slot 1 of Widget's retail table 0x00C00000, not slot 2"):
        getter_plan(free_getter_tree(tree))


def test_a_free_placeholder_getter_whose_class_view_has_no_snapshot_base_is_refused(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled=GETTER_COMPILED)
    with pytest.raises(Refusal, match="no installer unit.s view of Widget derives from Snapshot"):
        getter_plan(free_getter_tree(tree, widget=SNAPSHOT_WIDGET.replace(" : public Snapshot", "")))


def test_a_free_getter_with_a_readable_name_is_still_refused(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled=GETTER_COMPILED)
    with pytest.raises(Refusal, match="not a method"):
        getter_plan(free_getter_tree(tree, old="?widgetNameGet@@YAHXZ"))


# --------------------------------------- a class move prepares a unit's view header (lk106)
#
# Some classes are declared only in a unit's view header (RainOfFireUpdateView.h): the override's declaration
# goes there. A --to-class move may prepare such a `.h` when it registers no canonical class; every ledger source
# that includes it is rebuilt. A canonical header, or a header outside --to-class, is still refused.

VIEW = "Code/Game/WidgetView.h"
VIEW_TEXT = SNAPSHOT_WIDGET.split("Widget::Widget() {}")[0]
VIEW_WIDGET_CPP = '#include "WidgetView.h"\nWidget::Widget() {}\nvoid Widget::loadPostProcess() {}\n'


def view_tree(tree, canonical=False):
    getter_tree(tree)
    view = VIEW_TEXT.replace("    virtual const char *GetSnapshotName() const;\n};", "};", 1)
    (tree / VIEW).write_bytes(view.encode())
    (tree / "Code/Game/Widget.cpp").write_bytes(VIEW_WIDGET_CPP.encode())
    if canonical:
        (tree / "reverse/canonical_classes.csv").write_bytes(
            f"class,header,notes\nWidget,{VIEW},registered view\n".encode())
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "add", "-A")
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "view header")
    return tree


def view_plan(root, **overrides):
    prepared = {"Code/Game/Names.cpp": NAMES_PREPARED.encode(), VIEW: VIEW_TEXT.encode()}
    return getter_plan(root, prepared=prepared, **overrides)


def test_a_class_move_prepares_a_view_header_and_rebuilds_its_includers(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled=GETTER_COMPILED)
    p = view_plan(view_tree(tree))
    assert p.new == GETTER_NEW and p.to_class["slot"] == 2
    assert VIEW in p.after and b"GetSnapshotName" in p.after[VIEW]
    assert "Code/Game/Widget.cpp" in p.verify and "Code/Game/Names.cpp" in p.verify
    assert VIEW not in p.verify
    assert f"file:{VIEW}" in p.claims


def test_a_class_move_never_prepares_a_canonical_header(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled=GETTER_COMPILED)
    with pytest.raises(Refusal, match="is the registered header of Widget"):
        view_plan(view_tree(tree, canonical=True))


def test_a_view_header_is_prepared_by_a_class_move_only(tree):
    ctx = ctx_of(view_tree(tree))
    plan = rename.Plan("function", GETTER_OLD, GETTER_NEW, "inferred", "", "Code/Game/Names.cpp", GETTER_RVA)
    with pytest.raises(Refusal, match="must be an existing Code C[+][+] source"):
        rename._batch_source_edits(ctx, plan, {VIEW: VIEW_TEXT.encode()})
    assert rename._batch_source_edits(ctx, plan, {VIEW: VIEW_TEXT.encode()}, view_headers=True)
    assert VIEW not in plan.verify


def test_a_prepared_view_header_must_be_clean(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled=GETTER_COMPILED)
    root = view_tree(tree)
    (root / VIEW).write_bytes(b"// an unstaged edit\n" + (root / VIEW).read_bytes())
    with pytest.raises(Refusal, match="requires clean source paths"):
        view_plan(root)


def test_an_installer_including_a_prepared_view_header_is_judged_after_the_build(tree, monkeypatch):
    # its object still holds the base's getter in slot 2 before ./build.sh: planning passes it over (lk106)
    stale = {"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, STOP, "?GetSnapshotName@UpdateModule@@MBEPBDXZ"]}}
    retail(monkeypatch, GETTER_TABLES, compiled=stale)
    p = view_plan(view_tree(tree))
    assert p.new == GETTER_NEW and "Code/Game/Widget.cpp" in p.verify
    with pytest.raises(VerifyFailed, match="rebuilt vftable"):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)


def test_an_installer_without_the_prepared_header_is_still_judged_before_the_build(tree, monkeypatch):
    stale = {"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, STOP, "?GetSnapshotName@UpdateModule@@MBEPBDXZ"]}}
    retail(monkeypatch, GETTER_TABLES, compiled=stale)
    root = view_tree(tree)
    with pytest.raises(Refusal, match="slot 2 names"):
        getter_plan(root)          # the getter unit alone is prepared: Widget.cpp's view is unchanged


# ------------------------------------------------------------ the slot's name is voted (votes only)

WIDGET_H = "Code/Game/Widget.h"


def register(tree, cls="Widget", header=WIDGET_H):
    path = tree / "reverse/canonical_classes.csv"
    text = path.read_text() if path.exists() else "class,header,notes\n"
    path.write_text(text + f"{cls},{header},registered\n")
    if not (tree / header).exists():
        (tree / header).write_text(f"class {cls} {{ public: virtual ~{cls}(); }};\n", newline="\n")
    _git(tree, "add", "-A")
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", f"register {cls}")


def key_of(table_va, slot, cls="Widget", header=WIDGET_H):
    return f"{header}|slot|{cls}@0x{table_va:08X}|{slot}"


def approve(tree, key, name, status="agreed", workers=("w-aaaaaaaaaaaa", "w-bbbbbbbbbbbb")):
    """name_lane's approval of `name` for slot `key`: the workers' votes and the agreed record."""
    import name_agreement
    votes, agreed = tree / name_agreement.VOTES, tree / name_agreement.AGREED
    if not votes.exists():
        votes.write_text(",".join(name_agreement.VOTE_COLUMNS) + "\n")
    if not agreed.exists():
        agreed.write_text(",".join(name_agreement.AGREED_COLUMNS) + "\n")
    digest = name_agreement.digest(key, name)
    with votes.open("a") as f:
        for worker in workers:
            f.write(f"{key},{digest},seat,s-{worker},{worker},2026-11-14\n")
    # each vote's fingerprint: the header it was served, committed with it (votes_bound_to_text)
    sources = tree / rename.VOTE_SOURCES
    if not sources.exists():
        sources.write_text("key,hash,worker,session,source_sha\n")
    header = (tree / key.split("|", 1)[0]).read_bytes()
    with sources.open("a") as f:
        for worker in workers:
            f.write(f"{key},{digest},{worker},s-{worker},{__import__('hashlib').sha256(header).hexdigest()}\n")
    with agreed.open("a") as f:
        f.write(f"nl-{abs(hash(key)) % 10**8},slot,{key.rsplit('|', 1)[1]},{name},,{';'.join(workers)},{key},{status},"
                "two-agent agreement\n")
    _git(tree, "add", "-A")
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "slot votes")


def test_votes_slot_key_is_built_from_retail_facts_and_the_registered_header(tree):
    register(tree)
    ctx = ctx_of(tree)
    assert rename.slot_key(ctx, "Widget", TABLE, 1) == key_of(0x00C00000, 1)
    assert rename.slot_key(ctx, "Gadget", TABLE, 1) is None


def test_votes_an_unregistered_class_is_refused(tree, monkeypatch):
    retail(monkeypatch, GOOD)
    with pytest.raises(Refusal, match="Widget has no canonical header in reverse/canonical_classes.csv"):
        plan(tree)


KEPT = "?rva00401000@Widget@@UAEXXZ"
KEPT_PREPARED = f"""// cl: /O2
// {OLD} @ 0x00401000
class Widget {{ public: virtual void rva00401000(); }};
void Widget::rva00401000() {{}}
"""
KEPT_COMPILED = {"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, KEPT, STOP]}}


def kept_plan(root, new="rva00401000", **overrides):
    overrides.setdefault("approval_base", None)
    return rename.plan_rename("function", ctx=ctx_of(root), rva=0x00401000, to_class="Widget", new=new,
                              prepared={"Code/Game/Bits.cpp": KEPT_PREPARED.encode()}, **overrides)


def test_votes_a_move_that_keeps_its_placeholder_identifier_names_nothing(tree, monkeypatch):
    # The class is unregistered, no approval base is given and no vote exists: the move writes only the class
    # retail's table proves, under the identifier the row already had. The slot stays a placeholder.
    retail(monkeypatch, GOOD, compiled=KEPT_COMPILED)
    p = kept_plan(tree)
    assert any(KEPT in str(v) for v in vars(p).values())


def test_votes_a_kept_placeholder_still_needs_retails_installer(tree, monkeypatch):
    # the exemption is about the name only: ownership is still read from retail
    retail(monkeypatch, {TABLE: ([0x00403040, 0x00401000, 0x00404000], {OTHER_STORE: 0})}, compiled=KEPT_COMPILED)
    with pytest.raises(Refusal):
        kept_plan(tree)


def test_votes_another_placeholder_identifier_is_a_new_name(tree, monkeypatch):
    # a placeholder the row does not carry is a spelling someone chose: not exempt
    other = {"Code/Game/Widget.cpp": {"??_7Widget@@6B@": [GDTOR, "?rva00409999@Widget@@UAEXXZ", STOP]}}
    retail(monkeypatch, GOOD, compiled=other)
    with pytest.raises(Refusal, match="Widget has no canonical header in reverse/canonical_classes.csv"):
        rename.plan_rename("function", ctx=ctx_of(tree), rva=0x00401000, to_class="Widget", new="rva00409999",
                           prepared={"Code/Game/Bits.cpp": KEPT_PREPARED.replace("rva00401000()", "rva00409999()").encode()},
                           approval_base=None)


def test_votes_an_unvoted_slot_is_refused_naming_its_key(tree, monkeypatch):
    retail(monkeypatch, GOOD)
    register(tree)
    with pytest.raises(Refusal, match=re.escape(f"no approved name for slot key {key_of(0x00C00000, 1)}")):
        plan(tree)


def test_votes_the_approved_name_is_accepted_and_no_other(tree, monkeypatch):
    retail(monkeypatch, GOOD)
    register(tree)
    approve(tree, key_of(0x00C00000, 1), "spin")
    assert plan(tree).new == NEW
    assert plan(tree, new=NEW).new == NEW                     # a full mangled --new is judged by its identifier
    with pytest.raises(Refusal, match="the approved name spin for slot key .*, not whirl"):
        plan(tree, new="whirl")


@pytest.mark.parametrize("status,workers", [("disputed", ("w-aaaaaaaaaaaa", "w-bbbbbbbbbbbb")),
                                            ("agreed", ("w-aaaaaaaaaaaa",))])
def test_votes_a_disputed_or_one_vote_name_is_not_approved(tree, monkeypatch, status, workers):
    retail(monkeypatch, GOOD)
    register(tree)
    approve(tree, key_of(0x00C00000, 1), "spin", status=status, workers=workers)
    with pytest.raises(Refusal, match="no approved name for slot key"):
        plan(tree)


def test_votes_the_declaration_is_never_read(tree, monkeypatch):
    # the compiled table already declares spin there; without a vote the move is still refused
    retail(monkeypatch, GOOD)
    register(tree)
    with pytest.raises(Refusal, match="no approved name"):
        plan(tree, new="spin")


def test_votes_a_reviewed_shared_slot_needs_the_vote(tree, monkeypatch):
    retail(monkeypatch, SHARED)
    _holds(monkeypatch, [ENTRY])
    register(tree)
    with pytest.raises(Refusal, match="no approved name"):
        plan(tree)
    approve(tree, key_of(0x00C00000, 1), "spin")
    assert plan(tree).new == NEW


def test_votes_a_base_slot_needs_the_vote_on_its_table(tree, monkeypatch):
    _base(monkeypatch, [BASE])
    register(tree)
    with pytest.raises(Refusal, match=re.escape(f"no approved name for slot key {key_of(OTHER_TABLE_VA, 1)}")):
        plan(tree)
    approve(tree, key_of(OTHER_TABLE_VA, 1), "spin")
    assert plan(tree).new == NEW


def test_votes_every_batch_member_needs_its_vote(tree, monkeypatch):
    retail(monkeypatch, B_TABLE, compiled=B_COMPILED)
    root = batch_tree(tree)
    register(root)
    approve(root, key_of(0x00C00000, 1), "create")
    approve(root, key_of(0x00C00000, 2), "getName")
    with pytest.raises(Refusal, match=re.escape(f"no approved name for slot key {key_of(0x00C00000, 3)}")):
        batch_plan(root)
    approve(root, key_of(0x00C00000, 3), "parse")
    assert batch_plan(root).to_class["slots"] == {1: N_A, 2: N_B, 3: N_C}


def test_votes_a_snapshot_getter_needs_the_vote(tree, monkeypatch):
    retail(monkeypatch, GETTER_TABLES, compiled=GETTER_COMPILED)
    root = getter_tree(tree)
    register(root)
    with pytest.raises(Refusal, match="no approved name"):
        getter_plan(root)
    approve(root, key_of(0x00C00000, 2), "GetSnapshotName")
    assert getter_plan(root).new == GETTER_NEW


def test_votes_an_enum_respelled_move_needs_the_vote(tree, monkeypatch):
    sleep_tree(tree)
    register(tree)
    retail(monkeypatch, SLEEP_TABLES, compiled=SLEEP_COMPILED)
    with pytest.raises(Refusal, match="no approved name"):
        sleep_plan(tree)
    approve(tree, key_of(SLEEP_TABLE + 0x00400000, 0), "update")
    assert sleep_plan(tree).new == SLEEP_NEW


def test_votes_a_later_record_of_another_kind_ends_the_approval(tree, monkeypatch):
    # review r1: the key's latest record decides; an older slot approval is not revived past it
    retail(monkeypatch, GOOD)
    register(tree)
    key = key_of(0x00C00000, 1)
    approve(tree, key, "spin")
    with (tree / "reverse/name_agreed.csv").open("a") as f:
        f.write(f"nl-later,member,1,whirl,,,{key},blocked,a later record\n")
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qam", "a later record")
    assert rename.approved_slot_name(ctx_of(tree), key, "HEAD") is None
    with pytest.raises(Refusal, match="no approved name"):
        plan(tree)


def test_votes_a_header_edited_after_the_votes_ends_the_approval(tree, monkeypatch):
    # review r2: the consumer binds the votes to the header as it reads now
    retail(monkeypatch, GOOD)
    register(tree)
    approve(tree, key_of(0x00C00000, 1), "spin")
    assert plan(tree).new == NEW
    (tree / WIDGET_H).write_text("class Widget { public: virtual ~Widget(); virtual void spin(); };\n", newline="\n")
    _git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qam", "an edit")
    with pytest.raises(Refusal, match="no approved name"):
        plan(tree)


def test_votes_a_move_without_an_approval_base_is_refused(tree, monkeypatch):
    # coordinator: no fallback revision; the caller names it
    retail(monkeypatch, GOOD)
    register(tree)
    approve(tree, key_of(0x00C00000, 1), "spin")
    with pytest.raises(Refusal, match="pass --approval-base REV"):
        plan(tree, approval_base=None)


def test_votes_a_working_header_that_differs_from_the_base_is_refused(tree, monkeypatch):
    retail(monkeypatch, GOOD)
    register(tree)
    approve(tree, key_of(0x00C00000, 1), "spin")
    (tree / WIDGET_H).write_text("class Widget { public: virtual ~Widget(); }; // uncommitted\n")
    with pytest.raises(Refusal, match="differs from HEAD's"):
        plan(tree)


def test_votes_binding_needs_an_explicit_revision(tree):
    with pytest.raises(Refusal, match="explicit base"):
        rename.votes_bound_to_text(ctx_of(tree), "nl-x", "a|slot|W@0x00C00000|1", "spin", "a")
    with pytest.raises(Refusal, match="explicit revision"):
        rename.approved_slot_name(ctx_of(tree), "a|slot|W@0x00C00000|1", None)




# ------------------------------------------------------------ a plan across classes
#
# GiantBirdGuardMachine.cpp's private State view gives every derived class one slot 2 (`State::slot02`, aliased by
# hand to one class's body). Renaming it for one class leaves the others naming a symbol only the link misses, so
# --also RVA=CLASS:NEW moves another class's slot in the same plan, each proved on its own class's table.
G_OLD = "?rva00401300@Rva00401300@@QAEXXZ"
G_NEW = "?spin@Gizmo@@UAEXXZ"
G_CTOR = "??0Gizmo@@QAE@XZ"
G_HALT = "?halt@Gizmo@@UAEXXZ"
G_TABLE = 0x00800200
G_STORE = 0x00402110        # inside the Gizmo ctor row: mov dword ptr [ecx], G_TABLE
G_TABLES = {**GOOD, G_TABLE: ([0x00406000, 0x00401300, 0x00404100], {G_STORE: 0})}
G_COMPILED = {"Code/Game/Widget.cpp": COMPILED,
              "Code/Game/Gizmo.cpp": {"??_7Gizmo@@6B@": ["??_EGizmo@@UAEPAXI@Z", G_NEW, G_HALT]}}
GIZMO = """class Gizmo {
public:
    Gizmo();
    virtual ~Gizmo();
    virtual void spin();
    virtual void halt();
};
Gizmo::Gizmo() {}
void Gizmo::halt() {}
"""
G_BITS = f"""// cl: /O2
// {G_OLD} @ 0x00401300
class Rva00401300 {{ public: void rva00401300(); }};
void Rva00401300::rva00401300() {{}}
"""
G_BITS_PREPARED = f"""// cl: /O2
// {G_OLD} @ 0x00401300
class Gizmo {{ public: virtual void spin(); }};
void Gizmo::spin() {{}}
"""


def gizmo_tree(root):
    rows = FUNCTIONS + (f"{G_OLD},,0x00401300,40,Code/Game/GizmoBits.cpp,matched,vtable slot\n"
                        f"{G_CTOR},,0x00402100,64,Code/Game/Gizmo.cpp,matched,installs table 0x00C00200\n"
                        f"{G_HALT},,0x00404100,8,Code/Game/Gizmo.cpp,matched,slot 2\n"
                        "??_GShared@@UAEPAXI@Z,,0x00406000,28,Code/Game/Gadget.cpp,matched,ICF-shared\n")
    (root / "reverse/functions.csv").write_bytes(rows.encode())
    (root / "Code/Game/Gizmo.cpp").write_bytes(GIZMO.encode())
    (root / "Code/Game/GizmoBits.cpp").write_bytes(G_BITS.encode())
    _git(root, "-c", "user.name=t", "-c", "user.email=t@t", "add", "-A")
    _git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "gizmo")
    return root


def across_plan(root, also=((0x00401300, "spin", "Gizmo"),)):
    return rename.plan_rename("function", ctx=ctx_of(root), rva=0x00401000, to_class="Widget", new="spin",
                              prepared={"Code/Game/Bits.cpp": BITS_PREPARED.encode(),
                                        "Code/Game/GizmoBits.cpp": G_BITS_PREPARED.encode()},
                              also=list(also), approval_base="HEAD")


def test_a_plan_moves_slots_of_two_classes_tables(tree, monkeypatch):
    retail(monkeypatch, G_TABLES, compiled=G_COMPILED)
    root = gizmo_tree(tree)
    p = across_plan(root)
    assert [(g["cls"], g["table"], g["slot"]) for g in p.to_class["groups"]] == [("Widget", TABLE, 1),
                                                                                ("Gizmo", G_TABLE, 1)]
    assert p.subject() == ("Move 2 members into 2 classes (retail vftables: Widget 0x00C00000 slot 1; "
                           "Gizmo 0x00C00200 slot 1)")
    assert f"{G_OLD} -> {G_NEW}: retail table 0x00C00200 slot 1, installed by {G_CTOR}" in p.evidence
    assert set(p.claims) >= {0x00401000, 0x00401300}
    seen = []
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: seen.append(sources) or True)
    assert set(seen[0]) >= {"Code/Game/Bits.cpp", "Code/Game/GizmoBits.cpp", "Code/Game/Widget.cpp",
                            "Code/Game/Gizmo.cpp"}
    functions = (root / "reverse/functions.csv").read_text()
    for old, new in ((OLD, NEW), (G_OLD, G_NEW)):
        assert old not in functions and new in functions
    deleted = (root / "reverse/deleted_rows.csv").read_text().splitlines()
    # each move is tombstoned under its own class's table
    assert [line for line in deleted if line.startswith(f"{OLD},0x00401000,")][0].endswith(
        "(to-class: retail vftable 0x00C00000 slot 1)\"")
    assert [line for line in deleted if line.startswith(f"{G_OLD},0x00401300,")][0].endswith(
        "(to-class: retail vftable 0x00C00200 slot 1)\"")


@pytest.mark.parametrize("unit,table", [
    ("Code/Game/Gizmo.cpp", {"??_7Gizmo@@6B@": ["??_EGizmo@@UAEPAXI@Z", G_HALT, G_NEW]}),   # Gizmo's slots swapped
    ("Code/Game/Widget.cpp", {"??_7Widget@@6B@": [GDTOR, STOP, NEW]}),                    # Widget's
])
def test_each_class_proves_its_own_slot(tree, monkeypatch, unit, table):
    retail(monkeypatch, G_TABLES, compiled=dict(G_COMPILED, **{unit: table}))
    root = gizmo_tree(tree)
    with pytest.raises(Refusal, match="the vftable"):
        across_plan(root)


def test_a_plan_across_classes_rebuilt_wrong_restores_everything(tree, monkeypatch):
    retail(monkeypatch, G_TABLES, compiled=G_COMPILED)
    root = gizmo_tree(tree)
    before = {q.relative_to(root).as_posix(): q.read_bytes()
              for q in root.rglob("*") if q.is_file() and ".git" not in q.parts}
    p = across_plan(root)
    retail(monkeypatch, G_TABLES, compiled=dict(G_COMPILED, **{
        "Code/Game/Gizmo.cpp": {"??_7Gizmo@@6B@": ["??_EGizmo@@UAEPAXI@Z", G_HALT, G_NEW]}}))
    with pytest.raises(VerifyFailed, match="rebuilt vftable"):
        rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    after = {q.relative_to(root).as_posix(): q.read_bytes()
             for q in root.rglob("*") if q.is_file() and ".git" not in q.parts}
    assert after == before


def test_one_table_belongs_to_one_class(tree, monkeypatch):
    # Gizmo's row sits in Widget's table too: moving it into Gizmo there is refused before any table is shared
    tables = {TABLE: ([0x00403040, 0x00401000, 0x00401300], {CTOR_STORE: 0, G_STORE: 0})}
    retail(monkeypatch, tables, compiled=G_COMPILED)
    root = gizmo_tree(tree)
    with pytest.raises(Refusal):
        across_plan(root)


def test_a_plan_across_classes_names_each_address_and_new_name_once(tree, monkeypatch):
    retail(monkeypatch, G_TABLES, compiled=G_COMPILED)
    root = gizmo_tree(tree)
    with pytest.raises(Refusal, match="names one address twice"):
        across_plan(root, also=((0x00401300, "spin", "Gizmo"), (0x00401300, "turn", "Gizmo")))


@pytest.mark.parametrize("extra,passes", [
    ("?spin@State@@UAEXXZ", False),          # a class left on a renamed base slot: nothing defines it
    ("__purecall", True),                    # a pure base slot
    (STOP, True),                            # a row
])
def test_a_rebuilt_vftable_may_not_gain_a_name_nothing_defines(tree, monkeypatch, extra, passes):
    retail(monkeypatch, G_TABLES, compiled=G_COMPILED)
    root = gizmo_tree(tree)
    p = across_plan(root)
    # after the build a third class's table in the Gizmo unit names `extra`, which it did not before the plan
    retail(monkeypatch, G_TABLES, compiled=dict(G_COMPILED, **{
        "Code/Game/Gizmo.cpp": dict(G_COMPILED["Code/Game/Gizmo.cpp"], **{"??_7Idle@@6B@": [extra]})}))
    if passes:
        rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
        assert G_NEW in (root / "reverse/functions.csv").read_text()
    else:
        with pytest.raises(VerifyFailed, match=r"name what nothing defines: Code/Game/Gizmo.cpp's \?\?_7Idle@@6B@ "
                                               r"slot 0 names \?spin@State@@UAEXXZ"):
            rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
        assert G_OLD in (root / "reverse/functions.csv").read_text()


def test_a_name_the_unit_aliases_or_held_before_is_not_dangling(tree, monkeypatch):
    retail(monkeypatch, G_TABLES, compiled=dict(G_COMPILED, **{
        "Code/Game/Gizmo.cpp": dict(G_COMPILED["Code/Game/Gizmo.cpp"], **{"??_7Idle@@6B@": ["?old@State@@UAEXXZ"]})}))
    root = gizmo_tree(tree)
    p = across_plan(root)
    # the compiler's own deleting destructor is defined in the object it is compiled into
    objects = {"Code/Game/Gizmo.cpp": ({"??_EGizmo@@UAEPAXI@Z"}, {})}
    monkeypatch.setattr(rename, "object_link_names", lambda ctx, rel: objects.get(rel))
    # held before the plan: not the plan's doing
    assert rename.to_class_dangling_problems(ctx_of(root), p.to_class) == []
    gone = dict(p.to_class, vtables={})
    assert rename.to_class_dangling_problems(ctx_of(root), gone)
    # an /alternatename the object carries (from the unit or a header it includes) gives it, through a defined target
    objects["Code/Game/Gizmo.cpp"] = ({"??_EGizmo@@UAEPAXI@Z"}, {"?old@State@@UAEXXZ": STOP})
    assert rename.to_class_dangling_problems(ctx_of(root), gone) == []
    # an alias to nothing defined, or a cycle, gives nothing
    for aliases in ({"?old@State@@UAEXXZ": "?ghost@@YAXXZ"},
                    {"?old@State@@UAEXXZ": "?a@@YAXXZ", "?a@@YAXXZ": "?old@State@@UAEXXZ"}):
        objects["Code/Game/Gizmo.cpp"] = ({"??_EGizmo@@UAEPAXI@Z"}, aliases)
        assert rename.to_class_dangling_problems(ctx_of(root), gone)


def test_cli_also_class_wiring(tree, monkeypatch, capsys):
    retail(monkeypatch, G_TABLES, compiled=G_COMPILED)
    root = gizmo_tree(tree)
    argv = ["function", "--rva", "0x00401000", "--to-class", "Widget", "--new", "spin",
            "--also", "0x00401300=Gizmo:spin"]
    for rel, text in (("Code/Game/Bits.cpp", BITS_PREPARED), ("Code/Game/GizmoBits.cpp", G_BITS_PREPARED)):
        path = root.parent / (root.name + "-" + rel.rsplit("/", 1)[1] + ".prepared")
        path.write_bytes(text.encode())
        argv += ["--prepared", f"{rel}={path}"]
    assert rename.main(argv + ["--root", str(root), "--no-claim", "--no-object-scan", "--dry-run"]) == 0
    assert "Move 2 members into 2 classes" in capsys.readouterr().out
    with pytest.raises(SystemExit):        # a class only with --to-class
        rename.main(["function", "--rva", "0x00401000", "--new", "?x@@YAXXZ", "--respell", "--identity",
                     "--prepared", "Code/Game/Bits.cpp=x", "--also", "0x00401300=Gizmo:spin",
                     "--root", str(root), "--no-claim", "--dry-run"])



def test_r1_a_prepared_headers_includer_is_inspected(tree, monkeypatch):
    root = gizmo_tree(tree)
    (root / "Code/Game/View.h").write_text("struct View {};\n")
    (root / "Code/Game/Gadget.cpp").write_text('#include "View.h"\n' + GADGET)
    _git(root, "add", "Code/Game/View.h", "Code/Game/Gadget.cpp")
    _git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "header")
    retail(monkeypatch, G_TABLES, compiled=G_COMPILED)
    ctx = ctx_of(root)
    p = rename.plan_rename("function", ctx=ctx, rva=0x00401000, to_class="Widget", new="spin",
                           prepared={"Code/Game/Bits.cpp": BITS_PREPARED.encode(),
                                     "Code/Game/GizmoBits.cpp": G_BITS_PREPARED.encode(),
                                     "Code/Game/View.h": b"struct View { virtual void spin(); };\n"},
                           also=[(0x00401300, "spin", "Gizmo")], approval_base="HEAD")
    assert "Code/Game/Gadget.cpp" in p.to_class["units"]
    retail(monkeypatch, G_TABLES, compiled=dict(G_COMPILED, **{
        "Code/Game/Gadget.cpp": {"??_7View@@6B@": ["?spin@View@@UAEXXZ"]}}))
    with pytest.raises(VerifyFailed, match=r"Gadget.cpp's \?\?_7View@@6B@ slot 0 names \?spin@View@@UAEXXZ"):
        rename.apply_rename(p, ctx=ctx, verify=lambda ctx, sources: True)


def test_r1_a_retired_name_is_undefined_though_the_context_still_holds_it(tree, monkeypatch):
    root = gizmo_tree(tree)
    retail(monkeypatch, G_TABLES, compiled=G_COMPILED)
    ctx = ctx_of(root)                     # plan and apply share it, as the CLI does
    p = rename.plan_rename("function", ctx=ctx, rva=0x00401000, to_class="Widget", new="spin",
                           prepared={"Code/Game/Bits.cpp": BITS_PREPARED.encode(),
                                     "Code/Game/GizmoBits.cpp": G_BITS_PREPARED.encode()},
                           also=[(0x00401300, "spin", "Gizmo")], approval_base="HEAD")
    assert OLD in p.to_class["retired"] and G_OLD in p.to_class["retired"]
    retail(monkeypatch, G_TABLES, compiled=dict(G_COMPILED, **{
        "Code/Game/Gizmo.cpp": dict(G_COMPILED["Code/Game/Gizmo.cpp"], **{"??_7Idle@@6B@": [OLD]})}))
    with pytest.raises(VerifyFailed, match="names " + re.escape(OLD)):
        rename.apply_rename(p, ctx=ctx, verify=lambda ctx, sources: True)


def test_r1_a_stale_object_exempts_nothing(tree, monkeypatch):
    root = gizmo_tree(tree)
    ghost = "?spin@State@@UAEXXZ"
    stale = dict(G_COMPILED, **{"Code/Game/Gizmo.cpp": dict(G_COMPILED["Code/Game/Gizmo.cpp"],
                                                            **{"??_7Idle@@6B@": [ghost]})})
    retail(monkeypatch, G_TABLES, compiled=stale)
    # Gizmo.cpp's object predates its text: only current=False reads it
    monkeypatch.setattr(rename, "compiled_vtables",
                        lambda ctx, rel, current=True: None if rel == "Code/Game/Gizmo.cpp" and current
                        else stale.get(rel))
    monkeypatch.setattr(rename, "object_link_names",
                        lambda ctx, rel: ({"??_EGizmo@@UAEPAXI@Z"}, {}) if rel == "Code/Game/Gizmo.cpp" else None)
    p = across_plan(root)
    assert "Code/Game/Gizmo.cpp" not in p.to_class["vtables"]
    with pytest.raises(VerifyFailed, match="names " + re.escape(ghost)):
        rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)



def test_r2_aliases_are_read_from_the_object_as_the_linker_reads_them(tmp_path):
    # a /alternatename an #if drops never reaches the object; one an included header adds does
    import struct
    directive = b' /alternatename:?ghost@State@@UAEXXZ=?stop@Widget@@UAEXXZ '
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 20 + 40 + len(directive), 0, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".drectve", 0, 0, len(directive), 20 + 40, 0, 0, 0, 0, 0x00100A00)
    obj = tmp_path / "unit.obj"
    obj.write_bytes(header + section + directive + struct.pack("<I", 4))
    ctx = type("Ctx", (), {})()
    import unittest.mock
    with unittest.mock.patch.object(rename, "_source_object", lambda ctx, rel, current=True: obj):
        defined, aliases = rename.object_link_names(ctx, "Code/Game/Unit.cpp")
    assert aliases == {"?ghost@State@@UAEXXZ": "?stop@Widget@@UAEXXZ"}



def test_r3_a_weak_externals_default_is_no_alias(tmp_path, monkeypatch):
    # link.exe takes a weak external's search default (characteristics 1 or 2) for no reference: LNK2001
    import link_census
    obj = tmp_path / "unit.obj"
    obj.write_bytes(b"\0" * 64)
    monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: obj)
    monkeypatch.setattr(link_census, "object_symbols", lambda path, data=None: (
        {"_fall"}, set(), [("_weak", "_middle"), ("_middle", "_fall")], {"?alias@@YAXXZ": "_fall"}, set()))
    assert rename.object_link_names(None, "Code/Game/Unit.cpp") == ({"_fall"}, {"?alias@@YAXXZ": "_fall"})


@pytest.fixture
def compiler_weak_slot(tmp_path, monkeypatch):
    """Real COFF/rows/native-byte fixture; only compile currency is substituted.

    A weak's TagIndex may name an UNDEF external while its same-name scalar
    definition is a separate positive-section symbol, exactly as VC7.1 emits.
    """
    import hashlib
    import json
    from types import SimpleNamespace
    import build
    from test_gate_exploits import coff, TEXT, RDATA
    weak = "??_EWidget@@UAEPAXI@Z"
    scalar = "??_GWidget@@UAEPAXI@Z"
    table = "??_7Widget@@6B@"
    rel = "Code/Game/Weak.cpp"
    source, obj = tmp_path / "Weak.cpp", tmp_path / "weak.obj"
    text = b"class Widget { public: virtual ~Widget() {} };\n"
    source.write_bytes(text)
    owner = dict(name=scalar, target_rva="0x2000", target_size="6", source=rel, status="matched", notes="")
    rows = [owner]
    symbols = {scalar: [0x2000], "_destroy": [0x3000]}
    native = b"\xe8" + struct.pack("<i", 0x3000 - 0x2005) + b"\xc3"
    context = SimpleNamespace(rows=lambda: rows, pins=lambda: [], path=lambda _: source)
    monkeypatch.setattr(rename, "_source_object", lambda *a, **k: obj)
    monkeypatch.setattr(build, "compile_is_current", lambda path, out, **k: path.read_bytes() == text)
    monkeypatch.setattr(build, "load_all_function_rows", lambda: rows)
    monkeypatch.setattr(build, "load_symbol_map", lambda: symbols)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: native[:size] if rva == 0x2000 else None)
    def stamp():
        build._deps_sidecar(obj).write_text(json.dumps({
            "path": build._root_key(source), "object": hashlib.md5(obj.read_bytes()).hexdigest()}))
    def write(*, characteristic=2, tag=2, body=b"\xe8\0\0\0\0\xc3", code_flags=TEXT,
              definition_section=2, definition_type=32, weak_name=weak, default_name=scalar,
              relocation_kind=6, table_addend=0, duplicate=False, weak_default=False, callee="_destroy", chain=None):
        records = [(weak_name, 0, 0, 32, 105, 1)]
        if chain:
            records.append((default_name, 0, 0, 32, 105, 1))
        else:
            records.append((default_name, 0, 0, 32, 105 if weak_default else 2, 0))
        records += [(default_name, 0, definition_section, definition_type, 2, 0),
                    (table, 0, 1, 0, 2, 0), (callee, 0, 0, 32, 2, 0)]
        raw = bytearray(coff([
            (".rdata", RDATA | 0x1000, struct.pack("<I", table_addend), [(0, 0, relocation_kind)]),
            (".text$g", code_flags, body, [(1, 6 if chain else 5, 20)])], records))
        at, count = struct.unpack_from("<II", raw, 8)
        struct.pack_into("<II", raw, at + 18, tag, characteristic)
        if chain:
            struct.pack_into("<II", raw, at + 3 * 18, 0 if chain == "cycle" else 4, 2)
        if duplicate:
            raw[at + count * 18:at + count * 18] = raw[at + 3 * 18:at + 4 * 18]
            struct.pack_into("<I", raw, 12, count + 1)
        obj.write_bytes(raw)
        stamp()
    write()
    check = {"units": [rel], "vtables": {}, "retired": [], "new": "?moved@@YAXXZ"}
    return SimpleNamespace(ctx=context, rel=rel, obj=obj, source=source, owner=owner, rows=rows,
                           symbols=symbols, weak=weak, scalar=scalar, table=table, write=write,
                           stamp=stamp, build=build, check=check)


def test_compiler_deleting_weak_slot_uses_strict_local_definition_not_a_global_alias(compiler_weak_slot):
    f = compiler_weak_slot
    assert rename.object_link_names(f.ctx, f.rel) == ({f.scalar, f.table}, {})
    assert rename.object_compiler_weak_dtor_slots(f.ctx, f.rel) == {(f.table, 0, f.weak)}
    assert rename.to_class_dangling_problems(f.ctx, f.check) == []
    assert f.weak not in f.symbols  # the proof never installs a global weak binding


@pytest.mark.parametrize("changes", [
    {"characteristic": 0}, {"characteristic": 1}, {"characteristic": 3},
    {"tag": 0}, {"tag": 1}, {"tag": 4}, {"tag": 5}, {"tag": 99},
    {"weak_default": True}, {"definition_section": 0}, {"duplicate": True},
    {"chain": "terminal"}, {"chain": "cycle"},
    {"definition_type": 0}, {"definition_type": 0x30}, {"code_flags": 0x40000040},
    {"code_flags": 0x40000020}, {"code_flags": 0x60000040},
    {"body": b"\xe8\0\0\0\0\xc3\x90"},
    {"body": b"\xe8\0\0\0\0\x90"},
    {"body": b"\xe8\x01\0\0\0\xc3"}, {"callee": "_wrong_destroy"},
    {"default_name": "??_GOther@@UAEPAXI@Z"},
    {"weak_name": "_unrelated_weak"}, {"relocation_kind": 20}, {"table_addend": 4},
])
def test_compiler_weak_slot_missing_wrong_chained_cycle_or_unverified_code_stays_refused(compiler_weak_slot, changes):
    f = compiler_weak_slot
    f.write(**changes)
    assert rename.object_compiler_weak_dtor_slots(f.ctx, f.rel) == set()
    assert rename.to_class_dangling_problems(f.ctx, f.check)


@pytest.mark.parametrize("changes", [{}, {"definition_section": 0}, {"duplicate": True},
                                     {"body": b"\xe8\0\0\0\0\xc3\x90"}, {"callee": "_wrong_destroy"}])
def test_cross_unit_scalar_owner_still_requires_complete_strict_same_object_copy(compiler_weak_slot, changes):
    f = compiler_weak_slot
    f.owner["source"] = "Code/Game/CanonicalScalar.cpp"
    # A separate already-gated row supplies the real referrer's unit context;
    # its body is not the scalar body's proof. The API otherwise permits a
    # default owned/gated by another TU, so the new local checks are essential.
    f.rows.append(dict(name="_context", source=f.rel, status="matched", target_rva="0x1000", target_size="1", notes=""))
    f.write(**changes)
    slots = rename.object_compiler_weak_dtor_slots(f.ctx, f.rel)
    assert bool(slots) is (changes == {})
    assert bool(rename.to_class_dangling_problems(f.ctx, f.check)) is (changes != {})


@pytest.mark.parametrize("change", ["missing-row", "duplicate-row", "wrong-rva", "alias", "generated",
                                     "unverified", "stale-object", "stale-source", "missing-receipt",
                                     "wrong-receipt-path", "retired-weak", "retired-scalar", "strong-primary"])
def test_compiler_weak_slot_needs_current_real_row_object_and_receipt(compiler_weak_slot, change):
    import json
    f = compiler_weak_slot
    if change == "missing-row":
        f.rows.clear()
    elif change == "duplicate-row":
        f.rows.append(dict(f.owner))
    elif change == "wrong-rva":
        f.owner["target_rva"] = "0x2001"
    elif change == "alias":
        f.owner["notes"] = "object-symbol=??_GOther@@UAEPAXI@Z"
    elif change == "generated":
        f.owner["notes"] = "gen-alias"
    elif change == "unverified":
        f.owner["status"] = "unverified"
    elif change == "stale-object":
        f.obj.write_bytes(f.obj.read_bytes() + b"\0")
    elif change == "stale-source":
        f.source.write_bytes(f.source.read_bytes() + b"// changed\n")
    elif change == "missing-receipt":
        f.build._deps_sidecar(f.obj).unlink()
    elif change == "wrong-receipt-path":
        p = f.build._deps_sidecar(f.obj)
        r = json.loads(p.read_text()); r["path"] = "Code/Elsewhere.cpp"; p.write_text(json.dumps(r))
    elif change.startswith("retired-"):
        f.check["retired"] = [f.weak if change == "retired-weak" else f.scalar]
    elif change == "strong-primary":
        f.symbols[f.weak] = [0x9999]
    assert rename.object_compiler_weak_dtor_slots(f.ctx, f.rel, f.check["retired"]) == set()
    assert rename.to_class_dangling_problems(f.ctx, f.check)


@pytest.mark.skipif(sys.platform != "win32", reason="native VC7.1 deleting-dtor/link control")
def test_native_compiler_deleting_dtor_slot_links_its_real_same_object_default(monkeypatch):
    """Real compiler/linker/receipt and native slot; no game/runtime admission.

    The fixture's row/map/target bytes describe its actual linked DLL rather
    than impersonating a BFME retail row. All scalar relocations must resolve.
    """
    import json
    import uuid
    from types import SimpleNamespace
    import build
    import pefile
    root = build.vc71_root()
    monkeypatch.setenv("BFME_OBJSTORE", "off")
    work = build.ROOT / "build/test_rename_weak_dtor_native" / uuid.uuid4().hex[:8]
    work.mkdir(parents=True)
    source, obj = work / "weak.cpp", work / "weak.obj"
    source.write_text('// cl: /O1 /MD\n'
                      'class RenameWeakWidget { int value; public:\n'
                      'RenameWeakWidget():value(7){}\n'
                      'virtual ~RenameWeakWidget(){value=0;} };\n'
                      'extern "C" RenameWeakWidget *RenameWeakMake() { return new RenameWeakWidget; }\n')
    ok, log, code = build.try_compile_source(source, obj)
    assert ok and code == 0, log
    assert build.compile_is_current(source, obj)
    weak = "??_ERenameWeakWidget@@UAEPAXI@Z"
    scalar = "??_GRenameWeakWidget@@UAEPAXI@Z"
    table = "??_7RenameWeakWidget@@6B@"
    symbols = build.read_object_symbols(obj.read_bytes())
    assert sum(s["name"] == weak and s.get("storage") == 105 for s in symbols) == 1
    body, _ = build.read_object_symbol_bytes(obj, scalar, code_only=True)
    dll, mapping = work / "weak.dll", work / "weak.map"
    cmd = [str(root / "Vc7/bin/link.exe"), "/NOLOGO", "/MACHINE:X86", "/DLL", "/NOENTRY",
           "/NODEFAULTLIB", "/OPT:NOREF", "/OPT:NOICF", "/OUT:" + str(dll), "/MAP:" + str(mapping),
           str(obj), str(root / "Vc7/lib/msvcrt.lib"), str(root / "Vc7/lib/oldnames.lib")]
    linked = subprocess.run(cmd, cwd=build.ROOT, env=build.compiler_environment(root),
                            capture_output=True, text=True, errors="replace")
    assert linked.returncode == 0, linked.stdout + linked.stderr
    image = pefile.PE(str(dll))
    try:
        base = image.OPTIONAL_HEADER.ImageBase
        selected = {}
        for line in mapping.read_text(encoding="latin-1").splitlines():
            match = re.match(r"^\s+[0-9a-fA-F]+:[0-9a-fA-F]+\s+(\S+)\s+([0-9a-fA-F]{8})\s", line)
            if match:
                selected[match[1]] = int(match[2], 16) - base
        assert scalar in selected and table in selected
        # The native linker really takes the compiler's weak default for this
        # exact table word, without /FORCE or a custom provider/stub.
        actual_slot = struct.unpack("<I", image.get_data(selected[table], 4))[0]
        assert actual_slot == base + selected[scalar]
        rel = source.relative_to(build.ROOT).as_posix()
        row = dict(name=scalar, target_rva=hex(selected[scalar]), target_size=str(len(body)),
                   source=rel, status="matched", notes="")
        context = SimpleNamespace(rows=lambda: [row], pins=lambda: [], path=lambda _: source)
        ordinary_map = {name: [rva] for name, rva in selected.items() if name != weak}
        monkeypatch.setattr(build, "load_symbol_map", lambda: ordinary_map)
        monkeypatch.setattr(build, "load_all_function_rows", lambda: [row])
        monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: image.get_data(rva, size))
        monkeypatch.setattr(rename, "_source_object", lambda *a, **k: obj)
        assert rename.object_compiler_weak_dtor_slots(context, rel) == {(table, 0, weak)}
        assert weak not in ordinary_map
        check = {"units": [rel], "vtables": {}, "retired": [], "new": "?Moved@@YAXXZ"}
        assert rename.to_class_dangling_problems(context, check) == []
        (work / "proof.json").write_text(json.dumps({
            "scope": "Native fixture DLL only; not a BFME runtime/admission result", "link_exit": 0,
            "weak": weak, "scalar": scalar, "scalar_size": len(body), "scalar_rva": selected[scalar],
            "table_rva": selected[table], "selected_slot_va": actual_slot, "compiler_command": build.compiler_command(source, obj)[0]}))
    finally:
        image.close()



def test_r4_a_header_stale_object_exempts_nothing(tree, monkeypatch):
    # Gizmo.cpp's object predates a header it read: its table's names are not "held before"
    root = gizmo_tree(tree)
    ghost = "?spin@View@@UAEXXZ"
    compiled = dict(G_COMPILED, **{"Code/Game/Gizmo.cpp": dict(G_COMPILED["Code/Game/Gizmo.cpp"],
                                                               **{"??_7View@@6B@": [ghost]})})
    retail(monkeypatch, G_TABLES, compiled=compiled)
    monkeypatch.setattr(rename, "object_fresh", lambda ctx, rel: rel != "Code/Game/Gizmo.cpp")
    monkeypatch.setattr(rename, "object_link_names",
                        lambda ctx, rel: ({"??_EGizmo@@UAEPAXI@Z"}, {}) if rel == "Code/Game/Gizmo.cpp" else None)
    p = across_plan(root)
    assert "Code/Game/Gizmo.cpp" not in p.to_class["vtables"] and "Code/Game/Widget.cpp" in p.to_class["vtables"]
    with pytest.raises(VerifyFailed, match="names " + re.escape(ghost)):
        rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)


def test_r4_object_fresh_is_the_builds_strict_receipt(tmp_path, monkeypatch):
    import build
    obj = tmp_path / "unit.obj"
    obj.write_bytes(b"x")
    ctx = type("Ctx", (), {"path": lambda self, rel: tmp_path / rel})()
    monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: obj)
    seen = []
    monkeypatch.setattr(build, "compile_is_current", lambda source, output, strict=False: seen.append(strict) or False)
    assert rename.object_fresh(ctx, "Code/Game/Unit.cpp") is False and seen == [True]
    monkeypatch.setattr(build, "compile_is_current", lambda source, output, strict=False: True)
    assert rename.object_fresh(ctx, "Code/Game/Unit.cpp") is True
    monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: None)
    assert rename.object_fresh(ctx, "Code/Game/Unit.cpp") is False
