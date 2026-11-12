"""class_gate --staged against real throwaway git repositories.

A staged unit is judged against HEAD's copy of its own path or, for a git
rename (R, never a copy), of the path it was moved from; a body a deleted unit
carried verbatim is credited to one staged unit (a TU merge's move). Each case builds a
repository with `GameLogic` and `Widget` registered as shared-header classes
and runs the real gate against its index.
"""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_gate  # noqa: E402
import class_views  # noqa: E402

LOGIC = "class GameLogic {\npublic:\n    int m_frame;\n    int getFrame() const { return m_frame; }\n};\n"
WIDGET = "class Widget {\npublic:\n    int m_size;\n    int getSize() const { return m_size; }\n};\n"
BODY = "int Unit::run() { return 1; }\nint Unit::walk() { return 2; }\nint Unit::stop() { return 3; }\n"
OLD = "Code/Game/Old.cpp"
NEW = "Code/Game/New.cpp"


class Repo:
    def __init__(self, root, monkeypatch):
        self.root = root
        monkeypatch.setattr(class_gate, "ROOT", root)
        monkeypatch.setattr(class_views, "CANONICAL", root / "reverse" / "canonical_classes.csv")
        self.git("init", "-q")
        self.git("config", "user.email", "t@example.com")
        self.git("config", "user.name", "t")
        self.write("reverse/canonical_classes.csv",
                   "class,header\nGameLogic,Code/Game/GameLogic.h\nWidget,Code/Game/Widget.h\n")

    def git(self, *args):
        return subprocess.run(["git", *args], cwd=self.root, capture_output=True, text=True, check=True)

    def write(self, path, text):
        target = self.root / path
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(text, encoding="latin-1")

    def commit(self, *paths):
        self.git("add", "--", *paths)
        self.git("commit", "-q", "-m", "base")

    def stage(self, *paths):
        self.git("add", "-A", "--", *paths)

    def gate(self, capsys):
        capsys.readouterr()
        rc = class_gate.main(["--staged"])
        return rc, capsys.readouterr().err


@pytest.fixture
def repo(tmp_path, monkeypatch):
    r = Repo(tmp_path, monkeypatch)
    r.write(OLD, LOGIC + BODY)
    r.write("Code/Game/Other.cpp", "int other() { return 0; }\n")
    r.commit(".", )
    return r


def test_pure_rename_of_a_unit_with_a_private_class_passes(repo, capsys):
    repo.git("mv", OLD, NEW)
    assert class_gate.staged_renames() == {NEW: OLD}
    assert repo.gate(capsys) == (0, "")


def test_rename_with_a_comment_edit_passes(repo, capsys):
    repo.git("mv", OLD, NEW)
    repo.write(NEW, LOGIC + BODY + "// moved\n")
    repo.stage(NEW)
    assert repo.gate(capsys) == (0, "")


def test_rename_that_adds_a_class_copy_is_refused(repo, capsys):
    repo.git("mv", OLD, NEW)
    repo.write(NEW, LOGIC + WIDGET + BODY)
    repo.stage(NEW)
    rc, err = repo.gate(capsys)
    assert rc == 1 and "`Widget`" in err and "`GameLogic`" not in err


def test_added_class_with_allow_marker_passes(repo, capsys):
    repo.git("mv", OLD, NEW)
    repo.write(NEW, LOGIC + "// class-gate: allow Widget proved codegen view\n" + WIDGET + BODY)
    repo.stage(NEW)
    assert repo.gate(capsys) == (0, "")


def test_copy_of_a_unit_with_a_private_class_is_refused(repo, capsys):
    repo.write(NEW, LOGIC + BODY)
    repo.stage(NEW)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and "`GameLogic`" in err and NEW in err


def test_recreated_old_path_does_not_double_credit(repo, capsys):
    repo.git("mv", OLD, NEW)
    repo.write(OLD, LOGIC + BODY + "// recreated\n")
    repo.stage(OLD, NEW)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and NEW in err and OLD not in err


FRESH = "".join(f"int Fresh::f{i}() {{ return {i * 7919}; }}\n" for i in range(40))


def test_rename_below_the_similarity_threshold_is_refused(repo, capsys):
    repo.git("mv", OLD, NEW)
    repo.write(NEW, LOGIC.replace("m_frame;", "m_frame;\n    int m_new;") + FRESH)
    repo.stage(NEW)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and "`GameLogic`" in err


def test_rename_below_the_threshold_keeping_the_body_verbatim_is_a_move(repo, capsys):
    repo.git("mv", OLD, NEW)
    repo.write(NEW, LOGIC + FRESH)
    repo.stage(NEW)
    assert class_gate.staged_renames() == {}
    assert repo.gate(capsys) == (0, "")


@pytest.mark.parametrize("origin", ["Code/gen_small/x.cpp", "reference/open-bfme-1/x.cpp", "Code/Game/old.h"])
def test_rename_from_an_ungated_path_gets_no_credit(repo, capsys, origin):
    repo.write(origin, LOGIC + BODY)
    repo.commit(origin)
    repo.git("mv", origin, NEW)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and "`GameLogic`" in err


