"""tools/rename.py collisions that are false rejects: each case below was a
real blocked rename, and each class is tested with its unsafe neighbours,
which stay refused. A miniature tree (a temporary git repository), so no
compiler is needed (verification is injected)."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal  # noqa: E402


@pytest.fixture(autouse=True)
def _evidence_gates_stubbed(monkeypatch):
    monkeypatch.setattr(rename, "check_agreement", lambda *a, **k: None)
    monkeypatch.setattr(rename, "check_canonical", lambda *a, **k: None)


def make_tree(root, files):
    for rel, text in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    subprocess.run(["git", "-C", str(root), "init", "-q"], check=True, capture_output=True)
    subprocess.run(["git", "-C", str(root), "add", "-A"], check=True, capture_output=True)
    return root


BASE_FILES = {
    "reverse/symbols.csv": "name,address,notes\n",
    "reverse/deleted_rows.csv": "name,target_rva,reason\n",
    "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
    "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
    "reverse/gate_baseline.txt": "",
}


def tree_of(tmp_path, functions, **sources):
    files = dict(BASE_FILES)
    files["reverse/functions.csv"] = "name,export_rva,target_rva,target_size,source,status,notes\n" + functions
    files.update(sources)
    return make_tree(tmp_path, files)


def plan_function(root, rva, new, **kwargs):
    ctx = rename.Context(root, object_scan=kwargs.pop("object_scan", False))
    return rename.plan_rename("function", ctx=ctx, rva=rva, new=new, basis="inferred",
                              evidence="agree:abc123", **kwargs)


# --------------------------------------------- name back-references (type digits)

@pytest.mark.parametrize("mangled", [
    # the same type again in argument 2: `0` is the TYPE table's first entry
    "?rva003BDE5D@ScriptActions@@QAEXABVAsciiString@@0@Z",
    "?Rva0032B389Join@@YA?AVAsciiString@@ABV1@0@Z",
    "?rva004D1C81@Rva004D1C81@@QAE?AURva004D1C81Iter@@PAURva004D1C81Node@@0@Z",
])
def test_type_table_digit_is_not_a_reference_to_the_identifier(mangled):
    _prefix, old, suffix = rename.split_function_name(mangled)
    assert not rename.refers_to_identifier(mangled, suffix)
    renamed = rename.rename_function_symbol(mangled, "Respelled")
    assert renamed == mangled.replace(old, "Respelled", 1)


@pytest.mark.parametrize("mangled", [
    "?rva00401000@@YAXPAV0@@Z",                       # the class is the identifier's fragment
    "?rva00401000@Widget@@QAEXAAV0@@Z",
    "?rva00401000@Widget@@QAEXPAVInner@0@@Z",         # a nested name continues from fragment 0
    "?rva00401000@Widget@@QAEPAU0@V0@@Z",
])
def test_name_reference_to_the_identifier_stays_refused(mangled):
    with pytest.raises(Refusal, match="back-reference"):
        rename.rename_function_symbol(mangled, "respelled")


def test_unreadable_symbol_keeps_the_textual_test():
    # outside the parser's subset (an unknown type letter): the textual test
    # still decides, and it cannot tell a type digit from a name reference
    odd = "?rva00401000@Widget@@QAEXPAUS@@0@Zq"
    with pytest.raises(rename.Unparsed):
        rename.fragments(odd)
    assert rename.refers_to_identifier(odd, odd.split("@", 1)[1])


def test_plan_clears_a_row_whose_signature_repeats_a_type(tmp_path):
    old = "?rva003BDE5D@ScriptActions@@QAEXABVAsciiString@@0@Z"
    tree = tree_of(
        tmp_path,
        f"{old},,0x003BDE5D,20,Code/Game/Actions.cpp,matched,address-derived\n",
        **{"Code/Game/Actions.cpp": "// cl: /O2\nvoid ScriptActions::rva003BDE5D(const AsciiString &a, const AsciiString &b) {}\n"})
    plan = plan_function(tree, 0x003BDE5D, "doIt")
    assert plan.new == "?doIt@ScriptActions@@QAEXABVAsciiString@@0@Z"
    assert "doIt" in plan.after["Code/Game/Actions.cpp"].decode()


# ------------------------------- game units that merely instantiate STLport

OWNER = "?rva00401000@Widget@@QAEHXZ"
STL_INST = ("?push_back@?$vector@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@_STL@@QAEXABQAUArmy@@@Z")
STL_PLAIN = "?_M_throw_length_error@?$_Vector_base@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@_STL@@QBEXXZ"
HOST_CPP = ("// cl: /O2\n// ?rva00401000@Widget@@QAEHXZ @ 0x00401000\n"
            "class Widget { public: int rva00401000(); };\nint Widget::rva00401000() { return 1; }\n")


def host_tree(tmp_path, *, source="Code/Game/Widget.cpp", extra_rows=(), notes="vendored=stlport-4.5.3; army vector",
              inst=STL_INST, own="address-derived"):
    rows = (f"{OWNER},,0x00401000,10,{source},matched,{own}\n"
            f"?count@Widget@@QAEHXZ,,0x00403000,6,{source},matched,real\n"
            f"{inst},,0x00402000,30,{source},matched,{notes}\n")
    rows += "".join(f"{name},,{addr},8,{source},matched,{n}\n" for name, addr, n in extra_rows)
    return tree_of(tmp_path, rows, **{source: HOST_CPP})


def test_unit_instantiating_stlport_over_its_own_types_is_not_vendored(tmp_path):
    tree = host_tree(tmp_path)
    ctx = rename.Context(tree, object_scan=False)
    assert not rename.is_vendored_path(ctx, "Code/Game/Widget.cpp")
    plan = plan_function(tree, 0x00401000, "countParts")
    assert plan.new == "?countParts@Widget@@QAEHXZ"
    assert plan.verify == ["Code/Game/Widget.cpp"]
    # the instantiation row itself is untouched
    assert STL_INST in plan.after["reverse/functions.csv"].decode()


@pytest.mark.parametrize("kwargs,why", [
    # nothing of the game's own in the file: upstream's unit
    (dict(own="vendored=stlport-4.5.3; the body"), "all rows vendored"),
    # another library's row keeps the whole unit vendored
    (dict(extra_rows=[("?gpConnect@@YAXXZ", "0x00404000", "vendored=gamespy-2004")]), "gamespy row"),
    # a plain (non-template) upstream function body is upstream's text
    (dict(extra_rows=[(STL_PLAIN, "0x00404000", "vendored=stlport-4.5.3")]), "plain stlport row"),
    # an STLport unit by name
    (dict(source="Code/Game/stlport_widget.cpp"), "stlport unit name"),
])
def test_other_vendored_mixes_stay_vendored(tmp_path, kwargs, why):
    if why == "plain stlport row":
        kwargs["extra_rows"] = [("?_M_foo@_Foo@_STL@@QAEXXZ", "0x00404000", "vendored=stlport-4.5.3")]
    tree = host_tree(tmp_path, **kwargs)
    source = kwargs.get("source", "Code/Game/Widget.cpp")
    ctx = rename.Context(tree, object_scan=False)
    assert rename.is_vendored_path(ctx, source), why
    with pytest.raises(Refusal, match="vendored"):
        plan_function(tree, 0x00401000, "countParts")


def test_vendored_dir_unit_stays_vendored_with_own_rows(tmp_path):
    tree = host_tree(tmp_path, source="Code/Libraries/Source/Lua/lvm.cpp")
    ctx = rename.Context(tree, object_scan=False)
    assert rename.is_vendored_path(ctx, "Code/Libraries/Source/Lua/lvm.cpp")


def test_a_word_the_instantiation_row_spells_is_still_shared(tmp_path):
    # renaming the class Army's helper would also respell `Army` in the vendored
    # template names; the shared-identifier test is what protects them
    inst = "?push_back@?$vector@PAUrva00401000@@V?$allocator@PAUrva00401000@@@_STL@@@_STL@@QAEXABQAUrva00401000@@@Z"
    tree = host_tree(tmp_path, inst=inst)
    with pytest.raises(Refusal, match="also spells"):
        plan_function(tree, 0x00401000, "countParts")


# ------------------------------------ params and locals: what a spelling can mean

MUTEX_H = """#pragma once
class MutexClass;
class LockClass {
public:
    LockClass(MutexClass &m, int flags);
    ~LockClass();
    void swap(Header *tmp);
    int lock(int m) { return m + 1; }
};
inline int twice(int m) { int a = m; return a + m; }
"""
BASE_H = """#pragma once
class Base { public: Base(int m); int m; };
class Orphan : public Missing { public: int region; };
"""
MACRO_H = """#pragma once
#define ROWCOL(a, b) ((a) * 4 + (b))
"""
FUNCS = """name,export_rva,target_rva,target_size,source,status,notes
?rva00501000@@YAHHH@Z,,0x00501000,10,Code/Game/Lock.cpp,matched,address-derived
?rva00502000@Derived@@QAEHH@Z,,0x00502000,10,Code/Game/Lock.cpp,matched,address-derived
?rva00503000@@YAHH@Z,,0x00503000,10,Code/Game/Lock.cpp,matched,address-derived
"""


def lock_tree(tmp_path, cpp, **headers):
    sources = {"Code/Game/Lock.cpp": cpp}
    for name, text in headers.items():
        sources[f"Code/Game/{name}.h"] = text
    return tree_of(tmp_path, FUNCS.split("\n", 1)[1], **sources)


LOCK_CPP = """// cl: /O2
#include "Mutex.h"
#include "Base.h"
int rva00501000(int m, int count) { int tmp = m + count; return tmp; }
int Derived::rva00502000(int m) { return m * 2; }
int rva00503000(int x) { int region2 = x; return region2; }
void other(int key) { int region = key; }
"""


def scoped(root, kind, function, name, new, source="Code/Game/Lock.cpp"):
    ctx = rename.Context(root, object_scan=False)
    return rename.plan_rename(kind, ctx=ctx, source=source, function=function, name=name, new=new,
                              basis="inferred", evidence="agree:abc123")


def test_header_spelling_as_parameters_and_bodies_is_not_a_clash(tmp_path):
    # mutex.h's `LockClass(MutexClass &m, ...)`, `lock(int m)` and `twice(int m)` spell `m`
    # as parameters and as a local; none of them is a thing a free function can mean
    tree = lock_tree(tmp_path, LOCK_CPP, Mutex=MUTEX_H, Base="class Missing {};\n")
    plan = scoped(tree, "param", "rva00501000", "m", "mutexValue")
    text = plan.after["Code/Game/Lock.cpp"].decode()
    assert "int rva00501000(int mutexValue, int count) { int tmp = mutexValue + count;" in text
    assert plan.verify == ["Code/Game/Lock.cpp"]


def test_header_local_and_macro_formal_are_not_a_clash(tmp_path):
    tree = lock_tree(tmp_path, LOCK_CPP, Mutex=MUTEX_H, Base="class Missing {};\n", Macro=MACRO_H)
    cpp = tree / "Code/Game/Lock.cpp"
    cpp.write_text(cpp.read_text().replace('#include "Base.h"', '#include "Base.h"\n#include "Macro.h"')
                   .replace("int rva00503000(int x) { int region2 = x; return region2; }",
                            "int rva00503000(int a) { int b = a; return ROWCOL(a, b); }"))
    subprocess.run(["git", "-C", str(tree), "add", "-A"], check=True, capture_output=True)
    plan = scoped(tree, "param", "rva00503000", "a", "first")
    assert "int rva00503000(int first) { int b = first; return ROWCOL(first, b); }" in \
        plan.after["Code/Game/Lock.cpp"].decode()
    # a macro formal of the same name does not make a LOCAL's name risky either
    assert scoped(tree, "local", "rva00503000", "b", "second")


def test_new_name_used_as_a_param_or_local_elsewhere_is_no_collision(tmp_path):
    # `region` is a local of other() and `key` its parameter: both already live in this file
    tree = lock_tree(tmp_path, LOCK_CPP, Mutex=MUTEX_H, Base="class Missing {};\n")
    plan = scoped(tree, "param", "rva00503000", "x", "region")
    assert "int rva00503000(int region)" in plan.after["Code/Game/Lock.cpp"].decode()
    assert scoped(tree, "param", "rva00503000", "x", "key")


@pytest.mark.parametrize("edit,match", [
    # the new name is used in the function itself
    (lambda t: t.replace("{ int region2 = x; return region2; }", "{ int region2 = x; return region2 + rows; }"),
     "already a name in"),
    # a file-scope name or a member of a class here
    (lambda t: t + "int rows;\n", "already a name"),
    (lambda t: t + "struct Holder { int rows; };\n", "already a name"),
    # a macro in the file
    (lambda t: t + "#define rows 4\n", "already a name"),
    (lambda t: t + "#define GETROWS() rows\n", "already a name"),
])
def test_new_name_clashes_stay_refused(tmp_path, edit, match):
    tree = lock_tree(tmp_path, edit(LOCK_CPP), Mutex=MUTEX_H, Base="class Missing {};\n")
    with pytest.raises(Refusal, match=match):
        scoped(tree, "param", "rva00503000", "x", "rows")


def test_new_name_in_the_in_class_prototype_stays_refused(tmp_path):
    cpp = ("// cl: /O2\nclass Box { public: int fit(int a, int rows); };\n"
           "int Box::fit(int a, int rows2) { return a + rows2; }\n")
    funcs = "?rva00504000@Box@@QAEHHH@Z,,0x00504000,10,Code/Game/Lock.cpp,matched,address-derived\n"
    tree = tree_of(tmp_path, funcs, **{"Code/Game/Lock.cpp": cpp})
    with pytest.raises(Refusal, match="in-class declaration"):
        scoped(tree, "param", "Box::fit", "a", "rows")
    assert scoped(tree, "param", "Box::fit", "a", "left")


@pytest.mark.parametrize("header,files,match", [
    # a macro named like the old name, object-like or with the name free in its body
    ("#define m 3\n", {}, "macro"),
    ("#define GETM() m\n", {}, "macro"),
    # the class's base declares a member of that name: an initializer list names it
    ("class Derived : public Base { public: Derived(int m); };\n", {"Base": BASE_H}, "member of Base"),
    # a base the headers never declare: any class member counts
    ("class Derived : public Gone { public: Derived(int x); };\n", {"Base": "class Gone2 { public: int m; };\n"},
     "member of"),
])
def test_old_name_header_meanings_stay_refused(tmp_path, header, files, match):
    cpp = '// cl: /O2\n#include "Head.h"\n#include "Base.h"\nint Derived::rva00502000(int m) { return m * 2; }\n'
    funcs = "?rva00502000@Derived@@QAEHH@Z,,0x00502000,10,Code/Game/Lock.cpp,matched,address-derived\n"
    sources = {"Code/Game/Lock.cpp": cpp, "Code/Game/Head.h": header}
    sources["Code/Game/Base.h"] = files.get("Base", "class Base { };\n")
    tree = tree_of(tmp_path, funcs, **sources)
    with pytest.raises(Refusal, match=match):
        scoped(tree, "param", "Derived::rva00502000", "m", "width")


def test_old_name_member_of_an_unrelated_class_in_a_header_is_no_clash(tmp_path):
    header = "class Derived : public Base2 { public: Derived(int x); };\nclass Base2 { };\n"
    cpp = '// cl: /O2\n#include "Head.h"\n#include "Other.h"\nint Derived::rva00502000(int m) { return m * 2; }\n'
    funcs = "?rva00502000@Derived@@QAEHH@Z,,0x00502000,10,Code/Game/Lock.cpp,matched,address-derived\n"
    tree = tree_of(tmp_path, funcs, **{"Code/Game/Lock.cpp": cpp, "Code/Game/Head.h": header,
                                       "Code/Game/Other.h": "struct Unrelated { int m; int region; };\n"})
    assert scoped(tree, "param", "Derived::rva00502000", "m", "width")
    # ... and it is a clash for the class the member belongs to
    (tree / "Code/Game/Head.h").write_text("class Derived : public Unrelated { public: Derived(int x); };\n")
    subprocess.run(["git", "-C", str(tree), "add", "-A"], check=True, capture_output=True)
    with pytest.raises(Refusal, match="member of Unrelated"):
        scoped(tree, "param", "Derived::rva00502000", "m", "width")


def test_new_name_as_base_member_in_a_header_stays_refused(tmp_path):
    header = "class Base { public: int width; };\nclass Derived : public Base { public: Derived(int x); };\n"
    cpp = '// cl: /O2\n#include "Head.h"\nint Derived::rva00502000(int m) { return m * 2; }\n'
    funcs = "?rva00502000@Derived@@QAEHH@Z,,0x00502000,10,Code/Game/Lock.cpp,matched,address-derived\n"
    tree = tree_of(tmp_path, funcs, **{"Code/Game/Lock.cpp": cpp, "Code/Game/Head.h": header})
    with pytest.raises(Refusal, match="member of Base"):
        scoped(tree, "param", "Derived::rva00502000", "m", "width")
    assert scoped(tree, "param", "Derived::rva00502000", "m", "height")


def test_inline_method_in_a_class_body_sees_the_bases_members(tmp_path):
    header = "class Base { public: int m; };\n"
    cpp = ('// cl: /O2\n#include "Head.h"\nclass Derived : public Base {\npublic:\n'
           "    Derived(int m) : m(m) {}\n};\n")
    funcs = "?rva00505000@Derived@@QAE@H@Z,,0x00505000,10,Code/Game/Lock.cpp,matched,address-derived\n"
    tree = tree_of(tmp_path, funcs, **{"Code/Game/Lock.cpp": cpp, "Code/Game/Head.h": header})
    with pytest.raises(Refusal):
        scoped(tree, "param", "Derived", "m", "width")


# ------------------------------------------- occurrence classes, directly

@pytest.mark.parametrize("code,word,kinds", [
    ("int g(int m) { return m; }\nint m;\n", "m", ["param", "fnbody", "ns"]),
    ("struct S { int m; void f(int m); int h() { return m; } };\n", "m", ["class:S", "param", "fnbody"]),
    ("#define ROWCOL(a, b) ((a) * (b))\n", "a", []),
    ("#define GET() a\n#define a 2\n", "a", ["macro", "macro"]),
    ("#define a(x) x\n", "a", ["macro"]),
    ("enum E { m };\nstruct S { enum { m2, m }; };\n", "m", ["ns", "class:S"]),
    ("template<class T> class X : public Y<T> { int m; };\ntypedef struct { int m; } Anon;\n", "m",
     ["class:X", "class:Anon"]),
    # an anonymous aggregate's members belong to the class it sits in, or to its typedef name
    ("typedef struct _M { union { struct { float a; }; float m[4][4]; }; } M, *PM;\n", "m", ["class:_M"]),
    ("class A { union { int m; }; };\n", "m", ["class:A"]),
    ("extern \"C\" { int m; }\n", "m", ["ns"]),
    ("int a[] = { m };\n", "m", ["fnbody"]),
    # a header name's extension is a path, not a macro spelling the word
    ("#include <stl/_algobase.c>\n#  include <vector3.h>\n", "c", []),
    ("#include <vector3.h>\n", "h", []),
    ("#include <x.h>\n#define h 1\n", "h", ["macro"]),
    ("#error Include NameKeyGenerator.h first\n#warning see x.h\n", "h", []),
])
def test_occurrence_kinds(code, word, kinds):
    assert rename.occurrence_kinds(rename.name_metric.strip(code), word) == kinds


# ------------------------------- one virtual function declared in a base and an override

def virtual_tree(tmp_path, base_decl="virtual void rva00601000(int a);", derived_decl="virtual void rva00601000(int b);",
                 extra="", other_views=None, rows=None):
    cpp = ("// cl: /O2\nclass Base { public:\n    " + base_decl + "\n    virtual void other();\n};\n"
           "class Derived : public Base { public:\n    " + derived_decl + "\n};\n" + extra +
           "void Derived::rva00601000(int b) {}\n")
    funcs = rows or "?rva00601000@Derived@@UAEXH@Z,,0x00601000,10,Code/Game/Cls.cpp,matched,address-derived\n"
    sources = {"Code/Game/Cls.cpp": cpp}
    sources.update(other_views or {})
    return tree_of(tmp_path, funcs, **sources)


def test_override_pair_in_one_unit_is_one_function(tmp_path):
    tree = virtual_tree(tmp_path)
    plan = plan_function(tree, 0x00601000, "load")
    text = plan.after["Code/Game/Cls.cpp"].decode()
    assert text.count("load(") == 3 and "rva00601000" not in text
    assert plan.new == "?load@Derived@@UAEXH@Z"


def test_the_base_side_of_a_pair_renames_with_its_override(tmp_path):
    rows = "?rva00601000@Base@@UAEXH@Z,,0x00601000,10,Code/Game/Cls.cpp,matched,address-derived\n"
    tree = virtual_tree(tmp_path, rows=rows, extra="void Base::rva00601000(int a) {}\n")
    text = plan_function(tree, 0x00601000, "load").after["Code/Game/Cls.cpp"].decode()
    assert "rva00601000" not in text and text.count("load(") == 4


@pytest.mark.parametrize("kwargs,why", [
    (dict(base_decl="void rva00601000(int a);"), "base declaration not virtual"),
    (dict(base_decl="virtual void rva00601000(long a);"), "other parameter type"),
    (dict(base_decl="virtual void rva00601000(int a, int c);"), "other arity"),
    (dict(base_decl="virtual void rva00601000(int a) const;"), "other constness"),
    (dict(base_decl="virtual void rva00601000(int a);\n    virtual void rva00601000(char a);"), "overload set"),
    (dict(base_decl="virtual void rva00601000(const Foo);", derived_decl="virtual void rva00601000(const Bar);"),
     "unnamed const parameters may differ in type"),
    (dict(base_decl="virtual void rva00601000(Ns::A);", derived_decl="virtual void rva00601000(Ns::B);"),
     "qualified types differ"),
])
def test_unproven_pairs_stay_refused(tmp_path, kwargs, why):
    tree = virtual_tree(tmp_path, **kwargs)
    with pytest.raises(Refusal, match="rva00601000 as a method of Base"):
        plan_function(tree, 0x00601000, "load")


def test_a_class_that_is_not_a_base_stays_foreign(tmp_path):
    cpp = ("// cl: /O2\nclass Other { public: virtual void rva00601000(int a); };\n"
           "class Derived { public: virtual void rva00601000(int b); };\nvoid Derived::rva00601000(int b) {}\n")
    funcs = "?rva00601000@Derived@@UAEXH@Z,,0x00601000,10,Code/Game/Cls.cpp,matched,address-derived\n"
    tree = tree_of(tmp_path, funcs, **{"Code/Game/Cls.cpp": cpp})
    with pytest.raises(Refusal, match="method of Other"):
        plan_function(tree, 0x00601000, "load")


def test_a_view_that_lacks_the_derived_class_stays_foreign(tmp_path):
    # another unit declares only the base's slot: that text proves no override
    tree = virtual_tree(tmp_path, other_views={
        "Code/Game/View.cpp": "class Base { public: virtual void rva00601000(int a); };\n"})
    with pytest.raises(Refusal, match="View.cpp also declares rva00601000 as a method of Base"):
        plan_function(tree, 0x00601000, "load")


def test_a_row_naming_the_base_slot_elsewhere_still_shares_the_word(tmp_path):
    rows = ("?rva00601000@Derived@@UAEXH@Z,,0x00601000,10,Code/Game/Cls.cpp,matched,address-derived\n"
            "?rva00601000@Base@@UAEXH@Z,,0x00602000,10,Code/Game/Cls.cpp,matched,address-derived\n")
    tree = virtual_tree(tmp_path, rows=rows, extra="void Base::rva00601000(int a) {}\n")
    with pytest.raises(Refusal, match="also spells"):
        plan_function(tree, 0x00601000, "load")


# ------------------------- occurrence scan fails closed on unbalanced brackets

UNBALANCED = [
    # an #if/#else split signature leaves two openers for one closer
    "#if defined(X)\nvoid set(int a, int b\n#else\nvoid set(int a\n#endif\n    , int m);\n",
    # ... or two closers for one opener, so a count clamped at zero would resume as if nothing happened
    "void set(int a, int m);\n#if X\n    ,\n#endif\nint z);\n",
    # braces: the two class heads each open one body, the #endif closes one
    "#if X\nclass A : public B {\n#else\nclass A {\n#endif\n    int m;\n};\n",
    "struct S { int m; };\n}\n",
]


@pytest.mark.parametrize("code", UNBALANCED)
def test_unbalanced_text_refuses_instead_of_classifying(code):
    with pytest.raises(rename.UnbalancedScan, match="cannot balance .* of head.h .*spelling of m"):
        rename.occurrence_kinds(rename.name_metric.strip(code), "m", "head.h")
    assert issubclass(rename.UnbalancedScan, Refusal)


def test_unbalanced_text_that_never_spells_the_word_hides_nothing():
    code = rename.name_metric.strip(UNBALANCED[0])
    assert rename.occurrence_kinds(code, "zzz", "head.h") == []


def test_balanced_text_is_unchanged_by_the_check():
    code = "#ifdef X\nextern \"C\" {\n#endif\nint m;\n#ifdef X\n}\n#endif\nvoid f(int (*cb)(int m), int m) { int z = m; }\n"
    assert rename.occurrence_kinds(rename.name_metric.strip(code), "m") == ["ns", "param", "param", "fnbody"]


@pytest.mark.parametrize("code", UNBALANCED[:3])
def test_header_that_does_not_balance_refuses_the_param_rename(tmp_path, code):
    # the unbalanced header ends before the class that declares `m` is read, so
    # a fail-open scan would have found only 'param' spellings and renamed
    header = code + "class Derived : public Base { public: Derived(int x); int m; };\n"
    cpp = LOCK_CPP.replace('#include "Base.h"', '#include "Base.h"\n#include "Head.h"')
    tree = lock_tree(tmp_path, cpp, Mutex=MUTEX_H, Base="class Missing {};\n", Head=header)
    with pytest.raises(Refusal, match="cannot balance .* included header Code/Game/Head.h"):
        scoped(tree, "param", "Derived::rva00502000", "m", "width")


def test_unit_that_does_not_balance_refuses_the_new_name_check(tmp_path):
    cpp = LOCK_CPP + "#if X\nint rva00509000(int a,\n#else\nint rva00509000(int a, int b,\n#endif\n    int tally);\n"
    tree = lock_tree(tmp_path, cpp, Mutex=MUTEX_H, Base="class Missing {};\n")
    with pytest.raises(Refusal, match="cannot balance .* of Code/Game/Lock.cpp"):
        scoped(tree, "param", "rva00503000", "x", "tally")
    # the balanced original still plans
    tree2 = lock_tree(tmp_path / "ok", LOCK_CPP, Mutex=MUTEX_H, Base="class Missing {};\n")
    assert scoped(tree2, "param", "rva00503000", "x", "tally")


# ----------------------- a local's scope: every spelling must sit inside a declaring block

@pytest.mark.parametrize("body", [
    # the simple shapes: the declaration and every use below it in its block
    "{ int a = 1; return a + a; }",
    "{ int a = 1; { a += 1; } return a; }",
    # sibling blocks each declare their own
    "{ if (x) { int a = 1; use(a); } else { int a = 2; use(a); } }",
    # a nested redeclaration shadows consistently
    "{ int a = 1; { int a = 2; use(a); } use(a); }",
    # a for-init variable lives in the loop, braced or not
    "{ for (int a = 0; a < n; ++a) { use(a); } }",
    "{ for (int a = 0; a < n; ++a) use(a); }",
    "{ while (int a = next()) { use(a); } }",
    "{ try { f(); } catch (Err a) { use(a); } }",
    # `@@` marks the first spelling no declaration reaches: after the block, the loop or the statement
    "{ if (x) { int a = 1; use(a); } return @@a; }",
    "{ { int a = 1; } use(@@a); }",
    "{ for (int a = 0; a < n; ++a) { use(a); } return @@a; }",
    "{ for (int a = 0; a < n; ++a) use(a); return @@a; }",
    "{ if (int a = next()) use(a); else use(@@a); }",
    "{ int a = 1; } @@a = 2;",
    # a spelling in a sibling block that declares nothing
    "{ if (x) { int a = 1; use(a); } else { use(@@a); } }",
    # before the declaration
    "{ use(@@a); int a = 1; }",
    # `type name` is also how a product or a mask reads: none of these declares a
    "{ if (c) { int a = 1; use(a); } return foo(w * @@a); }",
    "{ if (c) { int a = 1; use(a); } return foo(w & @@a); }",
    "{ if (c) { int a = 1; use(a); } return (w * @@a); }",
    "{ if (c) { int a = 1; use(a); } if (w & @@a) { use(a); } }",
    "{ if (w & @@a) { use(a); } }",
    "{ while (w * @@a) { use(a); } }",
    "{ int a = 1; use(a); } for (int i = 0; i < n; ++i) use(w * @@a);",
    # a condition's declaration has an initializer; a loop's is its first clause; a handler's is its parameter
    "{ if (Thing *a = next()) { use(a); } return @@a; }",
    "{ for (Thing *a = 0; a; a = a->next) use(a); }",
    "{ try { f(); } catch (Err &a) { use(a); } return @@a; }",
])
def test_local_scope_gaps(body):
    expected = body.index("@@") if "@@" in body else None
    assert rename.local_use_outside_scope(body.replace("@@", ""), "a") == expected


OUTER_H = "extern int a;\nint use(int v);\n"
SCOPE_CPP = """// cl: /O2
#include "Outer.h"
int rva00501000(int x) { if (x) { int a = 1; x += a; } return x + a; }
int rva00503000(int x) { if (x) { int a = 1; x += a; } else { int a = 2; x -= a; } return x; }
int rva00502000(int x) {
    for (int a = 0; a < x; ++a) {
        x += use(a);
    }
    return x;
}
"""


def scope_tree(tmp_path, cpp=SCOPE_CPP):
    funcs = "".join(f"?rva{r:08X}@@YAHH@Z,,0x{r:08X},10,Code/Game/Lock.cpp,matched,address-derived\n"
                    for r in (0x501000, 0x502000, 0x503000))
    return tree_of(tmp_path, funcs, **{"Code/Game/Lock.cpp": cpp, "Code/Game/Outer.h": OUTER_H})


def test_local_in_a_nested_block_with_the_outer_name_used_after_it_stays_refused(tmp_path):
    # `return x + a` after the block names the header's global a: renaming the
    # block's local must not respell it
    tree = scope_tree(tmp_path)
    with pytest.raises(Refusal, match="a is used in rva00501000 at line 3, outside the block"):
        scoped(tree, "local", "rva00501000", "a", "step")


@pytest.mark.parametrize("tail", ["use(x * a)", "use(x & a)", "x * a"])
def test_a_product_with_the_outer_name_after_the_block_stays_refused(tmp_path, tail):
    # `use(x * a)` reads as the declaration `x *a` to a type-name scan: it is a use of the global
    cpp = SCOPE_CPP.replace("return x + a; }", f"return {tail}; }}")
    tree = scope_tree(tmp_path, cpp)
    with pytest.raises(Refusal, match="a is used in rva00501000 at line 3, outside the block"):
        scoped(tree, "local", "rva00501000", "a", "step")


def test_locals_confined_to_their_blocks_still_rename(tmp_path):
    tree = scope_tree(tmp_path)
    plan = scoped(tree, "local", "rva00503000", "a", "step")
    text = plan.after["Code/Game/Lock.cpp"].decode()
    assert "{ int step = 1; x += step; } else { int step = 2; x -= step; }" in text
    plan = scoped(tree, "local", "rva00502000", "a", "index")
    assert "for (int index = 0; index < x; ++index)" in plan.after["Code/Game/Lock.cpp"].decode()
    assert "x += use(index);" in plan.after["Code/Game/Lock.cpp"].decode()


# ------------- STLport rows: the row's own scope decides, not what its signature spells

@pytest.mark.parametrize("mangled", [
    STL_INST,                                                              # member of a class template instance
    "??0?$vector@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@_STL@@QAE@XZ",   # constructor
    "??1?$vector@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@_STL@@QAE@XZ",   # destructor
    "??$__copy@PAPAUArmy@@PAPAU1@@_STL@@YAPAPAUArmy@@PAPAU1@00@Z",        # function template instance
    "??$?9PBD@_STL@@YA_NABV?$reverse_iterator@PBD@0@0@Z",                # operator template instance
    "?_M_fill@?$_Vector_base@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@_STL@@QAEXXZ",
])
def test_template_instances_in_stl_are_instantiations(mangled):
    assert rename.is_stlport_instantiation(mangled)


@pytest.mark.parametrize("mangled", [
    # a plain upstream method that merely takes (and returns) a template instance
    "?erase@list@_STL@@QAE?AV?$_List_iterator@PAUArmy@@@2@V32@@Z",
    "?assign@Holder@_STL@@QAEXABV?$vector@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@2@@Z",
    "?__write_float@_STL@@YAXAAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@1@HHN@Z",
    # a template instance outside _STL
    "?push_back@?$vector@PAUArmy@@V?$allocator@PAUArmy@@@Other@@@Other@@QAEXXZ",
    "?push_back@?$vector@H@Other@@QAEXXZ",
    # not a symbol the parser reads
    "_push_back", "??_7vector@_STL@@6B@", "?__x@?$v@Q",
])
def test_signature_spelling_a_template_is_not_an_instantiation(mangled):
    assert not rename.is_stlport_instantiation(mangled)


def test_back_referenced_stl_scope_is_read_from_the_fragment_table():
    # the first `_STL` sits in the allocator's arguments; the scope's own is a digit
    mangled = "?push_back@?$vector@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@_STL@@QAEXABQAUArmy@@@Z"
    parts = rename.qualified_name_parts(mangled)
    assert parts == [("push_back", False), ("vector", True), ("_STL", False)]
    # as MSVC writes it: push_back=0 vector=1 Army=2 allocator=3 _STL=4, and the scope is a `4`
    for backref in ("?push_back@?$vector@PAUArmy@@V?$allocator@PAU2@@_STL@@@4@@QAEXXZ",
                    "?push_back@?$vector@PAUArmy@@V?$allocator@PAU2@@_STL@@@4@@QAEXABQAU2@@Z"):
        assert rename.qualified_name_parts(backref) == parts
        assert rename.is_stlport_instantiation(backref)


def test_a_plain_stlport_method_taking_a_template_instance_keeps_its_unit_vendored(tmp_path):
    plain = "?assign@Holder@_STL@@QAEXABV?$vector@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@2@@Z"
    tree = host_tree(tmp_path, extra_rows=[(plain, "0x00404000", "vendored=stlport-4.5.3")])
    ctx = rename.Context(tree, object_scan=False)
    assert rename.is_vendored_path(ctx, "Code/Game/Widget.cpp")
    with pytest.raises(Refusal, match="vendored"):
        plan_function(tree, 0x00401000, "countParts")
    # the same unit with only the instantiation stays a game unit
    assert not rename.is_vendored_path(rename.Context(host_tree(tmp_path / "ok"), object_scan=False),
                                       "Code/Game/Widget.cpp")
