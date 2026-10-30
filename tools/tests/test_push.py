"""tools/push.py lands a branch on master through the hooks: a lost race is
retried at once, a real refusal stops, a wrong identity is refused, the hook's
landing-window wait is honoured, and the same-account spacing holds.

A bare origin and two clones in a temporary directory; the seat's pre-push hook
is a fixture whose behaviour each test sets. Nothing reaches a network."""
import os
import subprocess
import sys
import time
import types
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import push  # noqa: E402

EMAIL = "seat@users.noreply.github.com"
HOOK = """#!/usr/bin/env bash
state="$PUSH_TEST_STATE"
n=$(cat "$state/hook-count" 2>/dev/null || echo 0)
echo $((n + 1)) > "$state/hook-count"
echo "previous=${BFME_PUSH_PREVIOUS:-}" >> "$state/hook-env"
echo "lost_race=${BFME_PUSH_LOST_RACE:-}" >> "$state/hook-lost"
if [ -f "$state/race" ] && [ "$n" -lt "$(cat "$state/race")" ]; then
    # another seat lands while this hook runs: git then rejects this push
    ( unset GIT_CONFIG_PARAMETERS GIT_CONFIG_COUNT GIT_DIR GIT_WORK_TREE GIT_INDEX_FILE
      cd "$state/other" && git pull -q --rebase origin master && echo "$n" >> other.txt \\
        && git add other.txt && git commit -qm "other seat $n" && git push -q origin HEAD:master )
    # that seat pushed as this account: it moved the shared clock
    [ ! -f "$state/same-account" ] || date +%s > "$BFME_PUSH_CLOCK"
fi
if [ -f "$state/lease" ]; then
    echo "push_lease: other is landing a full-gate push; waiting until it lands or 12:00:00" >&2
    sleep "$(cat "$state/lease")"
fi
if [ -f "$state/refuse" ]; then
    echo "PRE-PUSH FAILED: ledger integrity at HEAD (see above)" >&2
    exit 1
fi
exit 0
"""


def git(cwd, *args, env=None):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True,
                          env=env).stdout.strip()


@pytest.fixture
def seat(tmp_path, monkeypatch):
    origin = tmp_path / "origin.git"
    git(tmp_path, "init", "-q", "--bare", "-b", "master", str(origin))
    clones = {}
    for name in ("seat", "other"):
        clone = tmp_path / name
        git(tmp_path, "clone", "-q", str(origin), str(clone))
        git(clone, "config", "user.name", name)
        git(clone, "config", "user.email", EMAIL)
        git(clone, "config", "core.autocrlf", "false")
        clones[name] = clone
    seat = clones["seat"]
    (seat / "README").write_text("base\n")
    git(seat, "add", "README")
    git(seat, "commit", "-qm", "base")
    git(seat, "push", "-q", "origin", "HEAD:master")
    git(clones["other"], "pull", "-q", "origin", "master")
    # the other seat's own push runs no hook (a global core.hooksPath would run the fixture's)
    (tmp_path / "no-hooks").mkdir()
    git(clones["other"], "config", "core.hooksPath", (tmp_path / "no-hooks").as_posix())
    hooks = seat / ".githooks"
    hooks.mkdir()
    (hooks / "pre-push").write_text(HOOK, newline="\n")
    os.chmod(hooks / "pre-push", 0o755)
    git(seat, "add", ".githooks")
    git(seat, "commit", "-qm", "fixture hook")
    git(seat, "push", "-q", "--no-verify", "origin", "HEAD:master")   # fixture setup, not a seat's push
    git(clones["other"], "pull", "-q", "origin", "master")
    state = tmp_path / "state"
    state.mkdir()
    (state / "other").symlink_to(clones["other"], target_is_directory=True) if os.name != "nt" else None
    if os.name == "nt":
        state = clones["other"].parent / "state"
    monkeypatch.setenv("PUSH_TEST_STATE", state.as_posix())
    if os.name == "nt":
        # the hook cds into $state/other: give it a real directory link on Windows
        subprocess.run(["cmd", "/c", "mklink", "/J", str(state / "other"), str(clones["other"])],
                       check=True, capture_output=True)
    monkeypatch.setattr(push, "ROOT", seat)
    monkeypatch.setenv("BFME_PUSH_CLOCK", str(tmp_path / "clock"))
    monkeypatch.setenv("BFME_PUSH_SPACING_S", "0")
    return seat, clones["other"], origin, state


