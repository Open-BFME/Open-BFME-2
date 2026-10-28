"""tools/tier_tuning.py: the self-tuning default-pick shares next_work.tier_weights serves."""

import collections
import os
import random
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import next_work
import tier_tuning as tt

PRIORS = dict(next_work.TIER_WEIGHTS)
HOUR = 3600
T0 = 1_800_000_000


def measurement(**yields):
    base = {"consolidate": 0, "data": 0, "identity": 0, "header": 0}
    base.update(yields)
    return {"version": tt.MEASURE_VERSION, "sha": "f" * 40, "start": "e" * 40, "hours": tt.WINDOW_HOURS,
            "source_gap": 20000, "files_at_start": 22000, "tus": 2000, "debt_gap": 100000, "yield": base}


@pytest.fixture(autouse=True)
def tuning_on(monkeypatch):
    monkeypatch.delenv("BFME_TIER_TUNING", raising=False)
    monkeypatch.delenv("BFME_TIER_WEIGHTS", raising=False)


# ---- allocation: bounds, sum, determinism

@pytest.mark.parametrize("yields", [{}, {"consolidate": 1500, "data": 750, "identity": 230, "header": 520},
                                    {"consolidate": 10_000}, {"data": 5000}, {"header": 1}])
def test_shares_sum_to_100_within_the_band(yields):
    rows = tt.allocate(PRIORS, measurement(**yields))
    weights = {t: r["weight"] for t, r in rows.items()}
    assert set(weights) == set(PRIORS)
    assert round(sum(weights.values()), 6) == 100
    for tier, prior in PRIORS.items():                       # tenths rounding may cross by 0.1
        assert tt.BAND[0] * prior - 0.1 <= weights[tier] <= tt.BAND[1] * prior + 0.1, (tier, weights[tier])


def test_no_movement_or_no_measurement_keeps_the_priors():
    for m in (measurement(), None, {"error": "no history"}):
        rows = tt.allocate(PRIORS, m)
        assert {t: r["weight"] for t, r in rows.items()} == {t: float(p) for t, p in PRIORS.items()}


def test_a_yielding_tier_gains_and_a_stalled_one_loses():
    rows = tt.allocate(PRIORS, measurement(consolidate=1500, data=750, identity=230, header=520))
    assert rows["consolidate"]["weight"] > PRIORS["consolidate"]
    assert rows["header"]["weight"] < PRIORS["header"]
    assert rows["link"]["yield"] is None and rows["link"]["multiplier"] == 1.0   # unmeasured: prior


def test_allocation_is_deterministic():
    m = measurement(consolidate=1234, data=99, header=7)
    assert tt.allocate(PRIORS, m) == tt.allocate(dict(reversed(list(PRIORS.items()))), m)


# ---- kill switch

def test_the_kill_switch_restores_the_priors(monkeypatch):
    monkeypatch.setattr(tt, "cached_measure", lambda *a, **k: measurement(consolidate=9000))
    tuned, rows, _ = tt.weights(PRIORS)
    assert rows and tuned != PRIORS
    monkeypatch.setenv("BFME_TIER_TUNING", "off")
    assert tt.weights(PRIORS) == (PRIORS, None, "BFME_TIER_TUNING=off: static priors")
    assert next_work.tier_weights() == PRIORS
    monkeypatch.delenv("BFME_TIER_TUNING")
    monkeypatch.setenv("BFME_TIER_WEIGHTS", "link=40")                 # an explicit override: no tuning
    assert next_work.tier_weights() == {**PRIORS, "link": 40}


# ---- zero queue: the fallthrough redistributes pro rata

def test_an_empty_queue_shares_out_pro_rata(monkeypatch):
    monkeypatch.setattr(tt, "cached_measure", lambda *a, **k: measurement(consolidate=1500, data=750))
    weights = next_work.tier_weights()
    monkeypatch.setattr(next_work, "tier_weights", lambda: weights)        # one measurement, many draws
    empty = {"consolidate", "stubs"}
    rng = random.Random(7)
    firsts = collections.Counter()
    draws = 20000
    for _ in range(draws):
        firsts[next(t for t in next_work.debt_order(rng)[1:] if t not in empty)] += 1
    live = sum(w for t, w in weights.items() if t not in empty)
    assert not firsts.keys() & empty
    for tier, weight in weights.items():
        if tier not in empty:
            assert abs(firsts[tier] / draws - weight / live) < 0.015, tier


# ---- measurement on a real git history

