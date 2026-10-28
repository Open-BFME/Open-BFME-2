#!/usr/bin/env python3
"""Self-tuning shares for next_work.py's default pick (called by next_work.tier_weights).

WHY. The shares in next_work.TIER_WEIGHTS were set by hand and went stale: the
consolidate share sat at 7 while merges were the source-recovery figure, until it was
raised to 20 by hand. Here each share moves, within a band around its hand-set prior,
toward the tiers whose landings moved a headline figure in the last WINDOW_HOURS.

YIELD, NOT ACTIVITY. A tier's yield is read from ledger state on origin/master, never
from commits, subjects, trailers or markers:
  consolidate  Code/ source files (.cpp/.c/.asm, progress.py's SOURCE FILES rule) that
               commits removed net: per commit, deletions minus additions when positive,
               so a move or a split scores 0; the sum is capped at the window's real drop
               in source files, so a file restored and removed again earns nothing. As a
               fraction of the source gap at the window's start (files minus the TUs the
               start's reverse/tu_map.csv names).
  data         keys the shrink-only register lost over the window (start minus end,
  identity     never below 0), as a fraction of the debt headline at the window's start
               (gate baseline + data, identity and header registers + hatch counts).
The other tiers keep their prior (multiplier 1) because no ledger diff attributes their
landings to them: linked bytes come only from the census, which measures the whole
fleet (every tier links units); stubs come from a local link cycle; tu_map approval also
moves with renames and map rebuilds; ms-headers, dx and stlport retire no headline debt.
The header tier's main yield is the TU merges a canonical header unblocks, which land as
consolidate removals; its own queue keys undercount it, so it keeps its prior too.
UNMEASURED says why for each.

ALLOCATION. Seat-hours are taken as proportional to the prior, so a measured tier's
efficiency is yield / prior and its multiplier sqrt(efficiency / mean efficiency of the
measured tiers), clamped to BAND. The prior is the denominator even while tuned shares
are in force; with the square root that converges to multiplier = relative efficiency
(clamped) instead of running away. The shares are then scaled together to sum to 100,
each kept in [BAND[0]*prior, BAND[1]*prior], and rounded to tenths (exact sum 100).
A tier with an empty or fully claimed queue already gets nothing: next_work's draw falls
through it to the next drawn queue, which is exactly a proportional redistribution.

DETERMINISTIC AND CHEAP. Inputs are git objects reachable from one commit (origin/master,
else HEAD) and the window ends at that commit's committer time, so every seat on the same
SHA computes the same shares. One measurement (a git log and a few blob reads) is cached
in build/tier_tuning/<sha>.json, and each commit's removal count in commits.json; both are
written atomically and a cache entry is used only if it validates (same SHA, version,
window and schema). A git failure is a measurement error (priors, never cached), not an
empty register.

KILL SWITCH. BFME_TIER_TUNING=off (or next_work.py --static-weights) restores the priors;
an explicit BFME_TIER_WEIGHTS override also turns tuning off.
"""

import collections
import json
import math
import os
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CACHE = ROOT / "build" / "tier_tuning"
MEASURE_VERSION = 2
WINDOW_HOURS = 48            # two days of landings: one big merge batch moves a share, not the fleet
BAND = (0.5, 2.0)            # a share stays within half to twice its hand-set prior
SOURCE_SUFFIXES = (".cpp", ".c", ".asm")
TU_MAP = "reverse/tu_map.csv"
GATE_BASELINE = "reverse/gate_baseline.txt"
HATCH_BASELINE = "reverse/hatch_baseline.tsv"
# tier -> the shrink-only register whose lost keys are its yield (repair_queue.DEBT_QUEUES);
# all three count toward the debt gap, but only MEASURED tiers are tuned by them
REGISTERS = {"data": "reverse/data_check_baseline.txt", "identity": "reverse/code_identity_baseline.tsv",
             "header": "reverse/header_queue.tsv"}
