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
