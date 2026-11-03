### PassiveAreaEffectBehavior collection and module-data composition (2026-10-28)

Status: bounded merge verified; remaining class views and census confirmation
pending. Inspected base: `e1ad17f97e`; preview index: `41c28839bf`.

The supported merge combines collection and module-data construction in the
approved provisional TU, removing one net source file. All 13 rows and both
EH graphs remain exact. All 54 original external COMDAT fingerprints remain;
the added five-byte AsciiString destructor matches an existing retail-proven
copy. The merge guard preserves both linked donors (510 authored preview
bytes). The new destination is not yet in the census, so ordinary post-merge
preview is unavailable. No new linked coverage is claimed.

The batch audit is INCONCLUSIVE: its index predates the base and affected
consumer Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry
this moved scope into the next normal census. Seven whole-file donors need
class/layout or byte-shape reconciliation; two mixed sources remain separate.
[Verification, path audit and prerequisites](../../reverse/attempt_support/passive-area-consolidation-20261028-codex.md).

2026-10-30 (claude2): the seed now declares the module hierarchy and the
Object/module-data read views (c71c398a38). `tu_skeleton.py --merge` absorbed
Pulse, PoolKey and Xfer: 20 rows, `./build.sh` 20/20 matched, the
`$L310` pool-key funclet was verified past the renumbering, and the guard kept
`?$S1`. Still separate: Ctor and Dtor, whose merge guard says the merged
object "breaks another unit's copy of ??_7PassiveAreaEffectBehavior@@6B@" and
`@@6BBehaviorModuleBase@@@`. The seed's slots 1, 2 and 5-12 are pure
placeholders, so its vftable would not match the census copy. Naming
those slots' shared base bodies is the prerequisite. Update (/O1 /Ob1) and
ModuleDataDtor (Snapshot-derived view) do not compile in the seed. Carry
the merged TU into the next census.
