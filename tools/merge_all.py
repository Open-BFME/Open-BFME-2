#!/usr/bin/env python3
"""Bulk TU merges: `tu_skeleton.py --merge-all` walks the whole approved-TU queue.

WHY. Seats carried merges one TU at a time (`--merge TU --dry-run`, read the
rejects, `--merge TU`, commit). The verification is mechanical; only the
rejects need a decision. This runs the same merge (tu_skeleton.merge: donor
accretion, the seed screen, distinct spelling strategies, LinkGuard and the
protected-register carry, so a merge never loses a matched row or a unit's
link) over every queued TU, commits each verified TU as its own commit through
the hooks, and records everything it could not merge as a ranked decision
queue that the picker serves (repair_queue.consolidation_items).

ORDER. tu_skeleton.queue(): most donor files removed first. A TU whose scope
(the TU file, its donors, their rows) another seat claims is not attempted; it
is recorded as `claimed` with the holders.

PARALLEL. TUs are dispatched in waves of up to --jobs TUs whose file sets are
disjoint. Each runs in its own worker worktree (`<checkout>-ma<N>`, made with
tools/worktree_setup.py and reset to the integration tip before every wave),
so the per-file build caches, staging and claims never collide. A worker runs
`merge_all.py worker` inside its worktree, with that worktree's own tools, and
commits there through the hooks (`git -c core.hooksPath=.githooks commit`).
The coordinator then cherry-picks the wave's commits onto the invoking
checkout's branch in queue order. A cherry-pick that conflicts is aborted and
the TU is retried next pass, never resolved by hand. After every pick the
ledger is compared with the one before it: every matched row is still there,
and every row of an absorbed donor now names the TU; otherwise the pick is
undone and recorded.

RUN. Passes repeat until one merges nothing or --budget-min runs out (no new
wave starts after it; running workers finish). State lives in
build/merge_all/state.json: merged TUs, conflicts to retry, and failures keyed
by a digest of the TU's donor files (an unchanged failure is not retried; any
edit to a donor makes it eligible again). Re-running resumes. --dry-run runs
the merges with tu_skeleton's own --dry-run (compiles, writes nothing, claims
nothing) and reports; --static skips even the compiles and reports what the
queue alone shows. Nothing is pushed: after pushing the integrated branch,
`--merge-all --release` gives back the merged TUs' scope claims.

DECISIONS. build/merge_all/decisions.json, copied to the shared picker cache
(<git common dir>/bfme-picker-cache/merge_all/decisions.json), one item per
TU or donor not merged, ranked by the files merging it would remove:
  blocked-by-classes  compile reject of a donor whose private class views the
                      TU's other files declare differently, or a donor still
                      holding a private copy of a registered class: the class
                      list, linked to the header decision queue
                      (`next_work.py --tier header`, `header_adopt_lane.py order --merges`)
  split               a mixed donor file: which rows go to which TU
                      (`tu_skeleton.py --split FILE --for TU`)
  compile-error       any other compile reject: the first diagnostic
  link-regression     LinkGuard: the units and symbols that would stop linking
  row-loss            compiles, but loses matched rows
  claimed             another seat holds part of the scope: the holders
  refused / baseline / flags / hook / conflict / other
The picker serves split, compile-error and link-regression items.

  python3 tools/tu_skeleton.py --merge-all --dry-run --static     the queue, no compiles
  python3 tools/tu_skeleton.py --merge-all --dry-run --jobs 4     what would merge now
  python3 tools/tu_skeleton.py --merge-all --jobs 4 --budget-min 120
  python3 tools/tu_skeleton.py --merge-all --release              after pushing
"""
import argparse
import collections
import concurrent.futures as cf
import csv
import hashlib
import io
import json
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

