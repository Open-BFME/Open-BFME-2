#!/usr/bin/env python3
"""Shared body claims on origin: one ref per body, visible to every host.

WHY. The work queues run in separate writer clones and on other hosts. A
ledger row only records completed work, so it cannot keep two workers from
starting the same body. These short-lived refs coordinate work before either
worker commits.

HOW. A claim is the ref `refs/claims/0xRVA` on origin, pointing at a tiny
parentless commit whose message is JSON {owner, host, run, nonce, created,
expires}. Creating a ref that already exists is refused by a non-forced push,
so a claim is atomic across hosts with no server to run; `--atomic` makes a
multi-body claim all-or-nothing per attempt. An expired claim is taken over
with `--force-with-lease=<ref>:<old>` (compare-and-swap), and a release deletes
a ref only if it is still the owner's. Refs under refs/claims/ are not
branches: nobody checks them out or merges them, and nothing about pushing to
master changes.

busy_rvas() includes other seats' live claims, so every picker that asks it
(next_work, list_naked_candidates, bfme1_sweep, permute) skips claimed
bodies. `next_work.py --claim` and `list_naked_candidates.py --claim` claim
what they serve, settling this checkout's published landings first.

  python3 tools/claims.py list                 # live claims
  python3 tools/claims.py whoami               # this worker's owner string
  python3 tools/claims.py claim 0xRVA [...]    # claim for this worker (TTL 4 h)
  python3 tools/claims.py renew 0xRVA [...]    # extend your claims, keeping their lease
  python3 tools/claims.py release 0xRVA [...]  # release your own claims
  python3 tools/claims.py release --landed [SHA]
      # release claims whose rows are ON origin/master (SHA: rows it names by Claim-Lease trailer)
  python3 tools/claims.py gc [--max N] [--max-per-minute N] [--dry-run]
      # delete refs expired over an hour, fenced; any seat may run it

FAIL-CLOSED (Open-BFME-1 2026-09-29, ported 2026-10-09). claim() used to
return ([], []) when origin was unreachable, which a caller cannot tell from
"nothing to claim". Now:
  * claim() raises ClaimsUnavailable when origin cannot be fetched, and lists
    a body as claimed only when origin accepted the push. A body whose push
    failed is re-read from origin: held by another worker -> refused; not
    held by anyone -> refused AND listed in result.unconfirmed. The CLI
    exits 2. The exception carries what origin did show (.claimed, and
    .refused: bodies another worker holds); BFME2's pickers, bfme1_sweep and
    permute fall back to working unclaimed, but never on a body in .refused.
  * WORKER IDENTITY is BFME_CLAIM_OWNER, else `fleet:<BFME_RUN_ID>` inside a
    fleet run, else the agent a `work-<agent>` branch names, else
    `<user>@<host>/<checkout hash>` -- one per worktree, never one string
    shared by every seat on a host. See legacy_owner() for claims taken
    under the old `<user>@<host>` default.
  * FENCING: the claim commit's sha is the token (result.tokens). renew()
    (the heartbeat) and release(tokens=...) compare-and-swap on it, so a
    worker whose claim expired and was taken over learns it lost the body
    instead of overwriting or deleting the successor's claim. holds() asks
    origin whether a token is still current. The LEASE id survives renewals,
    and claim() on a live claim of the same owner keeps it too: a re-claim
    is a renewal, so a landing queued under the lease still settles.
  * add_match and add_match_batch no longer release on LOCAL verification:
    they queue the row in build/claims/landed_pending.jsonl and `release
    --landed` (settle(), which the pickers' --claim runs) releases a claim
    only once origin/master holds the row (its name, target_rva, size,
    source, status and member=/object-symbol= selectors; export_rva and other
    notes may change later), the same blobs of the files the verified compile
    read and the symbols.csv pins this checkout added (landing_evidence; a
    header origin adds that would shadow one of those files is not seen).
    Anything never settled -- an unproven landing, or a queue entry in an
    older evidence format -- expires with its TTL.
Readers (active(), busy_rvas()) still warn and serve without shared claims
when origin is unreachable: a picker only proposes, the claim decides.

SCOPES (BFME2). Work bigger than one body - reconciling a class onto a shared
header, draining a source file, re-homing split rows - is claimed by scope:

  python3 tools/claims.py claim file:Code/.../Unit.cpp   # refs/claims/file/<hash>
  python3 tools/claims.py claim class:RenderObjClass     # refs/claims/class/<name>
  (lease:<name>, refs/claims/lease/<name>, is a short-lived shared window:
  lease:landing is the landing window for full-gate pushes, tools/push_lease.py)

Same refs, same TTL, same compare-and-swap; `list` shows them with the path
or class. Mutual exclusion is by FILE (lock_keys): an RVA locks itself and its
row's file, a file itself. Header work holds class-only refs; class-to-file expansion
is retained for logical conflict checks without reserving hundreds of refs. acquire() -- what every picker and `claim` use -- pushes each
acquired lock key as its own create-only ref (sorted, all or nothing: a refusal
releases what it took), so two seats can never hold colliding work; no
timestamps are compared. Mixed old and new clients provide RVA-level exclusion
only; old clients do not participate in the file/class locking protocol. It then re-reads origin and yields to a live claim
of an older client that took no file locks. busy_rvas() skips every body in
a locked file; next_work's queues test busy_keys(). A file lock taken for a
body is a lock-only ref, released once no claim of its owner needs it
(release_orphans, run by settle and `release`). A claim next_work takes for
a debt item records its debt lines (`debt=` in the note), and settle()
releases it once origin/master no longer holds them (settle_scopes); any
other scope claim is released by hand after the push.

A host whose git proxy only accepts branch pushes keeps claims under a branch
namespace (`git config bfme.claimNamespace refs/heads/claims/`, or
BFME_CLAIM_NS); a fork can honour another repository's claims read-only with
`git config bfme.claimMirror upstream`.
Readers inspect both documented namespaces and refuse any live claim outside
their configured write namespace, including one with the same owner string.
The writes remain fenced within one namespace: different namespaces cannot
arbitrate simultaneous new claims atomically, so use one namespace per fleet.
"""
import argparse
import atexit
import hashlib
import io
import json
import locale
import math
import os
import random
import re
import socket
import subprocess
import sys
import tempfile
import threading
import time
import uuid
from contextlib import contextmanager
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def _git_env(cwd):
    """Use the explicit checkout, including from a hook or rebase exec."""
    env = dict(os.environ)
    # Git exports repository-local paths to hooks and rebase commands. They
    # override cwd/-C, so a submodule lookup can otherwise read the parent's
    # HEAD, index or object store. Keep configuration and authentication.
    for name in (
        "GIT_DIR", "GIT_WORK_TREE", "GIT_COMMON_DIR", "GIT_INDEX_FILE",
        "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
        "GIT_GRAFT_FILE", "GIT_SHALLOW_FILE", "GIT_PREFIX",
        "GIT_INTERNAL_SUPER_PREFIX", "GIT_IMPLICIT_WORK_TREE",
    ):
        env.pop(name, None)
    env["GIT_CEILING_DIRECTORIES"] = str(Path(cwd).resolve().parent)
    return env


# ---- per-repository configuration ------------------------------------------
# Everything that differs from Open-BFME-1's tools/claims.py by design is in
# this block or marked BFME2 below. Keep the rest identical to make syncing a
# plain diff.
LEDGER = "reverse/functions.csv"
# Where the byte gate writes each compiled source's object and dependency
# receipt (tools/build.py obj_path + _deps_sidecar); landing_evidence reads it.
RECEIPTS = "build/match"
# The callee pins verification resolves through; a landing's local additions
# must reach origin too (landing_evidence).
SYMBOLS = "reverse/symbols.csv"
# Where claims live on origin. A host whose git proxy only accepts branch
# pushes sets `git config bfme.claimNamespace refs/heads/claims/`.
NS = (os.environ.get("BFME_CLAIM_NS")
      or subprocess.run(["git", "-C", str(ROOT), "config", "--get", "bfme.claimNamespace"],
                        capture_output=True, text=True, env=_git_env(ROOT)).stdout.strip()
      or "refs/claims/")
READ_NAMESPACES = ("refs/claims/", "refs/heads/claims/")
# -----------------------------------------------------------------------------
# The fetched snapshot of origin's claim refs lives in a refs-only side
# repository, one per worktree (SEEN_REPO in the worktree's git dir), with the
# claim commits copied into its own object store. Two reasons:
#  * In this repository's refs, ~2,000 parentless claim commits were offered
#    as "have" tips by every ordinary `git fetch origin master`, and GitHub
#    answered with the whole history: 3.4 GB instead of 64 MiB for a seat 138
#    commits behind (2026-10-29). Nothing claims-related is in refs/ now.
#  * Per worktree, as refs/worktree/ was: a shared mirror let concurrent claim
#    fetches race their expected-old-SHA updates and report an available
#    origin as unreachable.
# refs/claims/ on origin still fences every worker against the same claim.
SEEN = "refs/claims-seen/"           # in the side repository; never pushed
SEEN_REPO = "claims-seen.git"
# Where older clients mirrored claims in this repository; deleted on sight.
LEGACY_SEEN = ("refs/worktree/claims-seen", "refs/worktree/claims-mirror-seen")
TTL_HOURS = float(os.environ.get("BFME_CLAIM_TTL_HOURS", "4"))
REMOTE = os.environ.get("BFME_CLAIM_REMOTE", "origin")
PENDING = Path("build") / "claims" / "landed_pending.jsonl"

# ---- pacing (Stage 2, item 4b) ----------------------------------------------
# Every seat pushes claims directly, so contention is met with full-jitter
# exponential backoff, and each host spaces its claim pushes through a shared
# GCRA bucket: a timestamp file under the machine-wide temp dir, one per
# claims remote, rewritten under a file lock.
BACKOFF_BASE = 0.5          # seconds; attempt n sleeps uniform(0, min(cap, base * 2**n))
BACKOFF_CAP = 30.0
PUSHES_PER_MINUTE = 60.0    # per host and remote; BFME_CLAIM_PUSHES_PER_MINUTE, 0 = unpaced
PUSH_BURST = 8              # pushes a quiet host may send back to back
HOST_DIR = Path(os.environ.get("BFME_CLAIM_HOST_DIR") or tempfile.gettempdir())
_HOST_THREADS = threading.Lock()


def _backoff(attempt, rng=random):
    """Seconds to wait before retry `attempt` (0-based): full jitter, capped."""
    return rng.uniform(0, min(BACKOFF_CAP, BACKOFF_BASE * (2 ** attempt)))


@lru_cache(maxsize=8)
def _remote_tag(root):
    url = _git("remote", "get-url", REMOTE, cwd=root).stdout.strip() or REMOTE
    return hashlib.sha1(url.encode("utf-8")).hexdigest()[:12]


@contextmanager
def _host_file(name, root=None):
    """Yield the path of a per-host, per-remote state file, locked against every
    process and thread on this machine."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from portable_lock import lock, unlock
    HOST_DIR.mkdir(parents=True, exist_ok=True)
    path = HOST_DIR / f"bfme-claims-{name}-{_remote_tag(str(root or ROOT))}"
    with _HOST_THREADS, open(path.with_suffix(".lock"), "a+b") as handle:
        lock(handle, exclusive=True)
        try:
            yield path
        finally:
            unlock(handle)


def _read_stamp(path):
    try:
        stamp = float(path.read_text(encoding="utf-8"))
        return stamp if math.isfinite(stamp) else 0.0
    except (OSError, ValueError):
        return 0.0


def _pace(root=None):
    """Reserve this host's next claim-push slot and sleep until it; returns the wait."""
    rate = float(os.environ.get("BFME_CLAIM_PUSHES_PER_MINUTE", PUSHES_PER_MINUTE))
    if not math.isfinite(rate):
        raise ValueError("BFME_CLAIM_PUSHES_PER_MINUTE must be finite")
    if rate <= 0:
        return 0.0
    interval = 60.0 / rate
    with _host_file("pacer", root) as path:
        now = time.time()
        due = min(max(_read_stamp(path), now), now + 3600)   # a clock jump never stalls an hour
        wait = max(0.0, due - now - (PUSH_BURST - 1) * interval)
        path.write_text(repr(due + interval), encoding="utf-8")
    if wait:
        time.sleep(wait)
    return wait


class ClaimsUnavailable(RuntimeError):
    """Origin could not be reached or read back, so the claim is incomplete.
    `claimed` lists bodies origin accepted or may have accepted before the failure (the caller
    should release them or let them expire); `refused` lists bodies origin was
    seen to hold for another worker before it failed. A caller that falls
    back to working unclaimed must still leave every refused body alone
    (review 2026-10-09: the fallback attempted a donor whose body a peer
    held)."""

    def __init__(self, message, claimed=(), refused=(), reachable=False):
        super().__init__(message)
        self.claimed = list(claimed)
        self.refused = list(refused)
        self.unclean = bool(self.claimed)
        self.reachable = reachable


class ClaimResult(tuple):
    """(claimed, refused) -- still unpacks and compares like the old tuple --
    plus `tokens` {rva: claim sha} for fencing, `unconfirmed` (the part of
    refused whose push failed while nobody else held the body) and `worker`,
    the owner string written into each claim."""

    def __new__(cls, claimed, refused, tokens=None, unconfirmed=(), worker="", leases=None, prior=()):
        self = tuple.__new__(cls, (list(claimed), list(refused)))
        self.prior = set(prior)         # claimed keys this worker already held live (renewed)
        self.tokens = dict(tokens or {})
        # the LEASE id survives renewals (the token rotates every heartbeat),
        # so it is what a queued unit refers to; see lease_holder()
        self.leases = dict(leases or {})
        self.unconfirmed = list(unconfirmed)
        self.worker = worker
        return self

    @property
    def claimed(self):
        return self[0]

    @property
    def refused(self):
        return self[1]


def _text(data):
    """Decode git output as text mode did (locale encoding, universal newlines)."""
    if isinstance(data, str):  # a test's fake subprocess.run already decoded it
        return data
    return io.TextIOWrapper(io.BytesIO(data or b""), encoding=locale.getpreferredencoding(False),
                            errors="strict").read()


def _git(*args, cwd=None, input_text=None, timeout=60, git_dir=None):
    """git `args` in checkout `cwd`; `git_dir` runs it in the claim mirror instead."""
    cwd = cwd or ROOT
    hooks = Path(cwd) / ".githooks"
    # Run THIS checkout's hooks, not whatever core.hooksPath points at: a host
    # whose hooksPath names an older checkout would run a pre-push that tries
    # to verify a claim marker as if it were code. The hooks still run.
    extra = ["-c", f"core.hooksPath={hooks.as_posix()}"] if args[:1] == ("push",) and hooks.is_dir() else []
    # Never let git discover a repository ABOVE `cwd`: a fixture directory
    # inside a real checkout (pytest's basetemp under build/) otherwise
    # inherits that checkout's origin, and a "no remote" test created real
    # claims on Open-BFME-1 (review 2026-09-29). Every caller passes a
    # checkout root, so discovery may start there and nowhere else.
    env = _git_env(cwd)
    if git_dir:
        env["GIT_DIR"] = str(git_dir)
    if args[:1] == ("push",):
        _pace(cwd)
    reads = getattr(_pick_state, "git_reads", None)       # inside read_once(): see there
    key = (os.path.normcase(os.path.abspath(str(cwd))), git_dir, args, input_text)
    if reads is not None:
        if args[:1] not in _READ_ONLY_GIT:
            reads.clear()                                  # anything else may move a ref
        elif key in reads:
            return reads[key]
    try:
        # stdin as bytes: text mode turns each "\n" into "\r\n" on Windows, and git
        # reads `sha\r` from `fetch --stdin` as an invalid refspec (2026-10-30)
        raw = subprocess.run(["git", *extra, *args], cwd=cwd, capture_output=True,
                             input=None if input_text is None else input_text.encode("utf-8"),
                             timeout=timeout, env=env)
    except subprocess.TimeoutExpired as error:
        return subprocess.CompletedProcess(error.cmd, 124, "", f"timed out after {timeout}s")
    got = subprocess.CompletedProcess(raw.args, raw.returncode, _text(raw.stdout), _text(raw.stderr))
    if reads is not None and args[:1] in _READ_ONLY_GIT and got.returncode == 0:
        reads[key] = got
    return got


