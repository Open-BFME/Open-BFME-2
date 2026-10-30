#!/usr/bin/env python3
"""Held-out precision of a tu_map approval rule (`tu_map.py --holdout RULE`).

The method is the provisional gate's (76341ba6b2), made reproducible here:

  truth   the map rebuilt from current inputs with every candidate rule OFF; a row's truth
          is its TU when that map approves it under an independent anchor (approved, and
          neither `provisional` nor a candidate rule's token).
  folds   the anchored TUs (those truth TUs) split into FOLDS folds by a hash of their path.
  input   per fold, every F, Z, S, L and W value naming a held-out TU is removed from the
          evidence rows BEFORE clustering (the row's hard/hint/tool are recomputed), and the
          map is rebuilt twice from that stripped evidence: rule OFF and rule ON.
  scored  the rows the rule approves (ON minus OFF on the same fold) whose truth TU is held
          out in that fold. Rows the rule approves whose truth TU kept its anchors in the
          input are reported as `not held out`, never scored: their anchors were visible.
  metrics purity (the owner's bar): a scored row is pure when the group it joins (every row
          approved under its TU in the ON map, with truth labels) has one truth TU; name
          precision: the rule's TU is the truth TU's own path; recall: correct scored rows
          over the held-out truth rows the OFF map leaves unapproved.

Row folds (`--unit row`): a TU fold strips every anchor a held-out TU has, so it cannot score a
rule that places rows only between a TU's own F/Z/L anchors (signal-T): it reports how many
held-out rows such a rule puts in a neighbour (purity), never a correct placement. A row fold
holds out ROWS instead: the truth rows split into FOLDS folds by a hash of their address, and
per fold the held-out rows' own F/Z/S/L/W are stripped (the other rows of their TU keep theirs),
so a held-out row looks like a row nothing anchors. Scored as above, over the held-out rows.

Leakage: the only route from a held-out TU's anchors into a fold's map is the evidence rows,
and they are stripped there; tu_evidence (E/P) reads only the fold's own map and the retail
image (FuncInfo, vftables), never the committed tu_map.csv or the ledger's strings. What the
fold still sees is non-anchor input: row names (class names give N), current source paths
(directories), retail layout. Truth is computed once, rule OFF, and never fed back.

Rules: `p-groups` and `prov-min-1` toggle the real gate (tu_evidence.P_GROUPS,
tu_map.PROV_MIN); `signal-X` builds with tu_evidence signal X promoted on top of PROMOTED
(rule OFF: X left out); `brackets`, `interleave` and `k-only` are candidate post-passes on a built
map, measured here only (not in the gate).

    python3 tools/tu_map.py --holdout p-groups [--folds 5] [--json FILE]
"""
import collections
import hashlib
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_map  # noqa: E402

FOLDS = 5
HARD = ("F", "Z", "S", "L")
STRIP = ("F", "Z", "S", "L", "W")
RULE_TOKENS = ("p-group",)          # evidence tokens of candidate rules: never truth


# ---------------------------------------------------------------- input

def strip(rows, held, held_rows=frozenset()):
    """Evidence rows with every F/Z/S/L/W naming a held-out TU removed, and every F/Z/S/L/W
    of a held-out row (by rva) (copies)."""
    out = []
    for r in rows:
        r = dict(r)
        for s in STRIP:
            if r.get(s) and (r[s].lower() in held or r["rva"] in held_rows):
                r[s] = None
        r["hard"] = r["F"] or r["Z"] or r["S"] or r["L"]
        r["hint"] = r["hard"] or r["N"]
        r["tool"] = bool(r["tool"] and r["hard"])
        out.append(r)
    return out


