#!/usr/bin/env python3
"""Review of an inferred name: one definition for the lane that
records votes (tools/name_lane.py) and the engine that lands names
(tools/rename.py).

An uncontested parameter or local name needs one worker's proposal. Every
other inferred name, including a contested scoped name, still needs two
independent blind proposals. Two things make that rule checkable:

  workers   every vote carries the identity of the worker that cast it, taken
            from the environment, not from a flag the caller types. A session
            label (`--session`) is a free string, so one agent could serve
            itself twice under two labels and outvote nobody but itself; the
            worker identity is BFME_CLAIM_OWNER or BFME_RUN_ID (the identity
            tools/claims.py claims under -- an orchestrator gives each seat its
            own), else the harness's CLAUDE_CODE_SESSION_ID, else
            tools/claims.py's default owner. It is stored hashed (w-<12 hex>),
            so no user, host or session id enters the repository. Agreement
            counts distinct workers, never distinct session labels.
  votes     reverse/name_votes.csv (append-only, union-merged) holds each vote
            as sha256(key|canon(name))[:24]. The agreement record in
            reverse/name_agreed.csv is only an index into those votes: the
            engine recomputes the approval from them (the required distinct
            workers voted that spelling or explicitly the same scoped meaning,
            no rival has as
            many, the record and the spelling are not disputed), so a
            hand-written agreement row authorises nothing.

canon() folds word order, plurals and common abbreviations, so
m_ladderComboBox and m_comboBoxLadder are one vote.

    python3 tools/name_agreement.py whoami      # this environment's worker id
"""
import argparse
import collections
import hashlib
import json
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

VOTES = "reverse/name_votes.csv"
AGREED = "reverse/name_agreed.csv"
MEANINGS = "reverse/name_meanings.csv"
RESOLUTIONS = "reverse/name_resolutions.csv"
VOTE_COLUMNS = ["key", "hash", "model", "session", "worker", "date"]
MEANING_COLUMNS = VOTE_COLUMNS + ["meaning"]
AGREED_COLUMNS = ["id", "kind", "old", "new", "rva", "agents", "key", "status", "detail"]
RESOLUTION_COLUMNS = ["key", "hash", "name", "source_sha", "worker", "model", "reason", "date"]
SYNONYMS = {"num": "count", "number": "count", "cnt": "count", "idx": "index", "len": "length", "pos": "position",
            "str": "string", "msg": "message", "btn": "button", "wnd": "window", "tex": "texture", "obj": "object"}
WORKER = re.compile(r"w-[0-9a-f]{12}")
HASH = re.compile(r"[0-9a-f]{24}")
ROLES = {"source", "destination", "input", "output", "inout", "index", "count", "length", "size",
         "flag", "callback", "handle", "owner", "result", "radius", "diameter", "angle", "position",
         "duration", "deadline"}
UNITS = {"none", "bytes", "elements", "pixels", "radians", "degrees", "frames", "seconds",
         "milliseconds", "world_units", "boolean", "identifier", "unspecified"}


def meaning_digest(key, descriptor):
    """Exact structured role agreement, not a dictionary of spelling synonyms."""
    if (not scoped_key(key) or not isinstance(descriptor, dict)
            or set(descriptor) != {"role", "entity", "units", "ownership"}
            or not all(isinstance(value, str) for value in descriptor.values())
            or descriptor["role"] not in ROLES or descriptor["units"] not in UNITS
            or descriptor["ownership"] not in {"borrowed", "owned", "shared", "value", "unspecified"}
            or not isinstance(descriptor["entity"], str)
            or not re.fullmatch(r"[a-z][a-z0-9_]{1,63}", descriptor["entity"])
            or descriptor["entity"] in {"unknown", "thing", "value", "data", "parameter", "local"}):
        raise ValueError("meaning needs role, a specific snake_case entity, units and ownership")
    return hash_canon(key, "meaning-v1:" + json.dumps(descriptor, sort_keys=True, separators=(",", ":")))


def record_meaning(record_id):
    found = re.search(r"-m([0-9a-f]{24})$", record_id or "")
    return found.group(1) if found else None


class VoteTally(collections.defaultdict):
    def __init__(self):
        super().__init__(lambda: collections.defaultdict(dict))
        self.meanings = collections.defaultdict(lambda: collections.defaultdict(set))


def scoped_key(key):
    parts = (key or "").split("|")
    return (len(parts) == 4 and parts[0].startswith("Code/")
            and parts[1] in ("param", "local") and bool(parts[2]) and bool(parts[3]))


