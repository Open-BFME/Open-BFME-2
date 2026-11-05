# CallHelpOnDamage onDamage consolidation

Base: `bd15bd2dac`. Index: 2026-11-05 05:17 at `c95fcfcfcd`;
the fetch kept that local index and imported the published object archive.

The seed's one-slot leaf view and the onDamage donor's flat module-data view
prevented their composition. Both now use the same DamageModule-based leaf
declarations and the constructor's INI-backed module-data layout, including
the real filter member at +0x18. The seed uses the canonical DamageModule
header; no constructor or new virtual-table definition is emitted there.
The donor retains its complete function and its existing local names.

Prerequisite verification:

- `./build.sh` on both files: 16/16 rows exact, including all seven funclet
  rows, the parser data row, string references and floating-point literal.
- Both declared-unmatched checks pass.
- Link previews: seed LINKS 265 -> 265 B; donor LINKS 343 -> 343 B.
- The supported guarded dry run now accepts the seed and onDamage donor
  together, 16 rows. It previously accepted no donors.

A separate constructor trial using the canonical header byte-matched but
introduced the unprovided DamageModule::xfer name through its vtable. The
trial was reverted and logged. Its loadPostProcess provider landed after
the index. The remaining constructor, Xfer, deleting-wrapper and module-data
destructor donors still need separate reconciliation; the latter fails bytes
under the seed flags. No census gain is claimed.

Applied merge and publication audit:

- `tu_skeleton.py --merge` absorbed the onDamage donor into the approved
  `Code/GameEngine/Source/GameLogic/Object/Die/CallHelpOnDamage.cpp`.
  Source files decrease by one. All seven moved ledger rows, the destructor
  fold-proof token, six existing TU-map source cells and the DamageInfo
  header-queue source/accept command follow the TU. The map was rebuilt in
  memory; the committed diff contains only source-cell repointing.
- Final `./build.sh`: 16/16 exact rows, one verified data row, seven funclet
  pins, one string literal and one floating-point literal. Frozen-source,
  CSV and whitespace checks pass. Link preview: LINKS, 608 authored bytes,
  equal to the previous 265 + 343 bytes. This is preservation, not census gain.
- Compared the final object with snapshots of both prerequisite objects:
  all 37 external definitions and 36 COMDAT digests/sizes match their union;
  the 36 external references, five weak bindings, seven alias routes and
  empty forced-include sets are identical. No removed provider or changed
  selected body requires consumer repair. No alias was removed.
- No absorbed-source keys exist in the code-identity, data-check, gate or
  hatch baselines. Header debt was transferred by the merge tool rather
  than retired. Its MS-header refresh needs no queue changes. The existing
  private DamageInfo view still reports B1 in ownership shadow mode and
  remains attached to its transferred header-adoption queue entry.
- Audited the full pending path move before publication: searches for the
  removed basename/path across tools, hooks, workflows, source/includes,
  configuration and source registries find no active consumer. Remaining
  references are provenance comments, prior attempt evidence and the
  census-generated link_status.csv snapshot. These are retained. Existing
  BannerCarrierUpdate path changes in the outgoing ancestry were already
  audited in banner-carrier-constructor-merge-20261105-codex3.md; a fresh
  active-consumer search still finds only its provenance comment.
- Active function/data ledgers, TU-map sources and the destructor fold proof
  resolve to the current TU. Carry the combined unit into the next scheduled
  census to confirm full consumer selection; no real-link or ownership gain
  is claimed.

Remaining donors retain their separate prerequisites: constructor field/view
reconciliation without introducing DamageModule::xfer's unprovided vtable
name; deleting-wrapper EmitVtableTag declaration; leaf xfer declaration;
module-data destructor code generation under the common TU flags. Mixed
ConstIntGetters4.cpp and TailJumpWrappers5B.cpp remain untouched.