@pytest.mark.parametrize("setting", ["false", "true", "copies"])
def test_rename_credit_ignores_diff_renames_config(repo, capsys, setting):
    repo.git("config", "diff.renames", setting)
    repo.git("mv", OLD, NEW)
    assert repo.gate(capsys) == (0, "")


def test_copy_is_refused_under_diff_renames_copies(repo, capsys):
    repo.git("config", "diff.renames", "copies")
    repo.write(NEW, LOGIC + BODY)
    repo.stage(NEW)
    assert repo.gate(capsys)[0] == 1


@pytest.mark.parametrize("name", ["My Unit.cpp", "Unité.cpp"])
def test_unusual_path_is_checked_not_skipped(repo, capsys, name):
    repo.write(f"Code/Game/{name}", LOGIC + BODY)
    repo.stage(f"Code/Game/{name}")
    rc, err = repo.gate(capsys)
    assert rc == 1 and name in err


def test_unusual_path_pure_rename_passes(repo, capsys):
    repo.write("Code/Game/My Old.cpp", LOGIC + BODY)
    repo.commit("Code/Game/My Old.cpp")
    repo.git("mv", "Code/Game/My Old.cpp", "Code/Game/My New.cpp")
    assert repo.gate(capsys) == (0, "")


def test_unreadable_staged_blob_is_refused(repo, capsys, monkeypatch):
    real = class_gate.git_text
    monkeypatch.setattr(class_gate, "git_text", lambda spec: None if spec == f":{NEW}" else real(spec))
    repo.write(NEW, LOGIC + BODY)
    repo.stage(NEW)
    rc, err = repo.gate(capsys)
    assert rc == 1 and "unreadable" in err


def test_new_unit_with_a_copy_is_refused(repo, capsys):
    repo.write("Code/Game/Fresh.cpp", WIDGET)
    repo.stage("Code/Game/Fresh.cpp")
    assert repo.gate(capsys)[0] == 1


def test_in_place_edit_adding_a_copy_is_refused(repo, capsys):
    repo.write(OLD, LOGIC + WIDGET + BODY)
    repo.stage(OLD)
    rc, err = repo.gate(capsys)
    assert rc == 1 and "`Widget`" in err


def test_in_place_edit_of_a_unit_with_a_copy_passes(repo, capsys):
    repo.write(OLD, LOGIC + BODY + "// edited\n")
    repo.stage(OLD)
    assert repo.gate(capsys) == (0, "")


def test_merge_head_copy_is_credited(repo, capsys):
    base = repo.git("rev-parse", "HEAD").stdout.strip()
    repo.git("checkout", "-q", "-b", "side")
    repo.write("Code/Game/Side.cpp", WIDGET)
    repo.commit("Code/Game/Side.cpp")
    repo.git("checkout", "-q", "-")
    repo.write("Code/Game/Main.cpp", "int m() { return 1; }\n")
    repo.commit("Code/Game/Main.cpp")
    subprocess.run(["git", "merge", "--no-commit", "--no-ff", "side"], cwd=repo.root, capture_output=True)
    assert repo.git("rev-parse", "MERGE_HEAD").stdout.strip() != base
    assert repo.gate(capsys) == (0, "")


def test_file_mode_is_unchanged(repo, capsys):
    capsys.readouterr()
    assert class_gate.main([OLD]) == 0
    repo.write(NEW, LOGIC + BODY)
    assert class_gate.main([NEW]) == 1
    assert "`GameLogic`" in capsys.readouterr().err


SECOND = "Code/Game/Second.cpp"
FILLER = "".join(f"// tu-skeleton: 0x{i:08X} placeholder for a row not merged yet\n" for i in range(60))


@pytest.fixture
def donors(repo):
    repo.write(SECOND, "int second() { return 2; }\n")
    repo.commit(SECOND)
    return repo


def merge_into(repo, text, *deleted):
    for path in deleted:
        repo.git("rm", "-q", "--", path)
    repo.write(NEW, text)
    repo.stage(NEW)


def test_tu_merge_moving_a_deleted_donors_body_passes(donors, capsys):
    merge_into(donors, FILLER + LOGIC + "// another donor\n" + BODY + "int second() { return 2; }\n", OLD, SECOND)
    assert class_gate.staged_renames() == {}
    assert donors.gate(capsys) == (0, "")


def test_tu_merge_with_an_edited_body_is_refused(donors, capsys):
    merge_into(donors, FILLER + LOGIC.replace("m_frame;", "m_frame;\n    int m_extra;") + BODY, OLD, SECOND)
    rc, err = donors.gate(capsys)
    assert rc == 1 and "`GameLogic`" in err


def test_deleted_body_credits_only_one_new_unit(donors, capsys):
    merge_into(donors, FILLER + LOGIC + BODY, OLD)
    donors.write("Code/Game/Third.cpp", FILLER + LOGIC + "int third() { return 3; }\n")
    donors.stage("Code/Game/Third.cpp")
    rc, err = donors.gate(capsys)
    assert rc == 1 and err.count("`GameLogic`") == 1


def test_deleted_body_is_no_credit_for_another_class(donors, capsys):
    merge_into(donors, FILLER + WIDGET + BODY, OLD)
    rc, err = donors.gate(capsys)
    assert rc == 1 and "`Widget`" in err


