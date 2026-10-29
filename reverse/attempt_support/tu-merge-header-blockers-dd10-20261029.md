# TU-merge and header blockers found by worker dd-10 (2026-10-29)

Target facts only; no donor claims. Every diagnostic below is the compiler's own
output from `tools/tu_skeleton.py --merge TU --dry-run` on `origin/master`
286d810c88, and the byte-gate results are `./build.sh` on that tree.

## Consolidation merges blocked by private class views

Three approved TUs that the consolidation queue ranks as unheld were dry-run in
the fleet sandbox. None merged a single donor, so none was applied.

| TU | donors | `--dry-run` result |
|---|---|---|
| `Code/GameEngine/Source/GameLogic/AI/AIGroup.cpp` | 45 files, 97 rows | `accepted: []`, 34 rejected, `blocked: no verified merge of two or more donors` |
| `Code/GameEngine/Source/GameNetwork/LANAPI.cpp` | 27 files, 97 rows | `accepted: []`, 21 rejected |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/GateOpenAndCloseBehavior.cpp` | 14 files, 42 rows | not run: claimed for dd-10 and released after the two above showed the same shape |

The shape is uniform: each donor fragment declares its own partial view of the
class it implements, and the seed's view is narrower, so a donor body composed
into the seed fails to compile:

- `error C2039: 'm_head' : is not a member of 'AIGroup'` (and `m_memberList`,
  `m_dirty`, `m_gameStartTime`, `m_lobbyPlayers`, `m_isActive`)
- `error C2039: 'groupDoCommandButtonAtPosition' : is not a member of 'AIGroup'`
  (and `RequestLocations`, `ResetGameStartTimer`, `removePlayer`, `setIsActive`,
  `init`, `getSpeed`, `add`, `xfer` on their own classes)
- `error C2061: syntax error : identifier 'CommandSourceType'` — the enum the
  seed never declares
- `error C2143: syntax error : missing ';' before '*'` for `TheAI`,
  `AIUpdateInterface::AICommandInterface`, `LANGameInfo`
- `error C2039: 'rva0028AC4E' : is not a member of 'Object'` and
  `'isAnyKindOf' : is not a member of 'Object'` — the Object view gap

`tools/tu_views.py <TU> --dry-run` is the documented reconciliation, but on
AIGroup it reports conflicts rather than a mechanical superset: `AI`,
`AIUpdateInterface`, `AICommandInterface`, `ThingTemplate`, `AI`,
`TerrainLogic`, `Pathfinder`, `SimpleObjectIterator` and `Path`/`PathNode` are
all `unterminated definition`, `ProductionUpdateInterface` differs in virtual
slot 0 (`s00()` vs `unusedSlot00()`), `CommandButton` names `m_command` at both
+0x10 and +0x14, and `Coord3DCopy::Coord3DCopy` has two different inline bodies.
`Thing` itself is canonical-header work (`header_adopt_lane.py accept --class
Thing`), so this TU waits on the header lane, not on a merge.

Consequence for the lane: these TUs are "blocked by classes" in
`docs/consolidation.md`'s sense, and the header tier is the prerequisite. A seat
that wants file-count progress from consolidation should prefer a TU whose
donors share one view (a split, or a TU whose fragments were carved from one
file), not one of the large unheld TUs above.

## Header adoption that is an ABI decision, not a mechanical swap

`Coord2D` (`Code/Libraries/Include/Lib/Coord2D.h`, variant `data+methods`) cannot
adopt two of its four queued units without a contract change:

- `Code/GameEngine/Source/GameClient/GUI/AnimateWindowGetVel.cpp` declares
  `struct Coord2D { Coord2D() {} Coord2D(const Coord2D &other) : x(other.x),
  y(other.y) {} float x; float y; };` — a user copy constructor. The canonical
  header has none, so the hidden-result ABI changes and the row FAILs.
- `Code/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowRightFastInitReverse.cpp`
  states the same in its own header comment: "Its matched source uses a
  memberwise copy constructor, unlike the ZH header", and works around it with
  `#define Coord2D ZHTrivialCoord2D` plus a local `~Coord2D() {}`.

The canonical header's own comment records `sizeof 8 (zh)`, i.e. the contract is
the Zero Hour one. Retail's Coord2D in these units is nontrivial (copy ctor and
empty dtor both rowed), so adopting the header needs `reverse/class_contracts/Coord2D.json`
re-decided first — a class-contract job, not a codemod.

## ms-headers: the `throw()` on a local declaration is load-bearing

`repair_queue.py ms-headers` calls these "drop-in" on declaration equality, but
the byte gate refuses two of them:

- `Code/GameEngine/Source/GameNetwork/NetPacket.cpp`: replacing
  `extern "C" void *__cdecl memcpy(...) throw();` and
  `extern "C" unsigned char *__cdecl _mbscpy(...) throw();` with
  `<string.h>`/`<mbstring.h>` changes the register allocation and stack frame of
  four rows (`?FillBufferWithRequestGameSpyStatsAuthKeyCommand@NetPacket`,
  `?FillBufferWithGameSpyStatsAuthKeyCommand@NetPacket`,
  `?rva0058E8EARequestFrameData@NetPacket`, `?rva0058F5E3TimeOutStart@NetPacket`).
- `Code/GameEngine/Source/GameLogic/Object/Update/WallUpgradeUpdate.cpp`:
  replacing `extern "C" void *memset(...) throw();` with `<string.h>` changes
  `?rva004AB57E@WallUpgradeUpdate` (the nothrow declaration keeps different
  registers live across the calls).

`Code/Libraries/Source/Apt/AptDate.cpp` did adopt cleanly (its two local
declarations carried no `throw()`), which is why it is the one ms-headers commit
in this batch.
