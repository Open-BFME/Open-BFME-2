#!/usr/bin/env python3
"""Carry a passed full gate to the rebased push that follows it (.githooks/pre-push).

WHY. A push whose range needs the full gate (a vendored, toolchain or unbounded
header change) spends 13-25 minutes byte-verifying every source. Master moves
meanwhile, git rejects the push, and the rebased push ran the whole gate again;
on 2026-10-12 one batch passed it ten times and never landed. The shared push
window that answered this (tools/push_lease.py) froze every other pusher for
the length of each full gate instead. A bounded scope of 512 or more sources
can also lose this race: a 550-source header scope repeatedly took about eight
minutes on Windows. The hook records it as well, after all required checks pass, and
its retry carries it under the same verifier and dependency guards. A carried
push records the tool list of the receipt it carried from (--loads-from).

HOW. When the full gate passes for a commit C0, the hook records C0 here (in
the git common directory, so every worktree of the clone sees it). A later push
of C1 that would need the full gate asks `find C1`. The receipt keeps the remote
base B the gate ran against and the verifier's identity (verifier_identity: the
blobs of .githooks/, the tree-wide baselines and the tools/ files the gate
loaded); a recorded C0 qualifies only when C1 descends from B and its verifier
has that identity, so neither the push nor B..B' changed it. That is: when
the verifier is the same at both (.githooks/, and of tools/ every file the full
gate at C0 loaded or listed, which build.py logs under BFME_GATE_LOADS; a receipt
without that list counts all of tools/), and the change from C0
to C1 is one header_dependents.py can bound (no toolchain or BFME 1 pointer
change, at most --limit dependents), and no tree-wide baseline changed. The hook then verifies the sources
that change from C0 to C1 can reach -- exactly the scope a push from C0 to C1
would verify -- instead of every source: C0's full gate already verified the
rest with the same inputs. The checks that compare sources with each other
(build.cross_source_checks) still judge every row, as do the exception-data
and converged-data audits when their lists changed. The DIR32 check reads again
only the objects this push verified: the receipt keeps the passed check's index
(every row's DIR32 pairs and every object's size and mtime), and a row outside
the verified sources reuses its pairs only while its ledger key and its object's
stamp are unchanged; anything else checks every row. Nothing is trusted from
another clone or host.

  python3 tools/full_gate_receipt.py record SHA [--loads DIR] [--loads-from SHA]
                                       [--dir32-index FILE]
                                                  # the full gate passed at SHA
  python3 tools/full_gate_receipt.py find SHA     # prints a usable C0, or nothing
  python3 tools/full_gate_receipt.py scoped-dir32 --verified-from LIST --ref SHA
                                                  # a scoped push's DIR32 check (build.scoped_dir32)
  python3 tools/full_gate_receipt.py cross-checks [--since C0 --verified-from LIST]
                                       [--index-out FILE]
                                                  # build.cross_source_checks (a script:
                                                  # the build's process pool re-imports it)
"""
import argparse
import hashlib
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
KEEP_HOURS = 48
CANDIDATES = 3  # header_dependents runs per find, nearest receipts first
# What the full gate's verdicts depend on beyond the sources scope_from selects:
# the verifier itself and the baselines that excuse rows anywhere in the tree.
# reverse/eh_baseline.csv and reverse/data_converged.csv change often; the hook
# re-runs their audits over every source instead (.githooks/pre-push).
VERIFIER = ("tools", ".githooks", "reverse/gate_baseline.txt", "reverse/dup_defs_baseline.tsv",
            "reverse/unclaimed_sources_whitelist.txt")


def git(*args, check=True):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, check=check)


def receipts_dir():
    common = git("rev-parse", "--git-common-dir").stdout.strip()
    return (ROOT / common).resolve() / "bfme-full-gate"


def full_sha(rev):
    done = git("rev-parse", "--verify", "--quiet", f"{rev}^{{commit}}", check=False)
    return done.stdout.strip() if done.returncode == 0 else None


def gate_loads(folder):
    """The tools/ files (and listed directories, ending in /) build.py logged under
    BFME_GATE_LOADS=folder (one file per process, named by its id), or None when
    the log is missing or lacks build.py."""
    folder = Path(folder) if folder else None
    if folder is None or not folder.is_dir():
        return None
    entries = set()
    for log in folder.iterdir():
        if not log.is_file() or not log.name.isdigit():
            continue     # build.py names each log after its process id; nothing else is one
        entries |= {line.strip().lower() for line in log.read_text(encoding="utf-8").splitlines() if line.strip()}
    return entries if "tools/build.py" in entries else None


