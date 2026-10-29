#!/usr/bin/env python3
"""Content-addressed memo for the work picker (tools/next_work.py), shared by every
worktree of a clone.

A pick rebuilds the same queues from the same inputs on every seat: the ledger parse,
check_csv, the TU map, the consolidation queue. memo() computes a value once per input
state and stores it under repair_queue.cache_dir() (<git common dir>/bfme-picker-cache),
so a second pick on the same commit -- in this worktree or another one of the clone --
reads it back.

The key of a memo is the TREE STATE plus the caller's own key parts:

  * HEAD's commit, every submodule's checked-out commit, and every path `git status`
    reports (tracked changes and untracked, non-ignored files) with a digest of its
    content: a pure function of the tracked tree as the worktree has it;
  * the REPAIR_* environment (repair_queue's input overrides) and BFME_PICKER_CACHE_SALT
    (a benchmark's stand-in for a new commit: it also re-keys stamped(), not the
    content-keyed keyed() and FileMemo, which survive a new commit).

Inputs git does not track (build/ outputs, ignored reports, the shared picker cache's own
files) are not in the key. While a value is computed every file it opens, lists or stats
outside the tracked tree is recorded, and the entry stores each one's state (content
digest, or kind and size for a probe that only stat()ed it, or missing); a stored entry
is served only while every recorded state still holds. A builder's inputs are found by
watching it read them, so a new input cannot be forgotten in a hand-written key list.

What is never cached: anything read from the network (claims) or the clock. A builder
that consults either must be split so only the pure part is memoised.

    import picker_cache
    items, note = picker_cache.memo("tier-stubs", repair_queue.stub_items)

BFME_PICKER_CACHE=off disables every memo (computes, stores nothing).
"""
import functools
import hashlib
import json
import os
import posixpath
import subprocess
import sys
import threading
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
VERSION = 1          # bump when an entry's shape or the key's meaning changes

_STATE = threading.local()
_PREFIXES = tuple(os.path.normcase(os.path.abspath(p)) + os.sep
                  for p in {sys.prefix, sys.base_prefix, sys.exec_prefix} if p)


def enabled():
    """False with BFME_PICKER_CACHE=off, and inside a pytest process unless a test names its
    own BFME_PICKER_CACHE directory: fixture trees never read or fill the clone's cache. (A
    picker a test runs as a subprocess on the real tree uses it like any seat.)"""
    setting = os.environ.get("BFME_PICKER_CACHE", "")
    if setting == "off":
        return False
    return bool(setting) or "pytest" not in sys.modules


def _git(*args, root=ROOT):
    got = subprocess.run(["git", *args], cwd=root, capture_output=True)
    return got.stdout if got.returncode == 0 else None


def cache_dir(root=str(ROOT)):
    """repair_queue.cache_dir() without importing it: BFME_PICKER_CACHE (a path), else
    <git common dir>/bfme-picker-cache."""
    if os.environ.get("BFME_PICKER_CACHE") not in (None, "", "off"):
        return Path(os.environ["BFME_PICKER_CACHE"])
    return _common_cache_dir(str(root))


@functools.lru_cache(maxsize=4)
def _common_cache_dir(root):
    common = (_git("rev-parse", "--path-format=absolute", "--git-common-dir", root=root) or b"").decode().strip()
    return Path(common or Path(root) / ".git") / "bfme-picker-cache"


def reset():
    """Forget every per-process snapshot (tree state, blobs, parsed ledgers): for tests that
    change a tree between calls."""
    _TREE.clear()
    _DIRTY.clear()
    _BLOBS.clear()
    _ROWS.clear()
    tracked.cache_clear()
    _common_cache_dir.cache_clear()


def file_digest(path):
    """sha256 of a file's bytes; None when it cannot be read."""
    h = hashlib.sha256()
    try:
        with open(path, "rb") as handle:
            for block in iter(lambda: handle.read(1 << 20), b""):
                h.update(block)
    except OSError:
        return None
    return h.hexdigest()


def submodules(root=ROOT):
    out = _git("config", "-f", ".gitmodules", "--get-regexp", r"\.path$", root=root) or b""
    return sorted(line.split(" ", 1)[1].strip() for line in out.decode().splitlines() if " " in line)