def work(seat, text="change"):
    (seat / "work.txt").write_text(text)
    git(seat, "add", "work.txt")
    git(seat, "commit", "-qm", "seat work")
    return git(seat, "rev-parse", "HEAD")


def run(capsys, **kw):
    code = push.land(say=print, **kw)
    return code, capsys.readouterr().out


def test_a_push_lands(seat, capsys):
    path, other, origin, state = seat
    work(path)
    code, out = run(capsys)
    assert code == 0, out
    assert git(origin, "rev-parse", "master") == git(path, "rev-parse", "HEAD")
    assert "attempt 1: landed 1 commit(s)" in out
    assert (state / "hook-count").read_text().strip() == "1"


def test_a_lost_race_is_retried_at_once_and_lands(seat, capsys):
    path, other, origin, state = seat
    tip = work(path)
    (state / "race").write_text("1")              # another seat lands during the first hook
    started = time.time()
    code, out = run(capsys)
    assert code == 0, out
    assert "attempt 1: lost the race" in out and "attempt 2: landed" in out
    assert (state / "hook-count").read_text().strip() == "2", (state / "hook-env").read_text() + out
    master = git(origin, "log", "--format=%s", "master")
    assert master.splitlines()[:2] == ["seat work", "other seat 0"]
    # each retry names the tip it rebased from, so the hook's receipts carry
    env = (state / "hook-env").read_text().splitlines()
    assert env[0] == "previous=" and env[1].startswith("previous=") and env[1] != "previous="
    assert env[1] == f"previous={tip}"
    assert time.time() - started < 60


def test_only_the_retry_after_a_lost_race_is_flagged_as_one(seat, capsys, monkeypatch):
    # master moved before the first attempt, so its rebase changes HEAD and it
    # already carries the receipt hint BFME_PUSH_PREVIOUS; only the retry after
    # the lost race carries BFME_PUSH_LOST_RACE, which the hook's retry window
    # keys on (a first attempt must not take the window).
    monkeypatch.delenv("BFME_PUSH_LOST_RACE", raising=False)
    path, other, origin, state = seat
    work(path)
    (other / "early.txt").write_text("early\n")
    git(other, "add", "early.txt")
    git(other, "commit", "-qm", "other seat early")
    git(other, "push", "-q", "origin", "HEAD:master")
    (state / "race").write_text("1")              # and another lands during the first hook
    code, out = run(capsys)
    assert code == 0, out
    assert "attempt 1: lost the race" in out and "attempt 2: landed" in out
    env = (state / "hook-env").read_text().splitlines()
    assert env[0] != "previous=", "the first rebase moved HEAD: a receipt hint"
    assert (state / "hook-lost").read_text().splitlines() == ["lost_race=", "lost_race=1"]


def test_an_exported_lost_race_flag_never_marks_a_first_attempt(seat, capsys, monkeypatch):
    # a shell that once exported BFME_PUSH_LOST_RACE=1 must not make a later,
    # unrelated first attempt look like a retry (it would take the landing window)
    monkeypatch.setenv("BFME_PUSH_LOST_RACE", "1")
    path, other, origin, state = seat
    work(path)
    code, out = run(capsys)
    assert code == 0, out
    assert (state / "hook-lost").read_text().splitlines() == ["lost_race="]