def canon(name):
    """Word order, plurals and common abbreviations are style, not meaning."""
    words = re.findall(r"[A-Z]+(?![a-z])|[A-Z]?[a-z]+|\d+", re.sub(r"^[msg]_", "", name or ""))
    words = [SYNONYMS.get(w.lower(), w.lower()) for w in words]
    return " ".join(sorted(w[:-1] if len(w) > 3 and w.endswith("s") else w for w in words))


def digest(key, name):
    return hash_canon(key, canon(name))


def hash_canon(key, canonical):
    return hashlib.sha256(f"{key}|{canonical}".encode()).hexdigest()[:24]


def worker_identity(root=None):
    """This environment's worker id, `w-<12 hex>`. The raw identity is
    BFME_CLAIM_OWNER / BFME_RUN_ID through tools/claims.py's owner(), else
    CLAUDE_CODE_SESSION_ID, else claims.owner()'s default (branch or
    user@host/checkout): never a value the voter passes on the command line."""
    env = os.environ
    if env.get("BFME_CLAIM_OWNER") or env.get("BFME_RUN_ID") or not env.get("CLAUDE_CODE_SESSION_ID"):
        import claims
        raw = "owner:" + claims.owner(root)
    else:
        raw = "session:" + env["CLAUDE_CODE_SESSION_ID"]
    return "w-" + hashlib.sha256(raw.encode("utf-8")).hexdigest()[:12]


def tally(votes, meaning_votes=()):
    """key -> hash -> {worker: model}. A vote without a well-formed worker id
    counts for nothing: it cannot be told apart from its voter's other votes."""
    votes = list(votes)
    out = VoteTally()
    bindings = {tuple(v.get(c, "") for c in VOTE_COLUMNS) for v in votes}
    for v in votes:
        worker = (v.get("worker") or "").strip()
        if WORKER.fullmatch(worker):
            out[v.get("key", "")][v.get("hash", "")][worker] = v.get("model", "")
    for v in meaning_votes:
        if (scoped_key(v.get("key")) and tuple(v.get(c, "") for c in VOTE_COLUMNS) in bindings
                and HASH.fullmatch(v.get("meaning") or "") and WORKER.fullmatch(v.get("worker") or "")):
            out.meanings[v["key"]][v["hash"], v["worker"]].add(v["meaning"])
    return out


def disputed(agreed_rows):
    """key -> canon spellings a dispute refused for it."""
    out = collections.defaultdict(set)
    for row in agreed_rows:
        if row.get("status") == "disputed":
            out[row.get("key", "")].add(canon(row.get("new", "")))
            meaning = record_meaning(row.get("id"))
            if meaning:
                out[row.get("key", "")].add("~meaning:" + meaning)
    return out


def support(counts, refused, key, name, meaning=None):
    """(workers, rivals, meaning hash) bound to votes for this exact key/name.

    Annotated aliases share support only under identical descriptors. Unknown
    legacy votes inherit a meaning only for the exact same spelling with one
    unambiguous role. Conflicting descriptors never collapse into one vote.
    """
    gone = refused.get(key, ())
    banned = {hash_canon(key, c) for c in gone if not c.startswith("~meaning:")}
    blocked_meanings = {c[len("~meaning:"):] for c in gone if c.startswith("~meaning:")}
    annotations = getattr(counts, "meanings", {}).get(key, {})
    roles = collections.defaultdict(set)
    for (spelling, _worker), values in annotations.items():
        roles[spelling].update(values)
    groups = collections.defaultdict(dict)
    spellings = collections.defaultdict(set)
    for spelling, voters in counts[key].items():
        if spelling in banned:
            continue
        for worker, model in voters.items():
            values = annotations.get((spelling, worker), set())
            if not values and len(roles[spelling]) == 1:
                values = roles[spelling]
            if len(values) == 1:
                role = next(iter(values))
                if role in blocked_meanings:
                    continue
                group = "meaning:" + role
            elif values:
                group = "conflicting:" + worker + ":" + spelling
            else:
                group = "spelling:" + spelling
            groups[group][worker] = model
            spellings[group].add(spelling)
    wanted = digest(key, name)
    candidates = [g for g in groups if wanted in spellings[g]
                  and (meaning is None or g == "meaning:" + meaning)]
    if len(candidates) != 1:
        return {}, list(groups.values()), meaning
    chosen = candidates[0]
    role = chosen[len("meaning:"):] if chosen.startswith("meaning:") else None
    return dict(groups[chosen]), [v for g, v in groups.items() if g != chosen], role


