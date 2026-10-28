## Instruction freshness

Before continuing work, reread `AGENTS.md` if 24 hours have elapsed
since the last read. Reread it immediately whenever a user message
or commit message reports an edit to `AGENTS.md`.

## Current phase: link and clean up

Byte matching of BFME 2's `.text` is complete (`python3 tools/progress.py`:
BYTE-MATCHED 100%). The open work is making matched units link, retiring debt,
replacing placeholder and generated rows with real C++ and real names, and
consolidating files. Investigate an apparent unrowed body against current
coverage, existing owners and history before calling it a regression. Restoring
a lost row is regression repair; identifying an existing placeholder is cleanup.

**Exit test** (`docs/verifier_upgrade_plan.md` step 12): the game links with no
`/FORCE` and no stubs at a non-retail base, and automated runs
(`tools/boot_smoke.py`, `tools/game_smoke.py`) reach the menu, a skirmish and
save/load. The phase closes with source recovery done too: `Code/` holds retail's
translation units, not one file per function, and every code row sits in its
approved TU (`reverse/tu_map.csv`).

**Headline figures:**

- **Linking**: the census's LINKED and LINKING, printed by `tools/progress.py`
  from `reverse/link_census_history.csv`. Only census figures count;
  `tools/link_check.py` only predicts.
- **Image ownership**: NOT OURS (`tools/image_ownership.py report`), driven to
  zero. Only the nightly workflow (`.github/workflows/nightly-measure.yml`)
  records it.
- **Source recovery**: SOURCE FILES (`.cpp`/`.c`/`.asm` under `Code/`, driven
  down from ~22,500 toward the ~2,000 TUs `reverse/tu_map.csv` names) and
  TU-APPROVED (code rows in an approved TU, which caps what merges can remove),
  printed by `tools/progress.py`. Merges (`tools/tu_skeleton.py --queue`) lower
  the first; TU-approval and TU-evidence work raises the second.
- **Debt**: `reverse/gate_baseline.txt`, the data, code-identity and header
  registers, and the hatch counts in `reverse/hatch_baseline.tsv`.

Progress is `matched` rows in `reverse/functions.csv` backed by real source and
byte verification; units the census records as linked; debt retired along its
register's path; source files merged into their approved TUs and rows approved;
and NOT OURS falling, shown only by ownership receipts that `image_ownership.py
record` accepts into `reverse/image_ownership_history.csv` (none yet), with
matched and linked coverage kept. Markers and prose are not
progress.

## Hard rules

Several agents push to `origin/master` continuously. Keep each change small,
verified and easy to rebase. Detail for the hook rules:
`docs/verifier_upgrade_plan.md` ("Live rules in detail").

### Verification and hooks

- Never `--no-verify`; never bypass a hook. If `git config core.hooksPath` names
  another checkout (common in worktrees), run `git -c core.hooksPath=.githooks`.
- Create worktrees with `python3 tools/worktree_setup.py create PATH --branch
  NAME`; never run a bare `submodule update --init` in a worktree. After
  pulling in a worktree, run `worktree_setup.py prepare`; remove one with
  `worktree_setup.py remove PATH`.
- A commit that edits `tools/` gate code, `.githooks/` or a baseline/whitelist
  needs a `Verifier-Change: <reason>` trailer.
- Spell control paths (the root, `reverse/`, `tools/`, `.githooks/`, `.github/`)
  in lowercase (`tools/check_case_collisions.py`; banked attempts, attempt
  evidence and class contracts are exempt).
- `.c` and `.asm` sources are byte-verified like `.cpp`. The hooks refuse a string
  literal shorter than retail's, a switch jump table mapping a case to the wrong
  target, and compiled bytes past a row's extent that differ from retail (for a
  longer body, raise the extent).
- Never add a line to `reverse/gate_baseline.txt`; delete a line when you fix its
  row.
- Retire debt only by its register's path: gate baseline, delete the line with
  the fix (`repair_queue.py pass-test "<line>"`, no trailer); data and identity,
  `repair_queue.py retire data|identity SOURCE`; header queue, the row's
  `header_adopt_lane.py accept`. A key whose source vanished: transfer it, cover
  the old source's rows in `reverse/deleted_rows.csv`, or rarely a per-key
  `Debt-Retired: <key> <source> <reason>` trailer (reason ≥20 characters; only
  for that case). `Verifier-Change` never retires a key.
