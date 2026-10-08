#!/usr/bin/env python3
"""Match game.dat functions to WorldBuilder functions, to carry WB's names over.

WorldBuilder (worldbuilder.exe, internal build) is compiled from the same
source tree as game.dat but unoptimised and with assertions, so its bodies
never byte-match. Its assertion macros push each function's "Class::method"
name, which tools/pe_features.py harvests. This tool pairs the two binaries'
functions by evidence that survives optimisation, then emits each paired
game.dat function with WB's name as a lead:

  1. anchors   - a string, import or constant that only a few functions use on
                 each side; pairs are accepted when each is the other's best
                 match by a clear margin;
  2. call graph - matched pairs vote for pairings among their unmatched callees
                 and callers (debug WB calls helpers that retail inlines, so a
                 vote needs agreement from more than one neighbour or the
                 functions' own features);
  3. call sites - the call lists of a matched pair are aligned on their matched
                 callees; equal runs of unmatched callees between two agreeing
                 call sites pair in order (WB callees small enough to have been
                 inlined in retail are skipped);
  4. vtables   - two vtables whose matched slots agree pair every other slot by
                 index;
  5. order     - functions between two matches adjacent in both binaries pair
                 in order: equal gaps outright, unequal gaps by a monotone
                 alignment whose pairs must each carry confident call-graph or
                 feature evidence.

Steps 2-5 repeat until nothing new pairs. WB's debug machinery (out-of-line
debug-object calls, calls inside assertion macros; pe_features `debug`,
`debug_calls`) is removed first, since retail compiles it out.

Precision and recall on held-out ledger pairs: tools/wb_eval.py, after a run
with --holdout.

    wb_match.py --wb build/wb/wb_functions.jsonl --gd build/wb/gd_functions.jsonl \
                --out build/wb/matches.jsonl

A match is identity evidence for a person or agent to confirm, never a byte
match: nothing here may be landed without the usual build verification.
"""
import argparse
import bisect
import collections
import json
import re
import sys

RARE = 3            # a feature shared by more functions than this is not an anchor
ANCHOR_MIN = 1.0    # minimum anchor score
MARGIN = 1.2        # best candidate must beat the runner-up by this factor
VOTE_MIN = 2.0      # call-graph votes needed to accept a propagated pair
VOTE_LEAD = 1.0     # ... and its lead over the runner-up on both sides
NEIGHBOURS = 48     # a caller/callee set larger than this casts no votes (too ambiguous)
ROUNDS = 30         # propagation rounds at most; they normally converge sooner
FEATURE_WEIGHT = {"strings": 1.0, "imports": 0.6, "consts": 0.4}


def load(path):
    with open(path) as fh:
        return {r["va"]: r for r in map(json.loads, fh)}


def strip_debug(wb):
    """WB without its debug machinery: retail compiles assertion macros out.

    Out-of-line debug-object calls (pe_features `debug`) have no retail
    counterpart, and every macro calls one, so pairing them would poison the
    call-graph votes; they are dropped, and so is every call made inside a
    debug macro (`debug_calls`). Feature files without those fields pass
    through unchanged.
    """
    kept = {}
    for va, rec in wb.items():
        if rec.get("debug"):
            continue
        drop = collections.Counter(rec.get("debug_calls") or ())
        calls = []
        for c in rec.get("calls") or ():
            if drop[c]:
                drop[c] -= 1
            else:
                calls.append(c)
        kept[va] = dict(rec, calls=calls)
    return kept


def index(funcs, field):
    inv = collections.defaultdict(set)
    for va, rec in funcs.items():
        for value in rec.get(field) or ():
            inv[value].add(va)
    return inv


def name_counts(wb):
    counts = collections.Counter()
    for rec in wb.values():
        counts.update(set(rec.get("names") or ()))
    return counts


NAME_SPREAD = 4     # a name carried by more WB functions than this is an inlined helper's
SOURCE_RE = re.compile(r"\.(?:cpp|c|cxx)$", re.I)


