## Instruction freshness

Before continuing work, reread `AGENTS.md` if 24 hours have elapsed
since the last read. Reread it immediately whenever a user message
or commit message reports an edit to `AGENTS.md`.

## Verifier upgrade (October 2026): live rules

The hooks refuse:

- a commit that edits `tools/` gate code, `.githooks/` or a baseline/whitelist
  without a `Verifier-Change: <reason>` trailer;
- any added line in `reverse/gate_baseline.txt` (keyed debt: delete a line when
  you fix its row, never add one);
- a string literal shorter than retail's, a switch jump table mapping a case to
  the wrong target, or compiled bytes past a row's extent that differ from
  retail (a body longer than its row: raise the extent);
- a new `symbols.csv` pin that is not an in-image code RVA, or that puts a second
  real name on an address that already has one (rename the owner). An ICF-folded
  template instantiation is admitted only with `fold-proof=<ledger source>` in
  its notes, when that unit compiles the name to retail's whole body there with
  every owner row's relocations and the name has no address of its own, a
  gen-alias twin included (`tools/pin_admission.py --add`); a later row or pin
  giving a fold-pinned name another address is refused too;
- `gen-alias` other than as an exact notes token whose masked callee is a
  byte-and-relocation twin; new `object-symbol=` alias rows;
- a second name for a converged data address. Each address in
  `reverse/data_converged.csv` (TheGameLogic, TheAI, TheWritableGlobalData, ...)
  has one global; another symbol bound there (`g_00DFE78C`, `extern AIView *TheAI`)
  links as a separate datum and fails link_cycle data-back for every row at that
  address. Declare the real global (`class AI; extern AI *TheAI;`) and cast to
  your view where you use it: `((AIView *)TheAI)->m_field`. The list only grows
  (`tools/data_check.py --converged`, after the byte gate);
- a control path (the root, `reverse/`, `tools/`, `.githooks/`, `.github/`) not
  spelled in lowercase (`tools/check_case_collisions.py`; banked attempts,
  attempt evidence and class contracts are exempt).

`.c` and `.asm` sources are byte-verified like `.cpp`. Escape hatches (pins,
`object-symbol=` rows, `/alternatename`, address-named globals, `class-gate:
allow`, `present-unmatched`, `#pragma optimize`, `__emit`) are counted per file in
`reverse/hatch_baseline.tsv` by `tools/hatch_counters.py` (shadow mode now; it
will refuse growth once enforced). Code identity and data checks also run in
shadow mode. Pushes go direct to `master`; `tools/publisher.py` only re-verifies
pushed work afterwards.

**Upgrade lanes.** Spend seats on these alongside matching:

- *False rejects.* If a check refuses work you can show is correct, do not work
  around it or edit the check in the same commit. Record
  `python3 tools/re_log.py record <symbol> <rva> <size> blocked
  "false-reject <check>: <evidence> t=<min> model=<model>"` and move on.
  Tooling seats: `rg "false-reject" reverse/re_attempts.log`, reproduce, and fix
  the check with a regression test and a `Verifier-Change:` trailer. Every case
  in `tools/tests/test_gate_exploits.py` must still be refused.
- *Escape-hatch debt.* Replacing a hatch in `reverse/hatch_baseline.tsv` with real
  code or a real name and lowering its count is credited repair work. Prefer
  files you are already in.
- *Repairs.* `python3 tools/repair_queue.py repair` serves gate debt, tier C rows
  and emulator divergences; `repair_queue.py link` serves rows a link cycle did
  not place; `repair_queue.py dest 0xRVA` names the file a new match belongs in.
- *VP6 clean room.* `reverse/vp6_cleanroom/queue.tsv` serves one spec per VP6
  decoder function. Implement from the spec and retail only; never read any VP6
  decoder source (On2, Winamp, ffdshow, MFNode): it may not be redistributed, and
  this lane is no reference sweep. Rules: `reverse/vp6_cleanroom/README.md`.
- *Verification runners* (`tools/link_cycle.py`, `tools/audit/run_nightly.cmd`,
  `tools/boot_smoke.py`, the shadow publisher): ask a maintainer before starting one.

Full plan and evidence: `docs/verifier_upgrade_plan.md`.

# Contributing

