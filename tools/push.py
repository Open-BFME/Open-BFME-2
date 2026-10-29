#!/usr/bin/env python3
"""Land the current branch on origin/master: rebase, push through the hooks, and
retry a lost race at once until it lands or a real check refuses it.

WHY. Seats pushed with hand-rolled loops (build/bfme_push.sh) or by hand
("pull --rebase, push, pull"), sleeping between attempts, and a lost race cost
a fresh rebase plus a full re-verify. The hooks now re-verify only what changed
since the last check (tools/push_receipts.py), so a retry costs seconds.

WHAT each attempt does:
  1. fetch origin master and rebase onto it (no submodule recursion), with the
     committer set to the push identity; a conflict stops (resolve it by hand);
  2. pin reference/open-bfme-1 to the commit's gitlink (tools/worktree_setup.py
     prepare in a linked worktree);
  3. refuse unless every outgoing commit's author and committer is the push
     identity: --email, else git config bfme.pushEmail, else user.email, which
     must be a GitHub noreply address;
  4. git push origin HEAD:master through .githooks/ (never --no-verify). The
     pre-push hook does every check, takes or waits for the landing window
     (lease:landing, tools/push_lease.py) and carries receipts; this passes it
     the tip before the rebase (BFME_PUSH_PREVIOUS), so a retry re-verifies
     only what master's new commits can affect;
  5. a lost race (cannot lock ref, fetch first, non-fast-forward, moved past
     this push's base) goes straight back to 1; anything else stops.
Same-account spacing: a successful push writes the shared clock file
(<git common dir>/bfme-last-push, or $BFME_PUSH_CLOCK); every attempt waits
until $BFME_PUSH_SPACING_S (default 300) have passed since the last one (the
race an attempt lost may be another seat of the same account landing).

  python3 tools/push.py [--tries 20] [--email ADDRESS] [--dry-run]
Prints one line per attempt with its time; exit 0 when it landed.
"""
import argparse
import os
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REMOTE = "origin"
BRANCH = "master"
SUBMODULE = "reference/open-bfme-1"
# What git and GitHub say when master moved under a push (the ref update lost).
LOST_RACE = re.compile(r"cannot lock ref|\(fetch first\)|non-fast-forward|moved past this push's base"
                       r"|incorrect old value provided|remote contains work that you do")
NOREPLY = re.compile(r"^[^@\s]+@users\.noreply\.github\.com$")


class Refused(Exception):
    """A push that must not be retried: the message says why."""


def git(*args, check=True, env=None, cwd=None):
    done = subprocess.run(["git", *args], cwd=cwd or ROOT, capture_output=True, text=True,
                          encoding="utf-8", errors="replace", env=env)
    if check and done.returncode:
        raise Refused(f"git {' '.join(args[:2])} failed: {(done.stderr or done.stdout).strip()}")
    return done


def config(key):
    done = git("config", "--get", key, check=False)
    return done.stdout.strip() if done.returncode == 0 else ""


def push_identity(email=None):
    """(name, email) every outgoing commit must carry."""
    email = email or config("bfme.pushEmail") or config("user.email")
    if not NOREPLY.match(email or ""):
        raise Refused(f"push identity {email or '(unset)'!r} is not a GitHub noreply address; "
                      "set git config bfme.pushEmail or pass --email")
    name = config("bfme.pushName") or config("user.name") or email.split("@", 1)[0].split("+")[-1]
    return name, email


def clock_path():
    if os.environ.get("BFME_PUSH_CLOCK"):
        return Path(os.environ["BFME_PUSH_CLOCK"])
    common = git("rev-parse", "--git-common-dir").stdout.strip()
    return (ROOT / common).resolve() / "bfme-last-push"


def last_push():
    try:
        return float(clock_path().read_text().split()[0])
    except (OSError, ValueError, IndexError):
        return 0.0


def wait_for_spacing(say):
    spacing = float(os.environ.get("BFME_PUSH_SPACING_S", "300"))
    left = last_push() + spacing - time.time()
    if left > 0:
        say(f"push: the account pushed {spacing - left:.0f} s ago; waiting {left:.0f} s (spacing {spacing:.0f} s)")
        time.sleep(left)


def record_push():
    path = clock_path()
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(f".{path.name}.{os.getpid()}")
    temp.write_text(f"{int(time.time())}\n")
    os.replace(temp, path)