STATE_DIR = ROOT / "build" / "merge_all"
LEDGER = "reverse/functions.csv"
INDEX_FILES = ("build/link_census/link_index.pkl",)     # copied into each worker (LinkGuard reads it)
SERVED = ("split", "compile-error", "link-regression")  # what the picker serves as seat decisions
KIND_ORDER = ("split", "compile-error", "link-regression", "blocked-by-classes", "row-loss", "claimed",
              "conflict", "hook", "refused", "baseline", "flags", "other")
HEADER_QUEUE_LINK = "python3 tools/next_work.py --tier header; python3 tools/header_adopt_lane.py order --merges"
MANGLED = re.compile(r"\?[A-Za-z0-9_?@$]+")
DIAGNOSTIC = re.compile(r"error [A-Z]+\d+[^|]*")
FAILURE_KINDS = ("compile-error", "blocked-by-classes", "link-regression", "row-loss", "baseline", "flags",
                 "refused", "split", "hook", "other")


# ---------------------------------------------------------------- git

def git(cwd, *args, check=True, env=None):
    done = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True, errors="replace",
                          env={**os.environ, **(env or {})})
    if check and done.returncode:
        raise RuntimeError(f"git {' '.join(args)} in {cwd}: {(done.stderr or done.stdout).strip()[:400]}")
    return done


def head(cwd):
    return git(cwd, "rev-parse", "HEAD").stdout.strip()


def dirty(cwd, paths=("Code", "reverse", "tools", "docs")):
    return [line for line in git(cwd, "status", "--porcelain", "--untracked-files=no", "--", *paths).stdout
            .splitlines() if line.strip()]


# ---------------------------------------------------------------- plan

def file_digest(root, files):
    """A digest of `files`' contents (a missing file counts): an unchanged failure is not retried."""
    h = hashlib.sha256()
    for f in sorted(files):
        h.update(f.encode() + b"\0")
        try:
            h.update(hashlib.sha256((Path(root) / f).read_bytes()).digest())
        except OSError:
            h.update(b"missing")
    return h.hexdigest()[:16]


def plan(entries, donors_of, held_keys, key_of, claim_keys):
    """Jobs for queue `entries` (tu_skeleton.queue order): {tu, removes, rows, files, donors, mixed,
    refused, held}. `held` lists the scope keys another seat holds (the TU is then not run)."""
    jobs = []
    for entry in entries:
        tu = entry["tu"]
        don, mixed, refused = donors_of(tu)
        keys = claim_keys(tu, don)
        held = [k for k in keys if key_of(k) in held_keys]
        jobs.append({"tu": tu, "removes": entry.get("removes", len(don) - 1), "rows": entry.get("rows", 0),
                     "files": sorted(set(don) | {tu}), "donors": {f: len(r) for f, r in don.items()},
                     "mixed": dict(mixed), "refused": dict(refused), "held": held})
    return jobs


def waves(jobs, width):
    """Lists of up to `width` jobs with pairwise disjoint file sets, in queue order: a job
    that shares a file with one already in the wave waits for a later wave."""
    pending, out = list(jobs), []
    while pending:
        wave, used, rest = [], set(), []
        for job in pending:
            files = set(job["files"])
            if len(wave) < width and not files & used:
                wave.append(job)
                used |= files
            else:
                rest.append(job)
        out.append(wave)
        pending = rest
    return out


# ---------------------------------------------------------------- decisions

def class_blockers(tu, donor, payload, header_queue, reconcile=""):
    """Classes that block `donor` in `tu`: blocking views from the header lane's merge ranking,
    registered classes it still copies (header_queue.tsv) and the tu_views hint's classes."""
    classes = set(header_queue.get(donor, ()))
    for name, d in ((payload or {}).get("classes") or {}).items():
        if tu in d.get("tus", ()) and donor in d.get("files", ()):
            classes.add(name)
    if reconcile and "views of" in reconcile:
        named = reconcile.split("views of", 1)[1].split("(", 1)[0]
        classes.update(c.strip(" .") for c in named.split(",") if c.strip(" .") and c.strip(" .") != "...")
    return sorted(classes)


