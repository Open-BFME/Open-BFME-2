"""StandInElementFamily read as a struct (W5, tools/retail_identity.py OPAQUE_REF_DEQUE_DESTROY and
OPAQUE_REF_DEQUE_DTOR): stand_in_swap keeps the class-key U and the struct back-references, the entries are what was
reviewed, and rename.py holds a struct reading to the class contract (stand_in_element_problem)."""
import json
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
import retail_identity as R  # noqa: E402

A, B = R.OPAQUE_REF_DEQUE_DESTROY, R.OPAQUE_REF_DEQUE_DTOR
C = R.Fact


def test_the_entries_are_what_was_reviewed():
    for fam in (A, B):
        assert fam in R.FAMILIES and isinstance(fam, R.StandInElementFamily)
        assert (fam.new, fam.new_key, fam.stride) == ("OpaqueRefElement4", "U", 4)
        assert all(R.family_of(at, fam.respell(old)) is fam for at, (old, _f) in fam.rows.items())
        assert not fam.pins and not fam.duplicates
    assert (A.old, A.copy, set(A.rows), set(A.members), set(A.retired)) == (
        "Rva00055880Element", 0x00055880, {0x00055880}, {0x00054FD9}, {0x00054FD9})
    assert (B.old, B.copy, set(B.rows), set(B.members), set(B.retired)) == (
        "Rva00056DEBElement", 0x000579DE, {0x00056DEB, 0x000579DE}, {0x00055880}, {0x00055880})
    # the second family's member is the first's respelled row
    assert B.members[0x00055880] == A.respell(A.rows[0x00055880][0])
    assert B.respell(B.rows[0x000579DE][0]) == ("??1?$deque@UOpaqueRefElement4@@V?$allocator@UOpaqueRefElement4@@@"
                                               "_STL@@@_STL@@QAE@XZ")


def test_the_real_image_states_them_all():
    if not R.build.EXE.exists():
        pytest.skip("no retail image here")
    for fam in (A, B):
        assert R.facts_problems(fam.facts()) == []


@pytest.mark.parametrize("name, key, want", [
    ("?f@@YAXPAUOld@@@Z", "U", "?f@@YAXPAUNew@@@Z"),
    ("?f@@YAXPAUOld@@@Z", "V", "?f@@YAXPAVNew@@@Z"),
    ("??4Old@@QAEAAU0@ABU0@@Z", "U", "??4New@@QAEAAU0@ABU0@@Z"),     # a struct's back-references stay struct
    ("??4Old@@QAEAAU0@ABU0@@Z", "V", "??4New@@QAEAAV0@ABV0@@Z"),     # P134's class reading, unchanged
])
def test_the_swap_follows_the_class_key(name, key, want):
    assert R.stand_in_swap(name, "Old", "New", key) == want


def test_the_default_key_is_the_class_one():
    assert R.stand_in_swap("?f@@YAXPAUOld@@@Z", "Old", "New") == "?f@@YAXPAVNew@@@Z"
    assert R.SCORED_KILL_TRACKER_VECTOR.new_key == "V"


def test_no_other_key():
    with pytest.raises(ValueError, match="no class-key"):
        R.stand_in_swap("?f@@YAXPAUOld@@@Z", "Old", "New", "T")


def kwargs(fam):
    return dict(old=fam.old, new=fam.new, new_key=fam.new_key, copy=fam.copy, stride=fam.stride,
                spellings=dict(fam.spellings), members=dict(fam.members), bindings=tuple(fam.bindings),
                rows=dict(fam.rows), pins=dict(fam.pins), duplicates=dict(fam.duplicates), retired=dict(fam.retired))


def test_the_real_kwargs_build():
    for fam in (A, B):
        R.StandInElementFamily(**kwargs(fam))


OLD_A = A.rows[0x00055880][0]


