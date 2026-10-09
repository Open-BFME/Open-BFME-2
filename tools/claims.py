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

busy_rvas() includes every live claim, so every picker that asks it
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
    source and status; export_rva and notes may change later) and the same
    blobs of the files the verified compile read (landing_deps). Anything
    never settled expires with its TTL.
Readers (active(), busy_rvas()) still warn and serve without shared claims
when origin is unreachable: a picker only proposes, the claim decides.

SCOPES (BFME2). Work bigger than one body - reconciling a class onto a shared
header, draining a source file, re-homing split rows - is claimed by scope:

  python3 tools/claims.py claim file:Code/.../Unit.cpp   # refs/claims/file/<hash>
  python3 tools/claims.py claim class:RenderObjClass     # refs/claims/class/<name>

Same refs, same TTL, same compare-and-swap; `list` shows them with the path
or class. Body pickers only consult RVA claims, so a scope claim is a
convention between workers: check `list` before starting scope-wide work.

A host whose git proxy only accepts branch pushes keeps claims under a branch
namespace (`git config bfme.claimNamespace refs/heads/claims/`, or
BFME_CLAIM_NS); a fork can honour another repository's claims read-only with
`git config bfme.claimMirror upstream`.
"""
import argparse
import hashlib
import json
import os
import re
import socket
import subprocess
import sys
import threading
import time
import uuid
from contextlib import contextmanager
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
# ---- per-repository configuration ------------------------------------------
# Everything that differs from Open-BFME-1's tools/claims.py by design is in
# this block or marked BFME2 below. Keep the rest identical to make syncing a
# plain diff.
LEDGER = "reverse/functions.csv"
# Where the byte gate writes each compiled source's dependency receipt
# (tools/build.py obj_path + _deps_sidecar); landing_deps reads it.
RECEIPTS = "build/match"
# Where claims live on origin. A host whose git proxy only accepts branch
# pushes sets `git config bfme.claimNamespace refs/heads/claims/`.
NS = (os.environ.get("BFME_CLAIM_NS")
      or subprocess.run(["git", "-C", str(ROOT), "config", "--get", "bfme.claimNamespace"],
                        capture_output=True, text=True).stdout.strip()
      or "refs/claims/")
# -----------------------------------------------------------------------------
SEEN = "refs/claims-seen/"          # local mirror; never pushed
TTL_HOURS = float(os.environ.get("BFME_CLAIM_TTL_HOURS", "4"))
REMOTE = os.environ.get("BFME_CLAIM_REMOTE", "origin")
PENDING = Path("build") / "claims" / "landed_pending.jsonl"


class ClaimsUnavailable(RuntimeError):
    """Origin could not be reached or read back, so the claim is incomplete.
    `claimed` lists bodies origin DID accept before the failure (the caller
    should release them or let them expire); `refused` lists bodies origin was
    seen to hold for another worker before it failed. A caller that falls
    back to working unclaimed must still leave every refused body alone
    (review 2026-10-09: the fallback attempted a donor whose body a peer
    held)."""

    def __init__(self, message, claimed=(), refused=()):
        super().__init__(message)
        self.claimed = list(claimed)
        self.refused = list(refused)


class ClaimResult(tuple):
    """(claimed, refused) -- still unpacks and compares like the old tuple --
    plus `tokens` {rva: claim sha} for fencing, `unconfirmed` (the part of
    refused whose push failed while nobody else held the body) and `worker`,
    the owner string written into each claim."""

    def __new__(cls, claimed, refused, tokens=None, unconfirmed=(), worker="", leases=None):
        self = tuple.__new__(cls, (list(claimed), list(refused)))
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


def _git(*args, cwd=None, input_text=None, timeout=60):
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
    env = dict(os.environ, GIT_CEILING_DIRECTORIES=str(Path(cwd).resolve().parent))
    try:
        return subprocess.run(["git", *extra, *args], cwd=cwd, capture_output=True, text=True,
                              input=input_text, timeout=timeout, env=env)
    except subprocess.TimeoutExpired as error:
        return subprocess.CompletedProcess(error.cmd, 124, "", f"timed out after {timeout}s")


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
    """Record in refs/claims-seen/ a claim write origin just accepted."""
    seen = SEEN + ref_of(rva)[len(NS):]
    _git(*(("update-ref", seen, sha) if sha else ("update-ref", "-d", seen)), cwd=root)


def current_lease(rva, who=None, root=None):
    """The lease id of `who`'s claim on `rva` in the local mirror (no network),
    or None. queue_landed binds a landing to it."""
    entry = _read_local(root).get(key_of(rva))
    if not entry or entry[1].get("owner") not in _names(who or owner(root), root):
        return None
    return entry[1].get("lease") or entry[0]


def key_of(text):
    """A claim key: an int RVA, or a scope string 'file/<hash>' / 'class/<name>' (BFME2)."""
    if isinstance(text, int):
        return text
    if text.startswith(("file/", "class/")):    # a key already (ClaimResult.tokens, renew)
        kind, rest = text.split("/", 1)
        if kind == "file" and len(rest) == 16 and all(c in "0123456789abcdef" for c in rest):
            return text
        if kind == "class" and key_of("class:" + rest.replace("%3A%3A", "::")) == text:
            return text
        raise ValueError(f"bad claim key {text!r}")
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


def _record(who, ttl_hours, note="", root=None, lease=None, since=None, scope=""):
    """A parentless commit carrying the claim JSON; returns its sha, which is
    the claim's fencing token (the nonce makes every claim's sha unique).
    `lease` and its start time `since` are kept across renewals; a fresh
    claim starts a new lease. A scope claim records its path or class."""
    tree = _git("mktree", input_text="", cwd=root).stdout.strip()
    now = time.time()
    nonce = uuid.uuid4().hex
    fields = {"owner": who, "host": socket.gethostname(), "note": note,
              "run": os.environ.get("BFME_RUN_ID", ""), "nonce": nonce,
              "lease": lease or nonce, "since": int(since or now),
              "created": int(now), "expires": int(now + ttl_hours * 3600)}
    if scope:
        fields["scope"] = scope
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


def fetch(root=None):
    """Mirror origin's claims locally (refs/claims-seen/*); False on failure."""
    got = _git("fetch", "-q", "--prune", "--no-tags", REMOTE, f"+{NS}*:{SEEN}*", cwd=root, timeout=120)
    return got.returncode == 0