def first_diagnostic(reason):
    found = DIAGNOSTIC.search(reason or "")
    return found.group().strip() if found else (reason or "").split(" | ")[0][:200]


def item(kind, tu, file, frees, rows, reason, **extra):
    return {"kind": kind, "tu": tu, "file": file, "frees": frees, "rows": rows, "reason": reason, **extra}


def split_items(tu, mixed, breakdown):
    """One `split` item per mixed donor: which of its rows go where. It frees the file when every
    row it holds has an approved TU (splitting it to each empties it)."""
    out = []
    for f, foreign in sorted(mixed.items()):
        rows = breakdown(f)
        where = {t or "(no approved TU)": len(r) for t, r in rows.items()}
        mine = where.get(tu, 0)
        out.append(item("split", tu, f, 0 if "" in rows else 1, mine,
                        f"{f} holds {mine} row(s) approved for {tu} and {foreign} of other TUs",
                        split=where, start=f"python3 tools/tu_skeleton.py --split {f} --for {tu} --dry-run"))
    return out


def classify(job, report, payload, header_queue, breakdown):
    """Decision items for one TU's merge report (tu_skeleton.merge's dict); with report None
    (--static) what the queue alone shows: splits, refusals and the donors whose class views
    the header lane's ranking says disagree (`static: true`, not compiled)."""
    tu, out = job["tu"], []
    donors = job["donors"]
    out += split_items(tu, job["mixed"], breakdown)
    for f, why in sorted(job["refused"].items()):
        out.append(item("refused", tu, f, 1, 0, f"{f} cannot be absorbed mechanically: {why}"))
    if report is None:
        for f in sorted(donors):
            classes = class_blockers(tu, f, payload, header_queue)
            if classes and f != tu:
                out.append(item("blocked-by-classes", tu, f, 1, donors[f], "private class views disagree in the "
                                "TU (header lane ranking; not compiled)", classes=classes, static=True,
                                header_queue=HEADER_QUEUE_LINK))
        return out
    blocked = report.get("blocked", "")
    if blocked.startswith("held by another worker"):
        return out + [item("claimed", tu, tu, job["removes"], job["rows"], blocked,
                           holders=blocked.split(":", 1)[1].strip().split(", "))]
    if blocked.startswith("link guard"):
        return out + [item("link-regression", tu, tu, job["removes"], job["rows"], blocked,
                           symbols=sorted(set(MANGLED.findall(blocked)))[:20])]
    if blocked.startswith("protected registers"):
        return out + [item("other", tu, tu, job["removes"], job["rows"], blocked)]
    if blocked.startswith("TU path exists"):
        return out + [item("split", tu, tu, job["removes"], job["rows"], blocked,
                           start=f"python3 tools/tu_skeleton.py --split {tu}")]
    if blocked.startswith("the TU file's own rows"):
        return out + [item("baseline", tu, tu, job["removes"], job["rows"], blocked)]
    adopt = report.get("adopt_first") or {}
    for f, why in sorted((report.get("rejected") or {}).items()):
        why = str(why)
        rows = donors.get(f, 0)
        if why.startswith("link:"):
            out.append(item("link-regression", tu, f, 1, rows, why, symbols=sorted(set(MANGLED.findall(why)))[:20]))
        elif why.startswith("compile"):
            classes = class_blockers(tu, f, payload, adopt, report.get("reconcile", ""))
            if classes:
                out.append(item("blocked-by-classes", tu, f, 1, rows, why, classes=classes,
                                diagnostic=first_diagnostic(why), header_queue=HEADER_QUEUE_LINK))
            else:
                out.append(item("compile-error", tu, f, 1, rows, why, diagnostic=first_diagnostic(why)))
        elif why.startswith("bytes"):
            out.append(item("row-loss", tu, f, 1, rows, f"{f} compiles in the merged TU but loses matched rows"))
        elif why == "no baseline match":
            out.append(item("baseline", tu, f, 1, rows, f"{f}'s own rows do not match alone under the verifier"))
        elif "flag override" in why:
            out.append(item("flags", tu, f, 1, rows, why))
        else:
            out.append(item("other", tu, f, 1, rows, why))
    if blocked and not report.get("rejected"):
        out.append(item("other", tu, tu, job["removes"], job["rows"], blocked))
    return out