def best_name(rec, counts):
    """The function's own name, or None when it cannot be told apart.

    Inlined header helpers put their names into every caller, so a name no
    other WB function carries is preferred. Failing a single such name, the
    name pushed beside a .cpp path (pe_features `name_files`) is the
    function's own and a header path marks an inlined one: overloads in one
    .cpp then keep their shared name, so long as it is carried by at most
    NAME_SPREAD functions. Anything still ambiguous gets no name rather than
    a wrong one.
    """
    names = rec.get("names") or ()
    unique = [n for n in names if counts[n] == 1]
    if len(unique) == 1:
        return unique[0]
    paths = dict(rec.get("name_files") or ())
    pool = unique or [n for n in names if counts[n] <= NAME_SPREAD]
    own = [n for n in pool if SOURCE_RE.search(paths.get(n, ""))]
    return own[0] if len(own) == 1 else None


def holdout_parity(va):
    """0 or 1: the hash half a gold address falls in for --holdout runs."""
    return (va * 2654435761) % 4294967296 % 2


def gold_seeds(wb, counts, gold_path, keep):
    """Pairs proven by the ledger: a REAL ledger name equal to a unique WB name.

    `keep(va)` selects which gold addresses may seed, so the rest stay held
    out for scoring.
    """
    import wb_gold
    by_norm = {}
    for va, rec in wb.items():
        name = best_name(rec, counts)
        if name:
            by_norm.setdefault(wb_gold.normalize(name), []).append(va)
    seeds = {}
    with open(gold_path) as fh:
        for rec in map(json.loads, fh):
            if rec.get("kind") != "REAL" or not rec.get("rowed") or not keep(rec["va"]):
                continue
            hits = {w for norm in rec.get("norms") or () for w in by_norm.get(norm, ())}
            if len(hits) == 1:
                seeds[rec["va"]] = hits.pop()
    return seeds


def feature_pairs(wb, gd):
    """Score candidate pairs by the rare features they share."""
    scores = collections.defaultdict(float)
    why = collections.defaultdict(set)
    for field, weight in FEATURE_WEIGHT.items():
        w_inv, g_inv = index(wb, field), index(gd, field)
        for value, g_set in g_inv.items():
            w_set = w_inv.get(value)
            if not w_set or len(w_set) > RARE or len(g_set) > RARE:
                continue
            share = weight / (len(w_set) * len(g_set))
            for g in g_set:
                for w in w_set:
                    scores[(g, w)] += share
                    why[(g, w)].add(field)
    return scores, why


def mutual_best(scores, minimum, margin, taken_g=(), taken_w=()):
    """Pairs that are each other's best candidate by `margin`."""
    by_g = collections.defaultdict(list)
    by_w = collections.defaultdict(list)
    for (g, w), s in scores.items():
        if g in taken_g or w in taken_w:
            continue
        by_g[g].append((s, w))
        by_w[w].append((s, g))

    def top(cands):
        cands.sort(reverse=True)
        best = cands[0]
        runner = cands[1][0] if len(cands) > 1 else 0.0
        return best, runner

    accepted = {}
    for g, cands in by_g.items():
        (s, w), runner = top(cands)
        if s < minimum or s < margin * runner:
            continue
        (s2, g2), runner2 = top(by_w[w])
        if g2 == g and s2 >= margin * runner2:
            accepted[g] = (w, s)
    return accepted


def callers(funcs):
    inv = collections.defaultdict(set)
    for va, rec in funcs.items():
        for target in rec.get("calls") or ():
            inv[target].add(va)
    return inv


