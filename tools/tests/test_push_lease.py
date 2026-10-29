"""The landing window (tools/push_lease.py): one full-gate push to master lands
at a time, everyone else waits its turn, and nothing blocks past the TTL.

Two hosts against a local bare origin, as in test_claims.py: no test reaches a
network or this checkout's origin.
"""
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
HOOK = TOOLS.parent / ".githooks" / "pre-push"
sys.path.insert(0, str(TOOLS))

import claims  # noqa: E402
import push_lease  # noqa: E402

SHA = "a" * 40


def _git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout


@pytest.fixture
def hosts(tmp_path, monkeypatch):
    origin = tmp_path / "origin.git"
    _git(tmp_path, "init", "-q", "--bare", str(origin))
    clones = {}
    for name in ("a", "b"):
        clone = tmp_path / name
        _git(tmp_path, "init", "-q", str(clone))
        _git(clone, "remote", "add", "origin", str(origin))
        _git(clone, "config", "user.name", name)
        _git(clone, "config", "user.email", f"{name}@example.com")
        clones[name] = clone
    monkeypatch.delenv("BFME_RUN_ID", raising=False)
    monkeypatch.setattr(claims, "NS", "refs/claims/")
    monkeypatch.setattr(claims, "REMOTE", "origin")
    monkeypatch.setattr(push_lease.time, "sleep", lambda s: None)

    def act(name):
        monkeypatch.setattr(claims, "ROOT", clones[name])
        monkeypatch.setenv("BFME_CLAIM_OWNER", name)
        claims.active.cache_clear()
        claims.mirrored.cache_clear()
        assert Path(claims._git("remote", "get-url", "origin").stdout.strip()) == origin
        return clones[name]
    act.origin = origin
    return act


def quiet(*args, **kwargs):
    pass


def test_the_landing_lease_key():
    assert push_lease.KEY == "lease/landing"
    assert claims.ref_of(push_lease.KEY) == claims.NS + "lease/landing"
    assert push_lease.MINUTES == 30 or "BFME_LANDING_LEASE_MINUTES" in os.environ


def test_one_full_gate_push_holds_the_window_at_a_time(hosts):
    hosts("a")
    token = push_lease.acquire(SHA, say=quiet)
    assert token
    owner, expires, sha = push_lease.holder()
    assert owner == "a" and sha == SHA
    hosts("b")
    # b's turn does not come while a holds it; with no wait left it gives up
    # (and lands without the window) rather than failing the push
    told = []
    assert push_lease.acquire("b" * 40, wait_minutes=0, say=told.append) is None
    assert any("landing without it" in line for line in told)
    told.clear()
    assert push_lease.wait(wait_minutes=0, say=told.append) is False
    assert any("a still holds the landing window" in line and "until" in line for line in told)
    hosts("a")
    assert push_lease.release(token)
    hosts("b")
    assert push_lease.wait(wait_minutes=0, say=quiet) is True
    assert push_lease.acquire("b" * 40, wait_minutes=0, say=quiet)
    assert push_lease.holder()[0] == "b"


def test_a_waiter_is_told_who_holds_it_and_until_when(hosts, monkeypatch):
    hosts("a")
    assert push_lease.acquire(SHA, say=quiet)
    hosts("b")
    polls, told = [], []
    monkeypatch.setattr(push_lease.time, "sleep", lambda s: polls.append(s))
    assert push_lease.wait(wait_minutes=0.0001, poll=0.001, say=told.append) is False
    assert re.search(r"a is landing a full-gate push \(aaaaaaaaaa\); waiting until it lands or \d\d:\d\d:\d\d",
                     told[0])


def test_the_holder_never_waits_for_itself_and_renews_on_retry(hosts):
    hosts("a")
    first = push_lease.acquire(SHA, say=quiet)
    assert push_lease.wait(wait_minutes=0, say=quiet) is True
    # the holder lost the race and retries with its rebased commit
    assert first and push_lease.acquire("c" * 40, wait_minutes=0, say=quiet)
    assert push_lease.holder()[0] == "a" and push_lease.holder()[2] == "c" * 40


def test_a_crashed_holder_blocks_no_one_past_the_ttl(hosts):
    hosts("a")
    assert push_lease.acquire(SHA, minutes=-1, say=quiet)       # already expired: a crashed holder
    hosts("b")
    assert push_lease.holder() is None
    assert push_lease.wait(wait_minutes=0, say=quiet) is True
    assert push_lease.acquire("b" * 40, wait_minutes=0, say=quiet)
    assert push_lease.holder()[0] == "b"