class Builder:
    """tu_map.build over (stripped) evidence rows, with the gate toggles set per build."""

    def __init__(self, layout):
        self.layout = layout
        self.rows = None

    def build(self, held=frozenset(), p_groups=False, prov_min=2, signal=None, without=None,
              held_rows=frozenset()):
        """`signal` is promoted for this build, `without` left out of PROMOTED; `held_rows`
        (int rvas) lose their own anchors."""
        import tu_evidence
        if self.rows is None:
            self.rows = tu_map.evidence_rows(self.layout)
        orig = tu_map.evidence_rows, tu_map.PROV_MIN, tu_evidence.P_GROUPS, tu_evidence.PROMOTED
        tu_map.evidence_rows = lambda layout, ledger=None: strip(self.rows, held, held_rows)
        tu_map.PROV_MIN, tu_evidence.P_GROUPS = prov_min, p_groups
        tu_evidence.PROMOTED = (orig[3] | {signal} if signal else orig[3]) - {without}
        try:
            out = tu_map.build(self.layout)
        finally:
            tu_map.evidence_rows, tu_map.PROV_MIN, tu_evidence.P_GROUPS, tu_evidence.PROMOTED = orig
        return sorted((r for r in out if r["kind"].startswith("code")), key=lambda r: int(r["rva"], 16))


def truth_of(rows):
    """{rva: tu key} of rows approved under an independent anchor (no provisional or rule token)."""
    return {r["rva"]: r["tu"].lower() for r in rows if r["confidence"] == "approved" and r["tu"]
            and tu_map.PROV_TOKEN not in r["evidence"].split() and not set(RULE_TOKENS) & set(r["evidence"].split())}


def fold_of(key, folds=FOLDS):
    return int(hashlib.sha1(key.encode()).hexdigest(), 16) % folds


# ---------------------------------------------------------------- candidate post-passes

def approved_keys(rows):
    return {r["tu"].lower() for r in rows if r["confidence"] == "approved" and r["tu"]}


def pass_k(rows):
    ok = approved_keys(rows)
    return {i: r["tu"] for i, r in enumerate(rows)
            if r["confidence"] == "proposed" and r["by"] == "K" and r["tu"].lower() in ok}


def pass_brackets(rows):
    """A proposed C row whose nearest approved rows on both sides carry its TU within GAP is
    approved; iterated, so new approvals bracket further rows."""
    conf = [r["confidence"] == "approved" for r in rows]
    tu = [r["tu"].lower() for r in rows]
    rva = [int(r["rva"], 16) for r in rows]
    got, changed = {}, True
    while changed:
        changed = False
        below, last = [None] * len(rows), None
        for i in range(len(rows)):
            below[i] = last
            last = i if conf[i] else last
        above, nxt = [None] * len(rows), None
        for i in range(len(rows) - 1, -1, -1):
            above[i] = nxt
            nxt = i if conf[i] else nxt
        for i, r in enumerate(rows):
            if conf[i] or r["by"] != "C" or r["confidence"] != "proposed" or not r["tu"]:
                continue
            a, b = below[i], above[i]
            if a is not None and b is not None and tu[a] == tu[b] == tu[i] and rva[b] - rva[a] <= tu_map.GAP:
                conf[i], got[i], changed = True, r["tu"], True
    return got


def pass_interleave(rows):
    """A run of noncontiguous rows of one TU, none F/Z/S/L, between approved rows of one other
    TU that has an F/Z/S/L row, takes that host TU."""
    hard = {r["tu"].lower() for r in rows if r["by"] in HARD and r["confidence"] == "approved"}
    assigned = [i for i, r in enumerate(rows) if r["tu"]]
    got, j = {}, 0
    while j < len(assigned):
        r = rows[assigned[j]]
        if "noncontiguous" not in r["evidence"] or r["confidence"] == "approved":
            j += 1
            continue
        k, start = r["tu"].lower(), j
        while j + 1 < len(assigned) and rows[assigned[j + 1]]["tu"].lower() == k \
                and "noncontiguous" in rows[assigned[j + 1]]["evidence"]:
            j += 1
        run = assigned[start:j + 1]
        lo = rows[assigned[start - 1]] if start > 0 else None
        hi = rows[assigned[j + 1]] if j + 1 < len(assigned) else None
        j += 1
        if lo is None or hi is None or any(rows[x]["by"] in HARD for x in run):
            continue
        if (lo["tu"].lower() == hi["tu"].lower() != k and lo["confidence"] == hi["confidence"] == "approved"
                and lo["tu"].lower() in hard):
            got.update({x: lo["tu"] for x in run})
    return got


