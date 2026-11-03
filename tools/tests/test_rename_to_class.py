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


def retail(monkeypatch, tables, compiled=None):
    """Inject the retail image {table rva: (slots, {store rva: this offset})}
    and the installer objects' vftables {source: {??_7 symbol: [names]}}."""
    monkeypatch.setattr(rename, "retail_vtables", lambda ctx: tables)
    built = {"Code/Game/Widget.cpp": COMPILED} if compiled is None else compiled
    monkeypatch.setattr(rename, "compiled_vtables", lambda ctx, rel, current=True: built.get(rel))


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
])
def test_to_class_symbol(old, new, expected):
    assert rename.to_class_symbol(old, "Widget", new) == expected


@pytest.mark.parametrize("old,new", [
    ("?name@Rva2Named@@QBEPBDXZ", "?name@Widget@@QAEPBDXZ"),     # cv changed
    ("?name@Rva2Named@@QBEPBDXZ", "?name@Widget@@QBEPBDXZ"),     # not virtual
    ("?name@Rva2Named@@QBEPBDXZ", "?name@Gadget@@UBEPBDXZ"),     # another class
    ("?f@Rva3@@QAEXPAV1@@Z", "f"),                               # back-reference in the parameters
])
def test_to_class_symbol_refusals(old, new):
    with pytest.raises(Refusal):
        rename.to_class_symbol(old, "Widget", new)


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