def test_rename_credited_body_is_not_credited_again(repo, capsys):
    repo.git("mv", OLD, NEW)
    repo.write("Code/Game/Third.cpp", FILLER + LOGIC + "int third() { return 3; }\n")
    repo.stage("Code/Game/Third.cpp")
    assert class_gate.staged_renames() == {NEW: OLD}
    rc, err = repo.gate(capsys)
    assert rc == 1 and "Third.cpp" in err and NEW not in err


# Changed bodies that the survey normalisation used to mistake for pure moves.
LEXICAL_CASES = []
for label, literal in [('string', '"a  b"'), ('wide', 'L"a  b"'), ('raw', 'R"(a  b)"')]:
    old = 'class GameLogic { const void *tag() { return %s; } };\n' % literal
    LEXICAL_CASES.append(('literal-' + label, old, old.replace('  ', ' ')))
for directive in ['#define', '%:define', '\f#define', '\v#define']:
    old = 'class GameLogic {\n%s FIELD int\n FIELD a;\n int b;\n};\n' % directive
    LEXICAL_CASES.append(('directive-' + repr(directive), old, old.replace('int\n FIELD', 'int FIELD')))
for splice in ['\\', '??/']:
    old = 'class GameLogic {\n int a; //comment%s\nint b;\n};\n' % splice
    LEXICAL_CASES.append(('splice-' + splice, old, old.replace('comment' + splice, 'comment')))
old = 'class GameLogic {\n const char *s = R"tag("})tag";\n int a;\n};\n'
LEXICAL_CASES.append(('raw-span', old, old.replace('int a;', 'long a;')))
old = 'class GameLogic {\n??=define FIELD int\n FIELD a;\n int b;\n};\n'
LEXICAL_CASES.append(('trigraph-directive', old, old.replace('int\n FIELD', 'int FIELD')))
old = 'class GameLogic { void f() <% int x; } int a; };\n'
LEXICAL_CASES.append(('brace-digraph', old, old.replace('int a;', 'double a;')))