def propagate(wb, gd, matched, feat_scores):
    """Grow `matched` (g -> (w, score, evidence)) through the call graph.

    A candidate pair scores one point per matched neighbour it agrees on:
    g calls X and w calls X's partner, or Y calls g and Y's partner calls w.
    Retail inlines many helpers debug WB still calls, so w's neighbourhood is
    larger; agreement is counted, never penalised for extras. A pair needs two
    agreeing neighbours, or one when it is the sole candidate on both sides,
    plus a plausible size, and must lead its runner-up on both sides.
    """
    g_callers, w_callers = callers(gd), callers(wb)
    while True:
        partner = {g: w for g, (w, _, _) in matched.items()}
        taken_w = set(partner.values())
        agree = collections.Counter()
        for g, w in partner.items():
            for g_side, w_side in (
                    (gd[g].get("calls") or (), wb[w].get("calls") or ()),
                    (g_callers.get(g, ()), w_callers.get(w, ()))):
                g_open = {c for c in g_side if c in gd and c not in partner}
                w_open = {c for c in w_side if c in wb and c not in taken_w}
                if not g_open or not w_open or len(g_open) * len(w_open) > NEIGHBOURS * NEIGHBOURS:
                    continue
                for gc in g_open:
                    for wc in w_open:
                        if plausible(gd[gc], wb[wc]):
                            agree[(gc, wc)] += 1
        by_g = collections.defaultdict(list)
        by_w = collections.defaultdict(list)
        for (g, w), n in agree.items():
            by_g[g].append((n + feat_scores.get((g, w), 0.0), w))
            by_w[w].append((n + feat_scores.get((g, w), 0.0), g))
        new = {}
        for g, cands in by_g.items():
            cands.sort(reverse=True)
            n, w = cands[0]
            runner = cands[1][0] if len(cands) > 1 else 0.0
            w_cands = sorted(by_w[w], reverse=True)
            w_runner = w_cands[1][0] if len(w_cands) > 1 else 0.0
            if w_cands[0][1] != g:
                continue
            sole = len(cands) == 1 and len(w_cands) == 1
            if (n >= VOTE_MIN and n >= runner + VOTE_LEAD and n >= w_runner + VOTE_LEAD) or (sole and n >= 1):
                new[g] = (w, n)
        if not new:
            return
        for g, (w, n) in new.items():
            matched[g] = (w, float(n), ["callgraph"])


INLINE_MAX = 64     # an unmatched WB callee this small may be inlined in retail
CALLSITE_RUN = 8    # longest run of unmatched callees paired in call order


def first_seen(calls, funcs):
    """Call targets in call-site order, first occurrence only, known functions only."""
    seen = {}
    for c in calls or ():
        if c in funcs:
            seen.setdefault(c, len(seen))
    return list(seen)


def call_anchors(g_calls, w_calls, partner):
    """Longest run of (i, j) where g_calls[i]'s partner is w_calls[j], increasing in both."""
    w_index = {c: j for j, c in enumerate(w_calls)}
    hits = [(i, w_index[partner[c]]) for i, c in enumerate(g_calls)
            if c in partner and partner[c] in w_index]
    best = []        # best[k]: index into hits of the smallest tail of a run of length k+1
    back = [None] * len(hits)
    for n, (_, j) in enumerate(hits):
        k = bisect.bisect_left([hits[b][1] for b in best], j)
        back[n] = best[k - 1] if k else None
        best[k:k + 1] = [n]
    run, n = [], best[-1] if best else None
    while n is not None:
        run.append(hits[n])
        n = back[n]
    return run[::-1]


def callsite_votes(wb, gd, partner, taken_w):
    """Votes for callee pairs that sit alone between agreeing call sites of a matched pair.

    The call lists of g and its partner w are aligned on their matched callees.
    Between two consecutive anchors (or a list end) a lone unmatched callee on
    each side is the same call; WB callees small enough to be inlined in
    retail are ignored on the WB side when they would spoil that.
    """
    votes = collections.Counter()
    for g, w in partner.items():
        g_calls = first_seen(gd[g].get("calls"), gd)
        w_calls = first_seen(wb[w].get("calls"), wb)
        bounds = [(-1, -1)] + call_anchors(g_calls, w_calls, partner) + [(len(g_calls), len(w_calls))]
        for (i1, j1), (i2, j2) in zip(bounds, bounds[1:]):
            g_open = [c for c in g_calls[i1 + 1:i2] if c not in partner]
            w_open = [c for c in w_calls[j1 + 1:j2] if c not in taken_w]
            if len(w_open) > 1:
                w_open = [c for c in w_open if wb[c]["size"] > INLINE_MAX]
            if 0 < len(g_open) == len(w_open) <= CALLSITE_RUN and all(
                    plausible(gd[gc], wb[wc]) for gc, wc in zip(g_open, w_open)):
                for pair in zip(g_open, w_open):
                    votes[pair] += 1
    return votes


