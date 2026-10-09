"""doc_lint and the guide's comment-stripping filter.

The guide (docs/doxygen/) must never publish a source comment: the tree's
Doxygen-style notes are reverse-engineering scratch (addresses, offsets,
vtable slots), and HIDE_UNDOC_* does not hide them because such a comment
makes the member documented. docs/doxygen/strip_comments.py removes every
comment from listed sources before Doxygen parses them; the Doxygen test
below proves no note reaches the HTML. doc_lint keeps the guide's own text
free of strings repository tools parse, of copied addresses and of
placeholder or unconfirmed names, and keeps the page ids consistent.
"""
import importlib.util
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

sys.dont_write_bytecode = True
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import doc_lint  # noqa: E402

REPO = Path(__file__).resolve().parents[2]
_spec = importlib.util.spec_from_file_location(
    "strip_comments", REPO / "docs" / "doxygen" / "strip_comments.py")
strip_comments = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(strip_comments)

HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
ROWS = [
    "?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z,,0x0027EEAD,348,Code/Map/Bridge.cpp,matched,",
    "??0Bridge@@QAE@XZ,,0x0027F000,64,Code/Map/Bridge.cpp,matched,",
    "_REF_decode@12,,0x0068DAA0,444,Code/Compression/refdecode.cpp,matched,",
    "?leadOnly@Thing@@QAEXXZ,,0x00100000,8,Code/Thing.cpp,matched,wb-name-unverified per WorldBuilder",
    "?d_00abcd00@@YAXXZ,,0x00ABCD00,32,Code/gen_asm/d_00abcd00.asm,matched,gen-dump",
]
MAINPAGE = "# Guide {#page_mainpage}\n\nSee \\ref sub_audio.\n"


def make_repo(root, files=None, rows=ROWS):
    """A minimal repository: the real Doxyfile and filter plus the given docs."""
    docs = root / "docs" / "doxygen"
    (docs / "pages" / "subsystems").mkdir(parents=True)
    (docs / "api").mkdir()
    shutil.copy(REPO / "docs" / "doxygen" / "Doxyfile", docs / "Doxyfile")
    shutil.copy(REPO / "docs" / "doxygen" / "strip_comments.py", docs / "strip_comments.py")
    (root / "reverse").mkdir()
    (root / "reverse" / "functions.csv").write_text("\n".join([HEADER] + rows) + "\n")
    widget = root / "Code" / "Lib" / "Widget.cpp"
    widget.parent.mkdir(parents=True, exist_ok=True)
    widget.write_text("class Widget\n{\npublic:\n\tvoid spin(int turns);\n};\n")
    base = {
        "docs/doxygen/sources.cfg": "# sources\n",
        "docs/doxygen/pages/mainpage.md": MAINPAGE,
        "docs/doxygen/pages/subsystems/audio.md": "# Audio {#sub_audio}\n\nSee \\ref grp_audio.\n",
        "docs/doxygen/api/audio.dox": "/// \\defgroup grp_audio Audio\n/// \\brief Sound.\n",
    }
    base.update(files or {})
    for rel, text in base.items():
        (root / rel).parent.mkdir(parents=True, exist_ok=True)
        (root / rel).write_text(text)
    return root


def run(root, **kw):
    kw.setdefault("names", True)
    return doc_lint.lint(root, doc_lint.WorkTree(root), **kw)


def codes(found, level="error"):
    return sorted({f.code for f in found if f.level == level})


# --------------------------------------------------------------------------- the filter

def test_strip_comments_blanks_every_comment_and_keeps_lines():
    src = ("int a; ///< retail note 0xBD\n"
           "/** Zero Hour brief\n spanning lines */ int b;\n"
           "const char *s = \"// not a comment /* either */\";\n"
           "char q = '\"'; // after a quote literal\n"
           "// spliced \\\n still the comment\n"
           "#error don't stop here // trailing note\n"
           "int c; /* unterminated\n")
    out = strip_comments.strip_comments(src)
    assert out.count("\n") == src.count("\n")
    for gone in ("retail note", "Zero Hour brief", "spanning", "after a quote",
                 "still the comment", "trailing note", "unterminated"):
        assert gone not in out
    for kept in ("int a;", "int b;", "\"// not a comment /* either */\"", "'\"'",
                 "#error don't stop here", "int c;"):
        assert kept in out