Several agents push to `origin/master` continuously. Keep each change small,
verified and easy to rebase. `docs/matching.md` covers byte matching,
`docs/structural.md` manual RE. Prose trimmed from these docs lives in git
history, one `git show` away.

## Work selection

An explicit request or assigned lane overrides the queue:

1. `git pull --rebase origin master`
2. `python3 tools/check_csv.py` — repair ledger errors before other work.
3. **Run the reference lanes before dump or structural reconstruction.** They are
   separate from the default picker; a zero result in one is no reason to skip
   the others.

   a. `python3 tools/bfme1_sweep.py scan` when its image, BFME 1 pointer or BFME 2
      ledger changed (otherwise reuse the scan), then
      `python3 tools/bfme1_sweep.py ranked` (byte-identical BFME 1 sources) and
      `python3 tools/bfme1_sweep.py near` (source leads for repair). `ranked` does
      not read `reverse/re_attempts.log` and re-serves candidates earlier seats
      refused (`0x0003CCE0` in `Rva0089CompactHelpers.cpp`, a folded T3 guess,
      was re-served after a rescan): check the log for a candidate's RVA before
      treating it as work.
   b. Ensure the committed BFME 1 pointer includes `tools/lift_lane.py`, then run
      `python3 reference/open-bfme-1/tools/lift_lane.py --limit 1000` at the start
      of the reference pass. It lists BFME 1's named lifted bodies with proven
      boundaries, same-name ZH definitions first: use each ZH-marked name and
      readable-body path to prioritize the matching `GeneralsMD/` source. A
      same-name hit does not prove identity, and lifted bytes are not C++
      recovery. If the tool is missing at the committed pointer, the BFME 1
      freshness check is due regardless of its timestamp: complete the verified
      pointer update below; never silently skip or mark this lane exhausted.
   c. `python3 tools/zh_sweep.py compile` when the object cache is missing or its
      source, headers, toolchain or flags changed (`--force` when those inputs
      changed), then `python3 tools/zh_sweep.py match` (exact ZH placements) and
      `python3 tools/zh_sweep.py packets` (near misses for `tools/next_work.py`).
      Work viable packets
      from `python3 tools/next_work.py --tier packet` before step 4; re-run
      `match` and `packets` after material ledger or dependency changes. Land only
      through the identity and full-byte gates.

4. `python3 tools/list_naked_candidates.py Code` serves a byte-true dump from
   `Code/gen_asm/`, boundary proven; prefer it once the reference lanes have no
   worthwhile lead.
5. `python3 tools/next_work.py` for identity/structural work (it explains its
   tiers); `--wb` serves bodies by WorldBuilder name lead; proven fixes:
   `docs/recipes.md`.
6. `python3 tools/place_bodies.py <sources>` finds, by masked byte search, the
   other bodies the units the ledger already compiles emit, and reads their call
   sites for callees. Rescan affected units after an import, repair or
   shared-dependency fix; land incidental bodies that satisfy the identity,
   provenance and byte requirements (a placement alone is no recovery); repeat
   while placements unlock more. Prune what `./build.sh` refuses to a fixpoint and
   record the refusal in `reverse/place_denylist.txt`.

A tier reporting zero candidates exhausts only that search method; an empty
byte-match queue does not exhaust reusable reference source. Regenerate with
`tools/drift_classify.py`, `tools/anchor_unclaimed.py`, `./build.sh`.

Finish or revert each body or homogeneous trivial batch before the next.

**Claim retail bodies before starting work:** `python3 tools/claims.py claim 0xRVA`
(every RVA in a batch); `python3 tools/next_work.py --claim` and
`python3 tools/list_naked_candidates.py Code --claim` claim while selecting and
retry if another worker won the race. The ranked and BFME 1 donor queues skip
live claims; after choosing a donor file, claim its target RVAs before editing.
If another worker holds a claim, choose other work. An orchestrator should set a
stable, distinct `BFME_CLAIM_OWNER` for each seat.

