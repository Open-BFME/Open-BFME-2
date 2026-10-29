#!/usr/bin/env python3
"""Receipts of byte-verification, so a push re-verifies only what changed since.

WHY. pre-commit already byte-verifies every unit a commit can affect, and a
push then verified the same units again; a push that lost the race to master
verified them a third time after its rebase. Each costs seconds to minutes.

WHAT. A receipt says: these units were byte-verified at this tree, by the
verifier with this identity (full_gate_receipt.verifier_identity over the
tools/ files the build loaded, .githooks/ and the tree-wide baselines).

  * pre-commit records a COMMIT receipt keyed by (tree, parent tree): its scope
    (every unit the staged change can affect: staged sources, changed rows,
    callers of changed names, header dependents) and, of those, the units its
    verify proved for the committed content (compile receipt current, no
    unstaged edit in the source or a recorded header). A commit whose pre-commit
    ran a full gate records nothing.
  * pre-push records a PUSH receipt for the pushed commit: every unit in its
    scope, each byte-verified there or proven by a receipt.

HOW pre-push uses them, for a scoped push from base B to tip X:
  * chain: when every commit in B..X (first-parent, one parent each) has a
    commit receipt for its own tree and its parent's tree, and every receipt's
    verifier is X's, the union of their units was verified at the tree where
    each last changed; a later commit whose scope holds a unit proves it again
    or drops it. Those units are proven at X.
  * previous push: a push receipt for a commit H (the tip before a rebase:
    push.py names it, else the newest receipt whose base X descends from) whose
    verifier is X's proves its units at H. The hook computes scope_from(H) --
    the units the change from H to X can affect (master's commits since the
    lost race) -- and only those are verified again.
  * everything else in the scope is byte-verified as before; nothing outside
    the scope is touched (as before). An object that is not current is
    rebuilt and verified whatever the receipts say.
A missing, foreign or stale receipt (another verifier, another tree, a commit
made with --no-verify, an amended or rebased commit) proves nothing, so the
unit is verified. Receipts live in the git common directory; nothing is
trusted from another clone.

  python3 tools/push_receipts.py record-commit --tree T --parent P --loads DIR --scope-from LIST
  python3 tools/push_receipts.py record-push --commit X --base B --loads DIR --units-from LIST [--from H]
  python3 tools/push_receipts.py cover --base B --tip X      # chain-proven units, NUL-separated
  python3 tools/push_receipts.py previous --tip X [--hint H] # a push receipt to carry from, or nothing
  python3 tools/push_receipts.py units --push H --tip X      # H's units if its verifier is X's
  python3 tools/push_receipts.py stale --units-from LIST     # those whose object here is not current
"""
import argparse
import json
import os
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import full_gate_receipt  # noqa: E402

EMPTY_TREE = "4b825dc642cb6eb9a060e54bf8d69288fbee4904"
KEEP_HOURS = 48


def git(*args, check=True):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, check=check)


def folder():
    common = git("rev-parse", "--git-common-dir").stdout.strip()
    return (ROOT / common).resolve() / "bfme-push-receipts"


def read_list(path):
    raw = Path(path).read_bytes() if path else b""
    if raw and not raw.endswith(b"\0"):
        raise SystemExit("push_receipts: unterminated unit list")
    return sorted({item.decode("utf-8") for item in raw.split(b"\0") if item})


def write_list(units):
    sys.stdout.buffer.write(b"".join(u.encode("utf-8") + b"\0" for u in sorted(units)))


def loads_of(path):
    """build.py's BFME_GATE_LOADS entries, or None (then all of tools/ counts)."""
    return full_gate_receipt.gate_loads(path)


def identity(rev, loads):
    return full_gate_receipt.verifier_identity(rev, set(loads) if loads is not None else None)


def tree_of(rev):
    done = git("rev-parse", "--verify", "--quiet", f"{rev}^{{tree}}", check=False)
    return done.stdout.strip() if done.returncode == 0 else None