def _read_local(root=None, seen=SEEN):
    """{key: (sha, info)} from the local mirror: int RVAs and scope strings."""
    out = _git("for-each-ref", "--format=%(refname)%09%(objectname)%09%(contents:subject)", seen,
               cwd=root).stdout
    claims = {}
    for line in out.splitlines():
        name, sha, subject = (line.split("\t") + ["", ""])[:3]
        rest = name[len(seen):]
        try:
            info = json.loads(subject)
            rva = rest if rest.startswith(("file/", "class/")) else int(rest, 16)
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
        print("claims: could not fetch refs/claims/* from origin; serving without shared claims",
              file=sys.stderr)
        return {}
    return {rva: info for rva, (_, info) in live(_read_local(root)).items()}


active.cache_clear = _active.cache_clear


# BFME2: a fork can also honour another repository's claims, read-only: with
# `git config bfme.claimMirror upstream`, bodies upstream's workers hold are
# skipped here too (their result arrives through the merge). Nothing is ever
# written to that remote.
MIRROR_SEEN = "refs/claims-mirror-seen/"


def mirrored(root=None):
    """{rva: info} of live claims on the mirrored remote; {} if none is set."""
    return dict(_mirrored(str(Path(root or ROOT).resolve())))


@lru_cache(maxsize=8)
def _mirrored(root):
    remote = _git("config", "--get", "bfme.claimMirror", cwd=root).stdout.strip()
    if not remote:
        return {}
    got = _git("fetch", "-q", "--prune", "--no-tags", remote,
               f"+refs/claims/*:{MIRROR_SEEN}*", cwd=root, timeout=15)
    if got.returncode:
        return {}
    return {rva: info for rva, (_, info) in live(_read_local(root, MIRROR_SEEN)).items()
            if isinstance(rva, int)}


