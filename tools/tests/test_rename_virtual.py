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
    ("??6C@@QAEAAV0@_N@Z", "??6C@@UAEAAV0@_N@Z"),
    ("??6C@@QAEAAV0@_J@Z", "??6C@@UAEAAV0@_J@Z"),
    ("??6C@@QAEAAV0@_K@Z", "??6C@@UAEAAV0@_K@Z"),
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
    "??6C@@QAEHH@Z",         # another return/operand shape
    "??6C@@QAEAAV0@H@Z",     # unsupported operand
    "??6C@@QBEAAV0@_N@Z",    # const member
    "??6C@@QAGAAV0@_N@Z",    # another calling convention
    "??6C@@QAEAAV0@_N0@Z",   # extra parameter
    "??6C@@QAEAAV0@AB_N@Z",  # reference rather than value
    "??6C@ns@@QAEAAV0@_N@Z", # qualified class needs its own scope selector
    "__ehhandler$?f@C@@QAEXH@Z",
])
def test_virtual_symbol_refuses_what_cannot_be_virtual(mangled):
    with pytest.raises(Refusal):
        rename.virtual_symbol(mangled)


@pytest.mark.parametrize("operand,declaration", [
    ("bool", "bool value"), ("bool", "const bool value"), ("bool", "bool const"),
    ("__int64", "signed __int64 value"),
    ("unsigned __int64", "unsigned  __int64 value"),
])
def test_stream_selector_preserves_other_overloads_and_const_members(operand, declaration):
    text = f"""class Widget {{ public:
  Widget &operator<<(int value);
  Widget &operator<<(const char *text);
  Widget &operator << ({declaration});
  Widget &operator<<({declaration}) const;
  Widget &operator>>({declaration});
}};
Widget &Widget::operator<<({declaration}) {{ return *this; }}
"""
    changed, made, _ = rename.respell_virtual_text(
        text, "Widget", "operator<<", [], stream_operand=operand)
    assert made == 1
    assert changed == text.replace(f"  Widget &operator << ({declaration});",
                                   f"  virtual Widget &operator << ({declaration});")


@pytest.mark.parametrize("declaration", [
    "static Widget &operator<<(bool);",
    "template<class T> Widget &operator<<(bool);",
    "int operator<<(bool);", "const Widget &operator<<(bool);",
    "Widget &operator<<(bool); Widget &operator<<(bool);",
])
def test_stream_selector_refuses_ambiguous_or_incompatible_declarations(declaration):
    with pytest.raises(Refusal):
        rename.respell_virtual_text("class Widget { public: " + declaration + " };",
                                    "Widget", "operator<<", [], stream_operand="bool")


@pytest.mark.parametrize("other", [
    "Widget &operator<<(bool &);", "Widget &operator<<(bool *);",
    "Widget &operator<<(bool, int);", "Widget &operator<<(Boolean);",
    "friend Widget &operator<<(Widget &, bool);",
    "class Nested { Widget &operator<<(bool); };",
])
def test_stream_selector_leaves_other_signatures_and_nested_declarations(other):
    text = "class Widget { public: " + other + " };"
    assert rename.respell_virtual_text(text, "Widget", "operator<<", [], stream_operand="bool") == (text, 0, 0)


def test_stream_selector_leaves_same_spelled_namespaced_class_untouched():
    text = "namespace Other { class Widget { public: Widget &operator<<(bool); }; }\n" \
           "class Widget { public: Widget &operator<<(bool); };\n"
    expected = text.replace("class Widget { public: Widget &operator<<(bool); };\n",
                            "class Widget { public: virtual Widget &operator<<(bool); };\n")
    assert rename.respell_virtual_text(text, "Widget", "operator<<", [], stream_operand="bool") == (expected, 1, 0)


def stream_tree(tree, encoded, operand):
    old = "??6Widget@@QAEAAV0@" + encoded + "@Z"
    for rel in ("reverse/functions.csv", "reverse/symbols.csv"):
        p = tree / rel
        p.write_text(p.read_text().replace(OLD, old))
    (tree / "Code/Game/Widget.cpp").write_text(f"""// {old}
class Widget {{ public:
  Widget();
  Widget &operator<<(int);
  Widget &operator<<({operand} value);
  Widget &operator<<(const char *);
}};
Widget::Widget() {{}}
Widget &Widget::operator<<({operand} value) {{ return *this; }}
""")
    (tree / "Code/Game/Gadget.cpp").write_text(f"""// calls {old}
class Widget {{ public: Widget &operator << ({operand}); Widget &operator<<(int); }};
void caller(Widget &w) {{ w << 1; }}
""")
    return old, old.replace("@@QAE", "@@UAE")


