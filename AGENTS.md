## Instruction freshness

Before continuing work, reread `AGENTS.md` if 24 hours have elapsed
since the last read. Reread it immediately whenever a user message
or commit message reports an edit to `AGENTS.md`.

# Contributing

Several agents push to `origin/master` continuously. Keep each change small,
verified and easy to rebase. `docs/matching.md` covers byte matching,
`docs/structural.md` manual RE. Prose trimmed from these docs lives in git
history, one `git show` away.

## Work selection

An explicit request or assigned lane overrides the queue:

1. `git pull --rebase origin master`
2. `python3 tools/check_csv.py` — repair ledger errors before other work
3. **Run the reference lanes before dump or structural reconstruction.** These
   queues are separate from the default picker; a zero result in one is not a
   reason to skip the others.

   a. Run `python3 tools/bfme1_sweep.py scan` when its image, BFME 1 pointer or
      BFME 2 ledger changed (otherwise reuse the scan), followed by
      `python3 tools/bfme1_sweep.py ranked` and
      `python3 tools/bfme1_sweep.py near`. The ranked queue is for byte-identical
      BFME 1 sources; `near` supplies source leads for repair.

      **A ranked hit may already be refused.** The queue does not consult
      `reverse/re_attempts.log`, so re-running it re-offers candidates that a
      previous seat rejected. Measured twice, a full rescan apart: `ranked`
      returns exactly one donor file and 17 bytes —
      `Rva00889...`/`0x0003CCE0` in `Rva0089CompactHelpers.cpp` — which is tier T3
      because lotrbfme.exe folded it, so the name is a guess on a folded address.
      It was recorded as refused in the log after the first rescan and `ranked`
      served it again after the second, with 5,006 control placements confirming
      the scan itself was healthy. Check the log for the candidate's RVA before
      treating a hit as available work.

   b. Ensure the committed BFME 1 pointer includes `tools/lift_lane.py`, then run
      `python3 reference/open-bfme-1/tools/lift_lane.py --limit 1000` at the
      start of the reference pass. This surfaces BFME 1's named lifted bodies
      with proven boundaries and puts same-name ZH definitions first. Use each
      ZH-marked name and readable-body path to prioritize the corresponding
      `GeneralsMD/` source as a lead; a same-name hit does not prove identity,
      and the lifted bytes themselves are not C++ recovery. If the tool is
      missing at the committed pointer, treat the BFME 1 freshness check as due
      regardless of its timestamp and complete the verified pointer update below;
      never silently skip or mark this lane exhausted.

   c. Run `python3 tools/zh_sweep.py compile` when the object cache is missing
      or its source, headers, toolchain or flags changed; add `--force` when
      those inputs changed. Then run `python3 tools/zh_sweep.py match` and
      `python3 tools/zh_sweep.py packets`. `match` serves exact ZH body
      placements; `packets` refreshes near misses in the queue consumed by
      `tools/next_work.py`. Inspect `python3 tools/next_work.py --tier packet`
      and work viable ZH packets before moving to step 4. Re-run `match` and
      `packets` after material ledger or dependency changes. Land only through
      the existing identity and full-byte verification gates.

4. `python3 tools/list_naked_candidates.py Code` serves a byte-true dump from
   `Code/gen_asm/`, boundary already proven. Prefer it after the reference
   lanes above have no worthwhile lead.

5. `python3 tools/next_work.py` for identity/structural work; it explains its
   own tiers.
6. `python3 tools/place_bodies.py <sources>` mines the units the ledger already
   compiles. A TU emits far more than the one function it was written to land,
   and the rest was invisible only because the export table had no address for
   it; the tool finds those addresses by masked byte search and reads each
   placed body's call sites for its callees. After an import, repair, or
   shared-dependency fix, rescan affected source units. Land incidental bodies
   as well as planned ones when each satisfies the existing identity,
   provenance, and byte verification requirements. Repeat while new placements
   unlock further candidates; a placement candidate alone is not a verified
   recovery. Prune what `./build.sh` refuses to a fixpoint, recording the
   refusal in `reverse/place_denylist.txt`.

A tier reporting zero candidates exhausts only that search method. In particular,
an empty byte-match queue does not exhaust reusable reference source. Regenerate with
`tools/drift_classify.py`, `tools/anchor_unclaimed.py`, `./build.sh`.

Finish or revert each body or homogeneous trivial batch before the next.