POST_PASSES = {"brackets": pass_brackets, "interleave": pass_interleave, "k-only": pass_k}
GATE_RULES = {"p-groups": {"p_groups": True}, "prov-min-1": {"prov_min": 1}}
# one rule per tu_evidence layout signal: ON promotes it, OFF leaves it out (a promoted
# signal is measured as if it were not)
SIGNAL_RULES = {f"signal-{s}": s for s in ("E", "I", "V", "T", "R")}
RULES = tuple(GATE_RULES) + tuple(SIGNAL_RULES) + tuple(POST_PASSES)


def toggles(rule):
    """(OFF build kwargs, ON build kwargs) of a gate or signal rule, or None for a post-pass."""
    if rule in GATE_RULES:
        return {}, GATE_RULES[rule]
    if rule in SIGNAL_RULES:
        return {"without": SIGNAL_RULES[rule]}, {"signal": SIGNAL_RULES[rule]}
    return None


def newly_approved(rule, off, on=None):
    """{rva: (tu, row)} the rule approves: ON minus OFF for a gate rule, the post-pass for a candidate."""
    if rule in POST_PASSES:
        return {off[i]["rva"]: (tu, off[i]) for i, tu in POST_PASSES[rule](off).items()}
    base = {r["rva"] for r in off if r["confidence"] == "approved"}
    return {r["rva"]: (r["tu"], r) for r in on if r["confidence"] == "approved" and r["rva"] not in base}


# ---------------------------------------------------------------- scoring

def score_fold(rule, off, on, truth, held, stats, worst, held_truth=None):
    """Add one fold's counts to `stats`; append mixed rows to `worst`. `held_truth` (row
    folds) are the held-out truth rows; by default those of the held-out TUs `held`."""
    got = newly_approved(rule, off, on)
    final = off if rule in POST_PASSES else on
    if held_truth is None:
        held_truth = {rva for rva, k in truth.items() if k in held}
    recoverable = {r["rva"] for r in off if r["rva"] in held_truth and r["confidence"] != "approved"}
    stats["recoverable"] += len(recoverable)
    groups = collections.defaultdict(collections.Counter)
    for r in final:
        if r["confidence"] == "approved" and r["tu"] and r["rva"] in truth and r["rva"] not in got:
            groups[r["tu"].lower()][truth[r["rva"]]] += 1
    for rva, (tu, _) in got.items():
        if rva in truth:
            groups[tu.lower()][truth[rva]] += 1
    for rva, (tu, r) in sorted(got.items()):
        if rva not in held_truth:
            stats["not held out" if rva in truth else "unlabelled"] += 1
            continue
        stats["scored"] += 1
        g = groups[tu.lower()]
        if tu.lower() == truth[rva]:
            stats["name"] += 1
            if rva in recoverable:
                stats["recovered"] += 1
        if len(g) == 1:
            stats["pure"] += 1
            stats["singleton"] += sum(g.values()) == 1
        elif len(worst) < 5:
            worst.append({"rva": rva, "by": r["by"], "tu": tu, "truth": truth[rva], "group": dict(g.most_common(3))})


