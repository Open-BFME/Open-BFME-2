# Retire 3 verified Display header queue entries

Base: `e1671b783ff3211d3246d285eb5ca61f22671b65`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 39 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMainMenuCallbacks_ExitGame.cpp` | `Code/GameEngine/Include/GameClient/Display.h` | 12 |
| `Code/GameEngine/Source/GameClient/InGameUIPostDraw.cpp` | `Code/GameEngine/Include/GameClient/Display.h` | 11 |
| `Code/GameEngine/Source/GameClient/GUI/AptSpellStore.cpp` | `Code/GameEngine/Include/GameClient/Display.h` | 16 |

This scope replaces entries excluded from the preceding task count
during the upstream reconciliation.


Rebase check at `806e4457fbb7f21234e9bdc6c6c2e091098a0085`. The owning tool retires 0 entries on this parent. 3 already left the queue in earlier work. 0 remain open after the recheck.