**Claim retail bodies before starting work.** Use
`python3 tools/claims.py claim 0xRVA` (pass every RVA in a batch). For a single selected candidate,
`python3 tools/next_work.py --claim` and
`python3 tools/list_naked_candidates.py Code --claim` claim while selecting and
retry if another worker won the race. The ranked and BFME 1 donor queues skip
live claims; after choosing a donor file, claim its target RVAs before editing.
If a claim is held by another worker, choose other work. An orchestrator should
set a stable, distinct `BFME_CLAIM_OWNER` for each seat so a seat can renew and
release only its own claims.

Claims are shared `refs/claims/0xRVA` on origin, expire after four hours, and
do not change `master` publication. `python3 tools/claims.py list` shows current
owners. A verified `add_match` or `add_match_batch` releases landed claims; run
`python3 tools/claims.py release 0xRVA` for a banked, blocked or abandoned body.
Renew the claim before expiry when work lasts longer than four hours.
Network failure warns and leaves work available without a shared claim.

## Prefer coverage-first reference sweeps

Prefer reference-source sweeps as the first approach whenever compatible reference units are available. Optimize for verified unique-byte gain per unit of effort by batching compatible units, especially within related library families whose dependencies already exist.

Escalate reference-based work before abandoning it for dump reconstruction:

1. Direct reuse / small repair. First try the reference unit essentially as-is, allowing small evidence-backed changes such as constants, declarations, offsets, helper selection, compiler settings, or other localized differences when they preserve the verified body and semantics.
2. Moderate repair. If the direct path fails but the function identity and relationship remain well supported, allow moderate evidence-backed adaptation of control flow, data access, calls, layouts, or compiler shape. Preserve the reference function's established purpose and semantics while reconciling target-specific differences.
3. Substantial reference-based reconstruction. If the reference is still clearly the same underlying function or subsystem, substantial reconstruction from it is allowed when retail evidence supports the identity, ABI, behavior, surrounding call relationships, and data usage. Treat the reference as the primary semantic and structural guide rather than discarding it merely because the target body has diverged significantly.
4. Byte-true dump reconstruction. Move to reconstructing the served Code/gen_asm/ body as real C++ only after the viable reference-based paths above have been exhausted or the available reference is no longer sufficiently applicable.

Use compiler and configuration variants from successfully matched siblings, with caching and isolated trials to improve throughput. Apply units that pass the existing matching pipeline, preserve provenance and compiler settings, continue through viable independent candidates, and group successful imports with their ledger updates into coherent commits. Move to deeper reconstruction when the sweep no longer offers worthwhile candidates.

Do not spend unbounded effort forcing a weak reference. Once evidence no longer supports the same identity or semantics, or reasonable repair attempts stop yielding useful progress, move on to the byte-true dump path.

Re-run sweeps as new dependencies, identities, compiler configurations, and sibling matches land; previously unproductive reference units may become viable later.

## Compile BFME 1 donors beyond byte matches

`bfme1_sweep.py` compares retail bytes; it cannot discover every reusable source
body. Before treating BFME 1 references as exhausted, compile plausible clean C++
donor units under BFME 2 settings and search their emitted bodies in `game.dat`,
even when the original BFME 1 bytes have no match. Prioritize supported identities
and siblings of successful transfers; exclude dumps and retired or refuted
candidates unless new evidence addresses the earlier finding.

For a clean BFME 1 C++ donor that `bfme1_sweep.py` cannot match, compile the
specific TU using BFME 2's toolchain and settings, then search emitted bodies in
`game.dat` with `tools/place_bodies.py <donor-TU>`. Use matched siblings to choose
compiler flags. This is a read-only lead search: never claim the external donor
path as BFME 2 source. Port supported bodies into an allowed `Code/` TU, preserve
the donor revision, flags and dependencies, and pass the normal byte and identity
gates. A placement alone proves neither identity nor recovery.

## Investigate shared deltas first

When multiple failures suggest the same layout, offset, callee, compiler,
ABI, or wrapper difference, test that shared explanation before retrying
each body independently. Apply a shared fix only where target evidence
supports it; similar symptoms alone do not establish a common cause.

Avoid repeating attempts whose current evidence points to the same
unresolved dependency. Continue with independent candidates, then resweep
affected units after the dependency is resolved.

## BFME 1 reference freshness

Use the existing `reference/open-bfme-1` submodule for both building and donor
discovery. When initializing it, and before BFME 2 work if the last successful
check is missing or over 24 hours old, fetch official `Open-BFME/Open-BFME-1`
`master`. Compare commit IDs; preserve dirty or unpublished submodule work.

