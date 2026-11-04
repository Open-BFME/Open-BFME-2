# TransitionDamageFX view reconciliation

Inspected `d6e57b77c0`, 2026-11-04. Scope: the approved
`Code/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX.cpp` TU and
its four remaining unmixed donors. The current map is rebuilt in memory by
`tu_skeleton.py`; no regenerated map is committed.

`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Damage/`
and `tu_skeleton.py --plan` identify 75 approved rows, five files including
the seed, and seven mixed donors. Every candidate passes the frozen-file check.
Scoped searches found no data/identity/hatch keys to retire for the changed
donor; no files or rows are removed or moved.

## Applied record alignment

`tu_views.py .../TransitionDamageFX.cpp --class Rva004BA1D0 --no-merge-check`
aligns the map-load donor with the seed's existing declaration. Compiled
field offsets/sizes are +0/4, +4/12, +0x10/4, +0x14/12 and +0x20/12.
Existing seed field names replace the donor's names; the seed's signed int
spelling replaces unsigned int at +0. This verifies the emitted accesses,
not a recovered native class name or proof that other record types are aliases.

`./build.sh .../TransitionDamageFX_mapLoadPostProcess.cpp` passes all five
rows, both pinned unwind labels and its float reference; the subsequent
frozen-file check passes. `link_check.py` preserves LINKS, 339 -> 339 bytes,
against census 2026-11-04 22:40 at `3a95b274a2`. This is a preview, not a
census or real-link coverage gain.

## Canonical DamageInfo adoption

The seed's queued adoption failed because its local `getDamageTypeFlag`
accepted DamageType while the canonical `DamageInfo::m_damageType` is int.
The seed now includes `Code/GameEngine/Include/GameLogic/Damage.h` instead
of declaring a private DamageInfo body, and the helper accepts int.
`./build.sh .../TransitionDamageFX.cpp` verifies 58/58 rows, 13 unwind pins,
28 literals plus two empty-string references, and five named imports.
The frozen-file check passes. `header_adopt_lane.py accept --class DamageInfo`
then passes its own byte/link retirement guard and removes exactly this
unit's queue row. No other header debt is retired; no canonical header changes.

## Merge trials and next checks

Both supported `tu_skeleton.py --merge .../TransitionDamageFX.cpp --dry-run`
trials accept zero donors. Before alignment, the map-load merge cannot find
`m_objectID`/`m_subObjects`. After alignment it reaches this distinct conflict:

```
error C2664: 'void _STL::vector<_Tp>::push_back(const _Tp &)':
cannot convert parameter 1 from 'Rva004BA1D0' to 'const Rva004BA1C8 &'
```

The other refusals remain: ModuleDataDestructorThunk reports `compile:`
without a diagnostic; Rva004BA399EraseRange loses bytes;
Behavior/TransitionDamageFXDtor loses its census-linked status because the
merged object selects `??1DamageModule@@UAE@XZ`. The link guard identifies
all five original files as census-linked. No merged source is retained.

Next: establish the native relationship and copy/destructor contracts of
Rva004BA1C8 and Rva004BA1D0 before changing the vector identity. An ICF-folded
destructor and equal record sizes alone do not prove a shared type. Reconcile
the outer TransitionDamageFX/Object views and the DamageModule destructor
provider before retrying their donors. The record alignment removes one
compiler obstacle but does not satisfy the consolidation pass test.