def index_path(sha):
    """Where the receipt for `sha` keeps its DIR32 index."""
    return receipts_dir() / f"{sha}.dir32.gz"


def verifier_identity(rev, loads):
    """A digest of the verifier at `rev`: the blob of every .githooks/ file and
    tree-wide baseline, of every tools/ file the gate loaded (`loads`; None: all
    of tools/), and the names in each tools/ directory it listed (an added or
    removed tool there can change what an import finds)."""
    out = git("ls-tree", "-r", "-z", rev, "--", *VERIFIER).stdout
    listed = {e for e in (loads or ()) if e.endswith("/")}
    lines = set()
    for entry in out.split("\0"):
        if "\t" not in entry:
            continue
        meta, path = entry.split("\t", 1)
        blob = meta.split()[2]
        lower = path.lower()
        if not path.startswith("tools/") or loads is None or lower in loads:
            lines.add(f"{blob} {path}")
        for folder in listed:
            if lower.startswith(folder):
                rest = path[len(folder):]
                lines.add("name " + (path if "/" not in rest else path[:len(folder)] + rest.split("/", 1)[0] + "/"))
    return hashlib.sha256("\n".join(sorted(lines)).encode("utf-8")).hexdigest()


def receipt_meta(sha):
    """(base, verifier identity) recorded with the receipt for `sha`, or None for
    a receipt that predates them."""
    for line in (receipts_dir() / sha).read_text(encoding="utf-8").splitlines()[1:2]:
        match = re.fullmatch(r"# base=([0-9a-f]{40}) verifier=([0-9a-f]{64})", line.strip())
        if match:
            return match.group(1), match.group(2)
    return None


def record(sha, now=None, loads=None, loads_from=None, dir32_index=None, base=None):
    """Record that the full gate passed at `sha` against remote base `base`;
    `loads` is build.py's BFME_GATE_LOADS folder. A carried push (no full gate
    of its own) passes `loads_from`, the receipt it carried from: its verdict
    rests on that gate's tools, and the carry already refused any change to
    them. Without a usable list the receipt counts all of tools/. The receipt
    keeps the base and the identity of the verifier that ran (verifier_identity)."""
    now = time.time() if now is None else now
    sha = full_sha(sha)
    if sha is None:
        raise SystemExit(f"full_gate_receipt: {sha} is not a commit")
    folder = receipts_dir()
    folder.mkdir(parents=True, exist_ok=True)
    entries = gate_loads(loads)
    if entries is None and loads_from and full_sha(loads_from) and (folder / full_sha(loads_from)).is_file():
        entries = receipt_loads(full_sha(loads_from))
    base = full_sha(base) if base else None
    if base is None:
        raise SystemExit("full_gate_receipt: record needs --base, the remote base the gate ran against")
    identity = verifier_identity(sha, entries)
    index_path(sha).unlink(missing_ok=True)
    if dir32_index and Path(dir32_index).is_file() and Path(dir32_index).stat().st_size:
        temp = folder / f"{sha}.dir32.{os.getpid()}.tmp"
        shutil.copyfile(dir32_index, temp)
        os.replace(temp, index_path(sha))
    (folder / sha).write_text(f"{int(now)}\n# base={base} verifier={identity}\n"
                              + "".join(f"{e}\n" for e in sorted(entries or ())))
    for old in folder.iterdir():
        if old.is_file() and old.stat().st_mtime < now - KEEP_HOURS * 3600:
            old.unlink(missing_ok=True)
    return 0


def recorded(now=None):
    """Recorded commits still in the clone, newest first."""
    now = time.time() if now is None else now
    folder = receipts_dir()
    if not folder.is_dir():
        return []
    found = []
    for path in folder.iterdir():
        if path.is_file() and path.stat().st_mtime >= now - KEEP_HOURS * 3600 and full_sha(path.name) == path.name:
            found.append((path.stat().st_mtime, path.name))
    return [sha for _, sha in sorted(found, reverse=True)]


def changed_files(old, new):
    return git("diff", "--name-only", old, new).stdout.split()


def bounded(old, new):
    done = subprocess.run([sys.executable, str(ROOT / "tools" / "header_dependents.py"), "--range", old, new],
                          cwd=ROOT, capture_output=True, text=True)
    return done.returncode == 0


def receipt_loads(sha):
    """The tools/ entries the full gate recorded at `sha` loaded, or None (all of tools/)."""
    lines = (receipts_dir() / sha).read_text(encoding="utf-8").splitlines()[1:]
    entries = {line.strip() for line in lines if line.strip() and not line.startswith("#")}
    return entries if "tools/build.py" in entries else None