# Git commands that only read: within read_once() one answer serves every repeat.
_READ_ONLY_GIT = {("for-each-ref",), ("symbolic-ref",), ("config",), ("rev-parse",)}


@contextmanager
def read_once():
    """Within this scope (one thread) a read-only git command run twice with the same
    arguments returns the first answer; any other git command (a fetch, an update-ref)
    drops every remembered answer first. busy_keys reads each claim mirror and the owner
    several times over one fetch: each read once."""
    outer = getattr(_pick_state, "git_reads", None)
    if outer is None:
        _pick_state.git_reads = {}
    try:
        yield
    finally:
        if outer is None:
            del _pick_state.git_reads


def owner(root=None):
    """The worker that holds a claim. BFME_CLAIM_OWNER wins; a fleet run is
    `fleet:<BFME_RUN_ID>` (the owner fleet_run claims under, so a tool the
    seat runs acts as the same worker); a `work-<agent>` branch names its
    agent (BFME2); otherwise `<user>@<host>/<checkout>` with a short hash of
    the checkout path. The old `<user>@<host>` was shared by every seat on a
    host, so any seat could renew or release another's."""
    explicit, legacy = _explicit_owner(root)
    if explicit:
        return explicit
    top = _git("rev-parse", "--show-toplevel", cwd=root).stdout.strip() or str(root or ROOT)
    tag = hashlib.sha1(os.path.normcase(os.path.abspath(top)).encode("utf-8")).hexdigest()[:8]
    return f"{legacy}/{tag}"


def _explicit_owner(root=None):
    """(explicit owner or None, `<user>@<host>`): the owner that BFME_CLAIM_OWNER,
    a fleet run or a work-<agent> branch names, and the host-wide default."""
    explicit = os.environ.get("BFME_CLAIM_OWNER")
    if explicit:
        return explicit, None
    run = os.environ.get("BFME_RUN_ID", "")
    if run:
        return f"fleet:{run}", None
    branch = _git("symbolic-ref", "--short", "-q", "HEAD", cwd=root).stdout.strip()
    if branch.startswith("work-") and len(branch) > 5:
        return branch[5:], None
    name = _git("config", "user.name", cwd=root).stdout.strip() or "unknown"
    return None, f"{name}@{socket.gethostname()}"


def legacy_owner(root=None):
    """The owner this checkout's claims carried before 2026-10-09, when the
    default was `<user>@<host>` with no checkout hash; None when an explicit
    owner applies (BFME_CLAIM_OWNER, a fleet run, a work-<agent> branch: those
    did not change).

    The upgrade otherwise strands such a claim: the per-checkout owner can
    neither renew nor release it (review 2026-10-09: 11 of 277 live claims).
    So renew(), release() and settlement accept a record whose owner is
    exactly this string as the default owner's own -- always fenced by the
    record's token, and renew() rewrites it under the per-checkout owner, so
    the alias retires as those claims are renewed, released or expire.
    claim() does NOT adopt it: a legacy claim is refused like a peer's.

    TRADEOFF: every checkout of one user on one host shares this string, as it
    did before the upgrade. Any of them can renew or release a legacy claim
    another of them took -- exactly what the old default already allowed, no
    more -- and never a claim taken under a per-checkout owner."""
    explicit, legacy = _explicit_owner(root)
    return None if explicit else legacy


def _names(who, root=None):
    """The owner strings whose claims are `who`'s own: `who`, plus the legacy
    `<user>@<host>` when `who` is this checkout's default owner."""
    names = {who}
    legacy = legacy_owner(root)
    if legacy and who == owner(root):
        names.add(legacy)
    return names


def _mirror(rva, sha, root=None):
    """Record in this worktree's mirror a claim write origin just accepted."""
    _mirror_many({rva: sha}, root)


def _mirror_many(writes, root=None):
    """Record in this worktree's mirror the claim writes origin just accepted,
    {key: sha, or None for a deletion}: one copy of their claim commits into the
    mirror and one update-ref transaction. Per key, a 20-key claim spent 8 of
    its 14 s in 20 local fetches and 20 update-refs (2026-10-30, 1,638 claims)."""
    if not writes:
        return
    _local_lock_records.cache_clear()
    side = _seen_repo(root)
    shas = sorted({sha for sha in writes.values() if sha})
    if shas:
        _adopt(shas, root, side)
    edits = "".join(f"update {SEEN + ref_of(key)[len(NS):]} {sha}\n" if sha
                    else f"delete {SEEN + ref_of(key)[len(NS):]}\n" for key, sha in writes.items())
    _git("update-ref", "--stdin", input_text=edits, cwd=root, git_dir=side)


def current_lease(rva, who=None, root=None):
    """The lease id of `who`'s claim on `rva` in the local mirror (no network),
    or None. queue_landed binds a landing to it."""
    entry = _read_local(root).get(key_of(rva))
    if not entry or entry[1].get("owner") not in _names(who or owner(root), root):
        return None
    return entry[1].get("lease") or entry[0]


def key_of(text):
    """A claim key: an int RVA, or a scope string 'file/<hash>' / 'class/<name>' /
    'lease/<name>' (BFME2; a short-lived shared window)."""
    if isinstance(text, int):
        return text
    if text.startswith(("file/", "class/", "lease/")):    # a key already (ClaimResult.tokens, renew)
        kind, rest = text.split("/", 1)
        if kind == "file" and len(rest) == 16 and all(c in "0123456789abcdef" for c in rest):
            return text
        if kind == "class" and key_of("class:" + rest.replace("%3A%3A", "::")) == text:
            return text
        if kind == "lease" and key_of("lease:" + rest) == text:
            return text
        raise ValueError(f"bad claim key {text!r}")
    if text.startswith("lease:"):
        name = text[6:]
        if not name or not all(c in "abcdefghijklmnopqrstuvwxyz0123456789-" for c in name):
            raise ValueError(f"bad lease name {name!r}")
        return "lease/" + name
    if text.startswith("file:"):
        path = text[5:].replace("\\", "/")
        return "file/" + hashlib.sha1(path.encode("utf-8")).hexdigest()[:16]
    if text.startswith("class:"):
        name = text[6:]
        if not all(part.replace("_", "a").isalnum() for part in name.split("::")):
            raise ValueError(f"bad class name {name!r}")
        # ':' is forbidden in Git refs; '%' cannot occur in an admitted class
        # identifier, so this keeps qualified scopes distinct without changing
        # existing unqualified claim keys. The record retains the readable name.
        return "class/" + name.replace("::", "%3A%3A")
    return int(text, 16)


def ref_of(rva):
    if isinstance(rva, str) and not rva.startswith(("0x", "0X")) and "/" in rva:
        return NS + rva                 # a scope key
    return f"{NS}0x{int(rva, 16) if isinstance(rva, str) else rva:08X}"


def label(key, info=None):
    if isinstance(key, int):
        return f"0x{key:08X}"
    return key.split("/", 1)[0] + ":" + ((info or {}).get("scope") or key.split("/", 1)[1])


def _order(key):
    """RVAs in address order, then scope keys by name."""
    return (0, key, "") if isinstance(key, int) else (1, 0, key)


def _ints(rvas):
    """Claim keys, sorted: RVAs (an int or hex text) and BFME2 scope keys."""
    return sorted({key_of(r) for r in rvas}, key=_order)


def _record(who, ttl_hours, note="", root=None, lease=None, since=None, scope="", lock=False, locks=()):
    """A parentless commit carrying the claim JSON; returns its sha, which is
    the claim's fencing token (the nonce makes every claim's sha unique).
    `lease` and its start time `since` are kept across renewals; a fresh
    claim starts a new lease. A scope claim records its path or class; a
    lock-only ref (acquire's file locks) records `lock`."""
    tree = _git("mktree", input_text="", cwd=root).stdout.strip()
    now = time.time()
    nonce = uuid.uuid4().hex
    fields = {"owner": who, "host": socket.gethostname(), "note": note,
              "run": os.environ.get("BFME_RUN_ID", ""), "nonce": nonce,
              "lease": lease or nonce, "since": int(since or now),
              "created": int(now), "expires": int(now + ttl_hours * 3600)}
    if locks:
        fields["locks"] = sorted(set(locks), key=_order)
    if scope:
        fields["scope"] = scope
    if lock:
        fields["lock"] = True
    body = json.dumps(fields, sort_keys=True)
    made = _git("-c", "user.name=claims", "-c", "user.email=claims@localhost",
                "commit-tree", tree, "-m", body, cwd=root)
    if made.returncode:
        raise RuntimeError(made.stderr.strip())
    return made.stdout.strip()


def configured(root=None):
    """Whether `root` is itself a checkout (not a directory inside one) with
    the claims remote configured. A fixture directory without one has nobody
    to coordinate with; a real checkout whose origin is unreachable is
    configured and fails closed."""
    top = _git("rev-parse", "--show-toplevel", cwd=root)
    same = os.path.normcase(os.path.realpath(top.stdout.strip() or "?")) == \
        os.path.normcase(os.path.realpath(str(root or ROOT)))
    return top.returncode == 0 and same and _git("remote", "get-url", REMOTE, cwd=root).returncode == 0


_pick_state = threading.local()


@contextmanager
def pick_snapshot():
    """Reuse one initial claims fetch during a pick; writes still get a fresh recheck."""
    outer = getattr(_pick_state, "fetched", None)
    if outer is None:
        _pick_state.fetched = set()
        active.cache_clear()
    try:
        yield
    finally:
        if outer is None:
            del _pick_state.fetched


def _invalidate_snapshot(root=None):
    fetched = getattr(_pick_state, "fetched", None)
    if fetched is not None:
        fetched.discard(str(Path(root or ROOT).resolve()))


def fetch(root=None):
    """Mirror claims, retrying ref-list/fetch races before reporting failure.

    A peer can delete an advertised ref before upload-pack reads it, including
    on GitHub. A reachable but moving snapshot must never enable offline work.
    Only cache a complete, successful fetch.
    """
    fetched = getattr(_pick_state, "fetched", None)
    key = str(Path(root or ROOT).resolve())
    if fetched is not None and key in fetched:
        return True
    # A claim marker has no submodule inputs. An inherited submodule.recurse
    # setting must not make this coordination operation fetch donor sources.
    # Frequent coordination reads must not run repository-wide maintenance;
    # normal Git operations and scheduled maintenance keep their own policy.
    for attempt in range(5):
        got = _snapshot(root, REMOTE, SEEN, timeout=120)
        if got.returncode == 0:
            break
        if attempt < 4:
            time.sleep(_backoff(attempt))
    if got.returncode and any(text in got.stderr.lower() for text in
                             ("not our ref", "couldn't find remote ref", "could not find remote ref",
                              "missing ref", "cannot lock ref", "unadvertised object")):
        raise ClaimsUnavailable("claims: origin reachable but claim refs kept changing; retry the pick",
                                reachable=True)
    if got.returncode == 0:
        _local_lock_records.cache_clear()
        if fetched is not None:
            fetched.add(key)
    return got.returncode == 0


def _namespace_mirrors(seen):
    """Keep writable refs separate from the read-only namespace snapshots."""
    yield NS, seen
    for index, namespace in enumerate(READ_NAMESPACES):
        if namespace != NS:
            # Outside `seen/`: _read_local must never interpret another
            # namespace's token as the lease on our configured write ref.
            yield namespace, f"{seen.rstrip('/')}-other/{index}/"


@lru_cache(maxsize=32)
def _seen_dir(top):
    """This worktree's claim mirror: a bare repository holding the mirror refs and
    their claim commits in its own object store (this repository's gc never sees
    them, so it must not own them). Made on first use, when any mirror refs older
    clients left in this repository are deleted. None outside a repository."""
    git_dir = _git("rev-parse", "--absolute-git-dir", cwd=top).stdout.strip()
    if not git_dir:
        return None
    side = Path(git_dir) / SEEN_REPO
    if not (side / "HEAD").is_file():
        made = _git("init", "-q", "--bare", "--template=", str(side), cwd=top)
        if made.returncode:
            raise ClaimsUnavailable(f"claims: cannot create the claim mirror {side}: {made.stderr.strip()}")
    legacy = [name for name in _git("for-each-ref", "--format=%(refname)", "refs/worktree/",
                                    cwd=top).stdout.split() if name.startswith(LEGACY_SEEN)]
    if legacy:
        _git("update-ref", "--stdin", input_text="".join(f"delete {name}\n" for name in legacy), cwd=top)
    return str(side)


def _seen_repo(root=None):
    return _seen_dir(str(Path(root or ROOT).resolve()))


def _missing(shas, root=None, git_dir=None):
    """The objects of `shas` that this repository (or `git_dir`) lacks, or the failed
    git result."""
    if not shas:
        return []
    checked = _git("cat-file", "--batch-check", input_text="".join(f"{sha}\n" for sha in shas),
                   cwd=root, git_dir=git_dir)
    if checked.returncode:
        return checked
    return [line.split()[0] for line in checked.stdout.splitlines() if line.endswith(" missing")]


@lru_cache(maxsize=32)
def _object_source(top):
    """This repository's git dir (shared by its worktrees), to copy claim commits from."""
    common = _git("rev-parse", "--git-common-dir", cwd=top).stdout.strip()
    return str((Path(top) / common).resolve()) if common else None


def _adopt(shas, root=None, side=None):
    """Copy claim commits from this repository into the mirror's object store,
    which must hold every object its refs name. A depth-1 local fetch copies
    each commit and its (empty) tree only: some claim commits have parents deep
    in master's history, which the mirror records as shallow and never holds.
    The git result of the copy (returncode 0 when nothing was missing)."""
    side = side or _seen_repo(root)
    missing = _missing(sorted(set(shas)), root, side)
    if not isinstance(missing, list):
        return missing
    if not missing:
        return subprocess.CompletedProcess(["git", "fetch"], 0, "", "")
    copied = _git("-c", "uploadpack.allowAnySHA1InWant=true", "fetch", "-q", "--depth=1", "--no-tags",
                  "--no-write-fetch-head", "--no-auto-maintenance", "--recurse-submodules=no", "--stdin",
                  _object_source(str(Path(root or ROOT).resolve())),
                  input_text="".join(f"{sha}\n" for sha in missing), cwd=root, git_dir=side)
    objects = Path(side) / "objects"
    if copied.returncode == 0 and (len(list((objects / "pack").glob("*.pack"))) >= 50
                                   or len(list((objects / "17").glob("*"))) > 27):
        # git's own gc.auto estimates (6,700 loose objects, 50 packs): the mirror's gc
        # consolidates them and in time drops claims no mirror ref names any more
        _git("-c", "gc.autoDetach=false", "gc", "--auto", "--quiet", cwd=root, git_dir=side)
    return copied


