Reread this file after 24 hours, and at once when a message or commit reports an edit to it.

## Goal and done

The product: BFME II rebuilt from source people can read and mod. Done: the game links
without `/FORCE` or stubs at a non-retail base; automated runs reach the menu, a
skirmish and save/load; game-logic CRCs equal retail's, a perturbed run caught
as the negative control (`docs/verifier_upgrade_plan.md` step 12); `Code/` is retail's
~2,300 TUs (today 17,893 files), every code row in its approved TU, real names, shared
classes.

Progress, in order: the real link's unresolved, duplicates and bridges
(`scoreboard.json`, `docs/automation.md`); the newest srv1 game-queue receipt for the newest
image (crash and row; menu, skirmish, save/load); `tools/image_iso.py` defects on
the newest image and what it could not analyze; `tools/progress.py`; debt registers and
hatch counts.

BYTE-MATCHED (100%), census LINKED and LINKING (`/FORCE` with stubs; `link_check.py`
only predicts) and NOT OURS are kept but never show the game works. Bridges are temporary
scaffolding, never progress, driven to 0 by real statics and classes; quote them beside a
run's reach. Markers, prose and `gen-*` rows are not progress; required records are records,
not progress.

## Start here

1. `git pull --rebase origin master`, `tools/check_csv.py`; repair ledger errors
   first and `./build.sh` your area if the pull touched it. A red `master` comes first:
   whoever is nearest repairs or reverts it.
2. An explicit request or lane overrides the queue; otherwise `tools/next_work.py
   --claim` (`docs/matching.md`). Check an apparent unrowed body against current coverage,
   existing owners and history; only a proven lost row is a regression, restored in its
   approved unit, never a fresh one-function file.
3. Claim first (`tools/claims.py claim 0xRVA` for every RVA, `class:NAME`, `file:PATH`);
   if another worker holds it, choose other work. Claims last four hours: `renew`; stop
   editing if renew refuses. Release a banked, blocked or abandoned body with
   `claims.py release`, scope claims by hand after the push; landed rows settle themselves
   (`--landed`, `docs/claims.md`).
4. Before planning an edit: `tools/find_declared_unmatched.py <file>`, the body's
   `reverse/re_attempts.log` entries, and for linking work the obstacle register
   (`docs/linking_obstacles.md`) for what you touch, updating entries you work on.
5. Work the file, not the row: drain its queued candidates, finishing or reverting each
   body or homogeneous batch before the next. Smallest change, `./build.sh <file>`,
   stage, commit.
6. Stay on one target while evidence-backed hypotheses remain; test a shared explanation
   (layout, callee, compiler, ABI) first; reassess after ~120 minutes without progress.
7. On failure record the verdict with `tools/re_log.py record`; `partial` only with a
   banked body; a substantive `blocked` or `partial` gets a handoff in
   `reverse/attempt_support/` (`docs/structural.md`).
8. A record never takes its own commit: it rides with its change. Records of no-change
   attempts go in one records commit per push, after the last change, never pushed alone
   before the session ends.

## Never

Many agents push to `master`: keep changes small, verified, rebasable.
Detail: `docs/verifier_upgrade_plan.md` ("Live rules in detail").

- Never `--no-verify` or bypass a hook (worktrees: `git -c core.hooksPath=.githooks`, made
  with `tools/worktree_setup.py`, never a bare `submodule update --init` in one). Gate code
  in `tools/`, `.githooks/` or a baseline/whitelist needs a `Verifier-Change: <reason>`
  trailer.
- A check refuses correct work: record a false reject; never work around it or edit it
  in that commit.
- Never compile by hand through `tools/build.py` (it poisons `build/match/`).
- `// cl:` holds flags only; no absolute `#include`; in Git Bash set `MSYS_NO_PATHCONV=1`
  before a `/I...` tool; control paths are lowercase.
- Never add a line to `reverse/gate_baseline.txt`; delete it when you fix its row. Retire
  debt only by its register's path; `Verifier-Change` never retires a key. A shadow
  check that reaches `enforce` never returns.
- Never add an escape hatch by hand: pins, `/alternatename`, `object-symbol=` rows,
  address-named globals, selectany, `class-gate: allow`, `present-unmatched`,
  `#pragma optimize`, `__emit`, `.asm` `db`. Counts rise only by a tool's admission or a
  total-keeping `hatch_counters.py --update`; running `--allow` or `--admit` yourself is
  hand-adding. Prefer removing hatches; remove a file's before renaming it.
- A pin is an in-image code RVA written by `pin_admission.py --add` or `add_match.py
  --pin`, never a second real name on a named address; an ICF fold needs `fold-proof=`.
  Run `pin_consistency.py --symbol <name>` before pinning and `--check` after;
  `reverse/pin_consistency_baseline.csv` only shrinks. `gen-alias` only as an exact notes
  token whose masked callee is a byte-and-relocation twin; never a new `object-symbol=`
  alias row.
- One global per address in `reverse/data_converged.csv`: declare the real global and cast
  (`((AIView *)TheAI)->m_field`); never bind a second symbol. The list only grows.
- No private copy of a class in `reverse/canonical_classes.csv`.
- Rows move only into the address's approved unit in a fresh `reverse/tu_map.csv`; a stale
  assignment or `repair_queue.py dest` fallback is no approval, and the consolidation lane
  never commits a regenerated `tu_map.csv`. Only compiler-emitted rows (`$L<n>`, `_$E<n>`)
  with no unit follow their parent, named in the commit message (`docs/consolidation.md`).
  Merge only with `tools/tu_skeleton.py`, never by hand or splitting a mixed file.
