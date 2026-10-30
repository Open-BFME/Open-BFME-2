"""build._hash_file's memo against files rewritten within one timestamp tick."""
import hashlib
import sys
from pathlib import Path
from types import SimpleNamespace

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import build  # noqa: E402

SECOND = 1_793_301_543 * 10**9


def frozen_file(tmp_path, monkeypatch, text):
    """A file whose stat never changes, whatever is written to it: device,
    inode, size, mtime and ctime as a coarse file-time tick reports them for a
    same-size rewrite inside that tick."""
    path = tmp_path / "unit.cpp"
    path.write_bytes(text.encode())
    stamp = SimpleNamespace(st_dev=1, st_ino=2, st_size=len(text), st_mtime_ns=SECOND, st_ctime_ns=SECOND)
    monkeypatch.setattr(build, "os", SimpleNamespace(stat=lambda p: stamp))
    monkeypatch.setattr(build, "_HASH_MEMO", {})
    return path


def md5(text):
    return hashlib.md5(text.encode()).hexdigest()


def test_a_same_size_rewrite_inside_the_timestamp_tick_is_hashed_again(tmp_path, monkeypatch):
    path = frozen_file(tmp_path, monkeypatch, "int f() { return 2; }\n")
    monkeypatch.setattr(build, "_hash_clock", lambda: SECOND + 1_000_000, raising=False)  # hashed 1 ms later
    assert build._hash_file(str(path)) == md5("int f() { return 2; }\n")
    path.write_bytes("int f() { return 3; }\n".encode())                 # same size, same stat
    assert build._hash_file(str(path)) == md5("int f() { return 3; }\n")


def test_a_file_settled_before_it_was_hashed_is_served_from_the_memo(tmp_path, monkeypatch):
    path = frozen_file(tmp_path, monkeypatch, "int f() { return 2; }\n")
    monkeypatch.setattr(build, "_hash_clock", lambda: SECOND + 10 * 10**9, raising=False)  # hashed 10 s later
    assert build._hash_file(str(path)) == md5("int f() { return 2; }\n")
    # a later edit always moves the stamp; this one cannot, so the memo answers
    path.write_bytes("int f() { return 3; }\n".encode())
    assert build._hash_file(str(path)) == md5("int f() { return 2; }\n")
