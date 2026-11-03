"""Declaration-only specializations must not masquerade as recovered bodies."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from find_declared_unmatched import find_defined_functions


@pytest.mark.parametrize("newline", ["\n", "\r\n", "\r\r\n"])
def test_multiline_tree_specializations_are_declarations(newline):
    source = """template <> _STL::_Rb_tree_node<ByteDwordValue> *
ByteDwordTree::_M_copy(_STL::_Rb_tree_node<ByteDwordValue> *x,
    _STL::_Rb_tree_node<ByteDwordValue> *p);
template <> _STL::_Rb_tree_node<ByteWordValue> *
ByteWordTree::_M_copy(_STL::_Rb_tree_node<ByteWordValue> *x,
    _STL::_Rb_tree_node<ByteWordValue> *p);
void Worker::run()
{
    perform();
}
"""
    assert find_defined_functions(source.replace("\n", newline)) == {
        ("Worker", "run", None)
    }


def test_real_multiline_definition_and_constructor_are_still_found():
    source = """Node *Tree::copy(Node *x,
    Node *parent) throw()
{
    return clone(x, parent);
}
Tree::Tree(int value,
    const char *name)
    : Base(value), member(name)
{
}
"""
    assert find_defined_functions(source) == {
        ("Tree", "copy", None), ("Tree", "Tree", None)
    }


def test_comments_literals_and_nested_defaults_do_not_hide_a_definition():
    source = '''void Worker::run(const char *name = "); {", // );
    int n = make_value(1, 2)) /* ; */
{
    perform(n);
}
'''
    assert find_defined_functions(source) == {("Worker", "run", None)}


def test_suffix_and_comment_punctuation_do_not_turn_a_prototype_into_a_body():
    source = '''Node *Tree::copy(Node *x, // { }
    Node *parent) throw(/* { */);
'''
    assert find_defined_functions(source) == set()


def test_declaration_annotation_cannot_excuse_a_later_definition():
    source = """// ?declared@Worker@@QAEXXZ present-unmatched
void Worker::declared(int x,
    int y);
void Worker::unclaimed()
{
}
"""
    assert find_defined_functions(source) == {("Worker", "unclaimed", None)}


def test_incomplete_signature_is_not_silently_excused():
    assert find_defined_functions("void Worker::unclaimed(\n") == {
        ("Worker", "unclaimed", None)
    }


@pytest.mark.parametrize("suffix", ["", " absent-from-retail", " present-unmatched"])
def test_vtable_comment_does_not_annotate_a_function(suffix):
    # tu_skeleton lifts this trailing data comment off the extern declaration.
    source = """// ?old@Worker@@QAEXXZ absent-from-retail
// ??_7WeaponSetUpgradeModuleData@@6B@%s
ModelConditionUpgradeModuleData::ModelConditionUpgradeModuleData()
    : Base()
{
}
""" % suffix
    assert find_defined_functions(source) == {
        ("ModelConditionUpgradeModuleData", "ModelConditionUpgradeModuleData", None)
    }


@pytest.mark.parametrize("matched_ctor", [False, True])
def test_vtable_comment_still_requires_a_matched_constructor(
        tmp_path, monkeypatch, capsys, matched_ctor):
    import find_declared_unmatched as tool
    source = "Code/Upgrade.cpp"
    (tmp_path / "Code").mkdir()
    (tmp_path / source).write_text("""// ??_7WeaponSetUpgradeModuleData@@6B@