- Anti-lift: clean C++; MASM or inline asm only for a proven codegen blocker (compiler
  machinery, x87 shape, SEH). A dump lifted into `naked`/`__emit` is no conversion.
- Never edit `Code/gen_asm/` (repoint the row, leave the `PROC`) or
  `Code/gen_small/uw_gen_*.cpp` (`gen_uw.py land` owns it; never infer `parent=` from
  adjacency). Recover `gen-*` rows as clean C++ at their proper path (`add_match.py
  --replace-rva`).
- `vendored=<lib>-<ver>` rows keep upstream's names, never `gen-`, and the exact release;
  sources at official BFME paths; pristine C TUs compile against
  `reference/shims/gamespy/`, never a real Platform SDK.
- No fallback paths. No nonmatching code in `Code/`; banked attempts (`reverse/attempts/`)
  are evidence, never progress.
- Never hand-edit `reverse/re_attempts.log`. Unfreeze a file only by rowing its body or an
  honest `absent-from-retail` marker (`docs/matching.md`).
  `reverse/unclaimed_sources_whitelist.txt` only shrinks.
- Census rule changes only through `tools/census_rebaseline.py`.
- Stage explicit paths, never `git add .`; track new ledger sources; keep others'
  dirty-tree work, reverting only your own attempt.
- Never load `reverse/functions.csv`, `ghidra_functions.csv` or `exports.csv` wholesale.
- File placement: game source in `Code/`, dumps in `Code/masm_dumps/`, scratch untracked
  in `build/`; a new `tools/` file replaces one or is called by a hook, picker or tool;
  prefer TU-scoped shims to shared-header edits.
- Keep target facts, donor facts and inferences apart: bytes, placement or a same-name hit
  prove no donor name, layout or recovery; never claim a donor path as BFME 2 source.
- VP6: never read any decoder source (On2, Winamp, ffdshow, MFNode).

## Publishing

- Push only with `tools/push.py`, never by hand or in a loop; a GitHub account's pushes
  stay at least five minutes apart across all its workers (`$BFME_PUSH_CLOCK` beyond one
  clone; `docs/claims.md`). Never take a freeze yourself.
- No GitHub merge button: cherry-pick onto `master`, `./build.sh` the rows, push, and
  comment the landed SHAs on the PR.
- Push source-path moves as soon as they verify, after one consumer audit per batch
  (`docs/consolidation.md`). Batch other verified commits until they move a headline
  figure (`docs/claims.md`; a batching trigger, not progress), substantive changes in
  separate commits; publish what is left when you stop.
- `tools/link_batch_audit.py` refuses proven link losses; inconclusive is not clean, so a
  landing script reads `link_check.py`'s own verdict; losses go to the obstacle register.
- Poll a full-gate hook run or a build returning an ID; never relaunch or duplicate it,
  or pipe a gate through anything hiding its exit code.
- Never start, re-run or approve `tools/nightly_measure.py`, `nightly-measure.yml` or
  `tools/audit/run_nightly.cmd`; never start `boot_smoke.py` or `game_smoke.py bisect`
  for a smoke item; ask a maintainer before a direct `link_cycle.py` run, `boot_smoke.py`
  or the shadow publisher.
- BFME 1 upstream: one check per account per 168 hours; never record success before
  verification (`docs/matching.md`).

## Lanes

- **Regressions, gate debt**: `repair_queue.py repair`; repaired crashes await the
  maintainer's pass; run a desync test only with a maintainer-provided sandbox and a
  retail record (`docs/verifier_upgrade_plan.md`).
- **Link, headers, data**: `next_work.py --tier link|header|data`, `repair_queue.py link`,
  `link_rank.py`, `header_adopt_lane.py order`, `name_globals.py` (`docs/linking.md`).
- **Source files**: `name_lane.py consolidate --under Code/<dir>/`, `tu_skeleton.py
  --queue`, `--merge TU [--dry-run]`, checks per batch (`docs/consolidation.md`).
- **Hatch debt**: replace hatches with real code or names where you work.
- **Names**: `rename.py`, `name_lane.py` (`scoped` for locals), batches finished through
  application; read `docs/naming.md` before renaming; naming never passes a repair or
  merge test or delays a move. Never add unrelated files to reach a quota; no scoped votes
  or external reviewer CLI; `--propose-only` only on an explicit proposal-only assignment.
- **Cleanup, reference lanes**: `eh_verify.py`, `repair_queue.py ms-headers`,
  `next_work.py --tier dx`, `bfme1_sweep.py` and other donor sweeps (`docs/matching.md`);
  `--wb` only on request.
- **False rejects**: `re_log.py record ... blocked "false-reject <check>: <evidence>
  t=<min> model=<model>"` and move on. Tooling seats fix the check with a regression
  test and `Verifier-Change:`; every `tools/tests/test_gate_exploits.py` case stays refused.
- **VP6 clean room**: `reverse/vp6_cleanroom/queue.tsv` and its README.

## Docs

| Task | Read |
|---|---|
| Live rules, runners, smoke queues | `docs/verifier_upgrade_plan.md` |
| Matching, picker, frozen files, BFME 1; attempts; near-miss fixes | `docs/matching.md`, `docs/structural.md`, `docs/recipes.md` |
| Linking, census; obstacles | `docs/linking.md`, `docs/linking_obstacles.md` |
| Real link, recurring jobs | `docs/automation.md` |
| Claims, push clock; names | `docs/claims.md`, `docs/naming.md` |
| TU merges, path audit | `docs/consolidation.md` |

Trimmed prose lives in git history.