def full_sha(rev):
    done = git("rev-parse", "--verify", "--quiet", f"{rev}^{{commit}}", check=False)
    return done.stdout.strip() if done.returncode == 0 else None


def _write(name, payload):
    where = folder()
    where.mkdir(parents=True, exist_ok=True)
    temp = where / f".{name}.{os.getpid()}.tmp"
    temp.write_text(json.dumps(payload, sort_keys=True), encoding="utf-8")
    os.replace(temp, where / name)
    now = time.time()
    for old in where.iterdir():
        try:
            if old.is_file() and old.stat().st_mtime < now - KEEP_HOURS * 3600:
                old.unlink()
        except OSError:
            pass


def _read(name):
    path = folder() / name
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return None
    if not isinstance(payload, dict) or not isinstance(payload.get("units"), list):
        return None
    if path.stat().st_mtime < time.time() - KEEP_HOURS * 3600:
        return None
    return payload


def clean_units(scope):
    """The units of `scope` whose verified object shows the index: a compile
    receipt current on disk, with the source and every recorded header free of
    unstaged edits (pre-commit builds the working tree; a dirty input there was
    verified, not committed)."""
    import header_dependents
    out = git("diff", "--name-only", "-z", "--no-renames").stdout
    dirty = {header_dependents.norm(p) for p in out.split("\0") if p}
    header_dependents.ROOT = ROOT
    receipts = header_dependents.receipts(scope, dirty)
    return sorted(unit for unit, (current, _) in receipts.items() if current)


def verifier_dirty(rev=None):
    """Whether the working tree's verifier (full_gate_receipt.VERIFIER) differs
    from `rev` (default: the index) or holds an untracked file: a verify run on
    it is not the verifier a receipt for `rev` names."""
    paths = full_gate_receipt.VERIFIER
    if git("diff", "--quiet", *([rev] if rev else []), "--", *paths, check=False).returncode:
        return True
    return bool(git("ls-files", "--others", "--exclude-standard", "-z", "--", *paths).stdout)


def record_commit(tree, parent, loads_dir, scope):
    """pre-commit verified `scope` (every unit the staged change can affect) at
    `tree`, the commit's tree, over `parent`, its parent's."""
    loads = loads_of(loads_dir)
    _write(f"commit-{tree}-{parent}.json", {
        "kind": "commit", "tree": tree, "parent": parent, "scope": sorted(scope),
        "units": clean_units(scope) if scope and not verifier_dirty() else [],
        "loads": sorted(loads) if loads is not None else None,
        "verifier": identity(tree, loads)})


def record_push(commit, base, loads_dir, units, carried_from=None):
    """A passed push of `commit`: its units with the union of the tool lists
    their verdicts rest on (this push's build, and the receipts it used)."""
    commit = full_sha(commit)
    if commit is None:
        raise SystemExit("push_receipts: record-push needs a commit")
    if verifier_dirty(commit):
        return
    loads = loads_of(loads_dir) if loads_dir else None
    used = [r for r in (chain_receipts(base, commit) or []) + [push_receipt(carried_from)] if r]
    if loads is not None or used:
        merged = set(loads or ())
        for receipt in used:
            if receipt.get("loads") is None:
                merged = None
                break
            merged |= set(receipt["loads"])
        loads = merged
    _write(f"push-{commit}.json", {
        "kind": "push", "commit": commit, "base": full_sha(base), "units": units,
        "loads": sorted(loads) if loads is not None else None,
        "verifier": identity(commit, loads)})


def push_receipt(commit):
    commit = full_sha(commit) if commit else None
    return _read(f"push-{commit}.json") if commit else None


def valid_for(receipt, tip):
    """Whether `receipt`'s verifier is the one at `tip` (a receipt that verified
    nothing carries no verdict to judge)."""
    if receipt is None:
        return False
    return not receipt["units"] or receipt.get("verifier") == identity(tip, receipt.get("loads"))