def catches_up(old, target):
    """Whether the full gate recorded at `old` can carry to `target`: the
    receipt names its base and verifier, `target` descends from that base, and
    the verifier at `target` is the one that ran (so the change from `old`
    cannot have changed it either)."""
    meta = receipt_meta(old)
    if meta is None:
        return False
    base, identity = meta
    if git("merge-base", "--is-ancestor", base, target, check=False).returncode != 0:
        return False
    return verifier_identity(target, receipt_loads(old)) == identity


def find(sha, now=None):
    """A recorded C0 whose full gate carries to `sha`, or None."""
    target = full_sha(sha)
    if target is None:
        return None
    usable = [old for old in recorded(now) if catches_up(old, target)]
    usable.sort(key=lambda old: len(changed_files(old, target)))
    for old in usable[:CANDIDATES]:
        if old == target or bounded(old, target):
            return old
    return None


def newest_index():
    """The most recently written DIR32 index of any receipt in this clone, or None."""
    folder = receipts_dir()
    found = sorted(folder.glob("*.dir32.gz"), key=lambda p: p.stat().st_mtime, reverse=True) \
        if folder.is_dir() else []
    return found[0] if found else None


def read_list(path):
    raw = Path(path).read_bytes()
    if raw and not raw.endswith(b"\0"):
        raise SystemExit("full_gate_receipt: unterminated source list")
    return {item.decode("utf-8") for item in raw.split(b"\0") if item}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    rec = sub.add_parser("record", help="the full gate passed at SHA")
    rec.add_argument("sha")
    rec.add_argument("--loads", help="build.py's BFME_GATE_LOADS folder from that full gate")
    rec.add_argument("--loads-from", help="the receipt a carried push carried from (its tool list)")
    rec.add_argument("--dir32-index", help="the passed DIR32 check's index (build.verify_dir32_consistency)")
    rec.add_argument("--base", required=True, help="the remote base the gate ran against")
    sub.add_parser("find", help="print a recorded commit whose full gate carries to SHA").add_argument("sha")
    scoped = sub.add_parser("scoped-dir32", help="DIR32 consistency of a scoped push's verified sources")
    scoped.add_argument("--verified-from", required=True, help="NUL-separated sources this push byte-verified")
    scoped.add_argument("--ref", required=True, help="the pushed commit (a source dirty against it is no witness)")
    cross = sub.add_parser("cross-checks", help="the full gate's cross-source checks over every row")
    cross.add_argument("--since", help="the carried receipt: reuse its DIR32 index where proven unchanged")
    cross.add_argument("--verified-from", help="NUL-separated sources this push byte-verified")
    cross.add_argument("--index-out", help="write the passing DIR32 check's index here")
    args = ap.parse_args(argv)
    if args.cmd == "scoped-dir32":
        verified = read_list(args.verified_from)
        if not verified:
            return 0
        dirty = {p.lower() for p in git("diff", "--name-only", "-z", args.ref).stdout.split("\0") if p}
        sys.path.insert(0, str(ROOT / "tools"))
        import build
        found = newest_index()
        index = build.load_dir32_index(found) if found else None
        if index is None:
            print("scoped DIR32: no receipt index in this clone; judging the verified sources alone")
        return build.scoped_dir32(verified, index=index, dirty=frozenset(dirty))
    if args.cmd == "cross-checks":
        if args.since and args.verified_from is None:
            raise SystemExit("full_gate_receipt: --since needs --verified-from")
        verified = None
        if args.verified_from is not None:
            raw = Path(args.verified_from).read_bytes()
            if raw and not raw.endswith(b"\0"):
                raise SystemExit("full_gate_receipt: unterminated --verified-from list")
            verified = {path.decode("utf-8") for path in raw.split(b"\0") if path}
        since = full_sha(args.since) if args.since else None
        if args.since and since is None:
            raise SystemExit(f"full_gate_receipt: {args.since} is not a commit")
        carried = index_path(since) if since and index_path(since).is_file() else None
        if since and carried is None:
            print(f"cross-source checks: the receipt for {since} keeps no DIR32 index; checking every row")
        sys.path.insert(0, str(ROOT / "tools"))
        import build
        return build.cross_source_checks(carried_index=carried, verified=verified, index_out=args.index_out)
    if args.cmd == "record":
        return record(args.sha, loads=args.loads, loads_from=args.loads_from, dir32_index=args.dir32_index,
                      base=args.base)
    old = find(args.sha)
    if old:
        print(old)
    return 0


if __name__ == "__main__":
    sys.exit(main())
