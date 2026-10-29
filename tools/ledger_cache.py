#!/usr/bin/env python3
"""Content-addressed memo for the hooks' ledger reads.

WHY. Every pre-push check read reverse/functions.csv (~99,000 rows) itself,
usually at both the base and the pushed commit: flag_delta_sources,
delta_sources, pin_admission and check_csv each spent seconds in `git show` and
CSV parsing of the same blobs, on every push, although the base is master's tip
(read by every push that clone made since master last moved) and pre-commit
had just read the pushed commit's blobs.

WHAT. memo(kind, key, compute, code) returns compute() for a key made only of
git object ids (blobs or trees, which name their content) and the hash of the
code that computes it, storing the result in the git common directory
(bfme-ledger-cache/). A result is a pure function of that content and code, so
reusing it changes nothing a check concludes; a different blob, tree or tool
version is a different key. Only results are stored, never verdicts that read
anything outside the key. The newest KEEP entries per kind are kept.

  python3 tools/ledger_cache.py clear      # drop every entry
"""
import hashlib
import os
import pickle
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
KEEP = 24
VERSION = 1
_CODE = {}


def folder():
    out = subprocess.run(["git", "-C", str(ROOT), "rev-parse", "--git-common-dir"], capture_output=True,
                         text=True)
    if out.returncode:
        return None
    return (ROOT / out.stdout.strip()).resolve() / "bfme-ledger-cache"


def code_hash(*paths):
    """The hash of the files whose code computes a memoised result."""
    key = tuple(str(p) for p in paths)
    if key not in _CODE:
        digest = hashlib.sha256(f"v{VERSION}".encode())
        for path in paths:
            digest.update(Path(path).read_bytes())
        _CODE[key] = digest.hexdigest()[:16]
    return _CODE[key]


def object_ids(rev, paths):
    """{path: object id} at `rev` for the `paths` that exist there (one ls-tree)."""
    out = subprocess.run(["git", "-C", str(ROOT), "ls-tree", "-z", rev, "--", *paths], capture_output=True)
    if out.returncode:
        raise RuntimeError(f"git ls-tree {rev} failed: {out.stderr.decode(errors='replace').strip()}")
    found = {}
    for entry in out.stdout.split(b"\0"):
        if b"\t" in entry:
            meta, path = entry.split(b"\t", 1)
            found[path.decode("utf-8")] = meta.split()[2].decode("ascii")
    return found


def memo(kind, key, compute, code):
    """compute(), memoised under (kind, key, code). `key` must be made only of git
    object ids; `code` is code_hash() of the files that define compute."""
    where = folder()
    if where is None or not key:
        return compute()
    name = hashlib.sha256(f"{kind}\0{code}\0{key}".encode()).hexdigest()[:40]
    path = where / f"{kind}-{name}.pickle"
    try:
        with path.open("rb") as handle:
            stored = pickle.load(handle)
        if isinstance(stored, tuple) and len(stored) == 2 and stored[0] == (kind, code, key):
            os.utime(path)
            return stored[1]
    except (OSError, EOFError, pickle.UnpicklingError, AttributeError, ValueError, TypeError):
        pass
    value = compute()
    try:
        where.mkdir(parents=True, exist_ok=True)
        temp = where / f".{path.name}.{os.getpid()}.tmp"
        with temp.open("wb") as handle:
            pickle.dump(((kind, code, key), value), handle, protocol=pickle.HIGHEST_PROTOCOL)
        os.replace(temp, path)
        entries = sorted(where.glob(f"{kind}-*.pickle"), key=lambda p: p.stat().st_mtime, reverse=True)
        for old in entries[KEEP:]:
            old.unlink(missing_ok=True)
    except OSError:
        pass
    return value


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    if argv[:1] == ["clear"]:
        where = folder()
        for path in (where.glob("*.pickle") if where and where.is_dir() else ()):
            path.unlink(missing_ok=True)
        return 0
    print(__doc__)
    return 2


if __name__ == "__main__":
    sys.exit(main())