def test_filter_passes_guide_files_through(tmp_path, capsys):
    guide = REPO / "docs" / "doxygen" / "pages" / "mainpage.md"
    assert strip_comments.is_guide_file(guide)
    code = tmp_path / "x.dox"
    code.write_text("/// \\brief kept only inside docs/doxygen\n")
    assert not strip_comments.is_guide_file(code)
    strip_comments.main([str(code)])
    assert "kept" not in capsys.readouterr().out


@pytest.mark.skipif(not shutil.which("doxygen"), reason="doxygen not installed")
def test_doxygen_publishes_dox_docs_and_no_source_comment(tmp_path):
    root = make_repo(tmp_path, {
        "docs/doxygen/sources.cfg": "INPUT += Code/Lib/Widget.cpp\n",
        "docs/doxygen/api/audio.dox": (
            "/// \\defgroup grp_audio Audio\n/// \\brief Sound.\n\n"
            "/// \\class Widget\n/// \\ingroup grp_audio\n/// \\brief GUIDETEXT class.\n\n"
            "/// \\fn void Widget::spin(int turns)\n/// \\brief GUIDETEXT member.\n"
            "/// \\param turns How many.\n"),
    })
    (root / "Code" / "Lib" / "Widget.cpp").write_text(
        "/** ZHBRIEF from a donor banner */\n"
        "class Widget\n{\npublic:\n"
        "\tvoid spin(int turns);\t///< SECRETNOTE slot 65\n"
        "\tint m_flag;\t\t///< SECRETFIELD 0xBD\n"
        "\t/// @todo SECRETTODO\n\tvoid other();\n};\n")
    (root / "build" / "doxygen").mkdir(parents=True)
    subprocess.run(["doxygen", "docs/doxygen/Doxyfile"], cwd=root, check=True,
                   capture_output=True)
    html = "\n".join(p.read_text(errors="replace")
                     for p in (root / "build" / "doxygen" / "html").rglob("*")
                     if p.is_file() and p.suffix in (".html", ".js"))
    assert "GUIDETEXT class" in html and "GUIDETEXT member" in html
    for secret in ("ZHBRIEF", "SECRETNOTE", "SECRETFIELD", "SECRETTODO", "m_flag"):
        assert secret not in html
    log = (root / "build" / "doxygen" / "warnings.log").read_text()
    assert [f for f in doc_lint.doxygen_findings(root, log) if f.level == "error"] == []


# --------------------------------------------------------------------------- text checks

@pytest.mark.parametrize("text", [
    "// stlport", "//STLport", "// cl: /O2", "__emit", "__declspec( naked )",
    "present-unmatched", "absent-from-retail", "class-gate: allow",
    "/alternatename:_x=_y", "#pragma optimize(\"\", off)",
])
def test_tool_strings_are_refused(tmp_path, text):
    root = make_repo(tmp_path, {"docs/doxygen/pages/mainpage.md": MAINPAGE + "\nProse " + text + "\n"})
    assert "tool-string" in codes(run(root, names=False))


@pytest.mark.parametrize("line", [
    "// ?foo@@YAXXZ", "/// // ?foo", "// byte-exact reconstruction: x",
    "// readable body of x", "// upstream layout: x",
])
def test_tool_prefixes_are_refused_at_line_start(tmp_path, line):
    root = make_repo(tmp_path, {"docs/doxygen/api/audio.dox":
                                "/// \\defgroup grp_audio Audio\n" + line + "\n"})
    assert "tool-string" in codes(run(root, names=False))


def test_addresses_are_errors_and_offsets_sizes_warnings(tmp_path):
    root = make_repo(tmp_path, {"docs/doxygen/pages/mainpage.md": MAINPAGE +
                                "Lives at 0x0068DAA0.\nSignature 0x10FB is fine.\n"
                                "Bounds at +0xB4.\nIt is 444 B long.\n"})
    found = run(root, names=False)
    assert codes(found) == ["address"]
    assert [f.line for f in found if f.code == "address"] == [4]
    assert {"offset", "size"} <= set(codes(found, "warning"))


