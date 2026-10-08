#!/usr/bin/env python3
"""Shared BFME2 body claims on origin: one ref per retail RVA, visible to every host.

The work queues run in separate writer clones and on other hosts. A ledger row
only records completed work, so it cannot keep two workers from starting the
same body. These short-lived refs coordinate work before either worker commits.

HOW. A claim is the ref `refs/claims/0xRVA` on origin, pointing at a tiny
parentless commit whose message is JSON {owner, host, expires}. Creating a ref
that already exists is refused by a non-forced push, so a claim is atomic
across hosts with no server to run; `--atomic` makes a multi-body claim
all-or-nothing per attempt. An expired claim is taken over with
`--force-with-lease=<ref>:<old>` (compare-and-swap), and a release deletes a
ref only if it is still the owner's. Refs under refs/claims/ are not branches:
nobody checks them out or merges them, and nothing about pushing to master
changes.

The normal BFME2 pickers omit live claims; add_match and add_match_batch release
claims after verification. A worker claims before starting and releases an
abandoned body. An orchestrator can use each picker's --claim option to close
the gap between selecting a body and starting its worker.

  python3 tools/claims.py list                 # live claims
  python3 tools/claims.py claim 0xRVA [...]    # claim for this host (TTL 4 h)
  python3 tools/claims.py release 0xRVA [...]  # release your own claims

SCOPES. Work bigger than one body - reconciling a class onto a shared header,
draining a source file, re-homing split rows - is claimed by scope instead:

  python3 tools/claims.py claim file:Code/.../Unit.cpp   # refs/claims/file/<hash>
  python3 tools/claims.py claim class:RenderObjClass     # refs/claims/class/<name>

Same refs, same TTL, same compare-and-swap; `list` shows them with the path
or class. Body pickers only consult RVA claims, so a scope claim is a
convention between workers: check `list` before starting scope-wide work.

Network trouble never blocks work: every entry point warns and carries on
without claims, which is exactly today's behaviour.
"""
import argparse
import json
import os
import socket
import subprocess
import sys
import time
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
# Where claims live on origin. A host whose git proxy only accepts branch
# pushes sets `git config bfme.claimNamespace refs/heads/claims/`.
NS = (os.environ.get("BFME_CLAIM_NS")
      or subprocess.run(["git", "-C", str(ROOT), "config", "--get", "bfme.claimNamespace"],
                        capture_output=True, text=True).stdout.strip()
      or "refs/claims/")
SEEN = "refs/claims-seen/"          # local mirror; never pushed
TTL_HOURS = float(os.environ.get("BFME_CLAIM_TTL_HOURS", "4"))
REMOTE = os.environ.get("BFME_CLAIM_REMOTE", "origin")


def _git(*args, cwd=None, input_text=None, timeout=60):
    cwd = cwd or ROOT
    hooks = Path(cwd) / ".githooks"
    # Run THIS checkout's hooks, not whatever core.hooksPath points at: a host
    # whose hooksPath names an older checkout would run a pre-push that tries
    # to verify a claim marker as if it were code. The hooks still run.
    extra = ["-c", f"core.hooksPath={hooks.as_posix()}"] if args[:1] == ("push",) and hooks.is_dir() else []
    return subprocess.run(["git", *extra, *args], cwd=cwd, capture_output=True, text=True,
                          input=input_text, timeout=timeout)


def owner():
    """Who holds a claim: BFME_CLAIM_OWNER, else the agent a `work-<agent>`
    branch names, else `<git user.name>@<host>`."""
    explicit = os.environ.get("BFME_CLAIM_OWNER")
    if explicit:
        return explicit
    branch = _git("symbolic-ref", "--short", "-q", "HEAD").stdout.strip()
    if branch.startswith("work-") and len(branch) > 5:
        return branch[5:]
    name = _git("config", "user.name").stdout.strip() or "unknown"
    return f"{name}@{socket.gethostname()}"


def key_of(text):
    """A claim key: an int RVA, or a scope string 'file/<hash>' / 'class/<name>'."""
    if isinstance(text, int):
        return text
    if text.startswith("file:"):
        import hashlib
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


def ref_of(key):
    if isinstance(key, str) and not key.startswith(("0x", "0X")) and "/" in key:
        return NS + key
    return f"{NS}0x{int(key, 16) if isinstance(key, str) else key:08X}"


def label(key, info=None):
    if isinstance(key, int):
        return f"0x{key:08X}"
    return key.split("/", 1)[0] + ":" + ((info or {}).get("scope") or key.split("/", 1)[1])


