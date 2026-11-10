"""gen_small's swept funclets are scaffolding wherever the generator filed them.

`gen_small.py sweep-funclets` mints `uw_<rva>` rows straight into the parent's
real TU, while `gen_uw.py land` mints the same anonymous rows into its own
`Code/gen_small/uw_gen_NNN.cpp` harness. `generated_unwind_scaffold` knew only
the second, so a swept row could never shed its address-derived name: the row
with MORE evidence -- a proven parent, filed in the parent's own file -- was the
one refused. 98 recorded false rejects sat on that (`rg "false-reject add_match"
reverse/re_attempts.log`), 1,264 rows are in the state, and each takeover also
retires an `object-symbol=` hatch.

What proves a swept row is still anonymous generator output is the parent: its
`parent=` must be a matched row of the same source, which is the condition that
let the generator mint it (only a row names a source whose object holds the
`.text$x` symbols). Nothing in that source spells the funclet -- the parent's
compilation emits it as an associative COMDAT -- so the takeover renames a row
and never touches a body.
"""
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match
import add_match_batch
import pe_imports

HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
PARENT = "??1Impl@InGameCommandButtonMovieClip@@QAE@XZ"
TU = "Code/GameEngine/Source/Common/Rva005C7954ElemDtor.cpp"
NOTES = f"gen-funclet;parent={PARENT};object-symbol=$L1330"


def ledger_row(**over):
    row = {"name": "uw_007a0c4c", "export_rva": "", "target_rva": "0x007A0C4C",
           "target_size": "11", "source": TU, "status": "matched", "notes": NOTES}
    row.update(over)
    return row


def parent_row(**over):
    row = {"name": PARENT, "export_rva": "", "target_rva": "0x005C7954",
           "target_size": "213", "source": TU, "status": "matched", "notes": ""}
    row.update(over)
    return row


@pytest.fixture
def tree(tmp_path, monkeypatch):
    """A repo root holding the swept row, its parent, and the TU they name."""
    (tmp_path / "reverse").mkdir()
    source = tmp_path / TU
    source.parent.mkdir(parents=True)
    source.write_text("// the parent's body; the funclet is its own COMDAT\n", encoding="utf-8")
    (tmp_path / "build.sh").write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
    ledger = tmp_path / "reverse/functions.csv"

    def write(*rows):
        lines = [HEADER] + [",".join(r[k] for k in HEADER.split(",")) for r in rows]
        ledger.write_bytes(("\n".join(lines) + "\n").encode())

    write(parent_row(), ledger_row())
    calls = []
    monkeypatch.setattr(add_match.subprocess, "run", lambda *a, **k: (
        calls.append(a[0]), SimpleNamespace(returncode=0))[1])
    # A refusal falls through to the import kind, which would want a real PE.
    monkeypatch.setattr(pe_imports, "generated_import_scaffold", lambda *a, **k: False)
    monkeypatch.setenv("BFME_CLAIMS", "off")
    return SimpleNamespace(root=tmp_path, ledger=ledger, write=write, calls=calls)


@pytest.fixture(params=["single", "batch"])
def admission(tree, request, monkeypatch):
    if request.param == "single":
        monkeypatch.setattr(sys, "argv", [
            "add_match.py", "$L1330", "0x007A0C4C", "11", TU,
            "--notes", f"gen-funclet;parent={PARENT}",
            "--replace-rva", "0x007A0C4C", "--root", str(tree.root)])
        return add_match.main
    manifest = tree.root / "rows.csv"
    manifest.write_text(f"$L1330,0x007A0C4C,11,{TU},gen-funclet;parent={PARENT},0x007A0C4C\n")
    monkeypatch.setattr(sys, "argv", ["add_match_batch.py", str(manifest),
                                      "--root", str(tree.root)])
    return add_match_batch.main


def test_swept_funclet_yields_its_name_and_still_runs_the_byte_gate(tree, admission):
    admission()
    text = tree.ledger.read_text()
    assert len(tree.calls) == 1 and tree.calls[0][-1] == TU
    assert "uw_007a0c4c" not in text and "$L1330" in text
    # the takeover retires the object-symbol= hatch the generator needed
    assert "object-symbol=" not in text


def test_a_failed_build_restores_the_swept_row(tree, admission, monkeypatch):
    before = tree.ledger.read_bytes()
    attempts = []
    monkeypatch.setattr(add_match.subprocess, "run", lambda *a, **k: (
        attempts.append(a[0]), SimpleNamespace(returncode=1))[1])
    with pytest.raises(SystemExit):
        admission()
    # the row reached the gate and only then was rolled back, so this cannot
    # pass by the takeover being refused outright
    assert len(attempts) == 1
    assert tree.ledger.read_bytes() == before


@pytest.mark.parametrize("forge", [
    pytest.param({"name": "?realBody@@YAXXZ"}, id="a real name is not anonymous"),
    pytest.param({"name": "uw_00000000"}, id="name not derived from its own rva"),
    pytest.param({"notes": NOTES + "; verified parent EH graph places it here"},
                 id="worker prose makes it a real claim"),
    pytest.param({"notes": f"gen-funclet;object-symbol=$L1330"},
                 id="harness notes outside the harness path"),
    pytest.param({"notes": f"gen-funclet;parent=??1Other@@QAE@XZ;object-symbol=$L1330"},
                 id="parent is no row of this source"),
    pytest.param({"status": "unmatched"}, id="the scaffold row is not matched"),
    pytest.param({"source": "Code/gen_asm/dump.cpp"}, id="generated asm is never rewritten"),
])
def test_a_row_that_is_not_generator_output_keeps_its_address(tree, admission, forge):
    tree.write(parent_row(), ledger_row(**forge))
    before = tree.ledger.read_bytes()
    with pytest.raises(SystemExit):
        admission()
    assert tree.ledger.read_bytes() == before and tree.calls == []


def test_an_unverified_parent_proves_nothing(tree, admission):
    tree.write(parent_row(status="unmatched"), ledger_row())
    before = tree.ledger.read_bytes()
    with pytest.raises(SystemExit):
        admission()
    assert tree.ledger.read_bytes() == before and tree.calls == []


def test_a_parent_in_another_file_proves_nothing(tree, admission):
    tree.write(parent_row(source="Code/GameEngine/Source/Common/Other.cpp"), ledger_row())
    before = tree.ledger.read_bytes()
    with pytest.raises(SystemExit):
        admission()
    assert tree.ledger.read_bytes() == before and tree.calls == []


def test_without_the_ledger_the_parent_cannot_be_checked_so_nothing_yields():
    assert not add_match.swept_funclet_scaffold(
        {"name": "uw_007a0c4c", "rva": 0x007A0C4C, "size": 11,
         "source": TU, "status": "matched", "notes": NOTES})


def test_the_harness_kind_is_untouched_by_the_new_branch():
    """gen_uw's own rows keep being judged on path, header and body shape."""
    harness = {"name": "uw_007a0c4c", "rva": 0x007A0C4C, "size": 11,
               "source": "Code/gen_small/uw_gen_013.cpp", "status": "matched",
               "notes": "gen-funclet;object-symbol=$L1330"}
    assert not add_match.swept_funclet_scaffold(harness, [parent_row()])