@pytest.mark.parametrize('label,old,new', LEXICAL_CASES, ids=[c[0] for c in LEXICAL_CASES])
def test_deleted_donor_lexical_change_is_refused(repo, capsys, label, old, new):
    repo.write(OLD, old + BODY)
    repo.commit(OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`GameLogic`' in err


@pytest.mark.parametrize('token', ['<%', '%>', '<:', ':>'])
def test_alternative_braces_or_brackets_disable_move_credit(token):
    # Even a token outside the class can corrupt the extractor's scope stack.
    assert class_gate.moved_bodies(LOGIC + '\n' + token) == {}


@pytest.mark.parametrize('literal', ['"a  b"', 'L"a  b"', "' '"])
def test_moved_literal_keeps_data_but_allows_comment_and_format_edits(repo, capsys, literal):
    old = 'class GameLogic { const void *tag() { return %s; } };\n' % literal
    repo.write(OLD, old + BODY)
    repo.commit(OLD)
    new = old.replace('return ', 'return /*same data*/  ')
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    assert repo.gate(capsys) == (0, '')


@pytest.mark.parametrize('side', ['both', 'donor', 'destination'])
@pytest.mark.parametrize('scopes', ['namespaces', 'same-file'])
def test_duplicate_class_name_gets_no_deleted_donor_credit(repo, capsys, side, scopes):
    # Sol R1: changing only B::X used to disappear behind A::X's body key.
    first = 'class X { int a; };\n'
    second = 'class X { int b; };\n'
    if scopes == 'namespaces':
        first = 'namespace A {\n' + first + '}\n'
        second = 'namespace B {\n' + second + '}\n'
    old = first + (second if side != 'destination' else '')
    new = first + (second.replace('int b;', 'double b;') if side != 'donor' else '')
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`X`' in err


@pytest.mark.parametrize('same', [False, True], ids=['changed-namespace', 'same-namespace'])
def test_deleted_donor_namespace_identity(repo, capsys, same):
    old = 'namespace A {\nclass X { int a; };\n}\n'
    new = old if same else old.replace('namespace A', 'namespace B')
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    if same:
        assert (rc, err) == (0, '')
    else:
        assert rc == 1 and '`X`' in err


X_BODY = 'class X { int a; };\n'


def scoped_x(*scopes):
    text = X_BODY
    for scope in reversed(scopes):
        text = scope + ' {\n' + text + '}\n'
    return text


@pytest.mark.parametrize('old,new,path,passes', [
    (scoped_x('namespace A', 'namespace B'), scoped_x('namespace A', 'namespace C'), ('A', 'B'), False),
    (scoped_x('namespace A', 'namespace B'), scoped_x('namespace A::B'), ('A', 'B'), True),
    (scoped_x('namespace'), X_BODY, ('(anonymous)',), False),
    (scoped_x('namespace'), scoped_x('namespace'), ('(anonymous)',), True),
    (scoped_x('class Outer'), scoped_x('class Other'), ('Outer',), False),
    (scoped_x('namespace A', 'class Outer'), scoped_x('namespace A', 'class Outer'), ('A', 'Outer'), True),
])
def test_deleted_donor_full_scope_path(repo, capsys, old, new, path, passes):
    assert class_gate.moved_bodies(old)['X'][0] == path
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    if passes:
        assert (rc, err) == (0, '')
    else:
        assert rc == 1 and '`X`' in err


@pytest.mark.parametrize('ambiguous', [
    '}\n' + X_BODY,
    '{\n' + X_BODY,
    '#define S A\n' + scoped_x('namespace S'),
    'BEGIN_NAMESPACE(A)\n' + X_BODY + 'END_NAMESPACE\n',
    scoped_x('namespace NS(A)'),
])
@pytest.mark.parametrize('side', ['donor', 'destination'])
def test_ambiguous_scope_gets_no_move_credit(repo, capsys, ambiguous, side):
    assert class_gate.moved_bodies(ambiguous) == {}
    old, new = (ambiguous, X_BODY) if side == 'donor' else (X_BODY, ambiguous)
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`X`' in err


@pytest.mark.parametrize('prefix,suffix', [
    ('#include "X.h"\n', ''),
    ('extern "C" {\n', '}\n'),
])
def test_move_scope_preserves_offsets_and_ignores_linkage(prefix, suffix):
    plain = scoped_x('namespace A')
    assert class_gate.moved_bodies(prefix + plain + suffix) == class_gate.moved_bodies(plain)


def test_inline_namespace_class_heads_keep_namespace_identity():
    old = 'namespace A { class X { int a; }; }'
    new = 'namespace B { class X { int a; }; }'
    assert class_gate.moved_bodies(old)['X'][0] == ('A',)
    assert class_gate.moved_bodies(new)['X'][0] == ('B',)


@pytest.mark.parametrize('side', ['donor', 'destination'])
@pytest.mark.parametrize('prefix,suffix', [
    ('OPEN_NAMESPACE; ', ' CLOSE_NAMESPACE'),
    ('OPEN_NAMESPACE(A); ', ' CLOSE_NAMESPACE(A);'),
    ('OPEN_NAMESPACE; int value; namespace A {\n', '\n}\n'),
    ('namespace A {\nOPEN_NAMESPACE;\nnamespace B {\n', '\n}\n}\n'),
    ('class Outer {\npublic: OPEN_NAMESPACE;\n', '\n};\n'),
])
def test_semicolon_macro_scope_gets_no_move_credit(repo, capsys, side, prefix, suffix):
    ambiguous = prefix + X_BODY + suffix
    # Compare against the same proven lexical scopes without the macro wrapper.
    plain = ambiguous.replace('OPEN_NAMESPACE(A);', '').replace('OPEN_NAMESPACE;', '')
    plain = plain.replace('CLOSE_NAMESPACE(A);', '').replace('CLOSE_NAMESPACE', '')
    old, new = (ambiguous, plain) if side == 'donor' else (plain, ambiguous)
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`X`' in err


@pytest.mark.parametrize('declaration', [
    'int value;', 'Widget value;', 'Widget *value;', 'Widget &value;',
    'A::Widget value;', 'Widget function(int);', 'using Alias = Widget;',
    'typedef Widget Alias;', 'static int value;', 'const Widget value;',
])
def test_recognizable_declarations_before_class_keep_move_credit(declaration):
    plain = scoped_x('namespace A')
    expected = class_gate.moved_bodies(plain)
    assert expected
    assert class_gate.moved_bodies(declaration + '\n' + plain) == expected



def test_semicolon_declaration_before_class_still_credits_move(repo, capsys):
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, 'Widget value;\n' + X_BODY + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + X_BODY + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    assert repo.gate(capsys) == (0, '')


TEMPLATE = 'template <class T> struct Box { T *m_p; };\ntemplate <> struct Box<int> { int m_v; };\n'


@pytest.mark.parametrize('where', ['before', 'after'])
def test_template_elsewhere_keeps_other_move_credit(where):
    # A template body is never credited, but it no longer voids the unit's
    # ordinary spans (a TU merge that composes an STLport specialization).
    text = TEMPLATE + X_BODY if where == 'before' else X_BODY + TEMPLATE
    found = class_gate.moved_bodies(text)
    assert found['X'] == class_gate.moved_bodies(X_BODY)['X']
    assert 'Box' not in found


@pytest.mark.parametrize('side', ['donor', 'destination', 'both'])
def test_tu_merge_beside_a_template_credits_the_moved_body(repo, capsys, side):
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    old = (TEMPLATE if side in ('donor', 'both') else '') + X_BODY
    new = (TEMPLATE if side in ('destination', 'both') else '') + X_BODY
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    assert repo.gate(capsys) == (0, '')


def test_tu_merge_beside_a_template_still_refuses_an_edited_body(repo, capsys):
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, TEMPLATE + X_BODY + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + TEMPLATE + X_BODY.replace('int a;', 'int b;') + FRESH, OLD)
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`X`' in err


# Directives that cannot form a scope no longer void a unit's move credit
# (re_attempts.log: the AIStates.cpp and EntEnragedUpdate merges, whose seeds
# carry an unrelated #define and #pragma, were refused as new private copies).
NEUTRAL_DIRECTIVES = '#define X_FRAMES 30\n#pragma intrinsic(_ReadWriteBarrier)\n#undef Y_OLD\n#define EXPORT\n'


