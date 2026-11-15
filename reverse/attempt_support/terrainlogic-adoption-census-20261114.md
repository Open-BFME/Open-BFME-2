# Why all 25 queued TerrainLogic units refuse the canonical header

`next_work.py --claim` serves TerrainLogic class-header adoption (25 of 47
queued units). Every one fails, and they fail in six distinct ways, not one.
This is the triage, so the next seat picks a category rather than a unit.

Run as three `adopt --apply` batches over the 25; the tree is unchanged
(`adopt` reverts its trial).

| category | units | what the tool says |
| --- | ---: | --- |
| **A. a method the canonical header does not declare** | 9 | `C2039: 'X' is not a member of 'TerrainLogic'` |
| **B. a field the unit spells differently** | 6 | `field renames: …` |
| **C. a header or shim redefinition** | 4 | `C2011` / `C2953` |
| **D. a method missing from another class's header** | 2 | `C2039` on `Coord3D` |
| **E. a byte or data row fails** | 3 | `FAIL <row>` / `Data rows: FAIL 1 of 1` |
| **F. no private view** | 1 | `no private view found` |

## A. Nine methods that exist only in the private views (9 units)

| unit | method |
| --- | --- |
| `AITargetHeuristicExpansionBase.cpp:196` | `findWaypoint` |
| `Rva0055A246Ctor.cpp:254` | `getHighestAlongLine` |
| `ScriptActions_doNamedFireSpecialPowerAtWaypoint.cpp:60` | `v34` |
| `System/Radar.cpp:1303` | `queryWater` |
| `Map/FireLogicSystemObjects.cpp:340` | `materialAt` |
| `MineshaftPortalBehaviourLinkStep.cpp:72` | `portalAt` |
| `Weapon_isClearGoalFiringLineOfSightTerrain.cpp:42` | `v15` |
| `ScriptEngine/Rva003BCAF6Do.cpp:17` | `s34` |
| `ScriptEngine/Rva003C4DC2Do.cpp:70` | `getHead` |

**None of the nine is rowed** — `grep -c '?<name>@' reverse/functions.csv` is 0
for every one, against TerrainLogic or any class. They are helpers each unit
invented in its own private view, and three of them (`v34`, `v15`, `s34`) are
decompiler spellings that `name_metric` already calls placeholders.

So these are not missing from the canonical header; they should not be in it.
Each unit needs its call reconciled with a real TerrainLogic member — which is
per-unit work on the call site, not on the header.

## B. Six field disagreements, and the header is the weaker side (6 units)

| unit | the unit says | the canonical says |
| --- | --- | --- |
| `TerrainLogicCtor.cpp`, `TerrainLogicDeleter.cpp` | `m_30` : `vector<int>` | `field30` : `vector<ICoord2D>` |
| `Map/TerrainLogic.cpp` | `m_waypointsByID` : `map<uint, void *>` | `field56C` : `map<uint, Waypoint *>` |
| `Map/TerrainLogicXfer.cpp` | `m_waterToUpdate` : `WaterToUpdate[1280]` | `field68` : `TerrainLogic::DynamicWaterEntry[1280]` |
| `Map/TerrainLogicRva00283CE7.cpp` | `first` at +0x578 | no canonical field at that offset and size |
| `Map/W3DTerrainLogic.cpp` | `m_30` at +0x30, 0 bytes | no canonical field at that offset and size |

Worth noting before anyone "fixes" the units: **the canonical header carries 12
`fieldNNN` placeholder names** (`field18`, `field1C`, `field20`, `field24`,
`field28`, `field2C`, `field30`, `field44`, …) where the units carry readable
ones (`m_waypointsByID`, `m_waterToUpdate`, `m_activeBoundary`). `name_metric`
classes `fieldNNN` as a placeholder, so for these the adopting units are better
named than the header they are being asked to adopt, and the rename check
refuses on the difference.

