#!/usr/bin/env python3
"""Queue items with a machine pass test, and where new code goes (FIX_PLAN_v2 rule 7).

tools/next_work.py serves these as tiers; this module builds them.

Retirement hooks judge the index (or the outgoing tree with --range). Builds and
verdicts require tracked inputs to equal that tree before and after verification;
unstaged fixes, deletions and header/ledger edits cannot vouch for staged blobs.
A vanished source may retire debt only by transferring the same key to a new
source, covering its removed ledger rows in deleted_rows.csv, or, exceptionally,
one human explanation per key: `Debt-Retired: <key> <source> <reason>` (at least
20 characters in the reason). Here <key>
is the full, literal baseline line (tabs preserved), or the class for a header
queue row. The source is repeated explicitly, and the reason must be nonempty.
Verifier-Change explains verifier edits; it never excuses retiring a debt key.

  repair  gate debt: one keyed baseline line = one row a gate check excuses
          (BFME2 reverse/gate_baseline.txt; BFME1 body_guard_baseline.csv and
          full_gate_baseline.txt). The item names the check and the row's source.
          PASS TEST: `repair_queue.py pass-test LINE` deletes the line and runs the
          row's own gate (tools/build.py SOURCE); a failure puts the line back.
          Exit 0 = the row passes the check and the line stays deleted: commit it
          with the fix. Repairs are credited: progress_v2 shows the debt shrinking.
          Also served: tools/match_tiers.py tier C rows (<reverse>/match_tiers.csv;
          pass: a regrade no longer puts the row in C) and diffexec logic/binding
          divergences (build/diffexec/results.json or REPAIR_DIFFEXEC, JSON or JSONL;
          pass: `tools/diffexec.py --row RVA` exits 0). Twin-body findings are left out.
          And boot-smoke crashes: rows `tools/boot_smoke.py --bisect` found break start-up
          when their authored code is overlaid (build/boot/boot_queue.json or REPAIR_BOOT;
          pass: `boot_smoke.py --overlay rva:RVA` reaches the menu); game-smoke desyncs
          (`tools/game_smoke.py bisect`: build/game/desync_queue.json or REPAIR_DESYNC;
          pass: determinism with the row alone); static relayout findings, `inline-data`
          and `truncated-table` (`tools/boot_relayout.py findings`: build/boot/
          static_queue.json or REPAIR_STATIC; pass: the row is no longer flagged).
  link    BFME2: rows the last link cycle did not place at their retail RVA, or
          placed but not self-strict, with the reason (build/link_cycle/
          link_status.csv, or REPAIR_LINK_STATUS). PASS TEST: the next cycle reports
          the row placed=1 self_strict=1 (`tools/link_cycle.py --measure-only`).
          That file is a build product: only a machine that ran the cycle has it.
          Without it, or when it describes an older commit than the committed link
          census, the tier reads the census instead (reverse/link_status.csv, one
          row per source, measured at the commit its link_census_history.csv row
          names): units that do not link, with their blockers. PASS TEST: `tools/
          link_check.py SOURCE` says LINKS; the next census records linked=yes.
          The census can be many commits old: a unit whose source, or a header
          its build receipt recorded, changed since the census commit is
          re-predicted by tools/link_check.py's own check and dropped only when
          that proves it LINKS. A proof needs the index of the census's commit
          and a current object (no compile, no fresh preprocess) for EVERY unit
          changed since the index, all refreshed into it: a stale provider would
          resolve a symbol it no longer defines. Without that the unit is KEPT,
          with the reason. A unit with no build receipt is labelled "own source
          unchanged". Verdicts are cached by object digest (cache_dir()).
          Census units whose source vanished or holds no matched row are
          counted in the note. A census item claims `file:SOURCE`.
          The output names the source used and the commit it describes; with
          neither, `link` says so and exits 1. A status file may be gzip.
          `link --bundle STORE` reads a PUBLISHED link-cycle bundle instead: the
          newest measurement in the store tools/cycle_artifacts.py fetch keeps
          (build/cycle_bundles), authenticated there (designated publisher,
          immutable release, tag at the measured commit, asset digests) and
          validated here. It is served only when its rules are positively this
          checkout's link_cycle's and it was measured at most 24 h ago
          (--allow-stale serves an older one, labelled STALE, and overrides
          nothing else). A bundle directory with no fetch evidence (one built
          locally) needs --local-unpublished and is labelled UNAUTHENTICATED.
          Nothing falls back to the local cycle or the census; a refusal exits
          with its reason and prints `[reason=...]`:
            1 corrupt  2 unavailable  3 empty  4 stale  5 incompatible-rules
            6 unauthenticated  7 no-closure-report
          Only 2 is worth retrying; 4 and 7 end with the next published bundle;
          1, 5 and 6 need a person. An orchestrator routes the seat to other
          work on any of them and never adds --allow-stale itself.
          `link --closure --bundle STORE` serves what the rows above cannot
          show: the CLOSURE ROOTS, the failed nodes that keep placed,
          self-strict rows out of the credit, ranked by conditional
          single-address gain (tools/closure_report.py: the unique bytes the
          credit would gain if every failed node at that one retail address
          passed, with every edge and every other verdict of the measured graph
          unchanged). It reads the store's newest bundle THAT HAS a closure
          report and says so when a newer measurement was published without
          one. The output names the bundle, whether its graph is the measured
          one bound to the receipt or a replay, how little of the closure
          bucket single roots cover, and its limits. It is a conditional figure
          on a frozen graph, not a repair proof. PASS TEST: a later published
          bundle no longer lists the root and its beneficiaries are
          closed_strict=1.
  data    data-identity debt: one reverse/data_check_baseline.txt key (tools/
          data_check.py: `source<TAB>check<TAB>symbol<TAB>address`). wrong-name: the
          unit reaches a data address through a symbol that is not the data
          ledger's global there; duplicate-def: it defines a datum another unit
          owns. Claims `file:SOURCE`. PASS TEST: `retire data SOURCE` (below).
  header  class-header queue: reverse/header_queue.tsv units that did not adopt their
          class's canonical header (tools/header_adopt_lane.py), DEPENDENCY_ORDER
          classes first. Claims `class:NAME` and `file:SOURCE`. PASS TEST: the
          row's `accept` command, which retires the row when the unit passes.
  identity code-identity debt: one reverse/code_identity_baseline.tsv key (tools/
          code_identity_gate.py, classes in tools/allowed_symbols.py). PASS TEST:
          `retire identity SOURCE` (below). A `divergent` key of a class member
          claims `class:NAME`.
          Each of the three is skipped, with a note, when its file is absent; debt
          naming a source that no longer exists is served first as a regression.
  retire  a debt key leaves its register only on the owning tool's verdict on fresh
          evidence (data_check / allowed_symbols over objects proven current), and
          the verdict fails closed: see "retiring debt" below. verify-removed
          applies it to every key or header row a commit deletes.
  dest    for a NEW match: the translation unit the row belongs in. EA evidence of
          the source file first (BFME1 ea_evidence.csv `file` rows), then the
          address's approved TU in tu_map.csv (the one tu_ownership A3 checks, read
          through tu_map.tu_at) unless the address's own F/Z/S evidence names another
          TU, then the existing file the address's own `__FILE__` string (F) names,
          then -- labelled a neighbour heuristic -- address contiguity: the unit both
          neighbouring rows come from, else the nearest neighbour's unit within
          DEST_WINDOW. A file that does not exist yet is offered only for an
          uncontradicted approved TU. Generated, dump and address-named one-function
          files are never offered; with no known neighbour the answer says so instead
          of inviting a fresh one-function file.

  python3 tools/repair_queue.py repair [--limit N]
  python3 tools/repair_queue.py link [--limit N] [--bundle STORE [--closure] [--allow-stale] [--local-unpublished]]
  python3 tools/repair_queue.py data|header|identity [--limit N]
  ms-headers  Microsoft-header copies from reverse/ms_header_queue.tsv, ranked by
          the audit's per-unit configuration and include closure. Static candidates
          need ./build.sh byte verification; CRT dllimport conflicts need per-body
          callee checks. Explicit lane only (not a next_work tier); --claim takes
          file:SOURCE through next_work's lock_keys/acquire selection path.

  python3 tools/repair_queue.py ms-headers [--class drop-in-candidate|adapt|unverified|conflicting|shim|failed] [--limit N] [--claim]
  stlport  whole files to move onto STLport 4.6 (`// stlport46`): the leads of
          reverse/stlport_trial.csv (tools/stlport_trial.py) the ledger still holds.
          next_work.py --tier stlport serves one with its move and a file:SOURCE claim.

  python3 tools/repair_queue.py stlport [--tsv]
  python3 tools/repair_queue.py dest 0xRVA
  python3 tools/repair_queue.py pass-test "<baseline line>"
  python3 tools/repair_queue.py retire data|identity SOURCE   # the tool's verdict retires keys
  python3 tools/repair_queue.py retired [--limit N]  # audit committed Debt-Retired trailers
  python3 tools/repair_queue.py verify-removed     # pre-commit, when a debt line is deleted:
                                                   # builds and judges each such row against staged inputs;
                                                   # data/identity keys and header rows: the tool's verdict
"""
import argparse
import bisect
import calendar
import collections
import csv
import gzip
import hashlib
import io
import json
import os
import posixpath
import re
import subprocess
import sys
import time
from functools import lru_cache
from pathlib import Path

# The hooks run HEAD's copy through stdin (an edit cannot approve itself): no real __file__
# then. Python 3.13 sets __file__ to "<stdin>" for `python3 -`, so a pseudo-path counts as none.
_SCRIPT = globals().get("__file__")
_HAS_SCRIPT = bool(_SCRIPT) and not str(_SCRIPT).startswith("<")
ROOT = Path(os.environ.get("REPAIR_ROOT")
            or (Path(_SCRIPT).resolve().parents[1] if _HAS_SCRIPT else Path.cwd()))
BFME1 = (ROOT / "targets" / "game" / "reverse").is_dir()
REV = "targets/game/reverse" if BFME1 else "reverse"
LEDGER = f"{REV}/functions.csv"
EVIDENCE = f"{REV}/ea_evidence.csv"
SOURCE_PREFIX = "game/" if BFME1 else "Code/"
NOT_A_HOME = ("game/gen_small/", "game/gen_asm/", "game/masm_dumps/", "Code/gen_small/", "Code/gen_asm/",
              "Code/masm_dumps/")
ADDRESS_FILE = re.compile(r"(?i)(?=(?:[0-9a-f]*\d){3})[0-9a-f]{6,8}")
DEST_WINDOW = 0x4000
LINK_STATUS_SET = os.environ.get("REPAIR_LINK_STATUS")      # named by hand: used whenever it exists
LINK_STATUS = LINK_STATUS_SET or str(ROOT / "build" / "link_cycle" / "link_status.csv")
CENSUS_STATUS = f"{REV}/link_status.csv"                     # committed: tools/link_census.py --history
CENSUS_HISTORY = f"{REV}/link_census_history.csv"            # its last row names the census's commit
FILE_ROUTES = ("wb1", "zh", "wb1-run", "retail-run", "wb2", "wb2-run")

CHECKS = {
    "strnul": "a string literal ends before retail's; write the whole literal",
    "ltable": "a jump-table entry or same-section pointer lands on the wrong case; fix the case mapping",
    "tail": "compiled bytes past the row's extent differ from retail; fix the tail (or the extent)",
    "truncated": "the compiled body is longer than the row and retail agrees; raise the extent",
    "genalias": "a gen-alias row's masked call is not a twin of its callee; call the real callee",
    "alias-row": "an object-symbol= alias still resolves callers; give the row its real body or name",
    "static": "TU-local data the body reads ($SG string, local static, const table) differs from retail",
    "dir32": "a DIR32 name does not resolve by retail address",
    "full-gate": "the row is red in the full gate",
}


def _read(rel):
    path = ROOT / rel
    return path.read_text(encoding="utf-8", errors="replace") if path.exists() else ""


@lru_cache(maxsize=1)
def ledger():
    """(rows by rva, sorted [(rva, size, source)] of real homes)."""
    by_rva, homes = {}, []
    for row in csv.DictReader(io.StringIO(_read(LEDGER))):
        if row.get("status") != "matched" or not row.get("target_rva"):
            continue
        rva = int(row["target_rva"], 16)
        by_rva.setdefault(rva, []).append(row)
        source = row["source"]
        if is_home(source):
            homes.append((rva, int(row["target_size"] or 0), source))
    homes.sort()
    return by_rva, homes


def is_home(source):
    """A unit a new row may be added to: real source, not generated, a dump, a .lib, or an
    address-named one-function file."""
    return (source.startswith(SOURCE_PREFIX) and not source.startswith(NOT_A_HOME)
            and source.lower().endswith((".cpp", ".c", ".cc", ".cxx"))
            and not ADDRESS_FILE.search(Path(source).stem))


# ---------------------------------------------------------------- repair tier

def baseline_files():
    if BFME1:
        return ((f"{REV}/body_guard_baseline.csv", "csv"), (f"{REV}/full_gate_baseline.txt", "full"))
    return ((f"{REV}/gate_baseline.txt", "keyed"),)


def parse_debt():
    """[(path, line, check, rva or None, name, detail)] for every baseline line."""
    out = []
    for path, kind in baseline_files():
        text = _read(path)
        if kind == "csv":
            body = [l for l in text.splitlines() if l.strip()]
            for line, row in zip(body[1:], csv.DictReader(io.StringIO("\n".join(body)))):
                out.append((path, line, row["check"], int(row["target_rva"], 16), row["name"], row.get("detail", "")))
        for line in text.splitlines():
            if not line.strip() or line.startswith("#") or kind == "csv":
                continue
            if kind == "keyed":
                check, rva, name = (line.split(None, 2) + ["", ""])[:3]
                out.append((path, line, check, int(rva, 16), name.strip(), ""))
            else:                                   # BFME1 full gate: `name (source)`
                m = re.match(r"(\S+) \((.+)\)$", line.strip())
                if m:
                    out.append((path, line, "full-gate", None, m[1], m[2]))
    return out


def repair_items():
    """Gate-debt rows, each with its check, the row's source and a pass test."""
    by_rva, _ = ledger()
    items = []
    for path, line, check, rva, name, detail in parse_debt():
        rows = by_rva.get(rva, []) if rva is not None else []
        row = next((r for r in rows if r["name"] == name), rows[0] if rows else None)
        # A dir32 key names the referenced datum; its source is the unit that spells it.
        source = row["source"] if row and check != "dir32" else (detail if check == "full-gate" else "")
        size = int(row["target_size"]) if row and check != "dir32" else 0
        items.append({
            "tier": "repair", "check": check, "target_rva": f"0x{rva:08X}" if rva is not None else "",
            "function": name, "source": source or "(git grep -l the name)", "size": size, "credit": size,
            "why": detail or CHECKS.get(check, check), "baseline": path, "baseline_line": line,
            "pass_test": f"python3 tools/repair_queue.py pass-test {shell_quote(line)}",
        })
    items.sort(key=lambda item: (item["check"] == "dir32", -item["size"]))
    return items


MATCH_TIERS = f"{REV}/match_tiers.csv"
DIFFEXEC = os.environ.get("REPAIR_DIFFEXEC") or str(ROOT / "build" / "diffexec" / "results.json")


