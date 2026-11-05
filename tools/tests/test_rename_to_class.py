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