def git(repo, *args, when=None):
    env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_AUTHOR_EMAIL="t@t", GIT_COMMITTER_NAME="t",
               GIT_COMMITTER_EMAIL="t@t")
    if when is not None:
        env["GIT_AUTHOR_DATE"] = env["GIT_COMMITTER_DATE"] = f"@{when} +0000"
    return subprocess.run(["git", *args], cwd=repo, env=env, check=True, capture_output=True, text=True).stdout


def commit(repo, when, files=(), delete=(), msg="c"):
    for path, text in dict(files).items():
        (repo / path).parent.mkdir(parents=True, exist_ok=True)
        (repo / path).write_text(text)
    for path in delete:
        (repo / path).unlink()
    git(repo, "add", "-A")
    git(repo, "commit", "-q", "--allow-empty", "-m", msg, when=when)


@pytest.fixture
def repo(tmp_path):
    repo = tmp_path / "r"
    repo.mkdir()
    git(repo, "init", "-q", "-b", "master")
    tus = "rva,size,kind,tu,confidence,by,evidence,source\n" + "".join(
        f"0x{i:08X},1,code,Code/T{i % 2}.cpp,approved,F,,Code/F{i}.cpp\n" for i in range(10))
    commit(repo, T0, {**{f"Code/F{i}.cpp": f"// {i}\n" for i in range(10)}, tt.TU_MAP: tus,
                      tt.REGISTERS["data"]: "# header\n" + "".join(f"Code/F{i}.cpp\tk\tn\t0x{i}\n" for i in range(6)),
                      tt.REGISTERS["identity"]: "# header\n", tt.REGISTERS["header"]: "class\tsource\n",
                      tt.GATE_BASELINE: "", tt.HATCH_BASELINE: "# h\npin\tCode/F0.cpp\tx\t4\n"})
    return repo


def test_measure_counts_net_removals_and_register_shrink(repo, tmp_path):
    t = T0 + 20 * HOUR
    commit(repo, t, {"Code/T0.cpp": "// merged\n"}, delete=["Code/F0.cpp", "Code/F2.cpp", "Code/F4.cpp"])
    commit(repo, t + 1, {"Code/G.cpp": "x"}, delete=["Code/F1.cpp"])                     # a move: 0
    text = (repo / tt.REGISTERS["data"]).read_text().splitlines(keepends=True)
    commit(repo, t + 2, {tt.REGISTERS["data"]: "".join(text[:-2])})                       # 2 keys retired
    commit(repo, T0 + 60 * HOUR)
    m = tt.measure("HEAD", repo)
    assert m["yield"] == {"consolidate": 2, "data": 2, "identity": 0, "header": 0}
    # window: the first commit is >48 h before the tip, so it is the start
    assert m["files_at_start"] == 10 and m["tus"] == 2 and m["source_gap"] == 8
    assert m["debt_gap"] == 6 + 4
    cache = tmp_path / "commits.json"
    start, end = m["start"], git(repo, "rev-parse", "HEAD").strip()
    assert tt.commit_removals(repo, start, end, cache) == 2 == tt.commit_removals(repo, start, end, cache)


def test_a_short_history_is_not_measured(repo):
    commit(repo, T0 + HOUR)
    assert "error" in tt.measure("HEAD", repo)


def test_cheap_commits_without_headline_movement_gain_nothing(repo):
    """Gaming: a tier lands 40 commits -- files moved, registers churned (a key removed
    and added back), edits -- and no headline moves: its share cannot rise."""
    when = T0 + 20 * HOUR
    for i in range(40):
        when += 60
        if i % 4 == 0:
            commit(repo, when, {f"Code/M{i}.cpp": "x"}, delete=[f"Code/F{i // 4}.cpp"])    # move
        elif i % 4 == 1:
            commit(repo, when, {f"Code/M{i - 1}.cpp": "y"})                              # edit
        elif i % 4 == 2:
            path = repo / tt.REGISTERS["header"]
            commit(repo, when, {tt.REGISTERS["header"]: path.read_text() + f"C{i}\tCode/x.cpp\n"})
        else:
            path = repo / tt.REGISTERS["header"]
            commit(repo, when, {tt.REGISTERS["header"]: "".join(path.read_text().splitlines(True)[:-1])})
    commit(repo, T0 + 60 * HOUR)
    m = tt.measure("HEAD", repo)
    assert m["yield"]["consolidate"] == 0 and m["yield"]["header"] == 0
    rows = tt.allocate(PRIORS, m)
    assert rows["consolidate"]["weight"] <= PRIORS["consolidate"]
    assert rows["header"]["weight"] <= PRIORS["header"]