def diffexec_items(path=None):
    """diffexec logic/binding divergences (a list, {"rows"|"results": [...]} or JSONL),
    `(twin bodies)` findings left out: the code is equal, only the name differs."""
    import json
    path = Path(path or DIFFEXEC)
    if not path.exists():
        return []
    text = path.read_text(encoding="utf-8-sig", errors="replace")
    try:
        data = json.loads(text)
        rows = data if isinstance(data, list) else data.get("rows") or data.get("results") or []
    except ValueError:
        rows = [json.loads(l) for l in text.splitlines() if l.strip().startswith("{")]
    items = []
    for r in rows:
        verdict = str(r.get("verdict", r.get("class", ""))).lower()
        rva = r.get("target_rva", r.get("rva"))
        if verdict not in ("logic", "binding") or "twin bodies" in str(r.get("reason", "")) or rva is None:
            continue
        rva = rva if isinstance(rva, str) else f"0x{int(rva):08X}"
        items.append({
            "tier": "repair", "check": f"diffexec-{verdict}", "target_rva": rva, "function": r.get("name", ""),
            "source": r.get("source", ""), "size": int(r.get("size") or 0), "credit": int(r.get("size") or 0),
            "why": str(r.get("reason", ""))[:300], "baseline": "", "baseline_line": "",
            "pass_test": f"python3 tools/diffexec.py --row {rva}  (exit 0: no logic/binding divergence)",
        })
    return items


BOOT_QUEUE = os.environ.get("REPAIR_BOOT") or str(ROOT / "build" / "boot" / "boot_queue.json")
DESYNC_QUEUE = os.environ.get("REPAIR_DESYNC") or str(ROOT / "build" / "game" / "desync_queue.json")
STATIC_QUEUE = os.environ.get("REPAIR_STATIC") or str(ROOT / "build" / "boot" / "static_queue.json")
STATIC_CHECKS = ("inline-data", "truncated-table")


def boot_items(path=None):
    """Rows whose authored code breaks the game when overlaid: `tools/boot_smoke.py
    --bisect` (start-up; build/boot/boot_queue.json or REPAIR_BOOT), `tools/game_smoke.py
    bisect` (a skirmish desyncs or crashes; build/game/desync_queue.json or REPAIR_DESYNC),
    and `tools/boot_relayout.py findings` (static: data past the row's extent, a truncated
    code-pointer table; build/boot/static_queue.json or REPAIR_STATIC). An item's own
    `check` and `pass_test` win; boot_smoke's items have neither (boot-crash). One path:
    that queue alone."""
    import json
    items = []
    for p in ([path] if path else [BOOT_QUEUE, DESYNC_QUEUE, STATIC_QUEUE]):
        p = Path(p)
        if not p.exists():
            continue
        for r in json.loads(p.read_text(encoding="utf-8")).get("items", []):
            items.append({
                "tier": "repair", "check": r.get("check") or "boot-crash", "target_rva": r["target_rva"],
                "function": r["name"], "source": r["source"], "size": int(r.get("size") or 0),
                "credit": int(r.get("size") or 0), "why": str(r.get("why", r.get("outcome", "")))[:300],
                "baseline": "", "baseline_line": "", "queue": str(p),
                "pass_test": r.get("pass_test") or f"python3 tools/boot_smoke.py --game-dir SANDBOX --overlay "
                                                   f"rva:{r['target_rva']} --timeout 150  (exit 0: reached-menu "
                                                   "with the row overlaid)",
            })
    return items


def tier_c_items(seen=()):
    """match_tiers.py tier C rows (contradicted) not already served from a baseline line."""
    seen = set(seen)
    items = []
    for r in csv.DictReader(io.StringIO(_read(MATCH_TIERS))):
        if r.get("tier") != "C" or (r["target_rva"].upper(), r["name"]) in seen:
            continue
        items.append({
            "tier": "repair", "check": "tier-C", "target_rva": r["target_rva"], "function": r["name"],
            "source": r["source"], "size": int(r["target_size"] or 0), "credit": int(r["target_size"] or 0),
            "why": r.get("reasons", "")[:300], "baseline": "", "baseline_line": "",
            "pass_test": "python3 tools/match_tiers.py --out build/match_tiers.csv: the row is no longer tier C",
        })
    return items


def all_repair_items():
    """Gate debt, then match_tiers tier C, diffexec divergences, boot/game-smoke
    failures and static relayout findings not already listed (a row once, first wins)."""
    items = repair_items()
    seen = {(i["target_rva"].upper(), i["function"]) for i in items}
    extra = []
    for i in diffexec_items() + boot_items():
        key = (i["target_rva"].upper(), i["function"])
        if key not in seen:
            seen.add(key)
            extra.append(i)
    extra += tier_c_items(seen)
    # static relayout findings after the failures a run or the emulator showed
    return items + sorted(extra, key=lambda i: (i["check"] in STATIC_CHECKS, -i["size"]))


def shell_quote(text):
    return "'" + text.replace("'", "'\"'\"'") + "'"


def locate_source(name):
    got = subprocess.run(["git", "grep", "-l", "-F", "--", name, SOURCE_PREFIX], cwd=ROOT,
                         capture_output=True, text=True)
    files = got.stdout.split()
    return files[0] if files else None


def pass_test(line, build_cmd=None):
    """Delete LINE from its baseline and run the row's own gate; restore the line on
    failure. Returns (ok, message)."""
    item = next((i for i in repair_items() if i["baseline_line"].strip() == line.strip()), None)
    if item is None:
        return False, "no such baseline line (already removed, or mistyped)"
    source = item["source"]
    if source.startswith("("):
        source = locate_source(item["function"])
        if not source:
            return False, f"no source spells {item['function']}; nothing left to verify"
    path = ROOT / item["baseline"]
    raw = path.read_bytes()
    # Mixed CRLF/LF baselines must lose the selected exemption before the
    # checker runs. Preserve every remaining byte, including its terminator.
    kept = b"".join(l for l in raw.splitlines(keepends=True)
                    if l.decode("utf-8", "replace").strip() != line.strip())
    cmd = build_cmd or [sys.executable, str(ROOT / "tools" / "build.py"), source]
    verified = False
    try:
        path.write_bytes(kept)
        verified = subprocess.run(cmd, cwd=ROOT).returncode == 0
    finally:
        # A missing executable or an interrupted build has verified nothing.
        # Keep the deletion only after the checker completed successfully.
        if not verified:
            path.write_bytes(raw)
    if not verified:
        return False, f"{item['check']} still fails for {item['function']} ({source}); line restored"
    return True, (f"PASS: {item['function']} passes {item['check']}; the line is deleted from "
                  f"{item['baseline']} -- commit it with the fix")


def _git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")


DEBT_BASE, DEBT_TARGET = "HEAD", ""  # empty ref means the Git index, never the filesystem


def _debt_present(source):
    return _git("cat-file", "-e", f"{DEBT_TARGET}:{source}").returncode == 0


def _verification_tree():
    got = _git("write-tree") if not DEBT_TARGET else _git("rev-parse", f"{DEBT_TARGET}^{{tree}}")
    if got.returncode:
        return None
    return got.stdout.strip()


# CreateProcess caps a Windows command line at 32,767 characters, and a large
# retirement batch reads far more dependency paths than that (WinError 206).
_PATHSPEC_BUDGET = 24000


def _pathspec_chunks(paths, budget=_PATHSPEC_BUDGET):
    """Split `paths` into lists whose joined length stays within `budget`."""
    chunk, size = [], 0
    for path in paths:
        if chunk and size + len(path) + 1 > budget:
            yield chunk
            chunk, size = [], 0
        chunk.append(path)
        size += len(path) + 1
    if chunk:
        yield chunk


def _diff_differs(run, prefix, paths):
    """True when `git diff --quiet` over `paths` (in command-line-sized chunks) differs or fails."""
    return any(run([*prefix, "--", *chunk]).returncode for chunk in _pathspec_chunks(paths))


def _verification_problems(tree, sources=()):
    """Bind the ordinary build's working inputs to staged/outgoing blobs, fail closed.

    Do not overlay or restore user files. Recheck the tree and relevant inputs
    after judgment, too, so a changed header, provider or ledger invalidates it.
    """
    if not tree or _verification_tree() != tree:
        return ["staged/outgoing tree unavailable or changed during debt verification"]
    paths = {LEDGER, HEADER_QUEUE, *REGISTERS.values(),
             *(path for path, _ in baseline_files()),
             f"{REV}/symbols.csv", f"{REV}/canonical_classes.csv",
             f"{REV}/data_converged.csv", f"{REV}/deleted_rows.csv",
             "reference/shims", "inputs/reference/shims"}
    # Keep headers/shims strict even without an old dependency receipt: a newly
    # included header must not evade the working-tree/index check.
    paths.update(f":(glob)**/*.{suffix}" for suffix in ("h", "hpp", "hxx", "inl", "inc"))
    nested = {}
    for source in sources:
        paths.add(source)
        for dep in unit_deps(source) or ():
            absolute = (ROOT / dep).resolve()
            try:
                rel = absolute.relative_to(ROOT.resolve()).as_posix()
            except ValueError:  # external SDK inputs have their own build receipts
                continue
            paths.add(rel)
            # Parent diff ignores dirty submodule worktrees. Check just the
            # headers this source actually read against the pinned gitlink.
            for parent in absolute.parents:
                if parent == ROOT.resolve():
                    break
                if (parent / ".git").exists():
                    sub = parent.relative_to(ROOT.resolve()).as_posix()
                    nested.setdefault(sub, []).append(absolute.relative_to(parent).as_posix())
                    break
    if _diff_differs(lambda args: _git(*args), ["diff", "--no-ext-diff", "--quiet", "--ignore-submodules=dirty", tree],
                     sorted(paths)):
        return ["working inputs differ from staged/outgoing blobs (or git diff failed); stage the fix before retiring debt"]
    for sub, inputs in nested.items():
        import claims
        entry = _git("ls-tree", tree, "--", sub)
        fields = entry.stdout.split()
        if entry.returncode or len(fields) < 3 or fields[0] != "160000":
            return [f"{sub}: staged/outgoing dependency gitlink unavailable"]
        env = claims._git_env(ROOT / sub)
        if _diff_differs(lambda args: subprocess.run(args, capture_output=True, text=True, env=env),
                         ["git", "-C", str(ROOT / sub), "diff", "--no-ext-diff", "--quiet",
                          "--ignore-submodules=dirty", fields[2]], inputs):
            return [f"{sub}: build inputs differ from staged/outgoing dependency blobs"]
    return []


def removed_debt_sources():
    """{source: [baseline lines]} for gate-debt lines the index deletes against HEAD.
    A removal is credited as a repair, so each one is re-verified (rule 5)."""
    out = {}
    for path, kind in baseline_files():
        old, new = _git("show", f"{DEBT_BASE}:{path}"), _git("show", f"{DEBT_TARGET}:{path}")
        if old.returncode or old.stdout == new.stdout:
            continue
        gone = set(old.stdout.splitlines()) - set(new.stdout.splitlines())
        for item in repair_items_from(path, kind, old.stdout):
            if item["baseline_line"] in gone:
                source = item["source"]
                if source.startswith("("):
                    source = locate_source(item["function"])
                if source:                          # nothing spells it any more: nothing to verify
                    out.setdefault(source, []).append(item["baseline_line"])
    return out


def verify_removed(build_cmd=None):
    """Build every removed line's source with inputs bound to staged/outgoing blobs."""
    removed = removed_debt_sources()
    if not removed:
        return []
    tree = _verification_tree()
    problems = _verification_problems(tree, removed)
    if problems:
        return problems
    failures = []
    for source, lines in sorted(removed.items()):
        cmd = (build_cmd or [sys.executable, str(ROOT / "tools" / "build.py")]) + [source]
        if subprocess.run(cmd, cwd=ROOT).returncode != 0:
            failures.append(f"{source}: removed {lines[0]!r} but the row still fails its check")
    return failures + _verification_problems(tree, removed)


def repair_items_from(path, kind, text):
    """repair_items() for one baseline text (HEAD's, when judging a removal)."""
    saved = _read
    try:
        others = {p for p, _ in baseline_files()} - {path}
        globals()["_read"] = lambda rel: text if rel == path else ("" if rel in others else saved(rel))
        return repair_items()
    finally:
        globals()["_read"] = saved


# ---------------------------------------------------------------- link tier

def stored_census():
    """{"commit", "date", "when"} of the committed link census, or None when the repo has
    no reverse/link_status.csv or no history row saying what it measured."""
    if not (ROOT / CENSUS_STATUS).exists():
        return None
    rows = list(csv.DictReader(io.StringIO(_read(CENSUS_HISTORY))))
    if not rows or not rows[-1].get("commit"):
        return None
    last = rows[-1]
    try:                                            # link_census.py writes the date in UTC
        when = calendar.timegm(time.strptime(last["date"], "%Y-%m-%d %H:%M"))
    except (TypeError, ValueError):
        when = 0
    return {"commit": last["commit"], "date": last.get("date", ""), "when": when}