def callsite_pass(wb, gd, matched):
    """Accept call-site pairs no other call-site vote contradicts on either side."""
    partner = {g: w for g, (w, _, _) in matched.items()}
    votes = callsite_votes(wb, gd, partner, set(partner.values()))
    g_rivals = collections.Counter(g for g, _ in votes)
    w_rivals = collections.Counter(w for _, w in votes)
    added = 0
    for (g, w), n in votes.items():
        if g_rivals[g] == 1 and w_rivals[w] == 1:
            matched[g] = (w, float(n), ["callsite"])
            added += 1
    return added


def vtables(funcs):
    tables = collections.defaultdict(dict)
    for va, rec in funcs.items():
        for table, slot in rec.get("vt") or ():
            tables[table][slot] = va
    return tables


def vtable_pass(wb, gd, matched):
    """Pair whole vtables whose matched slots agree, then every slot by index."""
    w_tables, g_tables = vtables(wb), vtables(gd)
    w_slot_of = collections.defaultdict(set)
    for table, slots in w_tables.items():
        for slot, va in slots.items():
            w_slot_of[va].add((table, slot))
    added = 0
    taken_w = {w for w, _, _ in matched.values()}
    for g_table, g_slots in g_tables.items():
        agree = collections.Counter()
        for slot, g in g_slots.items():
            if g in matched:
                for w_table, w_slot in w_slot_of.get(matched[g][0], ()):
                    if w_slot == slot:
                        agree[w_table] += 1
        if not agree:
            continue
        (w_table, n), *rest = agree.most_common()
        if n < 2 or (rest and rest[0][1] * MARGIN > n):
            continue
        w_slots = w_tables[w_table]
        for slot, g in g_slots.items():
            w = w_slots.get(slot)
            if w is None or g in matched or w in taken_w:
                continue
            matched[g] = (w, float(n), ["vtable"])
            taken_w.add(w)
            added += 1
    return added


GAP_MAX = 40       # largest unmatched run interpolated between two neighbours
SIZE_RATIO = 30    # a debug body may be this many times its retail one (plus slack)
SHRINK_RATIO = 1.25  # ... and a retail body this many times its debug one


def is_stub(rec, called):
    """WB exception-handling stubs: tiny, never called, not in a vtable."""
    return rec["size"] < 24 and rec["va"] not in called and not rec.get("vt")


def plausible(g_rec, w_rec):
    """Retail bodies are smaller than debug ones, but not wildly."""
    g, w = g_rec["size"], w_rec["size"]
    return g <= w * SHRINK_RATIO + 16 and w <= g * SIZE_RATIO + 64


class Layout:
    """Both binaries' functions in address order; WB's exception stubs are left out.

    Both builds keep each source file's functions in source order, so between
    two matches adjacent in both orders the same functions tend to appear in
    the same order.
    """

    def __init__(self, wb, gd):
        called = {c for rec in wb.values() for c in rec.get("calls") or ()}
        self.g_order = sorted(gd)
        self.w_order = [va for va in sorted(wb) if not is_stub(wb[va], called)]
        self.g_pos = {va: i for i, va in enumerate(self.g_order)}
        self.w_pos = {va: i for i, va in enumerate(self.w_order)}

    def gaps(self, matched):
        """((g1, w1), (g2, w2)) order positions of matches consecutive in game.dat order."""
        anchors = sorted((self.g_pos[g], self.w_pos[w]) for g, (w, _, _) in matched.items()
                         if g in self.g_pos and w in self.w_pos)
        return zip(anchors, anchors[1:])


