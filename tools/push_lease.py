#!/usr/bin/env python3
"""The landing window: one carried full-gate push to master lands at a time.

WHY. A push whose scope needs the full gate verifies for tens of minutes
before git sends it; with scoped pushes landing every few minutes, master
moves during almost every such gate and the push is rejected (the STLport 4.6
import passed it eight times over ~9 hours on 2026-10-28). A carried retry
(tools/full_gate_receipt.py) verifies only master's commits since the gate,
and this window keeps master still while it does. The first full gate holds
no window, so no seat waits a whole gate.

HOW. The window is a shared claim (tools/claims.py) on `lease:landing`, the
ref refs/claims/lease/landing on origin, with a short TTL
(BFME_LANDING_LEASE_MINUTES, default 30). It inherits what claims guarantee:
creating it is atomic across hosts, only its owner releases it, an expired one
is taken over by compare-and-swap, and `claims.py list` shows who holds it.
Its note names the commit being landed.

  * .githooks/pre-push ACQUIRES it before a carried push to master (one
    whose full gate already passed in this clone), waiting while another owner
    holds it; a retry by the holder renews it. The hook RELEASES it when it fails. On success it keeps it through
    git's push (the hook ends before git sends the pack, and a window released
    then let a waiter win the race anyway: the 2026-10-12 window) and hands it
    to a watcher that releases it once git has exited and origin/master holds
    the commit (`release-landed`); a rejected push keeps it for the retry.
  * A window whose commit is already on origin/master holds nothing: acquire
    expires it by compare-and-swap and takes it, so a holder that never
    released it (killed before its watcher ran) costs no waiter its TTL.
  * Every other push to master WAITS at the end of its hook while another
    owner holds a live window whose commit is not yet on origin/master; once
    that commit lands, the window counts as free.
  * While the hook holds the window it renews it every 10 minutes (the
    heartbeat, BFME_LANDING_HEARTBEAT_SECONDS), so a full gate longer than the
    TTL keeps it; the heartbeat stops when the hook exits.
  * A waiter follows the live window, re-reading its expiry each poll, and
    gives up only after BFME_LANDING_LEASE_WAIT_MINUTES (default 90) and pushes,
    saying so. Nothing blocks past a crashed holder's TTL: its window expires.
    The window is a turn, never a reason to fail a push.
  * Fail-open: when origin's claims cannot be read, acquire and wait warn and
    return; the push then races as it would without the window.

  python3 tools/push_lease.py status
  python3 tools/push_lease.py acquire SHA     # prints the lease token
  python3 tools/push_lease.py renew SHA       # the holder's heartbeat; prints the new token
  python3 tools/push_lease.py wait
  python3 tools/push_lease.py release TOKEN
  python3 tools/push_lease.py release-landed SHA TOKEN   # after git's push of SHA exits
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
# A waiter follows the live window: it waits while the window is held and
# renewed (a full gate on a loaded seat outlasts one TTL), and gives up only at
# this hard cap, so a crashed holder's window still frees everyone at its expiry.
WAIT_MINUTES = float(os.environ.get("BFME_LANDING_LEASE_WAIT_MINUTES", "90"))
POLL_SECONDS = float(os.environ.get("BFME_LANDING_LEASE_POLL_SECONDS", "30"))
NOTE = "full-gate push of {sha}"
NOTE_SHA = re.compile(r"full-gate push of ([0-9a-f]{40})")


def say_err(text):
    print(text, file=sys.stderr)


def mirror_current(root=None):
    """Whether origin's window ref is the one this clone's claims mirror holds
    (both absent counts): the mirror's record of the window is then exactly what
    a fetch would bring, so holder() need not fetch every claim ref (~2,000,
    seconds per push) to read it. False when they differ or origin cannot be
    asked, so the caller fetches as before."""
    ref = claims.ref_of(KEY)
    remote = claims._git("ls-remote", claims.REMOTE, ref, cwd=root, timeout=30)
    if remote.returncode:
        return False
    theirs = next((line.split("\t", 1)[0] for line in remote.stdout.splitlines()
                   if line.endswith("\t" + ref)), "")
    return theirs == (claims.mirror_sha(KEY, root) or "")


def holder(root=None, probe=False):
    """(owner, expires, sha being landed or None) of the live window, or None.
    With `probe`, the claims fetch is skipped when mirror_current() shows the
    mirror already holds origin's window ref. Raises ClaimsUnavailable."""
    if not (probe and mirror_current(root)) and not claims.fetch(root):
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
    # Negotiate from origin/master alone: with the claims mirror's ~1,900
    # refs/worktree/claims-seen/* refs as tips this fetch asked for ~3.4 GB.
    tip = ["--negotiation-tip=refs/remotes/origin/master"] if subprocess.run(
        ["git", "rev-parse", "-q", "--verify", "refs/remotes/origin/master"], cwd=cwd,
        capture_output=True).returncode == 0 else []
    if subprocess.run(["git", "fetch", "-q", *tip, "origin", "master"], cwd=cwd,
                      capture_output=True).returncode:
        return False
    return subprocess.run(["git", "merge-base", "--is-ancestor", sha, "FETCH_HEAD"], cwd=cwd,
                          capture_output=True).returncode == 0