- Code identity, `tools/tu_ownership.py`, `tools/invented_names.py`, link
  admission and `data_check.py` outside `--converged` report in shadow; read
  `reverse/code_identity_baseline.tsv`'s mode line. Once it says `enforce`,
  findings outside the registers are refused and it never returns to shadow.
- A full-gate hook run (header, vendored-reference and shared-shim edits,
  resolved merges): poll it, never relaunch it, never pipe a gate through
  anything that hides its exit code. Poll any build that returns a process or
  session ID; never launch a duplicate.
- Never compile by hand through `tools/build.py` (`build.compile_source`): it
  poisons the shared `build/match/` cache. If you did, delete that `.obj` **and**
  its `.deps.json` (`docs/matching.md`, "The build cache trap").
- If a check refuses work you can show is correct, do not work around it or edit
  the check in the same commit: record a false reject (Lanes).

### Names, pins, hatches, data

- Never add an escape hatch by hand (pins, `/alternatename`, `object-symbol=`
  rows, address-named globals, selectany, `class-gate: allow`,
  `present-unmatched`, `#pragma optimize`, `__emit`, `.asm` `db`;
  `reverse/hatch_baseline.tsv` is enforced). A count rises only through a tool
  admission (`tools/pin_admission.py --add`, `tools/add_match.py --pin`,
  `tools/name_globals.py`, `tools/gen_small.py land`) or a total-keeping move
  (`tools/hatch_counters.py --update`). Running `--allow` or `--admit` yourself
  is hand-adding. Prefer removing hatches; remove a file's hatches before
  renaming it.
- Write pins only through `tools/pin_admission.py --add` or
  `tools/add_match.py --pin`.
- A pin must be an in-image code RVA and never a second real name on a named
  address (rename the owner). An ICF fold needs `fold-proof=<ledger source>`.
  Run `tools/pin_consistency.py --symbol <name>` before pinning and `--check`
  after; `reverse/pin_consistency_baseline.csv` only shrinks. Check a harvested
  pin's thunk against the ledger's own body before spending a name on it.
- `gen-alias` only as an exact notes token whose masked callee is a
  byte-and-relocation twin; no new `object-symbol=` alias rows.
- One global per address in `reverse/data_converged.csv`. Declare the real
  global (`class AI; extern AI *TheAI;`) and cast to your view
  (`((AIView *)TheAI)->m_field`); never bind a second symbol (`g_00DFE78C`,
  `extern AIView *TheAI`). The list only grows.
- Never add a private copy of a class registered in
  `reverse/canonical_classes.csv` (`tools/class_gate.py`).
- Move rows only into the address's approved unit in the current TU map,
  including `tu_skeleton.py --merge` and `rehome_rows.py` moves. The committed
  `reverse/tu_map.csv` must be fresh; `tu_skeleton.py` can instead rebuild it
  in memory from current inputs. Never treat a stale assignment or a fallback
  from `repair_queue.py dest 0xRVA` as approval. Do not commit a regenerated
  map from the consolidation lane.
- Read `docs/naming.md` before renaming anything.

### Source and ledger integrity

- Anti-lift: write clean C++; MASM or inline asm only for a proven codegen
  blocker (compiler machinery, x87 shape, SEH). Lifting a dump into a
  `__declspec(naked)`/`__emit` .cpp is not a conversion and scores +0;
  `tools/conversion_gate.py` refuses it in both hooks, across your whole
  outgoing range.
- Never edit a file under `Code/gen_asm/`: repoint the row and leave the orphaned
  `PROC`. `Code/gen_small/uw_gen_*.cpp` is owned by `tools/gen_uw.py land`: never
  hand-edit it, never infer a funclet's `parent=` from adjacency.
- `gen-*` rows are placeholders, not progress. Recover by writing clean C++ at
  the proper `Code/` path and repointing: `tools/add_match.py <real-name> <rva>
  <size> <source> --replace-rva <rva>` (`--replace-existing` when the name is
  unchanged). After a batch, check one body per address: a duplicate range is an
  over-claim, not an ICF alias.
