# Retire 11 verified GameWindowManager header queue entries

Base: `c57f946795d410d895717e247fbbc619b9415b70`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 281 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameClient/GameClientDisplayModeChange.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 3 |
| `Code/GameEngine/Source/GameClient/InGameUIRemoveIdleWorker.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 2 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/ControlBarSystem.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 14 |
| `Code/GameEngine/Source/GameClient/InGameUIIdleWorker.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 9 |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction_Rva0053E4B1.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 3 |
| `Code/GameEngine/Source/GameClient/InGameUIUpdate.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 5 |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 19 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchPlayerTooltip.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 18 |
| `Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 86 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 97 |
| `Code/GameEngine/Source/GameClient/MessageStream/CommandXlat.cpp` | `Code/GameEngine/Include/GameClient/GameWindowManager.h` | 25 |


Rebase check at `69b9167a29361ccd904f460cada2c9dde29e59b4`. The owning tool retires 0 entries on this parent. 11 already left the queue in earlier work. 0 remain open after the recheck.