def mirror_sha(key, root=None, seen=SEEN):
    """The sha this worktree's claim mirror holds for `key`'s ref, or None."""
    got = _git("rev-parse", "-q", "--verify", seen + ref_of(key)[len(NS):], cwd=root, git_dir=_seen_repo(root))
    return got.stdout.strip() if got.returncode == 0 and got.stdout.strip() else None


def _snapshot(root, remote, seen, timeout):
    """Replace the mirror under `seen` with `remote`'s claim refs; the failed git
    result, or the listing's.

    `git ls-remote` lists the claim refs; only claim commits the mirror lacks
    and this repository lacks too are fetched, by sha, without writing a ref
    here. They are then copied into the mirror's own object store, and one
    update-ref transaction moves its refs. Works back to git 2.29 (fetch --stdin).
    With no new claim, a snapshot is one ls-remote and local reads."""
    side = _seen_repo(root)
    mirrors = list(_namespace_mirrors(seen))
    # A failed transaction (another process of this worktree moving the same
    # mirror refs) restarts the whole snapshot once: a retry from the old listing
    # would erase a claim write origin accepted meanwhile.
    for attempt in range(2):
        listed = _git("ls-remote", remote, *(f"{namespace}*" for namespace, _ in mirrors), cwd=root,
                      timeout=timeout)
        if listed.returncode:
            return listed
        want = {}
        for line in listed.stdout.splitlines():   # "<sha>\t<ref>"; patterns match ref tails, so filter
            sha, _, name = line.partition("\t")
            for namespace, mirror in mirrors:
                if name.startswith(namespace):
                    want[mirror + name[len(namespace):]] = sha
                    break
        shas = sorted(set(want.values()))
        lacking = _missing(shas, root, side)
        if not isinstance(lacking, list):
            return lacking
        absent = _missing(lacking, root)
        if not isinstance(absent, list):
            return absent
        if absent:
            got = _git("fetch", "-q", "--no-write-fetch-head", "--no-auto-maintenance", "--no-tags",
                       "--recurse-submodules=no", "--stdin", remote,
                       input_text="".join(f"{sha}\n" for sha in absent), cwd=root, timeout=timeout)
            if got.returncode:
                return got
        adopted = _adopt(lacking, root, side)
        if adopted.returncode:
            return adopted
        # Deletions go first, in their own transaction: git refuses one transaction
        # that deletes X and creates X/Y (or the reverse), a ref directory conflict
        # that left mirrors failing on every fetch.
        held = _git("for-each-ref", "--format=%(refname) %(objectname)", *(mirror for _, mirror in mirrors),
                    cwd=root, git_dir=side)
        if held.returncode:
            return held
        have = dict(line.split(" ", 1) for line in held.stdout.splitlines())
        deletes = [f"delete {name}\n" for name in sorted(have) if name not in want]
        updates = [f"update {name} {sha}\n" for name, sha in sorted(want.items()) if have.get(name) != sha]
        wrote = None
        for edits in (deletes, updates):
            if edits:
                wrote = _git("update-ref", "--stdin", input_text="".join(edits), cwd=root, git_dir=side)
                if wrote.returncode:
                    break
        if wrote is None or wrote.returncode == 0:
            return listed
    return wrote


def _read_visible(root=None, seen=SEEN, *, other_only=False):
    """Union of observed namespaces; only visibility, never a write lease.

    The latest expiry wins for display, so an expired marker cannot hide a
    live claim. With other_only, every returned key is outside our write
    namespace and must be refused regardless of its owner string.
    """
    visible = {}
    for namespace, mirror in _namespace_mirrors(seen):
        if other_only and namespace == NS:
            continue
        for key, entry in _read_local(root, mirror).items():
            previous = visible.get(key)
            latest = entry if previous is None or entry[1].get("expires", 0) > previous[1].get("expires", 0) else previous
            # Visibility must retain every live footprint even when two namespaces
            # use the same key with different persisted file sets.
            locks = {lock for candidate in (previous, entry) if candidate
                     and candidate[1].get("expires", 0) > time.time()
                     for lock in candidate[1].get("locks", ())}
            visible[key] = (latest[0], dict(latest[1], locks=sorted(locks, key=_order))) if locks else latest
    return visible


def _read_local(root=None, seen=SEEN):
    """{key: (sha, info)} from the local mirror: int RVAs and scope strings.
    Raises ClaimsUnavailable when the mirror cannot be read: a partial view could
    hide a live claim. Outside a repository there is no mirror and nothing to read."""
    side = _seen_repo(root)
    if side is None:
        return {}
    listed = _git("for-each-ref", "--format=%(refname)%09%(objectname)%09%(contents:subject)", seen,
                  cwd=root, git_dir=side)
    if listed.returncode:
        raise ClaimsUnavailable(f"claims: cannot read the claim mirror: {listed.stderr.strip()}")
    out = listed.stdout
    claims = {}
    for line in out.splitlines():
        name, sha, subject = (line.split("\t") + ["", ""])[:3]
        rest = name[len(seen):]
        try:
            info = json.loads(subject)
            rva = rest if rest.startswith(("file/", "class/", "lease/")) else int(rest, 16)
        except ValueError:
            continue
        # Two spellings of one address (e.g. a hand-made lowercase ref) must
        # not let a stale record hide a live one: keep the later expiry.
        if rva in claims and claims[rva][1].get("expires", 0) >= info.get("expires", 0):
            continue
        claims[rva] = (sha, info)
    return claims


def live(claims, now=None):
    now = now or time.time()
    return {rva: v for rva, v in claims.items() if v[1].get("expires", 0) > now}


def active(root=None):
    """{rva: info} of every unexpired claim on the origin of `root` (this
    checkout by default), fetched once per process per root. Empty (with a
    warning) when that origin cannot be reached: a fixture repository with no
    remote sees no claims, so a picker under test never inherits this
    checkout's live shared claims."""
    return dict(_active(str(Path(root).resolve()) if root else None))


@lru_cache(maxsize=8)
def _active(root):
    if not fetch(root):
        if getattr(_pick_state, "strict_fetch", False):
            raise ClaimsUnavailable("claims: cannot read the post-push claim snapshot")
        print("claims: could not fetch refs/claims/* from origin; serving without shared claims",
              file=sys.stderr)
        return {}
    return {rva: info for rva, (_, info) in live(_read_visible(root)).items()}


active.cache_clear = _active.cache_clear


# BFME2: a fork can also honour another repository's claims, read-only: with
# `git config bfme.claimMirror upstream`, bodies upstream's workers hold are
# skipped here too (their result arrives through the merge). Nothing is ever
# written to that remote.
MIRROR_SEEN = "refs/claims-mirror-seen/"  # in the side repository, like SEEN


def mirrored(root=None):
    """{rva: info} of live claims on the mirrored remote; {} if none is set."""
    return dict(_mirrored(str(Path(root or ROOT).resolve())))


@lru_cache(maxsize=8)
def _mirrored(root):
    remote = _git("config", "--get", "bfme.claimMirror", cwd=root).stdout.strip()
    if not remote:
        return {}
    got = _snapshot(root, remote, MIRROR_SEEN, timeout=15)
    if got.returncode:
        return {}
    return {rva: info for rva, (_, info) in live(_read_visible(root, MIRROR_SEEN)).items()
            if isinstance(rva, int)}


mirrored.cache_clear = _mirrored.cache_clear


# BFME2 scope locks: body edits reserve their source file atomically. Header work
# reserves class refs only, avoiding hundreds of long-lived file refs. Logical
# class-to-file expansion and a fresh post-push check make either kind yield to
# an intersecting claim. Older clients participate only in RVA-level exclusion.
# `?member@Scope@@<access>`: member functions (A-X) and static data members (0-2) only;
# a free function in a namespace (`?f@ns@@YAXXZ`) names no class.
MEMBER = re.compile(r"^\?(?:\?_?[0-9A-Z]|[A-Za-z_]\w*@)([A-Za-z_]\w*(?:@[A-Za-z_]\w*)*)@@[A-X012]")


def member_class(symbol):
    """The class ('Outer::Inner') a decorated member name belongs to, or None."""
    m = MEMBER.match(symbol or "")
    return "::".join(reversed(m[1].split("@"))) if m else None


def file_key(source):
    return key_of("file:" + source)


def class_key(name):
    try:
        return key_of("class:" + name) if name else None
    except ValueError:
        return None


def _ledger_stamp(root):
    try:
        st = (Path(root or ROOT) / LEDGER).stat()
        return (st.st_size, st.st_mtime_ns)
    except OSError:
        return None


def _scope_rows(path):
    """[[rva, file key, class key or None]] of the ledger's matched rows, in ledger order."""
    import picker_cache
    out, fkeys = [], {}
    for row in picker_cache.ledger_rows(path):
        if row.get("status") != "matched" or not (row.get("target_rva") or "").startswith("0x"):
            continue
        source = row["source"]
        if source not in fkeys:
            fkeys[source] = file_key(source)
        out.append([int(row["target_rva"], 16), fkeys[source], class_key(member_class(row["name"]))])
    return out


@lru_cache(maxsize=4)
def _scope_index(root, stamp):
    """(rva -> (file key, class key or None), file key -> {class keys},
    class key -> {file keys}) over the ledger's matched rows at `root`. The rows come
    from the shared picker cache, one entry per ledger content (tools/picker_cache.py)."""
    import picker_cache
    of_rva, classes, files = {}, {}, {}
    path = Path(root or ROOT) / LEDGER
    if stamp is None or not path.is_file():
        return of_rva, classes, files
    for rva, fkey, ckey in picker_cache.stamped(path, _scope_rows, "claims-scope", extra=[__file__]):
        of_rva[rva] = (fkey, ckey)
        if ckey:
            classes.setdefault(fkey, set()).add(ckey)
            files.setdefault(ckey, set()).add(fkey)
    return of_rva, classes, files


def scope_index(root=None):
    root = str(Path(root).resolve()) if root else None
    return _scope_index(root, _ledger_stamp(root))


@lru_cache(maxsize=8)
def _local_lock_records(root):
    return {k: info for k, (_, info) in live(_read_visible(root)).items()}


def lock_keys(keys, root=None, records=None):
    """The canonical lock keys of work occupying `keys` (claim keys): an RVA is itself
    and its ledger row's file, a class is itself and every file defining its members,
    a file or lease is itself. collide(a, b) is lock_keys(a) & lock_keys(b): symmetric."""
    records = records if records is not None else _local_lock_records(str(Path(root or ROOT).resolve()))
    return _lock_keys(keys, scope_index(root), records)


def lock_records(root=None):
    """The local lock records lock_keys reads when not given any: pass them to lock_keys when
    asking it of thousands of key sets (it resolves the root path each time otherwise)."""
    return _local_lock_records(str(Path(root or ROOT).resolve()))


def _lock_keys(keys, index, records):
    of_rva, _, files = index
    out = set()
    for key in keys:
        out.add(key)
        out.update(key_of(k) for k in records.get(key, {}).get("locks", ()))
        if isinstance(key, int):
            fkey = (of_rva.get(key) or (None,))[0]
            if fkey:
                out.add(fkey)
        elif key.startswith("class/"):
            out.update(files.get(key, ()))
    return out


def work_keys(rva=None, source=None, cls=None, root=None):
    """The claim keys one piece of work names: its RVA, its source file and the class
    it works on (lock_keys adds the RVA's file and the class's files)."""
    keys = set()
    if rva is not None:
        keys.add(rva)
    if source:
        keys.add(file_key(source))
    ckey = class_key(cls)
    if ckey:
        keys.add(ckey)
    return keys


def live_keys(root=None):
    """Every live claim key, all namespaces (RVA, file/, class/, lease/), the
    mirrored remote's RVAs included; empty with BFME_CLAIMS=off."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return set()
    return set(active(root)) | set(mirrored(root))


def _blocking_records(root=None, who=None):
    """Snapshots that block work; foreign namespaces never confer owner authority.

    Inspect each separately: a later own record must not hide a foreign holder
    or its persisted file locks at the same key.
    """
    active(root)  # fetch once per pick, or freshly when conflicts invalidated it
    names = _names(who or owner(root), root)
    for namespace, mirror in _namespace_mirrors(SEEN):
        yield {k: info for k, (_, info) in live(_read_local(root, mirror)).items()
               if namespace != NS or info.get("owner") not in names}
    yield mirrored(root)  # the upstream mirror is always read-only


def busy_keys(root=None):
    """The lock keys of every claim that this checkout cannot edit."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return set()
    with read_once():
        return {lock for records in _blocking_records(root)
                for lock in lock_keys(records, root, records=records)}


def busy_rvas(root=None):
    """Addresses a picker should skip (BFME2; Open-BFME-1 has
    eligibility.busy_rvas): every claimed RVA, and every body whose row lies in a
    locked file (a file claim, a class claim's files, another body's file). One
    fetch is cached per process."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return set()
    locks = busy_keys(root)
    of_rva, _, _ = scope_index(root)
    return {key for key in locks if isinstance(key, int)} | {
        rva for rva, (fkey, _) in of_rva.items() if fkey in locks}


def conflicts(mine, root=None, who=None):
    """{key: info} of live claims by OTHER owners whose lock keys meet those of work
    occupying `mine`. Read fresh (the cache is cleared first): acquire() asks after
    its push, which catches a claim of an older client that takes no file locks.
    Empty with BFME_CLAIMS=off."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return {}
    _invalidate_snapshot(root)
    active.cache_clear()
    strict = getattr(_pick_state, "strict_fetch", False)
    _pick_state.strict_fetch = True
    try:
        snapshots = list(_blocking_records(root, who))
    finally:
        _pick_state.strict_fetch = strict
    locks = lock_keys(mine, root)
    return {key: info for records in snapshots for key, info in records.items()
            if lock_keys({key}, root, records=records) & locks}


