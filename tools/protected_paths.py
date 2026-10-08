#!/usr/bin/env python3
"""Verifier and baseline edits must be declared, and baselines only shrink.

WHY. Every other hook check proves the GAME: bytes, ledgers, names. Nothing
looked at the checks themselves: a commit touching tools/build.py or a
baseline got a Python syntax check and nothing else, so an agent could loosen
the gate that was failing it and go green. Ported from Open-BFME-1
(b9eaa9c709 and follow-ups) as ordinary BFME 2 code (PLAN.md decision 3).

RULES.
  1. A commit that adds, edits or deletes a PROTECTED path must say why in a
     trailer line of its message:  Verifier-Change: <reason, 8+ chars>
     Every such change is listed loudly, declared or not, so the owner can
     audit them with `git log --grep '^Verifier-Change:'`.
  2. SHRINK-ONLY lists (SHRINK_ONLY below) may not grow at all: the trailer
     does not excuse growth. pin_consistency_baseline.csv and
     gate_baseline.txt have their own key-level checks in both hooks
     (pin_consistency --assert-shrink-only, gate_baseline.py) and are only
     rule 1 here.

WHERE. .githooks/commit-msg runs `--commit-msg FILE` on the staged change;
.githooks/pre-push runs `--range BASE TIP` on every outgoing commit, so a
commit made with --no-verify, by cherry-pick or by rebase is still judged.
Both hooks run this checker AS OF THE BASE revision (HEAD, or the remote
tip), never the working copy, so an edit to this file cannot approve itself.

LIMIT. Client-side hooks are advisory against an agent that edits the hooks
or pushes with --no-verify (both forbidden by AGENTS.md). Hard enforcement
needs a server-side or CI run of `--range` over what reaches master.

  python3 tools/protected_paths.py --commit-msg .git/COMMIT_EDITMSG
  python3 tools/protected_paths.py --range BASE TIP
  python3 tools/protected_paths.py --list
"""
import argparse
import fnmatch
import re
import subprocess
import sys

PROTECTED = (
    # the byte gate and what decides which sources it verifies
    "build.sh", "build.cmd", "tools/build.py", "tools/delta_sources.py", "tools/name_dependents.py",
    "tools/flag_defaults.py", "reverse/flag_overrides.csv", "tools/eh_verify.py",
    "tools/find_declared_unmatched.py", "tools/gen_case_shims.py",
    # ledger, identity and direction guards the hooks call
    "tools/check_csv.py", "tools/check_case_collisions.py", "tools/conversion_gate.py",
    "tools/link_debt.py", "tools/class_gate.py", "tools/pin_consistency.py", "tools/header_dependents.py", "tools/ledger_guard.py",
    "tools/pin_admission.py", "tools/gate_baseline.py", "tools/check_module_registry.py",
    "tools/protected_paths.py", "tools/hatch_counters.py", "tools/retail_inventory.py",
    "tools/publisher.py", "tools/publisher_pre_push.sh", "tools/publisher_fixtures/*",
    # data identity: the pre-commit check and the ledger it reads
    "tools/data_check.py", "tools/data_ledger.py", "reverse/data_ledger.csv",
    # which models may judge, and how they are called (decision record, pillar 5)
    "tools/judges.py", "tools/judges.json",
    # the advisory audit: its panel, canaries and harness
    "tools/audit/*",
    "tools/publisher_gate.py", "tools/publisher_hook.py", "tools/publisher_service.py",
    "reverse/publisher_mode",
    # the hooks that run all of the above
    ".githooks/*", ".github/workflows/*",
    # debt registers and exemption lists
    "reverse/*baseline*", "reverse/*whitelist*", "reverse/retail_inventory/*",
)

TRAILER = re.compile(r"^Verifier-Change:[ \t]*(\S.{7,}?)[ \t]*$", re.MULTILINE)


