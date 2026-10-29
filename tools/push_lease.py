#!/usr/bin/env python3
"""The landing window: one full-gate push to master lands at a time.

WHY. A push whose scope needs the full gate verifies for tens of minutes
before git sends it; with scoped pushes landing every few minutes, master
moves during almost every such gate and the push is rejected (the STLport 4.6
import passed it eight times over ~9 hours on 2026-10-28). A carried retry
(tools/full_gate_receipt.py) makes each lost race cheaper; this window makes
it rarer.

HOW. The window is a shared claim (tools/claims.py) on `lease:landing`, the
ref refs/claims/lease/landing on origin, with a short TTL
(BFME_LANDING_LEASE_MINUTES, default 30). It inherits what claims guarantee:
creating it is atomic across hosts, only its owner releases it, an expired one
is taken over by compare-and-swap, and `claims.py list` shows who holds it.
Its note names the commit being landed.

  * .githooks/pre-push ACQUIRES it before a full-gate (or carried) push to
    master, waiting while another owner holds it; a retry by the holder renews
    it. The hook RELEASES it when it fails. On success it keeps it: the hook
    ends before git sends the pack, and a window released then let a waiter
    win the race anyway (the 2026-10-12 window).
  * Every other push to master WAITS at the end of its hook while another
    owner holds a live window whose commit is not yet on origin/master; once
    that commit lands, the window counts as free.
  * Nothing blocks past the TTL: a crashed holder's window expires, and a
    waiter gives up after BFME_LANDING_LEASE_WAIT_MINUTES (default: the TTL)
    and pushes, saying so. The window is a turn, never a reason to fail a push.
  * Fail-open: when origin's claims cannot be read, acquire and wait warn and
    return; the push then races as it would without the window.

  python3 tools/push_lease.py status
  python3 tools/push_lease.py acquire SHA     # prints the lease token
  python3 tools/push_lease.py wait
  python3 tools/push_lease.py release TOKEN
"""
import argparse
import os
import re
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import claims  # noqa: E402

SCOPE = "lease:landing"
KEY = claims.key_of(SCOPE)
MINUTES = float(os.environ.get("BFME_LANDING_LEASE_MINUTES", "30"))
WAIT_MINUTES = float(os.environ.get("BFME_LANDING_LEASE_WAIT_MINUTES", str(MINUTES)))
POLL_SECONDS = float(os.environ.get("BFME_LANDING_LEASE_POLL_SECONDS", "30"))
NOTE = "full-gate push of {sha}"
NOTE_SHA = re.compile(r"full-gate push of ([0-9a-f]{40})")


def say_err(text):
    print(text, file=sys.stderr)


def holder(root=None):
    """(owner, expires, sha being landed or None) of the live window, or None.
    Raises ClaimsUnavailable."""
    if not claims.fetch(root):
        raise claims.ClaimsUnavailable("push_lease: cannot fetch refs/claims/* from origin")
    entry = claims.live(claims._read_local(root)).get(KEY)
    if not entry:
        return None
    match = NOTE_SHA.search(entry[1].get("note", "") or "")
    return entry[1].get("owner"), entry[1].get("expires", 0), match.group(1) if match else None


def landed(sha, root=None):
    """Whether origin/master already holds `sha` (the window's push went out)."""
    if not sha:
        return False
    cwd = root or claims.ROOT
    if subprocess.run(["git", "fetch", "-q", "origin", "master"], cwd=cwd, capture_output=True).returncode:
        return False
    return subprocess.run(["git", "merge-base", "--is-ancestor", sha, "FETCH_HEAD"], cwd=cwd,
                          capture_output=True).returncode == 0


def _until(expires):
    return time.strftime("%H:%M:%S", time.localtime(expires))


def acquire(sha, minutes=MINUTES, wait_minutes=WAIT_MINUTES, poll=POLL_SECONDS, root=None, say=say_err):
    """Take (or, as its holder, renew) the window for landing `sha`, waiting while
    another owner holds it. Returns the lease token, or None when origin's
    claims are unreachable or the wait ran out (the push goes ahead without it)."""
    deadline = time.time() + wait_minutes * 60
    told = False
    while True:
        try:
            got = claims.claim([SCOPE], ttl_hours=minutes / 60, note=NOTE.format(sha=sha), root=root)
        except claims.ClaimsUnavailable as why:
            say(f"push_lease: {why}; landing without the window")
            return None
        if got.claimed:
            return got.tokens[KEY]
        now = time.time()
        if now >= deadline:
            say(f"push_lease: the landing window is still held after {wait_minutes:g} min; "
                "landing without it")
            return None
        try:
            held = holder(root)
        except claims.ClaimsUnavailable:
            held = None
        if held and not told:
            say(f"push_lease: {held[0]} holds the landing window until {_until(held[1])}; waiting")
            told = True
        time.sleep(min(poll, max(0.0, deadline - now)))


def wait(wait_minutes=WAIT_MINUTES, poll=POLL_SECONDS, root=None, say=say_err):
    """Block while ANOTHER owner holds a live window whose commit has not
    landed. True when the window is free, ours or landed; False when the wait
    ran out or origin's claims are unreachable (the push goes ahead)."""
    me = claims._names(claims.owner(root), root)
    deadline = time.time() + wait_minutes * 60
    told = False
    while True:
        try:
            held = holder(root)
        except claims.ClaimsUnavailable as why:
            say(f"push_lease: {why}; pushing without waiting")
            return False
        if not held or held[0] in me or landed(held[2], root):
            return True
        now = time.time()
        if not told:
            say(f"push_lease: {held[0]} is landing a full-gate push"
                + (f" ({held[2][:10]})" if held[2] else "")
                + f"; waiting until it lands or {_until(min(held[1], deadline))}")
            told = True
        if now >= deadline:
            say(f"push_lease: {held[0]} still holds the landing window after {wait_minutes:g} min "
                f"(until {_until(held[1])}); pushing anyway")
            return False
        time.sleep(min(poll, max(0.0, deadline - now)))


def release(token, root=None):
    """Release our window if `token` still holds it; True when released."""
    try:
        return claims.release([SCOPE], tokens={KEY: token}, root=root) == [KEY]
    except claims.ClaimsUnavailable:
        return False


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("status", help="who holds the landing window")
    acq = sub.add_parser("acquire", help="take the window for SHA (waiting your turn); prints the token")
    acq.add_argument("sha")
    sub.add_parser("wait", help="wait while another owner holds the window")
    rel = sub.add_parser("release", help="release the window you hold")
    rel.add_argument("token")
    args = ap.parse_args(argv)
    if args.cmd == "status":
        try:
            held = holder()
        except claims.ClaimsUnavailable as why:
            print(why, file=sys.stderr)
            return 2
        print("free" if not held else f"held by {held[0]} until {_until(held[1])}"
              + (f" for {held[2]}" if held[2] else ""))
        return 0
    if args.cmd == "acquire":
        token = acquire(args.sha)
        if token:
            print(token)
        return 0
    if args.cmd == "wait":
        wait()
        return 0
    release(args.token)
    return 0


if __name__ == "__main__":
    sys.exit(main())