@pytest.mark.parametrize("encoded,operand", [("_N", "bool"), ("_J", "__int64"),
                                           ("_K", "unsigned __int64")])
def test_stream_virtual_transaction_selects_one_overload(tree, monkeypatch, encoded, operand):
    old, new = stream_tree(tree, encoded, operand)
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    p = plan(tree)
    assert p.new == new and p.virtual
    seen = []
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: seen.append(sources) or True)
    assert seen == [p.verify]
    widget = (tree / "Code/Game/Widget.cpp").read_text()
    assert f"virtual Widget &operator<<({operand} value);" in widget
    assert "  Widget &operator<<(int);" in widget
    assert "  Widget &operator<<(const char *);" in widget
    assert f"Widget &Widget::operator<<({operand} value) {{ return *this; }}" in widget
    assert f"virtual Widget &operator << ({operand});" in (tree / "Code/Game/Gadget.cpp").read_text()
    functions = (tree / "reverse/functions.csv").read_text()
    assert new in functions and old not in functions
    assert "parent=" + new in functions
    assert new in (tree / "reverse/symbols.csv").read_text()
    assert old in (tree / "reverse/deleted_rows.csv").read_text()


def test_stream_still_requires_native_class_installation_evidence(tree, monkeypatch):
    stream_tree(tree, "_N", "bool")
    retail(monkeypatch, {})
    before = snapshot(tree)
    with pytest.raises(Refusal, match="no retail vtable slot"):
        plan(tree)
    assert snapshot(tree) == before


def test_stream_byte_change_restores_everything(tree, monkeypatch):
    stream_tree(tree, "_N", "bool")
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    before = snapshot(tree)
    p = plan(tree)
    with pytest.raises(VerifyFailed):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: False)
    assert snapshot(tree) == before


@pytest.mark.parametrize("wrong_class", [False, True])
def test_stream_rejects_folded_bodies_and_unrelated_installers(tree, monkeypatch, wrong_class):
    stream_tree(tree, "_N", "bool")
    store = 0x00408010 if wrong_class else CTOR_STORE
    retail(monkeypatch, {TABLE: ([0x00401000], {store: 0})})
    if not wrong_class:
        p = tree / "reverse/functions.csv"
        p.write_text(p.read_text().replace("matched,real name", "matched,ICF twin"))
    before = snapshot(tree)
    with pytest.raises(Refusal, match="belongs to Other|shared body"):
        plan(tree)
    assert snapshot(tree) == before


@pytest.mark.parametrize("guard,message", [
    ("export", "canonical name"), ("new-pin", "already names"),
    ("tombstone", "tombstoned"), ("frozen", "frozen"),
])
def test_stream_keeps_protected_name_and_ledger_guards(tree, monkeypatch, guard, message):
    old, new = stream_tree(tree, "_N", "bool")
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    if guard == "export":
        p = tree / "reverse/exports.csv"
        p.write_text(p.read_text() + f"1,0x00401000,0x00401000,.text,code,{old}\n")
    elif guard == "new-pin":
        p = tree / "reverse/symbols.csv"
        p.write_text(p.read_text() + f"{new},0x00409900,existing name\n")
    elif guard == "tombstone":
        p = tree / "reverse/deleted_rows.csv"
        p.write_text(p.read_text() + f"{new},0x00401000,retired\n")
    else:
        (tree / "reverse/gate_baseline.txt").write_text(old + "\n")
    before = snapshot(tree)
    with pytest.raises(Refusal, match=message):
        plan(tree)
    assert snapshot(tree) == before


@pytest.mark.parametrize("succeeds", [False, True])
def test_stream_batch_checks_all_overloads_once_and_restores_on_failure(tree, monkeypatch, succeeds):
    old, new = stream_tree(tree, "_N", "bool")
    more = "??6Widget@@QAEAAV0@_J@Z"
    p = tree / "reverse/functions.csv"
    p.write_text(p.read_text() + f"{more},,0x00401100,40,Code/Game/Widget.cpp,matched,stream\n")
    p = tree / "Code/Game/Widget.cpp"
    p.write_text(p.read_text().replace("  Widget();", "  Widget();\n  Widget &operator<<(__int64);"))
    retail(monkeypatch, {TABLE: ([0x00401000, 0x00401100], {CTOR_STORE: 0})})
    (tree / rename.LOCK).touch()
    before = snapshot(tree)
    seen = []
    def verify(ctx, sources):
        seen.append(sources)
        assert "virtual Widget &operator<<(bool value);" in p.read_text()
        assert "virtual Widget &operator<<(__int64);" in p.read_text()
        return succeeds
    result = rename.run_batch(ctx_of(tree), [
        ("function", dict(rva=0x00401000, virtual=True)),
        ("function", dict(rva=0x00401100, virtual=True)),
    ], claim=False, verify=verify)
    assert len(seen) == 1 and not result.refused
    assert bool(result.failure) != succeeds
    if succeeds:
        functions = (tree / "reverse/functions.csv").read_text()
        assert new in functions and old not in functions
        assert more.replace("@@QAE", "@@UAE") in functions
    else:
        assert snapshot(tree) == before


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