def rank(items):
    order = {k: i for i, k in enumerate(KIND_ORDER)}
    return sorted(items, key=lambda i: (-i["frees"], -i["rows"], order.get(i["kind"], 99), i["tu"], i["file"]))


def histogram(items):
    """{kind: [items, files freed]}."""
    out = collections.OrderedDict()
    for kind in KIND_ORDER:
        mine = [i for i in items if i["kind"] == kind]
        if mine:
            out[kind] = [len(mine), sum(i["frees"] for i in mine)]
    return out


def shared_decisions_path():
    import repair_queue
    return repair_queue.cache_dir() / "merge_all" / "decisions.json"


def write_decisions(items, commit, state_dir=None, shared=None):
    state_dir = Path(state_dir or STATE_DIR)
    doc = {"measured_at": commit, "time": int(time.time()), "histogram": histogram(items), "items": rank(items)}
    for path in (state_dir / "decisions.json", shared or shared_decisions_path()):
        try:
            path.parent.mkdir(parents=True, exist_ok=True)
            tmp = path.with_suffix(f".{os.getpid()}.tmp")
            tmp.write_text(json.dumps(doc, indent=1, sort_keys=True), encoding="utf-8")
            os.replace(tmp, path)
        except OSError:
            pass
    return doc


# ---------------------------------------------------------------- state

