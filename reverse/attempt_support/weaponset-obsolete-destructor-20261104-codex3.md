# WeaponSet: retire the obsolete seed destructor

Inspected source revision: `44cb098955f0263f27424b1a76b1ba41d052f78f`.
Worker: `yasinschroeder-codex3`; model: GPT-6.1.

## Target facts and repair

The native destructor is already rowed at RVA 0x002C7311, 81 bytes, in
`Code/GameEngine/Source/GameLogic/Object/WeaponSetDtor.cpp`. It derives from
Snapshot and destroys six weapons. Its unwind at 0x00776F70 is also rowed there.
The seed `WeaponSet.cpp` still defined Zero Hour's three-slot destructor,
with the different mangled identity `??1WeaponSet@@QAE@XZ`. That body emitted
its own incompatible `??_7WeaponSet@@6B@` table. Removing this duplicate donor
body leaves the native owner intact; no code row or pin changes.

The object drops only these three external definitions:

- `??1WeaponSet@@QAE@XZ`
- `??_7WeaponSet@@6B@`
- `?deleteInstance@MemoryPoolObject@@QAEXXZ`

The census touch inventory identifies six affected sources: the seed, native
WeaponSet constructor/destructor/deleter, Player.cpp and InGameUI.cpp. Current
objects in that scope have no undefined external reference to any of those
three removed names. The native constructor, destructor and deleter all keep
the vtable definition; Player and InGameUI keep the MemoryPoolObject helper.
No alternatename, pin or other link-wide alias is removed.

## Verification

- Normal `./build.sh WeaponSet.cpp` before and after: 5/5 rows exact,
  65 authored bytes. String, float and import checks pass.
- `find_declared_unmatched.py WeaponSet.cpp`: clean after the change; the
  existing admitted-definition count drops from ten to nine.
- `hatch_counters.py --update`: present-unmatched 2334 -> 2333; only the
  destructor key leaves the register. No data/identity/header debt retires.
- Index: 2026-11-04 16:16, revision `2f0cb97f52`. Current-object preview of
  the six affected sources: 5/6 LINKS, 291 -> 356 authored bytes. The seed
  changes 0 -> 65; Player (112), constructor (60), deleter (28) and destructor
  (91) retain their linked bytes. InGameUI remains 0 -> 0 on its existing
  MemoryPoolObject/BitFlags COMDAT conflicts. This is a preview, not a census.
- `link_check.py --new-variants WeaponSet.cpp`: passes.
- `check_csv.py`: passes (99,450 function rows); diff whitespace checks pass.

Logs remain under ignored build/: weaponset-seed-before.log,
weaponset-dtor-link.log, weaponset-dtor-consumer-link.log and
weaponset-dtor-variants.log. The outgoing hook performs the batch link audit;
only a current census can confirm headline progress.

## Remaining consolidation prerequisites

The seed still includes Zero Hour's WeaponSet and WeaponTemplateSet views.
Native donor views and canonical headers need reconciliation before merging;
no source path moves or TU-approval changes are part of this repair. The seed's
field table also still lacks the retail OnlyAgainst, OnlyInCondition,
ReadyStatusSharedWithinSet and DefaultWeaponChoiceCritera entries, with native
mask layout/offsets. Those data repairs remain separate work.

The local functions retained in the seed are unchanged. This repair removes a
body and introduces no local or parameter bindings to name.