mirrored.cache_clear = _mirrored.cache_clear


def busy_rvas(root=None):
    """Addresses a picker should skip (BFME2; Open-BFME-1 has
    eligibility.busy_rvas). One fetch is cached per process."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return set()
    return {key for key in active(root) if isinstance(key, int)} | set(mirrored(root))


def claim(rvas, who=None, ttl_hours=TTL_HOURS, note="", root=None):
    """Claim `rvas` on origin. Returns a ClaimResult (claimed, refused).

    Tries all-or-nothing first (--atomic); if that fails, claims the rest one
    by one. A live claim of ours is renewed and KEEPS its lease (and start
    time): a re-claim is how a worker extends a claim, and a fresh lease
    orphaned the landing queued under the old one (review 2026-10-09). An
    expired claim -- ours included -- is taken over by compare-and-swap under
    a new lease. A body counts as claimed only when origin accepted it. A
    body the mirrored remote holds is refused, and so is a legacy-owner claim
    (see legacy_owner). Raises ClaimsUnavailable when origin cannot be
    fetched, or when no push succeeded and nobody else holds the bodies
    (network trouble, not a race); its .refused names the bodies origin
    showed another worker holding."""
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
    upstream = mirrored(root)
    held |= {r for r in rvas if isinstance(r, int) and r in upstream}   # upstream is on it
    wanted = [r for r in rvas if r not in held]
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
        if (scope, lease) not in shas:
            shas[scope, lease] = _record(who, ttl_hours, note, root, lease=lease, since=since,
                                         scope=scope)
        return shas[scope, lease]

    def spec(rva):
        sha = token(rva)
        old = current.get(rva)
        return (f"--force-with-lease={ref_of(rva)}:{old[0]}" if old else None,
                f"{sha}:{ref_of(rva)}" if not old else f"+{sha}:{ref_of(rva)}")

    def push(batch):
        leases = [s[0] for s in map(spec, batch) if s[0]]
        refspecs = [spec(r)[1] for r in batch]
        return _git("push", "-q", "--atomic", *leases, REMOTE, *refspecs,
                    cwd=root, timeout=120).returncode == 0

    claimed, failed = [], []
    if wanted and push(wanted):
        claimed = list(wanted)
    else:
        for rva in wanted:              # somebody raced us for part of the batch
            (claimed if push([rva]) else failed).append(rva)
    unconfirmed = []
    if failed:
        # A failed push is either a lost race or network trouble; origin says which.
        if not fetch(root):
            active.cache_clear()
            raise ClaimsUnavailable("claims: push failed and origin cannot be re-read; "
                                    "only the bodies in .claimed are held", claimed=claimed,
                                    refused=sorted(held, key=_order))
        after = _read_local(root)
        for rva in failed:
            entry = after.get(rva)
            if entry and entry[0] == token(rva):        # accepted; the reply was lost
                claimed.append(rva)
            elif not (entry and entry[1].get("expires", 0) > time.time()
                      and entry[1].get("owner") != who):
                unconfirmed.append(rva)
            else:
                held.add(rva)                           # lost the race to a peer
        if unconfirmed and not claimed and len(unconfirmed) == len(wanted):
            active.cache_clear()
            raise ClaimsUnavailable("claims: origin accepted no claim push and nobody else holds "
                                    "the bodies; nothing claimed",
                                    refused=sorted(held, key=_order))
    claimed = sorted(claimed, key=_order)
    refused = sorted(set(rvas) - set(claimed), key=_order)
    for rva in claimed:
        _mirror(rva, token(rva), root)
    active.cache_clear()
    return ClaimResult(claimed, refused, tokens={r: token(r) for r in claimed},
                       leases={r: lease_of(r)[0] for r in claimed},
                       unconfirmed=sorted(unconfirmed, key=_order), worker=who)


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
    # the lease each token belongs to, read from the token's own claim commit
    leases = {}
    for rva, token in tokens.items():
        body = _git("log", "-1", "--format=%B", token, cwd=root)
        try:
            leases[rva] = json.loads(body.stdout).get("lease") if body.returncode == 0 else None
        except ValueError:
            leases[rva] = None
    renewed, lost = {}, []
    for rva, token in sorted(tokens.items(), key=lambda kv: _order(kv[0])):
        entry = current.get(rva)
        same = entry and (entry[0] == token or (
            entry[1].get("lease") and entry[1].get("lease") == leases.get(rva)))
        if not same or entry[1].get("owner") not in names:
            lost.append(rva)
            continue
        sha = _record(who, ttl_hours, note or entry[1].get("note", ""), root,
                      lease=entry[1].get("lease") or token,
                      since=entry[1].get("since") or entry[1].get("created"),
                      scope=entry[1].get("scope", ""))
        token = entry[0]                                    # the generation we replace
        pushed = _git("push", "-q", f"--force-with-lease={ref_of(rva)}:{token}", REMOTE,
                      f"+{sha}:{ref_of(rva)}", cwd=root, timeout=120)
        if pushed.returncode == 0:
            renewed[rva] = sha
            _mirror(rva, sha, root)
            continue
        if not fetch(root):
            raise ClaimsUnavailable("claims: renew push failed and origin cannot be re-read")
        entry = _read_local(root).get(rva)
        if entry and entry[0] == sha:
            renewed[rva] = sha
        elif entry and entry[0] == token:
            raise ClaimsUnavailable(f"claims: origin did not accept the renewal of {ref_of(rva)}")
        else:
            lost.append(rva)
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
    body = _git("log", "-1", "--format=%B", token, cwd=root)
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
    generation read here), one by one only if that fails; a branch-namespace
    host overwrites the claim with an expired record instead of deleting it."""
    rvas = _ints(rvas)
    if not rvas:
        return []
    who = who or owner(root)
    names = _names(who, root)
    if not fetch(root):
        print("claims: origin unreachable; releasing nothing (claims expire on their own)", file=sys.stderr)
        return []
    current = _read_local(root)
    tokens = {key_of(r): t for r, t in (tokens or {}).items()}
    eligible = []
    for rva in rvas:
        entry = current.get(rva)
        if not entry or (entry[1].get("owner") not in names and not force):
            continue
        if rva in tokens and entry[0] != tokens[rva]:
            continue                    # taken over since: not ours to delete
        eligible.append((rva, entry[0]))

    def drop(batch):
        leases = [f"--force-with-lease={ref_of(rva)}:{sha}" for rva, sha in batch]
        expired = None
        if NS.startswith("refs/heads/"):
            # Branch-only hosts cannot delete a branch: overwrite the claim
            # with an already-expired record, which every reader ignores.
            expired = _record(who, -1, "released", root)
            refs = [f"+{expired}:{ref_of(rva)}" for rva, _ in batch]
        else:
            refs = [f":{ref_of(rva)}" for rva, _ in batch]
        if _git("push", "-q", "--atomic", *leases, REMOTE, *refs, cwd=root, timeout=120).returncode:
            return False
        for rva, _ in batch:
            _mirror(rva, expired, root)
        return True

    done = []
    if eligible and drop(eligible):
        done = [rva for rva, _ in eligible]
    elif eligible:
        # One owner may have renewed a ref after our fetch. Let that body stay
        # protected while clearing every other unchanged ref in the batch.
        for entry in eligible:
            if drop([entry]):
                done.append(entry[0])
    active.cache_clear()
    return done


