# Follow-up: remaining existing canonical-manager includes with pending keys

Exactly2 additional claimed-source keys qualify after root's destroy/text-entry acceptances. Every current pending GameWindowManager source key in the21-source scope was checked for a direct relative include resolving to Code/GameEngine/Include/GameClient/GameWindowManager.h and for absence of a private manager definition. No compile, acceptance, Code edit, claim, network or queue mutation was performed here. Exact current queue records and all9 existing rows are saved in other-existing-header-candidates.json.

Source/key: `GameWindowManager` + `Code/GameEngine/Source/Common/Rva002C5398Dtor.cpp`.

Direct canonical include: `#include "../../Include/GameClient/GameWindowManager.h"`. Existing pending reason: `pending canonical adoption; refreshed qc-10 item 5265`. Owning command for root after the dry run: `python3 tools/header_adopt_lane.py accept --class GameWindowManager Code/GameEngine/Source/Common/Rva002C5398Dtor.cpp`.

Current same-source ledger owners to verify:

- `??0Rva002C5398@@QAE@XZ`, 0x002C5334, 100B (matched).
- `??1Rva002C5398@@UAE@XZ`, 0x002C5398, 112B (matched).
- `__ehhandler$??0Rva002C5398@@QAE@XZ`, 0x00776DDF, 10B (matched).
- `__ehhandler$??1Rva002C5398@@UAE@XZ`, 0x00776DFC, 10B (matched).
- `uw_00776df1`, 0x00776DF1, 11B (matched).
- `Unwind@00b76dd7`, 0x00776DD7, 8B (matched).
- `Unwind@00b76de9`, 0x00776DE9, 8B (matched).
- `??_GRva002C5398@@UAEPAXI@Z`, 0x002C5590, 28B (matched).

Source/key: `GameWindowManager` + `Code/GameEngine/Source/GameClient/GUI/GameWindowManager_drawWindow_Thunk.cpp`.

Direct canonical include: `#include "../../../Include/GameClient/GameWindowManager.h"`. Existing pending reason: `pending canonical adoption; refreshed qc-10 item 5265`. Owning command for root after the dry run: `python3 tools/header_adopt_lane.py accept --class GameWindowManager Code/GameEngine/Source/GameClient/GUI/GameWindowManager_drawWindow_Thunk.cpp`.

Current same-source ledger owners to verify:

- `?drawWindow@GameWindowManager@@IAEHPAVGameWindow@@@Z`, 0x002C0FC9, 198B (matched).

For Rva002C5398Dtor, preserve all8 rows: constructor/destructor/deleting destructor plus their2 EH handlers and3 bound funclets, including current object-symbol notes. This candidate is ONLY acceptance of existing use of the canonical GameWindowManager interface; it does not rename Rva002C5398 or retire separate list/provider/identity/EH obligations.

For drawWindow_Thunk, preserve its198B row and the separate GameWindow queue key (opaque m_instData+0x30/456B adoption blocker). Passing manager acceptance would not establish canonical GameWindow adoption.

dumpWindow.cpp is NOT another stale manager key: it directly includes the canonical manager but there is no current GameWindowManager/source queue record. Its separate GameWindow key remains, including the m_field04/CreateInfo naming collision. enableWindowsInRange.cpp also already has no pending manager key. Do not re-add or retire unrelated keys for either source.

Root owns full-source reading, normal builds and each owning acceptance. No broader class rewrite or new provider is proposed. Tracked reads stopped.