Claims are `refs/claims/0xRVA` on origin, expire after four hours, and do not
change `master` publication; `python3 tools/claims.py list` shows owners. A
verified `add_match` or `add_match_batch` keeps the claim and queues the row; the
claim is released once origin/master holds the row, the blobs of every file the
verified compile read and any `reverse/symbols.csv` pins you added. The pickers'
`--claim` settle such landings, and so does `claims.py claim`, which claims first
and then settles eligible queued landings except the RVAs that command requested
(those stay held); `python3 tools/claims.py release --landed` does it on demand
after a push. A landing that cannot be shown (an untracked or ignored header)
keeps its claim until it expires. Release a banked, blocked or abandoned body
with `python3 tools/claims.py release 0xRVA`; renew before expiry with
`python3 tools/claims.py renew 0xRVA` when work lasts longer than four hours (it
keeps the lease, so a queued landing still releases; re-running `claim` on your
own live claim also preserves its lease). `renew` and `release` also act on
claims this checkout took before 2026-10-09 under the old `<user>@<host>` owner. When origin is
unreachable, `claims.py claim` claims nothing and exits 2; the pickers then warn
and serve the body unclaimed, skipping any body origin showed another worker
holding.

## Prefer coverage-first reference sweeps

Prefer reference-source sweeps first whenever compatible reference units exist;
optimize for verified unique bytes per effort by batching compatible units,
especially library families whose dependencies already exist. Escalate before
abandoning a reference for dump reconstruction:

1. Direct reuse or small evidence-backed repair (constants, declarations,
   offsets, helper selection, compiler settings) that preserves the verified body
   and semantics.
2. Moderate repair of control flow, data access, calls, layouts or compiler
   shape while identity and relationship stay well supported. Make evidence-backed
   adaptations; preserve the reference function's established purpose and
   semantics while reconciling target-specific differences.
3. Substantial reconstruction from the reference while retail evidence supports
   identity, ABI, behavior, call relationships and data usage; the reference
   stays the semantic and structural guide.
4. Byte-true reconstruction of the `Code/gen_asm/` body as real C++, only once the
   reference paths are exhausted or no longer applicable.

Use compiler variants from matched siblings, with caching and isolated trials;
preserve provenance, dependencies and compiler settings; continue through viable
independent candidates; commit successful imports with their ledger updates
coherently. Do not force a weak reference: once evidence no longer supports the
same identity or semantics, or reasonable repairs stop progressing, move on.
Re-run sweeps as dependencies, identities, compiler configurations and sibling
matches land.

## Compile BFME 1 donors beyond byte matches

`bfme1_sweep.py` compares retail bytes and cannot find every reusable body.
Before treating BFME 1 references as exhausted, compile plausible clean C++ donor
TUs with BFME 2's toolchain and settings (flags from matched siblings) and search
their emitted bodies in `game.dat` with `tools/place_bodies.py <donor-TU>`, even
when the BFME 1 bytes have no match. Prioritize supported identities and siblings
of successful transfers; exclude dumps and retired or refuted candidates unless
new evidence addresses the earlier finding. This is a read-only lead search:
never claim the external donor path as BFME 2 source. Port supported bodies into
an allowed `Code/` TU, preserving the donor revision, flags and dependencies, and
pass the normal byte and identity gates. A placement proves neither identity nor
recovery.

## Investigate shared deltas first

When multiple failures suggest the same layout, offset, callee, compiler, ABI or
wrapper difference, test that shared explanation before retrying each body.
Apply a shared fix only where target evidence supports it; similar symptoms alone
do not establish a common cause. Do not repeat
attempts blocked on the same unresolved dependency: continue with independent
candidates and resweep affected units once it is resolved.

## BFME 1 reference freshness

Use the `reference/open-bfme-1` submodule for building and donor discovery. On
initialization, and before BFME 2 work when the last successful check is missing
or over 24 hours old, fetch official `Open-BFME/Open-BFME-1` `master`, compare
commit IDs, and preserve dirty or unpublished submodule work.

Complete the current layout migration once: reconcile the old `Code/` and
`reference/` paths with upstream's `game/` and `inputs/reference/`, including
source `// cl:` flags and other moved inputs, using the existing layout resolver
where applicable, and check the resolved directories and headers (MSVC silently
ignores a missing include directory, so compilation alone does not prove the
intended headers were used). Verify and commit this repair with the updated
pointer; repeat only if upstream changes its layout again.

For a routine update:

1. Record the previous verified pointer and the checkout revision; update the
   clean checkout to upstream HEAD, keeping enough to compare old and new inputs
   at the same BFME 2 revision.
2. Run BFME 2's full byte verification with valid dependency caches; compare
   failures with the previous inputs under the same conditions; repair update
   regressions and report pre-existing failures separately. Never weaken
   verification or substitute headers silently.