# ---- release on authoritative landing -------------------------------------

def _pending_path(root=None):
    return Path(root or ROOT) / PENDING


DEP_LIMIT = 2000        # files one compile read; the most measured (2026-10-09) was 452
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


def receipt_path(source, root=None):
    """The dependency receipt the byte gate wrote when it compiled `source`:
    tools/build.py's obj_path(source) with the suffix .deps.json (the same
    encoding: path parts joined by '_', an uppercase letter as '^' + lower)."""
    stem = "_".join(Path(source).with_suffix("").parts)
    encoded = "".join(("^" + c.lower()) if c.isupper() else c for c in stem)
    return Path(root or ROOT) / RECEIPTS / (encoded + ".deps.json")


def _md5(path):
    """The digest tools/build.py records for a compiled file, or None."""
    try:
        return hashlib.md5(Path(path).read_bytes()).hexdigest()
    except OSError:
        return None


def _hash_objects(cwd, paths):
    """[blob sha of each working file as git would store it], via stdin (a
    command line of a few hundred header paths overflows Windows' limit)."""
    if not paths:
        return []
    got = _git("hash-object", "--stdin-paths", cwd=cwd, input_text="".join(p + "\n" for p in paths))
    shas = got.stdout.split()
    if got.returncode or len(shas) != len(paths):
        raise RuntimeError(f"git hash-object failed: {got.stderr.strip()}")
    return shas


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