# ------------------------------------------------------------ a prepared view
#
# 0x002BAEAB's unit held the Snapshot base as a member at +0 with a
# non-virtual destructor. A `virtual` keyword alone would add a vptr ahead of
# that member and shift every field, so the unit comes prepared with the base
# as a base class; the tool still respells, compiles and byte-gates it.
PREPARED_DTOR = f"""// {DTOR} @ 0x00403000
class WidgetBase {{ public: virtual ~WidgetBase(); }};
class Widget : public WidgetBase
{{
public:
    __declspec(noinline) virtual ~Widget();
    virtual void spinUp();
}};
Widget::~Widget() {{}}
"""
DTOR_TABLES = ({TABLE: ([0x00403040, 0x00401000], {CTOR_STORE: 0})}, {0x00403040: {0x00403000}})


def test_destructor_family_takes_a_prepared_view(tree, monkeypatch):
    retail(monkeypatch, *DTOR_TABLES)
    p = plan(tree, rva=0x00403000, prepared={"Code/Game/WidgetDtor.cpp": PREPARED_DTOR.encode()})
    assert {(o, n) for o, n, _ in p.renamed_rows} == {
        (DTOR, "??1Widget@@UAE@XZ"), (GDTOR, "??_GWidget@@UAEPAXI@Z")}
    assert "Code/Game/WidgetDtor.cpp" in p.verify
    assert "file:Code/Game/WidgetDtor.cpp" in p.claims
    seen = []
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: seen.append(sources) or True)
    assert seen == [p.verify]
    dtor = (tree / "Code/Game/WidgetDtor.cpp").read_text()
    assert "class Widget : public WidgetBase" in dtor           # the prepared shape, not a keyword edit
    assert "// ??1Widget@@UAE@XZ @ 0x00403000" in dtor            # its old spelling respelled
    assert "QAE" not in dtor


def test_a_prepared_view_is_restored_when_the_bytes_change(tree, monkeypatch):
    retail(monkeypatch, *DTOR_TABLES)
    before = snapshot(tree)
    p = plan(tree, rva=0x00403000, prepared={"Code/Game/WidgetDtor.cpp": PREPARED_DTOR.encode()})
    with pytest.raises(VerifyFailed):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: False)
    assert snapshot(tree) == before


def test_a_prepared_view_needs_matched_rows(tree, monkeypatch):
    retail(monkeypatch, *DTOR_TABLES)
    (tree / "Code/Game/Loose.cpp").write_bytes(b"int loose;\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="no matched rows to verify"):
        plan(tree, rva=0x00403000, prepared={"Code/Game/Loose.cpp": b"int loose2;\n"})


def test_a_prepared_view_still_needs_the_retail_evidence(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00403040], {CTOR_STORE: 0})}, calls={0x00403040: {0x00409999}})
    with pytest.raises(Refusal, match="no deleting destructor of Widget on a retail vtable slot calls it"):
        plan(tree, rva=0x00403000, prepared={"Code/Game/WidgetDtor.cpp": PREPARED_DTOR.encode()})


def test_prepared_goes_with_virtual_or_to_class_only(tree, monkeypatch):
    retail(monkeypatch, *DTOR_TABLES)
    with pytest.raises(Refusal, match="--prepared sources go with --to-class or --virtual only"):
        rename.plan_rename("function", ctx=ctx_of(tree), rva=0x00401000, new="countAll", basis="inferred",
                           evidence="agree:x", prepared={"Code/Game/WidgetDtor.cpp": PREPARED_DTOR.encode()})


# ------------------------------------------------------------ a view declared in an included header

VIEW_HEADER = "class Widget { public: int countParts(int n); virtual void spinUp(); };\n"
VIEWER = '#include "WidgetView.h"\nvoid viewer(Widget *w) { w->countParts(4); }\n'
BLIND = "class Widget;\nvoid blind(Widget *w);\n"