class State:
    """build/merge_all/state.json: what earlier runs did, so a run resumes."""

    def __init__(self, path):
        self.path = Path(path)
        try:
            self.data = json.loads(self.path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            self.data = {}
        for key in ("merged", "failed", "retry", "decisions"):
            self.data.setdefault(key, {})

    def save(self):
        self.path.parent.mkdir(parents=True, exist_ok=True)
        tmp = self.path.with_suffix(".tmp")
        tmp.write_text(json.dumps(self.data, indent=1, sort_keys=True), encoding="utf-8")
        os.replace(tmp, self.path)

    def skip(self, job, digest):
        """Why `job` is not run again, or None."""
        if job["tu"] in self.data["retry"]:
            return None
        failed = self.data["failed"].get(job["tu"])
        if failed and failed.get("digest") == digest:
            return f"failed before with the same donors ({failed.get('kind')})"
        return None

    def merged(self, tu, commit, keys, follow_up):
        kept = self.data["merged"].get(tu, {}).get("claim_keys", [])   # an earlier partial merge's, unreleased
        self.data["merged"][tu] = {"commit": commit, "claim_keys": sorted(set(kept) | set(keys)),
                                   "follow_up": follow_up}
        self.data["retry"].pop(tu, None)
        self.data["failed"].pop(tu, None)

    def failed(self, tu, digest, kind):
        self.data["failed"][tu] = {"digest": digest, "kind": kind}
        self.data["retry"].pop(tu, None)

    def retry(self, tu, why):
        self.data["retry"][tu] = why


# ---------------------------------------------------------------- row check

def ledger_rows(text):
    return [r for r in csv.DictReader(io.StringIO(text)) if r.get("status") == "matched"]


def rows_kept(before, after, tu, absorbed):
    """Problems with a merge's ledger change (CSV texts): a matched row lost or added, or a row of an
    absorbed donor that does not now name the TU. [] when every row survived the move."""
    key = lambda r: (r.get("target_rva", ""), r.get("name", ""))   # noqa: E731
    b, a = ledger_rows(before), ledger_rows(after)
    problems = []
    lost = collections.Counter(map(key, b)) - collections.Counter(map(key, a))
    added = collections.Counter(map(key, a)) - collections.Counter(map(key, b))
    if lost:
        problems.append(f"{sum(lost.values())} matched row(s) lost: {sorted(lost)[:3]}")
    if added:
        problems.append(f"{sum(added.values())} matched row(s) appeared: {sorted(added)[:3]}")
    where = {key(r): r["source"] for r in a}
    absorbed = set(absorbed) - {tu}
    stray = [k for k in map(key, (r for r in b if r["source"] in absorbed)) if where.get(k) != tu]
    if stray:
        problems.append(f"{len(stray)} row(s) of absorbed donors do not name {tu}: {stray[:3]}")
    return problems


# ---------------------------------------------------------------- worker (runs inside a worktree)

def commit_message(report):
    lines = [report["subject"], ""]
    if report.get("trailer"):
        lines.append(report["trailer"])
    lines += list(report.get("debt-retired") or [])
    return "\n".join(lines).rstrip() + "\n"


def worker(tu, out, dry_run=False, merge=None, commit=None, release=None, scope=None):
    """Merge `tu` in this checkout; on success commit it here. Writes the result to `out`:
    {report, commit, claim_keys, hook}. `merge`, `commit`, `release` and `scope` (the merge's
    claim keys, read before the merge deletes its donors) are injectable."""
    import tu_skeleton as T
    merge = merge or T.merge
    keys = [] if dry_run else (scope or (lambda: T.claim_keys(tu, T.donors(tu, T.skeleton(tu))[0])))()
    report = merge(tu, dry_run=dry_run, claim=not dry_run)
    report.pop("text", None)
    result = {"tu": tu, "report": report, "commit": None, "claim_keys": [], "hook": None}
    if not dry_run and report.get("subject") and not report.get("blocked"):
        result["claim_keys"] = list(keys)
        ok, output = (commit or _commit)(commit_message(report))
        if ok:
            result["commit"] = head(T.ROOT)
        else:   # the hooks refused it: put the tree back and give the scope back
            git(T.ROOT, "reset", "-q", "--hard", "HEAD")
            git(T.ROOT, "clean", "-fdq", "--", "Code", "reverse", check=False)
            (release or (lambda keys: T.claims.release(keys)))(result["claim_keys"])
            result["claim_keys"] = []
            result["hook"] = output[-1500:]
    Path(out).write_text(json.dumps(result, indent=1, default=str), encoding="utf-8")
    return result


def _commit(message):
    import tu_skeleton as T
    done = subprocess.run(["git", "-c", "core.hooksPath=.githooks", "commit", "-q", "-F", "-"], cwd=T.ROOT,
                          input=message, capture_output=True, text=True, errors="replace")
    return done.returncode == 0, (done.stdout + done.stderr)


# ---------------------------------------------------------------- coordinator

class Workers:
    """Worker worktrees `<checkout>-ma<N>` beside the invoking checkout (short paths)."""

    def __init__(self, root=ROOT, base_dir=None, create=None, prepare=None):
        self.root = Path(root)
        self.base_dir = Path(base_dir) if base_dir else self.root.parent
        self._create, self._prepare = create, prepare

    def path(self, i):
        return self.base_dir / f"{self.root.name}-ma{i}"

    def ready(self, i, tip):
        """The worktree for slot `i`, created if missing, at `tip` with a clean tree, its submodule at
        tip's pin and the coordinator's census index."""
        import worktree_setup
        wt = self.path(i)
        if not (wt / ".git").exists():
            (self._create or (lambda p, b: worktree_setup.create(str(p), branch=f"merge-all/{self.root.name}-{i}",
                                                                 base=b, cwd=str(self.root))))(wt, tip)
        git(wt, "checkout", "-q", "--detach", tip)
        git(wt, "reset", "-q", "--hard", tip)
        git(wt, "clean", "-fdq", "--", "Code", "reverse", "docs", check=False)
        (self._prepare or (lambda p: worktree_setup.prepare(str(p))))(wt)
        for rel in INDEX_FILES:
            src, dst = self.root / rel, wt / rel
            if src.exists() and (not dst.exists() or dst.stat().st_mtime < src.stat().st_mtime):
                dst.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(src, dst)
        return wt


def run_worker(wt, tu, dry_run, owner):
    """`merge_all.py worker` inside worktree `wt` (its own tools); the result dict."""
    out = Path(wt) / "build" / "merge_all" / f"worker-{hashlib.sha1(tu.encode()).hexdigest()[:10]}.json"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.unlink(missing_ok=True)
    env = {**os.environ, **({"BFME_CLAIM_OWNER": owner} if owner else {})}
    done = subprocess.run([sys.executable, "tools/merge_all.py", "worker", "--tu", tu, "--out", str(out)]
                          + (["--dry-run"] if dry_run else []), cwd=wt, env=env,
                          capture_output=True, text=True, errors="replace")
    try:
        return json.loads(out.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return {"tu": tu, "report": {"blocked": "worker failed: " + (done.stderr or done.stdout)[-600:]},
                "commit": None, "claim_keys": [], "hook": None}


def integrate(root, commit, tu, absorbed):
    """Cherry-pick a worker's `commit` onto `root`'s branch: ("merged", sha), ("conflict", why)
    or ("row-loss", why) after undoing a pick that changed the ledger wrongly."""
    before = git(root, "show", f"HEAD:{LEDGER}").stdout
    done = git(root, "cherry-pick", "--allow-empty", commit, check=False)
    if done.returncode:
        git(root, "cherry-pick", "--abort", check=False)
        return "conflict", (done.stderr or done.stdout).strip()[:400]
    after = git(root, "show", f"HEAD:{LEDGER}").stdout
    problems = rows_kept(before, after, tu, absorbed)
    if problems:
        git(root, "reset", "-q", "--hard", "HEAD~1")
        return "row-loss", "; ".join(problems)
    return "merged", head(root)


def coordinate(args, ts=None, run=None, workers=None, integrate_fn=None, now=time.time, log=print, root=ROOT):
    """The --merge-all run. `ts` (tu_skeleton), `run` (run_worker), `workers` (Workers) and
    `integrate_fn` are injectable; returns the decisions document."""
    if ts is None:
        import tu_skeleton as ts
    run = run or run_worker
    integrate_fn = integrate_fn or integrate
    state_dir = Path(getattr(args, "state_dir", None) or STATE_DIR)
    state = State(state_dir / "state.json")
    deadline = now() + args.budget_min * 60 if args.budget_min else None
    if not args.dry_run:
        busy = dirty(root)
        if busy:
            raise SystemExit("merge-all: the invoking checkout has uncommitted changes under Code/, reverse/, "
                             "tools/ or docs/ (worker worktrees check out the committed tip); commit or move "
                             "them first: " + "; ".join(busy[:5]))
    if not args.static:
        fetch_census_index(root)
    payload = header_payload()
    header_queue = ts.header_queue_rows()
    owner = "" if args.dry_run else ts.claims.owner(root)
    workers = workers or Workers(root, getattr(args, "worktree_root", None))
    decisions = {} if args.dry_run else dict(state.data["decisions"])
    merged, files_removed, tried, out_of_time = [], 0, set(), False

    def give_back(keys):    # an unintegrated attempt's claims, minus those earlier unreleased merges still need
        kept = {k for m in state.data["merged"].values() for k in m.get("claim_keys", [])}
        ts.claims.release([k for k in keys if k not in kept])
    for _pass in range(max(1, args.passes)):
        ts._CACHE.clear()
        entries = ts.queue(args.under, args.limit, root=root)
        try:
            held = set(ts.claims.busy_keys(root))   # lock keys: a class claim covers its members' files
        except Exception:   # noqa: BLE001 - no origin: nothing is known to be held
            held = set()
        jobs = plan(entries, lambda tu: ts.donors(tu, ts.skeleton(tu)), held, ts.claims.key_of, ts.claim_keys)
        runnable = []
        for job in jobs:
            tu = job["tu"]
            if tu in tried:
                continue
            if job["held"]:
                tried.add(tu)
                decisions[tu] = split_items(tu, job["mixed"], ts.breakdown) + [
                    item("claimed", tu, tu, job["removes"], job["rows"],
                         f"another seat holds {len(job['held'])} of its scope key(s)", holders=job["held"][:8])]
                continue
            job["digest"] = file_digest(root, job["files"])
            if not args.dry_run and state.skip(job, job["digest"]):
                continue    # its recorded decisions stand
            runnable.append(job)
        progress = 0
        for wave in waves(runnable, max(1, args.jobs)):
            if deadline and now() >= deadline:
                out_of_time = True
                log(f"merge-all: the {args.budget_min:g}-minute budget is spent; run it again to resume")
                break
            if args.static:
                for job in wave:
                    tried.add(job["tu"])
                    decisions[job["tu"]] = classify(job, None, payload, header_queue, ts.breakdown)
                continue
            tip = head(root)
            slots = [root] * len(wave) if args.dry_run else [workers.ready(i + 1, tip) for i in range(len(wave))]
            with cf.ThreadPoolExecutor(max_workers=len(wave)) as pool:
                results = list(pool.map(lambda pair: run(pair[0], pair[1]["tu"], args.dry_run, owner),
                                        zip(slots, wave)))
            for job, res in zip(wave, results):     # integrated in queue order
                tu = job["tu"]
                tried.add(tu)
                report = res.get("report") or {}
                items = classify(job, report, payload, header_queue, ts.breakdown)
                if res.get("hook"):
                    items.append(item("hook", tu, tu, job["removes"], job["rows"], "the commit hooks refused the "
                                      "verified merge", evidence=res["hook"][-600:]))
                accepted = report.get("accepted") or []
                gone = [f for f in accepted if f != tu]
                if args.dry_run:
                    if accepted and not report.get("blocked"):
                        merged.append(tu)
                        files_removed += len(gone)
                elif res.get("commit"):
                    status, detail = integrate_fn(root, res["commit"], tu, accepted)
                    if status == "merged":
                        state.merged(tu, detail, res.get("claim_keys", []), report.get("follow-up") or [])
                        merged.append(tu)
                        files_removed += len(gone)
                        progress += 1
                        log(f"merge-all: {tu}: {len(gone)} file(s) absorbed ({detail[:10]})")
                    elif status == "conflict":
                        give_back(res.get("claim_keys", []))   # not integrated: the next pass re-claims
                        state.retry(tu, detail)
                        tried.discard(tu)
                        items.append(item("conflict", tu, tu, job["removes"], job["rows"],
                                          "the verified merge does not apply on the integrated branch; retried "
                                          "next pass", evidence=detail))
                    else:
                        give_back(res.get("claim_keys", []))
                        state.failed(tu, job["digest"], status)
                        items.append(item(status, tu, tu, job["removes"], job["rows"], detail))
                else:
                    kinds = [i["kind"] for i in items if i["kind"] not in ("split", "refused")]
                    state.failed(tu, job["digest"], "hook" if res.get("hook") else (kinds or ["none"])[0])
                decisions[tu] = items
                if not args.dry_run:
                    state.data["decisions"] = decisions
                    state.save()
        if out_of_time or args.dry_run or args.static or not progress:
            break
    # an item whose file is gone (absorbed by a merge, deleted) leaves the decision queue
    live = {tu: kept for tu, items in decisions.items()
            if (kept := [i for i in items if (Path(root) / i["file"]).exists()])}
    if not args.dry_run:
        state.data["decisions"] = live
        state.save()
    doc = write_decisions([i for items in live.values() for i in items], head(root), state_dir)
    doc["merged"], doc["files_removed"] = merged, files_removed
    report_run(doc, args, len(tried), log)
    if not args.dry_run and merged:
        log("merge-all: after pushing the branch: python3 tools/tu_skeleton.py --merge-all --release")
    return doc


def fetch_census_index(root):
    """LinkGuard's census index, fetched once here (workers copy it or share this checkout's)
    rather than by every concurrent worker; a failure leaves each merge's own guard to block."""
    if Path(root).resolve() != ROOT.resolve():
        return
    try:
        import contextlib
        import link_check
        if not link_check.INDEX.exists() and os.environ.get("BFME_LINK_GUARD_FETCH", "on") != "off":
            with contextlib.redirect_stdout(io.StringIO()):
                link_check.fetch_index(objects=False)
    except BaseException as exc:  # noqa: BLE001 - LinkGuard blocks merges itself without an index
        if isinstance(exc, KeyboardInterrupt):
            raise


def header_payload():
    """The header lane's cached merge ranking (never computed here), for class blockers."""
    try:
        import header_adopt_lane
        return header_adopt_lane.cached_merge_payload(header_adopt_lane.merge_inputs()) or {}
    except Exception:   # noqa: BLE001 - class attribution is evidence only
        return {}


def report_run(doc, args, seen, log=print):
    mode = "static (no compiles)" if args.static else "dry run" if args.dry_run else "run"
    hist = doc["histogram"]
    if not args.static:
        log(f"merge-all {mode}: {len(doc['merged'])} TU(s) merge now, {doc['files_removed']} file(s) removed; "
            f"{seen} TU(s) examined")
    else:
        log(f"merge-all {mode}: {seen} TU(s) in the queue")
    log("blockers (items, files freed):")
    for kind, (n, frees) in hist.items():
        log(f"  {kind:<20} {n:6} {frees:6}")
    log(f"decision queue: {STATE_DIR.relative_to(ROOT).as_posix()}/decisions.json "
        f"(served: {', '.join(SERVED)}; python3 tools/next_work.py --tier consolidate)")


def release(state_dir=None, release_fn=None):
    """Give back the scope claims of the TUs this run merged (after the branch is pushed)."""
    state = State(Path(state_dir or STATE_DIR) / "state.json")
    if release_fn is None:
        import claims
        release_fn = claims.release
    keys = sorted({k for m in state.data["merged"].values() for k in m.get("claim_keys", [])})
    done = release_fn(keys) if keys else []
    for m in state.data["merged"].values():
        m["claim_keys"] = []
    state.save()
    print(f"merge-all: released {len(done)} of {len(keys)} scope claim(s)")
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    w = sub.add_parser("worker", help="merge one TU in this checkout (run by the coordinator)")
    w.add_argument("--tu", required=True)
    w.add_argument("--out", required=True)
    w.add_argument("--dry-run", action="store_true")
    a = sub.add_parser("run")
    add_run_args(a)
    a.add_argument("--dry-run", action="store_true")
    a.add_argument("--under", default="")
    a.add_argument("--limit", type=int)
    args = ap.parse_args(argv)
    if args.cmd == "worker":
        worker(args.tu, args.out, args.dry_run)
        return 0
    return run_main(args)


def add_run_args(ap):
    ap.add_argument("--jobs", type=int, default=1, help="TUs merged at once, each in its own worktree")
    ap.add_argument("--budget-min", type=float, default=0, help="start no wave after this many minutes")
    ap.add_argument("--passes", type=int, default=5, help="passes over the queue (conflicts retry next pass)")
    ap.add_argument("--static", action="store_true", help="with --dry-run: no compiles, the queue alone")
    ap.add_argument("--release", action="store_true", help="release merged TUs' scope claims (after pushing)")
    ap.add_argument("--worktree-root", help="where worker worktrees live (default: beside this checkout)")
    ap.add_argument("--state-dir", help=argparse.SUPPRESS)


def run_main(args):
    if args.release:
        return release(args.state_dir)
    if args.static:
        args.dry_run = True
    doc = coordinate(args)
    return 0 if doc["merged"] or args.dry_run else 2


if __name__ == "__main__":
    sys.exit(main())