@pytest.mark.parametrize("label, change, message", [
    ("the entry read as a class", lambda k: k.update(new_key="V"), "stand-in swap alone"),
    ("a spelling with the class key", lambda k: k["spellings"].update(
        {OLD_A: R.stand_in_swap(OLD_A, A.old, A.new, "V")}), "stand-in swap alone"),
    ("another key", lambda k: k.update(new_key="T"), "no class-key"),
    ("a row reaching no member", lambda k: k["rows"].update({0x00055880: (OLD_A, (C("calls", 0x000558A1, 0x1000),))}),
     "reaches no member|which is not"),
])
def test_the_constructor_refuses(label, change, message):
    k = kwargs(A)
    change(k)
    with pytest.raises(ValueError, match=message):
        R.StandInElementFamily(**k)


# ---------------------------------------------------------------- rename.py's ledger tie for a struct reading

HEADER = "Code/Lib/OpaqueRefElement4.h"


class Ctx:
    """The parts of rename.Context stand_in_element_problem reads."""

    def __init__(self, contract, header=b"typedef char X[sizeof(OpaqueRefElement4)==4?1:-1];\n", units=None):
        self.files = {HEADER: header, **(units or {})}
        if contract is not None:
            self.files["reverse/class_contracts/OpaqueRefElement4.json"] = json.dumps(contract).encode()

    def dicts(self, rel):
        assert rel == rename.CANONICAL_CLASSES
        return [{"class": "OpaqueRefElement4", "header": HEADER}]

    def read(self, rel):
        return self.files.get(rel)


def rows():
    out = [dict(name=name, target_rva=f"0x{at:08X}", target_size="64", status="matched", source="Code/Lib/X.cpp")
           for at, name in A.members.items()]
    out += [dict(name=old, target_rva=f"0x{at:08X}", target_size="64", status="matched", source="Code/Lib/X.cpp")
            for at, (old, _f) in A.rows.items()]
    return out


def test_a_struct_reading_matching_its_contract_passes_the_key_check():
    assert rename.stand_in_element_problem(Ctx({"key": "struct"}), rows(), A) is None


@pytest.mark.parametrize("contract, says", [({"key": "class"}, "says class"), ({}, "says nothing"),
                                            (None, "says nothing")])
def test_a_struct_reading_against_its_contract_refuses(contract, says):
    assert says in rename.stand_in_element_problem(Ctx(contract), rows(), A)


# ---------------------------------------------------------------- the compiled size in the row units (W5)

UNIT = "Code/Lib/X.cpp"
NO_HEADER_ASSERT = b"struct OpaqueRefElement4 { void *referent; };\n"
# what the text rule accepted, each with the class compiled at 8 bytes: only the compiler's record decides now
TEXT_ONLY = [
    b"#if 0\ntypedef char S[sizeof(OpaqueRefElement4)==4?1:-1];\n#endif\n",
    b"#define UNUSED typedef char S[sizeof(OpaqueRefElement4)==4?1:-1];\n",
    b'const char *s = "typedef char S[sizeof(OpaqueRefElement4)==4?1:-1];";\n',
    b"namespace N { struct OpaqueRefElement4 { int a; }; typedef char S[sizeof(OpaqueRefElement4)==4?1:-1]; }\n",
    b"#define sizeof(x) 4\ntypedef char S[sizeof(OpaqueRefElement4)==4?1:-1];\n",
]


def test_without_a_header_assertion_a_family_row_needs_a_unit():
    ctx = Ctx({"key": "struct"}, header=NO_HEADER_ASSERT)
    assert rename.stand_in_element_problem(ctx, rows(), A) is None
    got = rename.stand_in_element_problem(ctx, [r for r in rows() if r["name"] not in {o for o, _f in A.rows.values()}], A)
    assert got and "no family row has a unit" in got


def test_a_header_asserting_another_size_refuses():
    ctx = Ctx({"key": "struct"}, header=b"typedef char X[sizeof(OpaqueRefElement4)==8?1:-1];\n")
    got = rename.stand_in_element_problem(ctx, rows(), A)
    assert got and "asserts sizeof(OpaqueRefElement4) as [8]" in got