def landing_deps(source, root=None):
    """What origin/master must hold, blob for blob, before a landing's claim is
    released: every file the verified compile of `source` read.

    The byte gate's receipt (receipt_path) names the source and each header
    cl reported through /showIncludes, with the md5 it compiled. Each must
    still have that md5, so these are the bytes that verified. A file inside
    this checkout is then recorded by the blob git would store, unless git
    ignores it (a generated case shim is not repository content); a file
    outside it is the host's, not origin's. A file inside a submodule
    (reference/open-bfme-1, which also ships the toolchain headers) is recorded
    as the submodule's checked-out commit -- what origin/master's tree records
    -- once it is shown to equal that commit's blob: a submodule modified in a
    file the compile read cannot be published as verified. A .lib source is
    its own only input (its members are compared verbatim).

    Returns ({path: blob or commit}, why): `why` is "" when every input is
    established, else the reason one is not, and settlement then keeps the
    claim until it expires (fail closed). The source's blob is always there.

    Open-BFME-1 lists the files `git diff origin/master HEAD` (two dots) names
    instead: that also lists files a peer changed upstream, whose stale local
    blobs never equal origin's (its re_attempts.log, 0x008615F0
    false-reject), and misses an upstream change made after the last fetch.
    The three-dot diff BFME2 used first dropped every upstream change, so a
    stale header the compile had read was never compared (review
    2026-10-09). The receipt needs neither: a peer's change to a file this
    compile read holds the claim, a change to any other file does not. It
    does not see a header origin ADDED that would shadow one the compile read
    (include search order), nor reverse/symbols.csv pins."""
    base = Path(root or ROOT)
    source = source.replace("\\", "/")
    if not (base / source).is_file():
        return {source: ""}, "the source is missing"
    own = dict(zip([source], _hash_objects(base, [source])))
    if source.lower().endswith(".lib"):
        return own, ""
    receipt = receipt_path(source, base)
    try:
        meta = json.loads(receipt.read_text(encoding="utf-8"))
        recorded, compiled = dict(meta["deps"]), meta["source"]
    except (OSError, ValueError, KeyError, TypeError):
        return own, f"no readable build receipt {receipt.relative_to(base).as_posix()}"
    if compiled != _md5(base / source):
        return own, "the build receipt is for another revision of the source"
    listings, seen, plain, nested = {}, {}, [], {}
    for dep, digest in sorted(recorded.items()):
        path = Path(dep) if os.path.isabs(dep) else base / dep
        if _md5(path) != digest:
            return own, f"{dep} changed since the verified compile read it"
        try:
            rel = os.path.relpath(os.path.normpath(path), os.path.normpath(base)).replace("\\", "/")
        except ValueError:              # another drive
            continue
        if rel == ".." or rel.startswith("../") or os.path.isabs(rel):
            continue                    # outside the checkout: the host's, not origin's
        rel = _spelled(base, rel, listings)
        repo = _nested_repo(base, rel, seen)
        if repo:
            nested.setdefault(repo, []).append(rel[len(repo) + 1:])
        else:
            plain.append(rel)
    if len(plain) + len(nested) > DEP_LIMIT:
        return own, f"more than {DEP_LIMIT} dependencies"
    ignored = set()
    if plain:
        got = _git("check-ignore", "--stdin", "-z", cwd=base, input_text="\0".join(plain) + "\0")
        if got.returncode not in (0, 1):                # 1: none ignored
            return own, f"git check-ignore failed: {got.stderr.strip()}"
        ignored = {path for path in got.stdout.split("\0") if path}
    required = [path for path in plain if path not in ignored and path != source]
    deps = dict(own)
    deps.update(zip(required, _hash_objects(base, required)))
    for repo, inner in sorted(nested.items()):
        link = _git("ls-files", "-s", "--", repo, cwd=base).stdout.split()
        if not link or link[0] != "160000":
            if _git("check-ignore", "-q", repo, cwd=base).returncode == 0:
                continue                # an ignored nested clone: the host's
            return own, f"{repo} is a nested repository, not a submodule"
        head = _git("rev-parse", "HEAD", cwd=base / repo).stdout.strip()
        committed = _git("cat-file", "--batch-check=%(objectname)", cwd=base / repo,
                         input_text="".join(f"HEAD:{path}\n" for path in inner)).stdout.splitlines()
        if not head or len(committed) != len(inner):
            return own, f"cannot read {repo}'s checked-out commit"
        for path, blob, have in zip(inner, committed, _hash_objects(base / repo, inner)):
            if blob.strip() != have:
                return own, f"{repo} differs from its commit in {path}, which the compile read"
        deps[repo] = head
    return deps, ""


