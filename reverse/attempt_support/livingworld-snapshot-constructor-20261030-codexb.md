# LivingWorld constructor Snapshot adoption

Inspected base: `904c5b5d55`, 2026-10-30. The default picker claimed
`class:Snapshot`; the two constructor sources and canonical header were also
claimed before editing. This resolves the two constructor prerequisites in
LINK-098, not the separate LivingWorld class/provider reconciliation.

## Target evidence and chosen surface

Retail LivingWorldBattle constructors at RVA 003F6A3A (81 bytes) and
003F6F0D (243 bytes), and LivingWorldBuildPlot at 004FC807 (172 bytes), call
the list-base constructor at 00330757 without first storing Snapshot's vptr.
The calls are at 003F6A41, 003F6F27 and 004FC822 respectively. The latter two
establish unwind state zero before that call. Their state-zero funclets at
0078416C and 007936DB each load the saved object and jump to 0049B47C.
That existing Snapshot destructor stores table 00BBB554 and returns
(`c7 01 54 b5 bb 00 c3`, seven bytes). Its real provider remains
`Common/System/Snapshot.cpp`; no new provider, alias or pin is introduced.

These are target code/lifetime facts, not donor facts or original-syntax proof.
The previous private views already selected an inline empty imported
constructor, novtable class and out-of-line destructor. The canonical header
now offers that surface through `BFME_SNAPSHOT_CONSTRUCTOR_ONLY`, selected
only by these two constructor units. Its default surface retains the inline
destructor and ordinary vptr emission for existing users. The novtable option
is a verified code-generation choice; no original declaration syntax is claimed.
The two complete private Snapshot definitions and their waivers are removed.

## Verification and retirement

Before and after, `./build.sh` verifies all 12 rows in the two sources.
`eh_verify.py` reports two EXACT graphs, zero baseline and zero missing.
Declared-unmatched checks pass. Saved pre-edit objects were compared with the
current objects: all 32 Battle and 12 BuildPlot normalized COMDAT fingerprints
(bytes/relocations), their 48 and 28 external symbols, references and weak
aliases are identical. Strict `link_check.py --prepare-current` receipts pass
all 12 rows. Scratch native disassembly, saved objects and dependent inventory
are under ignored `build/snapshot-livingworld-codexb/`.

Ordinary previews before adoption preserve LINKS for 362 Battle and 182
BuildPlot authored bytes against index `85f6b7f40c` (2026-10-29 15:08).
The owning `header_adopt_lane.py accept --class Snapshot` passes both after
adoption, including its ordinary link guard, and retires exactly two queue
rows. `hatch_counters.py --update` removes exactly their two class-gate keys,
reducing that hatch count from 38 to 36. No ledger source, data owner or
function extent changes. No new linked-byte or census result is claimed.

The shared-header dependent selector identifies 1,497 ledger sources; the
normal commit hook must verify that complete selected set. The two remaining
Snapshot queue rows are MoneyVectorPushBack's distinct-record identity
(LINK-092) and FXParticleSystem's unresolved real info virtual surfaces.
BuildPlot's separate placeholder class/observer/provider reconciliation also
remains open; constructor header adoption does not establish its completion.

## Outgoing batch boundary

The complete pending batch also contains the earlier IngameNoticeDisplay
merge and handoff. Its single reset-source absorption is reaudited against
`origin/master` at `207b0a3db6` through `904c5b5d55` plus this staged adoption.
Combined old-path, basename and directory searches cover tools, hooks,
workflows, source includes, build inputs, docs and active ledgers/registers.
No active consumer requires an update. Old mentions are provenance comments,
historical link/name records and attempt evidence; the unrelated invented-name
test fixture under the same directory does not name the absorbed source.
The earlier consolidation handoff retains its debt/queue/provider audit.

The merged destination is refreshed through strict `--prepare-current` and
still passes all 22 function rows and two data rows. The complete staged batch
link audit remains INCONCLUSIVE: index `85f6b7f40c` predates the outgoing base,
and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. This is the prior merge's recorded consumer boundary, retained for
the next scheduled census. Broader consumer closure remains unverified.
