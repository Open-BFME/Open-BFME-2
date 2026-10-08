"""BFME2 shared claims as refs on origin, two hosts against a bare repo."""
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import claims  # noqa: E402


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

    def act(name):
        monkeypatch.setattr(claims, "ROOT", clones[name])
        monkeypatch.setenv("BFME_CLAIM_OWNER", name)
        claims.active.cache_clear()
    return act


def test_a_claim_is_exclusive_across_hosts(hosts):
    hosts("a")
    assert claims.claim([0x100, 0x200]) == ([0x100, 0x200], [])
    hosts("b")
    assert set(claims.active()) == {0x100, 0x200}
    assert claims.claim([0x200, 0x300]) == ([0x300], [0x200])     # partial batch
    assert claims.active()[0x300]["owner"] == "b"


def test_only_the_owner_releases(hosts):
    hosts("a")
    claims.claim([0x100])
    hosts("b")
    assert claims.release([0x100]) == []
    assert 0x100 in claims.active()
    hosts("a")
    assert claims.release([0x100]) == [0x100]
    assert claims.active() == {}


def test_an_expired_claim_can_be_taken_over(hosts):
    hosts("a")
    claims.claim([0x100], ttl_hours=-1)                            # already expired
    hosts("b")
    assert claims.active() == {}
    assert claims.claim([0x100]) == ([0x100], [])
    assert claims.active()[0x100]["owner"] == "b"


def test_renewing_your_own_claim_succeeds(hosts):
    hosts("a")
    claims.claim([0x100])
    assert claims.claim([0x100]) == ([0x100], [])


def test_an_unreachable_origin_blocks_nothing(hosts, monkeypatch):
    hosts("a")
    monkeypatch.setattr(claims, "REMOTE", "no-such-remote")
    assert claims.active() == {}
    assert claims.claim([0x100]) == ([], [])


def test_batch_release_uses_one_atomic_push(hosts, monkeypatch):
    hosts("a")
    assert claims.claim([0x100, 0x200, 0x300])[0] == [0x100, 0x200, 0x300]
    original_git = claims._git
    pushes = []

    def traced_git(*args, **kwargs):
        if args[0] == "push":
            pushes.append(args)
        return original_git(*args, **kwargs)

    monkeypatch.setattr(claims, "_git", traced_git)
    assert claims.release([0x100, 0x200, 0x300]) == [0x100, 0x200, 0x300]
    assert len(pushes) == 1
    assert "--atomic" in pushes[0]
    assert claims.active() == {}


def test_claim_markers_pass_the_repository_push_hook(hosts):
    hosts("a")
    hooks = claims.ROOT / ".githooks"
    hooks.mkdir()
    shutil.copy2(TOOLS.parent / ".githooks" / "pre-push", hooks / "pre-push")
    assert claims.claim([0x400]) == ([0x400], [])


def test_main_pickers_hide_busy_retail_addresses():
    import next_work
    import list_naked_candidates

    work = [{"target_rva": "0x00000100"}, {"candidate_rva": "0x00000200"},
            {"target_rva": "0x00000300"}]
    assert next_work.without_busy(work, {0x100, 0x200}) == work[2:]
    naked = [{"rva": "0x00000100"}, {"rva": "0x00000300"}]
    assert list_naked_candidates.without_busy(naked, {0x100}) == naked[1:]


def test_main_pickers_retry_when_a_peer_claimed_the_first_draw(monkeypatch):
    import next_work
    import list_naked_candidates as naked_queue

    def claim(rvas, **_kwargs):
        rva = rvas[0]
        return ([], [rva]) if rva == 0x100 else ([rva], [])

    monkeypatch.setattr(claims, "claim", claim)
    monkeypatch.setattr(next_work, "weighted_choice", lambda candidates: candidates[0])
    work = [{"target_rva": "0x00000100"}, {"target_rva": "0x00000200"}]
    assert next_work.claim_choice(work, "test") == (work[1], [0x200])

    monkeypatch.setattr(naked_queue, "select_candidate",
                        lambda candidates: (candidates[0], {"pool": len(candidates)}))
    naked = [{"rva": "0x00000100"}, {"rva": "0x00000200"}]
    assert naked_queue.claim_choice(naked) == (naked[1], {"pool": 1}, [0x200])


def test_scope_claims_are_exclusive_and_invisible_to_pickers(hosts):
    hosts("a")
    got, refused = claims.claim(["class:RenderObjClass", "file:Code/A/B.cpp", "0x100"])
    assert refused == [] and len(got) == 3
    hosts("b")
    live = claims.active()
    assert "class/RenderObjClass" in live and live["class/RenderObjClass"]["scope"] == "RenderObjClass"
    assert live[claims.key_of("file:Code/A/B.cpp")]["scope"] == "Code/A/B.cpp"
    assert claims.busy_rvas() == {0x100}                         # pickers see RVAs only
    assert claims.claim(["class:RenderObjClass"]) == ([], ["class/RenderObjClass"])
    hosts("a")
    assert sorted(claims.release(["class:RenderObjClass", "file:Code/A/B.cpp"])) == \
        sorted(["class/RenderObjClass", claims.key_of("file:Code/A/B.cpp")])


def test_qualified_class_claim_round_trips_and_is_exclusive(hosts):
    scope = "class:StrategicHUD::BattlePromptArmyPanelMovieClip::Impl"
    key = claims.key_of(scope)
    assert ":" not in claims.ref_of(key)
    assert key != claims.key_of("class:StrategicHUD__BattlePromptArmyPanelMovieClip__Impl")
    hosts("a")
    assert claims.claim([scope]) == ([key], [])
    hosts("b")
    live = claims.active()
    assert live[key]["scope"] == scope[6:]
    assert claims.label(key, live[key]) == scope
    assert claims.busy_rvas() == set()
    assert claims.claim([scope]) == ([], [key])
    assert claims.release([scope]) == []
    hosts("a")
    assert claims.claim([scope]) == ([key], [])
    assert claims.release([scope]) == [key]
    assert claims.active() == {}


@pytest.mark.parametrize("name", ["", "::Impl", "HUD::", "HUD:::Impl", "HUD:Impl",
                                  "HUD::A/B", "HUD::A.lock", "HUD::A%3A%3AB"])
def test_invalid_qualified_names_cannot_escape_the_ref_namespace(name):
    with pytest.raises(ValueError):
        claims.key_of("class:" + name)