def holdout(rule, layout=None, folds=FOLDS, builder=None, log=print, unit="tu"):
    """The rule's held-out report (a dict); `unit` "tu" holds out anchored TUs, "row" truth rows."""
    if rule not in RULES:
        raise SystemExit(f"tu_holdout: unknown rule {rule!r}; one of {', '.join(RULES)}")
    builder = builder or Builder(layout or tu_map.Layout(tu_map.ROOT))
    live = builder.build()
    truth = truth_of(live)
    keys = sorted(set(truth.values()))
    stats, worst = collections.Counter(), []
    toggle = toggles(rule)
    if toggle and toggle[0]:            # truth never includes the rule's own approvals
        live = builder.build(**toggle[0])
        truth = truth_of(live)
        keys = sorted(set(truth.values()))
    for f in range(folds):
        if unit == "row":
            rows = frozenset(rva for rva in truth if fold_of(rva, folds) == f)
            held, held_truth, extra = frozenset(), rows, {"held_rows": frozenset(int(a, 16) for a in rows)}
        else:
            held = frozenset(k for k in keys if fold_of(k, folds) == f)
            held_truth, extra = None, {}
        off = builder.build(held, **(toggle[0] if toggle else {}), **extra)
        on = builder.build(held, **toggle[1], **extra) if toggle else None
        score_fold(rule, off, on, truth, held, stats, worst, held_truth)
        log(f"tu_holdout {rule}: fold {f + 1}/{folds} ({len(held_truth or held)} {unit}s held out)")
    live_on = builder.build(**toggle[1]) if toggle else None
    gained = newly_approved(rule, live, live_on)
    report = {"rule": rule, "unit": unit, "folds": folds, "anchored_tus": len(keys), "truth_rows": len(truth),
              "scored": stats["scored"], "pure": stats["pure"], "singleton_groups": stats["singleton"],
              "name_correct": stats["name"], "recovered": stats["recovered"], "recoverable": stats["recoverable"],
              "not_held_out": stats["not held out"], "unlabelled": stats["unlabelled"],
              "purity": stats["pure"] / stats["scored"] if stats["scored"] else None,
              "live_rows_gained": len(gained), "worst": worst}
    report["live_files_freed"] = files_freed(layout or builder.layout, live, set(gained))
    return report


def files_freed(layout, live, gained):
    """Authored files whose matched rows are all approved only with `gained`."""
    ok = {r["rva"] for r in live if r["confidence"] == "approved"}
    files = collections.defaultdict(set)
    for r in tu_map.read_csv(layout.path("functions.csv")):
        src = r["source"]
        if (r.get("status") == "matched" and src.startswith("Code/") and src.endswith((".cpp", ".c", ".asm"))
                and not re.search(r"/(gen_small|gen_asm|masm_dumps)/", src) and r["target_rva"].startswith("0x")):
            files[src].add(f"0x{int(r['target_rva'], 16):08X}")
    return sum(1 for rvas in files.values() if not rvas <= ok and rvas <= ok | gained)


def render(report):
    p = report["purity"]
    held = "truth rows" if report.get("unit") == "row" else "anchored TUs"
    lines = [f"rule {report['rule']}: {report['folds']}-fold hold-out of {held} ({report['anchored_tus']} "
             f"anchored TUs, {report['truth_rows']} truth rows)",
             f"  purity {report['pure']}/{report['scored']}" + (f" = {100 * p:.2f}%" if p is not None else "")
             + f" ({report['singleton_groups']} in one-row groups, pure by construction)",
             f"  name precision {report['name_correct']}/{report['scored']}; recall "
             f"{report['recovered']}/{report['recoverable']}",
             f"  not scored: {report['not_held_out']} approved rows of TUs whose anchors stayed in the input, "
             f"{report['unlabelled']} with no truth",
             f"  live: +{report['live_rows_gained']} approved code rows, {report['live_files_freed']} files freed"]
    for w in report["worst"]:
        lines.append(f"  mixed: {w['rva']} by {w['by']} -> {w['tu']} (truth {w['truth']}; group {w['group']})")
    return "\n".join(lines)


def main(rule, folds=FOLDS, json_path=None, layout=None, unit="tu"):
    report = holdout(rule, layout, folds, log=lambda m: print(m, file=sys.stderr), unit=unit)
    print(render(report))
    if json_path:
        Path(json_path).write_text(json.dumps(report, indent=1), encoding="utf-8")
    return 0