def _porcelain(status):
    """[(code, path)] from `git status --porcelain -z`; a rename's source is a second field."""
    fields, out, i = status.split("\0"), [], 0
    while i < len(fields):
        entry = fields[i]
        i += 1
        if len(entry) < 4:
            continue
        out.append((entry[:2], entry[3:]))
        if "R" in entry[:2] or "C" in entry[:2]:
            if i < len(fields) and fields[i]:
                out.append((entry[:2], fields[i]))
            i += 1
    return out


_TREE = {}
_DIRTY = {}             # root -> paths `git status` reported when tree_state ran


def tree_state(root=ROOT):
    """A digest of the worktree as git sees it (module docstring), or None when git cannot
    say. Computed once per process."""
    root = str(root)
    if root in _TREE:
        return _TREE[root]
    head = _git("rev-parse", "HEAD", root=root)
    status = _git("status", "--porcelain=v1", "-z", "--untracked-files=all", "--ignore-submodules=all",
                  root=root)
    if head is None or status is None:
        _TREE[root] = None
        return None
    parts = [f"head {head.decode().strip()}"]
    for path in submodules(root):
        sub = _git("-C", path, "rev-parse", "HEAD", root=root)
        parts.append(f"sub {path} {sub.decode().strip() if sub else 'absent'}")
    entries = sorted(_porcelain(status.decode("utf-8", "surrogateescape")))
    _DIRTY[root] = {path for _, path in entries}
    for code, path in entries:
        full = Path(root) / path
        parts.append(f"{code} {path} {'dir' if full.is_dir() else file_digest(full)}")
    _TREE[root] = hashlib.sha256("\n".join(parts).encode("utf-8", "surrogateescape")).hexdigest()
    return _TREE[root]


@functools.lru_cache(maxsize=4)
def tracked(root=str(ROOT)):
    """Lower-cased tracked paths (and their directories) of the superproject, and the
    submodule paths, lower-cased: what the tree state already covers."""
    out = (_git("ls-files", "-z", root=root) or b"").decode("utf-8", "surrogateescape")
    files = {p.lower() for p in out.split("\0") if p}
    dirs = {posixpath.dirname(p) for p in files}
    while dirs:
        more = {posixpath.dirname(d) for d in dirs} - dirs
        files |= dirs
        dirs = {d for d in more if d}
    return frozenset(files), tuple(s.lower() + "/" for s in submodules(root))


def _classify(path, root):
    """('root', rel) or ('abs', path) for an input outside the tracked tree, else None."""
    try:
        full = os.path.normcase(os.path.abspath(os.fspath(path)))
    except (TypeError, ValueError):
        return None
    if isinstance(full, bytes):
        full = os.fsdecode(full)
    if full.startswith(_PREFIXES) or "__pycache__" in full or full.endswith((".pyc", ".pyo")):
        return None
    memo_dir = os.path.normcase(os.path.abspath(cache_dir(str(root)) / "memo")) + os.sep
    if full.startswith(memo_dir):            # a nested memo's entry: its own reads are propagated
        return None
    base = os.path.normcase(os.path.abspath(root))
    if full == base or full.startswith(base + os.sep):
        rel = full[len(base) + 1:].replace(os.sep, "/") if full != base else ""
        files, subs = tracked(str(root))
        low = rel.lower()
        if not rel or low in files or low.startswith(subs) or low.startswith(".git/") or low == ".git":
            return None
        return ("root", rel)
    return ("abs", full)


def _resolve(where, path, root):
    return Path(root) / path if where == "root" else Path(path)


def _observe(how, full):
    """The state of one recorded input: how it was read decides what is compared."""
    if how == "list":
        try:
            return sorted(os.listdir(full))
        except OSError:
            return None
    if how == "read":
        return "dir" if os.path.isdir(full) else file_digest(full)
    try:                                     # "stat": kind and size, never the mtime
        st = os.stat(full)
    except OSError:
        return None
    return ["dir"] if os.path.isdir(full) else ["file", st.st_size]