def review_workers(key, rivals):
    """One worker for an uncontested scoped name; two for every other name.

    A missing or malformed key never opts into lighter review. Rivals are
    already filtered for disputed spellings by the caller.
    """
    return 1 if scoped_key(key) and not any(rivals) else 2


def review_detail(key, voters, rivals=()):
    policy = "single-worker scoped approval" if review_workers(key, rivals) == 1 and len(voters) == 1 \
        else "two-agent agreement"
    agents = ";".join(f"{w}@{m}" for w, m in sorted(voters.items()))
    return f"{policy}: {agents}"


def wins(mine, rivals, *, lead=2, min_models=1, key=None):
    """`mine` and each rival are {worker: model} for one spelling. Uncontested
    scoped keys need one worker; all others need two and the requested lead.
    `min_models` applies to either policy. `key=None` keeps the two-worker rule."""
    needed = review_workers(key, rivals)
    # --lead still governs competing proposals; an uncontested local or
    # parameter needs one proposal. --min-models remains an independent floor.
    margin = 1 if needed == 1 else lead
    return (len(mine) >= needed and len(set(mine.values())) >= min_models
            and len(mine) - max((len(r) for r in rivals), default=0) >= margin)


def standing(votes, agreed_rows, key, name, *, meaning_votes=(), meaning=None):
    """(mine, rivals) for spelling `name` of `key`: the workers that voted its
    hash, and the voter sets of every other spelling not refused by a dispute."""
    mine, rivals, _ = support(tally(votes, meaning_votes), disputed(agreed_rows), key, name, meaning)
    return mine, rivals


def verify(votes, agreed_rows, key, name, *, lead=1, meaning_votes=(), meaning=None):
    """Problems (empty when the votes carry `name` for `key`): the floor the
    engine enforces whatever --lead the lane ran with: one worker for an
    uncontested scoped name, otherwise two and no equally supported rival
    (`lead` 1). The spelling and the record must not be disputed."""
    problems = []
    if canon(name) in disputed(agreed_rows).get(key, ()):
        problems.append(f"{name} was disputed for {key}")
    if meaning and "~meaning:" + meaning in disputed(agreed_rows).get(key, ()):
        problems.append("the proposed meaning was disputed")
    mine, rivals = standing(votes, agreed_rows, key, name, meaning_votes=meaning_votes, meaning=meaning)
    needed = review_workers(key, rivals)
    if len(mine) < needed:
        requirement = "one is needed for an uncontested scoped name" if needed == 1 else "two are needed"
        problems.append(f"{len(mine)} distinct worker(s) voted it in {VOTES} ({requirement})")
    top = max((len(r) for r in rivals), default=0)
    if mine and len(mine) - top < (1 if needed == 1 else lead):
        problems.append(f"a rival spelling has {top} worker(s) against its {len(mine)}")
    return problems


def resolved_workers(votes, agreed_rows, resolutions, key, name, source_sha):
    """Original voters who accepted a spelling after seeing the disagreement.

    A blind vote for the selected spelling is itself an acceptance. A later
    acceptance can only come from one of the original voters and binds to the
    unchanged source. Every voter must accept when more than two participated.
    """
    selected = digest(key, name)
    voters = {}
    for row in votes:
        if row.get("key") == key and WORKER.fullmatch(row.get("worker") or "") \
                and HASH.fullmatch(row.get("hash") or ""):
            voters.setdefault(row["worker"], row.get("model", ""))
    accepted = {row["worker"] for row in votes if row.get("key") == key
                and row.get("hash") == selected and row.get("worker") in voters}
    accepted.update(row["worker"] for row in resolutions if row.get("key") == key
                    and row.get("hash") == selected and row.get("name") == name
                    and row.get("source_sha") == source_sha
                    and row.get("worker") in voters and len((row.get("reason") or "").strip()) >= 12)
    return voters, accepted


def verify_resolution(votes, agreed_rows, resolutions, key, name, source_sha):
    problems = []
    if not re.fullmatch(r"[0-9a-f]{64}", source_sha or ""):
        problems.append("missing source fingerprint")
    if canon(name) in disputed(agreed_rows).get(key, ()):
        problems.append("chosen spelling was disputed")
    voters, accepted = resolved_workers(votes, agreed_rows, resolutions, key, name, source_sha)
    if len(voters) < 2:
        problems.append("resolution needs two original independent voters")
    if accepted != set(voters):
        problems.append(f"only {len(accepted)} of {len(voters)} original voters accepted this spelling")
    return problems


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("whoami", help="print this environment's worker id")
    args = ap.parse_args(argv)
    if args.cmd == "whoami":
        print(worker_identity())
    return 0


if __name__ == "__main__":
    sys.exit(main())
