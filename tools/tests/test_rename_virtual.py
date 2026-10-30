"""tools/rename.py function --virtual on a miniature tree: respelling a row
spelled non-virtual (QAE) as virtual (UAE) only on retail vtable evidence.
The retail image is injected (rename.retail_vtables / rename.retail_calls),
and so is verification, as in test_rename.py."""
import csv
import io
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

OLD = "?countParts@Widget@@QAEHH@Z"
NEW = "?countParts@Widget@@UAEHH@Z"
EH = "__ehhandler$" + OLD
CTOR = "??0Widget@@QAE@XZ"
DTOR = "??1Widget@@QAE@XZ"
GDTOR = "??_GWidget@@QAEPAXI@Z"
TABLE = 0x00800000          # retail table rva
CTOR_STORE = 0x00402010     # inside the ctor row: mov dword ptr [ecx], TABLE

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD},,0x00401000,40,Code/Game/Widget.cpp,matched,real name
{EH},,0x00790000,10,Code/Game/Widget.cpp,matched,gen-ehstub
$L100,,0x00790010,8,Code/Game/Widget.cpp,matched,gen-funclet;parent={OLD}
{CTOR},,0x00402000,64,Code/Game/Widget.cpp,matched,installs table 0x00C00000
{DTOR},,0x00403000,32,Code/Game/WidgetDtor.cpp,matched,dtor
{GDTOR},,0x00403040,28,Code/Game/WidgetDtor.cpp,matched,deleting dtor
?caller@Gadget@@QAEXXZ,,0x00404000,20,Code/Game/Gadget.cpp,matched,calls {OLD}
?shared@Widget@@QAEXXZ,,0x00405000,1,Code/Game/Widget.cpp,matched,ICF twin
??0Sprocket@@QAE@XZ,,0x00406000,64,Code/Game/Sprocket.cpp,matched,derived ctor
?spin@Other@@QAEXXZ,,0x00407000,6,Code/Game/Other.cpp,matched,unrelated class
??0Other@@QAE@XZ,,0x00408000,64,Code/Game/Other.cpp,matched,unrelated ctor
"""
SYMBOLS = f"""name,address,notes
{OLD},0x00401000,pin
?sharedToo@Gizmo@@QAEXXZ,0x00405000,folded with Widget::shared
"""
DELETED = 'name,target_rva,reason\n?gone@@YAXXZ,0x00100000,"old, retired"\n'
WIDGET = f"""// cl: /O2
// {OLD} @ 0x00401000
class Widget {{
public:
    Widget();
    int countParts(int n);
    void shared();
    virtual void spinUp();
}};
Widget::Widget() {{}}
int Widget::countParts(int n) {{ return n + 1; }}
void Widget::shared() {{}}
"""
GADGET = f"""class Widget {{ public: int countParts(int n); virtual void spinUp(); }};
#pragma comment(linker, "/alternatename:{OLD}=?other@@YAXXZ")
struct Gadget {{ void caller(); Widget *w; }};
void Gadget::caller() {{ w->countParts(3); }}\r
"""
WIDGET_DTOR = f"""// {DTOR} @ 0x00403000
class Widget {{
public:
    __declspec(noinline) ~Widget();
    virtual void spinUp();
}};
Widget::~Widget() {{}}
void deleteWidget(Widget *w) {{ delete w; }}
"""
SPROCKET = """class Widget { public: int countParts(int n); virtual void spinUp(); };
class Sprocket : public Widget { public: Sprocket(); };
Sprocket::Sprocket() {}
"""
OTHER = "class Other { public: Other(); void spin(); };\nOther::Other() {}\nvoid Other::spin() {}\n"


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
        "Code/Game/Widget.cpp": WIDGET,
        "Code/Game/Gadget.cpp": GADGET,
        "Code/Game/WidgetDtor.cpp": WIDGET_DTOR,
        "Code/Game/Sprocket.cpp": SPROCKET,
        "Code/Game/Other.cpp": OTHER,
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    return tmp_path


def retail(monkeypatch, tables, calls=None):
    """Inject the retail image: {table rva: (slots, {store rva: this offset})}
    and {body rva: call targets}."""
    monkeypatch.setattr(rename, "retail_vtables", lambda ctx: tables)
    monkeypatch.setattr(rename, "retail_calls", lambda ctx, rva, size: set((calls or {}).get(rva, ())))


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def plan(root, rva=0x00401000, **overrides):
    return rename.plan_rename("function", ctx=ctx_of(root), rva=rva, virtual=True, **overrides)


def snapshot(root):
    return {p.relative_to(root).as_posix(): p.read_bytes()
            for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}


# ------------------------------------------------------------ the decoration

@pytest.mark.parametrize("old,new", [
    ("?f@C@@QAEXH@Z", "?f@C@@UAEXH@Z"),                    # public
    ("?f@C@@IAEXH@Z", "?f@C@@MAEXH@Z"),                    # protected
    ("?f@C@@AAEXH@Z", "?f@C@@EAEXH@Z"),                    # private
    ("?name@C@@QBEPBDXZ", "?name@C@@UBEPBDXZ"),            # const method keeps its cv
    ("?f@Inner@Outer@@QAEXXZ", "?f@Inner@Outer@@UAEXXZ"),  # nested class
    ("??1C@@QAE@XZ", "??1C@@UAE@XZ"),
    ("??_GC@@QAEPAXI@Z", "??_GC@@UAEPAXI@Z"),
    ("?update@C@@QAE?AW4UpdateSleepTime@@XZ", "?update@C@@UAE?AW4UpdateSleepTime@@XZ"),
])
def test_virtual_symbol_changes_only_the_access_code(old, new):
    assert rename.virtual_symbol(old) == new


@pytest.mark.parametrize("mangled", [
    "?f@C@@UAEXH@Z",          # already virtual
    "?f@C@@SAXH@Z",           # static member
    "?f@@YAXH@Z",             # free function
    "?f@ns@@YAXH@Z",          # namespaced free function
    "??0C@@QAE@XZ",           # a constructor is never virtual
    "??4C@@QAEAAV0@ABV0@@Z",  # operator
    "__ehhandler$?f@C@@QAEXH@Z",
])
def test_virtual_symbol_refuses_what_cannot_be_virtual(mangled):
    with pytest.raises(Refusal):
        rename.virtual_symbol(mangled)


# ------------------------------------------------------------ the evidence gate

def test_refused_without_vtable_evidence(tree, monkeypatch):
    retail(monkeypatch, {})
    before = snapshot(tree)
    with pytest.raises(Refusal, match="no retail vtable slot"):
        plan(tree)
    assert snapshot(tree) == before


def test_refused_when_the_slot_belongs_to_an_unrelated_class(tree, monkeypatch):
    # Other's ctor installs a table whose slot holds Widget::countParts's address.
    retail(monkeypatch, {TABLE: ([0x00401000], {0x00408010: 0})})
    with pytest.raises(Refusal, match="belongs to Other, not Widget"):
        plan(tree)


def test_refused_on_a_displaced_store_without_a_primary_install(tree, monkeypatch):
    # a table stored at +0x8 by Widget's ctor, which installs nothing at +0: a member's table
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 8})})
    with pytest.raises(Refusal, match="no retail vtable slot"):
        plan(tree)


def test_refused_on_a_shared_body(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00405000], {CTOR_STORE: 0})})
    with pytest.raises(Refusal, match="shared body"):
        plan(tree, rva=0x00405000)


def test_refused_when_the_new_name_exists(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    raw = (tree / "reverse/symbols.csv").read_text() + f"{NEW},0x00409000,stray\n"
    (tree / "reverse/symbols.csv").write_text(raw)
    with pytest.raises(Refusal, match="already names a row or pin"):
        plan(tree)


def test_derived_table_counts_when_a_view_proves_the_base(tree, monkeypatch):
    # Sprocket's ctor installs the table; Sprocket.cpp declares Sprocket : Widget
    retail(monkeypatch, {TABLE: ([0x00401000], {0x00406010: 0})})
    p = plan(tree)
    assert "the table of Sprocket" in p.evidence and "derives from Widget" in p.evidence


# ------------------------------------------------------------ plan and apply

def test_full_virtual_respell(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00403040, 0x00401000], {CTOR_STORE: 0})})
    p = plan(tree, evidence="retail calls it only through the table")
    assert p.new == NEW and p.virtual
    assert "retail table 0x00C00000 slot 1, Widget's table" in p.evidence
    assert p.evidence.endswith("; retail calls it only through the table")
    assert p.verify == ["Code/Game/Gadget.cpp", "Code/Game/Sprocket.cpp", "Code/Game/Widget.cpp"]
    assert sorted(c for c in p.claims if isinstance(c, int)) == [0x00401000, 0x00404000, 0x00790000, 0x00790010]
    seen = []
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: seen.append(sources) or True)
    assert seen == [p.verify]

    widget = (tree / "Code/Game/Widget.cpp").read_text()
    assert "    virtual int countParts(int n);" in widget
    assert "int Widget::countParts(int n) { return n + 1; }" in widget     # a definition stays
    assert f"// {NEW} @ 0x00401000" in widget
    assert "    void shared();" in widget                                   # other members untouched
    gadget = (tree / "Code/Game/Gadget.cpp").read_bytes()
    assert b"class Widget { public: virtual int countParts(int n);" in gadget
    assert f'"/alternatename:{NEW}=?other@@YAXXZ"'.encode() in gadget
    assert gadget.endswith(b"w->countParts(3); }\r\n")                    # line endings kept
    sprocket = (tree / "Code/Game/Sprocket.cpp").read_text()
    assert "class Widget { public: virtual int countParts(int n);" in sprocket

    functions = (tree / "reverse/functions.csv").read_text()
    assert f"{NEW},,0x00401000,40," in functions
    assert f"__ehhandler${NEW},,0x00790000," in functions
    assert f"parent={NEW}" in functions and f"calls {NEW}" in functions
    assert OLD not in functions
    assert f"{NEW},0x00401000,pin" in (tree / "reverse/symbols.csv").read_text()
    deleted = (tree / "reverse/deleted_rows.csv").read_text()
    assert deleted.startswith(DELETED)
    assert f'{OLD},0x00401000,"Renamed to {NEW} by tools/rename.py (virtual: retail vtable slot)"\n' in deleted
    assert f'{EH},0x00790000,"Renamed to __ehhandler${NEW} by tools/rename.py' in deleted
    # no record of the old spelling: none is invented, the tier stays as it was
    assert not (tree / "reverse/name_basis.csv").exists()
    assert p.subject() == f"Respell {OLD} as virtual {NEW} (retail vtable slot)"


def test_a_recorded_name_carries_its_record(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    (tree / "reverse/name_basis.csv").write_text(
        "kind,old,new,basis,evidence,source,rva\n"
        f"function,?rva00401000@Widget@@QAEHH@Z,{OLD},inferred,agree:abc,Code/Game/Widget.cpp,0x00401000\n")
    p = plan(tree)
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    rows = list(csv.reader(io.StringIO((tree / "reverse/name_basis.csv").read_text())))
    assert rows[-1][:4] == ["carry", OLD, NEW, "inferred"]
    assert rows[-1][4].startswith("virtual respell by tools/rename.py: retail table 0x00C00000 slot 0")
    assert rows[-1][5:] == ["Code/Game/Widget.cpp", "0x00401000"]
    # the inferred landing stays revertible: its current spelling follows the carry row
    land = rename.landing(ctx_of(tree), "abc")
    assert land.current == NEW and land.target == "?rva00401000@Widget@@UAEHH@Z"


def test_byte_change_restores_everything(tree, monkeypatch):
    """A virtual declaration that changes a caller's call (now through the
    vtable) fails ./build.sh: every file comes back byte for byte."""
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    before = snapshot(tree)
    p = plan(tree)
    with pytest.raises(VerifyFailed):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: False)
    assert snapshot(tree) == before
    assert not list((tree / "build/rename-journal").glob("*.json"))


def test_destructor_family_is_respelled_together(tree, monkeypatch):
    # slot 0 holds the deleting dtor, whose retail body calls the dtor
    retail(monkeypatch, {TABLE: ([0x00403040, 0x00401000], {CTOR_STORE: 0})}, calls={0x00403040: {0x00403000}})
    p = plan(tree, rva=0x00403000)
    assert {(o, n) for o, n, _ in p.renamed_rows} == {
        (DTOR, "??1Widget@@UAE@XZ"), (GDTOR, "??_GWidget@@UAEPAXI@Z")}
    assert "called by ??_GWidget@@QAEPAXI@Z" in p.evidence
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    dtor = (tree / "Code/Game/WidgetDtor.cpp").read_text()
    assert "    virtual __declspec(noinline) ~Widget();" in dtor
    assert "// ??1Widget@@UAE@XZ @ 0x00403000" in dtor
    assert "Widget::~Widget() {}" in dtor


def test_destructor_needs_its_deleting_destructor_to_call_it(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00403040], {CTOR_STORE: 0})}, calls={0x00403040: {0x00409999}})
    with pytest.raises(Refusal, match="no deleting destructor of Widget on a retail vtable slot calls it"):
        plan(tree, rva=0x00403000)


def test_an_overload_set_is_refused(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    text = (tree / "Code/Game/Widget.cpp").read_text().replace(
        "    int countParts(int n);\n", "    int countParts(int n);\n    int countParts(float f);\n")
    (tree / "Code/Game/Widget.cpp").write_text(text)
    with pytest.raises(Refusal, match="overload set"):
        plan(tree)


def test_string_literal_spelling_is_refused(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    (tree / "Code/Game/Other.cpp").write_text(OTHER + f'const char *s = "{OLD}";\n')
    with pytest.raises(Refusal, match="string literal"):
        plan(tree)


def test_declarations_skip_calls_and_friends():
    code = rename.name_metric.strip(
        "class W {\npublic:\n    W() : m(countParts(1)) {}\n    friend int countParts(int);\n"
        "#if 1\n    int countParts(int n) { return n; }\n#endif\n    int m;\n};\n")
    found = rename.virtual_declarations(code, "W", "countParts")
    assert len(found) == 1 and not found[0][1]
    assert code[found[0][0]:].startswith("int countParts(int n)")


def test_cli_refuses_new_or_basis_with_virtual(tree):
    with pytest.raises(SystemExit):
        rename.main(["function", "--rva", "0x00401000", "--virtual", "--new", "x", "--root", str(tree),
                     "--no-claim", "--dry-run"])
    with pytest.raises(SystemExit):
        rename.main(["function", "--rva", "0x00401000", "--new", "countThings", "--root", str(tree),
                     "--no-claim", "--dry-run"])              # no --basis / --evidence: still required
