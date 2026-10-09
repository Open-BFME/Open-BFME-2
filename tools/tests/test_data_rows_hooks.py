"""The hooks byte-verify a data_rows.csv claim like a functions.csv one.

Review of cd1336610f: a commit staging only reverse/data_rows.csv took the
pre-commit hook's early exit, delta_sources.py read only functions.csv, the
parked-draft filter and pre-push's edited-source list knew only function rows,
and ledger_guard.py did not cover data_rows.csv. So a data row, or an edit to a
data-only TU, could be published with nothing verified. Each case runs the real
hook in test_hook_fail_closed's throwaway repository, with the real
delta_sources.py and ledger_guard.py; tools/build.py records what it was asked
to verify.
"""
import shutil

import pytest

from test_hook_fail_closed import ROOT, built, git, push_refs, repo, run, write  # noqa: F401

DATA_SOURCE = "Code/GameEngine/Source/Common/Language.cpp"
DATA_LEDGER = "reverse/data_rows.csv"
DATA_HEAD = "name,address,address_kind,size,section,source,status,evidence,model\n"
DATA_ROW = (f"?OurLanguage@@3W4LanguageID@@A,0x00DFE000,va,4,.data,{DATA_SOURCE},matched,"
            "ZH Common/Language.cpp defines it,m\n")


@pytest.fixture
def data_repo(repo):  # noqa: F811
    """The hook fixture plus a data-only TU, a header-only data ledger and the real
    delta_sources.py and ledger_guard.py."""
    write(repo, DATA_SOURCE, "int OurLanguage = 0;\n")
    write(repo, DATA_LEDGER, DATA_HEAD)
    for tool in ("delta_sources", "ledger_guard"):
        shutil.copyfile(ROOT / "tools" / f"{tool}.py", repo / "tools" / f"{tool}.py")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "data ledger")
    return repo


# ---------------------------------------------------------------- pre-commit

def test_pre_commit_verifies_a_ledger_only_data_row(data_repo):
    # Positive control: before, this commit took the early exit with nothing verified.
    write(data_repo, DATA_LEDGER, DATA_HEAD + DATA_ROW)
    git(data_repo, "add", DATA_LEDGER)
    result = run(data_repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert "PRE-COMMIT OK (ledger integrity + 1 source(s) byte-verified)" in result.stdout
    assert built(data_repo) == {DATA_SOURCE}


def test_pre_commit_refuses_a_data_ledger_whose_working_copy_differs(data_repo):
    write(data_repo, DATA_LEDGER, DATA_HEAD + DATA_ROW)
    git(data_repo, "add", DATA_LEDGER)
    write(data_repo, DATA_LEDGER, DATA_HEAD + DATA_ROW.replace("0x00DFE000", "0x00DFE004"))
    result = run(data_repo, "pre-commit")
    assert result.returncode == 1
    assert DATA_LEDGER in result.stderr
    assert not built(data_repo)


def test_pre_commit_refuses_an_unstaged_data_row_beside_a_staged_source(data_repo):
    # The build would prove the staged unit against a data row this commit lacks.
    write(data_repo, "Code/GameEngine/Source/Common/Unit.cpp",
          "struct Unit { void f(); };\nvoid Unit::f() { int x = 0; }\n")
    git(data_repo, "add", "Code")
    write(data_repo, DATA_LEDGER, DATA_HEAD + DATA_ROW)
    result = run(data_repo, "pre-commit")
    assert result.returncode == 1
    assert "PRE-COMMIT FAILED: unstaged ledger edits would be verified" in result.stderr
    assert DATA_LEDGER in result.stderr
    assert not built(data_repo)


# ---------------------------------------------------------------- pre-push

def test_pre_push_verifies_an_outgoing_data_row(data_repo):
    base = git(data_repo, "rev-parse", "HEAD")
    write(data_repo, DATA_LEDGER, DATA_HEAD + DATA_ROW)
    git(data_repo, "commit", "-qam", "data row")
    result = run(data_repo, "pre-push", push_refs(data_repo, base))
    assert result.returncode == 0, result.stderr
    assert "PRE-PUSH OK (1 outgoing source(s) byte-verified)" in result.stdout
    assert built(data_repo) == {DATA_SOURCE}


def test_pre_push_verifies_an_edited_data_only_source(data_repo):
    write(data_repo, DATA_LEDGER, DATA_HEAD + DATA_ROW)
    git(data_repo, "commit", "-qam", "data row")
    base = git(data_repo, "rev-parse", "HEAD")
    write(data_repo, DATA_SOURCE, "int OurLanguage = 1;\n")
    git(data_repo, "commit", "-qam", "edit the data-only unit, its row unchanged")
    result = run(data_repo, "pre-push", push_refs(data_repo, base))
    assert result.returncode == 0, result.stderr
    assert built(data_repo) == {DATA_SOURCE}