def _record(who, ttl_hours, note="", scope=""):
    """A parentless commit carrying the claim JSON; returns its sha."""
    tree = _git("mktree", input_text="").stdout.strip()
    fields = {"owner": who, "host": socket.gethostname(), "note": note,
              "expires": int(time.time() + ttl_hours * 3600)}
    if scope:
        fields["scope"] = scope
    body = json.dumps(fields, sort_keys=True)
    made = _git("-c", "user.name=claims", "-c", "user.email=claims@localhost",
                "commit-tree", tree, "-m", body)
    if made.returncode:
        raise RuntimeError(made.stderr.strip())
    return made.stdout.strip()


def fetch():
    """Mirror origin's claims locally (refs/claims-seen/*); False on failure."""
    try:
        got = _git("fetch", "-q", "--prune", "--no-tags", REMOTE,
                   f"+{NS}*:{SEEN}*", timeout=15)
    except (OSError, subprocess.TimeoutExpired):
        return False
    return got.returncode == 0


def _read_local(seen=SEEN):
    """{key: (sha, info)} from the local mirror: int RVAs and scope strings."""
    out = _git("for-each-ref", "--format=%(refname)%09%(objectname)%09%(contents:subject)", seen).stdout
    claims = {}
    for line in out.splitlines():
        name, sha, subject = (line.split("\t") + ["", ""])[:3]
        rest = name[len(seen):]
        try:
            info = json.loads(subject)
            key = rest if rest.startswith(("file/", "class/")) else int(rest, 16)
        except ValueError:
            continue
        # Two spellings of one address (e.g. a hand-made lowercase ref) must
        # not let a stale record hide a live one: keep the later expiry.
        if key in claims and claims[key][1].get("expires", 0) >= info.get("expires", 0):
            continue
        claims[key] = (sha, info)
    return claims


def live(claims, now=None):
    now = now or time.time()
    return {rva: v for rva, v in claims.items() if v[1].get("expires", 0) > now}


@lru_cache(maxsize=1)
def active():
    """{rva: info} of every unexpired claim on origin, fetched once per process.
    Empty (with a warning) when origin cannot be reached."""
    if not fetch():
        print("claims: could not fetch refs/claims/* from origin; serving without shared claims",
              file=sys.stderr)
        return {}
    return {rva: info for rva, (_, info) in live(_read_local()).items()}


# A fork can also honour another repository's claims, read-only: with
# `git config bfme.claimMirror upstream`, bodies upstream's workers hold are
# skipped here too (their result arrives through the merge). Nothing is ever
# written to that remote.
MIRROR_SEEN = "refs/claims-mirror-seen/"


@lru_cache(maxsize=1)
def mirrored():
    """{rva: info} of live claims on the mirrored remote; {} if none is set."""
    remote = _git("config", "--get", "bfme.claimMirror").stdout.strip()
    if not remote:
        return {}
    try:
        got = _git("fetch", "-q", "--prune", "--no-tags", remote,
                   f"+refs/claims/*:{MIRROR_SEEN}*", timeout=15)
    except (OSError, subprocess.TimeoutExpired):
        return {}
    if got.returncode:
        return {}
    return {rva: info for rva, (_, info) in live(_read_local(MIRROR_SEEN)).items() if isinstance(rva, int)}


def busy_rvas():
    """Addresses a picker should skip; one fetch is cached per process."""
    if os.environ.get("BFME_CLAIMS", "on") == "off":
        return set()
    return {key for key in active() if isinstance(key, int)} | set(mirrored())