@pytest.mark.parametrize('side', ['donor', 'destination', 'both'])
def test_tu_merge_beside_neutral_directives_credits_the_moved_body(repo, capsys, side):
    assert class_gate.moved_bodies(NEUTRAL_DIRECTIVES + X_BODY) == class_gate.moved_bodies(X_BODY)
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    old = (NEUTRAL_DIRECTIVES if side in ('donor', 'both') else '') + X_BODY
    new = (NEUTRAL_DIRECTIVES if side in ('destination', 'both') else '') + X_BODY
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    # The scope-qualified identity reader (class_layouts) still cannot read a
    # #define; in shadow mode it only reports, so the name check decides.
    assert rc == 0
    assert all('[shadow]' in line for line in err.splitlines())


def test_tu_merge_beside_neutral_directives_still_refuses_an_edited_body(repo, capsys):
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, X_BODY + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + NEUTRAL_DIRECTIVES + X_BODY.replace('int a;', 'int b;') + FRESH, OLD)
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`X`' in err


@pytest.mark.parametrize('ambiguous', [
    '#define OPEN namespace A {\n' + X_BODY,
    '#define OPEN }\n' + X_BODY,
    '#define DECL int a;\n' + X_BODY,
    '#define HASH #\n' + X_BODY,
    '#define BRACE <%\n' + X_BODY,
    '#define PAREN (\n' + X_BODY,
    '#if 1\n' + X_BODY + '#endif\n',
    '#ifdef A\n' + X_BODY + '#endif\n',
    '#ifndef A\n#else\n' + X_BODY + '#endif\n',
    '#define OPEN(a) namespace a {\n' + X_BODY,
    '#define F(a) a\n' + X_BODY,
    '%:define N 1\n' + X_BODY,
    '%:pragma once\n' + X_BODY,
    '#line 10\n' + X_BODY,
    '#error no\n' + X_BODY,
    '#\n' + X_BODY,
    '#define int long\n' + X_BODY,
    '#undef class\n' + X_BODY,
    '#define N 1 /* the define\n continues */ {\n' + X_BODY + '}\n',
    '#define T int\nclass X { T a; };\n',
    '#define X Y\n' + X_BODY,
    '#define S A\n' + scoped_x('namespace S'),
    '#define S A\n' + scoped_x('class S'),
])
@pytest.mark.parametrize('side', ['donor', 'destination'])
def test_scope_forming_directive_gets_no_move_credit(repo, capsys, ambiguous, side):
    assert class_gate.moved_bodies(ambiguous) == {}
    old, new = (ambiguous, X_BODY) if side == 'donor' else (X_BODY, ambiguous)
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`X`' in err


def test_macro_use_refuses_only_the_class_that_uses_it():
    # An object-like macro cannot open a scope, so a class that does not use it keeps credit.
    text = '#define T int\nclass Y { T b; };\n' + X_BODY
    found = class_gate.moved_bodies(text)
    assert found['X'] == class_gate.moved_bodies(X_BODY)['X']
    assert 'Y' not in found


# A `??` that starts an MSVC mangled name is no trigraph (re_attempts.log: the
# LivingWorldLogic.cpp merge carried BfmeFiveArgCtorWI.cpp's
# `#pragma comment(linker, "/alternatename:??1...")` and lost all move credit).
MANGLED = ['??1X@@QAE@XZ', '??0X@@QAE@XZ', '??_GX@@UAEPAXI@Z', '??_7X@@6B@']


def mangled_pragma(name):
    return '#pragma comment(linker, "/alternatename:%s=?real@@YAXXZ")\n' % name


@pytest.mark.parametrize('name', MANGLED)
def test_mangled_name_in_a_pragma_is_no_trigraph(name):
    assert class_gate.scope_code(mangled_pragma(name) + X_BODY) is not None
    assert class_gate.moved_bodies(mangled_pragma(name) + X_BODY) == class_gate.moved_bodies(X_BODY)
    assert class_gate.moved_bodies(X_BODY + mangled_pragma(name))['X'] == class_gate.moved_bodies(X_BODY)['X']


@pytest.mark.parametrize('name', MANGLED)
@pytest.mark.parametrize('side', ['donor', 'destination', 'both'])
def test_tu_merge_beside_a_mangled_name_pragma_credits_the_moved_body(repo, capsys, name, side):
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    old = (mangled_pragma(name) if side in ('donor', 'both') else '') + X_BODY
    new = (mangled_pragma(name) if side in ('destination', 'both') else '') + X_BODY
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 0
    assert all('[shadow]' in line for line in err.splitlines())


def test_tu_merge_beside_a_mangled_name_pragma_still_refuses_an_edited_body(repo, capsys):
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, mangled_pragma(MANGLED[0]) + X_BODY + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + mangled_pragma(MANGLED[0]) + X_BODY.replace('int a;', 'int b;') + FRESH, OLD)
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`X`' in err