def queue_landed(rva, row, who=None, root=None, deps=None, unproven=""):
    """add_match calls this after LOCAL verification: remember the row and
    the blobs of every file its verified compile read (landing_deps), so the
    claim is released only once origin/master carries the row's name,
    target_rva, size, source and status (not export_rva or notes, which may
    change later) and all of those blobs -- an old published row with the same
    key is not this landing (review 2026-09-29). `deps` and `unproven` are a
    landing_deps result the caller already has. Never raises: bookkeeping must
    not fail a landing."""
    try:
        fields = row.strip().split(",")
        source = fields[4] if len(fields) >= 6 else ""
        if deps is None:
            try:
                deps, unproven = landing_deps(source, root) if source else ({}, "the row names no source")
            except Exception as error:  # noqa: BLE001 -- still queue it: unproven keeps the claim
                deps, unproven = {}, f"dependency scan failed: {error}"
        now = int(time.time())
        who = who or owner(root)
        entry = {"rva": f"0x{int(rva):08X}", "row": row.strip(), "owner": who,
                 "lease": current_lease(rva, who, root),
                 "queued": now, "deps": deps, "deps_truncated": bool(unproven),
                 "id": uuid.uuid4().hex}
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


def _row_key(row):
    """(name, rva, size, source, status) of a ledger row: what landed, not its notes."""
    fields = row.strip().split(",")
    return tuple(fields[i] for i in (0, 2, 3, 4, 5)) if len(fields) >= 6 else None


def _fetch_master(root=None):
    """origin/master's sha after a fetch, or None."""
    fetched = _git("fetch", "-q", "--no-tags", REMOTE, "master", cwd=root, timeout=300)
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