def rebase(name, email):
    """Fetch and rebase onto origin/master; returns (tip before, tip after)."""
    before = git("rev-parse", "HEAD").stdout.strip()
    git("fetch", "-q", REMOTE, BRANCH)
    env = dict(os.environ, GIT_COMMITTER_NAME=name, GIT_COMMITTER_EMAIL=email)
    done = git("-c", "submodule.recurse=false", "rebase", "-q", f"{REMOTE}/{BRANCH}", check=False, env=env)
    if done.returncode:
        git("rebase", "--abort", check=False)
        raise Refused("rebase onto origin/master stopped on a conflict; resolve it, then run push.py again:\n"
                      + (done.stdout + done.stderr).strip())
    return before, git("rev-parse", "HEAD").stdout.strip()


def pin_submodule():
    """Check out the gitlink's commit of reference/open-bfme-1 when it differs."""
    pin = git("ls-tree", "HEAD", SUBMODULE, check=False).stdout.split()
    if len(pin) < 3:
        return
    current = git("-C", SUBMODULE, "rev-parse", "HEAD", check=False).stdout.strip()
    if current == pin[2]:
        return
    setup = ROOT / "tools" / "worktree_setup.py"
    linked = git("rev-parse", "--git-dir").stdout.strip() != git("rev-parse", "--git-common-dir").stdout.strip()
    if linked and setup.exists():
        done = subprocess.run([sys.executable, str(setup), "prepare"], cwd=ROOT, capture_output=True, text=True)
        if done.returncode == 0:
            return
        raise Refused(f"pinning {SUBMODULE} failed:\n{done.stdout}{done.stderr}")
    raise Refused(f"{SUBMODULE} is at {current or 'nothing'}, the commit pins {pin[2]}: "
                  "check it out (worktree_setup.py prepare in a worktree)")


def check_identity(email):
    out = git("log", "--format=%H %ae %ce", f"{REMOTE}/{BRANCH}..HEAD").stdout.split("\n")
    bad = [line.split()[0][:10] for line in out if line and line.split()[1:] != [email, email]]
    if bad:
        raise Refused(f"outgoing commit(s) {', '.join(bad)} are not authored and committed as {email}; "
                      "fix them (git commit --amend --reset-author, or rebase -x) and push again")
    return len([line for line in out if line])


def push_once(previous, dry_run):
    env = dict(os.environ)
    if previous:
        env["BFME_PUSH_PREVIOUS"] = previous
    args = ["-c", "core.hooksPath=.githooks", "-c", "submodule.recurse=false", "push"]
    if dry_run:
        args.append("--dry-run")
    args += [REMOTE, f"HEAD:{BRANCH}"]
    proc = subprocess.Popen(["git", *args], cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                            text=True, encoding="utf-8", errors="replace", env=env)
    lines = []
    for line in proc.stdout:
        sys.stdout.write(line)
        lines.append(line)
    return proc.wait(), "".join(lines)


def land(tries=20, email=None, dry_run=False, say=print):
    name, email = push_identity(email)
    previous = None
    for attempt in range(1, tries + 1):
        wait_for_spacing(say)
        started = time.time()
        before, tip = rebase(name, email)
        if previous is None and before != tip:
            previous = before
        pin_submodule()
        outgoing = check_identity(email)
        if outgoing == 0:
            say(f"push: attempt {attempt}: nothing to push (origin/master already holds HEAD)")
            return 0
        rebased = time.time()
        status, output = push_once(previous, dry_run)
        took = time.time() - started
        if status == 0:
            if not dry_run:
                record_push()
            say(f"push: attempt {attempt}: landed {outgoing} commit(s) at {tip[:10]} in {took:.1f} s "
                f"(rebase {rebased - started:.1f} s, hook and push {time.time() - rebased:.1f} s)")
            return 0
        if not LOST_RACE.search(output):
            say(f"push: attempt {attempt}: refused after {took:.1f} s (see above); not retrying")
            return 1
        say(f"push: attempt {attempt}: lost the race to master after {took:.1f} s; rebasing and retrying")
        previous = tip
    say(f"push: still racing after {tries} attempts; run it again")
    return 1


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--tries", type=int, default=20)
    ap.add_argument("--email", help="the push identity (default: git config bfme.pushEmail, else user.email)")
    ap.add_argument("--dry-run", action="store_true", help="git push --dry-run (still runs the hooks)")
    args = ap.parse_args(argv)
    try:
        return land(args.tries, args.email, args.dry_run)
    except Refused as why:
        print(f"push: {why}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
