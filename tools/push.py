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
     the tip before the rebase, or on a first attempt a driver's --previous
     (BFME_PUSH_PREVIOUS), so a retry re-verifies
     only what master's new commits can affect;
  5. a lost race (cannot lock ref, fetch first, non-fast-forward, moved past
     this push's base) goes straight back to 1; GitHub failing the ref update
     waits SERVER_ERROR_WAIT_S and goes back to 1; anything else stops.
Same-account spacing: a successful push writes the shared clock file
(<git common dir>/bfme-last-push, or $BFME_PUSH_CLOCK); every attempt waits
until $BFME_PUSH_SPACING_S (default 300) have passed since the last one (the
race an attempt lost may be another seat of the same account landing).

  python3 tools/push.py [--tries 20] [--email ADDRESS] [--dry-run] [--expect-base SHA] [--previous SHA]
                        [--after-lost-race]
Prints one line per attempt with its time; exit 0 when it landed.

--expect-base SHA is for a driver that verified its commits on top of SHA and must publish exactly
those: step 1 then fetches without rebasing and refuses (exit 3) unless origin/master is SHA and HEAD is
built on it, and a race lost during the hook is not retried (a retry would need the rebase); exit 3 tells
the driver to verify again on the new master. A GitHub server error is still retried, since nothing moved.
SHA is resolved with git rev-parse, so a symbolic revision (origin/master, a branch) is accepted too and
then means whatever it names at the time of the fetch: pass the immutable full SHA the driver verified on.

--previous SHA is for a driver that rebases or replays its batch itself between attempts (so push.py's own rebase
moves nothing): name the commit this branch's earlier attempt pushed, and the first attempt passes it to the hook
as BFME_PUSH_PREVIOUS, the receipt hint. Name only the same branch's earlier attempt. The hook still judges it:
a hint with no valid push receipt here falls back to the receipts it finds itself, and what the change from that
commit can affect is verified again either way, so a wrong hint costs verification, never a check.
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
# GitHub's ruleset answers a non-fast-forward with GH013 "Cannot force-push to this branch":
# push.py never forces, so that is master moving under the push too.
LOST_RACE = re.compile(r"cannot lock ref|\(fetch first\)|non-fast-forward|moved past this push's base"
                       r"|incorrect old value provided|remote contains work that you do"
                       r"|GH013.*Cannot force-push|Cannot force-push to this branch")
# GitHub itself failed the ref update or failed to store the pushed pack ("unable to write
# file", "index-pack failed", then "[remote rejected] ... (failed)"): nothing landed and no
# check refused this push.
SERVER_ERROR = re.compile(r"fatal error in commit_refs|\(Internal Server Error\)"
                          r"|remote unpack failed|index-pack failed|unable to write file .*pack"
                          r"|unable to rename temporary '.*\.pack'")
SERVER_ERROR_WAIT_S = 30
NOREPLY = re.compile(r"^[^@\s]+@users\.noreply\.github\.com$")


class Refused(Exception):
    """A push that must not be retried: the message says why."""


class MasterMoved(Refused):
    """--expect-base: origin/master is not the verified base; verify again (exit 3)."""


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
    """Wait until the account's last push is the spacing old, re-reading the
    clock after each sleep (another seat may push meanwhile)."""
    spacing = float(os.environ.get("BFME_PUSH_SPACING_S", "300"))
    while True:
        left = last_push() + spacing - time.time()
        if left <= 0:
            return
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
    # Offer only master's history as "have"s: unrelated local ref tips can make
    # the server send the whole history.
    tip = git("for-each-ref", "--format=--negotiation-tip=%(refname)", f"refs/remotes/{REMOTE}/{BRANCH}").stdout
    git("fetch", "-q", *tip.split(), REMOTE, BRANCH)
    env = dict(os.environ, GIT_COMMITTER_NAME=name, GIT_COMMITTER_EMAIL=email)
    done = git("-c", "submodule.recurse=false", "rebase", "-q", f"{REMOTE}/{BRANCH}", check=False, env=env)
    if done.returncode:
        git("rebase", "--abort", check=False)
        raise Refused("rebase onto origin/master stopped on a conflict; resolve it, then run push.py again:\n"
                      + (done.stdout + done.stderr).strip())
    return before, git("rev-parse", "HEAD").stdout.strip()


def at_expected_base(expect_base):
    """Fetch without rebasing; (HEAD, HEAD) when origin/master is `expect_base` and HEAD is built on it."""
    head = git("rev-parse", "HEAD").stdout.strip()
    tip = git("for-each-ref", "--format=--negotiation-tip=%(refname)", f"refs/remotes/{REMOTE}/{BRANCH}").stdout
    git("fetch", "-q", *tip.split(), REMOTE, BRANCH)
    base = git("rev-parse", "--verify", "-q", f"{expect_base}^{{commit}}", check=False).stdout.strip()
    if not base:
        raise Refused(f"--expect-base {expect_base} is not a commit here")
    master = git("rev-parse", f"{REMOTE}/{BRANCH}").stdout.strip()
    if master != base:
        raise MasterMoved(f"origin/master is {master[:10]}, not the verified base {base[:10]}; "
                          "not rebasing: verify again on the new master")
    if git("merge-base", "--is-ancestor", base, head, check=False).returncode:
        raise Refused(f"HEAD {head[:10]} is not built on the verified base {base[:10]}")
    return head, head


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


def push_once(previous, dry_run, lost_race=False):
    """One git push through the hooks. `previous` is the receipt hint (the tip
    before a rebase); `lost_race` tells the hook this attempt retries one that
    lost the race to master (BFME_PUSH_LOST_RACE=1, which the hook's retry
    window keys on). The flag comes from this invocation alone -- an earlier
    attempt of land() that lost, or --after-lost-race from a driver that runs
    its own retries -- never from the environment: a shell that once exported
    it would mark every later first attempt as a retry."""
    env = dict(os.environ)
    env.pop("BFME_PUSH_LOST_RACE", None)
    if previous:
        env["BFME_PUSH_PREVIOUS"] = previous
    if lost_race:
        env["BFME_PUSH_LOST_RACE"] = "1"
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


def resolve_previous(previous):
    """The full SHA of a driver's --previous commit; Refused when it names none here."""
    sha = git("rev-parse", "--verify", "-q", f"{previous}^{{commit}}", check=False).stdout.strip()
    if not sha:
        raise Refused(f"--previous {previous} is not a commit here")
    return sha


def land(tries=20, email=None, dry_run=False, say=print, after_lost_race=False, expect_base=None, previous=None):
    """`after_lost_race`: this run retries a push that lost the race to master
    (a driver that runs its own retries says so with --after-lost-race).
    `expect_base`: publish HEAD only on top of that exact master, never rebasing (MasterMoved).
    `previous`: the commit the driver's earlier attempt pushed, the first attempt's receipt hint."""
    name, email = push_identity(email)
    if previous:
        previous = resolve_previous(previous)
        say(f"push: receipt hint from the earlier attempt {previous[:10]} (--previous)")
    lost_race = after_lost_race
    for attempt in range(1, tries + 1):
        wait_for_spacing(say)
        started = time.time()
        before, tip = at_expected_base(expect_base) if expect_base else rebase(name, email)
        if previous is None and before != tip:
            previous = before
        pin_submodule()
        outgoing = check_identity(email)
        if outgoing == 0:
            say(f"push: attempt {attempt}: nothing to push (origin/master already holds HEAD)")
            return 0
        wait_for_spacing(say)            # a seat of this account may have landed during the rebase
        rebased = time.time()
        status, output = push_once(previous, dry_run, lost_race)
        took = time.time() - started
        if status == 0:
            if not dry_run:
                record_push()
            say(f"push: attempt {attempt}: landed {outgoing} commit(s) at {tip[:10]} in {took:.1f} s "
                f"(rebase {rebased - started:.1f} s, hook and push {time.time() - rebased:.1f} s)")
            return 0
        if SERVER_ERROR.search(output):
            say(f"push: attempt {attempt}: GitHub failed the ref update after {took:.1f} s; "
                f"retrying in {SERVER_ERROR_WAIT_S} s")
            previous = tip
            time.sleep(SERVER_ERROR_WAIT_S)
            continue
        if not LOST_RACE.search(output):
            say(f"push: attempt {attempt}: refused after {took:.1f} s (see above); not retrying")
            return 1
        if expect_base:
            raise MasterMoved(f"attempt {attempt}: lost the race to master after {took:.1f} s; not rebasing "
                              f"onto it (--expect-base): verify again on the new master")
        say(f"push: attempt {attempt}: lost the race to master after {took:.1f} s; rebasing and retrying")
        previous = tip
        lost_race = True
    say(f"push: still racing after {tries} attempts; run it again")
    return 1


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--tries", type=int, default=20)
    ap.add_argument("--email", help="the push identity (default: git config bfme.pushEmail, else user.email)")
    ap.add_argument("--dry-run", action="store_true", help="git push --dry-run (still runs the hooks)")
    ap.add_argument("--after-lost-race", action="store_true",
                    help="this run retries a push that lost the race to master (a driver that runs its own "
                         "retries, e.g. --tries 1 in a loop, passes it on each retry; the hook's landing "
                         "window for a long retry keys on it)")
    ap.add_argument("--previous", metavar="SHA",
                    help="the commit this branch's earlier attempt pushed (a driver that rebases its batch itself "
                         "names it): passed to the hook as the receipt hint BFME_PUSH_PREVIOUS")
    ap.add_argument("--expect-base", metavar="SHA",
                    help="publish HEAD only if origin/master is exactly SHA (the base the driver verified on); "
                         "never rebase; exit 3 when master moved. Pass the immutable full SHA: a symbolic "
                         "revision is accepted but means whatever it names when push.py fetches")
    args = ap.parse_args(argv)
    try:
        return land(args.tries, args.email, args.dry_run, after_lost_race=args.after_lost_race,
                    expect_base=args.expect_base, previous=args.previous)
    except MasterMoved as why:
        print(f"push: {why}", file=sys.stderr)
        return 3
    except Refused as why:
        print(f"push: {why}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