Complete the current layout migration once: reconcile the old `Code/` and
`reference/` paths with upstream's `game/` and `inputs/reference/`, including
source `// cl:` flags and other moved build inputs. Use the existing layout
resolver where applicable and check the resolved directories and headers. MSVC
silently ignores missing include directories, so compilation alone does not
prove the intended headers were used. Verify and commit this repair with the
updated pointer; repeat path migration only if upstream changes its layout again.

For routine submodule updates:

1. Record the previous verified pointer and the actual checkout revision. Update
   the clean checkout to upstream HEAD, preserving enough information to compare
   the old and new inputs at the same BFME 2 revision.
2. Run BFME 2's full byte verification with valid dependency caches. Compare
   failures against the previous verified inputs under the same conditions;
   repair update regressions and report pre-existing failures separately. Never
   weaken verification or substitute headers silently to make an update pass.
3. Refresh the donor byte sweep and compile trials affected by changed source,
   headers or compiler settings. Record the donor revision with cached results;
   discard or regenerate results whose inputs no longer agree.
4. Include the verified submodule pointer and any required repairs in the next
   commit batch. Advancing the local checkout alone does not update the pointer
   other contributors receive.

Record a successful check in ignored `build/bfme1-last-check.txt` only after
verification, or when upstream is already at the verified pointer. Do not repeat
the fetch per transfer. If an update is blocked, retain the last verified build
inputs and report the exact blocker and attempted repair; do not mark the update
successful or suspend future freshness checks indefinitely.

## Make matched code link

A matched row whose unit cannot link is half done. `reverse/link_status.csv`
and `tools/link_census.py` are the measure, under Open-BFME-1's rules: a
COMDAT copy loses when retail's own bytes prove it wrong (else when it differs
from the first copy in link order; never by majority, STLport included), and a
file fails when a name it touches resolves to a kept definition proven not
retail's (`wrong_selected`). It counts only objects proven current by
Open-BFME-1's census receipts (include search inventory or a witnessed
compile) and records nothing if objects, inputs or tools move during the run.
Each `link_census_history.csv` row names its `rules`; a rule change is
recorded once, by `tools/census_rebaseline.py`, never by hand. These tools
steer the work, reading the census's index
(`build/link_census/link_index.pkl`; copy the daily census's from
`build/wt_link/`):

- `python3 tools/link_rank.py` ranks blockers by the matched bytes they hold
  out (sole blockers, blocking names, units within `--near` of linking);
  `--file SOURCE` lists one unit's. Prefer work that unblocks the most bytes.
- `python3 tools/link_check.py SOURCE...` (or `--staged`) predicts, in
  seconds and without link.exe, whether units link after your change.
  `--refresh` first recompiles objects other commits made stale.
- `python3 tools/name_globals.py` replaces hard-coded global addresses (the
  largest blocker class) with the globals the ledger defines there, keeping
  only rewrites that still byte-match.
- `python3 tools/rehome_rows.py [--apply]` moves rows from split-out units
  back to the home unit that already compiles an exact copy, removing the
  duplicate definition that stops both from linking.

**Reconcile classes, not just bodies.** Private per-unit views of one class
are the root cause of most COMDAT and unresolved blockers.
`python3 tools/class_views.py` ranks classes by private views or, with
`--blockers`, by what the census holds against them; `--class X` and
`--shims X` list the views and competing shim headers to merge. A class
with a shared header is registered in `reverse/canonical_classes.csv`;
`tools/class_gate.py` (pre-commit) refuses new private copies of it.
Claim scope-wide work so two seats do not collide:
`python3 tools/claims.py claim class:NAME` or `file:PATH`.

## Work the file, not the row

`next_work.py` lists every other queued candidate in the same source file.
**That file is your unit of work** — drain it first. Measured land rate: 19.5%
solo, 46.5% with ten or more siblings landed together, because the layout,
offsets and callee pins from the first body are what the next one needs. A
shared header edit costs a full gate: edit every dependent body, pay once.

When several files in one subsystem demonstrate the same successful
reference-transfer pattern, prioritize other candidates in that subsystem.
Reuse established compiler settings and evidence-backed shared deltas,
verifying their applicability to each candidate. Folder structure alone
is not evidence. Return to the broader queue when transfer behavior
diverges or the remaining candidates require distinct investigation.

## Batch homogeneous trivial recoveries

Atomic does not mean one function per commit.