MEASURED = ("consolidate", "data", "identity")
UNMEASURED = {
    "header": "its yield is mostly the TU merges a header unblocks (credited to consolidate); "
              "queue keys retired undercount it",
    "link": "linked bytes are census-only and fleet-wide; no per-tier attribution",
    "stubs": "stub count comes from a local link cycle, not origin/master",
    "tu-approval": "tu_map approval also moves with renames and map rebuilds",
    "tu-evidence": "places sources in tu_map; no headline of its own",
    "ms-headers": "cleanup queue, not a headline register",
    "dx": "cleanup queue, not a headline register",
    "stlport": "cleanup queue, not a headline register",
}
OFF_VALUES = {"0", "off", "no", "false", "static"}


def disabled():
    """Why tuning is off, or None."""
    if os.environ.get("BFME_TIER_TUNING", "").strip().lower() in OFF_VALUES:
        return "BFME_TIER_TUNING=off: static priors"
    if os.environ.get("BFME_TIER_WEIGHTS", "").strip():
        return "BFME_TIER_WEIGHTS set: explicit shares, tuning off"
    return None


# ---------------------------------------------------------------- measurement (git)

class MeasureError(Exception):
    """A git read that should have worked did not: the measurement is incomplete."""


def _git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")


def _ok(root, *args):
    run = _git(root, *args)
    if run.returncode:
        raise MeasureError(f"git {args[0]} failed: {run.stderr.strip()[:120]}")
    return run.stdout


def _blob(root, sha, path):
    """PATH's text at SHA; "" only when the tree has no such path (a register not yet
    created, or deleted). Any other failure is a MeasureError, never an empty register."""
    if not _ok(root, "ls-tree", sha, "--", path).strip():
        return ""
    return _ok(root, "show", f"{sha}:{path}")


def register_keys(text):
    """Keys in a register: non-blank lines that are neither comments nor a column header."""
    lines = [line for line in text.splitlines() if line.strip() and not line.startswith("#")]
    if lines and lines[0].startswith("class\t"):            # header_queue.tsv's column row
        lines = lines[1:]
    return len(lines)


def hatch_total(text):
    total = 0
    for line in text.splitlines():
        fields = line.split("\t")
        if line.startswith("#") or len(fields) < 4:
            continue
        total += int(fields[-1]) if fields[-1].strip().isdigit() else 0
    return total


def tu_count(text):
    lines = text.splitlines()
    if not lines:
        return 0
    col = lines[0].split(",").index("tu") if "tu" in lines[0].split(",") else 3
    return len({line.split(",")[col].lower() for line in lines[1:] if len(line.split(",")) > col
                and line.split(",")[col]})


def is_source(path):
    return path.startswith("Code/") and path.lower().endswith(SOURCE_SUFFIXES)


def source_count(root, sha):
    return sum(1 for p in _ok(root, "ls-tree", "-r", "--name-only", sha, "Code").splitlines() if is_source(p))


def _is_sha(value):
    return isinstance(value, str) and len(value) == 40 and all(c in "0123456789abcdef" for c in value)


def _is_count(value):
    return isinstance(value, int) and not isinstance(value, bool) and value >= 0


def _write_atomic(path, data):
    """Write JSON DATA to PATH through a temporary file and os.replace (never a torn file)."""
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        tmp = path.with_name(f"{path.name}.{os.getpid()}.tmp")
        tmp.write_text(json.dumps(data, sort_keys=True), encoding="utf-8")
        os.replace(tmp, path)
    except OSError:
        pass


