# FireWeaponWhenDamaged update interface prerequisite

Inspected base: `3d6187f250`. The supported Behavior consolidation planner and
current in-memory TU routing approve the existing FireWeaponWhenDamaged rows
for FireWeaponWhenDamagedBehavior.cpp. The earlier prerequisite handoff is
`consolidation-fireweapondamaged-prerequisite-20261026-codex.md`.

## Target evidence and repair

The constructor/destructor's scoped FireWeaponWhenDamagedView.h declared
`UpdateModuleInterface::update` as a non-pure `void` method and omitted the
derived override. Both objects consequently referenced the obsolete
`?update@UpdateModuleInterface@@UAEXXZ` name. Ordinary baseline link preview
and the merge guard report that name unresolved with index `41c28839bf`.
PartTheHeavensUpdate.cpp retains a source-level compatibility alias, but its
new consolidated path has not supplied that alias to this index.

The existing matched FireWeaponWhenDamagedBehaviorUpdate.cpp already declares
the interface as pure, returning UpdateSleepTime, and declares/defines the
derived override at RVA `0x00482B24` (149 bytes). Retail's constructor-selected
interface table at VA `0x00849594` starts with VA `0x00882B24`, followed by
`0x00653376`. Thus the first slot names that existing derived body. The repair
uses those existing declarations in the scoped constructor/destructor view.
No donor-layout inference or complete interface-table recovery is claimed;
the second slot remains outside this one-slot view.

## Verification

- Ordinary before/after `./build.sh` on both consumers: 4/4 rows exact,
  including EH, with all reference checks passing. Both declaration scans
  report every body matched. Two EH parent graphs remain EXACT; the compiler's
  local funclet-label renumbering is accepted through the existing graph.
- Strict `link_check.py --prepare-current` receipts pass for both sources.
  Paired ordinary preview now reports LINKS, 596 and 234 authored bytes.
  The paired `--new-variants` check exits zero with no finding. These are
  predictions, not new census coverage.
- COFF comparison preserves every external definition and weak binding.
  Each object's only external-reference change replaces the obsolete base
  void method with the existing derived UpdateSleepTime method. The only
  external COMDAT change is the four-byte UpdateModule interface table:
  its offset-zero DIR32 referent changes accordingly, from digest
  `9eac165d0192` to `6ac145d89966`. All other external COMDATs are identical
  (ten in the constructor object, six in the destructor object).
- Shadow data: two sources, zero findings. Converged data: eleven addresses,
  zero second names or unjudged rows. Class gate accepts the scoped header.
  Neither consumer nor header has a gate, identity, data, header or hatch
  register entry to retire. No pin, alias, ledger row or compiler flag changes.

Scratch receipts live under `build/fireweapondamaged-b4/`, including original
objects, `prerequisite-object-delta.json`, `prerequisite-reference-delta.json`
and `prerequisite-eh.json`.

## Remaining consolidation boundary

The supported post-repair dry run still accepts no merge. Its singleton
trials compare a corrected table against the other object's old census copy
and refuse `comdat ... (first)` or `breaks another unit's copy`. The index has
exactly those two old copies, both with digest `9eac165d0192` and no retail
verdict. The paired current-source preview and new-variants check pass, but
that does not prove the complete merged object. No guard override, census
rewrite or manual composition is attempted. Carry both corrected consumers
into the next scheduled census, then retry the supported merge.

The update donor also retains private-view reconciliation errors (C2504:
UpdateModule undefined). Pool/xfer methods, mixed donors and the Libraries
allocator-specialization provider remain separate prerequisites. This commit
removes no source files and retires no registered debt. No census-linked or
image-ownership gain is claimed.

## Outgoing batch audit

The pending range starts at origin/master `840db2d676` and includes the earlier
ScriptGroup cleanup and INIAudioEventInfo predicate absorption. This repair
adds no source-path moves. The combined path-consumer search was repeated for
the removed predicate basename and Common/Thing directory across active tools,
hooks, workflows, source includes, build files, ledgers, registers and queues.
The basename remains only in provenance/historical evidence; Common/Thing
tool references are unaffected test fixtures. No active consumer needs a path
change. The earlier audio handoff retains its composition/register/queue audit.

Eight explicit current providers/consumers pass strict preparation together:
462/462 rows, two data rows, 37 string, 42 float and 106 import references.
This refreshes the earlier handoff's missing CreateAHeroManager consumer
receipt as well as the audio destination. No census/index/status is changed.

The staged-tree batch audit remains INCONCLUSIVE: index `41c28839bf` predates
the outgoing base, and the next affected consumer,
`Code/GameEngine/Source/Common/AIHarvestPrepareSiteState.cpp`, lacks a current
receipt. The refreshed eight-source checks do not establish full batch
closure. Carry this consumer and the earlier audio handoff's measurement
prerequisites into the next normal census; no census or runtime run is started.