When several bodies use the same established recovery pattern and form
one coherent, reviewable change, recover, ledger, verify, and commit them
as one batch. Examples include tiny getters/setters, thunks, wrappers,
and reference transfers differing only by verified RVA or offset.

Similar instruction shapes alone do not establish identity, types,
calling convention, or layout. Verify each member against its own
evidence; do not extrapolate correctness from a representative sample.

Prefer `Recover 31 disp8 ptr-chase getters` over 31 separate 7-byte
commits when all members satisfy these conditions. Keep batches small
enough to review and diagnose; prefer roughly 5–20 entries per commit
as a guideline, not a quota or hard limit.

Keep substantive reconstruction or work requiring distinct identity,
compiler, ABI/layout, or reconstruction reasoning in separate atomic
commits.

Verify the entire batch before committing. If a member fails, determine
whether the failure undermines the shared pattern. Continue with the
remaining members only if their evidence and verification still hold;
otherwise reassess the batch.

## Convert, verify, commit, push — per body or homogeneous trivial batch

1. Make the smallest source and ledger change for one function or a homogeneous trivial batch under the rule above.
2. `./build.sh <file-or-symbol>`. If a command returns a process or session ID,
   poll it; never launch a duplicate build.

   **Do not reach past the tools to debug a body.** `tools/build.py` is
   importable and `build.compile_source(source, output)` looks like the obvious
   way to see a raw compiler error, but it writes the **shared** object cache at
   `build/match/<mangled-source-path>.obj`. Every later `explain_mismatch` and
   `./build.sh` run for that source then silently reuses *your* object instead
   of building one, and the symptom is not an error — it is a body that stops
   emitting its symbol at all.

   That cost a wrong conclusion once: a "symbol not found in object" after an
   edit was read as proof the edit suppressed the function, when it was the
   cache replaying a hand-built object. The tell is a cached `.obj` whose source
   path no longer exists; the repair is to delete the `.obj` **and** its
   `.deps.json`. If you need a raw compile error, read `build.sh`'s own output
   or the `explain_mismatch` traceback — both go through the tools.
3. Stage explicit paths only: `git add <specific-paths>`, never `git add .`.
   Check every new ledger source is tracked.
4. Commit normally. **Never bypass hooks.**
5. `git pull --rebase origin master`, `git push`, then pull --rebase again. On
   rejection, follow the batching and retry rules in #7 before another attempt.
6. **Never land a pull request with GitHub's merge button.** The byte gates live
   in `.githooks/` and run on a local commit and a local push; a server-side
   merge invokes neither, so it publishes ledger rows asserting `matched` that
   nothing verified. That is the one failure this repo is built to prevent, and
   it is invisible afterwards because an unverified row reads exactly like a
   verified one. To land someone else's PR, cherry-pick it instead:

   ```sh
   git fetch origin pull/<N>/head:pr<N>
   git cherry-pick <sha>...        # onto master; authorship is preserved
   ./build.sh <symbol>             # the row's own verification still has to pass
   git push origin master
   ```

   Then comment on the PR: that it landed, under which SHAs, and that follow-up
   work should be stacked off `master` rather than the now-stale branch.

7. This step governs when to run #5. Keep each change verified; batch publication under these rules:

 Prefer accumulating verified commits until the unpublished batch recovers **500 retail bytes total or more**, then push them together. Keep substantive changes as separate verified commits. This is a preference, not a requirement to invent more work: publish a smaller final batch when the work or session ends, after the cooldown.

Header, vendored-reference and shared-shim edits — and a resolved merge — trigger the full gate in the hook; poll it, don't relaunch, and never filter a gate through a pipeline that hides its exit code.

Additionally, internally note the time of your last successful push and allow at least a 5-minute cooldown until the next push by the same GitHub account to this repository. Share that clock across workers using the account and continue useful work during the cooldown.

## Frozen files: check before you plan an edit

`find_declared_unmatched` refuses a source that defines **any** function the
ledger does not declare. Because a file accumulates definitions as bodies are
written ahead of their addresses, a file can cross that line and become
uneditable — and nothing re-checks it, because the gate only ever inspects
*staged* sources.

Measured 2026-09-29 over all 9,067 ledger sources: **116 files were refused,
every one of them carrying matched rows**, so none is an exempt parked draft.
They include the ones with the most remaining work:

```
InGameUI.cpp            121 undeclared definitions
Locomotor.cpp            50
OpenContain.cpp          50
GameWindowManager.cpp    45
PhysicsUpdate.cpp        44
```