- `vendored=<lib>-<ver>` rows carry upstream's real names, never `gen-`; the
  header comment names the exact release; sources live at official BFME paths,
  and pristine C TUs compile against `reference/shims/gamespy/`, never a real
  Platform SDK.
- No fallback paths; they conceal mismatches.
- Record a census rule change only through `tools/census_rebaseline.py`.
- Never leave a nonmatching reconstruction in `Code/`. Banked attempts
  (`reverse/attempts/<rva>.cpp`) are evidence, never progress.
- Never hand-edit `reverse/re_attempts.log`; record with `tools/re_log.py` and
  stage the log with your row.
- Before planning an edit, run `python3 tools/find_declared_unmatched.py
  <file>`. Remedy a frozen file by rowing the body or, only for code retail
  dead-stripped, an honest `// ?<Class::method> absent-from-retail` marker.
  Never hand-add `present-unmatched`: it is a counted hatch and the enforced
  gate refuses its unadmitted growth. Remove stale markers first; re-run the
  check after any change and revert your file attempt if it still refuses
  (`docs/matching.md`, "Frozen files").
  `reverse/unclaimed_sources_whitelist.txt` is no remedy and only shrinks.
- Stage explicit paths only (`git add <paths>`, never `git add .`); check every
  new ledger source is tracked. Preserve unrelated dirty-tree work; revert only
  your own attempt.
- Never load `reverse/functions.csv`, `ghidra_functions.csv` or `exports.csv`
  wholesale; use `rg` or narrow filters.
- Game source under `Code/`, MASM dumps in `Code/masm_dumps/`, scratch untracked
  under `build/`. A new file under `tools/` replaces a tool or is called by a
  hook, a picker or another tool. Prefer TU-scoped shims over shared-header
  edits.
- Provenance: keep target facts, donor facts and structural inferences apart in
  evidence. Exact bytes, a placement or a same-name hit do not prove a donor name,
  layout or recovery. Never claim an external donor path as BFME 2 source.

### Claims (`docs/claims.md`)

- Claim before starting work: `python3 tools/claims.py claim 0xRVA` (every RVA
  in a batch), a picker's `--claim`, or `class:NAME` / `file:PATH` for scope-wide
  work. If another worker holds it, choose other work. The one exception: when
  origin is unreachable a picker serves work unclaimed; proceed, but never
  touch work origin last showed another worker holding.
- Claims expire after four hours: renew with `claims.py renew 0xRVA` when work
  runs longer. If `renew` reports a claim not renewed, stop editing that work;
  reclaim it or switch.
- Release a banked, blocked or abandoned body with `claims.py release 0xRVA`, and
  scope claims by hand after the push; landed rows settle themselves
  (`claims.py release --landed`).
- An orchestrator sets a stable, distinct `BFME_CLAIM_OWNER` per seat and one
  claim namespace per fleet.

### Publication

- Push direct to `master`: `git pull --rebase origin master`, `git push`, then
  pull --rebase again; on rejection rebase and retry.
- Never land a pull request with GitHub's merge button: it publishes rows nothing
  verified. Cherry-pick the commits onto master, `./build.sh` their rows, push,
  then comment on the PR with the landed SHAs and that follow-up work stacks off
  `master`.
- Push TU merges, splits and other source-path moves as soon as they verify
  and the account's push clock allows: a held move keeps its scope claimed and
  conflicts with every later move (2026-10-28: the last commit of a push
  waited a median 12 minutes and a p90 of 189 minutes before landing). Batch
  other verified commits until the batch moves a headline figure (linked bytes
  up, NOT OURS down, debt down, source files down), and batch linking repairs,
  renames and banked attempts the same way. Keep substantive changes in
  separate commits. Publish a smaller final batch when the work or session
  ends, even if no headline figure moved.
- Allow at least five minutes between successful pushes by the same GitHub
  account to this repository; share that clock across workers using the
  account, and keep working during the cooldown.