def cycle_commit(path):
    """(commit, dirty) a link cycle's status describes, from the receipt.json beside it;
    (None, False) without one."""
    try:
        receipt = json.loads((Path(path).parent / "receipt.json").read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return None, False
    return (receipt.get("commit") or None), receipt.get("dirty", False)


def link_source(path=None):
    """(kind, path, note) of the link status the link tier reads, or (None, None, why).

    A link cycle's per-row status (kind "cycle") is preferred: it says which ROW failed and
    why. It is used when named by hand (PATH, REPAIR_LINK_STATUS), or when it exists and is
    not older than the committed census: its receipt's commit descends from the census's
    commit, or, with no receipt or a commit this clone lacks, the file is newer than the
    census's date. Otherwise the committed census (kind "census")."""
    local = Path(path or LINK_STATUS)
    census = stored_census()
    skipped = ""
    if local.exists():
        commit, dirty = cycle_commit(local)
        newer, basis = True, "named by hand"
        if not (path or LINK_STATUS_SET) and census:
            got = subprocess.run(["git", "merge-base", "--is-ancestor", census["commit"], commit],
                                 cwd=ROOT, capture_output=True) if commit else None
            if got is not None and got.returncode in (0, 1):
                newer, basis = got.returncode == 0, "commit vs the census's %s" % census["commit"][:10]
            else:
                newer, basis = local.stat().st_mtime >= census["when"], "file time vs the census's date"
        when = time.ctime(local.stat().st_mtime)
        described = ("commit %s%s" % (commit[:10], " +uncommitted edits" if dirty else "") if commit
                     else "commit unknown (no receipt.json)")
        if newer:
            return "cycle", local, f"local link cycle {local} ({described}, written {when})"
        skipped = f"; local {local} ({described}) is not newer ({basis}), not used"
    if census:
        return "census", ROOT / CENSUS_STATUS, (f"committed link census {CENSUS_STATUS} (measured at commit "
                                                f"{census['commit']}, {census['date']} UTC){skipped}")
    return None, None, (f"no link status: no link-cycle status at {local} (run tools/link_cycle.py) and no "
                        f"committed census at {CENSUS_STATUS} with a {CENSUS_HISTORY} row")


LINK_BLOCKERS = ("unresolved", "duplicates", "comdat", "addresses", "selected")   # link_check.report's


def tools_on_path():
    """Put tools/ on sys.path for a lazy import: the hooks run this file through stdin
    (verify-removed) without it."""
    tools = str(Path(_SCRIPT).resolve().parent if _HAS_SCRIPT else ROOT / "tools")
    if tools not in sys.path:
        sys.path.insert(0, tools)


def changed_since(commit):
    """The paths whose working copy differs from COMMIT (committed since or edited, a
    deletion included), or None when this clone cannot compare (it lacks the commit)."""
    got = _git("diff", "--name-only", "-z", "--no-renames", commit, "--")
    if got.returncode:
        return None
    return {name for name in got.stdout.split("\0") if name}


def unit_deps(source):
    """The repo-relative paths SOURCE's last compile read (its build receipt,
    `<object>.deps.json`), or None without a readable receipt."""
    tools_on_path()
    import build
    try:
        meta = json.loads(build._deps_sidecar(build.obj_path(ROOT / source)).read_text())
        return {dep.replace("\\", "/") for dep in meta.get("deps", {})}
    except (OSError, ValueError, AttributeError, TypeError):
        return None


def cache_dir():
    """Where picker verdicts are cached, content-addressed (safe to share): BFME_PICKER_CACHE,
    else <git common dir>/bfme-picker-cache, shared by every worktree of the clone."""
    if os.environ.get("BFME_PICKER_CACHE"):
        return Path(os.environ["BFME_PICKER_CACHE"])
    common = _git("rev-parse", "--path-format=absolute", "--git-common-dir").stdout.strip()
    return Path(common or ROOT / ".git") / "bfme-picker-cache"


def cached(kind, key, compute):
    """compute() once per content KEY (a JSON-able value) under cache_dir()/KIND."""
    digest = hashlib.sha256(json.dumps(key, sort_keys=True).encode()).hexdigest()
    path = cache_dir() / kind / f"{digest}.json"
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        pass
    value = compute()
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        tmp = path.with_suffix(f".{os.getpid()}.tmp")
        tmp.write_text(json.dumps(value), encoding="utf-8")
        os.replace(tmp, path)
    except OSError:
        pass
    return value


def units_of(rows):
    """{source: frozenset of (name, target_rva, target_size)} of matched ledger rows:
    what each unit provides to the link."""
    out = {}
    for row in rows:
        if row.get("status", "matched") != "matched":
            continue
        out.setdefault(row["source"], set()).add((row.get("name"), row.get("target_rva"), row.get("target_size")))
    return {source: frozenset(keys) for source, keys in out.items()}


def ledger_units_at(commit):
    """units_of the ledger at COMMIT, or None when this clone cannot read it."""
    got = _git("show", f"{commit}:{LEDGER}")
    return None if got.returncode else units_of(csv.DictReader(io.StringIO(got.stdout)))


def digest_of(path):
    """sha256 of a file's bytes, or None when it cannot be read."""
    try:
        return hashlib.sha256(Path(path).read_bytes()).hexdigest()
    except OSError:
        return None


def link_predictions(sources, census_commit):
    """{source: (verdict, detail)} from tools/link_check.py's own check: True LINKS, False
    does not link (detail: its blockers), None no verdict (detail: why). A verdict needs
    every provider as it is now, so it is given only when:
      * the census index measures census_commit (meta census_commit, else commit);
      * every ledger unit changed since the index's own commit -- by its source, by a
        header its build receipt recorded (no receipt: assumed changed), or by its ledger
        rows -- has an object link_census.object_current proves current WITHOUT a fresh
        preprocess (allow_fresh=False), and is in the census: a changed provider not
        refreshed would still resolve a symbol it no longer defines, a false LINKS;
      * no unit changed since the index was deleted; a unit the index's ledger held and
        the current one does not is forgotten (lc.forget) before the check;
      * nothing it read moves while it is checked: the refreshed objects, every
        provider's and checked unit's source and recorded headers, the ledger, the pins,
        the index and the checking tools are fingerprinted before and after, and every
        provider's object is proven current again afterwards.
    A checked unit whose own ledger rows changed since the index gets no verdict.
    Otherwise every source gets None, and its item is kept. Nothing is compiled or
    preprocessed. Verdicts are cached (cached()) by all of those fingerprints."""
    def none(why):
        return {s: (None, why) for s in sources}
    try:
        tools_on_path()
        import build
        import link_census
        import link_check as lc
    except (ImportError, SystemExit) as error:
        return none(f"tools/link_check.py unavailable: {error}")
    if not lc.INDEX.exists():
        return none("no census index to predict against (python3 tools/link_check.py --fetch-index)")
    index_hash = digest_of(lc.INDEX)
    if index_hash is None:
        return none("census index unreadable")
    meta = cached("index-meta", [str(lc.INDEX), index_hash], lambda: lc.index_meta(lc.INDEX))
    if meta is None:
        return none(f"{lc.INDEX.name} is not a census index")
    measured = meta.get("census_commit") or meta["commit"]
    if not census_commit or measured != census_commit:
        return none(f"the census index measures commit {measured[:10]}, the census {str(census_commit)[:10]}: "
                    "fetch the matching one (python3 tools/link_check.py --fetch-index)")
    moved = changed_since(meta["commit"])
    if moved is None:
        return none(f"this clone lacks the index's commit {meta['commit'][:10]}")
    then = ledger_units_at(meta["commit"])
    if then is None:
        return none(f"this clone cannot read the ledger at the index's commit {meta['commit'][:10]}")
    rows = link_census.ledger()
    now = units_of(rows)
    units = sorted(u for u in now if not u.lower().endswith(build.LIB_SUFFIX))
    rehomed = {u for u in units if u in then and then[u] != now[u]}       # its rows changed since the index
    dropped = sorted(u for u in then if u not in now and not u.lower().endswith(build.LIB_SUFFIX))
    headers = {p for p in moved if not p.lower().endswith((".cpp", ".c", ".cc", ".cxx", ".asm"))}
    providers, unknown, deps_of = [], [], {}
    for unit in units:
        deps = deps_of[unit] = unit_deps(unit) if headers or unit in sources or unit in moved else set()
        if unit in moved or unit in rehomed or (headers and deps is None) or (deps and deps & headers):
            providers.append(unit)
    gone = [p for p in moved if p.startswith(SOURCE_PREFIX) and p.lower().endswith((".cpp", ".c", ".asm"))
            and p not in set(units)]
    if gone:
        return none(f"{len(gone)} unit(s) changed since the index hold no ledger row now (e.g. {gone[0]}): "
                    "their old definitions cannot be retracted here, so LINKS is not provable")
    objects = {}
    for unit in providers:
        obj = build.obj_path(ROOT / unit)
        if not obj.is_file() or not link_census.object_current(ROOT / unit, obj, allow_fresh=False):
            unknown.append(unit)
        else:
            objects[unit] = obj
    if unknown:
        return none(f"{len(unknown)} changed provider unit(s) have no current object (e.g. {unknown[0]}; "
                    "./build.sh them or python3 tools/link_check.py --refresh), so LINKS is not provable")
    read = sorted({*providers, *sources} | {d for u in {*providers, *sources} for d in deps_of.get(u) or ()})

    def inputs():
        """Fingerprints of everything the verdict depends on (compared after the check)."""
        return {"sources": {rel: digest_of(ROOT / rel) for rel in read},
                "ledger": hashlib.sha256(json.dumps(link_census.ledger(), sort_keys=True,
                                                    default=str).encode()).hexdigest(),
                "ledger_file": digest_of(ROOT / LEDGER), "pins": digest_of(ROOT / f"{REV}/symbols.csv"),
                "tools": {Path(m.__file__).name: digest_of(m.__file__) for m in (lc, link_census, build)},
                "picker": digest_of(__file__),
                "index": digest_of(lc.INDEX),
                "objects": link_census.object_stamps(list(objects.values()))}
    try:
        before = inputs()
        digests = {unit: lc.object_digest(obj) for unit, obj in objects.items()}
    except OSError as error:
        return none(f"objects unreadable: {error}")
    if (any(value is None for value in before["sources"].values())
            or any(value is None for value in before["tools"].values())
            or any(before[name] is None for name in ("ledger_file", "pins", "index", "picker"))):
        return none("a compiler input, ledger, pin, tool or census index is unreadable")

    def compute():
        index = lc.load_index()
        lc.require_common_index(index)
        outside = [u for u, o in objects.items() if not lc.in_census(index, o.name)]
        if outside:
            return {"none": f"{len(outside)} changed unit(s) are not in the census (e.g. {outside[0]}): their "
                            "definitions are not in the index, so LINKS is not provable"}
        lc.forget(index, [build.obj_path(ROOT / u).name for u in dropped])
        truth = link_census.RetailTruth(link_census.ledger())
        lc.refresh(index, list(objects.values()), truth)
        out = {}
        for source in sources:
            try:
                result = lc.check_object(objects[source], index, truth, source)
            except Exception as error:                    # link_census.MissingObject and the like
                out[source] = [None, f"link_check: {error}"]
                continue
            blockers = {kind: len(result[kind]) for kind in LINK_BLOCKERS if result[kind]}
            out[source] = [not blockers, ", ".join("%s %d" % kv for kv in blockers.items()) or "LINKS"]
        return out
    key = {"index": [meta["commit"], meta["date"], measured, before["index"]], "objects": digests,
           "checked": sorted(sources), "sources": before["sources"], "ledger": before["ledger"],
           "pins": before["pins"], "tools": before["tools"], "picker": before["picker"], "forgotten": dropped}
    try:
        got = cached("link", key, compute)
        after = inputs()
        after_digests = {unit: lc.object_digest(obj) for unit, obj in objects.items()}
    except (SystemExit, Exception) as error:              # no verdict, said so; nothing is guessed
        return none(f"census index unusable: {error}")
    moved_after = changed_since(meta["commit"])
    if (after != before or after_digests != digests or moved_after is None or moved_after != moved
            or not all(link_census.object_current(ROOT / u, o, allow_fresh=False)
                       for u, o in objects.items())):
        moved_now = sorted(k for k in before if before[k] != after[k])
        if after_digests != digests:
            moved_now.append("object bytes")
        if moved_after != moved:
            moved_now.append("changed source/header paths")
        if not moved_now:
            moved_now = ["object currency"]
        return none(f"inputs moved while they were checked ({', '.join(moved_now)}); retry")
    if "none" in got:
        return none(got["none"])
    out = {s: tuple(got.get(s, (None, "not predicted"))) for s in sources}
    out.update({s: (None, "its ledger rows changed since the census index: re-census to judge it")
                for s in sources if s in rehomed})
    return out


def census_items(path, commit=None):
    """(items, notes): units the committed census says do not link, one item per source,
    credited with its matched bytes, nearest to linking (fewest blockers) first.

    The census can be many commits old. A unit whose source, or a header its build
    receipt recorded, changed since the census COMMIT is re-predicted (link_predictions);
    it is dropped only when link_check proves it LINKS, otherwise served with what
    link_check said or why it could not say. A unit with no receipt is labelled "own
    source unchanged" and kept. A census unit whose source is gone, or that holds no
    matched row now, is counted in the notes, never skipped silently."""
    by_rva, _ = ledger()
    rows_of = {}
    for rva, rows in by_rva.items():
        for row in rows:
            rows_of.setdefault(row["source"], []).append((rva, row))
    items, vanished, rowless = [], [], []
    # The committed census is on origin/master: a claim's `debt=` note waits on its row
    # (claims.settle_scopes releases it once that census says linked=yes).
    debt = {"baseline": CENSUS_STATUS} if Path(path) == ROOT / CENSUS_STATUS else {}
    with Path(path).open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            if row.get("linked") == "yes":
                continue
            if row["source"] not in rows_of:
                (rowless if (ROOT / row["source"]).exists() else vanished).append(row["source"])
                continue
            owned = sorted(rows_of[row["source"]], key=lambda r: r[0])
            blockers = {k: int(row.get(k) or 0) for k in
                        ("unresolved", "duplicates", "comdat_losers", "addresses", "wrong_selected")}
            size = sum(int(r["target_size"] or 0) for _, r in owned)
            items.append({
                "tier": "link", "check": "unit-link", "target_rva": "0x%08X" % owned[0][0],
                "function": owned[0][1]["name"], "source": row["source"], "size": size, "credit": size, "placed": False,
                "blockers": sum(blockers.values()), "fresh": "",
                "claim": [f"file:{row['source']}"],              # the unit is the work: one seat per file
                "why": ("unit does not link (%d matched row(s)): " % len(owned)
                        + (", ".join("%s %d" % kv for kv in blockers.items() if kv[1]) or "linked=no")),
                "pass_test": f"python3 tools/link_check.py {row['source']}: LINKS (the next census: linked=yes)",
                **({"debt_lines": [row["source"]], **debt} if debt else {}),
            })
    notes = []
    for names, what in ((vanished, "whose source no longer exists"),
                        (rowless, "whose source holds no matched row now (re-homed?)")):
        if names:
            notes.append(f"{len(names)} census unit(s) {what}, not served: " + ", ".join(names[:3])
                         + (" ..." if len(names) > 3 else ""))
    changed = changed_since(commit) if commit else None
    if changed is None:
        notes.append("freshness not checked: " + (f"census commit {commit[:10]} is not in this clone"
                                                   if commit else "the census names no commit"))
        for item in items:
            item["fresh"] = "not checked against the census commit"
        items.sort(key=lambda item: (item["blockers"], -item["size"]))
        return items, notes
    headers = {p for p in changed if not p.lower().endswith((".cpp", ".c", ".cc", ".cxx", ".asm"))}
    moved, blind = [], 0
    for item in items:
        deps = unit_deps(item["source"]) if headers else set()
        hit = sorted(deps & headers) if deps else []
        if item["source"] in changed:
            item["fresh"] = "its source changed since the census"
        elif hit:
            item["fresh"] = f"{len(hit)} header(s) it includes changed since the census (e.g. {hit[0]})"
        elif deps is None:
            blind += 1
            item["fresh"] = "own source unchanged since the census; its headers unchecked (no build receipt)"
            continue
        else:
            item["fresh"] = "its source and recorded headers are unchanged since the census"
            continue
        moved.append(item)
    verdicts = link_predictions([item["source"] for item in moved], commit) if moved else {}
    counts, unknown = {True: 0, False: 0, None: 0}, []
    for item in moved:
        links, detail = verdicts.get(item["source"], (None, "not predicted"))
        counts[links] += 1
        if links:
            item["drop"] = True
            continue
        if links is None:
            unknown.append(detail)
        item["fresh"] += (f"; link_check now: does not link ({detail})" if links is False
                          else f"; no link_check verdict, kept: {detail}")
        item["why"] += "; " + item["fresh"]
    items = [item for item in items if not item.pop("drop", False)]
    if moved:
        notes.append(f"{len(moved)} unit(s) changed since census commit {commit[:10]} (source or recorded "
                     f"headers): {counts[True]} proven LINKS and dropped, {counts[False]} still do not link, "
                     f"{counts[None]} kept with no verdict" + (f" ({unknown[0]})" if unknown else ""))
    if blind:
        notes.append(f"{blind} unit(s) have no build receipt, so header changes since the census are unchecked "
                     "(kept)")
    items.sort(key=lambda item: (item["blockers"], -item["size"]))
    return items, notes


def link_items(path=None):
    """BFME2 link repairs, with a note naming the source read and the commit it describes:
    a link cycle's rows not placed at retail RVA or placed but not self-strict, else the
    committed census's units that do not link (link_source), freshness-filtered against
    the commit the committed census's history row names."""
    if BFME1:
        return [], "BFME1 has no link cycle yet"
    kind, path, note = link_source(path)
    if kind is None:
        return [], note
    if kind == "census":
        census = stored_census() if Path(path) == ROOT / CENSUS_STATUS else None
        items, notes = census_items(path, census["commit"] if census else None)
        return items, "; ".join([f"{len(items)} unit(s) that do not link, from the {note}"] + notes)
    items = cycle_items(path)
    return items, f"{len(items)} row(s) from the {note}"


def open_status(path):
    """A link_status.csv, plain or gzip (by its magic bytes), as text."""
    path = Path(path)
    with path.open("rb") as handle:
        gz = handle.read(2) == b"\x1f\x8b"
    if gz:
        return io.TextIOWrapper(gzip.open(path), encoding="utf-8", newline="")
    return path.open(encoding="utf-8", newline="")


def cycle_items(path):
    """A link cycle's real rows not placed at their retail RVA, or placed but not
    self-strict: placed ones first, then by size."""
    items = []
    with open_status(path) as handle:
        for row in csv.DictReader(handle):
            if row.get("kind") != "real" or (row["placed"] == "1" and row["self_strict"] == "1"):
                continue
            placed = row["placed"] == "1"
            reason = (row["failures"] or "not self-strict") if placed else (row["placement_reason"] or "not placed")
            items.append({
                "tier": "link", "target_rva": row["retail_rva"], "function": row["name"],
                "source": row["source"], "size": int(row["size"] or 0), "credit": int(row["size"] or 0),
                "placed": placed, "why": reason[:300],
                "pass_test": "python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1",
            })
    # placed-but-not-strict first: one relocation fix credits the whole row
    items.sort(key=lambda item: (not item["placed"], -item["size"]))
    return items


def cycle_artifacts():
    """tools/cycle_artifacts.py, imported here, not at the top: the hooks run this file
    through stdin (verify-removed) without tools/ on the path."""
    tools = str(Path(_SCRIPT).resolve().parent if _HAS_SCRIPT else ROOT / "tools")
    if tools not in sys.path:
        sys.path.insert(0, tools)
    import cycle_artifacts as ca
    return ca


def bundle_note(b, fr, what):
    return (f"{what} from link-cycle bundle {b.tag} ({b.dir}; commit {b.commit[:12]}, measured "
            f"{fr['measured_end_utc']} UTC, {fr['age_hours']:.1f} h ago{', STALE' if fr['stale'] else ''}; "
            + ("authenticated publication" if b.evidence else "UNAUTHENTICATED LOCAL BUNDLE") + f"; {fr['ancestry']})")


def bundle_warnings(lines, fr):
    out = [line for line in lines if line.startswith(("STALE", "UNAUTHENTICATED", "NOT THE NEWEST"))]
    if fr["tool_digest_matches"] is False:
        out += [line for line in lines if line.startswith("link_cycle tool digest")]
    return out


def bundle_link_items(bundle, now=None, allow_stale=False, local_unpublished=False):
    """(items, note, warnings) from a published link-cycle bundle (a store, or a bundle
    directory): authenticated, validated, of this checkout's rules, and fresh or ALLOW_STALE.
    Raises a cycle_artifacts.Problem with its reason: never a census fallback."""
    ca = cycle_artifacts()
    b, fr, lines = ca.serve(bundle, allow_stale=allow_stale, now=now, root=ROOT, local_unpublished=local_unpublished)
    items = cycle_items(b.link_status)
    return items, bundle_note(b, fr, f"{len(items)} row(s)"), bundle_warnings(lines, fr)


def closure_items(bundle, now=None, allow_stale=False, local_unpublished=False):
    """(items, note lines, warnings): the closure roots (tools/closure_report.py) of the
    store's newest bundle that has a closure report, ranked by conditional single-address
    gain. Raises as bundle_link_items does; reason no-closure-report when there is none."""
    ca = cycle_artifacts()
    import closure_report as cr
    b, fr, lines = ca.serve(bundle, allow_stale=allow_stale, now=now, root=ROOT, need_closure=True,
                            local_unpublished=local_unpublished)
    try:
        doc = cr.load_roots(b.closure_roots)
    except cr.ReportError as e:                   # another schema or algorithm: not this checkout's ranking
        raise ca.Refused(f"bundle {b.tag}: {e}", "incompatible-rules") from None
    items = []
    for e in doc["roots"]:
        name, source = cr.root_line(e)
        items.append({
            "tier": "closure", "target_rva": e["root"], "function": name, "source": source or "(no unit)",
            "size": e["conditional_gain_bytes"], "credit": e["conditional_gain_bytes"], "placed": True,
            "check": "closure",
            "why": (f"beneficiaries {e['beneficiary_rows']} row(s) {e['beneficiary_bytes']} B + own failing rows "
                    f"{e['direct_rows']} / {e['direct_bytes']} B; {len(e['nodes'])} failed node(s) at this address; "
                    f"{len(e['failures'])} failure(s) to clear: " + "; ".join(e["failures"])),
            "pass_test": "a later published bundle (tools/cycle_artifacts.py fetch --latest) no longer lists root "
                         f"{e['root']} and its rows are closed_strict=1"
                         + ("" if e.get("verified") else " [gain not re-proved by a forced closure]"),
        })
    s = doc["summary"]
    reach, buckets = s["closure_blocked_reach"], s["buckets"]
    size = (lambda table, k: table.get(k, {}).get("unique_bytes", 0))
    bucket, single = size(buckets, "closure-blocked"), size(reach, "one scored root")
    share = f"{100.0 * single / bucket:.1f}%" if bucket else "n/a"
    notes = [bundle_note(b, fr, f"{len(items)} closure root(s) with a gain"),
             f"  graph: {doc['graph']['label']}"
             + ("" if doc["graph"]["bound"] else ": the edges were rebuilt after the run, not written by its measure"),
             f"  credit {s['credit_unique_bytes']:,} B. Placed real rows outside it: {size(buckets, 'failing'):,} B "
             f"fail their own checks; {bucket:,} B are self-strict but closure-blocked; closed-strict but not "
             f"placed: {size(buckets, 'closed-strict-unplaced'):,} B (repair_queue.py link).",
             f"  COVERAGE: single roots cover only {single:,} B of the {bucket:,} B closure bucket ({share}); "
             f"{size(reach, 'two or more'):,} B sit behind two or more roots and {size(reach, 'one unscored leaf'):,} B "
             "behind one filler or unknown target, and are in no root's score. "
             f"{s['roots_with_no_beneficiary']} of the {len(items)} roots unblock only their own failing rows.",
             "  B column: CONDITIONAL single-address gain = credit(graph with every failed node at that retail "
             "address passing) - credit(graph), unique bytes, on the frozen graph of the measured commit.",
             "  limits: " + "; ".join(doc["limits"]) + "."]
    return items, notes, bundle_warnings(lines, fr)


# ---------------------------------------------------------------- identity and header debt

DATA_BASELINE = f"{REV}/data_check_baseline.txt"          # tools/data_check.py, shrink-only
HEADER_QUEUE = f"{REV}/header_queue.tsv"                  # tools/header_adopt_lane.py run --apply
IDENTITY_BASELINE = f"{REV}/code_identity_baseline.tsv"   # tools/code_identity_gate.py, shrink-only
IDENTITY_WHY = {
    "wrong": "binds {symbol} at {target}, but the copy of {symbol} the link keeps is not retail's body there",
    "interior": "binds {symbol}, whose {target} lies inside a row, not at its start",
    "unowned": "binds {symbol} at {target}, which no ledger row owns (tools/auto_rows.py, or bind the owner)",
    "divergent": "binds {symbol} at {target}; its copies differ and the kept one is not certified "
                 "(one shared view of the class)",
}


def class_of(symbol):
    """The class a decorated member name belongs to ('Outer::Inner'), or None:
    tools/claims.py member_class (member access codes only; a namespace's free
    function names no class)."""
    tools_on_path()
    import claims
    return claims.member_class(symbol)


def sources_bytes():
    """{source: matched bytes} from the ledger."""
    by_rva, _ = ledger()
    out = {}
    for rows in by_rva.values():
        for row in rows:
            out[row["source"]] = out.get(row["source"], 0) + int(row["target_size"] or 0)
    return out


def gone_note(gone, what):
    return (f"; {len(gone)} source(s) its {what} name no longer exist, served first as regressions ("
            + ", ".join(sorted(gone)[:3]) + (" ..." if len(gone) > 3 else "") + ")") if gone else ""


def vanished_items(tier, gone, path):
    """Debt a register still holds for sources that no longer exist: regressions to
    investigate (the debt went nowhere; deleting a source is not a fix), served first."""
    retire = {"data": "data", "identity": "identity"}.get(tier)
    return [{
        "tier": tier, "check": "vanished-source", "target_rva": "", "function": source, "source": source,
        "size": 0, "credit": 0, "baseline": path, "debt_lines": sorted(lines), "claim": [f"file:{source}"],
        "why": (f"{len(lines)} line(s) of {path} name {source}, which no longer exists: find where its rows went "
                f"(git log --diff-filter=DR -- {source}) and restore or re-home them"),
        "pass_test": (f"python3 tools/repair_queue.py retire {retire} {source} once the source exists again"
                      if retire else "the unit exists again and passes tools/header_adopt_lane.py accept"),
    } for source, lines in sorted(gone.items())]


def data_identity_items():
    """(items, note): one item per reverse/data_check_baseline.txt key
    (`source<TAB>check<TAB>symbol<TAB>address`; tools/data_check.py). wrong-name: SOURCE
    reaches the data address through SYMBOL, not the data ledger's name for it;
    duplicate-def: SOURCE defines SYMBOL at an address another unit owns. Both link as a
    second datum. duplicate-def first (a link blocker), then wrong-name keys whose
    address carries the most keys (one declaration fix, repeated). Each claims
    `file:SOURCE`. PASS TEST: `retire data SOURCE` -- data_check's own verdict on the
    current objects, which deletes the key (see retiring debt). Keys of a source that no
    longer exists are served first as regressions. Absent file: skipped, said so."""
    if not (ROOT / DATA_BASELINE).exists():
        return [], f"{DATA_BASELINE} absent: data-identity queue skipped"
    tools_on_path()
    import data_check
    keys = sorted(data_check.read_baseline(_read(DATA_BASELINE)))
    names = {}
    try:
        import data_ledger
        names = data_ledger.load(ROOT / f"{REV}/data_ledger.csv")
    except (ImportError, OSError, ValueError) as error:
        print(f"repair_queue: data ledger unreadable ({error}); data items carry no ledger name",
              file=sys.stderr)
    per_address = {}
    for key in keys:
        if len(key) == 4:
            per_address[key[3]] = per_address.get(key[3], 0) + 1
    items, gone = [], {}
    for key in keys:
        if len(key) != 4:
            continue
        source, check, symbol, address = key
        line = "\t".join(key)
        if not (ROOT / source).exists():
            gone.setdefault(source, []).append(line)
            continue
        try:
            owner = names.get(int(address, 16), {})
        except ValueError:
            owner = {}
        real = owner.get("name") or "(no ledger name)"
        if check == "duplicate-def":
            why = (f"defines {symbol} at {address}, which {owner.get('source') or 'another unit'} owns: "
                   f"declare it extern ({real}) instead of defining it")
        else:
            why = (f"reaches {address} through {symbol}; the data ledger's global there is {real}: declare "
                   f"the real global and cast to your view where you use it")
        items.append({
            "tier": "data", "check": check, "target_rva": "", "address": address, "function": symbol,
            "source": source, "size": 0, "credit": 0, "ledger_name": real, "keys_at_address": per_address[address],
            "why": why + (f" ({per_address[address]} key(s) at this address)" if per_address[address] > 1 else ""),
            "baseline": DATA_BASELINE, "baseline_line": line, "debt_lines": [line], "claim": [f"file:{source}"],
            "pass_test": (f"./build.sh {source} && python3 tools/repair_queue.py retire data {source}: "
                          "tools/data_check.py's own check of the current objects no longer finds the key and "
                          "finds nothing new; it then deletes the key (never by hand)"),
        })
    items.sort(key=lambda i: (i["check"] != "duplicate-def", -i["keys_at_address"], i["address"], i["source"]))
    kinds = {}
    for item in items:
        kinds[item["check"]] = kinds.get(item["check"], 0) + 1
    return vanished_items("data", gone, DATA_BASELINE) + items, (
        f"{len(items)} data-identity key(s) from {DATA_BASELINE} ("
        + ", ".join(f"{k} {n}" for k, n in sorted(kinds.items())) + ")" + gone_note(gone, "keys"))


HEADER_ESTABLISH_LIMIT = 30   # classes without a header served at once, by merge donors unblocked


def _contract_virtual(path):
    """Does the frozen contract at `path` give the class a vfptr or virtual slots?"""
    try:
        contract = json.loads(Path(path).read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return False
    return bool(contract.get("vslots")) or any(f.get("kind") == "VPTR" for f in contract.get("fields", ()))


def header_items():
    """(items, note): reverse/header_queue.tsv units that did not adopt their class's
    canonical header (tools/header_adopt_lane.py run --apply queues them), classes whose
    header unblocks the most queued merge donors first (header_adopt_lane.merge_rank, which
    never ranks a prerequisite below what needs it), then by DEPENDENCY_ORDER (a header is
    adopted once the types it uses have one definition) and source; `rank` and
    `merge_donors` carry that order into the draw. After them, up to HEADER_ESTABLISH_LIMIT
    classes without a header whose private views block queued merges
    (`class-header-establish`: contract, generate, apply through the lane).
    Each item claims `class:NAME` and includes every queued source of that class in
    its work footprint, even private views without member rows in the ledger. The
    first diagnostic is often a member the header lacks, so the fix is class-wide. An
    establish item claims every file `run --apply` may rewrite: the class's census (every
    authored unit with a private body of it, which holds the dependency views stripped with
    it) and its header destination; a class whose census is not cached is not served. The
    ranking is read from the shared picker cache only (header_adopt_lane.merge_payload_nonblocking):
    a miss ranks by DEPENDENCY_ORDER and starts one background refresh. PASS TEST: the row's
    acceptance (`header_adopt_lane.py accept`), which retires the row when it passes."""
    if not (ROOT / HEADER_QUEUE).exists():
        return [], f"{HEADER_QUEUE} absent: class-header queue skipped"
    tools_on_path()
    import header_adopt_lane
    rank = {name: i for i, (_, names) in enumerate(header_adopt_lane.DEPENDENCY_ORDER) for name in names}
    canon = header_adopt_lane.registered()
    payload, merge_note = None, ""
    try:
        if Path(ROOT).resolve() != header_adopt_lane.ROOT.resolve():
            raise RuntimeError(f"the lane's tree is {header_adopt_lane.ROOT}, not {ROOT}")
        payload, merge_note = header_adopt_lane.merge_payload_nonblocking()
    except Exception as exc:  # noqa: BLE001 - the ranking is advisory; say so instead of hiding it
        merge_note = f"merge ranking unavailable ({type(exc).__name__}: {exc}), DEPENDENCY_ORDER only"
    merge_note = f"; {merge_note}" if merge_note else ""
    payload = payload or {}
    blockers, census, destinations = (payload.get("classes") or {}, payload.get("census") or {},
                                      payload.get("destinations") or {})
    merges = {c: score for c, score, _ in header_adopt_lane.merge_rank(blockers, canon)}
    credit = sources_bytes()
    items, gone = [], {}
    queued = list(csv.DictReader(io.StringIO(_read(HEADER_QUEUE)), delimiter="\t"))
    class_sources = {}
    for row in queued:
        if row.get("class") and row.get("source"):
            class_sources.setdefault(row["class"], set()).add(row["source"])
    for row in queued:
        name, source = row.get("class") or "", row.get("source") or ""
        if not name or name == "class" or not source:
            continue
        if not (ROOT / source).exists():
            gone.setdefault(source, []).append(f"{name}\t{source}")
            continue
        rvas = (row.get("retail_rvas") or "").split()
        items.append({
            "tier": "header", "check": "class-header", "class": name, "target_rva": rvas[0] if rvas else "",
            "function": name, "source": source, "size": 0, "credit": credit.get(source, 0),
            "header": row.get("header", ""), "rank": rank.get(name, len(rank)), "ranks": len(rank) + 1,
            "merge_donors": merges.get(name, 0),
            "why": f"adopt {row.get('header') or 'the canonical header'} for {name}: {row.get('failure', '')}",
            "claim": [f"class:{name}"] + [f"file:{s}" for s in sorted(class_sources[name])],
            "baseline": HEADER_QUEUE,
            "debt_lines": [f"{name}\t{source}"],
            "pass_test": (header_adopt_lane.acceptance_command(name, source) + ": the unit #includes the header, "
                          "declares no private body and byte-matches; the command then retires the row"),
        })
    queued_classes = {i["class"] for i in items}
    contracts = header_adopt_lane.class_contract.CONTRACTS
    establish, uncensused = [], 0
    for name, score, own in header_adopt_lane.merge_rank(blockers, canon):
        if name in canon or name in queued_classes or len(establish) >= HEADER_ESTABLISH_LIMIT:
            continue
        if name not in census:            # its footprint is unknown: never serve a partial claim
            uncensused += 1
            continue
        d = blockers.get(name, {})
        dest = destinations.get(name) or {"header": None, "why": "no destination cached"}
        files = sorted(set(d.get("files", ())) | set(census[name]) | ({dest["header"]} if dest["header"] else set()))
        contract = contracts / (header_adopt_lane.class_contract.portable_component(name) + ".json")
        if d.get("virtual") or _contract_virtual(contract):
            # generate() writes no virtual functions yet (docs/linking_obstacles.md, "Module base
            # chain"): a polymorphic class's header is written by hand and adopted as a fixed header
            where = (f"at {dest['header']} (from {dest['evidence']})" if dest["header"] else
                     f"at the official BFME path python3 tools/header_adopt_lane.py dest --class {name} names "
                     f"(none now: {dest['why']}; choose from its evidence, never invent one)")
            obstacle = ("header_adopt_lane generate() emits no virtual functions (docs/linking_obstacles.md, "
                        "\"Module base chain\"), and this class is polymorphic")
            generate = (f"write {name}'s canonical header by hand {where} from the contract and the retail "
                        f"vtables (class_contract.py's vslots, reverse/vtables.tsv), then python3 "
                        f"tools/header_adopt_lane.py run --class {name} --header "
                        f"{dest['header'] or 'PATH'} --sample 60 (no --generate), then --apply")
        else:
            obstacle = ""
            generate = (f"python3 tools/header_adopt_lane.py run --class {name} --header {dest['header']} "
                        f"--generate --sample 60 (destination from {dest['evidence']}), then --apply"
                        if dest["header"] else
                        f"no header destination ({dest['why']}): run python3 tools/header_adopt_lane.py dest "
                        f"--class {name}, choose an official BFME path from its evidence (never invent one), then "
                        f"python3 tools/header_adopt_lane.py run --class {name} --header PATH --generate --sample "
                        "60, then --apply")
        establish.append({
            **({"obstacle": obstacle} if obstacle else {}),
            "tier": "header", "check": "class-header-establish", "class": name, "target_rva": "",
            "function": name, "source": (d.get("files") or [""])[0], "size": 0, "credit": 0,
            "rank": rank.get(name, len(rank)), "ranks": len(rank) + 1, "merge_donors": score,
            "credit_note": (f"unblocks up to {score} merge donor(s) ({own} of its own views"
                            f"{', ' + str(d.get('rows', 0)) + ' rows in ' + str(len(d.get('tus', ()))) + ' TU(s)' if d else ''}"
                            "; the rest through classes that need it first)"),
            "why": (f"no canonical header for {name}; its private views disagree inside queued merges ("
                    + (", ".join(f"{k} {n}" for k, n in sorted(d.get("kinds", {}).items())) or
                       "needed first by a class that does") + ")" + (f"; OBSTACLE: {obstacle}" if obstacle else "")),
            "header": dest["header"] or "",
            "start": ((f"python3 tools/class_contract.py --class {name} --write; " if not contract.exists() else
                       f"read {contract.relative_to(ROOT).as_posix()}; ") + generate
                      + " (the contract's evidence rules decide every attribute; an undecided one is not guessed)"),
            "claim": [f"class:{name}"] + [f"file:{f}" for f in files],
            "pass_test": (f"reverse/canonical_classes.csv registers {name} through header_adopt_lane.py run --apply, "
                          "the adopted units build exact and the rest are queued in " + HEADER_QUEUE),
        })
    # The classes whose header unblocks the most queued merge donors first; DEPENDENCY_ORDER
    # stays a floor (merge_rank never ranks a prerequisite below what needs it).
    items.sort(key=lambda i: (-i["merge_donors"], i["rank"], i["class"], i["source"]))
    establish.sort(key=lambda i: (-i["merge_donors"], i["class"]))
    classes = len({i["class"] for i in items})
    return vanished_items("header", gone, HEADER_QUEUE) + items + establish, (
        f"{len(items)} unit(s) of {classes} class(es) from {HEADER_QUEUE}" + gone_note(gone, "rows")
        + f"; {len(establish)} class(es) without a header ranked by merge donors unblocked "
          "(header_adopt_lane.py order --merges)"
        + (f", {uncensused} more without a cached census not served" if uncensused else "") + merge_note)


def identity_items():
    """(items, note): one item per reverse/code_identity_baseline.tsv key
    (`source<TAB>row<TAB>symbol<TAB>retail target<TAB>class`; tools/code_identity_gate.py,
    classes in tools/allowed_symbols.py): ROW's reference to TARGET binds SYMBOL, which
    the link does not resolve to retail's body there. `divergent` keys of a class member
    claim `class:NAME` (the copies are the class's views); the rest claim the row.
    PASS TEST: `retire identity SOURCE` -- allowed_symbols' own scan of the current
    objects, which deletes the key (see retiring debt)."""
    if not (ROOT / IDENTITY_BASELINE).exists():
        return [], f"{IDENTITY_BASELINE} absent: code-identity queue skipped"
    tools_on_path()
    import code_identity_gate
    keys, mode = code_identity_gate.read_register(_read(IDENTITY_BASELINE))
    by_rva, _ = ledger()
    rva_of = {(row["source"], row["name"]): rva for rva, rows in by_rva.items() for row in rows}
    items, gone = [], {}
    for line in sorted(keys):
        parts = line.split("\t")
        if len(parts) != 5:
            continue
        source, name, symbol, target, cls = parts
        if not (ROOT / source).exists():
            gone.setdefault(source, []).append(line)
            continue
        rva = rva_of.get((source, name))
        try:
            owners = [r["name"] for r in by_rva.get(int(target, 16), [])]
        except ValueError:
            owners = []
        scope = class_of(symbol) if cls == "divergent" else None
        size = next((int(r["target_size"] or 0) for r in by_rva.get(rva, []) if r["name"] == name), 0)
        items.append({
            "tier": "identity", "check": cls, "target_rva": "0x%08X" % rva if rva is not None else "",
            "function": name, "symbol": symbol, "binding_target": target, "source": source,
            "size": size, "credit": size, "class": scope,
            "why": (IDENTITY_WHY.get(cls, "binds {symbol} at {target}").format(symbol=symbol, target=target)
                    + (f"; {target}'s owner: {owners[0]}" if owners else "")),
            "baseline": IDENTITY_BASELINE, "baseline_line": line, "debt_lines": [line],
            "claim": [f"class:{scope}"] if scope else ([] if rva is not None else [f"file:{source}"]),
            "pass_test": (f"./build.sh {source} && python3 tools/repair_queue.py retire identity {source}: "
                          f"tools/allowed_symbols.py's own scan of the current objects no longer binds {symbol} "
                          f"at {target} from this row and finds nothing new; it then deletes the key (never by "
                          "hand)"),
        })
    items.sort(key=lambda i: (i["check"] == "unowned", -i["size"], i["source"]))
    kinds = {}
    for item in items:
        kinds[item["check"]] = kinds.get(item["check"], 0) + 1
    return vanished_items("identity", gone, IDENTITY_BASELINE) + items, (
        f"{len(items)} code-identity key(s) from {IDENTITY_BASELINE}, mode {mode} ("
        + ", ".join(f"{k} {n}" for k, n in sorted(kinds.items())) + ")" + gone_note(gone, "keys"))


# ---------------------------------------------------------------- retiring debt
#
# A debt line leaves its register only on the owning tool's verdict on fresh evidence,
# never by a hand deletion: `retire data|identity SOURCE` re-runs tools/data_check.py's
# or tools/allowed_symbols.py's own check of SOURCE against objects build.compile_is_current
# proves built from the tree as it is, and deletes exactly the keys that check no longer
# finds. It refuses -- writing nothing -- when it cannot judge: the source is gone, a row
# the source held at HEAD is gone (lost coverage hides findings), an object is missing,
# stale or unreadable, a row's symbol is absent, or the check finds anything the register
# does not already hold (a rename trades one key for another). verify-removed applies the
# same verdict to every key the index deletes from either register, and header
# acceptance (tools/header_adopt_lane.py verdict) to every header_queue.tsv row it deletes.
# .githooks/pre-commit runs it (HEAD's copy, through stdin) whenever a commit stages or
# deletes any of the three registers: they set baseline_changed like gate_baseline.txt.


def problems_note(problems):
    return "; ".join(problems[:4]) + (f" (+{len(problems) - 4} more)" if len(problems) > 4 else "")


@lru_cache(maxsize=1)
def head_ledger_rows():
    """{source: {row names}} of the matched rows HEAD's ledger holds ({} when HEAD has none)."""
    got = _git("show", f"{DEBT_BASE}:{LEDGER}")
    out = {}
    if got.returncode:
        return out
    for row in csv.DictReader(io.StringIO(got.stdout)):
        if row.get("status") == "matched" and row.get("target_rva"):
            out.setdefault(row["source"], set()).add(row["name"])
    return out


def coverage_problems(source, names):
    """Why SOURCE's rows cannot vouch for a clean verdict: gone, rowless, or rows lost since HEAD."""
    if not (ROOT / source).exists():
        return [f"{source} no longer exists: its debt is a regression to investigate (restore or re-home its "
                "rows), never a fix"]
    if not names:
        return [f"{source} holds no matched row: nothing left to judge (lost row coverage)"]
    lost = sorted(head_ledger_rows().get(source, set()) - set(names))
    return [f"{len(lost)} row(s) HEAD held are gone from {source} (lost coverage hides findings): "
            + ", ".join(lost[:3])] if lost else []


def data_verdict(source, held):
    """(problems, found keys) from tools/data_check.py's own check of SOURCE. `held`: the
    register's keys for SOURCE; a finding outside it is a problem (never silently added)."""
    tools_on_path()
    import build
    import data_check
    import data_ledger
    rows = data_check.source_rows([source])
    problems = coverage_problems(source, {r["name"] for r in rows})
    if problems:
        return problems, set()
    for obj in sorted({build.row_object(r) for r in rows}):
        if not obj.exists():
            problems.append(f"no object {obj.name} (./build.sh {source})")
        elif not source.lower().endswith(build.LIB_SUFFIX) and not build.compile_is_current(ROOT / source, obj):
            problems.append(f"object {obj.name} is not current for its source and headers (./build.sh {source})")
    if problems:
        return problems, set()
    unread = []
    facts = data_check.object_facts(rows, unread)
    problems += [f"row {name} unreadable: {why}" for _, name, why in unread]
    try:
        ledger_rows = data_ledger.load()
    except (OSError, ValueError) as error:
        return problems + [f"data ledger unreadable: {error}"], set()
    if not ledger_rows:
        return problems + ["no data ledger: nothing judges the keys"], set()
    found = set(data_check.findings(facts, ledger_rows))
    problems += ["new finding " + "\t".join(k) for k in sorted(found - set(held))]
    return problems, found


def identity_verdict(source, held):
    """(problems, found keys) from tools/allowed_symbols.py's own scan of SOURCE's rows,
    failing where scan() would skip silently: a missing or stale object (any ledger
    object: the kept copy is judged against every definition), an unparsable object, a
    participating provider (an object defining a name SOURCE's objects reference) not
    proven current for its own source, a row symbol the object lacks, unreadable retail
    bytes, a scan error."""
    tools_on_path()
    import allowed_symbols as allowed
    import build
    try:
        ident, rows = allowed.load([source], strict=True)
    except allowed.Unreadable as error:
        return [f"an object is unreadable, so the kept copies are unknown: {error}"], set()
    problems = coverage_problems(source, {r["name"] for r in rows})
    if problems:
        return problems, set()
    ledger_rows = allowed.census.ledger()
    missing = sorted({str(allowed.row_object(r)) for r in ledger_rows
                      if not r["source"].lower().endswith(".asm") and not allowed.row_object(r).exists()})
    if missing:
        problems.append(f"{len(missing)} ledger object(s) missing, so the kept copies are unknown "
                        f"(e.g. {Path(missing[0]).name}; ./build.sh)")
    source_of = {}
    for r in ledger_rows:
        source_of.setdefault(str(allowed.row_object(r)), r["source"])
    own = {str(allowed.row_object(r)) for r in rows}
    referenced = {name for name, users in (ident.defs.referrers or {}).items() if users & own}
    providers = sorted({p for name in referenced for p, *_ in ident.defs.get(name, ())} - own)
    stale = [p for p in providers if not source_of.get(p, "").lower().endswith(build.LIB_SUFFIX)
             and not (p in source_of and build.compile_is_current(ROOT / source_of[p], Path(p)))]
    if stale:
        problems.append(f"{len(stale)} provider object(s) of names {source} references are not proven current "
                        f"(e.g. {Path(stale[0]).name}; ./build.sh {source_of.get(stale[0], '')})")
    found = set()
    for row in rows:
        if row["source"].lower().endswith((".asm", build.LIB_SUFFIX)):
            continue
        obj = allowed.row_object(row)
        if not obj.exists():
            continue                                         # counted above
        if not build.compile_is_current(ROOT / source, obj):
            problems.append(f"object {obj.name} is not current (./build.sh {source})")
            break
        symbol = build.ledger_object_symbol(row)
        o = ident.obj(str(obj))
        retail = ident.read(int(row["target_rva"], 16), int(row["target_size"]))
        if retail is None:
            problems.append(f"row {row['name']}: retail bytes unreadable")
            continue
        try:
            if allowed.row_code_symbol(row, o, retail) is None:
                problems.append(f"row {row['name']}: {obj.name} defines no code symbol {symbol}")
                continue
            refs = ident.row_refs(row)
        except (Exception, SystemExit) as error:              # scan() would skip it silently
            problems.append(f"row {row['name']}: scan failed: {error}")
            continue
        found |= {allowed.key((row,) + ref) for ref in refs if ref[4] in allowed.WRONG}
    problems += ["new finding " + k for k in sorted(found - set(held))]
    return problems, found


def register_keys(kind, text):
    """The key set a register text holds: data tuples, identity lines."""
    tools_on_path()
    if kind == "data":
        import data_check
        return data_check.read_baseline(text)
    import code_identity_gate
    return code_identity_gate.read_register(text)[0]


def key_source(kind, key):
    return key[0] if kind == "data" else key.split("\t", 1)[0]


def key_line(kind, key):
    return "\t".join(key) if kind == "data" else key


REGISTERS = {"data": DATA_BASELINE, "identity": IDENTITY_BASELINE}


def verdict_of(kind, source, held):
    return (data_verdict if kind == "data" else identity_verdict)(source, held)


def retire(kind, source):
    """Delete from KIND's register exactly the SOURCE keys the owning tool no longer
    finds, after a clean verdict. Returns (ok, message); writes nothing unless ok."""
    path = ROOT / REGISTERS[kind]
    if not path.exists():
        return False, f"{REGISTERS[kind]} absent"
    text = path.read_bytes().decode("utf-8")
    held = {k for k in register_keys(kind, text) if key_source(kind, k) == source}
    if not held:
        return False, f"{REGISTERS[kind]} holds no key for {source}"
    problems, found = verdict_of(kind, source, held)
    if problems:
        return False, f"REFUSED, nothing retired: {problems_note(problems)}"
    fixed = {key_line(kind, k) for k in held - found}
    if not fixed:
        return False, f"all {len(held)} key(s) of {source} are still found; nothing retired"
    eol = "\r\n" if "\r\n" in text else "\n"
    kept = [line for line in text.split(eol) if line.rstrip("\r") not in fixed]
    tmp = path.with_suffix(path.suffix + ".tmp")
    tmp.write_bytes(eol.join(kept).encode("utf-8"))
    os.replace(tmp, path)
    return True, (f"PASS: {len(fixed)} key(s) of {source} no longer found and retired from {REGISTERS[kind]} "
                  f"({len(held) - len(fixed)} still found); commit the register with the fix")


def removed_keys(kind):
    """({source: [keys]} the index deletes from KIND's register against HEAD, staged keys)."""
    rel = REGISTERS[kind]
    old, new = _git("show", f"{DEBT_BASE}:{rel}"), _git("show", f"{DEBT_TARGET}:{rel}")
    if old.returncode or old.stdout == new.stdout:
        return {}, set()
    staged = register_keys(kind, new.stdout) if new.returncode == 0 else set()
    out = {}
    for key in register_keys(kind, old.stdout) - staged:
        out.setdefault(key_source(kind, key), []).append(key)
    return out, staged


def removed_header_rows():
    """[(class, source)] header_queue.tsv rows the index deletes against HEAD."""
    old, new = _git("show", f"{DEBT_BASE}:{HEADER_QUEUE}"), _git("show", f"{DEBT_TARGET}:{HEADER_QUEUE}")
    if old.returncode or old.stdout == new.stdout:
        return []

    def rows(text):
        return {(r.get("class") or "", r.get("source") or "")
                for r in csv.DictReader(io.StringIO(text), delimiter="\t") if r.get("class")}
    return sorted(rows(old.stdout) - (rows(new.stdout) if new.returncode == 0 else set()))


def _staged_text(path):
    got = _git("show", f"{DEBT_TARGET}:{path}")
    return got.stdout if got.returncode == 0 else ""


_LEDGER_SOURCES = {}


def _ledger_sources(rev):
    """{source: {(name, target_rva)}} of the ledger at `rev` ('' = the index), by blob."""
    blob = _git("rev-parse", f"{rev}:{LEDGER}").stdout.strip()
    if blob not in _LEDGER_SOURCES:
        out = {}
        for r in csv.DictReader(io.StringIO(_git("show", f"{rev}:{LEDGER}").stdout)):
            if r.get("target_rva"):
                out.setdefault(r.get("source") or "", set()).add((r.get("name"), r["target_rva"]))
        _LEDGER_SOURCES[blob] = out
    return _LEDGER_SOURCES[blob]


def _debt_follows(source, dest):
    """`source`'s debt may move to `dest`: the source is gone, or every ledger row it
    held has moved to `dest` and none stays. Judged per source: a valid donor sharing
    the key never excuses another source that keeps its code and rows."""
    if dest == source or not _debt_present(dest):
        return False
    if not _debt_present(source):
        return True
    old, new = _ledger_sources(DEBT_BASE).get(source), _ledger_sources(DEBT_TARGET)
    return bool(old) and not new.get(source) and old <= new.get(dest, set())


def _debt_transferred(kind, source, keys, staged):
    """Every key re-added under a destination this source's debt may follow to (see
    _debt_follows); old duplicates prove nothing."""
    if kind == "header":
        def rows(text):
            return {(r.get("class"), r.get("source")) for r in
                    csv.DictReader(io.StringIO(text), delimiter="\t")}
        old = _git("show", f"{DEBT_BASE}:{HEADER_QUEUE}")
        added = rows(_staged_text(HEADER_QUEUE)) - rows(old.stdout)
        return all(any(name == key and dest and _debt_follows(source, dest)
                       for name, dest in added) for key in keys)
    old = _git("show", f"{DEBT_BASE}:{REGISTERS[kind]}")
    added = set(staged) - register_keys(kind, old.stdout)
    dests = {}
    for k in added:
        dest, _, tail = key_line(kind, k).partition("\t")
        dests.setdefault(tail, set()).add(dest)
    return all(any(_debt_follows(source, dest) for dest in dests.get(key_line(kind, k).split("\t", 1)[1], ()))
               for k in keys)


def _removed_source_accounted(kind, source, keys, staged, message=""):
    """A disappearing unit must transfer its debt, tombstone all rows, or be explained."""
    lines = message.splitlines()
    def explained(key):
        prefix = f"Debt-Retired: {key if kind == 'header' else key_line(kind, key)} {source} "
        return any(line.startswith(prefix) and len(line[len(prefix):].strip()) >= 20 for line in lines)
    if keys and all(explained(key) or _debt_transferred(kind, source, [key], staged) for key in keys):
        return True
    old = _git("show", f"{DEBT_BASE}:{LEDGER}")
    before = [r for r in csv.DictReader(io.StringIO(old.stdout)) if r.get("source") == source]
    after = {(r.get("name"), r.get("target_rva")) for r in
             csv.DictReader(io.StringIO(_staged_text(LEDGER)))}
    deleted = {(r.get("name"), r.get("target_rva")) for r in
               csv.DictReader(io.StringIO(_staged_text("reverse/deleted_rows.csv"))) if r.get("reason")}
    return bool(before) and all((r.get("name"), r.get("target_rva")) in deleted
                               and (r.get("name"), r.get("target_rva")) not in after for r in before)


def verify_missing_debt(message=""):
    """Commit-msg completes the disappearing-source checks deferred by pre-commit."""
    failures = []
    tree = _verification_tree()
    for kind in ("data", "identity"):
        removed, staged = removed_keys(kind)
        for source, keys in removed.items():
            if _debt_present(source):
                failures += _verification_problems(tree, [source])
            elif not _removed_source_accounted(kind, source, keys, staged, message):
                failures.append(f"{source}: removed {kind} debt needs a transfer, deleted_rows coverage or per-key Debt-Retired trailer")
    for name, source in removed_header_rows():
        if _debt_present(source):
            failures += _verification_problems(tree, [source])
        elif not _removed_source_accounted("header", source, [name], (), message):
            failures.append(f"{source}: vanished unit ({name}) needs a transfer, deleted_rows coverage or per-key Debt-Retired trailer")
    return failures


def _head_header_verdict(name, source):
    """Load acceptance and layout helpers from the trusted base, never the edit being judged."""
    import types
    saved = {name: sys.modules.get(name) for name in ("class_contract", "class_layouts")}
    try:
        modules = {}
        for module_name in ("class_layouts", "class_contract", "header_adopt_lane"):
            path = f"tools/{module_name}.py"
            got = _git("show", f"{DEBT_BASE}:{path}")
            if got.returncode:
                return [f"{DEBT_BASE}:{path} unavailable"]
            module = types.ModuleType(module_name)
            module.__file__ = str(ROOT / path)
            if module_name != "header_adopt_lane":
                sys.modules[module_name] = module
            exec(compile(got.stdout, module.__file__, "exec"), module.__dict__)
            modules[module_name] = module
        return modules["header_adopt_lane"].verdict(name, source)
    finally:
        for module_name, previous in saved.items():
            if previous is None:
                sys.modules.pop(module_name, None)
            else:
                sys.modules[module_name] = previous


def verify_removed_debt(build_cmd=None, header_verdict=None, defer_missing=False, message=""):
    """Failures for identity and header debt the index deletes: each removed data or
    identity key's source is built, then judged (the verdict against the staged
    register plus the removed keys: each removed key must be gone, nothing new found);
    each removed header_queue.tsv row must pass header acceptance."""
    failures = []
    tree = _verification_tree()
    judged = set()
    for kind in ("data", "identity"):
        removed, staged = removed_keys(kind)
        for source, keys in sorted(removed.items()):
            if _debt_transferred(kind, source, keys, staged):
                continue
            present = _debt_present(source)
            if not present and (defer_missing or
                    _removed_source_accounted(kind, source, keys, staged, message)):
                continue
            if not present:
                failures.append(f"{source}: removed {kind} debt without a staged/outgoing source or retirement accounting")
                continue
            if present:
                problems = _verification_problems(tree, [source])
                if problems:
                    failures += [f"{source}: {problem}" for problem in problems]
                    continue
                judged.add(source)
                cmd = (build_cmd or [sys.executable, str(ROOT / "tools" / "build.py")]) + [source]
                if subprocess.run(cmd, cwd=ROOT).returncode != 0:
                    failures.append(f"{source}: removed {len(keys)} {kind} key(s) but the source does not build")
                    continue
            held = {k for k in staged if key_source(kind, k) == source} | set(keys)
            problems, found = verdict_of(kind, source, held)
            problems += [f"still found: {key_line(kind, k)}" for k in keys if k in found]
            if problems:
                failures.append(f"{source}: removed {len(keys)} {REGISTERS[kind]} key(s) without the tool's "
                                f"verdict: {problems_note(problems)}")
    for name, source in removed_header_rows():
        if _debt_transferred("header", source, [name], ()):
            continue
        if not _debt_present(source):
            if defer_missing or _removed_source_accounted("header", source, [name], (), message):
                continue
            failures.append(f"{source}: its {HEADER_QUEUE} row ({name}) went with the source; a vanished unit is "
                            "a regression to investigate, not an adoption")
            continue
        if header_verdict is None:
            header_verdict = _head_header_verdict
        problems = _verification_problems(tree, [source])
        if problems:
            failures += [f"{source}: {problem}" for problem in problems]
            continue
        judged.add(source)
        problems = header_verdict(name, source)
        if problems:
            failures.append(f"{source}: {HEADER_QUEUE} row ({name}) removed but acceptance fails: "
                            + "; ".join(problems))
    return failures + (_verification_problems(tree, judged) if judged else [])


def verify_debt_range(base, target, missing=False):
    """Judge the outgoing net retirement, independently of the local index.

    Read explanations only from actual outgoing commit messages. The ordinary
    build must match the outgoing tree, just as the rest of pre-push requires.
    """
    global DEBT_BASE, DEBT_TARGET
    previous = DEBT_BASE, DEBT_TARGET
    try:
        DEBT_BASE, DEBT_TARGET = base, target
        messages = _git("log", "--format=%B", f"{base}..{target}")
        if messages.returncode:
            return ["cannot read outgoing retirement messages"]
        head_ledger_rows.cache_clear()
        if missing:
            return verify_missing_debt(messages.stdout)
        return verify_removed() + verify_removed_debt(message=messages.stdout)
    finally:
        DEBT_BASE, DEBT_TARGET = previous
        head_ledger_rows.cache_clear()


# ---------------------------------------------------------------- structural (Phase 2) queues
#
# The exit test is a link with no stubs and no /FORCE, from files that are retail's
# translation units. These queues serve that work through the same picker, claims and
# fallthrough as the debt queues. None of them retires a register line: each item's pass
# test is the owning tool's own verdict (a later link cycle, tu_skeleton, tu_map, the
# byte gate).
# Their items carry no byte `credit` (a count is not bytes, and next_work's draw reads
# credit as a size): `count` ranks them (next_work.debt_rank_factor) and `credit_note`
# says what it counts.

LINK_CYCLE_SET = os.environ.get("REPAIR_LINK_CYCLE")         # named by hand: used whenever it exists
LINK_CYCLE = LINK_CYCLE_SET or str(ROOT / "build" / "link_cycle")
MS_HEADER_QUEUE = f"{REV}/ms_header_queue.tsv"               # tools/ms_header_audit.py
DX_QUEUE = f"{REV}/dx_migration_queue.tsv"                   # tools/dx_migration.py scan
STLPORT_TRIAL = f"{REV}/stlport_trial.csv"                   # tools/stlport_trial.py report
TU_MAP = f"{REV}/tu_map.csv"                                 # tools/tu_map.py (rebuilt in memory when stale)
UNRESOLVED = re.compile(r'^(o\d+\.obj) : error LNK20(?:01|19): unresolved external symbol '
                        r'(?:"[^"]*" \((\S+)\)|(\S+))')


def _obj_name(source):
    """tools/build.py obj_path's file name for SOURCE (lower case, as zzobj/names.json records it)."""
    stem = "_".join(Path(source).with_suffix("").parts)
    return ("".join(("^" + c.lower()) if c.isupper() else c for c in stem) + ".obj").lower()


def stub_items(path=None):
    """(items, note): the symbols the last link cycle had to stub (stubs.json: names the
    pass-1 link left unresolved, each given a 4-byte .stubd slot so the link completes). The
    exit test needs zero. Read from a local link-cycle output directory (REPAIR_LINK_CYCLE or
    build/link_cycle): stubs.json must be the one its receipt.json names (stubs_sha256 and
    objects_digest), and the receipt's commit must be HEAD or an ancestor of it; otherwise
    the queue is skipped with the reason, never served from another source. A published
    bundle carries only stubs_sha256, not the names, so seats without the measuring
    machine's output see a skip note.

    Referencing units come from the same run's pass1.log (LNK2001/LNK2019) mapped back to
    sources through zzobj/names.json. Member stubs group by class (claims `class:NAME`:
    the fix is the class's definition, plus every file that references a member); a free
    symbol claims the files that reference it, or its pinned RVA. A stub with neither is counted in the note, not served."""
    out = Path(path or LINK_CYCLE)
    need = [out / n for n in ("receipt.json", "stubs.json", "pass1.log", "zzobj/names.json")]
    missing = [p.name for p in need if not p.exists()]
    if missing:
        return [], f"{out}: no link-cycle stub list ({', '.join(missing)} absent): stub-closure queue skipped"
    receipt = json.loads(need[0].read_text(encoding="utf-8"))
    stubs = json.loads(need[1].read_text(encoding="utf-8"))
    names = stubs.get("value") if isinstance(stubs, dict) else None
    digest = hashlib.sha256(json.dumps(names, sort_keys=True).encode()).hexdigest() if names is not None else ""
    if (names is None or digest != receipt.get("stubs_sha256")
            or stubs.get("objects_digest") != receipt.get("objects_digest")):
        return [], f"{out}: stubs.json is not the one receipt.json names: stub-closure queue skipped"
    commit = receipt.get("commit") or ""
    got = subprocess.run(["git", "merge-base", "--is-ancestor", commit, "HEAD"], cwd=ROOT,
                         capture_output=True) if commit else None
    if got is None or got.returncode != 0:
        return [], (f"{out}: link cycle measured commit {commit[:10] or '(none)'}, which is not HEAD or an "
                    "ancestor of it: stub-closure queue skipped")
    stubbed = set(names)
    objects = json.loads(need[3].read_text(encoding="utf-8")).get("names", {})
    sources = {}
    for row in csv.DictReader(io.StringIO(_read(LEDGER))):
        sources.setdefault(_obj_name(row["source"]), row["source"])
    refs = {}
    with need[2].open(encoding="latin-1") as handle:
        for line in handle:
            m = UNRESOLVED.match(line)
            if m and (m.group(2) or m.group(3)) in stubbed:
                source = sources.get(objects.get(m.group(1), ""))
                if source and (ROOT / source).exists():
                    refs.setdefault(m.group(2) or m.group(3), set()).add(source)
    pins = {}
    for row in csv.DictReader(io.StringIO(_read(f"{REV}/symbols.csv"))):
        if row.get("name") in stubbed and (row.get("address") or "").startswith("0x"):
            pins.setdefault(row["name"], row["address"])
    groups, unclaimable = {}, 0
    for name in sorted(stubbed):
        cls = class_of(name)
        if cls:
            groups.setdefault(("class", cls), []).append(name)
        elif refs.get(name) or pins.get(name):
            groups[("symbol", name)] = [name]
        else:
            unclaimable += 1
    age = receipt.get("date_utc", "?")
    items = []
    for (kind, key), members in groups.items():
        users = sorted(set().union(*(refs.get(n, set()) for n in members)))
        home = max(users, key=lambda s: sum(s in refs.get(n, ()) for n in members)) if users else "(no unit)"
        # A class claim locks the ledger's member files only; every unit pass1.log names as
        # referencing the group is part of the fix too, so it joins the footprint.
        claim = ([f"class:{key}"] if kind == "class" else []) + [f"file:{s}" for s in users]
        items.append({
            "tier": "stubs", "check": "stub", "class": key if kind == "class" else None,
            "function": f"{key} ({len(members)} stub(s))" if kind == "class" else key,
            "target_rva": "" if kind == "class" or users else pins[key],
            "source": home, "size": 0, "count": len(members), "stubs": members,
            "credit_note": f"{len(members)} of the link's {len(stubbed)} stubs",
            "why": (f"the link stubs {', '.join(members[:6])}{' ...' if len(members) > 6 else ''}; referenced from "
                    f"{len(users)} unit(s): define the body or data, or bind the reference to retail's real name"),
            "start": (f"python3 tools/class_views.py --class {key}" if kind == "class" else
                      f"python3 tools/pin_consistency.py --symbol {key}") + "; read docs/linking_obstacles.md first",
            "claim": claim if claim else [pins[key]],
            "pass_test": ("the next link cycle (tools/link_cycle.py, maintainer-run; read through its receipt) no "
                          "longer lists " + ("these symbols" if len(members) > 1 else "this symbol") + " in "
                          "stubs.json; locally, python3 tools/link_check.py " + (users[0] if users else "<unit>")
                          + " finds no unresolved reference to it"),
        })
    items.sort(key=lambda i: (-i["count"], i["function"]))
    return items, (f"{len(items)} stub group(s) over {len(stubbed)} stubbed symbol(s) from {out} (link cycle at "
                   f"commit {commit[:10]}{' +uncommitted edits' if receipt.get('dirty') else ''}, measured {age} "
                   f"UTC)" + (f"; {unclaimable} free symbol(s) with no referencing unit or pin not served"
                              if unclaimable else ""))


def consolidation_items():
    """(items, note): approved TUs a merge can shrink (tools/tu_skeleton.py --queue), one
    item per TU. The claim is the merge's own file footprint (the TU and every donor;
    tu_skeleton --merge adds the moved RVAs under the same owner). PASS TEST: the merge
    itself, which verifies every donor by compiling and byte-matching."""
    if not (ROOT / TU_MAP).exists():
        return [], f"{TU_MAP} absent: consolidation queue skipped"
    tools_on_path()
    import tu_skeleton
    import tu_views
    queue = tu_skeleton.queue(root=ROOT)
    items = []
    for entry in queue:
        tu = entry["tu"]
        don, _, _ = tu_skeleton.donors(tu, tu_skeleton.skeleton(tu))
        files = sorted(set(don) | {tu})
        # donors declaring their own views of one class are the usual rejection: share them first
        views = tu_views.shared_private(sorted(don), ROOT)
        first = (f"python3 tools/tu_views.py {tu} (its donors declare their own views of "
                 f"{', '.join(views[:3])}{', ...' if len(views) > 3 else ''}), then " if views else "")
        items.append({
            "tier": "consolidate", "check": "tu-merge", "function": tu, "source": tu, "target_rva": "",
            "size": 0, "count": entry["removes"],
            "credit_note": f"up to {entry['removes']} file(s) removed (an upper bound: the merge keeps only donors "
                           "that compile together)",
            "why": (f"merge up to {entry['removes']} donor file(s) ({entry['rows']} rows) into the approved TU; "
                    f"{entry['mixed']} mixed and {entry['refused']} refused file(s) stay; reconcile rejected donors "
                    "in their own commits first (docs/consolidation.md, \"Workflow per TU\")"),
            "start": (f"python3 tools/name_lane.py consolidate --under {posixpath.dirname(tu)}/, then "
                      f"{first}python3 tools/tu_skeleton.py --merge {tu} --dry-run"),
            "claim": [f"file:{f}" for f in files],
            "pass_test": (f"BFME_CLAIM_OWNER=<seat> python3 tools/tu_skeleton.py --merge {tu}, then ./build.sh {tu} "
                          f"and python3 tools/find_declared_unmatched.py {tu}: the donors are gone and every moved "
                          "row still byte-matches (docs/consolidation.md)"),
        })
    stale = " (tu_map.csv stale: queue from a map rebuilt in memory, never written)" if tu_skeleton._CACHE.get(
        "stale") else ""
    return items, f"{len(items)} approved TU(s) a merge can shrink, from tools/tu_skeleton.py --queue{stale}"


TU_BLOCKS = {
    "noncontiguous": "rows another anchored TU owns sit inside this TU's address span; identify the interleaved "
                     "rows (a wrong name, a COMDAT, a misplaced anchor) so the span is contiguous",
    "contradicted": "the row's own F/Z/S evidence names another TU; resolve which is right before any move",
    "unanchored": "only naming hints (N/K/U) route these rows; an F/Z/S anchor (a real name with a Zero Hour "
                  "definition or a __FILE__ string) is what approves them: name the placeholder rows",
    "brackets": "contiguity (C) between rows that are not approved themselves; approve the brackets first",
}


def tu_approval_items():
    """(items, note): TUs whose rows tu_map.csv only proposes, one item per TU, ranked by how
    many files their rows span (what a later merge could remove). tu_map is a pure function of
    its inputs and is never edited by hand, so a row becomes approved only through evidence:
    a real name (rename.py, name_evidence.py) giving an F/Z/S anchor, or a resolved
    interleaving or contradiction (docs/consolidation.md, "Evidence catalogue"). The item
    claims the TU scope `file:TU`; each rename takes its own file claims (tools/rename.py).
    PASS TEST: the map rebuilt from current inputs approves the rows
    (tools/tu_skeleton.py --plan TU lists them; never commit a regenerated map from this lane)."""
    if not (ROOT / TU_MAP).exists():
        return [], f"{TU_MAP} absent: TU-approval queue skipped"
    tools_on_path()
    import tu_skeleton
    by_tu = {}
    for row in tu_skeleton.map_rows():
        if row["confidence"] == "proposed" and row["kind"].startswith("code") and row["tu"]:
            by_tu.setdefault(row["tu"], []).append(row)
    items = []
    for tu, rows in by_tu.items():
        blocks = collections.Counter(
            "contradicted" if "contradicted" in row["evidence"] else
            "noncontiguous" if "noncontiguous" in row["evidence"] else
            "brackets" if row["by"] == "C" else "unanchored" for row in rows)
        files = {row["source"] for row in rows if row["source"] and (ROOT / row["source"]).exists()}
        main, count = blocks.most_common(1)[0]
        items.append({
            "tier": "tu-approval", "check": main, "function": tu, "source": tu,
            "target_rva": "", "size": 0, "count": len(files), "rows": len(rows),
            "credit_note": f"{len(rows)} proposed row(s) in {len(files)} file(s)",
            "why": (f"{len(rows)} proposed row(s) in {len(files)} file(s) ("
                    + ", ".join(f"{k} {n}" for k, n in blocks.most_common()) + f"): {TU_BLOCKS[main]}"),
            "start": (f"python3 tools/name_lane.py consolidate --under {posixpath.dirname(tu)}/ and read the TU's "
                      "packet; names through tools/name_evidence.py and tools/rename.py (docs/naming.md)"),
            "claim": [f"file:{tu}"],
            "pass_test": (f"python3 tools/tu_skeleton.py --plan {tu}: the rows are approved in the map rebuilt from "
                          "current inputs (tu_map.py; never commit a regenerated map from this lane)"),
        })
    items.sort(key=lambda i: (-i["count"], -i["rows"], i["function"]))
    stale = " (tu_map.csv stale: rebuilt in memory, never written)" if tu_skeleton._CACHE.get("stale") else ""
    return items, (f"{len(items)} TU(s) with {sum(i['rows'] for i in items)} proposed code row(s) from "
                   f"{TU_MAP}{stale}")


def tu_evidence_items():
    """(items, note): unmapped address runs holding sources no tu_map row places at all
    (tools/tu_evidence.py runs), largest first, one item per run (at most 16 sources). Each
    carries the retail-structural evidence tu_evidence re-derives for its rows (funclet
    order, vftable layout, initializer order, .rdata order, funclet parentage), the
    bracketing rows and the gap. A signal approves only once promoted past its precision
    gate; the seat's job is a re-checkable anchor (a real name with a Zero Hour definition
    or a __FILE__ string, often a mis-named row whose Z fails) or a missing bracket, never an
    asserted TU. The item claims its sources (`file:`). PASS TEST: the map rebuilt from
    current inputs gives the run's rows a TU (tools/tu_evidence.py --source SRC lists what
    reaches them; never commit a regenerated map from this lane). Also served: one `wb-path`
    lead per non-editor WorldBuilder source path the map has no TU for
    (tools/wb_source_paths.py triage_items), to investigate, never to approve or create a TU."""
    if not (ROOT / TU_MAP).exists():
        return [], f"{TU_MAP} absent: TU-evidence queue skipped"
    tools_on_path()
    import tu_evidence
    import tu_map
    import tu_skeleton
    out = tu_skeleton.map_rows()
    layout = tu_map.Layout(ROOT)
    st = tu_evidence.Structures(layout, out) if layout.image.is_file() else None
    runs, bare = tu_evidence.runs(out, st, exists=lambda s: (ROOT / s).exists())
    items = []
    for run in runs:
        lo, hi, srcs = run["lo"], run["hi"], run["sources"]
        ends = []
        for side, r in (("below", run["below"]), ("above", run["above"])):
            if r:
                ends.append(f"{side} {r['rva']} {r['tu']} ({r['confidence']} by {r['by']})")
        sig = "; ".join(f"{s} " + ", ".join(f"{tu} x{n}" for tu, n in c.most_common(3))
                        + (" (gated)" if s in tu_evidence.PROMOTED else " (proposal)")
                        for s, c in sorted(run["signals"].items()))
        items.append({
            "tier": "tu-evidence", "check": "signal" if run["signals"] else "no-signal",
            "function": f"0x{lo:08X}..0x{hi:08X}", "source": srcs[0], "target_rva": f"0x{lo:08X}",
            "size": 0, "count": len(srcs), "rows": run["rows"], "sources": srcs,
            "credit_note": f"{len(srcs)} source(s) with no TU evidence, {run['rows']} row(s)",
            "why": (f"{run['rows']} row(s) in {len(srcs)} source(s) no tu_map signal places; "
                    + ("; ".join(ends) or "no assigned row on either side")
                    + (f", 0x{run['gap']:X} bytes apart" if run["gap"] is not None else "")
                    + (f". Retail layout evidence: {sig}" if sig else ". No retail layout signal reaches them")
                    + ". Find a re-checkable anchor (a real name with a Zero Hour definition or a __FILE__ "
                      "string; often a mis-named row whose Z fails) or a missing bracket; never assert a TU"),
            "start": (f"python3 tools/tu_evidence.py --source {srcs[0]}; python3 tools/name_lane.py consolidate "
                      f"--under {posixpath.dirname(srcs[0])}/; names through tools/name_evidence.py and "
                      "tools/rename.py (docs/naming.md)"),
            "claim": [f"file:{s}" for s in srcs],
            "pass_test": ("the map rebuilt from current inputs gives the run's rows a TU: python3 tools/tu_map.py "
                          "--dir <source> or tools/tu_skeleton.py --plan <tu> (never commit a regenerated map from "
                          "this lane)"),
        })
    stale = " (tu_map.csv stale: rebuilt in memory, never written)" if tu_skeleton._CACHE.get("stale") else ""
    image = "" if st is not None else "; no retail image, so no layout evidence"
    served = len({src for i in items for src in i["sources"]})
    note = (f"{len(items)} unmapped run(s) holding {served} of {bare} source(s) with "
            f"no TU evidence, from {TU_MAP}{stale}{image}")
    # WorldBuilder path leads (tools/wb_source_paths.py): investigate-only, never an approval.
    import wb_source_paths
    leads, lead_note = wb_source_paths.triage_items(out, root=ROOT)
    return items + leads, f"{note}; {lead_note}"


def ms_header_queue_items():
    """(items, note): reverse/ms_header_queue.tsv as a picker queue (ms_header_items)."""
    if not (ROOT / MS_HEADER_QUEUE).exists():
        return [], f"{MS_HEADER_QUEUE} absent: Microsoft-header queue skipped"
    items = ms_header_items()
    for item in items:
        row = item["audit"]
        item.update(start=(f"in {row['file']} only: include {row['headers']} and delete the local "
                           f"definition(s) of {row['names']}; ./build.sh {row['file']}"),
                    check=item["classification"], count=int(row["defs"] or 0),
                    credit_note=f"{row['defs']} local definition(s) of Microsoft-header names",
                    why=(f"{item['classification']}: defines {row['defs']} name(s) of {row['headers']} locally; "
                         "include the real header and delete the copy"
                         + ("; CRT dllimport conflicts need per-body callee checks"
                            if item["classification"] == "conflicting" else "")))
    return items, f"{len(items)} file(s) from {MS_HEADER_QUEUE} (repair_queue.py ms-headers)"


def dx_items():
    """(items, note): units to move off the reference/shims DirectX stand-ins onto the SDK
    headers (tools/dx_migration.py servable(), what next_work.py --tier dx serves)."""
    if not (ROOT / DX_QUEUE).exists():
        return [], f"{DX_QUEUE} absent: DirectX migration queue skipped"
    tools_on_path()
    import dx_migration
    items = [{"tier": "dx", "check": r["class"], "function": r["source"], "source": r["source"], "target_rva": "",
              "size": 0, "count": int(r["matched_rows"] or 0), "claim": ["file:" + r["source"]],
              "credit_note": f"{r['matched_rows']} matched row(s) in the unit",
              "start": (f"in {r['source']} only: replace the reference/shims DirectX stand-in includes with the "
                        "SDK headers, marked // dxsdk" + (f" ({r['edits']})" if r.get("edits") else "")
                        + f"; ./build.sh {r['source']}"),
              "why": f"[{r['class']}] move the unit to the SDK headers (// dxsdk)"
                     + (f"; edits: {r['edits']}" if r.get("edits") else ""),
              "pass_test": f"./build.sh {r['source']}, then python3 tools/dx_migration.py scan {r['source']}"}
             for r in dx_migration.servable() if (ROOT / r["source"]).exists()]
    return items, f"{len(items)} unit(s) from {DX_QUEUE}"


def stlport_move(source, knobs, renames):
    """The lane's move for one file (docs/matching.md, "Cleanup lane details": STLport):
    opt in, byte-verify the whole file, repoint every row. `adapt` is always applied (4.6
    refuses 4.5.3's const allocator declarations); the other knobs only when the marker
    alone fails, because the trial ran 4.6 under the unit's 4.5.3 overlay copies and the
    opt-in swaps each overlay /I for its 4.6 port (vendor/stlport-4.6-bfme), which may
    already match."""
    tools_on_path()
    import stlport_trial
    try:
        text = (ROOT / source).read_text(encoding="utf-8", errors="replace")
    except OSError:
        text = ""
    flags = " ".join(line for line in text.splitlines() if line.startswith("// cl:"))
    overlays = [o for o in stlport_trial.STL_OVERLAYS if "/I" + o in flags or "-I" + o in flags]
    steps, fallback = [f"in {source} only: change its `// stlport` line to `// stlport46`"], []
    for knob in sorted({part for knob in knobs for part in knob.split("+")}):
        if knob == "adapt":
            steps.append("drop the 4.5.3-only `const` from its allocator<T>::allocate/deallocate/construct/"
                         "destroy declarations (4.6's are non-const)")
        elif knob == "-shim":
            fallback.append("delete " + (" ".join("/I" + o for o in overlays) or "its reference/shims STLport overlay /I")
                            + " from its `// cl:` line")
        else:
            fallback.append(f"add /D{knob.removeprefix('-D')} to its `// cl:` line")
    if renames:
        steps.append(f"rename {', '.join(renames)} to the non-const 4.6 mangling (QBE->QAE, "
                     "stlport_trial.const_twin) with tools/rename.py (docs/naming.md)")
    steps.append(f"./build.sh {source} (every row in the file, not only the trial's)")
    if fallback:
        steps.append("only if that fails, apply the trial's knob and rebuild: " + " and ".join(fallback))
    steps.append(f"repoint each matched row of the file: python3 tools/add_match.py <name> <rva> <size> {source} "
                 "--replace-existing --notes \"<its notes>; migrated=stlport-4.6\"")
    return "; ".join(steps)


def stlport_items():
    """(items, note): whole files to move onto STLport 4.6, what next_work.py --tier
    stlport serves: stlport_trial.queue_files (repair_queue.py stlport), the trial's
    leads the ledger still holds in files not yet opted in. The trial is a lead; the
    pass test is ./build.sh of the whole file under `// stlport46`."""
    if not (ROOT / STLPORT_TRIAL).exists():
        return [], f"{STLPORT_TRIAL} absent: STLport 4.6 queue skipped"
    tools_on_path()
    import stlport_trial
    items = []
    for entry in stlport_trial.queue_files():
        source, rows = entry["source"], entry["rows"]
        if not (ROOT / source).is_file():
            continue
        renames = [r["name"] for r in rows if stlport_trial.ALLOCATOR_MEMBER.match(r["name"])]
        check = ("unit trial" if entry["lead"] == "unit" else "library lead") + (
            " +" + ",".join(entry["knobs"]) if entry["knobs"] else "")
        items.append({
            "tier": "stlport", "check": check, "function": source, "source": source, "target_rva": "",
            "size": 0, "count": len(rows), "lead": entry["lead"], "knobs": entry["knobs"],
            "trial_fails": entry["fails"], "claim": ["file:" + source],
            "credit_note": f"{len(rows)} trial row(s), {entry['bytes']:,} B moved onto STLport 4.6",
            "start": stlport_move(source, entry["knobs"], renames),
            "why": (f"[{check}] {len(rows)} row(s) ({entry['bytes']:,} B) of this unit matched retail under "
                    "STLport 4.6 in the trial; retail linked 4.6 and the unit still compiles against 4.5.3"
                    + ("" if entry["lead"] == "unit" else
                       "; library lead: pristine 4.6 src/ reproduced them, the unit itself was never compiled "
                       "under 4.6")
                    + (f"; {entry['fails']} other row(s) of the file failed the trial: fix them in the same "
                       "move or revert it" if entry["fails"] else "")),
            "pass_test": (f"./build.sh {source} with `// stlport46` and every row repointed "
                          "(migrated=stlport-4.6); repair_queue.py stlport no longer serves it"),
            "bytes": entry["bytes"]})
    # Units the trial compiled itself and saw no row of fail first, then by bytes.
    items.sort(key=lambda i: (i["lead"] != "unit" or bool(i["trial_fails"]), -i["bytes"]))
    rows = sum(i["count"] for i in items)
    return items, (f"{len(items)} file(s), {rows} trial row(s) from {STLPORT_TRIAL} "
                   "(repair_queue.py stlport)")


# {tier: (input file, builder)}: tools/next_work.py serves them in this order.
DEBT_QUEUES = {"data": (DATA_BASELINE, data_identity_items), "header": (HEADER_QUEUE, header_items),
               "identity": (IDENTITY_BASELINE, identity_items)}
# The Phase 2 structural queues, served by the same picker; their builders skip themselves
# with a note when an input is absent.
STRUCTURAL_QUEUES = {"stubs": stub_items, "consolidate": consolidation_items, "tu-approval": tu_approval_items,
                     "tu-evidence": tu_evidence_items,
                     "ms-headers": ms_header_queue_items, "dx": dx_items, "stlport": stlport_items}


# ---------------------------------------------------------------- destination

@lru_cache(maxsize=1)
def file_evidence():
    out = {}
    for row in csv.DictReader(io.StringIO(_read(EVIDENCE))):
        if row.get("kind") == "file":
            out.setdefault(int(row["rva"], 16), []).append((row["route"], row["value"]))
    return out


@lru_cache(maxsize=1)
def tu_routes():
    """tools/tu_map.py's map and its tu_at index (with the retail image for boundary
    evidence); imported here, not at the top, because the hooks run this file through
    stdin (verify-removed) without tools/ on the path."""
    sys.path.insert(0, str(Path(_SCRIPT).resolve().parent if _HAS_SCRIPT else ROOT / "tools"))
    import tu_map
    m = tu_map.load(ROOT)
    return tu_map, m, tu_map.code_index(m, tu_map.Image.open(tu_map.Layout(ROOT).image))


def dest_tu(rva):
    """{"dest": path or None, "basis": why} for a new row at RVA."""
    for route, value in sorted(file_evidence().get(rva, ()),
                               key=lambda rv: FILE_ROUTES.index(rv[0]) if rv[0] in FILE_ROUTES else 99):
        path = SOURCE_PREFIX + value.lstrip("/")
        if (ROOT / path).exists():
            return {"dest": path, "basis": f"EA source-file evidence ({route})"}
    tu_map, m, index = tu_routes()
    t = tu_map.tu_at(m, rva, index)
    own = tu_map.anchors(t["evidence"]) if t else {}
    # What tu_ownership A2/A3 hold a row to (the same predicate): an approved TU no F/Z/S
    # anchor of the address, or of the rows its C evidence rests on, disputes. A map built
    # before contradicted approvals were demoted can still carry one, and then a merged
    # cluster's file is not created over the file retail's own __FILE__ string names.
    tu = tu_map.approved_tu(m, t)
    if tu:
        made = "" if (ROOT / tu).exists() else "; the file does not exist yet: create it"
        return {"dest": tu, "basis": f"approved TU in tu_map.csv (by {t['by']}{made})"}
    dispute = tu_map.disputed(m, t) if t and t["confidence"] == "approved" else None
    state = "no TU" if not t else (t["confidence"] or "no TU") + (f" {t['tu']}" if t["tu"] else "")
    if dispute:
        state += f", contradicted by {dispute}"
    if t and t["kind"] == "code-interior":
        state += f", {t['evidence'].split()[0]} {t['evidence'].split()[1]}"   # inside 0x... (a known body)
    if own.get("F") and (ROOT / own["F"]).exists():
        return {"dest": own["F"], "basis": f"retail __FILE__ string at this address (F in tu_map.csv; "
                                           f"tu_map: {state})"}
    if not t and index.host(rva) is None and index.gap(rva) == "padding":
        return {"dest": None, "basis": "retail padding (0xCC) inside no known body: no function starts here"}
    got = neighbour_dest(rva)
    got["basis"] = f"neighbour heuristic, no usable approved TU (tu_map: {state}): " + got["basis"]
    return got


def neighbour_dest(rva):
    """The pre-tu_map rule: the unit both neighbouring ledger rows come from, else the
    nearest neighbour's within DEST_WINDOW."""
    _, homes = ledger()
    starts = [h[0] for h in homes]
    i = bisect.bisect_left(starts, rva)
    prev = homes[i - 1] if i > 0 else None
    nxt = homes[i] if i < len(homes) and homes[i][0] != rva else (homes[i + 1] if i + 1 < len(homes) else None)
    if prev and nxt and prev[2] == nxt[2] and nxt[0] - (prev[0] + prev[1]) <= DEST_WINDOW:
        return {"dest": prev[2], "basis": f"between two rows of this unit (0x{prev[0]:08X}, 0x{nxt[0]:08X})"}
    near = []
    if prev and rva - (prev[0] + prev[1]) <= DEST_WINDOW:
        near.append((rva - (prev[0] + prev[1]), prev))
    if nxt and nxt[0] - rva <= DEST_WINDOW:
        near.append((nxt[0] - rva, nxt))
    if near:
        gap, home = min(near)
        return {"dest": home[2], "basis": f"nearest neighbour row 0x{home[0]:08X}, {gap} bytes away"}
    return {"dest": None, "basis": f"no neighbouring unit within 0x{DEST_WINDOW:X} bytes; put it in its "
                                   "class's file, never a new one-function file"}


def annotate_dest(candidates):
    """Add dest/dest_basis to queue candidates (new matches)."""
    for candidate in candidates:
        rva = candidate.get("target_rva") or candidate.get("candidate_rva")
        try:
            got = dest_tu(int(rva, 16))
        except (TypeError, ValueError):
            continue
        candidate["dest"], candidate["dest_basis"] = got["dest"], got["basis"]
    return candidates


def ms_header_items(cls=None):
    """Audit-ranked file work; classification is not a C++ class lock."""
    tools_on_path()
    import ms_header_audit
    rows = ms_header_audit.read_queue(ROOT / "reverse/ms_header_queue.tsv")
    rows = [row for row in rows if cls in (None, row["class"])
            and (ROOT / row["file"]).is_file()]
    rows.sort(key=lambda row: (ms_header_audit.CLASS_ORDER[row["class"]], -int(row["defs"]), row["file"]))
    return [{"tier": "ms-headers", "source": row["file"], "function": row["file"],
             "target_rva": "", "size": 0, "claim": ["file:" + row["file"]],
             "classification": row["class"], "audit": row,
             "pass_test": "./build.sh " + row["file"]} for row in rows]


def serve_ms_headers(args):
    """Use the shared picker's symmetric locks and atomic acquisition, not raw refs."""
    import next_work
    if args.claim:
        next_work.claims.settle(defer=True)    # rides on the claim push
    items = next_work.without_busy(ms_header_items(args.cls), next_work.busy_keys())
    limit = args.limit if args.limit is not None else (1 if args.claim else 20)
    print(f"{len(items)} available file(s) define Microsoft-header names locally; "
          "include the real header, delete the copy, prove with ./build.sh: byte gate is the authority. "
          "CRT dllimport conflicts need per-body callee checks")
    shown = 0
    for item in items:
        if shown >= max(0, limit):
            break
        acquired = []
        if args.claim:
            picked, acquired = next_work.claim_choice([item], "ms-headers")
            if picked is None:
                continue
        row = item["audit"]
        print(f"  {row['class']:<17} {row['defs']:>4} defs  {row['file']}")
        if args.claim:
            print("         " + ("claim held: " + " ".join(item["claim"]) if acquired
                                  else "UNCLAIMED: origin unavailable"))
        print(f"         {row['headers']}{'  (needs // platformsdk)' if row['platformsdk'] == 'yes' else ''}: "
              f"{row['names'][:160]}")
        if row.get("closure"):
            print(f"         via includes: {row['closure'][:160]}")
        if row.get("note"):
            print(f"         NOTE: {row['note']}")
        print(f"         pass test: {item['pass_test']}")
        shown += 1
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("repair", "link", "data", "header", "identity"):
        p = sub.add_parser(name)
        p.add_argument("--limit", type=int, default=20)
        if name == "link":
            p.add_argument("--bundle", metavar="DIR",
                           help="a link-cycle bundle (tools/cycle_artifacts.py fetch): its rows, validated, with "
                                "their freshness; no census fallback")
            p.add_argument("--allow-stale", action="store_true",
                           help="with --bundle: serve a bundle measured over 24 h ago, labelled STALE")
            p.add_argument("--closure", action="store_true",
                           help="with --bundle: closure roots ranked by conditional single-address gain")
            p.add_argument("--local-unpublished", action="store_true",
                           help="with --bundle DIR: a locally built bundle with no fetch evidence, labelled "
                                "UNAUTHENTICATED (a producer inspecting its own bundle; never for shared work)")
    sub.add_parser("dest").add_argument("rva")
    sub.add_parser("pass-test").add_argument("line")
    verify_parser = sub.add_parser("verify-removed", help="hook: re-verify rows whose debt lines the index deletes")
    verify_parser.add_argument("--defer-missing", action="store_true",
                               help="pre-commit: commit-msg will check disappearing sources with the actual message")
    verify_parser.add_argument("--range", nargs=2, metavar=("BASE", "REV"))
    missing_parser = sub.add_parser("verify-missing", help="commit-msg: account for disappearing sources")
    missing_parser.add_argument("message_file", nargs="?")
    missing_parser.add_argument("--range", nargs=2, metavar=("BASE", "REV"))
    p = sub.add_parser("retired", help="list committed Debt-Retired trailers with their commit IDs")
    p.add_argument("--limit", type=int, default=20, help="maximum commits with retirement trailers")
    p = sub.add_parser("retire", help="delete the SOURCE keys the owning tool no longer finds (fail closed)")
    p.add_argument("kind", choices=sorted(REGISTERS))
    p.add_argument("source")
    p = sub.add_parser("ms-headers", help="explicit Microsoft-header migration lane (file locks)")
    p.add_argument("--limit", type=int, help="files to serve (default: 20, or 1 with --claim)")
    p.add_argument("--claim", action="store_true", help="atomically claim each selected file and its locks")
    p.add_argument("--class", dest="cls", type=lambda v: "drop-in candidate" if v in ("drop-in", "drop-in-candidate") else v,
                   choices=("drop-in candidate", "adapt", "unverified", "conflicting", "shim", "failed"))
    p = sub.add_parser("stlport", help="STLport 4.6 full-file migration leads (fresh build required)")
    p.add_argument("--tsv", action="store_true")
    args = ap.parse_args(argv)
    if args.cmd == "stlport":
        import stlport_trial
        stlport_trial.queue(args)
        return 0
    if args.cmd == "ms-headers":
        return serve_ms_headers(args)
    if args.cmd == "retired":
        got = _git("log", "--format=%h%x00%(trailers:key=Debt-Retired,only)%x00",
                   "--grep=^Debt-Retired:")
        if got.returncode:
            print("repair_queue: cannot read retirement history", file=sys.stderr)
            return 1
        records = got.stdout.split("\0")
        shown = 0
        for sha, trailers in zip(records[::2], records[1::2]):
            if trailers.strip() and shown < max(0, args.limit):
                for line in trailers.splitlines():
                    if line.strip():
                        print(f"{sha.strip()} {line.strip()}")
                shown += 1
        return 0
    if args.cmd in ("verify-removed", "verify-missing") and args.range:
        failures = verify_debt_range(*args.range, missing=args.cmd == "verify-missing")
        for line in failures:
            print(f"repair_queue: {line}", file=sys.stderr)
        return 1 if failures else 0
    if args.cmd == "verify-missing":
        if not args.message_file:
            ap.error("verify-missing needs a message file or --range BASE REV")
        failures = verify_missing_debt(Path(args.message_file).read_text(encoding="utf-8"))
        for line in failures:
            print(f"repair_queue: {line}", file=sys.stderr)
        return 1 if failures else 0
    if args.cmd == "verify-removed":
        failures = verify_removed() + (verify_removed_debt(defer_missing=True) if args.defer_missing
                                       else verify_removed_debt())
        for line in failures:
            print(f"repair_queue: {line}", file=sys.stderr)
        return 1 if failures else 0
    if args.cmd == "dest":
        got = dest_tu(int(args.rva, 16))
        print(f"{got['dest'] or '(no unit)'}  <- {got['basis']}")
        return 0
    if args.cmd == "retire":
        ok, message = retire(args.kind, args.source.replace("\\", "/"))
        print(message)
        return 0 if ok else 1
    if args.cmd == "pass-test":
        ok, message = pass_test(args.line)
        print(message)
        return 0 if ok else 1
    if getattr(args, "bundle", None):
        if BFME1:
            print("repair_queue: BFME1 has no link cycle yet", file=sys.stderr)
            return 1
        ca = cycle_artifacts()
        try:
            if args.closure:
                items, notes, warnings = closure_items(args.bundle, allow_stale=args.allow_stale,
                                                       local_unpublished=args.local_unpublished)
                note = "\n".join(notes)
            else:
                items, note, warnings = bundle_link_items(args.bundle, allow_stale=args.allow_stale,
                                                          local_unpublished=args.local_unpublished)
        except ca.Problem as e:                              # a reason, never a fallback
            print(f"repair_queue: link-cycle bundle {ca.describe(e)}", file=sys.stderr)
            return ca.exit_code(e)
        for line in warnings:
            print(f"repair_queue: {line}", file=sys.stderr)
    elif any(getattr(args, flag, False) for flag in ("closure", "allow_stale", "local_unpublished")):
        print("repair_queue: --closure, --allow-stale and --local-unpublished need --bundle STORE "
              "(tools/cycle_artifacts.py fetch): the closure roots exist only in a published bundle; nothing else "
              "is served in their place", file=sys.stderr)
        return 1
    elif args.cmd in DEBT_QUEUES:
        items, note = DEBT_QUEUES[args.cmd][1]()
    else:
        items, note = (all_repair_items(), f"{len(parse_debt())} baseline line(s), plus tier C / diffexec / boot, game and static queues") if args.cmd == "repair" else link_items()
        if args.cmd == "link" and not BFME1 and link_source()[0] is None:
            print(f"repair_queue: {note}", file=sys.stderr)     # an empty queue would read as "nothing to fix"
            return 1
    print(note)
    for item in items[:args.limit]:
        print(f"  {item['size']:>6}B {item.get('check', '')} {item['target_rva'] or item.get('address', '')} "
              f"{item['function'][:80]}" + (f"  [claims {' '.join(item['claim'])}]" if item.get("claim") else ""))
        print(f"         {item['source']}: {item['why'][:400 if item.get('tier') == 'closure' else 160]}")
        print(f"         pass test: {item['pass_test']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