3. Refresh donor sweeps and compile trials affected by changed source, headers or
   settings; record the donor revision with cached results; discard or regenerate
   results whose inputs no longer agree.
4. Include the verified submodule pointer and any required repairs in the next
   commit batch: advancing the local checkout does not update what other
   contributors receive.

Record success in ignored `build/bfme1-last-check.txt` only after verification,
or when upstream is already at the verified pointer. Do not fetch per transfer. If
an update is blocked, keep the last verified inputs and report the exact blocker
and attempted repair; do not mark it successful or suspend future freshness
checks indefinitely.

## Make matched code link

A matched row whose unit cannot link is half done. `reverse/link_status.csv` and
`tools/link_census.py` measure it under Open-BFME-1's rules: a COMDAT copy loses
when retail's bytes prove it wrong (else when it differs from the first copy in
link order; never by majority, STLport included), and a file fails when a name it
touches resolves to a kept definition proven not retail's (`wrong_selected`). It
counts only objects proven current by census receipts and records nothing if
objects, inputs or tools move during the run. Each `link_census_history.csv` row
names its `rules`; a rule change is recorded once, by `tools/census_rebaseline.py`,
never by hand. The census index is `build/link_census/link_index.pkl` (copy the daily
census's from `build/wt_link/`):

- `python3 tools/link_rank.py` ranks blockers by the matched bytes they hold out
  (`--file SOURCE` for one unit, `--near` for units close to linking). Prefer work
  that unblocks the most bytes.
- `python3 tools/link_check.py SOURCE...` (or `--staged`) predicts, without
  link.exe, whether units link after your change; `--refresh` first recompiles
  objects other commits made stale.
- `python3 tools/name_globals.py` replaces hard-coded global addresses (the
  largest blocker class) with the ledger's globals, keeping rewrites that still
  byte-match.
- `python3 tools/rehome_rows.py [--apply]` moves rows from split-out units back
  to the home unit that already compiles an exact copy.

In a dedicated linking pass, prefer sweeping BFME 1 linking repairs before
rediscovering shared fixes: compare BFME 2's ranked blockers with
`reference/open-bfme-1`'s linking repairs, canonical headers and dependency
reconciliations, inspect relevant donor commits and their verification
evidence, and prioritize repairs to shared library and engine families already
used by BFME 2. Routine linking and small dependency repairs accompanying a
recovery proceed directly. Track the donor revision reviewed and whether each
repair is inherited, applicable, blocked or inapplicable; revisit blocked ones
when their dependencies or donor evidence change, and do not repeat an unchanged
donor scan. Try the donor repair directly where BFME 2 evidence supports it, then
adapt it locally; preserve BFME 2 layouts,
addresses, ABI and behavior; verify affected bodies and check providers and
consumers together — a BFME 1 linking result is a lead, not BFME 2 proof. After a
repair succeeds, sweep BFME 2 units with the same supported cause, batch the
compatible fixes and refresh the blockers; continue with independent candidates
when a repair needs unrelated investigation.

**Reconcile classes, not just bodies.** Private per-unit views of one class cause
most COMDAT and unresolved blockers. `python3 tools/class_views.py` ranks classes
by private views (`--blockers`: by what the census holds against them; `--class X`
and `--shims X` list the views and competing shim headers). A class with a shared
header is registered in `reverse/canonical_classes.csv`, and `tools/class_gate.py`
refuses new private copies of it. To give a class a canonical header, follow
`python3 tools/header_adopt_lane.py order`: `tools/class_contract.py` decides its
ABI from evidence (bytes, retail access, retail vftables, ZH, majority), and
`header_adopt_lane.py run --generate --apply` generates the header, gates each
unit and queues the rest in `reverse/header_queue.tsv`. Claim scope-wide work:
`python3 tools/claims.py claim class:NAME` or `file:PATH`.

## Work the file, not the row

`next_work.py` lists every other queued candidate in the same source file: that
file is your unit of work; drain it first (land rate 19.5% solo, 46.5% with ten
or more siblings landed together). A shared header edit costs a full gate: edit
every dependent body, pay once. When several files in one subsystem show the
same successful reference-transfer pattern, prioritize that subsystem, reusing
its compiler settings and evidence-backed deltas after checking each applies
(folder structure alone is not evidence); return to the broad queue when transfer
behavior diverges or the remaining candidates require distinct investigation.

## Batch homogeneous trivial recoveries

Atomic does not mean one function per commit. When bodies use one established
recovery pattern and form one coherent, reviewable change (tiny getters/setters,
thunks, wrappers, reference transfers differing only by verified RVA or offset),
recover, ledger, verify and commit them as one batch, roughly 5–20 entries (a
guideline, not a quota or hard limit). Similar instruction shapes do not
establish identity, types, calling convention or layout: verify each member
against its own evidence. Keep substantive reconstruction, or work needing
distinct identity, compiler, ABI/layout or reconstruction reasoning, in separate
commits. Verify the whole batch before committing. If a member fails, determine
whether that undermines the shared pattern; continue with the remaining members
only if their evidence and verification still hold, otherwise reassess the batch.

## Convert, verify, commit, push — per body or homogeneous trivial batch

1. Make the smallest source and ledger change for one function or batch.
2. `./build.sh <file-or-symbol>`. If a command returns a process or session ID,
   poll it; never launch a duplicate build. Do not compile by hand through
   `tools/build.py` (`build.compile_source`) to see a raw error: it writes the
   shared cache `build/match/<mangled-source-path>.obj`, and later `./build.sh`
   and `explain_mismatch` runs silently reuse your object (the symptom: a body
   that stops emitting its symbol). The tell is a cached `.obj` whose source path
   no longer exists; delete that `.obj` **and** its `.deps.json`. Read raw errors
   from `build.sh` or the `explain_mismatch` traceback.
3. Stage explicit paths only (`git add <paths>`, never `git add .`); check every
   new ledger source is tracked.
4. Commit normally. **Never bypass hooks.**
5. `git pull --rebase origin master`, `git push`, then pull --rebase again; on
   rejection follow #7 before retrying.
6. **Never land a pull request with GitHub's merge button**: the byte gates run
   in local hooks, so a server-side merge publishes `matched` rows nothing
   verified, invisibly. Cherry-pick instead:

   ```sh
   git fetch origin pull/<N>/head:pr<N>
   git cherry-pick <sha>...        # onto master; authorship is preserved
   ./build.sh <symbol>             # the row's own verification still has to pass
   git push origin master
   ```

   Then comment on the PR with the landed SHAs, and that follow-up work should
   stack off `master`.
7. Publication: prefer accumulating verified commits until the unpublished batch
   recovers **500 retail bytes** or more, then push together; keep substantive
   changes as separate commits; publish a smaller final batch when the work or
   session ends. Header, vendored-reference and shared-shim edits, and resolved
   merges, trigger the full gate in the hook: poll it, don't relaunch, and never
   filter a gate through a pipeline that hides its exit code. Internally note the
   time of your last successful push and allow at least a five-minute cooldown
   until the next push by the same GitHub account to this repository; share that
   clock across workers using the account and keep working during the cooldown.

## Frozen files: check before you plan an edit

`find_declared_unmatched` refuses a staged source that defines **any** function
the ledger does not declare, and nothing re-checks unstaged files, so a file can
become uneditable. Check before planning work in one (silent means it commits):

```sh
python3 tools/find_declared_unmatched.py <file>
```

Two remedies, not interchangeable:

- **Row the body** — real work, and the reason the file is frozen.
- **A `present-unmatched` or `absent-from-retail` marker**, one per definition:
  a declaration that the body is known but unpinned (or that retail dead-stripped
  it), honest only where true; never use it to hide an over-claim. It must start
  `// ?` (`// ?<Class::method> present-unmatched`) or it is silently ignored; the
  label is free, only the trailing word is read. Do not copy a ledger row's
  trailing comma into it (`// ?<mangled>,` misses).

Read the undeclared definitions the report names. Before adding markers, remove
stale ones: a marker on a definition that IS matched is reported "still marked
present-unmatched (stale annotation)", and an add-only pass makes that worse.
After any marker insertion, manual or scripted, re-run `find_declared_unmatched`
on that file and revert your whole file attempt if it still refuses (the report
gives `Class::method` without argument types, so a marker can land on the wrong
overload). The error message's suggestion of
`reverse/unclaimed_sources_whitelist.txt` does not apply: that protected list
(`tools/protected_paths.py`) only exempts sources with zero matched rows and may
only shrink.

## Anti-lift policy

Clean C++ is preferred; MASM or inline asm only for a proven codegen blocker
(compiler machinery, x87 shape, SEH). Lifting a dump into a
`__declspec(naked)`/`__emit` .cpp is **not** a conversion: it byte-matches by
construction, scores +0, and deletes the body the next converter needed. The
naked body must be gone, replaced by real C++. `tools/conversion_gate.py`
enforces this in both hooks; the push hook scans your whole outgoing range, so a
blocked push may name a historical lift. Never `--no-verify`.

Ghidra boundaries, xrefs and vtables are identity evidence; decompiled C is not
byte-match proof. After several failed shapes or ~30 minutes without byte
progress take a fresh candidate, never leaving a nonmatching reconstruction in
`Code/`. Record the verdict with
`python3 tools/re_log.py record <symbol> <rva> <size> <status> <evidence>` (never
hand-edit `reverse/re_attempts.log`), citing the real boundary, `t=<minutes>` and
your model. Walled only by a missing function? Add `blocked-on=0x<rva>`: the queue
re-serves you as untried once it lands. `add_match` records `landed` and lists
deferrals citing the body it landed — stage the log with your row.

**Close, not exact? Bank the body:** `partial '<what is wrong>' --stash <your .cpp>
--score <0..1>` keeps the candidate servable and starts the next agent from your
body. Both flags are required (a `partial` without a banked body landed 5.1%
against 7.5% for silence). No body, no `partial` — record `blocked`.

## Placement and integrity

- Game source under `Code/`; MASM dumps in `Code/masm_dumps/`; scratch untracked
  under `build/`. Banked attempts (`reverse/attempts/<rva>.cpp`) are evidence,
  never progress: nothing compiles them, `add_match` deletes one on landing,
  `check_csv` flags leftovers.
- Prefer TU-scoped shims over shared-header edits.
- Progress = `matched` `reverse/functions.csv` rows backed by real source and
  byte verification. Markers and prose are not.
- **Landing a `reverse/symbols.csv` pin?** Pins are an additive candidate list:
  the resolver keeps the first pinned address that reproduces retail, so a pin
  naming the wrong function still byte-matches. Run
  `tools/pin_consistency.py --symbol <name>` before you pin and `--check` after;
  `reverse/pin_consistency_baseline.csv` may only shrink. A harvested pin is a
  candidate: resolve the thunk and check it against the ledger's own body before
  spending a name on it.
- No fallback paths; they conceal mismatches.
- Never load `reverse/functions.csv`, `ghidra_functions.csv` or `exports.csv`
  wholesale; use `rg` or narrow filters.
- Preserve unrelated dirty-tree work; revert only your own attempt.
- A new file under `tools/` should replace an existing tool or be called by a
  hook, a picker or another tool; one-off and exploratory scripts stay untracked
  in `build/`.

## Preserve donor provenance

In the evidence records, distinguish facts established from target evidence,
facts carried from donor source, and structural inferences; record the basis for
identity and layout claims separately when their evidence differs. Exact bytes
alone do not establish a donor name or layout as a target fact: preserve the
uncertainty until independent target evidence resolves it.

## Generated claims

`gen-*` rows (`Code/gen_small/`, `Code/gen_asm/`) are byte-true placeholders, not
progress. Recovering a real identity means writing clean C++ at its proper `Code/`
path and repointing the row:
`tools/add_match.py <real-name> <rva> <size> <source> --replace-rva <rva>` for
`gen_asm` dumps (`--replace-existing` when the name is unchanged). `check_csv`
rejects a gen-* row sharing a range with a real-name row; the placeholder yields.

**Never edit a file under `Code/gen_asm/`**: repoint the row and leave the
orphaned `PROC`. `Code/gen_small/uw_gen_*.cpp` is owned end to end by
`tools/gen_uw.py land` — never hand-edit it, and never infer a funclet's
`parent=` from adjacency. After landing a batch, sweep your own rows: one body per
address; a duplicate range among them is an over-claim, not an ICF alias.

## Vendored third-party claims

`vendored=<lib>-<ver>` rows carry the upstream's real identities, never `gen-`
prefixes; the header comment names the exact release. Library sources live at
their official BFME paths, and pristine C TUs compile against
`reference/shims/gamespy/`, never a real Platform SDK.
