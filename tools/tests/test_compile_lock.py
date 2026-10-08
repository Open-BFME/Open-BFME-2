"""Full compiles isolate native caches while retaining Wine's host guard.

Subprocesses run the real compile_rows lock path with a compiler that waits for
an explicit release. Thus acquisition order is proved without timing a compiler
or writing any real object cache, including on hosts testing the other policy.
"""
import os
from pathlib import Path
import queue
import subprocess
import sys
import threading

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


_CHILD = r"""
import os
from pathlib import Path
import sys
from types import SimpleNamespace
sys.path.insert(0, sys.argv[1])
import build
root, cache, home = map(Path, sys.argv[2:5])
build.ROOT = root
build.BUILD_DIR = cache
# Select the compiler policy without changing pathlib's host OS or the actual
# portable_lock implementation. Every lock below is an actual process lock.
build.os = SimpleNamespace(**vars(os))
build.os.name = sys.argv[5]
build.Path.home = classmethod(lambda cls: home)
build.extract_lib_members = lambda rows: None
build.stale_sources = lambda sources, *args, **kwargs: list(sources)
build._pool_size = lambda: 1
first = True
def compile_source(source, output, **kwargs):
    global first
    if first:
        first = False
        print("acquired", flush=True)
        assert sys.stdin.readline().strip() == "release"
build.compile_source = compile_source
sources = [root / ("Source%d.cpp" % i) for i in range(int(sys.argv[6]))]
build.compile_rows([], sources)
print("done", flush=True)
"""


class _Compile:
    def __init__(self, root, cache, home, policy, count=9):
        root.mkdir(parents=True, exist_ok=True)
        env = dict(os.environ)
        env.pop("BUILD_RECOMPILE_ONLY", None)
        self.process = subprocess.Popen(
            [sys.executable, "-u", "-c", _CHILD,
             str(Path(build.__file__).parent), str(root), str(cache), str(home),
             policy, str(count)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT, text=True, env=env)
        self.lines = queue.Queue()
        self.released = False
        def read_output():
            for line in self.process.stdout:
                self.lines.put(line.rstrip())
            self.lines.put(None)
        self.reader = threading.Thread(target=read_output, daemon=True)
        self.reader.start()

    def line(self):
        try:
            line = self.lines.get(timeout=10)
        except queue.Empty:
            pytest.fail("compile child did not report acquisition or contention")
        assert line is not None, "compile child exited before reporting its lock"
        return line

    def release(self):
        if not self.released and self.process.poll() is None:
            self.process.stdin.write("release\n")
            self.process.stdin.flush()
            self.released = True

    def finish(self):
        self.release()
        assert self.process.wait(timeout=10) == 0
        assert self.line() == "done"

    def close(self):
        try:
            self.release()
            self.process.wait(timeout=10)
        except (BrokenPipeError, OSError, subprocess.TimeoutExpired):
            self.process.kill()
            self.process.wait(timeout=10)
        finally:
            self.reader.join(timeout=2)
            self.process.stdin.close()
            self.process.stdout.close()


@pytest.mark.parametrize("policy,shared_cache,independent", [
    ("nt", False, True),
    ("nt", True, False),
    ("posix", False, False),
])
def test_full_compile_scope(tmp_path, policy, shared_cache, independent):
    first_cache = tmp_path / "cache-a"
    second_cache = first_cache if shared_cache else tmp_path / "cache-b"
    first = _Compile(tmp_path / "seat-a", first_cache, tmp_path / "home", policy)
    second = None
    try:
        assert first.line() == "acquired"
        second = _Compile(tmp_path / "seat-b", second_cache, tmp_path / "home", policy)
        line = second.line()
        if independent:
            # Both compile callbacks hold their locks simultaneously.
            assert line == "acquired"
            second.finish()
            first.finish()
        else:
            assert line.startswith("waiting for build lock")
            assert second.process.poll() is None
            first.finish()
            assert second.line() == "acquired"
            second.finish()
    finally:
        first.close()
        if second is not None:
            second.close()


def test_small_verifies_do_not_wait_for_a_full_build(tmp_path):
    cache, home = tmp_path / "cache", tmp_path / "home"
    full = _Compile(tmp_path / "full", cache, home, "nt")
    small = None
    try:
        assert full.line() == "acquired"
        small = _Compile(tmp_path / "small", cache, home, "nt", count=8)
        assert small.line() == "acquired"
        small.finish()
        full.finish()
    finally:
        full.close()
        if small is not None:
            small.close()


def test_native_scope_resolves_cache_aliases(tmp_path, monkeypatch):
    from types import SimpleNamespace
    native = SimpleNamespace(**vars(os))
    native.name = "nt"
    monkeypatch.setattr(build, "os", native)
    cache = tmp_path / "cache"
    cache.mkdir()
    alias_parent = tmp_path / "alias-parent"
    alias_parent.mkdir()
    monkeypatch.setattr(build, "BUILD_DIR", alias_parent / ".." / "cache")
    assert build._full_compile_lock_path() == cache.resolve() / ".compile.lock"