def _with_units(tree, monkeypatch, units):
    """Add WidgetView.h and the ledger units `units` ({rel: text}) with a row
    each, and report every unit's current object as referencing the old name."""
    (tree / "Code/Game/WidgetView.h").write_bytes(VIEW_HEADER.encode())
    rows = []
    for at, (rel, text) in enumerate(sorted(units.items())):
        (tree / rel).write_bytes(text.encode())
        rows.append(f"?unit{at}@@YAXPAVWidget@@@Z,,0x0040A{at:03X},8,{rel},matched,calls {OLD}\n")
    with open(tree / "reverse/functions.csv", "a", encoding="utf-8", newline="") as handle:
        handle.writelines(rows)
    _git(tree, "add", "-A")
    monkeypatch.setattr(rename, "object_referencers", lambda ctx, symbols: set(units))
    monkeypatch.setattr(rename, "object_confirms", lambda ctx, rel, symbols: True)


def test_a_unit_whose_view_lives_in_a_rewritten_header_is_covered(tree, monkeypatch):
    """BridgeScaffoldBehavior.cpp's UpdateModule view sits in its included
    BridgeScaffoldBehaviorView.h: the header gains `virtual`, so the unit is
    not one with nothing to reconcile; it is verified with the header."""
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    _with_units(tree, monkeypatch, {"Code/Game/Viewer.cpp": VIEWER})
    p = plan(tree)
    assert "Code/Game/WidgetView.h" in p.after
    assert "Code/Game/Viewer.cpp" in p.verify
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    assert (tree / "Code/Game/WidgetView.h").read_bytes() == VIEW_HEADER.replace(
        "public: int countParts", "public: virtual int countParts").encode()
    assert (tree / "Code/Game/Viewer.cpp").read_bytes() == VIEWER.encode()


def test_a_unit_no_rewritten_header_reaches_is_still_refused(tree, monkeypatch):
    """The header covers only its includers: a referencing unit that neither
    declares the method nor includes a rewritten view keeps the refusal."""
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    _with_units(tree, monkeypatch, {"Code/Game/Viewer.cpp": VIEWER, "Code/Game/Blind.cpp": BLIND})
    before = snapshot(tree)
    with pytest.raises(Refusal, match=r"Code/Game/Blind\.cpp's object references .*reconcile the view first"):
        plan(tree)
    assert snapshot(tree) == before


# ------------------------------------------------------------ --access: another access than the row's
#
# BehaviorModule::xfer (0x004C9C7D) is rowed public non-virtual (QAE) while
# the module views that call it as a protected virtual spell MAE: the plain
# respell gives only UAE. `--access protected` gives MAE and puts each
# in-class declaration under `protected:`, restoring the access it had.

PROTECTED = "?countParts@Widget@@MAEHH@Z"


@pytest.mark.parametrize("old,access,new", [
    ("?f@C@@QAEXH@Z", "protected", "?f@C@@MAEXH@Z"),
    ("?f@C@@QAEXH@Z", "private", "?f@C@@EAEXH@Z"),
    ("?f@C@@QAEXH@Z", "public", "?f@C@@UAEXH@Z"),
    ("?f@C@@IAEXH@Z", "public", "?f@C@@UAEXH@Z"),
    ("?name@C@@QBEPBDXZ", "protected", "?name@C@@MBEPBDXZ"),
    ("??1C@@QAE@XZ", "protected", "??1C@@MAE@XZ"),
])
def test_virtual_symbol_takes_the_requested_access(old, access, new):
    assert rename.virtual_symbol(old, access) == new


@pytest.mark.parametrize("mangled,access", [
    ("?f@C@@QAEXH@Z", "friend"),
    ("?f@C@@UAEXH@Z", "protected"),     # already virtual: an access change alone is no respell
    ("?f@@YAXH@Z", "protected"),        # free function
    ("?f@C@@SAXH@Z", "protected"),      # static member
])
def test_virtual_symbol_access_keeps_its_refusals(mangled, access):
    with pytest.raises(Refusal):
        rename.virtual_symbol(mangled, access)