**All 116 have since been unfrozen** (verified: zero of the 116 still refused).
The recipe that did it is worth reusing, because it is self-verifying rather
than judgement-based:

1. Run `find_declared_unmatched` on each refused file and read the undeclared
   definitions it names.
2. For files with few enough that the report still distinguishes them (**ten**
   worked; the earlier ceiling of three was needlessly cautious), insert
   `// ?<Class::method> present-unmatched` above each definition.
3. **Re-run the gate on that file, and revert it entirely if it still
   refuses.** A marker on the wrong overload — the `MeshClass::Scale` case —
   cannot then survive.

That loop took 86 files in three passes (ceilings 3, 10 and 25) with 8 reverts,
and the reversions are the point: the guard, not a hand-set ceiling, is what
makes the marking safe. The ceiling only decides how many files are *attempted*
-- a file whose declarations cannot all be placed is restored untouched rather
than half-marked, so raising it risks nothing but time.

**There are two failure modes, and the recipe above only fixes one.** Adding a
marker fixes a definition that has none. But a file can also be blocked by a
marker sitting on a definition that IS matched, which the tool reports
differently:

```
?getPath@CDDrive@@UAE?AVAsciiString@@XZ is matched in functions.csv from
this file but still marked present-unmatched (stale annotation - remove the
marker)
```

That needs the marker REMOVED, and an add-only sweep makes it worse -- it reads
the stale line as an undeclared definition, marks an already-matched one, and
the guard reverts the file. dx8indexbuffer.cpp sat in the remaining list with a
count of 1 for this reason: it had one problem and the sweep could only
aggravate it. Check for stale annotations before adding anything.

And a count of undeclared definitions is not a count of work needed.
CDManager.cpp reported 16 unclaimed definitions and needed nothing added --
14 already carried markers, and removing 2 stale ones unfroze the file.

A fourth and final cause, found on the last two files: the locator matched
`Class::method` as a literal, but the source writes `operator =` with spaces.
Matching with whitespace stripped on both sides, while still requiring `(` or
`<` next, closed collect.cpp and shattersystem.cpp. Those two had looked
permanently out of reach at 31 and 24 definitions; both were one whitespace
bug.

Any edit to a still-frozen file — however small, however correct — fails the
commit until its undeclared definitions are dealt with. Check membership before
you plan work in a file:

```sh
python3 tools/find_declared_unmatched.py <file>   # silent means it will commit
```

Two remedies, and they are not interchangeable:

- **`present-unmatched` / `absent-from-retail` markers**, one per definition.
  This is a *declaration* that the body is known but unpinned (or that retail
  dead-stripped it), so it is honest only where that is true. Adding it to hide
  a real over-claim is exactly the failure the gate exists to catch.

  **The marker must start with `?` or it is silently ignored.** The tool enters
  its symbol-splitting path only for lines beginning `// ?`, so a marker written
  any other way leaves the definition undeclared and the tool reports the *same
  refusal you started with*, saying nothing about the marker itself:

  ```
  // GameLogicRandomVariable::setRange present-unmatched    no effect
  // ?GameLogicRandomVariable::setRange present-unmatched   works
  ```

  Worth knowing before concluding that markers do not work. The label after `?`
  is never checked against the ledger -- only the trailing word is -- so a
  readable name is fine, but keep it honest.
- **Row the body**, which is real work and the reason the file is frozen.

Note that the second half of the tool's own error message is not actionable
here: it suggests `reverse/unclaimed_sources_whitelist.txt`, and that file
exists only in the BFME 1 reference tree, not in this repo. Do not go looking
for it — marker the definitions or row them.

An earlier version of this section said flatly: do not script the marking. That
was too strong, and the sweeps above are the counter-example — but the reason
behind it is real. The report names each definition as `Class::method` with no
argument types, so when a file defines two overloads of one method —
`MeshClass::Scale` is the worked case — nothing in the output says which one is
undeclared, and a marker placed on the wrong overload is caught only after the
edit, and loudly:

```
?Scale@MeshClass@@UAEXMMM@Z is matched in functions.csv from this file but
still marked present-unmatched (stale annotation — remove the marker)
```

So the rule is not "never script it" but "never script it without the guard":
insert, re-run the gate on that file, and revert the whole file if it still
refuses. With that loop the overload case is handled automatically — it cost two
reverts across 78 files. Without it, a script puts markers on matched
definitions and the failure surfaces one file at a time.