# Each of the nine real trigraphs, and a backslash splice, on a directive line
# still voids the unit's move credit, wherever the line sits.
TRIGRAPH_LINES = ['#pragma message("a??%sb")\n' % char for char in "=/'()!<>-"]
SPLICE_LINES = [mangled_pragma(MANGLED[0]).replace('\n', ' \\\n'),
                '#pragma message("a??1b") \\\n']


def test_the_nine_trigraphs_are_exactly_the_refused_ones():
    assert len(TRIGRAPH_LINES) == 9
    for char in map(chr, range(32, 127)):
        line = '#pragma message("a??%sb")\n' % char
        assert (class_gate.scope_code(line + X_BODY) is None) == (char in "=/'()!<>-"), char


@pytest.mark.parametrize('line', TRIGRAPH_LINES + SPLICE_LINES)
def test_trigraph_or_splice_directive_gets_no_move_credit_at_unit_level(line):
    assert class_gate.scope_code(line + X_BODY) is None
    assert class_gate.scoped_move_spans(line + X_BODY) == []
    assert class_gate.moved_bodies(line + X_BODY) == {}
    assert class_gate.moved_bodies(X_BODY + line) == {}


@pytest.mark.parametrize('line', TRIGRAPH_LINES + SPLICE_LINES)
@pytest.mark.parametrize('side', ['donor', 'destination'])
def test_trigraph_or_splice_directive_gets_no_move_credit(repo, capsys, line, side):
    ambiguous = line + X_BODY
    old, new = (ambiguous, X_BODY) if side == 'donor' else (X_BODY, ambiguous)
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, old + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + new + FRESH, OLD)
    assert class_gate.staged_renames() == {}
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`X`' in err


def test_template_body_of_a_registered_class_is_never_credited(repo, capsys):
    # The donor's X is a template; a plain X in the merged unit is new.
    repo.write('reverse/canonical_classes.csv', 'class,header\nX,Code/Game/X.h\n')
    repo.write(OLD, 'template <class T> class X { int a; };\n' + BODY)
    repo.commit('reverse/canonical_classes.csv', OLD)
    merge_into(repo, FILLER + X_BODY + FRESH, OLD)
    rc, err = repo.gate(capsys)
    assert rc == 1 and '`X`' in err


# Step 2: the scope-qualified identity check, its template move credit and its mode.
HASH = ("namespace rts {\ntemplate <class K> struct hash {\n"
        "    unsigned operator()(const K &k) const { return 0; }\n};\n}\n")
HASH_INT = ("namespace rts {\ntemplate <> struct hash<int> {\n"
            "    unsigned operator()(int k) const { return k; }\n};\n}\n")
MODE_PATH = "reverse/class_gate_mode.txt"


@pytest.fixture
def trepo(tmp_path, monkeypatch):
    r = Repo(tmp_path, monkeypatch)
    r.write("reverse/canonical_classes.csv",
            "class,header\nGameLogic,Code/Game/GameLogic.h\nrts::hash,Code/Game/RtsHashView.h\n")
    r.write(OLD, "int old() { return 0; }\n")
    r.write("Code/Game/Other.cpp", "int other() { return 0; }\n")
    r.commit(".")
    return r


def set_mode(repo, mode, commit=True):
    repo.write(MODE_PATH, f"# mode: {mode}\n")
    if commit:
        repo.commit(MODE_PATH)
    else:
        repo.stage(MODE_PATH)


def test_a_new_template_copy_is_reported_in_shadow_and_logged(trepo, capsys):
    set_mode(trepo, "shadow")
    trepo.write(NEW, HASH + BODY)
    trepo.stage(NEW)
    rc, err = trepo.gate(capsys)
    assert rc == 0 and "class_gate [shadow] Code/Game/New.cpp: would refuse `rts::hash`" in err
    log = (trepo.root / ".git" / "class_gate_shadow.jsonl").read_text()
    assert '"key": "rts::hash"' in log and '"path": "Code/Game/New.cpp"' in log


def test_a_missing_mode_file_is_shadow_never_off(trepo, capsys):
    trepo.write(NEW, HASH + BODY)
    trepo.stage(NEW)
    rc, err = trepo.gate(capsys)
    assert rc == 0 and "[shadow]" in err and "rts::hash" in err