class _Recorder:
    def __init__(self):
        self.seen = {}                       # raw path -> strongest use ("read" > "list" > "stat")

    def note(self, how, path):
        rank = {"stat": 0, "list": 1, "read": 2}
        old = self.seen.get(path)
        if old is None or rank[how] > rank[old]:
            self.seen[path] = how


def _active():
    return getattr(_STATE, "recorders", None) or ()


def _audit(event, args):
    recorders = _active()
    if not recorders:
        return
    if event == "open":
        path, mode, flags = (tuple(args) + (None, None, None))[:3]
        if isinstance(path, int):
            return
        if isinstance(mode, str):
            if not ("r" in mode or "+" in mode):
                return
        elif isinstance(flags, int) and flags & (os.O_WRONLY | os.O_RDWR) == os.O_WRONLY:
            return
        how = "read"
    elif event in ("os.listdir", "os.scandir"):
        path, how = (args[0] if args else "."), "list"
        if isinstance(path, int):
            return
    else:
        return
    for rec in recorders:
        rec.note(how, path)


_HOOKED = []
_INSTALL = threading.Lock()


def _install():
    """Once per process: the audit hook (opens, listings) and the stat probes. Both record
    only into the calling thread's active recorders, so other threads pay one attribute
    read per call."""
    with _INSTALL:
        if not _HOOKED:
            _install_locked()


def _install_locked():
    sys.addaudithook(_audit)
    for mod, name in ((os, "stat"), (os, "lstat"), (os.path, "exists"), (os.path, "isfile"),
                      (os.path, "isdir"), (os.path, "lexists"), (os.path, "getsize"), (os.path, "getmtime")):
        fn = getattr(mod, name, None)
        if fn is not None and not hasattr(fn, "_picker_cache_original"):
            setattr(mod, name, _wrap(fn))
    _HOOKED.append(True)


def _wrap(fn):
    @functools.wraps(fn)
    def probe(path, *args, **kwargs):
        recorders = _active()
        if recorders and not isinstance(path, int):
            for rec in recorders:
                rec.note("stat", path)
        return fn(path, *args, **kwargs)
    probe._picker_cache_original = fn
    return probe


def _key(kind, key, root):
    env = {k: v for k, v in os.environ.items() if k.startswith("REPAIR_") or k == "BFME_PICKER_CACHE_SALT"}
    blob = json.dumps([VERSION, kind, tree_state(root), key, env], sort_keys=True, default=str)
    return hashlib.sha256(blob.encode()).hexdigest()


def _entry_path(kind, digest, root):
    safe = "".join(c if c.isalnum() or c in "-_" else "_" for c in kind)
    return cache_dir(str(root)) / "memo" / safe / f"{digest}.json"


def _valid(entry, root):
    for where, path, how, state in entry.get("reads", ()):
        if _observe(how, _resolve(where, path, root)) != state:
            return False
    return True


KEEP = 24              # entries kept per kind: a commit's entries are dead once master moves on


def _write(path, value):
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        tmp = path.with_name(f"{path.name}.{os.getpid()}.{threading.get_ident()}.tmp")
        tmp.write_text(json.dumps(value, sort_keys=True), encoding="utf-8")
        os.replace(tmp, path)
    except OSError:
        return
    _prune(path.parent)


def _prune(directory, keep=None):
    """Delete all but the KEEP newest entries of one kind (and temporaries older than an hour)."""
    import time
    try:
        entries = [(e.stat().st_mtime, e.path) for e in os.scandir(directory) if e.is_file()]
    except OSError:
        return
    done = [(m, p) for m, p in entries if p.endswith(".json")]
    stale = [p for m, p in entries if p.endswith(".tmp") and time.time() - m > 3600]
    for _, p in sorted(done, reverse=True)[KEEP if keep is None else keep:]:
        stale.append(p)
    for p in stale:
        try:
            os.remove(p)
        except OSError:
            pass


STATS = {"hit": [], "miss": []}


