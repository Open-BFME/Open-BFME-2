"""Flag proposals see the pending row, but never replace its ordinary byte gate."""
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match


@pytest.fixture
def transaction(tmp_path, monkeypatch):
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    ledger = reverse / "functions.csv"
    ledger.write_bytes(b"name,export_rva,target_rva,target_size,source,status,notes\n")
    source = tmp_path / "Code/Example.cpp"
    source.parent.mkdir()
    source.write_bytes(b"// ?example@@YAXXZ present-unmatched\nvoid example() {}\n")
    (tmp_path / "build.sh").write_text("#!/bin/sh\nexit 0\n")
    overrides = reverse / "flag_overrides.csv"
    overrides.write_bytes(b"source,flags,rows,default_lost,reason\nCode/Other.cpp,/O2,1,1,existing\n")
    monkeypatch.setattr(sys, "argv", ["add_match.py", "?example@@YAXXZ", "0x1000", "6",
                                    "Code/Example.cpp", "--root", str(tmp_path), "--propose-flags"])
    before = {p: p.read_bytes() for p in (ledger, source, overrides)}
    calls = []

    def run(command, **kwargs):
        calls.append(command)
        assert kwargs["cwd"] == tmp_path
        assert b"?example@@YAXXZ,,0x00001000,6," in ledger.read_bytes()
        assert b"present-unmatched" not in source.read_bytes()
        if Path(command[1]).name == "flag_defaults.py":
            assert command == [sys.executable, str(tmp_path / "tools/flag_defaults.py"),
                               "propose", "Code/Example.cpp"]
            overrides.write_bytes(overrides.read_bytes() + b"Code/Example.cpp,/O2,1,1,region default loses rows\n")
        return SimpleNamespace(returncode=0)

    monkeypatch.setattr(add_match.subprocess, "run", run)
    return SimpleNamespace(root=tmp_path, ledger=ledger, source=source, overrides=overrides,
                           before=before, calls=calls, run=run)


def test_proposal_precedes_unchanged_full_source_gate(transaction):
    add_match.main()
    assert len(transaction.calls) == 2
    assert Path(transaction.calls[0][1]).name == "flag_defaults.py"
    assert transaction.calls[1][-1] == "Code/Example.cpp"
    assert b"Code/Example.cpp,/O2" in transaction.overrides.read_bytes()
    assert b"Code/Other.cpp,/O2" in transaction.overrides.read_bytes()


@pytest.mark.parametrize("stage", ["proposal", "build"])
@pytest.mark.parametrize("failure", ["exit", "interrupt"])
@pytest.mark.parametrize("existing_override_file", [True, False])
def test_failure_rolls_back_row_marker_and_override(transaction, monkeypatch, stage,
                                                  failure, existing_override_file):
    if not existing_override_file:
        transaction.overrides.unlink()
        transaction.before.pop(transaction.overrides)

    def run(command, **kwargs):
        transaction.calls.append(command)
        proposal = Path(command[1]).name == "flag_defaults.py"
        if proposal:
            transaction.overrides.write_bytes(b"partially written proposal\n")
        if proposal == (stage == "proposal"):
            if failure == "interrupt":
                raise KeyboardInterrupt()
            return SimpleNamespace(returncode=1)
        return SimpleNamespace(returncode=0)

    monkeypatch.setattr(add_match.subprocess, "run", run)
    with pytest.raises(KeyboardInterrupt if failure == "interrupt" else SystemExit):
        add_match.main()
    assert len(transaction.calls) == (1 if stage == "proposal" else 2)
    for path, before in transaction.before.items():
        assert path.read_bytes() == before
    if not existing_override_file:
        assert not transaction.overrides.exists()


def test_no_verify_cannot_admit_flag_proposal(transaction, monkeypatch):
    monkeypatch.setattr(sys, "argv", sys.argv + ["--no-verify"])
    with pytest.raises(SystemExit):
        add_match.main()
    assert not transaction.calls
    for path, before in transaction.before.items():
        assert path.read_bytes() == before


def test_default_path_does_not_run_proposal_or_change_overrides(transaction, monkeypatch):
    monkeypatch.setattr(sys, "argv", [arg for arg in sys.argv if arg != "--propose-flags"])
    add_match.main()
    assert len(transaction.calls) == 1
    assert transaction.overrides.read_bytes() == transaction.before[transaction.overrides]


@pytest.mark.parametrize("change", ["write", "delete"])
def test_rollback_preserves_register_changed_after_proposal(transaction, monkeypatch, change):
    def run(command, **kwargs):
        if Path(command[1]).name == "flag_defaults.py":
            return transaction.run(command, **kwargs)
        if change == "write":
            transaction.overrides.write_bytes(b"another writer's updated register\n")
        else:
            transaction.overrides.unlink()
        return SimpleNamespace(returncode=1)

    monkeypatch.setattr(add_match.subprocess, "run", run)
    with pytest.raises(RuntimeError, match="register changed after proposal"):
        add_match.main()
    for path in (transaction.ledger, transaction.source):
        assert path.read_bytes() == transaction.before[path]
    if change == "write":
        assert transaction.overrides.read_bytes() == b"another writer's updated register\n"
    else:
        assert not transaction.overrides.exists()