def acquire(targets, work=(), note="", who=None, root=None, ttl_hours=TTL_HOURS):
    """Claim one piece of work under mutual exclusion; returns a ClaimResult.

    `targets` are what the work is claimed as (RVAs, `file:`/`class:` scopes),
    `work` its other keys (next_work.claim_keys). Body edits atomically reserve
    their RVA and file refs; header reconciliation reserves class refs only.
    lock_keys expands both logical footprints for the fresh post-push check,
    so intersecting work yields without reserving every member file for hours. All or nothing: when any ref is refused, or a
    live claim of another owner still collides after the push (an older client's
    claim takes no file locks), every ref this call newly took is released and the
    result claims nothing and refuses the colliding keys. A ref this owner already
    held is kept. Raises ClaimsUnavailable as claim() does."""
    spelled = {key_of(t): t for t in targets}
    logical = set(spelled) | set(work)
    locks = lock_keys(logical, root)
    # Header reconciliation holds class refs only. Its file footprint remains in
    # lock_keys for the mandatory fresh post-push conflict check against body edits.
    class_work = any(isinstance(k, str) and k.startswith("class/") for k in spelled)
    if class_work:
        spelled = {k: v for k, v in spelled.items() if isinstance(k, str) and k.startswith("class/")}
        acquired_locks = set(spelled)
    else:
        acquired_locks = locks
    extra = sorted(acquired_locks - set(spelled), key=_order)
    kwargs = {"note": note, "atomic_only": True, "work_locks": locks}
    for name, value, default in (("who", who, None), ("root", root, None), ("ttl_hours", ttl_hours, TTL_HOURS)):
        if value != default:
            kwargs[name] = value
    if extra:
        kwargs["locks"] = extra
    try:
        result = claim([spelled[k] for k in sorted(spelled, key=_order)] + extra, **kwargs)
    except ClaimsUnavailable as error:
        # A lost reply can leave accepted refs even if the subsequent fetch fails.
        _rollback([k for k in error.claimed if k not in getattr(error, "prior", ())],
                  getattr(error, "tokens", {}), who, root, error.refused)
        error.claimed = [k for k in error.claimed if k in getattr(error, "prior", ())]
        error.unclean = bool(error.claimed)
        raise
    claimed, refused = list(result[0]), list(result[1])
    tokens = getattr(result, "tokens", {})
    if not refused and tokens:
        try:
            refused = sorted(conflicts(locks, root=root, who=who), key=_order)
        except ClaimsUnavailable as error:
            # Keep the fencing tokens if rollback itself cannot complete.
            _rollback([k for k in claimed if k not in result.prior], tokens, who, root)
            error.claimed = [k for k in claimed if k in result.prior]
            error.tokens = {k: tokens[k] for k in error.claimed}
            error.unclean = bool(error.claimed)
            raise
    if not refused:
        return result if isinstance(result, ClaimResult) else ClaimResult(claimed, [])
    fresh = [k for k in claimed if k not in set(getattr(result, "prior", ()))]
    _rollback(fresh, tokens, who, root, refused)
    return ClaimResult([], refused, unconfirmed=getattr(result, "unconfirmed", ()),
                       worker=getattr(result, "worker", ""))


def _rollback(fresh, tokens, who, root, refused=()):
    if not fresh:
        return
    try:
        done = set(release(fresh, who=who, root=root, tokens=tokens))
    except ClaimsUnavailable:
        done = set()  # the accepted tokens still allow a fenced direct rollback
    for key in fresh:
        if key in done or key not in tokens:
            continue
        ref = ref_of(key)
        expired = _record(who or owner(root), -1, "released", root) if NS.startswith("refs/heads/") else None
        spec = f"+{expired}:{ref}" if expired else f":{ref}"
        for attempt in range(5):
            if _git("push", "-q", f"--force-with-lease={ref}:{tokens[key]}", REMOTE, spec,
                    cwd=root, timeout=120).returncode == 0:
                _mirror(key, expired, root)
                done.add(key)
                break
            if attempt < 4:
                time.sleep(_backoff(attempt))
    _invalidate_snapshot(root)
    active.cache_clear()
    if len(done) != len(fresh):
        error = ClaimsUnavailable("claims: partial acquisition could not be rolled back; do not start another item",
                                  claimed=set(fresh) - done, refused=refused)
        error.tokens = {k: tokens[k] for k in error.claimed if k in tokens}
        raise error


def release_orphans(root=None, who=None):
    """Release this owner's lock-only refs (acquire's file locks) that none of its
    other live claims needs any more: the body landed and settled, or was released
    by hand. Returns the released keys; origin trouble releases nothing."""
    if not fetch(root):
        return []
    free = _orphan_locks(root, who)
    return release(list(free), who=who, root=root, tokens=free) if free else []


def _orphan_locks(root=None, who=None, gone=()):
    """{key: sha} of this owner's lock-only refs in the fetched snapshot that no
    other live claim of its needs once the keys in `gone` are deleted."""
    names = _names(who or owner(root), root)
    gone = set(gone)
    mine = {k: v for k, v in live(_read_local(root)).items()
            if v[1].get("owner") in names and k not in gone}
    needed = lock_keys({k for k, (_, info) in mine.items() if not info.get("lock")}, root,
                       records={k: info for k, (_, info) in mine.items()})
    return {k: sha for k, (sha, info) in mine.items() if info.get("lock") and k not in needed}


def release_work(keys, who=None, root=None, tokens=None, force=False):
    """release() `keys` and the file locks they leave unneeded, in one atomic push."""
    keys = _ints(keys)
    _invalidate_snapshot(root)
    if not fetch(root):
        print("claims: origin unreachable; releasing nothing (claims expire on their own)", file=sys.stderr)
        return []
    plan = _eligible(keys, who, root, tokens, force=force) if keys else {}
    holders = {who or owner(root)}
    if force:
        current = _read_local(root)
        holders.update(current[k][1].get("owner") for k in plan)
    for holder in holders:
        plan.update(_orphan_locks(root, holder, gone=plan))
    done = _drop(plan, who, root) if plan else []
    active.cache_clear()
    return done


def claim(rvas, who=None, ttl_hours=TTL_HOURS, note="", root=None, locks=(), atomic_only=False, work_locks=()):
    """Claim `rvas` on origin. Returns a ClaimResult (claimed, refused).

    Tries all-or-nothing first (--atomic); if that fails, claims the rest one
    by one, unless atomic_only (acquire) requires all-or-nothing. Free refs after a
    failed transaction are retried with jitter, at most four atomic attempts;
    reachable-origin failures are refused, never reported as offline. A live claim of ours is renewed and KEEPS its lease (and start
    time): a re-claim is how a worker extends a claim, and a fresh lease
    orphaned the landing queued under the old one (review 2026-10-09). An
    expired claim -- ours included -- is taken over by compare-and-swap under
    a new lease. A body counts as claimed only when origin accepted it. A
    body the mirrored remote holds is refused, and so is a legacy-owner claim
    (see legacy_owner). Raises ClaimsUnavailable when origin cannot be
    fetched; its .refused names the bodies origin
    showed another worker holding. `locks` (acquire's file locks) are written
    as lock-only refs, which release_orphans frees once no claim needs them; a
    ref this worker already holds as work stays work."""
    who = who or owner(root)
    scopes = {key_of(r): r[r.index(":") + 1:] for r in rvas if isinstance(r, str) and ":" in r}
    rvas = _ints(rvas)
    if not rvas:
        return ClaimResult([], [], worker=who)
    if not fetch(root):
        raise ClaimsUnavailable("claims: cannot fetch refs/claims/* from origin; nothing claimed")
    current = _read_local(root)
    now = time.time()
    held = {r for r in rvas if r in current and current[r][1].get("expires", 0) > now
            and current[r][1].get("owner") != who}
    held |= set(rvas) & set(live(_read_visible(root, other_only=True), now))
    upstream = mirrored(root)
    held |= {r for r in rvas if isinstance(r, int) and r in upstream}   # upstream is on it
    wanted = [r for r in rvas if r not in held]
    prior = {r for r in wanted if r in current and current[r][1].get("expires", 0) > now}
    locks = {key_of(k) for k in locks} - {r for r in prior if not current[r][1].get("lock")}
    if atomic_only and held:
        return ClaimResult([], sorted(held, key=_order), worker=who)
    fresh = uuid.uuid4().hex
    shas = {}

    def lease_of(rva):
        """(lease, since) the claim on `rva` is written under."""
        old = current.get(rva)
        if old and old[1].get("owner") == who and old[1].get("expires", 0) > now:
            return old[1].get("lease") or old[0], old[1].get("since") or old[1].get("created")
        return fresh, None

    def token(rva):
        # one claim commit per call, per scope (a scope record names its
        # scope) and per lease (a renewed claim keeps its own)
        scope = scopes.get(rva, "")
        lease, since = lease_of(rva)
        lock = rva in locks
        stored = set(current.get(rva, (None, {}))[1].get("locks", ())) | set(work_locks)
        cache_key = (scope, lease, lock, tuple(sorted(stored, key=_order)))
        if cache_key not in shas:
            shas[cache_key] = _record(who, ttl_hours, note, root, lease=lease, since=since,
                                               scope=scope, lock=lock, locks=stored)
        return shas[cache_key]

    def spec(rva):
        sha = token(rva)
        old = current.get(rva)
        return (f"--force-with-lease={ref_of(rva)}:{old[0]}" if old else None,
                f"{sha}:{ref_of(rva)}" if not old else f"+{sha}:{ref_of(rva)}")

    def push(batch, deletions=((), ())):
        """One atomic push per command-line-sized chunk: a merge scope of ~200 files
        and their rows overflowed Windows' command line in a single push (2026-10-28).
        The queued deletions ride in the first chunk. When a later chunk fails, an
        all-or-nothing claim takes back the fresh refs earlier chunks created."""
        extra = list(deletions[0]) + list(deletions[1])
        reserve = len(subprocess.list2cmdline(extra)) + 2 if extra else 0
        pushed = []
        for i, chunk in enumerate(list(_arg_batches(batch, lambda r: [a for a in spec(r) if a], reserve)) or [[]]):
            leases = [s[0] for s in map(spec, chunk) if s[0]] + (list(deletions[0]) if i == 0 else [])
            refspecs = [spec(r)[1] for r in chunk] + (list(deletions[1]) if i == 0 else [])
            if _git("push", "-q", "--atomic", *leases, REMOTE, *refspecs, cwd=root, timeout=120).returncode:
                fresh_refs = {r: token(r) for r in pushed if r not in current}
                if atomic_only and fresh_refs:
                    _drop(fresh_refs, who, root)
                return False
            pushed += chunk
            if len(batch) > len(chunk):     # mirrored now, so a rollback's fenced _drop sees them
                _mirror_many({r: token(r) for r in chunk}, root)
        return True

    # The releases settle(defer=True) queued ride in this push: one transaction
    # instead of one more push. A key this push writes is needed again, so its
    # deletion is dropped. If the combined push fails they go on their own.
    outbox, outbox_who, settled = _take_outbox(root, exclude=wanted) if wanted else ({}, None, ())
    claimed, failed = [], []
    with _guard_deletions(outbox, settled, root) as outbox:
        deletions = _deletion(outbox, outbox_who or who, root) if outbox else ((), (), None)
        accepted = bool(wanted) and push(wanted, deletions)
    if accepted:
        claimed = list(wanted)
        _mirror_many({key: deletions[2] for key in outbox}, root)
        _settled(root, settled, outbox)
        outbox = {}
    else:
        if atomic_only:
            failed = list(wanted)
        else:
            if wanted:
                time.sleep(_backoff(0))
            for rva in wanted:              # somebody raced us for part of the batch
                (claimed if push([rva]) else failed).append(rva)
    unconfirmed = []
    for attempt in range(4):
        if not failed:
            break
        # A failed push is either a lost race or network trouble; origin says which.
        _invalidate_snapshot(root)
        try:
            available = fetch(root)
        except ClaimsUnavailable as error:
            available = False
            reachable = error.reachable
        else:
            reachable = False
        if not available:
            active.cache_clear()
            # A failed reply may follow an accepted push. Retain every token
            # that might be on origin so acquire can fence its rollback.
            uncertain = set(claimed) | set(failed)
            error = ClaimsUnavailable("claims: push reply failed and origin cannot be re-read; .claimed tokens may remain",
                                      claimed=sorted(uncertain, key=_order), refused=sorted(held, key=_order),
                                      reachable=reachable)
            error.tokens = {r: token(r) for r in uncertain}
            error.prior = prior
            defer_release(outbox, root, outbox_who, settled)     # retried at exit
            raise error
        after = _read_local(root)
        other = live(_read_visible(root, other_only=True))
        for rva in failed:
            entry = after.get(rva)
            if entry and entry[0] == token(rva):        # accepted; the reply was lost
                claimed.append(rva)
            elif rva in other:
                held.add(rva)                         # a peer won in the other namespace
            elif not (entry and entry[1].get("expires", 0) > time.time()
                      and entry[1].get("owner") != who):
                unconfirmed.append(rva)
            else:
                held.add(rva)                           # lost the race to a peer
        if not unconfirmed or claimed or held or attempt == 3:
            break
        # A reachable server can reject a free batch because another ref transaction
        # held its locks. Refresh the leases and retry instead of serving it unclaimed.
        current = after
        shas.clear()
        time.sleep(_backoff(attempt))
        failed = list(unconfirmed)
        if push(failed):
            claimed.extend(failed)
            unconfirmed = []
            break
        unconfirmed = []
    if outbox:
        # The combined push was refused. Delete what is still at its sha on its
        # own, after the claim, from the snapshot just re-read.
        _settled(root, settled, _drop(outbox, outbox_who or who, root, entries=settled))
    claimed = sorted(claimed, key=_order)
    refused = sorted(set(rvas) - set(claimed), key=_order)
    _mirror_many({rva: token(rva) for rva in claimed}, root)
    active.cache_clear()
    return ClaimResult(claimed, refused, tokens={r: token(r) for r in claimed},
                       leases={r: lease_of(r)[0] for r in claimed},
                       unconfirmed=sorted(unconfirmed, key=_order), worker=who,
                       prior=prior & set(claimed))


