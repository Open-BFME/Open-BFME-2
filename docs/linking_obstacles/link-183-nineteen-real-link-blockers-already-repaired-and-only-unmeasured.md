### LINK-183: nineteen real-link blockers are already repaired and only unmeasured
Status: Repair landed / awaiting verification, for the 23 units named below only. Updated: 2026-11-03; inspected revision: `a7bdf8e7ab9` (master `e514a012436`).

Evidence / affected units: `reverse/exit_link_blockers.tsv` lists 93 units from the real link
at `d0b9cc5d27c08aa18ab5eefa25da59d7f45446fc`. Re-running `tools/link_check.py` over all 93 on
current master, against the published index of **2026-11-03 20:03 at `8661f15284`**, reports
23 of them linking cleanly and the list's aggregate rising from 10,580 to 12,786 bytes
(39.8s, `0 of 93` would have been the previous reading for most of them). Four of the 23 were
already at parity in the census and are listed for completeness; the other 19 move from zero:

    Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankTruckDraw.cpp        0 -> 103
    Code/GameEngineDevice/Source/W3DDevice/GameClient/HeightMap.cpp                            0 -> 107
    Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogic.cpp                       0 -> 145
    Code/GameEngine/Source/Common/R5VectorDtorEHFramedPolymorphic.cpp                          0 -> 27
    Code/GameEngine/Source/Common/R5VectorDtorEHFramedPolymorphic_Rva005de870.cpp              0 -> 93
    Code/GameEngine/Source/Common/RTS/Player.cpp                                               0 -> 112
    Code/GameEngine/Source/Common/System/CDManager.cpp                                         0 -> 54
    Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu.cpp            0 -> 65
    Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp       0 -> 98
    Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp              0 -> 23
    Code/GameEngine/Source/GameClient/System/FXParticleSystem/ModuleCtorChainsA.cpp            0 -> 740
    Code/GameEngine/Source/GameLogic/Object/Behavior/FlightDeckBehavior.cpp                    0 -> 35
    Code/GameEngine/Source/GameLogic/Object/Body/BodyModuleCtor.cpp                            0 -> 125
    Code/GameEngine/Source/GameLogic/Object/Update/HelicopterSlowDeathUpdate.cpp               0 -> 22
    Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdate.cpp                           0 -> 16
    Code/GameEngine/Source/GameLogic/Object/Weapon.cpp                                         0 -> 217
    Code/Libraries/Source/WWVegas/WW3D2/dynamesh.cpp                                           0 -> 113
    Code/Libraries/Source/WWVegas/WW3D2/shattersystem.cpp                                      0 -> 133
    Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva005de9c4_ctor.cpp                    0 -> 31
    Code/GameEngine/Source/Common/Rva007B6880Thunks.cpp                                 8,968 -> 8,968
    Code/GameEngine/Source/Common/RvaCountNoteRunFamily.cpp                                 606 -> 606
    Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIArmyUnitSwapperValidation.cpp  444 -> 444
    Code/Libraries/Source/WWVegas/WWLib/StlportTreeKeyRangeVector.cpp                       509 -> 509

Completed: nothing was edited. The repairs these units needed are already on master; what was
missing was a current measurement. The cause of the confusion is worth recording because it
wastes seat time repeatedly: a checkout's `build/link_census/link_index.pkl` is untracked, is
never refreshed automatically, and `link_check` reports the census the *index* carries, not the
newest one in `reverse/link_census_history.csv`. A worktree whose index was fetched on
2026-10-30 reports these units unresolved and names providers that demonstrably exist in the
tree, which reads like a stale census when it is a stale local file.
`python3 tools/link_check.py --fetch-index` takes seconds and is the supported refresh;
four independent seats concluded "only a maintainer-run census can clear this" on
2026-11-03 before that was checked, and a census had in fact run that day at 18:36.

Remaining / next check: these are `link_check` predictions, so they are leads, not a headline.
The picker's own pass test for an exit-link item is this check plus "the next real link stops
listing it", so confirm against the next real link (`.github/workflows/real-link.yml`,
`tools/exit_link.py --link`) and the next census before clearing any per-unit entry. Refresh
the index first in any checkout that reports one of these as unresolved. The other 70 units in
the list still do not link and keep their existing entries and prerequisites; nothing here
clears a family because one consumer links.

Clearance: pending. Prediction-only, scoped to the 23 units above against index `8661f15284`.
No linked-byte, debt or census gain is claimed.
Census confirmation: awaiting the next published census.

**The other 70 are 70 separate problems (2026-11-03):**
Grouping the same sweep's findings by missing symbol: 68 units report findings naming 343
distinct symbols, and **332 of those 343 block exactly one unit**. The largest shared cause
reaches three units (`__imp_?allocate@__new_alloc@_STL@@SAPAXI@Z`, in
`Common/RTS/ProductionPrerequisite.cpp`, `Common/Thing/ThingFactory.cpp` and
`GameNetwork/GameSpy/Thread/BuddyThread_Unresolved.cpp`), and the next ones reach two
(`__imp_?deallocate@__new_alloc@...`, `?s_objectFieldParseTable@ThingTemplate@@`,
`??0AudioEventRTS@@QAE@ABV0@@Z` and `??1AudioEventRTS@@UAE@XZ`,
`??1ArmyHeroIcon@StrategicInGameUI@@UAE@XZ`, `?crc@UpdateModule@@MAEXPAVXfer@@@Z`).
So there is no single provider whose repair unlocks a batch of the remainder: planning
should treat them as individual items, and a seat looking for leverage will not find it
here. The `__imp_` cases are not a family either — `__declspec(dllimport)` is a deliberate,
widely used device in this tree (7,503 occurrences across 2,779 sources) for suppressing a
TU's own COMDAT copy so the link keeps retail's, and an unresolved `__imp_` means one call
in that unit was not inlined after all. `ProductionPrerequisite.cpp` additionally carries
LINK-064's open retyping prerequisite. Measurement only; nothing was edited and no gain is
claimed.