def claim(rvas, who=None, ttl_hours=TTL_HOURS, note=""):
    """Claim `rvas` on origin. Returns (claimed, refused) lists of ints.

    Tries all-or-nothing first (--atomic); if another host holds one, claims
    the rest individually. A claim of ours is renewed; an expired claim is
    taken over by compare-and-swap. Raises nothing on network trouble: the
    bodies come back as claimed=[] and refused=[] with a warning."""
    who = who or owner()
    scopes = {key_of(r): r[r.index(":") + 1:] for r in rvas if isinstance(r, str) and ":" in r}
    rvas = sorted({key_of(r) for r in rvas}, key=str)
    if not rvas:
        return [], []
    if not fetch():
        print("claims: origin unreachable; claiming nothing", file=sys.stderr)
        return [], []
    current = _read_local()
    now = time.time()
    held = {r for r in rvas if r in current and current[r][1].get("expires", 0) > now
            and current[r][1].get("owner") != who}
    held |= {r for r in rvas if isinstance(r, int) and r in mirrored()}  # upstream is on it
    wanted = [r for r in rvas if r not in held]
    if not wanted:
        return [], sorted(held, key=str)
    shas = {}

    def record(rva):
        scope = scopes.get(rva, "")
        if scope not in shas:
            shas[scope] = _record(who, ttl_hours, note, scope)
        return shas[scope]

    def spec(rva):
        sha = record(rva)
        old = current.get(rva)
        return (f"--force-with-lease={ref_of(rva)}:{old[0]}" if old else None,
                f"{sha}:{ref_of(rva)}" if not old else f"+{sha}:{ref_of(rva)}")

    def push(batch):
        leases = [s[0] for s in map(spec, batch) if s[0]]
        refspecs = [spec(r)[1] for r in batch]
        try:
            result = _git("push", "-q", "--atomic", *leases, REMOTE,
                          *refspecs, timeout=30)
        except (OSError, subprocess.TimeoutExpired):
            return False
        return result.returncode == 0

    claimed = []
    if wanted and push(wanted):
        claimed = wanted
    else:
        for rva in wanted:              # somebody raced us for part of the batch
            if push([rva]):
                claimed.append(rva)
    failed = set(wanted) - set(claimed)
    if failed and not fetch():
        print("claims: origin unreachable after claim push; proceeding without "
              "a shared claim for the remaining bodies", file=sys.stderr)
        active.cache_clear()
        return claimed, sorted(held, key=str)
    latest = _read_local() if failed else current
    refused = sorted(set(held) | {r for r in failed if r in latest and
                     latest[r][1].get("expires", 0) > time.time() and
                     latest[r][1].get("owner") != who}, key=str)
    unclaimed = failed - set(refused)
    if unclaimed:
        print("claims: could not publish claim for " +
              " ".join(label(r) for r in sorted(unclaimed, key=str)) +
              "; proceeding without a shared claim", file=sys.stderr)
    active.cache_clear()
    return claimed, refused


def release(rvas, who=None, force=False):
    """Delete claims we own (or any, with force). Returns released keys."""
    rvas = sorted({key_of(r) for r in rvas}, key=str)
    if not rvas:
        return []
    who = who or owner()
    if not fetch():
        print("claims: origin unreachable; releasing nothing (claims expire on their own)", file=sys.stderr)
        return []
    current = _read_local()
    eligible = []
    for rva in rvas:
        entry = current.get(rva)
        if not entry or (entry[1].get("owner") != who and not force):
            continue
        eligible.append((rva, entry[0]))

    def drop(batch):
        leases = [f"--force-with-lease={ref_of(rva)}:{sha}" for rva, sha in batch]
        if NS.startswith("refs/heads/"):
            # Branch-only hosts cannot delete a branch: overwrite the claim
            # with an already-expired record, which every reader ignores.
            expired = _record(who, -1, "released")
            refs = [f"+{expired}:{ref_of(rva)}" for rva, _ in batch]
        else:
            refs = [f":{ref_of(rva)}" for rva, _ in batch]
        try:
            result = _git("push", "-q", "--atomic", *leases, REMOTE,
                          *refs, timeout=30)
        except (OSError, subprocess.TimeoutExpired):
            return False
        return result.returncode == 0

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


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["list", "claim", "release"])
    ap.add_argument("rvas", nargs="*")
    ap.add_argument("--note", default="")
    ap.add_argument("--force", action="store_true", help="release: also claims owned by others")
    args = ap.parse_args(argv)
    if args.action == "list":
        claims = active()
        for rva, info in sorted(claims.items(), key=lambda kv: str(kv[0])):
            left = (info.get("expires", 0) - time.time()) / 3600
            print(f"{label(rva, info)}  {info.get('owner', '?'):30} {left:5.1f} h left  {info.get('note', '')}")
        print(f"{len(claims)} live claim(s)")
        return 0
    if args.action == "claim":
        got, refused = claim(args.rvas, note=args.note)
        print(f"claimed {len(got)}: {' '.join(label(r) for r in got)}")
        if refused:
            print(f"held by someone else: {' '.join(label(r) for r in refused)}")
        return 0 if not refused else 1
    done = release(args.rvas, force=args.force)
    print(f"released {len(done)}: {' '.join(label(r) for r in done)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