def peek(kind, key=None, root=ROOT):
    """(True, value) when memo(kind, ..., key) would be served from the cache now, else
    (False, None); computes nothing."""
    root = str(root)
    if not enabled() or tree_state(root) is None:
        return False, None
    try:
        entry = json.loads(_entry_path(kind, _key(kind, key, root), root).read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return False, None
    if entry.get("version") == VERSION and _valid(entry, root):
        STATS["hit"].append(kind)
        return True, entry["value"]
    return False, None


def put(kind, value, key=None, root=ROOT):
    """Store VALUE as memo(kind, ..., key)'s for this tree state, for a value computed where
    nothing untracked could be recorded (a subprocess reading only tracked files)."""
    root = str(root)
    if enabled() and tree_state(root) is not None:
        _write(_entry_path(kind, _key(kind, key, root), root),
               {"version": VERSION, "kind": kind, "reads": [], "value": value})
        STATS["miss"].append(kind)


def memo(kind, compute, key=None, root=ROOT, also=()):
    """compute()'s value for this tree state, KEY and the recorded untracked inputs: read
    from the shared cache when an entry for them exists, else computed and stored. The
    value must survive JSON (a tuple comes back as a list: callers re-tuple). ALSO names
    untracked inputs to record even if compute never touches them (an optional file whose
    absence it decides by other means)."""
    root = str(root)
    if not enabled() or tree_state(root) is None:
        return compute()
    _install()
    digest = _key(kind, key, root)
    path = _entry_path(kind, digest, root)
    try:
        entry = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        entry = None
    if entry and entry.get("version") == VERSION and _valid(entry, root):
        for rec in _active():                # an enclosing memo depends on what this one read
            for where, p, how, _ in entry.get("reads", ()):
                rec.note(how, str(_resolve(where, p, root)))
        STATS["hit"].append(kind)
        return entry["value"]
    rec = _Recorder()
    stack = list(_active())
    _STATE.recorders = stack + [rec]
    try:
        value = compute()
    finally:
        _STATE.recorders = stack
    for extra in also:
        rec.note("stat", extra)
    reads = {}
    for raw, how in rec.seen.items():
        place = _classify(raw, root)
        if place and (place not in reads or how == "read" or (how == "list" and reads[place] == "stat")):
            reads[place] = how
    entry = {"version": VERSION, "kind": kind,
             "reads": sorted([where, p, how, _observe(how, _resolve(where, p, root))]
                             for (where, p), how in reads.items()),
             "value": value}
    stored = json.loads(json.dumps(entry["value"], sort_keys=True))
    _write(path, entry)
    STATS["miss"].append(kind)
    return stored


def memo_pair(kind, compute, **kwargs):
    """memo() of a builder returning (items, note), re-tupled."""
    items, note = memo(kind, lambda: list(compute()), **kwargs)
    return items, note


def stamped(path, parse, kind, extra=()):
    """parse(path) once per content of PATH (and of EXTRA files, e.g. the parser's own
    modules), shared across worktrees: for derived indexes of one tracked file, without
    the tree-state key."""
    if not enabled():
        return parse(path)
    parts = [file_digest(path)] + [file_digest(p) for p in extra]
    if None in parts:
        return parse(path)
    salt = os.environ.get("BFME_PICKER_CACHE_SALT", "")    # a benchmark's stand-in for a new ledger
    digest = hashlib.sha256(json.dumps([VERSION, kind, parts, salt]).encode()).hexdigest()
    entry_path = _entry_path(kind, digest, str(ROOT))
    try:
        return json.loads(entry_path.read_text(encoding="utf-8"))["value"]
    except (OSError, ValueError, KeyError, TypeError):
        pass
    value = parse(path)
    _write(entry_path, {"version": VERSION, "kind": kind, "value": value})
    return json.loads(json.dumps(value, sort_keys=True))


_ROWS = {}


def ledger_rows(path=None):
    """reverse/functions.csv (or PATH) as csv.DictReader rows, parsed once per process per
    (size, mtime) of the file: every picker module reads the same 30 MB ledger, and each
    parsed it again. The rows are SHARED: a caller must not mutate them. [] when the file
    is absent."""
    path = Path(path or ROOT / "reverse" / "functions.csv")
    try:
        st = path.stat()
    except OSError:
        return []
    key = os.path.normcase(str(path.resolve()))
    stamp = (st.st_size, st.st_mtime_ns)
    hit = _ROWS.get(key)
    if hit and hit[0] == stamp:
        return hit[1]
    import csv
    with path.open(encoding="utf-8", errors="replace", newline="") as handle:
        rows = list(csv.DictReader(handle))
    _ROWS[key] = (stamp, rows)
    return rows


def keyed(kind, key, compute):
    """compute() once per KEY (JSON-able content identifiers the caller vouches for, e.g. a
    git tree id and the computing modules' digests), shared across worktrees. Nothing is
    recorded: use it only where KEY names every input."""
    if not enabled():
        return compute()
    digest = hashlib.sha256(json.dumps([VERSION, kind, key], sort_keys=True).encode()).hexdigest()
    path = _entry_path(kind, digest, str(ROOT))
    try:
        return json.loads(path.read_text(encoding="utf-8"))["value"]
    except (OSError, ValueError, KeyError, TypeError):
        pass
    value = compute()
    _write(path, {"version": VERSION, "kind": kind, "value": value})
    return json.loads(json.dumps(value, sort_keys=True))


# Set by a process that reads the tree and never writes it (tools/next_work.py): only then
# may a tracked file's content be named by its index blob without reading it (blob_key).
READ_ONLY = False
_BLOBS = {}


def blob_key(rel, root=ROOT):
    """'<blob id>:<eol config>' naming tracked file REL's content without reading it -- its
    index blob, when the tree state saw it clean, checked out under this clone's line-ending
    settings (core.autocrlf, core.eol; .gitattributes is tracked, so in the tree state) --
    or None: outside a READ_ONLY run, or for an untracked, changed or missing file. The
    caller reads the file then."""
    root = str(root)
    if not READ_ONLY or not enabled() or tree_state(root) is None:
        return None
    if root not in _BLOBS:
        out = (_git("ls-files", "-s", "-z", root=root) or b"").decode("utf-8", "surrogateescape")
        blobs = {}
        for entry in out.split("\0"):
            meta, _, path = entry.partition("\t")
            parts = meta.split()
            if path and len(parts) == 3 and parts[2] == "0":
                blobs[path] = parts[1]
        eol = ",".join((_git("config", "--get", name, root=root) or b"").decode().strip()
                       for name in ("core.autocrlf", "core.eol"))
        _BLOBS[root] = (blobs, eol)
    blobs, eol = _BLOBS[root]
    rel = str(rel).replace("\\", "/")
    blob = blobs.get(rel)
    if blob is None or rel in _DIRTY.get(root, ()):
        return None
    return f"{blob}:{eol}"


class FileMemo:
    """{content key: value} of one per-file function, one JSON file per version of the code
    computing it (CODE: its modules' paths), shared across worktrees and merged on save()
    (saved at exit). Keys are blob_key()s, or 'sha1:<digest>' of text the caller read."""

    def __init__(self, kind, code):
        self.kind = kind
        self.code = [str(c) for c in code]
        self.lock = threading.RLock()
        self.data, self.new, self.path = None, {}, None

    def _open(self):
        if self.data is not None:
            return
        digest = hashlib.sha256(json.dumps([VERSION, self.kind] + [file_digest(c) for c in self.code])
                                .encode()).hexdigest()
        self.path = _entry_path(self.kind, digest, str(ROOT))
        try:
            self.data = json.loads(self.path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            self.data = {}
        import atexit
        atexit.register(self.save)

    def get(self, key, compute):
        """compute()'s value for content KEY (None: compute, never stored)."""
        if key is None or not enabled():
            return compute()
        with self.lock:
            self._open()
            if key in self.data:
                return self.data[key]
        value = json.loads(json.dumps(compute()))
        with self.lock:
            self.data[key] = self.new[key] = value
        return value

    def save(self):
        with self.lock:
            if not self.new or self.path is None:
                return
            try:
                merged = json.loads(self.path.read_text(encoding="utf-8"))
            except (OSError, ValueError):
                merged = {}
            merged.update(self.new)
            _write(self.path, merged)
            self.new = {}


def text_key(text):
    return "sha1:" + hashlib.sha1(text.encode("utf-8", "surrogateescape")).hexdigest()