def _expire_landed(root=None):
    """Expire the live window if origin/master already holds its commit (its
    holder's push went out), by compare-and-swap on the ref as last fetched.
    True when it was expired here."""
    entry = claims._read_local(root).get(KEY)
    if not entry or entry[1].get("expires", 0) <= time.time():
        return False
    match = NOTE_SHA.search(entry[1].get("note", "") or "")
    if not match or not landed(match.group(1), root):
        return False
    expired = claims._record(claims.owner(root), -1, "released", root)
    ref = claims.ref_of(KEY)
    if claims._git("push", "-q", f"--force-with-lease={ref}:{entry[0]}", claims.REMOTE,
                   f"+{expired}:{ref}", cwd=root).returncode:
        return False
    claims._mirror(KEY, expired, root)
    return True


def _until(expires):
    return time.strftime("%H:%M:%S", time.localtime(expires))


def acquire(sha, minutes=MINUTES, wait_minutes=WAIT_MINUTES, poll=POLL_SECONDS, root=None, say=say_err):
    """Take (or, as its holder, renew) the window for landing `sha`, waiting while
    another owner holds it, at most `wait_minutes`. Returns the lease token, or
    None when origin's claims are unreachable or the wait ran out (the push goes
    ahead without it)."""
    cap = time.time() + wait_minutes * 60
    shown = None
    taken_over = set()   # landed commits whose window this wait already expired
    while True:
        try:
            got = claims.claim([SCOPE], ttl_hours=minutes / 60, note=NOTE.format(sha=sha), root=root)
        except claims.ClaimsUnavailable as why:
            say(f"push_lease: {why}; landing without the window")
            return None
        if got.claimed:
            return got.tokens[KEY]
        try:
            held = holder(root)
        except claims.ClaimsUnavailable:
            held = None
        # a holder whose commit already landed holds nothing: take its window now
        if held and held[2] and held[2] not in taken_over and _expire_landed(root):
            say(f"push_lease: {held[0]}'s window is for {held[2][:10]}, already on master; taking it")
            taken_over.add(held[2])
            continue
        now = time.time()
        if now >= cap:
            say(f"push_lease: the landing window is still held after {wait_minutes:g} min; "
                "landing without it")
            return None
        if held and held[1] != shown:
            say(f"push_lease: {held[0]} holds the landing window until {_until(held[1])}; waiting")
            shown = held[1]
        time.sleep(min(poll, max(0.0, cap - now)))


def renew(sha, minutes=MINUTES, root=None):
    """The holder's heartbeat: renew the window for `sha` without waiting.
    Returns the new token, or None when another owner holds it or origin's
    claims are unreachable."""
    try:
        got = claims.claim([SCOPE], ttl_hours=minutes / 60, note=NOTE.format(sha=sha), root=root)
    except claims.ClaimsUnavailable:
        return None
    return got.tokens[KEY] if got.claimed else None


def wait(wait_minutes=WAIT_MINUTES, poll=POLL_SECONDS, root=None, say=say_err):
    """Block while ANOTHER owner holds a live window whose commit has not
    landed, following its current expiry (re-read each poll: the holder renews
    it during a long gate), at most `wait_minutes`. True when the window is free,
    ours, expired or landed; False when the cap ran out or origin's claims are
    unreachable (the push goes ahead)."""
    me = claims._names(claims.owner(root), root)
    cap = time.time() + wait_minutes * 60
    shown = None
    while True:
        try:
            held = holder(root, probe=True)
        except claims.ClaimsUnavailable as why:
            say(f"push_lease: {why}; pushing without waiting")
            return False
        if not held or held[0] in me or landed(held[2], root):
            return True
        now = time.time()
        if held[1] != shown:
            say(f"push_lease: {held[0]} is landing a full-gate push"
                + (f" ({held[2][:10]})" if held[2] else "")
                + f"; waiting until it lands or {_until(min(held[1], cap))}"
                + (" (renewed)" if shown is not None else ""))
            shown = held[1]
        if now >= cap:
            say(f"push_lease: {held[0]} still holds the landing window after {wait_minutes:g} min "
                f"(until {_until(held[1])}); pushing anyway")
            return False
        time.sleep(min(poll, max(0.0, cap - now)))


def release(token, root=None):
    """Release our window if `token` still holds it; True when released."""
    try:
        return claims.release([SCOPE], tokens={KEY: token}, root=root) == [KEY]
    except claims.ClaimsUnavailable:
        return False


def release_landed(sha, token, root=None):
    """After git's push of `sha` exited: release our window (`token`) if
    origin/master holds `sha`. A rejected push keeps it for the holder's retry,
    which renews it; a holder that never retries frees it at its TTL."""
    return landed(sha, root) and release(token, root)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("status", help="who holds the landing window")
    acq = sub.add_parser("acquire", help="take the window for SHA (waiting your turn); prints the token")
    acq.add_argument("sha")
    ren = sub.add_parser("renew", help="the holder's heartbeat: renew the window for SHA; prints the token")
    ren.add_argument("sha")
    sub.add_parser("wait", help="wait while another owner holds the window")
    rel = sub.add_parser("release", help="release the window you hold")
    rel.add_argument("token")
    rl = sub.add_parser("release-landed", help="release the window you hold once SHA is on origin/master")
    rl.add_argument("sha")
    rl.add_argument("token")
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
    if args.cmd == "renew":
        token = renew(args.sha)
        if token:
            print(token)
        return 0
    if args.cmd == "wait":
        wait()
        return 0
    if args.cmd == "release-landed":
        return 0 if release_landed(args.sha, args.token) else 1
    release(args.token)
    return 0


if __name__ == "__main__":
    sys.exit(main())