The element types cut both ways and each needs its own evidence: canonical
`map<uint, Waypoint *>` is more specific than the unit's `map<uint, void *>`,
while the unit's `WaterToUpdate` and the canonical's
`TerrainLogic::DynamicWaterEntry` are two names for the same 20-byte record
(the header's own facts comment reads "+68 sixty-four 20-byte water records").

## C. Four redefinitions (4 units)

| unit | clash |
| --- | --- |
| `ParticleSystemFXNuggetReallyDoFX.cpp`, `StrafeAreaUpdate_update.cpp` | `StringBase` template already defined (`reference/shims/bfme2_ascii/string_base.h:188`) |
| `Map/TerrainLogicBeaconPathPoint.cpp` | `Coord3D` class type redefinition |
| `FlammableUpdateDtor.cpp` | `SubsystemInterface` class type redefinition (`…/subsystem/SubsystemInterface.h:14`) |

**Corrected after investigating it.** My first read was that one include guard
in TerrainLogic.h would clear all four. It would not, and acting on that would
be wrong.

The mechanism: TerrainLogic.h includes the *canonical* header for each of these
types, while the unit already has a *shim* definition of the same type under a
different guard, so both land.

    Code/Libraries/Source/subsystem/SubsystemInterface.h   #ifndef CANONICAL_SUBSYSTEMINTERFACE_H
    reference/shims/sweep/Common/SubsystemInterface.h      #ifndef __SUBSYSTEMINTERFACE_H_

`FlammableUpdateDtor.cpp`'s `// cl:` line carries `/Ireference/shims/sweep`, so
it reaches the second. The same holds for the others: `Coord3D` is defined in
three `Code/Libraries/Include/Lib/` headers and in
`reference/shims/pathfind/GameLogic/AIPathfind.h` and
`reference/shims/bfme2_bridgebehavior/Lib/BaseType.h`; `StringBase` in four
shims including `bfme2_ascii/string_base.h`.

TerrainLogic.h does guard this way for Snapshot — line 12 tests the *shim's*
`__SNAPSHOT_H_` — and does not for SubsystemInterface, which tests only
`CANONICAL_SUBSYSTEMINTERFACE_H`. That asymmetry is what made a guard fix look
right.

It is not, because **the two definitions are not interchangeable**. The
canonical class declares `SubsystemInterface()`, a virtual destructor and, under
`BFME_SUBSYSTEM_SLOTS`, a specific slot order (`init` pure,
`loadIniFilesFromLegend`, `postProcessLoad`, `vslot04`…`vslot08`). The shim is
ZH's verbatim GeneralsMD header with ZH's virtuals, and its own comment records
that retail has three extra stub virtuals at slots 6-8 for ~113 vtables but not
in the Display branch. Guarding the include so that whichever arrives first
wins would give TerrainLogic a different base vtable depending on the unit,
which is the thing the canonical lane exists to prevent.

So category C is an **adoption-ordering dependency**: these units cannot adopt
canonical TerrainLogic until they stop taking SubsystemInterface, Coord3D and
StringBase from shims — that is, until those classes are adopted in them first.
Not a header bug, and not a quick win.

## D. `Coord3D::add` is rowed and its canonical header omits it (2 units)

`AIStatesBfmeOnExit.cpp:863` calls `Coord3D::add` and
`PathfinderAttackView.cpp:89` calls `Coord3D::assign`.

These differ from category A: `?add@Coord3D@@QAEXPBUCoord3DBase@@@Z` **is** a
matched row, 49 bytes at `0x000F0E3B`, owned by
`Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp`. The canonical
`Code/Libraries/Include/Lib/Coord3D.h` declares a sibling of the identical
shape, `void set(const struct Coord3DBase *p);`, and no `add`.
(`Coord3D::assign` is unrowed, so it belongs in category A.)

`Coord3D.json` has no `methods` key — a canonical header's members come from
`special_declarations` reading the **views**, so the route is for `add`'s owner
or a view to declare it, not a contract edit and not a hand edit of a generated
file.

## E, F. Four that are not header problems

`ActionManagerSpecialPowerChecks.cpp` fails a row byte-match;
`Map/FireLogicSystem.cpp` and `MineshaftPortalBehaviour.cpp` each fail
`Data rows: FAIL 1 of 1`; `System/TBuff.cpp` has no private view to replace.
These fail before the header is reached.

## Suggested order

1. **D (1 unit)** — get `Coord3D::add` declared through its owning view. The
   smallest, and the only one with a matched row already proving the member.
2. **B (6 units)** — needs a decision on the `fieldNNN` placeholders first;
   renaming the canonical fields is naming-lane work and changes the header for
   every adopter, not just these six.
3. **A (9 units)** — per-unit call-site reconciliation, the largest and least
   shared, but each unit is independent.
4. **C (4 units)** — blocked behind adopting SubsystemInterface, Coord3D and
   StringBase in those units. Largest dependency, least tractable here.
5. **E, F (4 units)** — not this lane.

C was first in an earlier revision of this note, on the mistaken reading above.

## Reproducing

    python3 tools/header_adopt_lane.py adopt --class TerrainLogic \
      --header Code/GameEngine/Include/GameLogic/TerrainLogic.h --apply <units>

The "not rowed" claims are `grep -c '?<name>@TerrainLogic@@'` and
`grep -c '?<name>@'` over `reverse/functions.csv`; the placeholder count is
`grep -cE '^\s+\S+ field[0-9A-F]+'` over the header.