def test_a_new_template_copy_is_refused_in_enforce(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(NEW, HASH + BODY)
    trepo.stage(NEW)
    rc, err = trepo.gate(capsys)
    assert rc == 1 and "class_gate [refused] Code/Game/New.cpp: defines its own `rts::hash`" in err


def test_a_new_specialization_beside_an_existing_primary_is_refused(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(OLD, HASH + BODY)
    trepo.commit(OLD)
    trepo.write(OLD, HASH + HASH_INT + BODY)
    trepo.stage(OLD)
    rc, err = trepo.gate(capsys)
    assert rc == 1 and "`rts::hash<int>`" in err and "`rts::hash` " not in err


def test_using_the_template_without_a_copy_passes(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(NEW, '#include "RtsHashView.h"\nrts::hash<int> h;\nint f() { return h(1); }\n')
    trepo.stage(NEW)
    assert trepo.gate(capsys) == (0, "")


def test_an_edit_beside_an_existing_copy_passes(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(OLD, HASH + BODY)
    trepo.commit(OLD)
    trepo.write(OLD, HASH + BODY + "int added() { return 4; }\n")
    trepo.stage(OLD)
    assert trepo.gate(capsys) == (0, "")


def test_a_merge_moving_a_template_copy_verbatim_is_credited(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(OLD, HASH + BODY)
    trepo.commit(OLD)
    trepo.git("rm", "-q", "--", OLD)
    trepo.write(NEW, FILLER + "// merged\n" + HASH + BODY)
    trepo.stage(NEW)
    assert trepo.gate(capsys) == (0, "")


def test_a_merge_with_an_edited_template_body_is_refused(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(OLD, HASH + BODY)
    trepo.commit(OLD)
    trepo.git("rm", "-q", "--", OLD)
    trepo.write(NEW, FILLER + HASH.replace("return 0;", "return 1;") + BODY)
    trepo.stage(NEW)
    rc, err = trepo.gate(capsys)
    assert rc == 1 and "`rts::hash`" in err


def test_one_deleted_template_body_credits_one_copy(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(OLD, HASH + BODY)
    trepo.commit(OLD)
    trepo.git("rm", "-q", "--", OLD)
    trepo.write(NEW, FILLER + HASH + BODY)
    trepo.write("Code/Game/Third.cpp", FILLER + HASH + "int third() { return 3; }\n")
    trepo.stage(NEW, "Code/Game/Third.cpp")
    rc, err = trepo.gate(capsys)
    assert rc == 1 and err.count("[refused]") == 1


def test_an_unreadable_unit_is_compared_by_key(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(NEW, "#define FLAG 1\n" + HASH + BODY)
    trepo.stage(NEW)
    rc, err = trepo.gate(capsys)
    assert rc == 1 and "`rts::hash` (an unreadable unit, compared by heads)" in err


def test_an_allow_marker_names_a_qualified_key(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(NEW, "// class-gate: allow rts::hash proved codegen view\n" + HASH + BODY)
    trepo.stage(NEW)
    assert trepo.gate(capsys) == (0, "")


def test_a_class_in_another_namespace_is_not_the_registered_one(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(NEW, "namespace other {\nstruct hash { int a; };\n}\n" + BODY)
    trepo.stage(NEW)
    assert trepo.gate(capsys) == (0, "")


def test_enforce_never_returns_to_shadow(trepo, capsys):
    set_mode(trepo, "enforce")
    set_mode(trepo, "shadow", commit=False)
    rc, err = trepo.gate(capsys)
    assert rc == 1 and "never returns from enforce to shadow" in err


def test_shadow_census_writes_a_dated_summary(trepo, monkeypatch, capsys):
    import tu_skeleton
    trepo.write("Code/Game/A.cpp", HASH + "int a() { return 1; }\n")
    trepo.write("Code/Game/B.cpp", HASH.replace("return 0;", "return 2;") + "int b() { return 2; }\n")
    trepo.write("Code/Game/C.cpp", HASH + "int c() { return 3; }\n")
    trepo.commit(".")
    monkeypatch.setattr(tu_skeleton, "queue_entries", lambda: [{"tu": "Code/Game/AB.cpp"}, {"tu": "Code/Game/AC.cpp"}])
    monkeypatch.setattr(tu_skeleton, "skeleton", lambda tu: tu)
    donors = {"Code/Game/AB.cpp": ["Code/Game/A.cpp", "Code/Game/B.cpp"],
              "Code/Game/AC.cpp": ["Code/Game/A.cpp", "Code/Game/C.cpp"]}
    monkeypatch.setattr(tu_skeleton, "donors", lambda tu, sk: ({d: [] for d in donors[tu]}, {}, {}))
    assert class_gate.main(["--shadow-census", "build/class_gate_shadow"]) == 0
    out = capsys.readouterr().out
    assert "would refuse Code/Game/AB.cpp: rts::hash" in out and "AC.cpp" not in out
    written = list((trepo.root / "build" / "class_gate_shadow").glob("class_gate_shadow_*.json"))
    assert len(written) == 1 and '"copies_per_key"' in written[0].read_text()


def test_two_identical_destinations_in_one_unit_never_exhaust_the_credit(trepo, capsys):
    # Review of ad0a3497fc: one deleted body and two identical copies in one staged unit popped an
    # empty pool (IndexError) and changed the gate's exit in shadow mode.
    set_mode(trepo, "shadow")
    trepo.write(OLD, HASH + BODY)
    trepo.commit(OLD)
    trepo.git("rm", "-q", "--", OLD)
    trepo.write(NEW, FILLER + HASH + BODY + HASH)
    trepo.stage(NEW)
    rc, err = trepo.gate(capsys)
    assert rc == 0 and "IndexError" not in err and "would refuse `rts::hash`" in err


def test_an_identity_check_failure_cannot_change_the_gate_in_shadow(trepo, capsys, monkeypatch):
    set_mode(trepo, "shadow")
    trepo.write(NEW, HASH + BODY)
    trepo.stage(NEW)
    monkeypatch.setattr(class_gate, "introduced_identities", lambda *a: 1 / 0)
    rc, err = trepo.gate(capsys)
    assert rc == 0 and "[shadow] identity check failed on Code/Game/New.cpp: ZeroDivisionError" in err
    monkeypatch.setattr(class_gate, "staged_identity_deletions", lambda *a: [][1])
    rc, err = trepo.gate(capsys)
    assert rc == 0 and "identity check failed on move credit: IndexError" in err


def test_an_identity_check_failure_fails_closed_in_enforce(trepo, capsys, monkeypatch):
    set_mode(trepo, "enforce")
    trepo.write(NEW, "int x() { return 0; }\n")
    trepo.stage(NEW)
    monkeypatch.setattr(class_gate, "introduced_identities", lambda *a: 1 / 0)
    rc, err = trepo.gate(capsys)
    assert rc == 1 and "[refused] identity check failed" in err


@pytest.mark.parametrize("before_define,after_define", [(False, True), (True, True), (True, False)])
def test_a_new_specialization_shows_when_a_side_is_unreadable(trepo, capsys, before_define, after_define):
    # Review of ad0a3497fc: a #define made the unit unreadable and hash<int> vanished.
    set_mode(trepo, "enforce")
    trepo.write(OLD, ("#define FLAG 1\n" if before_define else "") + HASH + BODY)
    trepo.commit(OLD)
    trepo.write(OLD, ("#define FLAG 1\n" if after_define else "") + HASH + HASH_INT + BODY)
    trepo.stage(OLD)
    rc, err = trepo.gate(capsys)
    assert rc == 1 and "`rts::hash<int>` (an unreadable unit, compared by heads)" in err


def test_an_unchanged_unreadable_unit_reports_nothing(trepo, capsys):
    set_mode(trepo, "enforce")
    trepo.write(OLD, "#define FLAG 1\n" + HASH + HASH_INT + BODY)
    trepo.commit(OLD)
    trepo.write(OLD, "#define FLAG 1\n" + HASH + HASH_INT + BODY + "int more() { return 5; }\n")
    trepo.stage(OLD)
    assert trepo.gate(capsys) == (0, "")


def test_move_credit_may_come_from_an_unrelated_deleted_unit(trepo, capsys):
    # Accepted by design: credit checks identity, scope and body, not TU-merge provenance; one
    # deleted copy credits one staged copy, so the number of private copies cannot grow.
    set_mode(trepo, "enforce")
    trepo.write("Code/Other/Far.cpp", HASH + "int far() { return 9; }\n")
    trepo.commit("Code/Other/Far.cpp")
    trepo.git("rm", "-q", "--", "Code/Other/Far.cpp")
    trepo.write(NEW, HASH + BODY)
    trepo.stage(NEW)
    assert trepo.gate(capsys) == (0, "")


def fail_shadow_log_git(monkeypatch):
    """Make only the shadow log's git call fail to launch; the gate's own git calls still run."""
    real = class_gate.subprocess.run

    def run(args, *rest, **kwargs):
        if list(args[:2]) == ["git", "rev-parse"]:
            raise OSError("cannot launch git")
        return real(args, *rest, **kwargs)
    monkeypatch.setattr(class_gate.subprocess, "run", run)


def test_a_failing_shadow_log_cannot_change_a_shadow_finding(trepo, capsys, monkeypatch):
    set_mode(trepo, "shadow")
    trepo.write(NEW, HASH + BODY)
    trepo.stage(NEW)
    fail_shadow_log_git(monkeypatch)
    rc, err = trepo.gate(capsys)
    assert rc == 0 and "class_gate [shadow] Code/Game/New.cpp: would refuse `rts::hash`" in err
    assert not (trepo.root / ".git" / "class_gate_shadow.jsonl").exists()


def test_a_failing_shadow_log_cannot_change_a_shadow_error_report(trepo, capsys, monkeypatch):
    set_mode(trepo, "shadow")
    trepo.write(NEW, HASH + BODY)
    trepo.stage(NEW)
    fail_shadow_log_git(monkeypatch)
    monkeypatch.setattr(class_gate, "introduced_identities", lambda *a: 1 / 0)
    rc, err = trepo.gate(capsys)
    assert rc == 0 and "[shadow] identity check failed on Code/Game/New.cpp: ZeroDivisionError" in err
    assert class_gate.identity_failure("Code/Game/New.cpp", OSError("x"), "shadow") == 0


def test_a_failing_shadow_print_or_log_write_cannot_change_the_gate(trepo, capsys, monkeypatch):
    set_mode(trepo, "shadow")
    trepo.write(NEW, HASH + BODY)
    trepo.stage(NEW)
    real_print = print

    def broken_print(*args, **kwargs):
        if args and "[shadow]" in str(args[0]):
            raise ValueError("closed stream")
        return real_print(*args, **kwargs)
    monkeypatch.setattr(class_gate, "print", broken_print, raising=False)
    monkeypatch.setattr(class_gate.json if hasattr(class_gate, "json") else __import__("json"), "dumps",
                        lambda *a, **k: (_ for _ in ()).throw(TypeError("unserializable")))
    rc, _err = trepo.gate(capsys)
    assert rc == 0
    assert class_gate.identity_failure("move credit", OSError("x"), "shadow") == 0
    assert class_gate.identity_failure("move credit", OSError("x"), "enforce") == 1