# a header whose text matches the stride while the class it defines is 8 bytes
HEADER_TEXT_ONLY = [
    b"struct OpaqueRefElement4 { int a, b; };\n// typedef char S[sizeof(OpaqueRefElement4)==4?1:-1];\n",
    b"struct OpaqueRefElement4 { int a, b; };\n#if 0\ntypedef char S[sizeof(OpaqueRefElement4)==4?1:-1];\n#endif\n",
]


@pytest.mark.parametrize("header", [NO_HEADER_ASSERT, b"typedef char X[sizeof(OpaqueRefElement4)==4?1:-1];\n",
                                    *HEADER_TEXT_ONLY])
def test_the_spec_names_every_owning_unit_whatever_the_header_says(header):
    source_of = {at: f"Code/Lib/U{at:X}.cpp" for at in A.rows}
    ctx = Ctx({"key": "struct"}, header=header)
    assert rename.stand_in_element_problem(ctx, rows(), A) is None
    spec = rename.element_size_spec(ctx, A, source_of)
    assert spec == dict(cls="OpaqueRefElement4", header=HEADER, stride=4, units=sorted(source_of.values()))




class Tree:
    """A root holding the header and the unit, as element_size_problems reads them after ./build.sh."""

    def __init__(self, root, unit=b"int x;\n", header=NO_HEADER_ASSERT):
        self.root = Path(root).resolve()
        for rel, data in ((HEADER, header), (UNIT, unit)):
            (self.root / rel).parent.mkdir(parents=True, exist_ok=True)
            (self.root / rel).write_bytes(data)

    def read(self, rel):
        path = self.root / rel
        return path.read_bytes() if path.exists() else None


def pp(root, *defs):
    """cl -E output: a #line marker per file, then each (file, text)."""
    return "".join(f'#line 1 "{root / f}"\n{t}\n' for f, t in defs)


def compiled(monkeypatch, root, layouts, text=None, includes=(HEADER,)):
    text = pp(root, (HEADER, "struct OpaqueRefElement4 { void *referent; };"), (UNIT, "int x;")) \
        if text is None else text

    def fake(ctx, rel, found=None):
        if isinstance(text, Exception):
            return None, text.args[0]
        if found is not None:
            found.extend(str(root / i) for i in includes)
        return text, None

    def views(ctx, rel, fresh=False):
        if not fresh:
            raise AssertionError("the size proof reads class_layouts' cache")
        if isinstance(layouts, Exception):
            raise layouts
        return layouts
    monkeypatch.setattr(rename, "preprocess_unit", fake)
    monkeypatch.setattr(rename, "view_layouts", views)


SPEC = dict(cls="OpaqueRefElement4", header=HEADER, stride=4, units=[UNIT])
FOUR = {"OpaqueRefElement4": {"fwd": False, "size": 4}}


def test_a_unit_compiling_the_header_class_at_the_stride_passes(tmp_path, monkeypatch):
    tree = Tree(tmp_path)
    compiled(monkeypatch, tree.root, FOUR)
    assert rename.element_size_problems(tree, SPEC) == []


@pytest.mark.parametrize("unit", TEXT_ONLY)
def test_an_assertion_in_the_text_does_not_count_against_the_compiled_size(tmp_path, monkeypatch, unit):
    tree = Tree(tmp_path, unit=unit)
    compiled(monkeypatch, tree.root, {"OpaqueRefElement4": {"fwd": False, "size": 8},
                                      "N::OpaqueRefElement4": {"fwd": False, "size": 4}})
    got = rename.element_size_problems(tree, SPEC)
    assert got and "compiles sizeof(OpaqueRefElement4) as 8" in got[0]