def test_a_landed_window_counts_as_free(hosts):
    # the holder keeps the window through git's push; once origin/master holds
    # its commit, waiters go ahead without waiting for a release or the TTL
    clone = hosts("a")
    (clone / "f").write_text("x")
    _git(clone, "add", "f")
    _git(clone, "commit", "-qm", "landed")
    pushed = _git(clone, "rev-parse", "HEAD").strip()
    assert push_lease.acquire(pushed, say=quiet)
    hosts("b")
    assert push_lease.wait(wait_minutes=0, say=quiet) is False      # not on master yet
    hosts("a")
    _git(clone, "push", "-q", "origin", "HEAD:refs/heads/master")
    hosts("b")
    assert push_lease.wait(wait_minutes=0, say=quiet) is True


def test_only_the_holder_releases_and_a_stale_token_cannot(hosts):
    hosts("a")
    old = push_lease.acquire(SHA, minutes=-1, say=quiet)
    hosts("b")
    new = push_lease.acquire("b" * 40, wait_minutes=0, say=quiet)
    assert not push_lease.release(new.replace(new[0], "0" if new[0] != "0" else "1"))
    hosts("a")
    assert not push_lease.release(old)                      # taken over since
    assert push_lease.holder()[0] == "b"


def test_a_waiter_proceeds_once_the_holder_releases(hosts, monkeypatch):
    hosts("a")
    token = push_lease.acquire(SHA, say=quiet)
    hosts("b")
    polls = []

    def release_on_second_poll(seconds):
        polls.append(seconds)
        if len(polls) == 2:
            hosts("a")
            assert push_lease.release(token)
            hosts("b")
    monkeypatch.setattr(push_lease.time, "sleep", release_on_second_poll)
    assert push_lease.wait(wait_minutes=60, say=quiet) is True
    assert len(polls) == 2


def test_unreachable_claims_fail_open(hosts, monkeypatch):
    hosts("a")
    monkeypatch.setattr(claims, "fetch", lambda root=None: False)
    assert push_lease.acquire(SHA, say=quiet) is None
    assert push_lease.wait(say=quiet) is False


def test_the_window_is_invisible_to_body_pickers(hosts):
    hosts("a")
    assert push_lease.acquire(SHA, say=quiet)
    assert claims.busy_rvas() == set()
    assert claims.key_of("lease:landing") in claims.active()


# --- the hook: release on failure, keep through a passing push -----------------

def _bash():
    """Git-for-Windows Bash, not the WindowsApps/WSL shim a bare `bash` finds."""
    candidates = []
    if os.name == "nt":
        git = shutil.which("git")
        if git:
            git_root = Path(git).resolve().parent.parent
            candidates += [git_root / "bin/bash.exe", git_root / "usr/bin/bash.exe"]
        program_files = Path(os.environ.get("ProgramFiles", r"C:\Program Files"))
        candidates += [program_files / "Git/bin/bash.exe", program_files / "Git/usr/bin/bash.exe"]
    if shutil.which("bash"):
        candidates.append(Path(shutil.which("bash")))
    for candidate in candidates:
        if Path(candidate).is_file():
            return str(candidate)
    pytest.skip("Bash is required to exercise the hook")


STUB = """import sys
open('calls', 'a').write(' '.join(sys.argv[1:]) + '\\n')
if sys.argv[1] == 'acquire':
    print('TOKEN')
if sys.argv[1] == 'renew':
    print('TOKEN%d' % sum(1 for line in open('calls') if line.startswith('renew')))
"""


def landing_hook(tmp_path, outcome, env=None):
    """The hook's landing-window helpers around a stub push_lease.py: take the
    window, then run `outcome` (pass: landing_ok=1; fail; or shell text);
    returns the run and the calls the stub saw. Each renewal issues a new token."""
    text = HOOK.read_text(encoding="utf-8")
    helpers = text[text.index('LANDING_TOKEN=""'):text.index("# full_gate_pool:")]
    stub = tmp_path / "tools" / "push_lease.py"
    stub.parent.mkdir()
    stub.write_text(STUB, newline="\n")
    body = {"pass": "landing_ok=1\n", "fail": "exit 1\n"}.get(outcome, outcome)
    script = tmp_path / "hook.sh"
    script.write_text(f"_remote_ref=refs/heads/master\n{helpers}\ntake_landing_window {SHA}\n{body}",
                      newline="\n")
    done = subprocess.run([_bash(), "--noprofile", "--norc", script.as_posix()], cwd=tmp_path,
                          capture_output=True, text=True, env=dict(os.environ, **(env or {})))
    return done, (tmp_path / "calls").read_text().split("\n")[:-1]