def renew(tokens, who=None, ttl_hours=TTL_HOURS, note="", root=None):
    """Heartbeat: extend claims we still hold. `tokens` is {rva: sha} from a
    ClaimResult or an earlier renew. Each ref is compare-and-swapped against
    its token, so a claim that expired and was taken over is reported lost,
    never overwritten. The lease is kept. A legacy-owner claim (see
    legacy_owner) is renewed under `who`. Returns (renewed {rva: new sha},
    lost [rva]); raises ClaimsUnavailable when origin cannot be read."""
    who = who or owner(root)
    tokens = {key_of(r): t for r, t in tokens.items()}
    if not tokens:
        return {}, []
    names = _names(who, root)
    if not fetch(root):
        raise ClaimsUnavailable("claims: cannot fetch refs/claims/* to renew")
    current = _read_local(root)
    # Read the original leases first: an earlier heartbeat's token remains valid
    # for this lease, and must renew its dependent locks just like the latest token.
    leases = {}
    for key, token in list(tokens.items()):
        body = _git("log", "-1", "--format=%B", token, cwd=root, git_dir=_seen_repo(root))
        try:
            leases[key] = json.loads(body.stdout).get("lease") if body.returncode == 0 else None
        except ValueError:
            leases[key] = None
        entry = current.get(key)
        same = entry and (entry[0] == token or
                          (leases[key] and entry[1].get("lease") == leases[key]))
        if not same or entry[1].get("owner") not in names:
            continue
        for lock in lock_keys({key}, root, records={k: info for k, (_, info) in current.items()}):
            entry_lock = current.get(lock)
            if entry_lock and entry_lock[1].get("owner") in names:
                tokens.setdefault(lock, entry_lock[0])
    renewed, lost = {}, []
    pending = {}                                            # rva: (generation we replace, new sha)
    for rva, token in sorted(tokens.items(), key=lambda kv: _order(kv[0])):
        entry = current.get(rva)
        same = entry and (entry[0] == token or (
            entry[1].get("lease") and entry[1].get("lease") == leases.get(rva)))
        if not same or entry[1].get("owner") not in names:
            lost.append(rva)
            continue
        pending[rva] = (entry[0], _record(who, ttl_hours, note or entry[1].get("note", ""), root,
                                          lease=entry[1].get("lease") or token,
                                          since=entry[1].get("since") or entry[1].get("created"),
                                          scope=entry[1].get("scope", ""), lock=entry[1].get("lock", False),
                                          locks=entry[1].get("locks", ())))
    # One push renews every key (per key, a 20-key heartbeat made 20 paced pushes:
    # 54 s on a quiet host, minutes under a fleet). No --atomic: each ref keeps its
    # own lease, so a key taken over meanwhile fails alone; --porcelain names the
    # refs that moved. What it did not move goes through the per-key loop below,
    # which re-reads origin to tell a lost claim from a lost race.
    by_ref = {ref_of(rva): rva for rva in pending}
    for chunk in _arg_batches(list(pending), lambda r: [f"--force-with-lease={ref_of(r)}:{pending[r][0]}",
                                                         f"{pending[r][1]}:{ref_of(r)}"], 0):
        # No "+": a forced refspec overrides a stale lease, so a claim taken over
        # after the fetch above was overwritten. A matching lease forces anyway.
        pushed = _git("push", "--porcelain", *(f"--force-with-lease={ref_of(r)}:{pending[r][0]}" for r in chunk),
                      REMOTE, *(f"{pending[r][1]}:{ref_of(r)}" for r in chunk), cwd=root, timeout=120)
        for line in pushed.stdout.splitlines():
            flag, _, rest = line.partition("\t")
            ref = rest.split("\t", 1)[0].rpartition(":")[2]
            if flag in (" ", "+", "*", "=") and by_ref.get(ref) in chunk:
                renewed[by_ref[ref]] = pending[by_ref[ref]][1]
    _mirror_many({rva: sha for rva, sha in renewed.items()}, root)
    for rva, (token, sha) in pending.items():
        if rva in renewed:
            continue
        for attempt in range(5):
            pushed = _git("push", "-q", f"--force-with-lease={ref_of(rva)}:{token}", REMOTE,
                          f"{sha}:{ref_of(rva)}", cwd=root, timeout=120)
            if pushed.returncode == 0:
                renewed[rva] = sha
                _mirror(rva, sha, root)
                break
            _invalidate_snapshot(root)
            if not fetch(root):
                raise ClaimsUnavailable("claims: renew push failed and origin cannot be re-read")
            entry = _read_local(root).get(rva)
            if entry and entry[0] == sha:
                renewed[rva] = sha
                break
            if not entry or entry[0] != token:
                lost.append(rva)
                break
            if attempt == 4:
                raise ClaimsUnavailable(f"claims: origin did not accept the renewal of {ref_of(rva)}")
            time.sleep(_backoff(attempt))
    active.cache_clear()
    return renewed, lost


def renew_held(rvas, who=None, ttl_hours=TTL_HOURS, note="", root=None):
    """`claims.py renew`: renew() each of `rvas` that origin shows `who`
    holding (legacy owner included), at the token origin shows now, so the
    lease survives. Returns (renewed {key: sha}, not_renewed [key]): a body
    nobody holds, another worker holds, or that was taken over mid-renewal is
    not renewed. Raises ClaimsUnavailable when origin cannot be read."""
    who = who or owner(root)
    keys = _ints(rvas)
    if not keys:
        return {}, []
    names = _names(who, root)
    if not fetch(root):
        raise ClaimsUnavailable("claims: cannot fetch refs/claims/* to renew")
    current = _read_local(root)
    tokens = {k: current[k][0] for k in keys if k in current and current[k][1].get("owner") in names}
    renewed, lost = renew(tokens, who=who, ttl_hours=ttl_hours, note=note, root=root) \
        if tokens else ({}, [])
    return renewed, sorted(set(lost) | (set(keys) - set(tokens)), key=_order)


def lease_holder(rva, lease, root=None):
    """The CURRENT token of the live claim on `rva` that belongs to `lease`
    (a lease id from ClaimResult.leases, or a claim sha from any renewal of
    it), else None. A publisher reads this right before its atomic push and
    leases the ref at the returned token, so a heartbeat's rotation neither
    invalidates a queued unit nor lets a taken-over claim publish. Raises
    ClaimsUnavailable when origin cannot be read."""
    if not fetch(root):
        raise ClaimsUnavailable("claims: cannot fetch refs/claims/*")
    entry = _read_local(root).get(key_of(rva))
    if not entry or entry[1].get("expires", 0) <= time.time():
        return None
    return entry[0] if lease in (entry[0], entry[1].get("lease")) else None


def publication(token, tip, root=None):
    """A new claim commit that copies claim `token` (owner, lease, expiry)
    and records that `tip` published it. A publisher pushes it in the same
    atomic push as master with --force-with-lease=<ref>:<token>, so the
    server itself checks the claim generation in that transaction. The lease
    is kept, so the owner's heartbeat continues from the new commit."""
    body = _git("log", "-1", "--format=%B", token, cwd=root, git_dir=_seen_repo(root))
    if body.returncode:
        raise ClaimsUnavailable(f"claims: claim commit {token} is not available locally")
    info = json.loads(body.stdout)
    info.update(published=tip, nonce=uuid.uuid4().hex, lease=info.get("lease") or token)
    tree = _git("mktree", input_text="", cwd=root).stdout.strip()
    made = _git("-c", "user.name=claims", "-c", "user.email=claims@localhost",
                "commit-tree", tree, "-m", json.dumps(info, sort_keys=True), cwd=root)
    if made.returncode:
        raise RuntimeError(made.stderr.strip())
    return made.stdout.strip()


def holds(rva, token, root=None):
    """True when origin's claim ref for `rva` is still exactly `token` (the
    fencing check a publisher makes before landing). Raises ClaimsUnavailable
    when origin cannot be asked."""
    got = _git("ls-remote", REMOTE, ref_of(rva), cwd=root, timeout=120)
    if got.returncode:
        raise ClaimsUnavailable(f"claims: cannot ask origin about {ref_of(rva)}")
    return any(line.split("\t")[0] == token for line in got.stdout.splitlines())


def release(rvas, who=None, force=False, root=None, tokens=None):
    """Delete claims we own (or any, with force). Returns released keys.

    With `tokens` ({rva: sha}) a ref is deleted only while it still carries
    that token, so a successor's claim survives a late release. Network
    trouble releases nothing (with a warning): claims expire on their own.
    A legacy-owner claim (see legacy_owner) counts as the default owner's.
    BFME2: the batch goes in one atomic push (each ref leased at the
    generation read here), with contended batches retried together; a branch-namespace
    host overwrites the claim with an expired record instead of deleting it."""
    rvas = _ints(rvas)
    if not rvas:
        return []
    _invalidate_snapshot(root)  # deletion must use a fresh snapshot, even inside a picker
    if not fetch(root):
        print("claims: origin unreachable; releasing nothing (claims expire on their own)", file=sys.stderr)
        return []
    done = _drop(_eligible(rvas, who, root, tokens, force=force), who, root)
    active.cache_clear()
    return done


def _eligible(keys, who=None, root=None, tokens=None, force=False, current=None):
    """{key: sha} of `keys` that release() may delete from the fetched snapshot:
    `who`'s own (any, with force) and, with `tokens`, still at that token."""
    names = _names(who or owner(root), root)
    current = _read_local(root) if current is None else current
    tokens = {key_of(r): t for r, t in (tokens or {}).items()}
    out = {}
    for key in _ints(keys):
        entry = current.get(key)
        if not entry or (entry[1].get("owner") not in names and not force):
            continue
        if key in tokens and entry[0] != tokens[key]:
            continue                    # taken over since: not ours to delete
        out[key] = entry[0]
    return out


def _safe_deletions(pairs, root=None):
    """Keep observed tokens, and retain locks needed by any surviving body.

    In particular, a renewal may move a body's token before its file lock's
    heartbeat lands. Retrying only the unchanged lock would free live work.
    """
    current = _read_local(root)
    changed = {k for k, sha in pairs.items() if current.get(k, (None,))[0] != sha}
    pairs = {k: sha for k, sha in pairs.items() if current.get(k, (None,))[0] == sha}
    records = {k: info for k, (_, info) in current.items()}
    # A moved dependent lock also keeps its body: never split their release
    # into separate transactions merely because one lease was refused.
    pairs = {k: sha for k, sha in pairs.items()
             if current[k][1].get("lock") or not (lock_keys({k}, root, records=records) & changed)}
    records = {k: info for k, (_, info) in live(current).items()
               if k not in pairs and not info.get("lock")}
    needed = lock_keys(records, root, records=records)
    return {k: sha for k, sha in pairs.items()
            if not current[k][1].get("lock") or k not in needed}


@contextmanager
def _guard_deletions(pairs, entries=(), root=None):
    """Keep unevaluated landings claimed through a deferred deletion's push.

    queue_landed uses the same lock. Evidence queued since settlement must
    neither be released by the old plan nor race its actual transaction.
    """
    if not pairs:
        yield {}
        return
    if not entries:
        yield _safe_deletions(pairs, root)
        return
    evaluated = {text for _, text in entries}
    with _queue_lock(root) as path:
        hold = {int(e["rva"], 16) for e in _read_queue(path)
                if json.dumps(e, sort_keys=True) not in evaluated}
        yield _safe_deletions({k: sha for k, sha in pairs.items() if k not in hold}, root)


def _deletion(pairs, who=None, root=None):
    """(lease args, refspecs, expired record) deleting each ref of `pairs`
    {key: sha} only while it still carries that sha. Branch-only hosts cannot
    delete a branch: they overwrite the claim with an already-expired record,
    which every reader ignores."""
    leases = [f"--force-with-lease={ref_of(key)}:{sha}" for key, sha in pairs.items()]
    expired = _record(who or owner(root), -1, "released", root) if NS.startswith("refs/heads/") else None
    refs = [f"+{expired}:{ref_of(key)}" if expired else f":{ref_of(key)}" for key in pairs]
    return leases, refs, expired


def _drop(pairs, who=None, root=None, entries=()):
    """Delete `pairs` {key: sha} in one atomic, lease-fenced push. A refused
    push is re-read: refs that moved (renewed, taken over, already gone) are
    left alone and the rest retried together. Returns the
    deleted keys."""
    pairs = dict(pairs)
    chunks = list(_arg_batches(list(pairs), lambda k: [f"--force-with-lease={ref_of(k)}:{pairs[k]}", f":{ref_of(k)}"]))
    if len(chunks) > 1:     # one atomic push per command-line-sized chunk (see claim's push)
        return sorted((k for c in chunks for k in _drop({k: pairs[k] for k in c}, who, root, entries)), key=_order)
    done = []
    for attempt in range(5):
        if not pairs:
            break
        with _guard_deletions(pairs, entries, root) as pairs:
            if not pairs:
                break
            leases, refs, expired = _deletion(pairs, who, root)
            if _git("push", "-q", "--atomic", *leases, REMOTE, *refs, cwd=root, timeout=120).returncode == 0:
                for key in pairs:
                    _mirror(key, expired, root)
                done += list(pairs)
                break
        if attempt == 4:
            break
        time.sleep(_backoff(attempt))
        _invalidate_snapshot(root)
        fetch(root)  # the next guard rechecks every token and dependent lock together
    return sorted(done, key=_order)


# ---- fewer pushes per task (Stage 2, item 4c) ------------------------------
# settle(defer=True) -- what the pickers run -- queues its fenced deletions
# here instead of pushing them; the seat's next claim() push carries them in
# its own atomic transaction. Whatever no claim push took is flushed in one
# push when the process exits.
_OUTBOX = {}
_OUTBOX_LOCK = threading.Lock()
_OUTBOX_HOOKED = []


def _outbox_key(root):
    return str(Path(root or ROOT).resolve())


def defer_release(pairs, root=None, who=None, entries=()):
    """Queue fenced deletions {key: sha} for the next claim push of `root`;
    `entries` [(key, queued landing JSON)] are forgotten once their key is deleted."""
    if not pairs:
        return
    with _OUTBOX_LOCK:
        box = _OUTBOX.setdefault(_outbox_key(root), {"who": who, "pairs": {}, "entries": set()})
        box["pairs"].update(pairs)
        box["entries"].update(entries)
        if not _OUTBOX_HOOKED:
            _OUTBOX_HOOKED.append(atexit.register(_flush_all))


def _take_outbox(root=None, exclude=()):
    """Remove and return ({key: sha}, who, entries) for `root`; keys in `exclude`
    (the claim push rewrites them, so they are needed again) are dropped."""
    exclude = set(exclude)
    with _OUTBOX_LOCK:
        box = _OUTBOX.pop(_outbox_key(root), None) or {"who": None, "pairs": {}, "entries": set()}
    return ({k: sha for k, sha in box["pairs"].items() if k not in exclude}, box["who"],
            box["entries"])


def _settled(root, entries, done):
    """Forget the queued landings whose claims `done` just deleted."""
    done = set(done)
    _forget_landed(root, {text for key, text in entries if key in done})


def flush_outbox(root=None):
    """Push the deferred deletions of `root` now; returns the deleted keys."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return []
    pairs, who, entries = _take_outbox(root)
    if not pairs:
        return []
    _invalidate_snapshot(root)
    if not fetch(root):
        defer_release(pairs, root, who, entries)
        return []
    done = _drop(pairs, who, root, entries=entries)
    active.cache_clear()
    _settled(root, entries, done)
    return done


def _flush_all():
    for key in list(_OUTBOX):
        try:
            flush_outbox(key)
        except Exception as error:  # noqa: BLE001 -- claims expire on their own
            print(f"claims: deferred release failed ({error}); claims expire on their own", file=sys.stderr)


# ---- garbage collection (Stage 2, item 4a) ---------------------------------
# Nothing ever deleted an expired claim, so origin piled up thousands of refs
# and every fetch paid for them. Any seat may collect: each ref is deleted only
# at the sha it was seen at (--force-with-lease, one atomic push per batch), and
# only when its own record expired more than the grace period ago. A renewal or
# takeover moves the ref, so its lease fails and it survives. Only the write
# namespace is ever touched.
GC_GRACE_MINUTES = 60       # also the floor: clock skew must never free a live claim
GC_BATCH = 150              # refs per push; _gc_batches also bounds command-line length
GC_MAX_PER_MINUTE = 600
GC_SLICE = 50               # refs an opportunistic pass deletes
GC_EVERY_SECONDS = 600      # one opportunistic pass per host and remote per interval


def gc_candidates(root=None, grace_minutes=GC_GRACE_MINUTES, now=None):
    """{key: sha} of refs in the write namespace (from the fetched mirror) whose
    record expired more than `grace_minutes` ago. Unreadable records are kept."""
    if not math.isfinite(grace_minutes):
        raise ValueError("gc grace minutes must be finite")
    cutoff = (time.time() if now is None else now) - max(grace_minutes, GC_GRACE_MINUTES) * 60
    listed = _git("for-each-ref", "--format=%(refname)%09%(objectname)%09%(contents:subject)", SEEN,
                  cwd=root, git_dir=_seen_repo(root))
    if listed.returncode:
        raise ClaimsUnavailable("claims: cannot read fetched claim records to collect")
    found = {}
    for line in listed.stdout.splitlines():
        name, sha, subject = (line.split("\t") + ["", ""])[:3]
        rest = name[len(SEEN):]
        try:
            expires = json.loads(subject).get("expires")
            key = key_of(rest) if rest.startswith(("file/", "class/", "lease/")) else int(rest, 16)
        except (ValueError, AttributeError):
            continue
        if (isinstance(expires, bool) or not isinstance(expires, (int, float))
                or not math.isfinite(expires) or expires >= cutoff):
            continue
        if ref_of(key) != NS + rest:
            continue                    # a hand-made spelling ref_of would not delete
        found[key] = sha
    return found


ARG_BUDGET = 24000      # characters of push arguments per git call (Windows caps a command line at 32,767)


def _arg_batches(items, args_of, reserve=0):
    """`items` in order, cut into lists whose push arguments (`args_of(item)`) fit
    ARG_BUDGET; the first list also leaves room for `reserve` characters."""
    chunk, units, budget = [], 0, ARG_BUDGET - reserve
    for item in items:
        cost = len(subprocess.list2cmdline(args_of(item)).encode("utf-16-le")) // 2 + 2
        if chunk and units + cost > budget:
            yield chunk
            chunk, units, budget = [], 0, ARG_BUDGET
        chunk.append(item)
        units += cost
    if chunk:
        yield chunk


def _gc_batches(keys, found, batch):
    """Bound both the ref count and Windows' command line, including long scopes."""
    chunk, units = {}, 0
    for key in keys:
        ref = ref_of(key)
        args = [f"--force-with-lease={ref}:{found[key]}", f":{ref}"]
        cost = len(subprocess.list2cmdline(args).encode("utf-16-le")) // 2 + 2
        if cost > 24000:
            raise ValueError("gc ref exceeds command-line budget")
        if chunk and (len(chunk) >= batch or units + cost > 24000):
            yield chunk
            chunk, units = {}, 0
        chunk[key] = found[key]
        units += cost
    if chunk:
        yield chunk


