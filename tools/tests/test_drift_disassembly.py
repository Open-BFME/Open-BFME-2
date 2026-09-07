"""A present but incompatible objdump must not classify every body as structural."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import drift_classify


def test_objdump_failure_is_not_treated_as_success(monkeypatch, tmp_path):
    monkeypatch.setattr(drift_classify, "SCRATCH", tmp_path)

    def incompatible_objdump(command, **kwargs):
        assert kwargs["check"] is True
        raise subprocess.CalledProcessError(1, command, stderr="unknown argument '-b'")

    monkeypatch.setattr(drift_classify.subprocess, "run", incompatible_objdump)
    result = drift_classify.disasm(b"\x55\x8b\xec\xc3")
    assert [item[0] for item in result] == ["push", "mov", "ret"]
    assert result[1][2] == "ebp, esp"


def test_successful_gnu_output_remains_the_reference_backend(monkeypatch, tmp_path):
    monkeypatch.setattr(drift_classify, "SCRATCH", tmp_path)
    monkeypatch.setattr(drift_classify.subprocess, "run", lambda *args, **kwargs:
                        subprocess.CompletedProcess(args[0], 0, "   0:  c3                   ret\n", ""))
    monkeypatch.setattr(drift_classify, "_disasm_capstone", lambda data:
                        pytest.fail("A working GNU backend should be used directly"))
    assert drift_classify.disasm(b"\xc3") == [("ret", "", "")]


def test_absent_objdump_uses_the_same_supported_decoder(monkeypatch, tmp_path):
    monkeypatch.setattr(drift_classify, "SCRATCH", tmp_path)

    def missing(*args, **kwargs):
        raise FileNotFoundError("objdump")

    monkeypatch.setattr(drift_classify.subprocess, "run", missing)
    assert drift_classify.disasm(b"\xc3") == [("ret", "", "")]
