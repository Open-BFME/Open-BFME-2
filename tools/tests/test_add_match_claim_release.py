"""add_match and add_match_batch must not release a shared claim on LOCAL
verification.

They called claims.release([rva], force=True) right after the local byte
gate, before the commit was pushed (and AGENTS.md batches pushes), so another
worker could take a body whose conversion was still unpublished, and `force`
could delete another seat's claim. They now queue the exact row, and the
claim is released only once origin/master holds it (claims.release_landed).
Ported from Open-BFME-1's tools/tests/test_add_match_claim_release.py; its
receipt and fleet-fencing cases test add_match features BFME2 does not have.
"""
import json
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match  # noqa: E402
import add_match_batch  # noqa: E402
import claims  # noqa: E402

HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
DUMP = "?d_00abcd00@@YAXXZ,,0x00ABCD00,32,Code/gen_asm/d_00abcd00.asm,matched,gen-dump"
DUMP2 = "?d_00abcd40@@YAXXZ,,0x00ABCD40,16,Code/gen_asm/d_00abcd40.asm,matched,gen-dump"
REAL = "?realBody@Thing@@QAEXXZ"
REAL2 = "?otherBody@Thing@@QAEXXZ"
SOURCE_REL = "Code/GameEngine/Source/Common/Thing.cpp"


@pytest.fixture
def landing(tmp_path, monkeypatch):
    reverse = tmp_path / "reverse"
    reverse.mkdir(parents=True)
    source = tmp_path / SOURCE_REL
    source.parent.mkdir(parents=True)
    source.write_bytes(f"// {REAL} present-unmatched\n// {REAL2} present-unmatched\n"
                       "void realBody() {}\nvoid otherBody() {}\n".encode())
    (reverse / "functions.csv").write_bytes(f"{HEADER}\n{DUMP}\n{DUMP2}\n".encode())
    (tmp_path / "build.sh").write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
    monkeypatch.setattr(add_match, "DEFAULT_ROOT", tmp_path)
    monkeypatch.setattr(add_match_batch, "DEFAULT_ROOT", tmp_path)
    real_run = subprocess.run
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)

    def run(command, *args, **kwargs):     # the byte gate passes; git stays real
        if command[0] == "git":
            return real_run(command, *args, **kwargs)
        return SimpleNamespace(returncode=0)
    monkeypatch.setattr(add_match.subprocess, "run", run)
    monkeypatch.setenv("BFME_CLAIM_OWNER", "worker-a")
    monkeypatch.delenv("BFME_CLAIMS", raising=False)

    def forbidden(*args, **kwargs):
        raise AssertionError("a landing released a claim before publication")
    monkeypatch.setattr(claims, "release", forbidden)
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", REAL, "0x00ABCD00", "32", SOURCE_REL, "--replace-rva", "0x00ABCD00",
        "--root", str(tmp_path)])
    return tmp_path


def _queued(root):
    return [json.loads(line) for line in
            (root / claims.PENDING).read_text(encoding="utf-8").splitlines()]


def test_local_verification_queues_instead_of_releasing(landing):
    add_match.main()
    queued = _queued(landing)
    assert len(queued) == 1
    assert queued[0]["rva"] == "0x00ABCD00" and queued[0]["owner"] == "worker-a"
    assert queued[0]["row"] == f"{REAL},,0x00ABCD00,32,{SOURCE_REL},matched,"
    assert queued[0]["deps"][SOURCE_REL]            # bound to the verified source blob


def test_claims_off_queues_nothing(landing, monkeypatch):
    monkeypatch.setenv("BFME_CLAIMS", "off")
    add_match.main()
    assert not (landing / claims.PENDING).exists()


def test_a_test_only_root_never_queues(landing, monkeypatch):
    monkeypatch.setattr(add_match, "DEFAULT_ROOT", landing / "elsewhere")
    add_match.main()
    assert not (landing / claims.PENDING).exists()


def test_a_batch_queues_every_row_instead_of_releasing(landing, monkeypatch):
    manifest = landing / "rows.csv"
    manifest.write_text(f"{REAL},0x00ABCD00,32,{SOURCE_REL},,0x00ABCD00\n"
                        f"{REAL2},0x00ABCD40,16,{SOURCE_REL},,0x00ABCD40\n", encoding="utf-8")
    monkeypatch.setattr(sys, "argv", ["add_match_batch.py", str(manifest), "--root", str(landing)])
    add_match_batch.main()
    queued = _queued(landing)
    assert [e["rva"] for e in queued] == ["0x00ABCD00", "0x00ABCD40"]
    assert {e["owner"] for e in queued} == {"worker-a"}
    assert queued[1]["row"] == f"{REAL2},,0x00ABCD40,16,{SOURCE_REL},matched,"
    assert queued[0]["deps"] == queued[1]["deps"] and queued[0]["deps"][SOURCE_REL]
    assert not any(e["deps_truncated"] for e in queued)