- If the outgoing batch changes source paths, audit active tooling and other
  path consumers once across the entire batch immediately before pushing.
  Update affected consumers and verify them together; repeat only if relevant
  moves or consumers change. Core ledger repointing still accompanies each
  applied move. Checklist: `docs/consolidation.md` ("Tooling compatibility audit
  before pushing").
- The pre-push hook runs `tools/link_batch_audit.py` once for the outgoing
  batch, including ledger/pin identity edits, removed providers and changed
  class declarations. It checks affected consumers and refuses proven losses
  of previously linking units, even when changed bodies byte-match. Read its
  report; inconclusive means unverified, not clean. Carry those cases into the
  next census and record link obstacles in `docs/linking_obstacles.md`.
- Never start, re-run or approve `tools/nightly_measure.py`, the nightly
  workflow (`.github/workflows/nightly-measure.yml`, `docs/nightly_actions.md`)
  or `tools/audit/run_nightly.cmd` (the maintainer's scheduled tasks). Ask a
  maintainer before a direct `tools/link_cycle.py` run, `tools/boot_smoke.py` or
  the shadow publisher. Use `python3 tools/link_check.py --fetch-index` and the census
  history instead.
- BFME 1 freshness: before BFME 2 work, when `build/bfme1-last-check.txt` is
  missing or over 72 hours old, check `reference/open-bfme-1` against official
  upstream and follow `docs/matching.md` ("BFME 1 reference updates"); never
  record success before verification.

## Work loop

### Select

An explicit request or assigned lane overrides the queue.

For any linking work, including work served by the default picker, read
`docs/linking_obstacles.md` before choosing a target. Update the relevant entries
with completed work, newly encountered obstacles and remaining prerequisites in
the repair or attempt-handoff commit, and before ending a linking pass. Mark a
cleared obstacle with verification evidence and its scope; retain its history.
Maintenance and measurement rules: `docs/linking.md` ("Shared obstacle register").

0. `git pull --rebase origin master`, then `python3 tools/check_csv.py`; repair
   ledger errors first. If the pull touched your own area, `./build.sh` the
   affected sources and repair regressions.
1. `python3 tools/next_work.py --claim` serves, in order: regressions and gate
   debt (`python3 tools/repair_queue.py repair`), then link, stub-closure, header,
   TU-approval, consolidation, data, code-identity, ms-headers, dx and stlport
   (STLport 4.6 file moves) queues by weight (`docs/matching.md`, "The default pick"). Check any new-match candidate against current
   covered ranges, generated/alias owners, input freshness and history. Restore
   a proven lost row in its approved unit, never a fresh one-function file;
   existing-placeholder identity work stays in the naming/cleanup lanes.
   `--wb` is served on request only. Lanes and their tools are below; picker
   detail: `docs/matching.md` ("Work selection in detail").
2. Work the file, not the row: drain the other queued candidates in the same
   source file, finishing or reverting each body or homogeneous batch before the
   next.
3. Stay with one substantive target while new evidence-backed hypotheses remain.
   Test a shared explanation (layout, callee, compiler, ABI) before retrying
   several failures one by one. Reassess after ~120 minutes without progress
   (`docs/structural.md`, "Attempts").

### Convert, verify, commit, push

1. Make the smallest source and ledger change for one function, unit or
   homogeneous trivial batch (`docs/matching.md`, "Batch homogeneous trivial
   changes"; verify each member on its own evidence).
2. `./build.sh <file-or-symbol>`.
3. Stage explicit paths and commit normally.
4. On failure, record the verdict: `python3 tools/re_log.py record <symbol>
   <rva> <size> <status> <evidence>` with the boundary, `t=<minutes>` and your
   model (`blocked-on=0x<rva>` when walled by a missing function). Close but not
   exact: `partial '<what is wrong>' --stash <your .cpp> --score <0..1>`; no body,
   no `partial`. Commit a handoff under `reverse/attempt_support/` for
   substantive `blocked` or `partial` attempts. Read prior entries before
   retrying any function.
5. Publish per the rules above.

## Lanes and tools

- **Regressions and gate debt**: `repair_queue.py repair` (baseline lines,
  tier C rows, emulator divergences, smoke queues). Smoke items: never start
  `boot_smoke.py` or `game_smoke.py bisect`; run a desync test only with a
  maintainer-provided sandbox and retail record; record repaired crashes as
  awaiting the maintainer's pass (`docs/verifier_upgrade_plan.md`, "Boot and
  smoke queues").
- **Link repair**: `next_work.py --tier link`, `repair_queue.py link`,
  `python3 tools/link_rank.py` (`docs/linking.md`).
- **Class headers**: `next_work.py --tier header`, `python3 tools/class_views.py`,
  `python3 tools/header_adopt_lane.py order` (`docs/linking.md`).
- **Data identity**: `next_work.py --tier data`, `tools/data_check.py`,
  `python3 tools/name_globals.py`.
- **Source-file recovery**: `python3 tools/tu_skeleton.py --queue`
  (`docs/consolidation.md`).
- **Escape-hatch debt**: replace a hatch with real code or a real name and lower
  its count, preferably in files you are already in.
- **Names**: `tools/rename.py`, `tools/name_lane.py` (`docs/naming.md`).
- **Cleanup**: funclet repoints via `tools/eh_verify.py`, `repair_queue.py
  ms-headers`, `next_work.py --tier dx` (`docs/matching.md`, "Cleanup lane
  details").
- **Reference lanes** (source leads for regressions, link repairs and `gen-*`
  repoints): `tools/bfme1_sweep.py`, `reference/open-bfme-1/tools/lift_lane.py`,
  `tools/zh_sweep.py`, `tools/list_naked_candidates.py`, `tools/place_bodies.py`
  (`docs/matching.md`, "Reference lanes and donor sweeps"). Check
  `reverse/re_attempts.log` before reworking a served candidate.
- **False rejects**: record `python3 tools/re_log.py record <symbol> <rva> <size>
  blocked "false-reject <check>: <evidence> t=<min> model=<model>"` and move on.
  Tooling seats: `rg "false-reject" reverse/re_attempts.log`, reproduce, fix the
  check with a regression test and a `Verifier-Change:` trailer; every case in
  `tools/tests/test_gate_exploits.py` must still be refused.
- **VP6 clean room**: `reverse/vp6_cleanroom/queue.tsv`. Implement from the spec
  and retail only; never read any VP6 decoder source (On2, Winamp, ffdshow,
  MFNode); it is no reference sweep. Rules: `reverse/vp6_cleanroom/README.md`.

## Consolidate files into retail translation units

Check debt ownership, header queues and provider/consumer bindings for each
consolidation batch. Follow `docs/consolidation.md` ("Consolidation verification
checks") and record the results in the audit before pushing.

Start a consolidation or subsystem naming pass with
`python3 tools/name_lane.py consolidate --under Code/<subsystem>/` and read its
original-path evidence, alternatives and blockers. Reuse a report only while
`python3 tools/name_lane.py consolidate --check build/consolidation` passes;
regenerate it after relevant inputs change. This is the supported evidence
planner; hints and investigation groups do not approve a TU or a merge.

The one-function files are merged back into the TU retail built them from with
`tools/tu_skeleton.py`, never by hand: `--queue` picks an approved TU
(`reverse/tu_map.csv`), `--merge TU --dry-run` names the donors that do not yet
compile together, and `--merge TU` claims the scope, writes the TU, deletes the
absorbed donors and repoints every path-keyed column, keeping only merges that
lose no matched row. Reconcile a rejected donor's private views in its own
verified commit first; never split a mixed file inside a merge. Workflow:
`docs/consolidation.md`.

## Docs

- `docs/verifier_upgrade_plan.md`: the plan, hook rules in detail, runners, smoke
  queues.
- `docs/matching.md`: byte matching, picker detail, frozen files, batching,
  reference lanes, BFME 1 updates.
- `docs/structural.md`: manual RE, reassessing, recording and banking attempts.
- `docs/recipes.md`: proven fixes for near misses.
- `docs/linking.md`: the census, link tools, class reconciliation.
- `docs/linking_obstacles.md`: required linking handoff; update repairs, new
  obstacles and evidence for cleared entries.
- `docs/claims.md`: claim mechanics.
- `docs/naming.md`: names and `tools/rename.py`.
- `docs/consolidation.md`: TU merges.

Prose trimmed from these docs lives in git history, one `git show` away.