def _read_commit_cache(cache):
    """{sha: count} from CACHE when every entry is valid under this MEASURE_VERSION, else {}."""
    try:
        got = json.loads(cache.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return {}
    counts = got.get("counts") if isinstance(got, dict) and got.get("version") == MEASURE_VERSION else None
    if not isinstance(counts, dict) or not all(_is_sha(k) and _is_count(v) for k, v in counts.items()):
        return {}
    return counts


def commit_removals(root, start, end, cache=None):
    """Code/ source files the first-parent commits START..END removed, each commit counted
    alone (deletions minus additions, when positive): a move or a split is 0. Churn across
    commits (a file restored, then removed again) is capped by measure(). A commit's count
    never changes, so counts are kept in CACHE/commits.json and only commits not seen before
    are diffed. Raises MeasureError when git fails."""
    cache = Path(cache) if cache else (CACHE / "commits.json" if root == ROOT else None)
    known = _read_commit_cache(cache) if cache and cache.exists() else {}
    shas = _ok(root, "rev-list", "--first-parent", f"{start}..{end}").split()
    fresh = [sha for sha in shas if sha not in known]
    if fresh:
        # Commits come newest first; one log back to the oldest unseen commit covers them all.
        log = _ok(root, "log", "--first-parent", "--no-renames", "--format=tformat:@@%H", "--name-status",
                  "--diff-filter=AD", f"{fresh[-1]}^..{end}", "--", "Code/")
        counts, sha, adds, dels = {}, None, 0, 0
        for line in log.splitlines() + ["@@"]:
            if line.startswith("@@"):
                if sha:
                    counts[sha] = max(0, dels - adds)
                sha, adds, dels = line[2:] or None, 0, 0
                continue
            status, _, path = line.partition("\t")
            if is_source(path):
                adds += status == "A"
                dels += status == "D"
        for sha in fresh:
            known[sha] = counts.get(sha, 0)
        if cache:
            _write_atomic(cache, {"version": MEASURE_VERSION, "counts": {sha: known[sha] for sha in shas}})
    return sum(known[sha] for sha in shas)


def measure(ref="origin/master", root=ROOT):
    """The window's headline movement at REF: a dict (JSON-safe), or {"error": why} when
    any read fails (an error is never cached)."""
    end = _git(root, "rev-parse", "--verify", "--quiet", f"{ref}^{{commit}}").stdout.strip()
    if not end:
        return {"error": f"{ref} does not resolve"}
    try:
        end_time = int(_ok(root, "show", "-s", "--format=%ct", end).strip())
        start = _ok(root, "rev-list", "-1", "--first-parent",
                    f"--before={end_time - WINDOW_HOURS * 3600}", end).strip()
        if not start:
            return {"sha": end, "error": f"no first-parent commit {WINDOW_HOURS} h before {end[:10]}"}
        credited = commit_removals(root, start, end)
        files, files_end = source_count(root, start), source_count(root, end)
        tus = tu_count(_blob(root, start, TU_MAP))           # the gap at the window's start
        keys = {tier: (register_keys(_blob(root, start, path)), register_keys(_blob(root, end, path)))
                for tier, path in REGISTERS.items()}
        debt = (sum(k[0] for k in keys.values()) + register_keys(_blob(root, start, GATE_BASELINE))
                + hatch_total(_blob(root, start, HATCH_BASELINE)))
    except (MeasureError, ValueError) as error:
        return {"sha": end, "error": str(error) or "git read failed"}
    # A file restored and then removed again is credited to both removing commits; only the
    # window's real reduction in source files counts.
    removed = min(credited, max(0, files - files_end))
    return {"version": MEASURE_VERSION, "sha": end, "start": start, "hours": WINDOW_HOURS,
            "source_gap": max(1, files - tus), "files_at_start": files, "files_at_end": files_end,
            "tus": tus, "debt_gap": max(1, debt),
            "yield": {"consolidate": removed, **{t: max(0, a - b) for t, (a, b) in keys.items()}}}


YIELD_KEYS = frozenset(("consolidate",) + tuple(REGISTERS))


def valid_measurement(m, sha):
    """Whether M is a complete measurement of SHA under this version and window."""
    if not isinstance(m, dict):
        return False
    y = m.get("yield")
    return (m.get("version") == MEASURE_VERSION and m.get("sha") == sha and _is_sha(sha)
            and _is_sha(m.get("start")) and m.get("hours") == WINDOW_HOURS
            and all(_is_count(m.get(k)) for k in ("source_gap", "files_at_start", "files_at_end", "tus", "debt_gap"))
            and m["source_gap"] == max(1, m["files_at_start"] - m["tus"]) and m["debt_gap"] >= 1
            and isinstance(y, dict) and set(y) == YIELD_KEYS and all(_is_count(v) for v in y.values())
            and y["consolidate"] <= max(0, m["files_at_start"] - m["files_at_end"])
            and all(y[t] <= m["debt_gap"] for t in REGISTERS))


def cached_measure(ref="origin/master", root=ROOT):
    """measure() of REF, from build/tier_tuning/<sha>.json only when that file is a valid
    measurement of the same SHA; anything else is discarded and recomputed."""
    sha = _git(root, "rev-parse", "--verify", "--quiet", f"{ref}^{{commit}}").stdout.strip()
    path = CACHE / f"{sha}.json"
    if sha and path.exists():
        try:
            got = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            got = None
        if valid_measurement(got, sha):
            return got
    got = measure(sha or ref, root)
    if sha and valid_measurement(got, sha):
        _write_atomic(path, got)
    return got


# ---------------------------------------------------------------- allocation (pure)

def fraction(tier, m):
    """The share of its headline's remaining gap tier's landings closed in the window."""
    gap = m["source_gap"] if tier == "consolidate" else m["debt_gap"]
    return m["yield"][tier] / gap


def fit(targets, priors, total=100.0):
    """Scale TARGETS by one factor so that, each clamped to BAND around its prior, they sum
    to TOTAL (bisection; always solvable because the priors sum to TOTAL), then round to
    tenths by largest remainder so the sum is exact."""
    lo = {t: BAND[0] * priors[t] for t in targets}
    hi = {t: BAND[1] * priors[t] for t in targets}

    def summed(scale):
        return sum(min(hi[t], max(lo[t], scale * targets[t])) for t in targets)

    a, b = 0.0, 1.0
    while summed(b) < total and b < 1e6:
        b *= 2
    for _ in range(100):
        mid = (a + b) / 2
        a, b = (mid, b) if summed(mid) < total else (a, mid)
    raw = {t: min(hi[t], max(lo[t], b * targets[t])) * 10 for t in targets}
    tenths = {t: math.floor(v) for t, v in raw.items()}
    short = round(total * 10) - sum(tenths.values())
    for t in sorted(raw, key=lambda t: (tenths[t] - raw[t], t))[:max(0, short)]:
        tenths[t] += 1
    return {t: tenths[t] / 10 for t in targets}


def allocate(priors, m):
    """Rows {tier: {prior, yield, fraction, ratio, multiplier, weight, reason}} from PRIORS and
    a measurement M (None or {"error"}: every tier keeps its prior)."""
    rows = {t: {"prior": p, "yield": None, "fraction": None, "ratio": None, "multiplier": 1.0,
                "reason": UNMEASURED.get(t, "no yield rule")} for t, p in priors.items()}
    usable = m is not None and "error" not in m
    measured = [t for t in MEASURED if t in priors and priors[t] > 0] if usable else []
    for t in measured:
        rows[t].update({"yield": m["yield"][t], "fraction": fraction(t, m)})
    mean = (sum(rows[t]["fraction"] for t in measured) / sum(priors[t] for t in measured)) if measured else 0
    for t in measured:
        if mean <= 0:
            rows[t]["reason"] = "no measured tier moved a headline in the window: prior"
            continue
        ratio = (rows[t]["fraction"] / priors[t]) / mean
        mult = min(BAND[1], max(BAND[0], math.sqrt(ratio)))
        unit = "source files removed" if t == "consolidate" else "register keys retired"
        rows[t].update({"ratio": ratio, "multiplier": mult,
                        "reason": f"{rows[t]['yield']:,} {unit}: {ratio:.2f}x the measured mean per share"
                                  + (" (band)" if mult != math.sqrt(ratio) else "")})
    if not usable:
        why = (m or {}).get("error", "no measurement")
        for row in rows.values():
            row["reason"] = f"{why}: prior"
    live = {t: p for t, p in priors.items() if p > 0}
    fitted = fit({t: live[t] * rows[t]["multiplier"] for t in live}, live, total=float(sum(live.values())))
    for t, row in rows.items():
        row["weight"] = fitted.get(t, 0)
    return rows


Tuning = collections.namedtuple("Tuning", "weights rows note in_force")


def weights(priors, ref="origin/master", root=ROOT):
    """Tuning(weights, rows, note, in_force): the tuned shares, or the priors when tuning is
    off (rows None) or the measurement failed (in_force False; NOTE says why)."""
    off = disabled()
    if off:
        return Tuning(dict(priors), None, off, False)
    m = cached_measure(ref, root)
    rows = allocate(priors, m)
    ok = "error" not in m
    note = (f"tuned on {m['sha'][:10]} over {m['hours']} h" if ok
            else f"tuning unavailable ({m['error']}): priors")
    return Tuning({t: r["weight"] for t, r in rows.items()}, rows, note, ok)