def lines_set(text):
    return {line.strip() for line in text.splitlines() if line.strip() and not line.startswith("#")}


def counts(text):
    out = {}
    for line in text.splitlines():
        line = line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, _, value = line.partition("=")
        try:
            out[key.strip()] = int(value)
        except ValueError:
            continue
    return out


def findings(text):
    import csv
    import io
    return {row.get("finding", "") for row in csv.DictReader(io.StringIO(text))} - {""}


# Each measure returns {key: description} of what `new` adds over `old`, so
# a merge can be judged against every parent (a key grown vs all of them).

def _grown_lines(old, new):
    return {line: line for line in lines_set(new) - lines_set(old)}


def _grown_counts(old, new):
    """A raised count, and a count that is new (or deleted and reintroduced,
    review 2026-09-29: surplus deleted then restored as 1000) above zero."""
    before, after = counts(old), counts(new)
    return {k: f"{k} = {after[k]} (was {before[k] if k in before else 'absent'})"
            for k in after if after[k] > before.get(k, 0)}


def _grown_findings(old, new):
    return {f: f for f in findings(new) - findings(old)}


# path -> (what grows, detector whose change may excuse growth, or None)
SHRINK_ONLY = {
    "reverse/dir32_consistency_whitelist.txt": (_grown_lines, None),
    "reverse/unclaimed_sources_whitelist.txt": (_grown_lines, None),
    "reverse/module_registry_baseline.txt": (_grown_lines, None),
}


def git(*args, check=False):
    got = subprocess.run(["git", *args], capture_output=True, text=True, encoding="utf-8",
                         errors="replace")
    if check and got.returncode:
        raise SystemExit(f"protected_paths: git {' '.join(args)} failed: {got.stderr.strip()}")
    return got


def blob(rev, path):
    """File text at `rev` (':' = the index); '' when absent."""
    got = git("show", f"{rev}:{path}" if rev != ":" else f":{path}")
    return got.stdout if got.returncode == 0 else ""


def protected(paths):
    return sorted(p for p in set(paths) if any(fnmatch.fnmatchcase(p, pat) for pat in PROTECTED))


def reason(message):
    body = "\n".join(line for line in message.splitlines() if not line.startswith("#"))
    found = TRAILER.search(body)
    return found.group(1).strip() if found else None


def banner(title, paths, why, where=""):
    bar = "=" * 72
    print(bar, file=sys.stderr)
    print(f"{title}{where}", file=sys.stderr)
    for path in paths:
        print(f"    {path}", file=sys.stderr)
    print(f"  Verifier-Change: {why}" if why else "  Verifier-Change: MISSING", file=sys.stderr)
    print(bar, file=sys.stderr)


def growth(old_revs, new_rev, touched, excused):
    """[(path, [grown items])] for shrink-only baselines that grew in ONE
    commit (or the staged change): `new_rev` against each of `old_revs`, its
    parents. An item counts only if it is new against every parent. A
    detector exception applies only when that same commit changes the
    detector and declares it (`excused`); review 2026-09-29 found a detector
    edit in one commit excusing growth in another when the range was pooled."""
    out = []
    for path, (measure, detector) in SHRINK_ONLY.items():
        if path not in touched:
            continue
        if detector and detector in excused:
            continue
        new = blob(new_rev, path)
        grown = None
        for old in old_revs:
            items = measure(blob(old, path), new)
            grown = items if grown is None else {k: v for k, v in grown.items() if k in items}
        if grown:
            out.append((path, sorted(grown.values())))
    return out


def report_growth(grown):
    for path, items in grown:
        print(f"protected_paths: {path} may only SHRINK; this adds:", file=sys.stderr)
        for item in items[:15]:
            print(f"    + {item}", file=sys.stderr)
        if len(items) > 15:
            print(f"    ... {len(items) - 15} more", file=sys.stderr)
    if grown:
        print("  Fix the finding instead. A Verifier-Change trailer does not excuse growth.",
              file=sys.stderr)