def release_landed(sha=None, root=None, who=None, keep_days=1.0):
    """Release claims for bodies that have landed on origin/master.

    Every queued landing (queue_landed) whose row (name, target_rva, size,
    source, status) and whose every recorded input blob (landing_deps)
    origin/master's tip now holds is released under the owner that queued it
    and dropped from the queue; with `sha`, the matched rows that commit adds
    whose lease the commit names in a `Claim-Lease: 0xRVA=<lease>` trailer
    are released under `who` -- except any body that still has an unsettled
    queued landing, which stays claimed whatever selected it. A landed entry
    whose release did not happen while its lease is still the live claim
    stays queued for the next settlement; it is dropped once released, once
    another lease holds the body, or once the claim expired. Unsettled
    entries older than `keep_days` are dropped (their claims have long
    expired). Returns (released, still_pending) lists of ints. Raises
    ClaimsUnavailable when origin/master cannot be read."""
    queue = pending(root)
    if not queue and sha is None:
        return [], []
    tip = _fetch_master(root)
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

    def landed(entry):
        deps = entry.get("deps")
        if entry.get("deps_truncated") or not deps or _row_key(entry.get("row", "")) not in rows:
            return False
        # a source missing locally proves nothing about what was verified
        if not deps.get(entry["row"].split(",")[4]):
            return False
        return all(published.get(path, "") == blob for path, blob in deps.items())
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
        by_owner.setdefault(sha_holder, {}).setdefault(rva, set()).add(trailers[rva])
    # A body with ANY queued landing whose row and blobs are not all on
    # origin/master stays claimed, however it was selected: an older commit
    # that adds the same RVA (release --landed SHA), or an earlier queued
    # landing of the same body, never overrides a pending one (review
    # 2026-09-29: `release --landed <old sha>` freed a body whose replacement
    # source was still local).
    released = []
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
            if tokens:
                released += release(sorted(tokens), who=holder, root=root, tokens=tokens)
        # A landed entry is the only evidence a retry has, so it goes only once
        # its claim is settled: released here, held under another lease,
        # expired or gone -- or still held for a newer queued landing of the
        # body, which carries it from here. A release that did not happen
        # while the entry's lease is still the live claim (origin refused or
        # unreachable, a renewal won the compare-and-swap) keeps it queued
        # (review 2026-10-09: a failed delete dropped it, stranding the claim).
        retry, again = set(), set()
        for rva, entry in evidence:
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
    return sorted(set(released)), sorted(set(waiting) | (unsettled - set(released)) | again)


def settle(rvas=(), who=None, root=None, tokens=None):
    """BFME2 (Open-BFME-1: fleet_run.settle_shared). Release this checkout's
    queued landings that origin/master now holds, then the claims `rvas`
    except bodies whose landing is still waiting for publication. BFME2 has no
    fleet_run, so the pickers' --claim and bfme1_sweep's donor landing settle
    here. When origin/master cannot be read, a landed-but-unpublished body
    looks like an abandoned one, so every claim is kept until it expires.
    Never raises; returns the released keys."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return []
    try:
        released, waiting = release_landed(root=root)
        busy = set(waiting) | set(released)
        free = [k for k in _ints(rvas) if k not in busy]
        done = release(free, who=who, root=root, tokens=tokens) if free else []
    except Exception as error:  # noqa: BLE001 -- claims expire on their own
        print(f"{error}; claims kept until published or expired", file=sys.stderr)
        return []
    return sorted(set(done) | set(released), key=_order)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["list", "claim", "renew", "release", "whoami"])
    ap.add_argument("rvas", nargs="*")
    ap.add_argument("--note", default="")
    ap.add_argument("--force", action="store_true", help="release: also claims owned by others")
    ap.add_argument("--landed", nargs="?", const="", default=None, metavar="SHA",
                    help="release: claims whose rows origin/master holds (this checkout's queued "
                         "landings; with SHA also rows that commit adds under a Claim-Lease: 0xRVA=<lease> trailer)")
    args = ap.parse_args(argv)
    if args.action == "whoami":
        print(owner())
        return 0
    if args.action == "list":
        claims = active()
        for rva, info in sorted(claims.items(), key=lambda kv: _order(kv[0])):
            left = (info.get("expires", 0) - time.time()) / 3600
            print(f"{label(rva, info)}  {info.get('owner', '?'):30} {left:5.1f} h left  {info.get('note', '')}")
        print(f"{len(claims)} live claim(s)")
        return 0
    if args.action == "claim":
        try:
            result = claim(args.rvas, note=args.note)
        except ClaimsUnavailable as error:
            print(error, file=sys.stderr)
            if error.claimed:
                print(f"claimed before the failure: {' '.join(label(r) for r in error.claimed)}")
            if error.refused:
                print(f"held by someone else: {' '.join(label(r) for r in error.refused)}")
            return 2
        got, refused = result
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
        try:
            done, waiting = release_landed(args.landed or None)
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
    done = release(args.rvas, force=args.force)
    print(f"released {len(done)}: {' '.join(label(r) for r in done)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