def gc(root=None, grace_minutes=GC_GRACE_MINUTES, limit=None, batch=GC_BATCH,
       max_per_minute=GC_MAX_PER_MINUTE, sample=None, rng=random, fresh=True, dry_run=False,
       attempts=3, timeout=120):
    """Delete expired claim refs (lock refs included) on origin. Returns
    (deleted keys, kept keys): kept refs moved under us or could not be deleted.
    `sample` deletes a random slice (so concurrent seats spread out), `limit`
    caps the run, `max_per_minute` spaces the batches. Raises ClaimsUnavailable
    when origin cannot be read."""
    if not math.isfinite(grace_minutes) or not math.isfinite(max_per_minute) or max_per_minute < 0:
        raise ValueError("gc grace and rate must be finite, and rate nonnegative")
    if batch < 1 or (limit is not None and limit < 0) or (sample is not None and sample < 0):
        raise ValueError("gc batch must be positive; max and sample must be nonnegative")
    if fresh:
        _invalidate_snapshot(root)
    if not fetch(root):
        raise ClaimsUnavailable("claims: cannot fetch refs/claims/* to collect")
    found = gc_candidates(root, grace_minutes)
    keys = sorted(found, key=_order)
    if sample is not None and sample < len(keys):
        keys = sorted(rng.sample(keys, sample), key=_order)
    if limit is not None:
        keys = keys[:limit]
    if dry_run:
        return keys, []
    deleted, kept = [], []
    processed = 0
    for chunk in _gc_batches(keys, found, batch):
        began = time.monotonic()
        done = _gc_push(chunk, root, grace_minutes, attempts=attempts, timeout=timeout)
        deleted += done
        done_set = set(done)
        kept += [k for k in chunk if k not in done_set]
        processed += len(chunk)
        if max_per_minute and processed < len(keys):
            time.sleep(max(0.0, len(chunk) * 60.0 / max_per_minute - (time.monotonic() - began)))
    active.cache_clear()
    return deleted, kept


def _gc_push(chunk, root, grace_minutes, attempts=3, timeout=120):
    """One fenced, atomic deletion of `chunk` {key: sha}. A refused push is
    re-read and only refs still at their sha and still expired are retried.
    Every attempt keeps a lock some surviving body still needs, as release
    does (_safe_deletions): a body renewed mid-collection drops out of the
    chunk while its lock's heartbeat may not have landed yet."""
    for attempt in range(attempts):
        chunk = _safe_deletions(chunk, root)
        if not chunk:
            return []
        leases = [f"--force-with-lease={ref_of(k)}:{sha}" for k, sha in chunk.items()]
        refs = [f":{ref_of(k)}" for k in chunk]
        if _git("push", "-q", "--atomic", *leases, REMOTE, *refs, cwd=root, timeout=timeout).returncode == 0:
            for key in chunk:
                _mirror(key, None, root)
            return sorted(chunk, key=_order)
        if attempt == attempts - 1:
            break
        time.sleep(_backoff(attempt))
        _invalidate_snapshot(root)
        if not fetch(root):
            break
        still = gc_candidates(root, grace_minutes)
        chunk = {k: sha for k, sha in chunk.items() if still.get(k) == sha}
    return []


def gc_opportunistic(root=None, rng=random):
    """A small random collection slice, at most once per GC_EVERY_SECONDS per host
    and remote, from the claims snapshot already fetched (settle runs it), so no
    machine owns GC. Never raises; returns the deleted keys."""
    if os.environ.get("BFME_CLAIM_GC", "on") == "off" or os.environ.get("BFME_CLAIMS", "on") == "off":
        return []
    try:
        with _host_file("gc", root) as path:
            if time.time() - _read_stamp(path) < GC_EVERY_SECONDS:
                return []
            path.write_text(repr(time.time()), encoding="utf-8")
        # One short attempt: settle runs this in-line before serving a pick,
        # and a slow or refusing origin must not stall the seat.
        return gc(root, sample=GC_SLICE, batch=GC_SLICE, max_per_minute=0, rng=rng, fresh=False,
                  attempts=1, timeout=20)[0]
    except Exception as error:  # noqa: BLE001 -- collection is best effort
        print(f"claims: gc skipped ({error})", file=sys.stderr)
        return []


# ---- release on authoritative landing -------------------------------------

def _pending_path(root=None):
    return Path(root or ROOT) / PENDING


DEP_LIMIT = 2000        # files one compile read; the most measured (2026-10-09) was 452
# The format of a queued landing's evidence. 2: landing_evidence (receipt-bound
# blobs read once, pins). An entry without it -- ba6f8d1ebb and ae731098e8
# wrote incomplete dependency snapshots -- never releases a claim; the claim
# expires instead (review 2026-10-09, round 2).
EVIDENCE = 2
_QUEUE_THREADS = threading.Lock()


@contextmanager
def _queue_lock(root=None):
    """Serialize queue rewrites across threads and processes (fcntl locks do
    not exclude threads of one process, hence the thread lock as well)."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from portable_lock import lock, unlock
    path = _pending_path(root)
    path.parent.mkdir(parents=True, exist_ok=True)
    with _QUEUE_THREADS, open(path.with_suffix(".lock"), "a+b") as handle:
        lock(handle, exclusive=True)
        try:
            yield path
        finally:
            unlock(handle)


def _read_queue(path):
    try:
        text = path.read_text(encoding="utf-8")
    except OSError:
        return []
    out = []
    for line in text.splitlines():
        try:
            out.append(json.loads(line))
        except ValueError:
            continue
    return out


def _write_queue(path, entries):
    tmp = path.with_name(f"{path.name}.{os.getpid()}.{threading.get_ident()}.tmp")
    tmp.write_text("".join(json.dumps(e, sort_keys=True) + "\n" for e in entries), encoding="utf-8")
    os.replace(tmp, path)


def object_path(source, root=None):
    """The object the byte gate compiled `source` to and verified: tools/
    build.py's obj_path (path parts joined by '_', an uppercase letter as '^'
    + lower). Code/a_b.cpp and Code/a/b.cpp share it."""
    stem = "_".join(Path(source).with_suffix("").parts)
    encoded = "".join(("^" + c.lower()) if c.isupper() else c for c in stem)
    return Path(root or ROOT) / RECEIPTS / (encoded + ".obj")


def receipt_path(source, root=None):
    """The dependency receipt written beside that object (build.py
    _deps_sidecar): its md5s of the source and of every header the compile
    read, the source path and the object's md5."""
    return object_path(source, root).with_suffix(".deps.json")


def _md5(path):
    """The digest tools/build.py records for a file, or None."""
    try:
        return hashlib.md5(Path(path).read_bytes()).hexdigest()
    except OSError:
        return None


def _blob_id(data):
    return hashlib.sha1(b"blob %d\0" % len(data) + data).hexdigest()


def _text_blob_variants(blob, root=None):
    """Hashes of the same immutable text with LF or CRLF line endings.

    Compile receipts bind the raw worktree bytes, which can be CRLF even
    when the published Git blob is LF (including after core.autocrlf changes).
    Read the named blob as bytes: text-mode subprocess output would silently
    normalize it. Binary and non-UTF-8 inputs get no equivalence claim.
    """
    try:
        base = Path(root or ROOT)
        env = _git_env(base)
        got = subprocess.run(["git", "cat-file", "blob", blob], cwd=root or ROOT,
                             capture_output=True, timeout=60, env=env)
        data = got.stdout
        if got.returncode or _blob_id(data) != blob or b"\0" in data:
            return set()
        data.decode("utf-8")
        lf = data.replace(b"\r\n", b"\n")
        return {_blob_id(lf), _blob_id(lf.replace(b"\n", b"\r\n"))}
    except (OSError, subprocess.TimeoutExpired, UnicodeDecodeError):
        return set()


def _stored_blobs(cwd, buffers):
    """({path: blob}, None) for `buffers` ({path: bytes read once}), or (None,
    path) for the first one that cannot be bound. Each blob is derived from
    the buffer itself -- its bytes, or its bytes with CRLF normalized to LF --
    and git (one `hash-object --stdin-paths`, paths on stdin: hundreds of
    them overflow a Windows command line) only says which of the two its
    filters store. A git answer that is neither means the file changed after
    it was read, or a filter other than line endings applies: unbound."""
    paths = list(buffers)
    if not paths:
        return {}, None
    got = _git("hash-object", "--stdin-paths", cwd=cwd, input_text="".join(p + "\n" for p in paths))
    shas = got.stdout.split()
    if got.returncode or len(shas) != len(paths):
        return None, paths[0]
    out = {}
    for path, sha in zip(paths, shas):
        data = buffers[path]
        if sha not in (_blob_id(data), _blob_id(data.replace(b"\r\n", b"\n"))):
            return None, path
        out[path] = sha
    return out, None


def _local_pins(base):
    """(pin lines this checkout adds to reverse/symbols.csv over its merge base
    with origin/master, working tree included; why-not or ""). Verification
    resolves callees through them, so origin must hold them too."""
    if not (base / SYMBOLS).exists():
        return [], ""
    merge = _git("merge-base", "HEAD", "refs/remotes/origin/master", cwd=base)
    if merge.returncode or not merge.stdout.strip():
        return [], "no merge base with origin/master to list this checkout's symbols.csv pins"
    diff = _git("diff", "--no-color", "--no-ext-diff", "--unified=0", merge.stdout.strip(),
                "--", SYMBOLS, cwd=base)
    if diff.returncode:
        return [], f"cannot diff {SYMBOLS}"
    return sorted({line[1:].strip() for line in diff.stdout.splitlines()
                   if line.startswith("+") and not line.startswith("+++") and line[1:].strip()}), ""


def _spelled(base, rel, listings):
    """`rel` as spelled on disk. cl reports an include in the spelling the
    #include asked for, which Windows and Wine resolve whatever its case, and
    git compares paths exactly. Symbolic links and junctions are not followed:
    a junctioned reference/open-bfme-1 is still that path here."""
    current, out = Path(base), []
    for part in rel.split("/"):
        if current not in listings:
            try:
                names = os.listdir(current)
            except OSError:
                names = []
            listings[current] = (set(names), {name.lower(): name for name in names})
        exact, folded = listings[current]
        name = part if part in exact else folded.get(part.lower(), part)
        out.append(name)
        current = current / name
    return "/".join(out)


def _nested_repo(base, rel, seen):
    """The checkout-relative directory of the nested repository (a submodule)
    that holds `rel`, or None."""
    parts = rel.split("/")[:-1]
    for depth in range(1, len(parts) + 1):
        directory = "/".join(parts[:depth])
        if directory not in seen:
            seen[directory] = (Path(base) / directory / ".git").exists()
        if seen[directory]:
            return directory
    return None