@pytest.mark.parametrize("body,expected", [
    # a public declaration followed by more members: wrapped, public restored
    ("class W {\npublic:\n    int f(int n);\n    int g;\n};\n",
     "class W {\npublic:\n    protected: virtual int f(int n); public:\n    int g;\n};\n"),
    # the last member: no restore label
    ("class W {\npublic:\n    int g;\n    int f(int n);\n};\n",
     "class W {\npublic:\n    int g;\n    protected: virtual int f(int n);\n};\n"),
    # already protected: only `virtual`
    ("class W {\nprotected:\n    int f(int n);\n    int g;\n};\n",
     "class W {\nprotected:\n    virtual int f(int n);\n    int g;\n};\n"),
    # class default access is private, struct's public
    ("class W { int f(int n); int g; };\n", "class W { protected: virtual int f(int n); private: int g; };\n"),
    ("struct W { int f(int n); int g; };\n", "struct W { protected: virtual int f(int n); public: int g; };\n"),
    # an inline body is wrapped whole; a label that follows needs no restore
    ("class W {\npublic:\n    int f(int n) { if (n) { return n; } return 0; }\nprivate:\n    int g;\n};\n",
     "class W {\npublic:\n    protected: virtual int f(int n) { if (n) { return n; } return 0; }\nprivate:\n"
     "    int g;\n};\n"),
    # a nested class's label does not set the outer body's access
    ("class W {\n    class N { public: int h; };\npublic:\n    int f(int n);\n    int g;\n};\n",
     "class W {\n    class N { public: int h; };\npublic:\n    protected: virtual int f(int n); public:\n"
     "    int g;\n};\n"),
    # an already virtual declaration under another access still moves
    ("class W {\npublic:\n    virtual int f(int n);\n    int g;\n};\n",
     "class W {\npublic:\n    protected: virtual int f(int n); public:\n    int g;\n};\n"),
])
def test_access_wraps_each_declaration(body, expected):
    text, made, _ = rename.respell_virtual_text(body, "W", "f", [], access="protected")
    assert text == expected and made == 1


def test_no_access_keeps_the_declaration_where_it_is():
    body = "class W {\npublic:\n    int f(int n);\n    int g;\n};\n"
    assert rename.respell_virtual_text(body, "W", "f", [])[0] == body.replace("int f", "virtual int f")
    assert rename.respell_virtual_text(body, "W", "f", [], access="public")[0] == \
        body.replace("int f", "virtual int f")


def test_full_virtual_respell_with_protected_access(tree, monkeypatch):
    retail(monkeypatch, {TABLE: ([0x00403040, 0x00401000], {CTOR_STORE: 0})})
    p = plan(tree, access="protected")
    assert p.new == PROTECTED and p.virtual
    assert "protected access requested" in p.evidence
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    widget = (tree / "Code/Game/Widget.cpp").read_text()
    assert "    protected: virtual int countParts(int n); public:\n    void shared();" in widget
    assert "int Widget::countParts(int n) { return n + 1; }" in widget     # a definition stays
    assert f"// {PROTECTED} @ 0x00401000" in widget
    gadget = (tree / "Code/Game/Gadget.cpp").read_bytes()
    assert b"class Widget { public: protected: virtual int countParts(int n); public: virtual void spinUp(); };" \
        in gadget
    functions = (tree / "reverse/functions.csv").read_text()
    assert f"{PROTECTED},,0x00401000,40," in functions and f"__ehhandler${PROTECTED}" in functions
    assert OLD not in functions
    assert f"{OLD},0x00401000,\"Renamed to {PROTECTED} by tools/rename.py" in \
        (tree / "reverse/deleted_rows.csv").read_text()


def test_access_keeps_the_evidence_refusals(tree, monkeypatch):
    retail(monkeypatch, {})
    before = snapshot(tree)
    with pytest.raises(Refusal, match="no retail vtable slot"):
        plan(tree, access="protected")
    retail(monkeypatch, {TABLE: ([0x00405000], {CTOR_STORE: 0})})
    with pytest.raises(Refusal, match="shared body"):
        plan(tree, rva=0x00405000, access="protected")
    assert snapshot(tree) == before


def test_access_goes_with_virtual_only(tree, monkeypatch):
    with pytest.raises(Refusal, match="--access goes with --virtual only"):
        rename.plan_rename("function", ctx=ctx_of(tree), rva=0x00401000, new="countAll", basis="inferred",
                           evidence="agree:x", access="protected")
    with pytest.raises(SystemExit):
        rename.main(["function", "--rva", "0x00401000", "--access", "protected", "--new", "countAll",
                     "--basis", "inferred", "--evidence", "agree:x", "--root", str(tree), "--no-claim",
                     "--dry-run"])
    with pytest.raises(SystemExit):
        rename.main(["function", "--rva", "0x00401000", "--virtual", "--access", "friend", "--root", str(tree),
                     "--no-claim", "--dry-run"])


def test_cli_dry_run_takes_the_access(tree, monkeypatch, capsys):
    retail(monkeypatch, {TABLE: ([0x00401000], {CTOR_STORE: 0})})
    before = snapshot(tree)
    rename.main(["function", "--rva", "0x00401000", "--virtual", "--access", "protected", "--root", str(tree),
                 "--no-claim", "--no-object-scan", "--dry-run"])
    assert f"-> {PROTECTED}" in capsys.readouterr().out
    assert snapshot(tree) == before
