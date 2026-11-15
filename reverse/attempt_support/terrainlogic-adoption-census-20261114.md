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

TerrainLogic.h includes `SubsystemInterface.h`, a Snapshot shim and
`Coord3D.h`, each behind its own `#if !defined(...)` guard pair. These four
units already reach those types another way, so the include lands a second
definition. This is the one category that looks like a header-side fix:
the guards admit a second definition when the other path defined the type under
a different macro.

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

1. **C (4 units)** — one include-guard fix in TerrainLogic.h may clear all
   four, and it is the only category whose repair is in the header.
2. **D (1 unit)** — get `Coord3D::add` declared through its owning view.
3. **B (6 units)** — needs a decision on the `fieldNNN` placeholders first;
   renaming the canonical fields is naming-lane work and changes the header for
   every adopter, not just these six.
4. **A (9 units)** — per-unit call-site reconciliation, the largest and least
   shared.
5. **E, F (4 units)** — not this lane.

## Reproducing

    python3 tools/header_adopt_lane.py adopt --class TerrainLogic \
      --header Code/GameEngine/Include/GameLogic/TerrainLogic.h --apply <units>

The "not rowed" claims are `grep -c '?<name>@TerrainLogic@@'` and
`grep -c '?<name>@'` over `reverse/functions.csv`; the placeholder count is
`grep -cE '^\s+\S+ field[0-9A-F]+'` over the header.