def test_the_hook_releases_the_window_when_it_fails(tmp_path):
    done, calls = landing_hook(tmp_path, "fail")
    assert done.returncode == 1
    assert calls == [f"acquire {SHA}", "release TOKEN"]


def test_the_hook_keeps_the_window_through_a_passing_push(tmp_path):
    done, calls = landing_hook(tmp_path, "pass")
    assert done.returncode == 0, done.stderr
    assert calls == [f"acquire {SHA}"]
    assert "holding the landing window" in done.stdout


def test_the_holder_renews_the_window_through_a_long_gate(tmp_path):
    # a full gate outlasting the TTL keeps the window; a failure releases the
    # latest token, since each renewal replaces it
    done, calls = landing_hook(tmp_path, "sleep 4\nexit 1\n", {"BFME_LANDING_HEARTBEAT_SECONDS": "1"})
    assert done.returncode == 1
    renewals = [c for c in calls if c.startswith("renew")]
    assert calls[0] == f"acquire {SHA}" and len(renewals) >= 2
    assert all(c == f"renew {SHA}" for c in renewals)
    assert calls[-1] == f"release TOKEN{len(renewals)}"


def test_the_heartbeat_stops_when_the_hook_exits(tmp_path):
    import time
    done, calls = landing_hook(tmp_path, "sleep 2\nlanding_ok=1\n", {"BFME_LANDING_HEARTBEAT_SECONDS": "1"})
    assert done.returncode == 0, done.stderr
    time.sleep(3)
    assert (tmp_path / "calls").read_text().split("\n")[:-1] == calls
    assert not any(c.startswith("release") for c in calls)


class Clock:
    """time.time advancing `step` seconds per sleep, for claims and push_lease alike."""
    def __init__(self, step):
        self.now, self.step = 1_800_000_000.0, step

    def time(self):
        return self.now


def test_a_waiter_follows_a_renewed_window_past_its_first_expiry(hosts, monkeypatch):
    clock = Clock(20 * 60)
    monkeypatch.setattr(push_lease.time, "time", clock.time)
    hosts("a")
    tokens = [push_lease.acquire(SHA, say=quiet)]            # expires in 30 min
    hosts("b")
    polls, told = [], []

    def renew_then_release(seconds):
        clock.now += clock.step
        polls.append(seconds)
        hosts("a")
        if len(polls) < 3:
            tokens.append(push_lease.renew(SHA))             # the holder's heartbeat
            assert tokens[-1]
        else:
            assert push_lease.release(tokens[-1])
        hosts("b")
    monkeypatch.setattr(push_lease.time, "sleep", renew_then_release)
    # 60 minutes in, past the window's first expiry, the waiter is still waiting
    assert push_lease.wait(say=told.append) is True
    assert len(polls) == 3
    assert any("(renewed)" in line for line in told)


def test_a_waiter_gives_up_at_the_hard_cap(hosts, monkeypatch):
    clock = Clock(20 * 60)
    monkeypatch.setattr(push_lease.time, "time", clock.time)
    hosts("a")
    assert push_lease.acquire(SHA, say=quiet)
    hosts("b")

    def renew_forever(seconds):
        clock.now += clock.step
        hosts("a")
        assert push_lease.renew(SHA)
        hosts("b")
    monkeypatch.setattr(push_lease.time, "sleep", renew_forever)
    told = []
    started = clock.now
    assert push_lease.wait(wait_minutes=90, say=told.append) is False
    assert 90 * 60 <= clock.now - started <= 110 * 60
    assert "still holds the landing window after 90 min" in told[-1]


def test_the_holder_cannot_renew_a_window_another_seat_holds(hosts):
    hosts("a")
    assert push_lease.acquire(SHA, say=quiet)
    hosts("b")
    assert push_lease.renew("b" * 40) is None
    assert push_lease.holder()[0] == "a"