def test_placeholder_tokens_in_prose_warn(tmp_path):
    root = make_repo(tmp_path, {"docs/doxygen/pages/mainpage.md": MAINPAGE + "See Rva0042CBB6Thing.\n"})
    assert "placeholder" in codes(run(root, names=False), "warning")


def test_braces_in_dox_prose_warn_but_balanced_code_does_not(tmp_path):
    good = ("/// \\defgroup grp_audio Audio\n/// \\code\n/// if (x) { y(); }\n/// \\endcode\n")
    root = make_repo(tmp_path, {"docs/doxygen/api/audio.dox": good})
    assert "brace" not in codes(run(root, names=False), "warning")
    bad = "/// \\defgroup grp_audio Audio\n/// Returns {a, b}.\n/// \\code\n/// if (x) {\n/// \\endcode\n"
    root = make_repo(tmp_path / "b", {"docs/doxygen/api/audio.dox": bad})
    lines = [f.line for f in run(root, names=False) if f.code == "brace"]
    assert lines == [2, 3]


def test_source_extension_under_docs_is_an_error(tmp_path):
    root = make_repo(tmp_path, {"docs/doxygen/api/notes.h": "// x\n"})
    assert "placement" in codes(run(root, names=False))


# --------------------------------------------------------------------------- ids and refs

def test_clean_fixture_has_no_findings(tmp_path):
    assert [str(f) for f in run(make_repo(tmp_path))] == []


def test_page_anchor_must_follow_file_name(tmp_path):
    root = make_repo(tmp_path, {"docs/doxygen/pages/architecture.md": "# Architecture {#page_arch}\n"})
    msgs = [f.message for f in run(root, names=False) if f.code == "page-id" and f.level == "error"]
    assert msgs == ["first heading must carry {#page_architecture}"]


def test_subsystem_page_anchor_and_group_pairing(tmp_path):
    root = make_repo(tmp_path, {"docs/doxygen/pages/subsystems/network.md": "# Network {#page_network}\n"})
    found = run(root, names=False)
    assert any(f.message == "first heading must carry {#sub_network}" for f in found)
    assert any("no api/network.dox group" in f.message for f in found)


def test_api_file_must_define_its_group(tmp_path):
    root = make_repo(tmp_path, {"docs/doxygen/api/memory.dox": "/// \\defgroup grp_mem Memory\n"})
    found = run(root, names=False)
    assert any(f.message == "api/memory.dox must define \\defgroup grp_memory" for f in found)


def test_unknown_ref_and_ingroup_targets(tmp_path):
    root = make_repo(tmp_path, {
        "docs/doxygen/pages/mainpage.md": MAINPAGE + "And \\ref page_missing, \\subpage sub_audio.\n",
        "docs/doxygen/api/audio.dox": "/// \\defgroup grp_audio Audio\n/// \\class Bridge\n/// \\ingroup grp_nope\n",
    })
    msgs = sorted(f.message for f in run(root, names=False) if f.code == "ref")
    assert msgs == ["\\ingroup target 'grp_nope' is not a defined group",
                    "\\ref target 'page_missing' is not defined"]


def test_duplicate_ids(tmp_path):
    root = make_repo(tmp_path, {"docs/doxygen/pages/glossary.md": "# Glossary {#page_glossary}\n\n## A {#sub_audio}\n"})
    assert any("already defined" in f.message for f in run(root, names=False))


def test_file_block_needs_a_listed_source(tmp_path):
    root = make_repo(tmp_path, {"docs/doxygen/api/audio.dox": "/// \\defgroup grp_audio Audio\n/// \\file Widget.cpp\n"})
    assert "ref" in codes(run(root, names=False))
    (root / "docs/doxygen/sources.cfg").write_text("INPUT += Code/Lib/Widget.cpp\n")
    assert "ref" not in codes(run(root, names=False))


