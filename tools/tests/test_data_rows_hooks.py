"""The hooks byte-verify a data_rows.csv claim like a functions.csv one.

Review of cd1336610f: a commit staging only reverse/data_rows.csv took the
pre-commit hook's early exit, delta_sources.py read only functions.csv, the
parked-draft filter and pre-push's edited-source list knew only function rows,
and ledger_guard.py did not cover data_rows.csv. So a data row, or an edit to a
data-only TU, could be published with nothing verified. Round 2 (review of
b667b74e91): name_dependents.py ignored data rows, so deleting or moving `g`'s
data row, or dropping its pin, left `int *dp = &g;` unverified. Each case runs
the real hook in test_hook_fail_closed's throwaway repository, with the real
delta_sources.py, ledger_guard.py, name_dependents.py and data_rows.py;
tools/build.py records what it was asked to verify and offers name_dependents
the helpers it imports (no object is cached, so units are judged on their text).
"""
import shutil

import pytest

from test_hook_fail_closed import ROOT, built, git, push_refs, repo, run, write  # noqa: F401

DATA_SOURCE = "Code/GameEngine/Source/Common/Language.cpp"
DATA_LEDGER = "reverse/data_rows.csv"
PINS = "reverse/symbols.csv"
DATA_HEAD = "name,address,address_kind,size,section,source,status,evidence,model\n"
PIN_HEAD = "name,address,notes\n"
DATA_ROW = (f"?OurLanguage@@3W4LanguageID@@A,0x00DFE000,va,4,.data,{DATA_SOURCE},matched,"
            "ZH Common/Language.cpp defines it,m\n")
BUILD = """import json, sys
from pathlib import Path

LIB_SUFFIX = ".lib"


def is_alias_row(row):
    return False


def gate_baselined(kind, row):
    return False


def ledger_object_symbol(row):
    return row["name"]


def row_object(row):
    return Path("build/match") / (Path(row["source"]).stem + ".obj")  # never compiled here


if __name__ == "__main__":
    with open("build-calls.jsonl", "a", encoding="utf-8") as out:
        out.write(json.dumps(sys.argv[1:]) + "\\n")
"""


@pytest.fixture
def data_repo(repo):  # noqa: F811
    """The hook fixture plus a data-only TU, a header-only data ledger, an empty
    pin list and the real delta_sources.py, ledger_guard.py, name_dependents.py
    and data_rows.py."""
    write(repo, DATA_SOURCE, "int OurLanguage = 0;\n")
    write(repo, DATA_LEDGER, DATA_HEAD)
    write(repo, PINS, PIN_HEAD)
    write(repo, "tools/build.py", BUILD)
    for tool in ("delta_sources", "ledger_guard", "name_dependents", "data_rows"):
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


# ---------------------------------------------------------------- data rows that relocate to a lost name

G_SOURCE = "Code/GameEngine/Source/Common/GlobalG.cpp"
DP_SOURCE = "Code/GameEngine/Source/Common/GlobalPointer.cpp"
G_ROW = f"?g@@3HA,0x00DFE004,va,4,.data,{G_SOURCE},matched,fixture,m\n"
DP_ROW = f"?dp@@3PAHA,0x00DFE008,va,4,.data,{DP_SOURCE},matched,fixture,m\n"
G_PIN = "?g@@3HA,0x009FE004,fixture data pin\n"
# change: ((data rows, pins) before, (data rows, pins) after, sources the hook must verify)
CHANGES = {
    "data row deleted": ((G_ROW + DP_ROW, ""), (DP_ROW, ""), {DP_SOURCE}),
    "data row re-addressed": ((G_ROW + DP_ROW, ""), (G_ROW.replace("0x00DFE004", "0x00DFE00C") + DP_ROW, ""),
                              {G_SOURCE, DP_SOURCE}),
    "pin removed": ((DP_ROW, G_PIN), (DP_ROW, ""), {DP_SOURCE}),
}


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
@pytest.mark.parametrize("change", sorted(CHANGES))
def test_hooks_verify_a_data_row_whose_target_the_change_takes_away(data_repo, hook, change):
    # `int *dp = &g;` is retained, but g's home goes: dp's data row no longer
    # verifies (data_rows.verify_row), although neither dp's row nor its source changed.
    (rows_before, pins_before), (rows_after, pins_after), verified = CHANGES[change]
    write(data_repo, G_SOURCE, "int g = 0;\n")
    write(data_repo, DP_SOURCE, "extern int g;\nint *dp = &g;\n")
    write(data_repo, DATA_LEDGER, DATA_HEAD + rows_before)
    write(data_repo, PINS, PIN_HEAD + pins_before)
    git(data_repo, "add", "-A")
    git(data_repo, "commit", "-qm", "g and dp")
    base = git(data_repo, "rev-parse", "HEAD")
    write(data_repo, DATA_LEDGER, DATA_HEAD + rows_after)
    write(data_repo, PINS, PIN_HEAD + pins_after)
    git(data_repo, "add", DATA_LEDGER, PINS)
    if hook == "pre-push":
        git(data_repo, "commit", "-qm", change)
    result = run(data_repo, hook, push_refs(data_repo, base) if hook == "pre-push" else "")
    assert result.returncode == 0, result.stderr
    assert built(data_repo) == verified


def test_pre_push_verifies_an_edited_data_only_source(data_repo):
    write(data_repo, DATA_LEDGER, DATA_HEAD + DATA_ROW)
    git(data_repo, "commit", "-qam", "data row")
    base = git(data_repo, "rev-parse", "HEAD")
    write(data_repo, DATA_SOURCE, "int OurLanguage = 1;\n")
    git(data_repo, "commit", "-qam", "edit the data-only unit, its row unchanged")
    result = run(data_repo, "pre-push", push_refs(data_repo, base))
    assert result.returncode == 0, result.stderr
    assert built(data_repo) == {DATA_SOURCE}
