# CurseSpecialPower consolidation prerequisite

Inspected 2026-11-04, starting at `0201cbc134` after the runner rebased the
verified class-view prerequisite (original local commit `66df6dc25f`).

Scope: `Code/GameEngine/Source/GameLogic/Object/Update/CurseSpecialPower.cpp`
and its one clean donor, `SpawnPointProductionExitUpdateCtor.cpp`.

The planner reports unresolved placement because the committed TU map is stale.
`tu_skeleton.py --merge ... --dry-run` rebuilds the map in memory and approves
the constructor at 0x004CCD7F for this provisional TU. Three other sources are
mixed and remain outside the merge. No map or ledger was rewritten.

The first trial failed to compile: the pool-key owner's minimal class lacked
the constructor and its opaque 0x88-byte base. The prerequisite adopts the
constructor owner's existing base layout and constructor/destructor declarations.
`./build.sh CurseSpecialPower.cpp` passes all five unique code bodies, one data
row, literal/import checks and the parent EH graph (EXACT); the declaration
check passes. `link_check.py CurseSpecialPower.cpp` reports LINKS, retaining
153 census-linked bytes (census 2026-11-04 05:53 at `5a13f2cd61`). This is a
preview, not a new census.

The second merge trial compiles but refuses the changed first-selected COMDAT
`??_7CurseSpecialPower@@6B@`. This is a real remaining reconstruction mismatch,
not a false reject. The combined minimal class declares the destructor then
getModuleNameKey, putting the latter at slot 1. Target bytes from game.dat
SHA-256 `f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`
at vtable VA 0x00C5F850 instead give these code RVAs:

| Slot | RVA | Current ledger identity |
| --- | --- | --- |
| 0 | 0x004CCE30 | CurseSpecialPower scalar deleting destructor |
| 1 | 0x00483CEF | Rva00483CEF::rva00483CEF (nonvirtual spelling) |
| 2 | 0x004CCDB0 | Rva004CCDB0Get (free-function spelling) |
| 3 | 0x004CE0BE | Rva004CE0BE::xfer |
| 4 | 0x004CCDEB | CurseSpecialPower::getModuleNameKey |

The ledger spellings alone do not prove the true declaring classes of slots
1-3. Recover those inherited slot declarations and their provider identities
before retrying the merge. Both original files and every row remain; no source
path, alias, hatch or debt key was removed. No source-file reduction is claimed.