def test_sources_cfg_entries(tmp_path):
    (tmp_path / "Code" / "gen_asm").mkdir(parents=True)
    (tmp_path / "Code" / "gen_asm" / "d.asm").write_text("x\n")
    (tmp_path / "Code" / "Lib").mkdir(parents=True)
    (tmp_path / "Code" / "Lib" / "Rva0042CBB6.cpp").write_text("x\n")
    root = make_repo(tmp_path, {"docs/doxygen/sources.cfg": (
        "INPUT += Code/Lib/Widget.cpp\nINPUT += Code/Lib/Widget.cpp\nINPUT += Code/Lib\n"
        "INPUT += Code/Lib/Missing.cpp\nINPUT += Code/gen_asm/d.asm\n"
        "INPUT += Code/Lib/Rva0042CBB6.cpp\nFILE_PATTERNS = *.cpp\n")})
    errors = [f.message for f in run(root, names=False) if f.code == "sources" and f.level == "error"]
    assert sorted(errors) == sorted([
        "Code/Lib is a directory; list files only",
        "Code/Lib/Missing.cpp does not exist",
        "Code/gen_asm/d.asm is generated placeholder code",
        "Code/Lib/Rva0042CBB6.cpp is placeholder-named; it is not documented",
        "only 'INPUT += <path>' lines belong here"])
    assert any("already listed" in f.message for f in run(root, names=False))


# --------------------------------------------------------------------------- names

def test_cited_names_resolve_through_ledger_and_tree(tmp_path):
    dox = ("/// \\defgroup grp_audio Audio\n"
           "/// \\class Bridge\n"
           "/// \\fn bool Bridge::isPointOnBridge(const Coord3D *point)\n"
           "/// \\fn int GCALL REF_decode(void *dest, const void *src, int *size)\n"
           "/// \\fn void Widget::spin(int turns)\n"
           "/// \\see Bridge::Bridge, REF_decode, Widget\n"
           "/// Prose cites Bridge::isPointOnBridge and std::vector.\n")
    root = make_repo(tmp_path, {"docs/doxygen/api/audio.dox": dox})
    assert [str(f) for f in run(root)] == []


def test_unknown_placeholder_and_unconfirmed_names(tmp_path):
    dox = ("/// \\defgroup grp_audio Audio\n"
           "/// \\class Nowhere\n"
           "/// \\fn void Thing::leadOnly()\n"
           "/// \\fn void d_00abcd00()\n"
           "/// \\see RvaThing::get\n"
           "/// Prose cites Ghost::walk.\n")
    root = make_repo(tmp_path, {"docs/doxygen/api/audio.dox": dox})
    found = sorted((f.line, f.level) for f in run(root) if f.code == "name")
    assert found == [(2, "error"), (3, "error"), (4, "error"), (5, "error"), (6, "warning")]


def test_doxygen_warning_records_are_joined_and_scoped(tmp_path):
    root = make_repo(tmp_path)
    docs = (root / "docs" / "doxygen" / "api" / "audio.dox").resolve()
    log = ("%s:5: warning: no uniquely matching class member found for \n"
           "  void Widget::spin()\nPossible candidates:\n  'x' at line 2\n"
           "%s:9: warning: documented symbol 'X::f' was not declared or defined.\n"
           % (docs, (root / "Code" / "Lib" / "Widget.cpp").resolve()))
    found = doc_lint.doxygen_findings(root, log)
    assert [(f.path, f.line, f.level) for f in found] == [
        ("docs/doxygen/api/audio.dox", 5, "error"), (doc_lint.WARN_LOG, 0, "note")]
    assert "Possible candidates" in found[0].message


def test_staged_scope_refuses_code_paths(tmp_path):
    root = make_repo(tmp_path)
    subprocess.run(["git", "init", "-q"], cwd=root, check=True)
    subprocess.run(["git", "add", "Code/Lib/Widget.cpp", "docs/doxygen"], cwd=root, check=True)
    found = doc_lint.check_staged_scope(root)
    assert [f.path for f in found] == ["Code/Lib/Widget.cpp"]
    assert [str(f) for f in doc_lint.lint(root, doc_lint.Index(root), names=False)] == []


def test_repository_guide_is_clean():
    found = doc_lint.lint(REPO, doc_lint.WorkTree(REPO))
    assert [str(f) for f in found if f.level != "note"] == []