def landing_evidence(source, root=None):
    """What origin/master must hold before a landing's claim is released, read
    once at queue time: ({"deps": {path: blob or commit}, "pins": [line],
    "receipt": {path, cmd, object}}, why). `why` is "" when every input is
    established, else the reason one is not; settlement then keeps the claim
    until it expires (fail closed). deps always holds the source's blob.

    deps are the files the verified compile of `source` read. The byte gate's
    receipt (receipt_path) must name this source (Code/a_b.cpp and
    Code/a/b.cpp share a receipt file) and the object build/match holds (its
    md5); with the compile command's fingerprint those are kept as
    "receipt". Each file the receipt lists -- the source and every header cl
    reported through /showIncludes -- is read ONCE: its md5 must be the one
    the compile read, and its blob is derived from those same bytes
    (_stored_blobs), so a file rewritten between the two is never recorded.
    A header must be tracked in this checkout (an ignored or never-added file
    cannot reach origin) unless it lies in a submodule: reference/open-bfme-1,
    which also ships the toolchain headers, is recorded as the commit checked
    out when this ran, and each header the compile read there must equal that
    captured commit's blob -- never the live HEAD, which may move meanwhile. A
    header outside the checkout, in a nested repository that is not a
    submodule, or past DEP_LIMIT is unproven. A .lib source is its own only
    compile input (its members are compared verbatim).

    pins are the reverse/symbols.csv lines this checkout adds over its merge
    base with origin/master (_local_pins): callee resolution reads them.

    KNOWN LIMITATION: a header origin ADDS in a directory searched before the
    one a recorded header came from would shadow it there, and nothing here
    sees that (it needs the include search inventory link_census records).

    Open-BFME-1 lists the files `git diff origin/master HEAD` (two dots) names
    instead: that also lists files a peer changed upstream, whose stale local
    blobs never equal origin's (its re_attempts.log, 0x008615F0
    false-reject), and misses an upstream change made after the last fetch.
    The three-dot diff BFME2 used first dropped every upstream change, so a
    stale header the compile had read was never compared (review 2026-10-09).
    The receipt needs neither: a peer's change to a file this compile read
    holds the claim, a change to any other file does not."""
    base = Path(root or ROOT)
    source = source.replace("\\", "/")
    evidence = {"deps": {source: ""}, "pins": [], "receipt": {}}
    try:
        data = (base / source).read_bytes()
    except OSError:
        return evidence, "the source is missing"
    own, odd = _stored_blobs(base, {source: data})
    if own is None:
        return evidence, f"git would not store {odd} as the bytes just read"
    evidence["deps"] = dict(own)
    evidence["pins"], why = _local_pins(base)
    if why:
        return evidence, why
    if source.lower().endswith(".lib"):
        return evidence, ""
    receipt = receipt_path(source, base)
    try:
        meta = json.loads(receipt.read_text(encoding="utf-8"))
        recorded = dict(meta["deps"])
    except (OSError, ValueError, KeyError, TypeError):
        return evidence, f"no readable build receipt {receipt.relative_to(base).as_posix()}"
    if meta.get("path") != source:
        return evidence, (f"the build receipt is for {meta['path']}, not {source}" if meta.get("path")
                          else "the build receipt names no source (written before receipts did)")
    if not meta.get("object") or meta.get("object") != _md5(object_path(source, base)):
        return evidence, "the build receipt does not describe the object build/match holds"
    if meta.get("source") != hashlib.md5(data).hexdigest():
        return evidence, "the build receipt is for another revision of the source"
    evidence["receipt"] = {"path": source, "cmd": meta.get("cmd", ""), "object": meta["object"]}
    listings, seen, plain, nested = {}, {}, {}, {}
    for dep, digest in sorted(recorded.items()):
        path = Path(dep) if os.path.isabs(dep) else base / dep
        try:
            read = path.read_bytes()
        except OSError:
            return evidence, f"{dep} is gone"
        if hashlib.md5(read).hexdigest() != digest:
            return evidence, f"{dep} changed since the verified compile read it"
        try:
            rel = os.path.relpath(os.path.normpath(path), os.path.normpath(base)).replace("\\", "/")
        except ValueError:              # another drive
            rel = "../"
        if rel == ".." or rel.startswith("../") or os.path.isabs(rel):
            return evidence, f"{dep} lies outside the checkout, so origin cannot hold it"
        rel = _spelled(base, rel, listings)
        repo = _nested_repo(base, rel, seen)
        if repo:
            nested.setdefault(repo, {})[rel[len(repo) + 1:]] = read
        elif rel != source:
            plain[rel] = read
    if len(plain) + len(nested) > DEP_LIMIT:
        return evidence, f"more than {DEP_LIMIT} dependencies"
    index = _git("ls-files", "-s", "-z", cwd=base, timeout=120)
    if index.returncode:
        return evidence, "cannot read this checkout's index"
    tracked, links = set(), set()
    for record in index.stdout.split("\0"):
        mode, _, path = record.partition("\t")
        if path:
            tracked.add(path)
            if mode.startswith("160000"):
                links.add(path)
    for rel in plain:
        if rel not in tracked:
            return evidence, f"{rel} is not tracked (ignored or never added), so origin cannot hold it"
    blobs, odd = _stored_blobs(base, plain)
    if blobs is None:
        return evidence, f"git would not store {odd} as the bytes the compile read"
    deps = dict(own)
    deps.update(blobs)
    for repo, files in sorted(nested.items()):
        if repo not in links:
            return evidence, f"{repo} is a nested repository, not a submodule"
        head = _git("rev-parse", "HEAD", cwd=base / repo).stdout.strip()
        if not head:
            return evidence, f"cannot read {repo}'s checked-out commit"
        committed = _git("cat-file", "--batch-check=%(objectname)", cwd=base / repo,
                         input_text="".join(f"{head}:{path}\n" for path in files)).stdout.splitlines()
        stored, odd = _stored_blobs(base / repo, files)
        if stored is None or len(committed) != len(files):
            return evidence, f"git would not store {repo}/{odd} as the bytes the compile read"
        for path, blob in zip(files, committed):
            if blob.strip() != stored[path]:
                return evidence, (f"{repo} differs from its commit {head[:10]} in {path}, "
                                  "which the compile read")
        deps[repo] = head
    evidence["deps"] = deps
    return evidence, ""


def landing_deps(source, root=None):
    """({path: blob or commit}, why): landing_evidence's file part."""
    evidence, why = landing_evidence(source, root)
    return evidence["deps"], why


def evidence_for(source, root=None):
    """landing_evidence that never raises (bookkeeping must not fail a
    landing): an error makes the landing unproven, which keeps its claim."""
    try:
        if source:
            return landing_evidence(source, root)
        return {"deps": {}, "pins": [], "receipt": {}}, "the row names no source"
    except Exception as error:  # noqa: BLE001
        return {"deps": {}, "pins": [], "receipt": {}}, f"evidence scan failed: {error}"


def queue_landed(rva, row, who=None, root=None, evidence=None, unproven=""):
    """add_match calls this after LOCAL verification: remember the row and
    its landing_evidence (pass `evidence` and `unproven` when a scan of the
    same source is at hand: one scan per source per run). The claim is
    released only once origin/master carries the row -- its name, target_rva,
    size, source, status and member=/object-symbol= selectors, not export_rva
    or other notes, which may change later -- every recorded blob and every
    recorded pin; an old published row with the same key is not this landing
    (review 2026-09-29). Never raises: bookkeeping must not fail a landing."""
    try:
        fields = row.strip().split(",")
        if evidence is None:
            evidence, unproven = evidence_for(fields[4] if len(fields) >= 6 else "", root)
        now = int(time.time())
        who = who or owner(root)
        entry = {"rva": f"0x{int(rva):08X}", "row": row.strip(), "owner": who,
                 "lease": current_lease(rva, who, root), "queued": now,
                 "evidence": EVIDENCE, "deps": evidence.get("deps") or {},
                 "pins": evidence.get("pins") or [], "receipt": evidence.get("receipt") or {},
                 "deps_truncated": bool(unproven), "id": uuid.uuid4().hex}
        if unproven:
            entry["deps_unproven"] = unproven
            print(f"claims: 0x{int(rva):08X}: what its verification read cannot be compared with "
                  f"origin/master ({unproven}); its claim is kept until it expires", file=sys.stderr)
        with _queue_lock(root) as path:
            # a checkout nobody settles must not grow the queue forever: entries
            # past two days describe claims that have long expired
            keep = [e for e in _read_queue(path) if now - e.get("queued", 0) < 2 * 86400]
            _write_queue(path, keep + [entry])
    except Exception as error:  # noqa: BLE001
        print(f"claims: could not queue landed body {rva}: {error}", file=sys.stderr)


def pending(root=None):
    """Queued landings of this checkout (see queue_landed)."""
    return _read_queue(_pending_path(root))


# Notes tokens that choose WHICH bytes a row is: the archive member a .lib row
# reads, the object symbol a row compiles under (tools/build.py
# ledger_member, ledger_object_symbol). Other notes are commentary.
SELECTORS = ("member=", "object-symbol=")


def _row_key(row):
    """(name, rva, size, source, status, selectors) of a ledger row: what
    landed. export_rva and the notes apart from SELECTORS tokens may change
    later without changing the body."""
    fields = row.strip().split(",")
    if len(fields) < 6:
        return None
    notes = ",".join(fields[6:])
    selectors = tuple(sorted(token.strip() for token in notes.split(";")
                             if token.strip().startswith(SELECTORS)))
    return tuple(fields[i] for i in (0, 2, 3, 4, 5)) + (selectors,)


def _fetch_master(root=None):
    """origin/master's sha after a fetch, or None."""
    # Offer only master's history as "have"s (when this clone tracks it): unrelated
    # local ref tips can make the server send the whole history.
    tip = _git("for-each-ref", "--format=--negotiation-tip=%(refname)", f"refs/remotes/{REMOTE}/master",
               cwd=root).stdout.split()
    fetched = _git("fetch", "-q", "--no-tags", *tip, REMOTE, "master", cwd=root, timeout=300)
    if fetched.returncode:
        print(f"claims: git fetch {REMOTE} master failed (exit {fetched.returncode}): "
              f"{fetched.stderr.strip() or '(no stderr)'}", file=sys.stderr)
        return None
    resolved = _git("rev-parse", "FETCH_HEAD", cwd=root)
    if resolved.returncode or not resolved.stdout.strip():
        print(f"claims: git rev-parse FETCH_HEAD failed (exit {resolved.returncode}"
              f"{', empty stdout' if not resolved.stdout.strip() else ''}): "
              f"{resolved.stderr.strip() or '(no stderr)'}", file=sys.stderr)
        return None
    return resolved.stdout.strip()


def _rows_at(rev, root=None):
    shown = _git("show", f"{rev}:{LEDGER}", cwd=root, timeout=120)
    if shown.returncode:
        return None
    return {k for k in map(_row_key, shown.stdout.splitlines()) if k}


def landed_rvas(sha, root=None, tip=None):
    """RVAs of the matched rows commit `sha` adds, if `sha` is on origin/master.
    Raises ClaimsUnavailable when origin cannot be fetched, ValueError when the
    commit is not (yet) on origin/master."""
    tip = tip or _fetch_master(root)
    if not tip:
        raise ClaimsUnavailable("claims: cannot fetch origin/master")
    if _git("merge-base", "--is-ancestor", sha, tip, cwd=root).returncode:
        raise ValueError(f"{sha} is not on origin/master ({tip[:10]}): not landed yet")
    diff = _git("diff", f"{sha}^", sha, "--", LEDGER, cwd=root).stdout
    out = set()
    for line in diff.splitlines():
        if line.startswith("+") and not line.startswith("+++"):
            fields = line[1:].strip().split(",")
            if len(fields) >= 6 and fields[5] == "matched":
                try:
                    out.add(int(fields[2], 16))
                except ValueError:
                    continue
    return sorted(out)


LEASE_TRAILER = re.compile(r"^Claim-Lease:[ \t]*0x([0-9A-Fa-f]{1,8})=([0-9a-f]{8,64})[ \t]*$",
                           re.MULTILINE)


def lease_trailers(sha, root=None):
    """{rva: lease} from `Claim-Lease: 0xRVA=<lease>` trailer lines of commit
    `sha`: the explicit evidence that this commit landed the body under that
    lease. `release --landed SHA` releases nothing without it."""
    body = _git("log", "-1", "--format=%B", sha, cwd=root).stdout
    return {int(rva, 16): lease for rva, lease in LEASE_TRAILER.findall(body)}


def release_landed(sha=None, root=None, who=None, keep_days=1.0, hold=(), tip=None, plan=None,
                   planned_entries=None):
    """Release claims for bodies that have landed on origin/master.

    Every queued landing (queue_landed) with EVIDENCE whose row (_row_key),
    every recorded input (same blob, or only LF/CRLF differences in compiler
    text) and every recorded pin line origin/master's tip now holds is
    released under the owner that queued it and dropped from the
    queue (an entry in an older evidence format never releases: its claim
    expires); with `sha`, the matched rows that commit adds
    whose lease the commit names in a `Claim-Lease: 0xRVA=<lease>` trailer
    are released under `who` -- except any body that still has an unsettled
    queued landing, which stays claimed whatever selected it. A landed entry
    whose release did not happen while its lease is still the live claim
    stays queued for the next settlement; it is dropped once released, once
    another lease holds the body, or once the claim expired. Unsettled
    entries older than `keep_days` are dropped (their claims have long
    expired). Bodies in `hold` are never released, whether a queued landing
    or a `sha` trailer names them, and keep any queued landing: the caller is
    claiming them again. With `plan` (a dict) nothing is pushed: the fenced
    deletions are added to it as {key: sha} for the caller to push (settle),
    and their entries stay queued until a later settlement sees them gone
    (or the caller drops them once pushed: `planned_entries` collects them).
    Returns
    (released, still_pending) lists of ints. Raises ClaimsUnavailable when
    origin/master cannot be read."""
    hold = set(hold)        # once: an iterator would be spent by the first test (Sol, round 2)
    queue = pending(root)
    if not queue and sha is None:
        return [], []
    tip = tip or _fetch_master(root)
    if not tip:
        raise ClaimsUnavailable("claims: cannot fetch origin/master")
    rows = _rows_at(tip, root) if queue else set()
    if rows is None:
        raise ClaimsUnavailable("claims: cannot read origin/master's ledger")
    wanted = {p for e in queue for p in (e.get("deps") or {})}
    published = {}
    if wanted:
        # the whole tree, not `-- <paths>`: hundreds of header paths overflow
        # a Windows command line. A submodule is listed as its commit.
        listed = _git("ls-tree", "-r", "-z", tip, cwd=root, timeout=120)
        if listed.returncode:
            raise ClaimsUnavailable("claims: cannot read origin/master's tree")
        for line in listed.stdout.split("\0"):
            meta, _, path = line.partition("\t")
            if path in wanted:
                published[path] = meta.split()[2]
    pinned = set()
    if any(e.get("pins") for e in queue):
        shown = _git("show", f"{tip}:{SYMBOLS}", cwd=root, timeout=120)
        pinned = {line.strip() for line in shown.stdout.splitlines()} if shown.returncode == 0 else set()

    text_variants = {}

    def input_matches(path, recorded, source):
        blob = published.get(path, "")
        if blob == recorded:
            return True
        # A .lib is compared verbatim, never as compiler text. Likewise no
        # equivalence applies to a submodule commit or other binary file.
        if not blob or source.lower().endswith(".lib") or Path(path).suffix.lower() in (
                ".lib", ".obj", ".dll", ".exe", ".dat"):
            return False
        if blob not in text_variants:
            text_variants[blob] = _text_blob_variants(blob, root)
        return recorded in text_variants[blob]

    def landed(entry):
        # an older snapshot (no receipt binding, blobs read twice, no pins) is
        # never trusted: its claim simply expires (review 2026-10-09, round 2)
        if entry.get("evidence") != EVIDENCE:
            return False
        deps = entry.get("deps")
        if entry.get("deps_truncated") or not deps or _row_key(entry.get("row", "")) not in rows:
            return False
        # a source missing locally proves nothing about what was verified
        if not deps.get(entry["row"].split(",")[4]):
            return False
        if any(pin not in pinned for pin in entry.get("pins") or ()):
            return False
        return all(input_matches(path, blob, entry["row"].split(",")[4])
                   for path, blob in deps.items())
    if sha:
        landed_rvas(sha, root, tip)        # raises unless the commit is on origin/master
    # The trailer IS the landing evidence: a ledger conversion names the body
    # it adds, and a commit that adds no row (a provider_repair link-selection
    # fix removes a competing definition) can still name what it landed.
    # SHA path: only bodies whose lease the commit names in a Claim-Lease
    # trailer. A timestamp comparison was unsound (whole-second commit times,
    # clock skew between hosts: review 2026-09-30 released a claim taken 0.9 s
    # after the commit), so no evidence means the claim is left untouched.
    trailers = lease_trailers(sha, root) if sha else {}
    extra = sorted(trailers)
    # holder -> {rva: set of leases a landed entry was built under}
    by_owner, waiting, keep, unsettled, evidence = {}, [], [], set(), []
    now = time.time()
    for entry in queue:
        try:
            rva = int(entry["rva"], 16)
        except (KeyError, ValueError):
            continue
        if rva in hold:
            # the caller is claiming this body again (claims.py claim): its claim
            # stays, lease and all, and so does the landing that will settle it
            unsettled.add(rva)
            keep.append(entry)
            waiting.append(rva)
            continue
        if landed(entry) and entry.get("lease"):
            holder = entry.get("owner") or who or owner(root)
            by_owner.setdefault(holder, {}).setdefault(rva, set()).add(entry["lease"])
            evidence.append((rva, entry))
        else:
            unsettled.add(rva)
            if now - entry.get("queued", 0) < keep_days * 86400:
                keep.append(entry)
                waiting.append(rva)
    sha_holder = who or owner(root)
    for rva in extra:
        if rva in hold:         # held whether or not a landing is queued for it
            continue
        by_owner.setdefault(sha_holder, {}).setdefault(rva, set()).add(trailers[rva])
    # A body with ANY queued landing whose row and blobs are not all on
    # origin/master stays claimed, however it was selected: an older commit
    # that adds the same RVA (release --landed SHA), or an earlier queued
    # landing of the same body, never overrides a pending one (review
    # 2026-09-29: `release --landed <old sha>` freed a body whose replacement
    # source was still local).
    released, planned = [], {}
    if not any(by_owner.values()) and not queue:
        return [], sorted(set(waiting))
    snapshot = {json.dumps(e, sort_keys=True) for e in queue}
    kept = {json.dumps(e, sort_keys=True) for e in keep}
    with _queue_lock(root) as path:
        # Re-read under the lock, right before releasing: an entry queued
        # while we were on the network was never evaluated, so its body stays
        # claimed (review 2026-09-30: a repair queued during the fetch had its
        # claim released). queue_landed waits on this lock meanwhile.
        current = _read_queue(path)
        for entry in current:
            if json.dumps(entry, sort_keys=True) not in snapshot:
                try:
                    unsettled.add(int(entry["rva"], 16))
                except (KeyError, ValueError):
                    continue
        # The generation is read NOW, after the evidence: a body claimed
        # afresh since the landing (a NEW lease: by another worker, or by the
        # same one after the claim lapsed) is not the claim that landing was
        # built under, and survives (review 2026-09-30). Renewals,
        # publications and a re-claim of a live claim keep the lease, so they
        # do not block a release. The release itself is a compare-and-swap on
        # the generation read here.
        if not fetch(root):
            raise ClaimsUnavailable("claims: cannot fetch refs/claims/* to settle")
        generation = _read_local(root)
        for holder, wanted_leases in by_owner.items():
            tokens = {}
            for rva, leases in wanted_leases.items():
                if rva in unsettled or rva not in generation:
                    continue
                token, info = generation[rva]
                lease = info.get("lease") or token
                if lease in leases:
                    tokens[rva] = token
            if tokens and plan is None:
                released += release(sorted(tokens), who=holder, root=root, tokens=tokens)
            elif tokens:
                got = _eligible(sorted(tokens), holder, root, tokens, current=generation)
                plan.update(got)
                planned.update(got)
        # A landed entry is the only evidence a retry has, so it goes only once
        # its claim is settled: released here, held under another lease,
        # expired or gone -- or still held for a newer queued landing of the
        # body, which carries it from here. A release that did not happen
        # while the entry's lease is still the live claim (origin refused or
        # unreachable, a renewal won the compare-and-swap) keeps it queued
        # (review 2026-10-09: a failed delete dropped it, stranding the claim).
        retry, again = set(), set()
        for rva, entry in evidence:
            if rva in planned:
                retry.add(json.dumps(entry, sort_keys=True))    # dropped once seen gone
                if planned_entries is not None:
                    planned_entries.append((rva, json.dumps(entry, sort_keys=True)))
                continue
            live_claim = generation.get(rva)
            if (rva in unsettled or rva in released or not live_claim
                    or live_claim[1].get("expires", 0) <= time.time()
                    or (live_claim[1].get("lease") or live_claim[0]) != entry["lease"]):
                continue
            retry.add(json.dumps(entry, sort_keys=True))
            again.add(rva)
        # drop only the entries settled here
        settled = snapshot - kept - retry
        _write_queue(path, [e for e in current if json.dumps(e, sort_keys=True) not in settled])
    released = set(released) | set(planned)
    return sorted(released), sorted(set(waiting) | (unsettled - released) | again)