ModelConditionUpgradeModuleData::ModelConditionUpgradeModuleData() {}
""")
    ctor = "??0ModelConditionUpgradeModuleData@@QAE@XZ"
    vtable = "??_7WeaponSetUpgradeModuleData@@6B@"
    names = {"?anchor@Worker@@QAEXXZ"}
    if matched_ctor:
        names.add(ctor)
    # A declared data symbol must not substitute for a matched function row.
    monkeypatch.setattr(tool, "read_function_names", lambda *_: (
        names | {vtable}, names, {source: len(names)},
        {name: {source} for name in names}))
    monkeypatch.setattr(tool, "read_data_row_sources", lambda *_: [])
    monkeypatch.setattr(tool, "load_claims_whitelist", lambda: set())
    monkeypatch.setattr(tool, "ROOT", tmp_path)
    monkeypatch.setattr(sys, "argv", ["find_declared_unmatched.py", "--fail", source])
    if matched_ctor:
        tool.main()
        assert "All defined functions are already matched." in capsys.readouterr().out
    else:
        with pytest.raises(SystemExit) as exc:
            tool.main()
        assert exc.value.code == 1
        assert "ModelConditionUpgradeModuleData::ModelConditionUpgradeModuleData" in capsys.readouterr().out


def test_single_line_bodies_are_retained_but_prototypes_and_calls_are_not():
    source = """void Worker::declared();
void Worker::run() { perform(); }
    BASECLASS::Read(buffer, size);
"""
    assert find_defined_functions(source) == {("Worker", "run", None)}


@pytest.mark.parametrize("newline", ["\n", "\r\n", "\r\r\n"])
def test_qualified_call_in_wrapped_condition_is_not_a_definition(newline):
    source = """void Worker::run()
{
    if (ready ||
        _STL::find(begin, end, true) == end) {
        perform();
    }
}
"""
    assert find_defined_functions(source.replace("\n", newline)) == {
        ("Worker", "run", None)
    }


def test_nested_wrapped_call_and_suffix_parentheses_are_distinguished():
    source = '''namespace Work {
    void Worker::run(int n = make_value(1, 2)) throw(/* ) */)
    {
        if (ready && (
            Helper::check(make_value(1, 2), ")") /* ) */)) {
            perform();
        }
    }
}
'''
    assert find_defined_functions(source) == {("Work::Worker", "run", None)}


def test_constructor_initializers_and_indented_definitions_remain_visible():
    source = """namespace Work {
    Worker::Worker(int n)
        : Base(make_value(n)), value(n)
    {
    }
    void Worker::unclaimed(int n)
    {
    }
}
"""
    assert find_defined_functions(source) == {
        ("Work::Worker", "Worker", None), ("Work::Worker", "unclaimed", None)
    }


def test_a_data_only_source_is_claimed_by_its_data_rows(tmp_path, monkeypatch, capsys):
    """A TU that defines only data owns data_rows.csv rows (tools/data_rows.py), not
    function rows; Open-BFME-1's claims gate counts them, and the port did not."""
    import find_declared_unmatched as tool
    import data_rows
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n")
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code/Language.cpp").write_text("int OurLanguage = 0;\n")
    monkeypatch.setattr(tool, "ROOT", tmp_path)
    monkeypatch.setattr(tool, "FUNCTIONS_CSV", tmp_path / "reverse/functions.csv")
    monkeypatch.setattr(tool, "CLAIMS_WHITELIST", tmp_path / "absent.txt")
    monkeypatch.setattr(tool, "DATA_ROWS_CSV", tmp_path / "reverse/data_rows.csv", raising=False)
    monkeypatch.setattr(sys, "argv", ["find_declared_unmatched.py", "--fail", "Code/Language.cpp"])

    def report():
        try:
            tool.main()
            code = 0
        except SystemExit as exc:
            code = exc.code
        return code, capsys.readouterr().out

    code, out = report()  # no data row yet: a source that owns nothing
    assert code == 1 and "Code/Language.cpp: ZERO matched" in out.replace("\\", "/")
    (tmp_path / "reverse/data_rows.csv").write_text(
        data_rows.HEADER + "\n?OurLanguage@@3HA,0x00403000,va,4,.data,Code/Language.cpp,matched,ZH,m\n")
    code, out = report()
    assert code == 0 and "ZERO matched" not in out


