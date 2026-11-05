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

## Committed-repair audit follow-up

Repair commit: `b09b6cab89`. After stopping the optional old-seed merge trial
(no verdict and no applied move), `link_check.py --prepare-current WeaponSet.cpp`
passes: all five rows have strict reusable receipts. The committed batch audit
(`--base b09b6cab89^ --tip b09b6cab89`) remains **inconclusive**, not clean:
the index at `2f0cb97f52` predates the outgoing base, so its provisional
since-index scope reaches `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`,
which lacks a current receipt. Log: `build/weaponset-dtor-committed-audit.log`.
The six-source preview above is the bounded evidence for this repair; the
publisher's hook and the next census still decide wider link retention.

The supported consolidation planner completed at
`build/consolidation/weaponset`; its `--check` passes. Its WeaponSet packet flags
stale committed TU-map inputs, duplicate class views, compiler-setting
conflicts and path-keyed data/hatch registers. Placement alternatives remain
hints until current TU routing is rebuilt and corroborated. This repair neither
approves a placement nor removes a source file. A future merge must refresh the
planner and reconcile these prerequisites before running `tu_skeleton.py`.

## Consolidation dry-run follow-up (2026-11-05)

The allocated WeaponSet trial (`tu_skeleton.py --merge WeaponSet.cpp --dry-run`)
accepted no donors and reports `blocked: no verified merge of two or more
donors`. The tool found `WeaponSet.cpp`, `WeaponSetCtor.cpp`,
`WeaponTemplateSetParse.cpp`, `WeaponSetIsOutOfAmmo.cpp`,
`WeaponSetRvaSlotSearch.cpp`, `Rva002C7474Loop.cpp`, `BitFlags218Any.cpp`,
`WeaponSetDeleter.cpp`, `WeaponSetRva002C75D1.cpp`, `Rva002C777EBuild.cpp`,
`WeaponSetSetWeaponLock.cpp`, `Rva002C8754.cpp` and `WeaponSetDtor.cpp`
census-linked. Rejected donors need manual prerequisite work: repeated class
redefinitions (`Weapon`, `WeaponSet`, `AsciiString`, `Coord3D`, and others),
`WeaponSlotType` assignment mismatches, missing class members, `BitFlags`
template disagreement, and the obsolete destructor's byte mismatch. No donor
or source was changed. The existing clear-provider and obsolete-destructor
findings remain; no link clearance or census gain is claimed.