def _forget_landed(root, texts):
    """Drop the queued landings `texts` (their JSON) whose claims were just released."""
    if not texts:
        return
    with _queue_lock(root) as path:
        _write_queue(path, [e for e in _read_queue(path) if json.dumps(e, sort_keys=True) not in texts])


DEBT_TOKEN = re.compile(r"\bdebt=(\S+)")


def debt_digest(line):
    """The 12-hex digest a scope claim's `debt=` note records for one debt line
    (a baseline key, or a header_queue.tsv `class<TAB>source`)."""
    return hashlib.sha1(line.strip().encode("utf-8")).hexdigest()[:12]


def debt_note(lines_by_path):
    """`debt=path#digest,...` for a scope claim's note: what settle_scopes waits on."""
    return "debt=" + ",".join(f"{path}#{debt_digest(line)}" for path, lines in sorted(lines_by_path.items())
                              for line in lines)


def _debt_lines(text, path):
    """Digests of the debt lines a file holds (header_queue.tsv rows as class<TAB>source;
    a link census, link_status.csv, as the source of each unit that does not link)."""
    out = set()
    if path.endswith("link_status.csv"):
        import csv
        import io
        return {debt_digest(row["source"]) for row in csv.DictReader(io.StringIO(text))
                if row.get("source") and row.get("linked") != "yes"}
    for line in text.splitlines():
        if not line.strip() or line.startswith("#"):
            continue
        if path.endswith("header_queue.tsv"):
            parts = line.split("\t")
            if len(parts) < 2 or parts[0] == "class":
                continue
            line = "\t".join(parts[:2])
        out.add(debt_digest(line))
    return out


def settle_scopes(root=None, who=None, tip=None, hold=(), plan=None):
    """Release this owner's claims (RVA or scope; `hold` and lock-only refs excepted)
    whose recorded debt lines (the `debt=` note next_work --claim writes for every
    debt item) origin/master no longer holds: the fix is published, so the work is
    free. A claim without a `debt=` note (a hand claim, a link-cycle row) is never
    released here -- release it by hand after the push. Returns the released keys;
    origin trouble or an unreadable debt file releases nothing (fail closed).
    With `plan` the fenced deletions are added to it instead of pushed."""
    tip = tip or _fetch_master(root)
    if tip is None or not fetch(root):
        return []
    names = _names(who or owner(root), root)
    hold = set(hold)
    texts, free, tokens = {}, [], {}
    for key, (sha, info) in live(_read_local(root)).items():
        if (key in hold or info.get("lock") or (isinstance(key, str) and key.startswith("lease/"))
                or info.get("owner") not in names):
            continue
        wanted = [token for match in DEBT_TOKEN.finditer(info.get("note", "")) for token in match[1].split(",")]
        pairs = [token.rsplit("#", 1) for token in wanted if "#" in token]
        if not pairs:
            continue
        held = False
        for path, digest in pairs:
            if path not in texts:
                shown = _git("show", f"{tip}:{path}", cwd=root, timeout=120)
                texts[path] = _debt_lines(shown.stdout, path) if shown.returncode == 0 else None
            if texts[path] is None or digest in texts[path]:   # unreadable: keep (fail closed)
                held = True
                break
        if not held:
            free.append(key)
            tokens[key] = sha
    if plan is not None:
        plan.update(tokens)
        return sorted(tokens, key=_order)
    return release(free, who=who, root=root, tokens=tokens) if free else []


def settle(rvas=(), who=None, root=None, tokens=None, hold=(), defer=False):
    """BFME2 (Open-BFME-1: fleet_run.settle_shared). Release this checkout's
    queued landings that origin/master now holds, then the claims `rvas`
    except bodies whose landing is still waiting for publication. BFME2 has no
    fleet_run, so the pickers' --claim and bfme1_sweep's donor landing settle
    here. When origin/master cannot be read, a landed-but-unpublished body
    looks like an abandoned one, so every claim is kept until it expires.
    Bodies in `hold` are never released, even when `rvas` names them.

    Every release -- landed bodies, finished scopes, `rvas` and the file locks
    that leaves unneeded -- goes in ONE fenced atomic push; with `defer` (the
    pickers) not even that: the seat's next claim push carries it (claim()), or
    the process flushes it on exit. Then a small opportunistic gc slice runs
    (gc_opportunistic). Never raises; returns the released (with `defer`: the
    queued) keys."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return []
    try:
        hold = set(hold)    # once: release_landed and `free` both test it
        tip = _fetch_master(root)
        if not tip and pending(root):
            return []
        plan, entries = {}, []
        released, waiting = release_landed(root=root, hold=hold, tip=tip, plan=plan, planned_entries=entries)
        busy = set(waiting) | set(released)
        free = [k for k in _ints(rvas) if k not in busy and k not in hold]
        if free:
            _invalidate_snapshot(root)  # deletion must use a fresh snapshot, even inside a picker
            if fetch(root):
                plan.update(_eligible(free, who, root, tokens))
        if tip:
            settle_scopes(root=root, who=who, hold=hold, tip=tip, plan=plan)
        if fetch(root):
            plan.update(_orphan_locks(root, who, gone=plan))     # file locks no claim needs now
        plan = {k: sha for k, sha in plan.items() if k not in hold}
        if defer:
            defer_release(plan, root, who, entries)
            done = list(plan)
        else:
            done = _drop(plan, who, root, entries=entries) if plan else []
            active.cache_clear()
            _settled(root, entries, done)
        gc_opportunistic(root)
    except Exception as error:  # noqa: BLE001 -- claims expire on their own
        print(f"{error}; claims kept until published or expired", file=sys.stderr)
        return []
    return sorted(set(done), key=_order)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["list", "claim", "renew", "release", "whoami", "gc"])
    ap.add_argument("rvas", nargs="*")
    ap.add_argument("--note", default="")
    ap.add_argument("--force", action="store_true", help="release: also claims owned by others")
    ap.add_argument("--landed", nargs="?", const="", default=None, metavar="SHA",
                    help="release: claims whose rows origin/master holds (this checkout's queued "
                         "landings; with SHA also rows that commit adds under a Claim-Lease: 0xRVA=<lease> trailer)")
    ap.add_argument("--grace-minutes", type=float, default=GC_GRACE_MINUTES,
                    help=f"gc: delete refs expired longer than this (floor {GC_GRACE_MINUTES})")
    ap.add_argument("--max", type=int, default=None, help="gc: delete at most this many refs")
    ap.add_argument("--batch", type=int, default=GC_BATCH, help="gc: refs per atomic push")
    ap.add_argument("--max-per-minute", type=float, default=GC_MAX_PER_MINUTE,
                    help="gc: delete at most this many refs per minute (0: unpaced)")
    ap.add_argument("--sample", type=int, default=None, help="gc: a random slice of this many refs")
    ap.add_argument("--dry-run", action="store_true", help="gc: list what would be deleted")
    args = ap.parse_args(argv)
    if args.action == "whoami":
        print(owner())
        return 0
    if args.action == "gc":
        try:
            deleted, kept = gc(grace_minutes=args.grace_minutes, limit=args.max, batch=args.batch,
                               max_per_minute=args.max_per_minute, sample=args.sample,
                               dry_run=args.dry_run)
        except ClaimsUnavailable as error:
            print(error, file=sys.stderr)
            return 2
        except ValueError as error:
            ap.error(str(error))
        if args.dry_run:
            for key in deleted:
                print(label(key))
        print(f"{'would delete' if args.dry_run else 'deleted'} {len(deleted)} expired claim ref(s)"
              + (f"; kept {len(kept)} that moved or were refused" if kept else ""))
        return 0
    if args.action == "list":
        claims = active()
        for rva, info in sorted(claims.items(), key=lambda kv: _order(kv[0])):
            left = (info.get("expires", 0) - time.time()) / 3600
            print(f"{label(rva, info)}  {info.get('owner', '?'):30} {left:5.1f} h left  {info.get('note', '')}")
        print(f"{len(claims)} live claim(s)")
        return 0
    if args.action == "claim":
        # Each key with its file locks (acquire): a body's file is locked with it, and
        # a key whose file a peer's work holds is refused, as the pickers refuse it.
        got, refused, unconfirmed = [], [], []
        # Settle first, as the pickers' --claim does: a seat that claims here directly
        # never ran a picker, and 28% of live RVA claims (2026-10-10) sat on bodies
        # origin/master already held until they expired. Holding what it asks for:
        # releasing a claim the command is about to renew would re-take it under a
        # new lease, leaving a gap a peer could win (GPT-6.1-Sol review). Deferred,
        # so the releases ride in the first claim push. settle() never raises.
        asked = set(_ints(args.rvas))
        released = settle(hold=asked, defer=True)
        try:
            for text in args.rvas:
                result = acquire([text], note=args.note)
                got += [k for k in result.claimed if k not in got]
                refused += [key_of(text)] if result.refused else []
                unconfirmed += result.unconfirmed
        except ClaimsUnavailable as error:
            print(error, file=sys.stderr)
            if got or error.claimed:
                print(f"claimed before the failure: {' '.join(label(r) for r in got + list(error.claimed))}")
            if error.refused:
                print(f"held by someone else: {' '.join(label(r) for r in error.refused)}")
            return 2
        result = ClaimResult(got, refused, unconfirmed=unconfirmed)
        print(f"claimed {len(got)}: {' '.join(label(r) for r in got)}")
        if refused:
            print(f"not claimed: {' '.join(label(r) for r in refused)}"
                  + (f" (unconfirmed, origin trouble: {' '.join(label(r) for r in result.unconfirmed)})"
                     if result.unconfirmed else " (held by someone else)"))
            legacy = legacy_owner()
            mine = [r for r, info in active().items() if r in refused and legacy
                    and info.get("owner") == legacy]
            if mine:
                print(f"{' '.join(label(r) for r in mine)}: held under this checkout's pre-2026-10-09 "
                      f"owner {legacy}; `claims.py renew` continues it, `release` frees it")
        flush_outbox()      # whatever no claim push carried (every target refused)
        remaining = live(_read_local())
        released = [key for key in released if key not in remaining]
        if released:
            print(f"released {len(released)} landed claim(s) origin/master now holds: "
                  f"{' '.join(label(r) for r in released)}")
        return 0 if not refused else 1
    if args.action == "renew":
        try:
            renewed, missed = renew_held(args.rvas, note=args.note)
        except ClaimsUnavailable as error:
            print(error, file=sys.stderr)
            return 2
        print(f"renewed {len(renewed)}: {' '.join(label(r) for r in renewed)}")
        if missed:
            print(f"not renewed (not yours, taken over or not claimed): "
                  f"{' '.join(label(r) for r in missed)}")
        return 0 if not missed else 1
    if args.action == "release" and args.landed is not None:
        plan, entries = {}, []
        try:
            planned, waiting = release_landed(args.landed or None, plan=plan, planned_entries=entries)
            if fetch():
                plan.update(_orphan_locks(gone=plan))
            released = _drop(plan, entries=entries) if plan else []
            active.cache_clear()
            _settled(None, entries, released)
            done = sorted(k for k in released if isinstance(k, int))
            waiting = sorted(set(waiting) | (set(planned) - set(done)))
        except ClaimsUnavailable as error:
            print(error, file=sys.stderr)
            return 2
        except ValueError as error:
            print(f"claims: {error}", file=sys.stderr)
            return 1
        print(f"released {len(done)} landed: {' '.join(f'0x{r:08X}' for r in done)}")
        if waiting:
            print(f"still queued (not yet on origin/master as verified, or its release is retried "
                  f"next time): {' '.join(f'0x{r:08X}' for r in waiting)}")
        return 0
    done = release_work(args.rvas, force=args.force)  # with the file locks it leaves unneeded, one push
    print(f"released {len(done)}: {' '.join(label(r) for r in done)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