A related trap worth knowing, because it presents identically: a marker
written `// ?<mangled>,` is not the symbol name. The comma is the ledger row's
separator, copied along with the name, and the tool takes everything after
`// ?` to end-of-line as the symbol, so it misses and reports a declared,
matched definition as undeclared. 689 files carried such a marker; 14 of them
failed on it and were fixed in `24d5a90fb`.

## Anti-lift policy

Clean C++ is preferred; MASM or inline asm only for a proven codegen blocker
(compiler machinery, x87 shape, SEH). Lifting a dump into a
`__declspec(naked)`/`__emit` .cpp is **not** a conversion: it byte-matches by
construction, scores +0, and deletes the body the next converter needed. The
naked body must be **gone**, replaced by real C++. `tools/conversion_gate.py`
enforces this in both hooks, and the push hook scans your whole outgoing range
— a blocked push may name a historical lift, not yours. Never `--no-verify`.

Ghidra boundaries, xrefs and vtables are identity evidence; decompiled C is
not byte-match proof. After several failed shapes or ~30 minutes without byte
progress take a fresh candidate, never leaving a nonmatching reconstruction in
`Code/`. Record the verdict:
`python3 tools/re_log.py record <symbol> <rva> <size> <status> <evidence>`
(never hand-edit `reverse/re_attempts.log`); cite the real boundary and
include `t=<minutes>` and your model.

**Close, not exact? Bank the body.**
`partial '<what is wrong>' --stash <your .cpp> --score <0..1>` keeps the
candidate servable and starts the next agent from your body, not cold. Both
flags are required: over 95 rows, a `partial` describing the near miss without
banking it landed 5.1% against 7.5% for silence. No body, no `partial` —
record `blocked`.

## Placement and integrity

- Game source under `Code/`; MASM dumps in `Code/masm_dumps/`; scratch
  untracked under `build/`. Banked attempts (`reverse/attempts/<rva>.cpp`) are
  evidence, never progress: nothing compiles them, `add_match` deletes one on
  landing, `check_csv` flags leftovers.
- Prefer TU-scoped shims over shared-header edits.
- Progress = `matched` `reverse/functions.csv` rows backed by real source and
  byte verification. Markers and prose are not.
- **Landing a `reverse/symbols.csv` pin?** It is an ADDITIVE candidate list:
  the resolver keeps the first pinned address that reproduces retail, so a pin
  naming the *wrong* function still byte-matches and a green gate proves
  nothing about it. Run `tools/pin_consistency.py --symbol <name>` before you
  pin and `--check` after. `reverse/pin_consistency_baseline.csv` is the
  known-bad backlog and may only shrink — never add a line to get green. A
  harvested pin is a candidate, not an address: resolve the thunk and check it
  against the ledger's own body before spending a name on it.
- No fallback paths; they conceal mismatches.
- Never load `reverse/functions.csv`, `ghidra_functions.csv` or `exports.csv`
  wholesale; use `rg` or narrow filters.
- Preserve unrelated dirty-tree work; revert only your own attempt.

## Preserve donor provenance

In the existing evidence records, distinguish facts established from
target evidence, facts carried from donor source, and structural
inferences. Record the basis for identity and layout claims separately
when their evidence differs.

Exact bytes alone do not establish a donor name or layout as a target
fact. Preserve uncertainty until independent target evidence resolves it.

## Generated claims

`gen-*` rows (`Code/gen_small/`, `Code/gen_asm/`) are byte-true placeholders,
not progress. Recovering a real identity means writing clean C++ at its proper
`Code/` path and repointing the row:
`tools/add_match.py <real-name> <rva> <size> <source> --replace-rva <rva>` for
`gen_asm` dumps (`--replace-existing` when the name is unchanged). `check_csv`
rejects a gen-* row sharing a range with a real-name row; the placeholder
yields.

**Never edit a file under `Code/gen_asm/`**: repoint the row and leave the
orphaned `PROC`, which keeps converters conflict-free there.
`Code/gen_small/uw_gen_*.cpp` is owned end to end by `tools/gen_uw.py land` —
never hand-edit it, and never infer a funclet's `parent=` from adjacency; a
guessed parent is invented identity.

After landing a batch, sweep your own rows: one body per address. A duplicate
range among them is an over-claim, not an ICF alias.

## Vendored third-party claims

`vendored=<lib>-<ver>` rows carry the upstream's real identities, never `gen-`
prefixes; the header comment names the exact release. Library sources live at
their official BFME paths, and pristine C TUs compile against
`reference/shims/gamespy/`, never a real Platform SDK.
