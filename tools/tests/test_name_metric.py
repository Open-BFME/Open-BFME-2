"""Declared-name counting, with BFME1's placeholder policy."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_metric as names


@pytest.mark.parametrize("kind, name, bad", [
    ("file", "Rva00123456", True), ("type", "BfmeThing", True),
    ("function", "d_00123456", True), ("member", "m_field_0x20", True),
    ("local", "local_20", True), ("param", "param_1", True),
    ("param", "tmp", True), ("local", "t2", True), ("local", "x", True),
    ("local", "i", False), ("local", "j", False), ("local", "k", False),
    ("member", "m_health", False), ("param", "targetPosition", False),
    ("function", "getHealth", False), ("file", "Generals", False),
])
def test_placeholder_policy(kind, name, bad):
    assert bool(names.weak(kind, name)) is bad


def test_all_declaration_kinds_and_no_comments_strings_or_padding():
    source = '''
// class Rva00123456 { int fake; };
const char *label = "int local_20;";
struct Unit {
    int m_health;
    char m_pad[4];
    void update(Unit *targetPosition) {
        int tmp = 0;
        int health = m_health;
    }
};
enum Side { Good, Evil };
extern int thePlayer;
'''
    assert names.declared("Code/Unit.cpp", source) == [
        ("file", "Unit"), ("type", "Unit"), ("member", "m_health"),
        ("type", "Side"), ("function", "update"), ("param", "targetPosition"),
        ("local", "tmp"), ("local", "health"),
        ("global", "label"), ("global", "thePlayer"),
    ]


def test_an_elaborated_type_specifier_still_declares_the_member():
    """`class Object *obj;` is a member, not a nested type.

    members() skipped every statement opening with class/struct/union/enum, so a
    member or global written that way was counted nowhere - and rename.py's
    reference_declarers, which reads this to show a word is a genuine name in the
    reference trees, could not see it either.
    """
    source = '''
struct Node {
    Node *plain;
    class Object *elaborated;
    struct Thing *tagged;
    enum Kind kind;
};
class Object *theObject;
'''
    assert names.declared("Code/Node.cpp", source) == [
        ("file", "Node"), ("type", "Node"),
        ("member", "plain"), ("member", "elaborated"),
        ("member", "tagged"), ("member", "kind"),
        ("global", "theObject"),
    ]


@pytest.mark.parametrize("body, why", [
    ("class Fwd;", "a forward declaration declares no member"),
    ("class Inner { int hidden; };", "a nested definition is read as its own type"),
])
def test_an_elaborated_keyword_without_a_declarator_declares_no_member(body, why):
    source = "struct Holder {\n    %s\n    int real;\n};\n" % body
    got = [n for kind, n in names.declared("Code/Holder.cpp", source) if kind == "member"]
    assert "Fwd" not in got and "Inner" not in got, why
    assert "real" in got


def test_a_named_union_is_a_type_and_its_fields_are_members():
    """A named union declares a type and data members, like a class or struct.

    DECL matched only class and struct, so `union Tangent { ... } m_inTangent;`
    contributed neither the tag nor the fields. `union` was also missing from
    members()' old skip list, which counted the tag as a data member - the one
    reading that was wrong in both directions at once.
    """
    source = '''
class Curve {
    union Tangent
    {
        float value;
        int bits;
    } m_inTangent, m_outTangent;
};
'''
    got = names.declared("Code/Curve.cpp", source)
    assert ("type", "Tangent") in got
    assert ("member", "value") in got and ("member", "bits") in got
    assert ("member", "m_inTangent") in got and ("member", "m_outTangent") in got


def test_a_base_clause_is_not_read_as_a_member():
    source = "struct Derived : public Base {\n    int real;\n};\n"
    assert [n for kind, n in names.declared("Code/Derived.cpp", source) if kind == "member"] == ["real"]


def track(root, paths):
    subprocess.run(["git", "init", "-q", str(root)], check=True)
    for rel, text in paths.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    subprocess.run(["git", "add", "--", *paths], cwd=root, check=True)


def test_only_tracked_source_counts_and_globals_are_deduplicated(tmp_path, monkeypatch):
    track(tmp_path, {
        "Code/First.cpp": "extern int thePlayer;\n",
        "Code/Second file.h": "extern int thePlayer;\n",
        "Code/gen_asm/Unknown.cpp": "int fake;\n",
        "Code/gen_small/Unknown.cpp": "int fake;\n",
        "Code/readme.txt": "int fake;\n",
        "reference/Donor.cpp": "int fake;\n",
    })
    (tmp_path / "Code/Untracked.cpp").write_text("int fake;\n")
    monkeypatch.setattr(names, "ROOT", tmp_path)
    assert names.readable() == (3, 0)  # two files, one global


def test_missing_tracked_source_aborts(tmp_path, monkeypatch):
    track(tmp_path, {"Code/Unit.cpp": "int health;\n"})
    (tmp_path / "Code/Unit.cpp").unlink()
    monkeypatch.setattr(names, "ROOT", tmp_path)
    with pytest.raises(FileNotFoundError):
        names.readable()


def test_empty_scope_aborts(tmp_path, monkeypatch):
    track(tmp_path, {"README.md": "No code"})
    monkeypatch.setattr(names, "ROOT", tmp_path)
    with pytest.raises(ValueError, match="No declared names"):
        names.readable()


# Real names BFME1's two-hex-character offset rule read as placeholders (the
# 'd3D' of parseCoord3D, the 'd1' of dwReserved1); tools/rename.py lets an
# inferred name replace only a placeholder, so these must stay real.
@pytest.mark.parametrize("name", [
    "parseCoord3D", "parseBitString32", "getInt64", "addInt64", "getCoord3D", "initFilters3D",
    "getCenterPoint2D", "readInt32", "getPosition3D", "m_sampleCount2D", "m_sampleCount3D", "data2",
    "dwReserved1", "lpReserved2", "bfReserved1", "int64", "float32", "vec3d", "crc32", "sha256",
    "readWord128", "texture_2D",
])
def test_dimension_width_and_reserved_names_are_real(name):
    assert not names.placeholder(name)


@pytest.mark.parametrize("name", [
    "m_0C", "m_B0", "m_64", "m_4", "field_1C", "unk14", "off_20", "m_var0", "m_field_0x20", "m_value_84",
    "m_valueC4", "m_value184", "m_unkC8", "m_p10", "m04", "slot20", "m_at0c",
])
def test_offset_names_are_placeholders(name):
    assert names.placeholder(name)


def test_global_names_blanks_a_continued_directive_in_a_crlf_file():
    # the directive scan reads backslash-CR-LF as a continuation, so the continued line is no global declaration
    # (before, it stayed in the code of a CRLF file and `int hidden;` below read as a second global there).
    # The metric reads files with read_text, which makes the newlines LF; rename.py and name_lane.py decode
    # raw bytes and hand this function the CR, which is the text pinned here
    code = "#define DECLARE(x) \\\r\n    int hiddenGlobal;\r\nint realGlobal;\r\n"
    assert list(names.global_names(code)) == ["realGlobal"]
    assert list(names.global_names(code.replace("\r\n", "\n"))) == ["realGlobal"]


@pytest.mark.parametrize("newline", ["\n", "\r\n"])
def test_strip_keeps_the_continuation_of_a_comment_inside_a_define(newline):
    # GameMemory.h's GCMP_FIND opens a `/* \` comment inside the continued macro body; blanking its
    # backslash ended the directive there and left the body's closing brace as a stray `}` in the code
    code = newline.join(["#define POOL(x) \\", "{ \\", "    /* \\", "    note \\", "    */ \\",
                         "    int hiddenGlobal; \\", "}", "int realGlobal;", ""])
    stripped = names.strip(code)
    assert len(stripped) == len(code) and "note" not in stripped
    assert list(names.global_names(stripped)) == ["realGlobal"]
    assert names.PREPROCESSOR.sub("", stripped).count("}") == 0