INLINE_ADAPTER = """namespace _STL {
    template <> __declspec(dllimport) __forceinline
    unsigned int TableAlias::_M_bkt_num_key(const Key &key) const
    {
        return reinterpret_cast<Native *>(this)->bucketIndex(&key);
    }
}
"""


def test_inline_specializations_remain_in_the_source_inventory():
    candidates = set()
    definitions = find_defined_functions(INLINE_ADAPTER, inline_candidates=candidates)
    assert definitions == candidates == {("_STL::TableAlias", "_M_bkt_num_key", None)}


@pytest.mark.parametrize("prefix", [
    "", "inline ", "__forceinline ",
    "/* template <> __declspec(dllimport) __forceinline */\n",
    '// template <> __declspec(dllimport) __forceinline\n',
    'const char *s = "template <> __declspec(dllimport) __forceinline";\n',
])
def test_inline_syntax_and_comments_do_not_excuse_unclaimed_bodies(prefix):
    candidates = set()
    definitions = find_defined_functions(prefix + "void Worker::run() {}\n",
                                         inline_candidates=candidates)
    assert definitions == {("Worker", "run", None)}
    assert candidates == set()


@pytest.mark.parametrize("staged", [False, True])
@pytest.mark.parametrize("obstacle", [
    None, "body", "import", "other-class", "stale", "changed-copy", "missing-object",
])
def test_inline_adapter_requires_current_absent_object_symbol(
        tmp_path, monkeypatch, capsys, staged, obstacle):
    import build
    import find_declared_unmatched as tool
    from test_gate_exploits import coff, TEXT
    source = "Code/Walkers.cpp"
    (tmp_path / "Code").mkdir()
    path = tmp_path / source
    path.write_text(INLINE_ADAPTER + ("// changed\n" if obstacle == "changed-copy" else ""))
    monkeypatch.setattr(tool, "ROOT", tmp_path)
    monkeypatch.setattr(tool, "read_function_names", lambda *_: (
        {"?walk@@YAXXZ"}, {"?walk@@YAXXZ"}, {source: 1}, {"?walk@@YAXXZ": {source}}))
    monkeypatch.setattr(tool, "read_data_row_sources", lambda *_: [])
    monkeypatch.setattr(tool, "load_claims_whitelist", lambda: set())
    monkeypatch.setattr(tool, "git_show", lambda *_: INLINE_ADAPTER)
    obj = tmp_path / "walkers.obj"
    symbols = []
    if obstacle in ("body", "other-class"):
        cls = "?$hashtable@VKey@@" if obstacle == "body" else "Unrelated"
        symbols = [(f"?_M_bkt_num_key@{cls}@@QAEIXZ", 0, 1, 0x20, 2, 0)]
    elif obstacle == "import":
        symbols = [("__imp_?_M_bkt_num_key@?$hashtable@VKey@@@@QAEIXZ", 0, 0, 0x20, 2, 0)]
    if obstacle != "missing-object":
        obj.write_bytes(coff([(".text", TEXT, b"\xc3", [])], symbols))
    monkeypatch.setattr(build, "obj_path", lambda *_: obj)
    current_calls = []

    def current(src, out, *, strict=False):
        current_calls.append((src, out, strict))
        return obstacle != "stale"

    monkeypatch.setattr(build, "compile_is_current", current)
    monkeypatch.setattr(sys, "argv", ["find_declared_unmatched.py", "--fail", source]
                        + (["--staged"] if staged else []))
    # A changed working copy can only prove itself in unstaged mode.
    rejected = obstacle not in (None, "changed-copy") or (staged and obstacle == "changed-copy")
    if rejected:
        with pytest.raises(SystemExit) as exc:
            tool.main()
        assert exc.value.code == 1
        assert "TableAlias::_M_bkt_num_key" in capsys.readouterr().out
    else:
        tool.main()
        assert "All defined functions are already matched." in capsys.readouterr().out
    assert all(strict for _, _, strict in current_calls)