HOWTO = ("  Add a trailer line to the commit message saying why the check changes, e.g.\n"
         "      Verifier-Change: build.py masks the new reloc type 0x0007 (was reported red)\n"
         "  (git commit --amend keeps your change; the push hook checks every commit.)")


def check_staged(message_file):
    if git("rev-parse", "-q", "--verify", "MERGE_HEAD").returncode == 0:
        return 0                        # a merge is judged per commit by the push hook
    # --no-renames: a protected file moved to an unprotected path is listed under its old name too
    staged = git("diff", "--cached", "--name-only", "--no-renames", "--diff-filter=ACMRDT",
                 check=True).stdout.split()
    hits = protected(staged)
    if not hits:
        return 0
    with open(message_file, encoding="utf-8", errors="replace") as handle:
        why = reason(handle.read())
    head = "HEAD" if git("rev-parse", "-q", "--verify", "HEAD").returncode == 0 else None
    banner("PROTECTED VERIFIER/BASELINE PATHS IN THIS COMMIT", hits, why)
    grown = growth([head], ":", set(staged), set(staged) if why else set()) if head else []
    report_growth(grown)
    if not why:
        print("commit-msg: this commit changes verifier code or a baseline without saying so.",
              file=sys.stderr)
        print(HOWTO, file=sys.stderr)
        return 1
    return 1 if grown else 0


def parents_of(sha):
    return git("rev-list", "--parents", "-n", "1", sha, check=True).stdout.split()[1:]


def commit_paths(sha):
    parents = parents_of(sha)
    if len(parents) > 1:
        # only what the merge itself changed against every parent (a resolution)
        got = git("diff-tree", "--no-commit-id", "--cc", "--name-only", "-r", sha, check=True)
    elif parents:
        got = git("diff-tree", "--no-commit-id", "--name-only", "-r", sha, check=True)
    else:
        got = git("diff-tree", "--no-commit-id", "--root", "--name-only", "-r", sha, check=True)
    return [p for p in got.stdout.splitlines() if p]


def check_range(base, tip):
    commits = git("rev-list", "--reverse", f"{base}..{tip}", check=True).stdout.split()
    bad, grown = 0, []
    for sha in commits:
        paths = commit_paths(sha)
        hits = protected(paths)
        if not hits:
            continue
        why = reason(git("log", "-1", "--format=%B", sha, check=True).stdout)
        subject = git("log", "-1", "--format=%s", sha).stdout.strip()
        banner("PROTECTED VERIFIER/BASELINE PATHS", hits, why, f" in {sha[:10]} {subject[:40]}")
        if not why:
            bad += 1
        # every commit against its own parent(s); the exception is this commit's alone
        parents = parents_of(sha) or ["4b825dc642cb6eb9a060e54bf8d69288fbee4904"]   # empty tree
        mine = growth(parents, sha, set(paths), set(paths) if why else set())
        grown += [(f"{path} in {sha[:10]}", items) for path, items in mine]
    report_growth(grown)
    if bad:
        print(f"pre-push: {bad} outgoing commit(s) change verifier code or a baseline "
              "without a Verifier-Change trailer.", file=sys.stderr)
        print(HOWTO.replace("(git commit --amend keeps your change; the push hook checks every commit.)",
                            "(reword the named commit: git commit --amend if it is the last one)"),
              file=sys.stderr)
    return 1 if bad or grown else 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--commit-msg", metavar="FILE")
    mode.add_argument("--range", nargs=2, metavar=("BASE", "TIP"))
    mode.add_argument("--list", action="store_true")
    args = ap.parse_args(argv)
    if args.list:
        print("\n".join(PROTECTED))
        return 0
    if args.commit_msg:
        return check_staged(args.commit_msg)
    return check_range(*args.range)


if __name__ == "__main__":
    sys.exit(main())