def interpolate(wb, gd, matched, layout):
    """Pair the unmatched functions in equal gaps between two adjacent matches.

    Only equal-length gaps whose every pair has plausible sizes are taken.
    """
    taken_w = {w for w, _, _ in matched.values()}
    added = 0
    for (g1, w1), (g2, w2) in layout.gaps(matched):
        gap_g, gap_w = g2 - g1 - 1, w2 - w1 - 1
        if not (0 < gap_g == gap_w <= GAP_MAX):
            continue
        pairs = [(layout.g_order[g1 + k], layout.w_order[w1 + k]) for k in range(1, gap_g + 1)]
        if any(g in matched or w in taken_w or not plausible(gd[g], wb[w]) for g, w in pairs):
            continue
        for g, w in pairs:
            matched[g] = (w, 1.0, ["order"])
            taken_w.add(w)
            added += 1
    return added


ALIGN_GAP_MAX = 320  # largest gap (either side) aligned between two neighbours
ALIGN_PRIOR = 0.25   # alignment credit for any plausible pair, so order alone links
ALIGN_MIN = 0.5      # evidence an aligned pair needs to be accepted
ALIGN_MARGIN = 0.5   # ... and its lead over every rival in its row and column
ALIGN_SOLE_MIN = 0.0  # evidence a pair with no plausible rival in its gap needs


class Neighbourhood:
    """Matched-neighbour evidence for a candidate pair, from the call graph."""

    def __init__(self, wb, gd):
        self.wb, self.gd = wb, gd
        self.g_callers, self.w_callers = callers(gd), callers(wb)
        self.w_calls = {va: set(rec.get("calls") or ()) for va, rec in wb.items()}

    def evidence(self, g, w, partner, feat_scores):
        """Agreeing minus half the disagreeing matched callees and callers, plus features."""
        score = 2.0 * feat_scores.get((g, w), 0.0)
        for g_side, w_side in ((set(self.gd[g].get("calls") or ()), self.w_calls[w]),
                               (self.g_callers.get(g, ()), self.w_callers.get(w, ()))):
            for c in g_side:
                if c in partner:
                    score += 1.0 if partner[c] in w_side else -0.5
        return score


def aligned(scores):
    """Index pairs of the monotone alignment maximising the sum of positive scores."""
    rows, cols = len(scores), len(scores[0])
    best = [[0.0] * (cols + 1) for _ in range(rows + 1)]
    for i in range(rows - 1, -1, -1):
        for j in range(cols - 1, -1, -1):
            take = scores[i][j] + best[i + 1][j + 1] if scores[i][j] is not None else float("-inf")
            best[i][j] = max(take, best[i + 1][j], best[i][j + 1])
    pairs, i, j = [], 0, 0
    while i < rows and j < cols:
        s = scores[i][j]
        if s is not None and best[i][j] == s + best[i + 1][j + 1]:
            pairs.append((i, j))
            i, j = i + 1, j + 1
        elif best[i][j] == best[i + 1][j]:
            i += 1
        else:
            j += 1
    return pairs


def confident(scores, i, j):
    """Evidence at (i, j) clears ALIGN_MIN and leads its row and column by ALIGN_MARGIN.

    A pair with no plausible rival in its row or column needs only ALIGN_SOLE_MIN.
    """
    s = scores[i][j]
    rivals = [v for k, v in enumerate(scores[i]) if k != j and v is not None]
    rivals += [row[j] for k, row in enumerate(scores) if k != i and row[j] is not None]
    return s >= (ALIGN_MIN if rivals else ALIGN_SOLE_MIN) and all(s >= v + ALIGN_MARGIN for v in rivals)


