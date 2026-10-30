# XferSaveAsText canonical base-header adoption

Inspected `eb384b72a19073f986ee9ae431ebb3766d45562c` on 2026-10-29 under `class:Xfer` and
`file:Code/GameEngine/Include/Common/BfmeXfer.h`. This clears the text saver's
constructor-emission prerequisite from the
[previous handoff](xfer-header-blockers-20261028-codex.md).

## Change and evidence boundary

The private Xfer in BfmeRva00C7B388Xfer.cpp already had an imported,
force-inlined empty constructor. The previous out-of-class definition
could preserve the rows but emitted a second external constructor, while
an imported out-of-class definition disagreed with the canonical declaration.
The header now offers that existing declaration/body under the explicit
`BFME_XFER_INLINE_CTOR` option. Its ordinary declaration remains the default.
The text saver selects it alongside the existing inline-destructor option,
retains its original inline-depth control and defines the inline destructor
locally. This removes the private Xfer definition without creating another
constructor provider or changing the class layout.

This is a compiler-emission/header reconciliation of existing source.
No new donor identity, original TU placement, generated-body recovery or
new retail coverage is inferred. The function ledger, pins, data ownership,
source paths and other five Xfer header-queue entries are unchanged.

## Verification

- Normal paired build: 79/79 function rows (36 text-saver, 43 constructor-owner),
  one data row, 42 literals plus three empty-string references and one named
  import pass. The text saver's renumbered EH label is verified from the parent
  EH data at 0x007A6D72.
- The before/after object comparison preserves all 88 text-saver and 63 owner
  external COMDAT byte-and-relocation fingerprints. Neither object adds,
  removes or changes a fingerprint; external definitions, undefined symbols
  and weak bindings are equal. [Comparison](xfer-text-header-adoption-20261029-codex.json).
- `header_adopt_lane.py accept --class Xfer` passes and retires exactly the
  text saver's queue row through the owning tool. Frozen-file checks pass for
  the source and header.
- `link_check.py --prepare-current` prepares both sources with strict current
  receipts. The paired ordinary preview retains LINKS for 2,447 + 2,015 =
  4,462 authored bytes against index `85f6b7f40c` (2026-10-29 15:08).
  These are unchanged preview bytes, not a new census result.

## Remaining work

The FamilyDeletingDtors tag-constructor emitter needs its own emission or
approved-placement solution; selecting an imported inline constructor does
not itself emit its scalar deleting destructor. The concrete reader/block
provider identities in GameStateAutoSave and xfer_load, the stream identity
in XferSaveOpen, and PersistentStorageThread's concrete reader interface
remain separate prerequisites. This adoption does not clear those entries.

Local raw build inputs and comparison objects are in
`build/xfer-header-20261029-codex/`; the result above does not depend on their
continued availability.

## Dependent gate and outgoing audit

`header_adopt_lane.py gate-cost` verifies all 641 pre-existing header
dependents in two chunks: 441 seconds, BUILD_POOL=13, zero red chunks.
Together with the separately verified adopting source, the staged header
scope contains 642 ledger sources. The normal commit hook checks that
staged scope again as required.

The staged-tree outgoing audit is INCONCLUSIVE (exit 2). Its index
`85f6b7f40c` predates base `eb384b72a1`, and 640 dependent objects lack
current census receipts (first: Common/AIGuardState_xfer.cpp). Passing the
normal byte gate does not supply those strict link receipts. Carry the
642-source header scope and its affected consumers into the next scheduled
census; this change claims neither complete consumer closure nor a measured
linking/ownership gain.

## Publication recovery

Recovery inspected `54b49e6fc4` on base `f014d1c08f` on 2026-10-29. The
preparation record names backup `refs/runner/preparation/1793297270425427113`
and no stash or resync stash. Its saved commit equals the recovered HEAD;
the rebase is complete, and no staged, unstaged or untracked edits remain to
restore. The backup and existing unrelated stashes are retained.

The fleet publisher's refusal at base `28c5f4a483` states that header
acceptance received no usable per-unit link verdict. `/opt/runner/publish
--now` replays that saved refusal for the unchanged candidate; it did not
run a new hook. The recovery therefore restores the original queue row in
a follow-up commit, retaining all verified source/header changes. The final
batch retires no header debt. Retry the owning acceptance command when the
publishing checkout can reproduce the per-unit preview; no verifier is changed.

Checks in this checkout before restoring the queue row:

- `python3 tools/check_csv.py`: passes.
- `python3 tools/repair_queue.py verify-removed --range origin/master HEAD`:
  passes both ordinarily and with the publisher's Python/build/git environment.
- `BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run`: exit 0, PRE-PUSH OK,
  642 sources byte-verified, 718 exact EH rows, scoped DIR32 and converged-data
  checks pass. This dry run publishes nothing despite push.py's generic
  "landed" status wording.
- Ordinary `link_check.py` on the text saver: LINKS, 2,447 -> 2,447 bytes
  against index `85f6b7f40c`, both ordinarily and in the publisher environment.
- The link batch audit remains INCONCLUSIVE on the older index and 640
  missing current receipts, as recorded above. No census gain is claimed.

Local raw logs are `build/recovery-push-dry-run.log`,
`build/recovery-publish.log`, `build/recovery-debt-publisher-env.log` and
`build/recovery-link-publisher-env.log`. These establish local verification
and the recorded publication refusal, not its root cause.

## Queue retirement retry (2026-10-30)

At `5ac57bb2d0d287eb2c67c9e54104c09d08e4d10f`, the supported
`header_adopt_lane.py accept --class Xfer` command passes for
`Code/GameEngine/Source/Common/System/BfmeRva00C7B388Xfer.cpp` and removes
exactly its restored queue row. This retry changes no source, shared header,
ledger, pin or provider binding. The earlier publication refusal remains
recorded above; the current owning-tool verdict is passing.

Normal `./build.sh` verifies all 36 function rows, the renumbered parent-EH
label, 42 literals, two empty-string references and one named import.
`find_declared_unmatched.py` reports no unrowed definitions. Strict
`link_check.py --prepare-current` passes for the explicit source; the ordinary
preview retains LINKS for 2,447 bytes against `85f6b7f40c` (2026-10-29 15:08).
This retires one header-debt row only. It does not repeat or close the earlier
642-source header/consumer audit, establish the publication refusal's cause,
or claim a census gain. The other four Xfer queue entries retain their
constructor-emission, concrete-reader and stream prerequisites.