@pytest.mark.parametrize("label, layouts, says", [
    ("only another namespace's class", {"N::OpaqueRefElement4": {"fwd": False, "size": 4}}, "compiles no definition"),
    ("a forward declaration", {"OpaqueRefElement4": {"fwd": True, "size": 0}}, "compiles no definition"),
    ("no layouts", RuntimeError("X.cpp: compile failed: C2061"), "cannot be read"),
])
def test_no_compiled_definition_refuses(tmp_path, monkeypatch, label, layouts, says):
    tree = Tree(tmp_path)
    compiled(monkeypatch, tree.root, layouts)
    got = rename.element_size_problems(tree, SPEC)
    assert got and says in got[0]


def test_the_class_must_come_from_the_registered_header(tmp_path, monkeypatch):
    tree = Tree(tmp_path)
    compiled(monkeypatch, tree.root, FOUR, includes=())
    assert "never includes" in rename.element_size_problems(tree, SPEC)[0]
    own = pp(tree.root, (HEADER, ""), (UNIT, "struct OpaqueRefElement4 { void *referent; };"))
    compiled(monkeypatch, tree.root, FOUR, text=own)
    got = rename.element_size_problems(tree, SPEC)[0]
    assert "defines OpaqueRefElement4 in code/lib/x.cpp, not only through" in got


def test_a_line_directive_refuses(tmp_path, monkeypatch):
    tree = Tree(tmp_path, unit=b'#line 1 "Code/Lib/OpaqueRefElement4.h"\nstruct OpaqueRefElement4 { int a, b; };\n')
    compiled(monkeypatch, tree.root, FOUR)
    assert "X.cpp carries a #line directive" in rename.element_size_problems(tree, SPEC)[0]
    tree = Tree(tmp_path, header=b'#line 1 "elsewhere.h"\n' + NO_HEADER_ASSERT)
    compiled(monkeypatch, tree.root, FOUR)
    assert "includes Code/Lib/OpaqueRefElement4.h, which carries a #line" in rename.element_size_problems(tree, SPEC)[0]


def test_an_unpreprocessed_unit_refuses(tmp_path, monkeypatch):
    tree = Tree(tmp_path)
    compiled(monkeypatch, tree.root, FOUR, text=RuntimeError("the preprocessor refused it: C1083"))
    assert "cannot be preprocessed" in rename.element_size_problems(tree, SPEC)[0]


@pytest.mark.parametrize("header", HEADER_TEXT_ONLY)
def test_a_header_text_assertion_does_not_count_against_the_compiled_size(tmp_path, monkeypatch, header):
    tree = Tree(tmp_path, header=header)
    compiled(monkeypatch, tree.root, {"OpaqueRefElement4": {"fwd": False, "size": 8}})
    got = rename.element_size_problems(tree, SPEC)
    assert got and "compiles sizeof(OpaqueRefElement4) as 8" in got[0]


def test_the_size_is_compiled_afresh_not_read_from_the_cache(tmp_path, monkeypatch):
    """A header changed to 8 bytes after a cached compile said 4: only a fresh compile may answer."""
    tree = Tree(tmp_path, header=b"struct OpaqueRefElement4 { int a, b; };\n")
    compiled(monkeypatch, tree.root, FOUR)
    monkeypatch.setattr(rename, "view_layouts", lambda ctx, rel, fresh=False:
                        {"OpaqueRefElement4": {"fwd": False, "size": 8 if fresh else 4}})
    got = rename.element_size_problems(tree, SPEC)
    assert got and "compiles sizeof(OpaqueRefElement4) as 8" in got[0]


def test_view_layouts_skips_the_cache_only_when_asked(monkeypatch):
    import class_layouts
    seen = []
    monkeypatch.setattr(class_layouts, "compile_layouts", lambda unit, use_cache=True: seen.append(use_cache) or {})
    ctx = type("C", (), {"root": rename.ROOT})()
    rename.view_layouts(ctx, "Code/Lib/X.cpp")
    rename.view_layouts(ctx, "Code/Lib/X.cpp", fresh=True)
    assert seen == [True, False]