def align(wb, gd, matched, feat_scores, layout, hood):
    """Pair functions inside unequal gaps between two matches adjacent in both binaries.

    interpolate() needs equal gaps; here retail may have dropped or inlined
    some functions and debug WB kept extra ones, so each gap is aligned in
    order (a pair with plausible size scores ALIGN_PRIOR plus its neighbour
    evidence) and an aligned pair is accepted only when its own evidence is
    confident. Accepted pairs become anchors that split the gap next round.
    """
    partner = {g: w for g, (w, _, _) in matched.items()}
    taken_w = set(partner.values())
    found = {}
    for (g1, w1), (g2, w2) in layout.gaps(matched):
        if not (0 < g2 - g1 - 1 <= ALIGN_GAP_MAX and 0 < w2 - w1 - 1 <= ALIGN_GAP_MAX):
            continue
        gs = layout.g_order[g1 + 1:g2]
        ws = [w for w in layout.w_order[w1 + 1:w2] if w not in taken_w]
        if not ws:
            continue
        evidence = [[hood.evidence(g, w, partner, feat_scores) if plausible(gd[g], wb[w]) else None
                     for w in ws] for g in gs]
        credit = [[None if e is None else e + ALIGN_PRIOR for e in row] for row in evidence]
        for i, j in aligned(credit):
            if confident(evidence, i, j):
                found[gs[i]] = (ws[j], evidence[i][j])
    for g, (w, s) in found.items():
        matched[g] = (w, s, ["align"])
    return len(found)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--wb", required=True)
    ap.add_argument("--gd", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--gold", help="seed with ledger REAL names (build/wb/gold.jsonl)")
    ap.add_argument("--holdout", type=int, nargs="?", const=1, choices=(0, 1),
                    help="seed only from gold addresses whose hash parity is not this value (default 1), "
                         "so tools/wb_eval.py --parity can score the rest honestly")
    args = ap.parse_args(argv)
    wb, gd = load(args.wb), load(args.gd)
    counts = name_counts(wb)
    wb = strip_debug(wb)

    matched = {}
    if args.gold:
        held = args.holdout
        keep = (lambda va: True) if held is None else (lambda va: holdout_parity(va) != held)
        seeds = gold_seeds(wb, counts, args.gold, keep)
        matched = {g: (w, 100.0, ["seed"]) for g, w in seeds.items() if g in gd}
        print(f"gold seeds: {len(matched)}", file=sys.stderr)
    feat_scores, why = feature_pairs(wb, gd)
    taken_w = {w for w, _, _ in matched.values()}
    anchors = mutual_best(feat_scores, ANCHOR_MIN, MARGIN, matched, taken_w)
    matched.update({g: (w, s, sorted(why[(g, w)])) for g, (w, s) in anchors.items()})
    print(f"anchors: {len(anchors)}", file=sys.stderr)
    layout, hood = Layout(wb, gd), Neighbourhood(wb, gd)
    for round_ in range(1, ROUNDS + 1):
        before = len(matched)
        propagate(wb, gd, matched, feat_scores)
        grown = vtable_pass(wb, gd, matched)
        ordered = interpolate(wb, gd, matched, layout)
        aligned_ = align(wb, gd, matched, feat_scores, layout, hood)
        sites = callsite_pass(wb, gd, matched)
        print(f"round {round_}: {len(matched)} matched (+{len(matched) - before}, "
              f"{grown} by vtable, {ordered} by order, {aligned_} by alignment, "
              f"{sites} by call site)", file=sys.stderr)
        if len(matched) == before:
            break

    named = 0
    with open(args.out, "w") as out:
        for g, (w, score, evidence) in sorted(matched.items()):
            name = best_name(wb[w], counts)
            named += name is not None
            rec = {"gd_va": g, "wb_va": w, "wb_name": name, "score": round(score, 3),
                   "evidence": evidence, "wb_file": (wb[w].get("files") or [None])[0],
                   "name_spread": counts[name] if name else 0}
            out.write(json.dumps(rec) + "\n")
    print(f"{len(matched)} matches, {named} carry a WB name", file=sys.stderr)


if __name__ == "__main__":
    sys.exit(main())