def test_after_lost_race_marks_a_drivers_own_retry(seat, capsys, monkeypatch):
    # a driver that runs its own retries (push.py --tries 1 in a loop) says so per
    # invocation; the flag reaches the hook on that run's first attempt
    monkeypatch.delenv("BFME_PUSH_LOST_RACE", raising=False)
    path, other, origin, state = seat
    work(path)
    code = push.main(["--tries", "1", "--after-lost-race", "--email", EMAIL])
    out = capsys.readouterr().out
    assert code == 0, out
    assert (state / "hook-lost").read_text().splitlines() == ["lost_race=1"]


def test_a_real_refusal_stops_without_retrying(seat, capsys):
    path, other, origin, state = seat
    work(path)
    (state / "refuse").write_text("")
    code, out = run(capsys)
    assert code == 1
    assert "refused" in out and "not retrying" in out
    assert (state / "hook-count").read_text().strip() == "1"
    assert git(origin, "rev-parse", "master") != git(path, "rev-parse", "HEAD")


@pytest.mark.parametrize("who", ["author", "committer", "config"])
def test_a_wrong_identity_is_refused_before_pushing(seat, capsys, who):
    path, other, origin, state = seat
    if who == "config":
        git(path, "config", "user.email", "someone@example.com")
        work(path)
    else:
        env = dict(os.environ)
        env["GIT_AUTHOR_EMAIL" if who == "author" else "GIT_COMMITTER_EMAIL"] = "someone@example.com"
        (path / "work.txt").write_text("x")
        git(path, "add", "work.txt")
        git(path, "commit", "-qm", "foreign", env=env)
    with pytest.raises(push.Refused):
        push.land(say=print)
    assert not (state / "hook-count").exists()


def test_the_landing_window_wait_is_honoured(seat, capsys):
    # the hook (pre-push) waits for another seat's landing window; push.py lets it
    path, other, origin, state = seat
    work(path)
    (state / "lease").write_text("2")
    started = time.time()
    code, out = run(capsys)
    assert code == 0, out
    assert time.time() - started >= 2
    assert (state / "hook-count").read_text().strip() == "1"


def test_the_same_account_spacing_holds_before_the_first_attempt(seat, capsys, monkeypatch, tmp_path):
    path, other, origin, state = seat
    work(path)
    monkeypatch.setenv("BFME_PUSH_SPACING_S", "3")
    (tmp_path / "clock").write_text(f"{int(time.time())}\n")
    started = time.time()
    code, out = run(capsys)
    assert code == 0, out
    assert time.time() - started >= 2
    assert "waiting" in out
    assert float((tmp_path / "clock").read_text()) >= started


def test_a_retry_waits_when_the_race_was_lost_to_the_same_account(seat, capsys, monkeypatch):
    path, other, origin, state = seat
    work(path)
    monkeypatch.setenv("BFME_PUSH_SPACING_S", "3")
    (state / "race").write_text("1")
    (state / "same-account").write_text("")
    started = time.time()
    code, out = run(capsys)
    assert code == 0, out
    assert "attempt 1: lost the race" in out and "waiting" in out and "attempt 2: landed" in out
    assert time.time() - started >= 2


def test_the_spacing_rereads_the_clock_after_sleeping(tmp_path, monkeypatch):
    # another seat of the account lands while this one sleeps: wait out its push too
    clock = tmp_path / "clock"
    monkeypatch.setenv("BFME_PUSH_CLOCK", str(clock))
    monkeypatch.setenv("BFME_PUSH_SPACING_S", "300")
    clock.write_text("800\n")
    now = [1000.0]

    def sleep(seconds):
        if now[0] == 1000.0:
            clock.write_text("1050\n")
        now[0] += seconds

    monkeypatch.setattr(push, "time", types.SimpleNamespace(time=lambda: now[0], sleep=sleep))
    push.wait_for_spacing(lambda line: None)
    assert now[0] >= 1050 + 300


def test_nothing_to_push(seat, capsys):
    code, out = run(capsys)
    assert code == 0 and "nothing to push" in out