def chain_receipts(base, tip):
    """The commit receipts of base..tip, one per commit, or None when any is
    missing or the history is not a first-parent line of one-parent commits."""
    listing = git("rev-list", "--reverse", "--parents", f"{base}..{tip}", check=False)
    if listing.returncode:
        return None
    found = []
    for line in listing.stdout.split("\n"):
        if not line:
            continue
        shas = line.split()
        if len(shas) != 2:
            return None
        tree, parent = tree_of(shas[0]), tree_of(shas[1])
        receipt = _read(f"commit-{tree}-{parent}.json")
        if receipt is None or receipt.get("tree") != tree or receipt.get("parent") != parent:
            return None
        found.append(receipt)
    if found and git("merge-base", "--is-ancestor", base, tip, check=False).returncode:
        return None
    return found


def cover(base, tip):
    """Units the commit receipts of base..tip prove at tip ("*": all), or an empty set."""
    receipts = chain_receipts(base, tip)
    if not receipts or not all(valid_for(r, tip) for r in receipts):
        return set()
    units = set()
    for receipt in receipts:
        # a unit the commit's change could affect is proven only if it verified it
        units = (units - set(receipt.get("scope", ()))) | set(receipt["units"])
    return units


def previous(tip, hint=None):
    """A push receipt to carry from: `hint` (the tip before a rebase) if it has a
    valid one, else the newest whose base `tip` descends from. None otherwise."""
    if hint:
        receipt = push_receipt(hint)
        return receipt["commit"] if valid_for(receipt, tip) else None
    where = folder()
    if not where.is_dir():
        return None
    candidates = sorted(where.glob("push-*.json"), key=lambda p: p.stat().st_mtime, reverse=True)
    for path in candidates[:8]:
        receipt = _read(path.name)
        if not receipt or not receipt.get("base") or not full_sha(receipt.get("commit", "")):
            continue
        if git("merge-base", "--is-ancestor", receipt["base"], tip, check=False).returncode:
            continue
        if valid_for(receipt, tip):
            return receipt["commit"]
    return None


def stale(units):
    """The `units` whose object here is not current (build.stale_sources): a
    receipt proves the verdict, not this worktree's object, and the audits read it."""
    import build
    compiled = [ROOT / u for u in units if not u.lower().endswith(".lib")]
    return sorted(s.relative_to(ROOT).as_posix()
                  for s in build.stale_sources(compiled, {c: build.obj_path(c) for c in compiled}))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    rc = sub.add_parser("record-commit")
    rc.add_argument("--tree", required=True)
    rc.add_argument("--parent", required=True)
    rc.add_argument("--loads")
    rc.add_argument("--scope-from", required=True, help="the units pre-commit verified (NUL-separated)")
    rp = sub.add_parser("record-push")
    rp.add_argument("--commit", required=True)
    rp.add_argument("--base", required=True)
    rp.add_argument("--loads")
    rp.add_argument("--units-from", required=True)
    rp.add_argument("--from", dest="carried_from")
    cv = sub.add_parser("cover")
    cv.add_argument("--base", required=True)
    cv.add_argument("--tip", required=True)
    pv = sub.add_parser("previous")
    pv.add_argument("--tip", required=True)
    pv.add_argument("--hint")
    st = sub.add_parser("stale")
    st.add_argument("--units-from", required=True)
    un = sub.add_parser("units")
    un.add_argument("--push", required=True)
    un.add_argument("--tip", required=True)
    args = ap.parse_args(argv)
    if args.cmd == "record-commit":
        record_commit(args.tree, args.parent, args.loads, read_list(args.scope_from))
    elif args.cmd == "record-push":
        record_push(args.commit, args.base, args.loads, read_list(args.units_from), args.carried_from)
    elif args.cmd == "cover":
        write_list(cover(args.base, args.tip))
    elif args.cmd == "previous":
        found = previous(args.tip, args.hint)
        if found:
            print(found)
    elif args.cmd == "stale":
        write_list(stale(read_list(args.units_from)))
    else:
        receipt = push_receipt(args.push)
        write_list(receipt["units"] if valid_for(receipt, args.tip) else ())
    return 0


if __name__ == "__main__":
    sys.exit(main())
