# GameModePreferences header adoption, 2026-11-04

Inspected source revision: `41e9e8268d`. Claim owner: `yasinschroeder-codexb`.

Replaced all twelve queued private GameModePreferences declarations with the
existing canonical header. Enabled STLport in the eight consumers lacking its
build marker. GameModePreferences.cpp now uses the header's neutral `field14`
and `field18` spellings at their unchanged offsets. MapSelectMenu and PeerThread
use the existing target OptionPreferences header instead of the donor
UserPreferences header, avoiding duplicate base definitions. No shared header,
ledger identity, source path or alias changed.

Target layout evidence is already recorded in GameModePreferences.h: the
complete object occupies 0x1C bytes. AptOnlineCustomMatch's member starts at
+0x46C and ends at +0x488, so its old +0x470 filler disappears. AptLanLobby's
member starts at +0x408 and ends at +0x424, leaving four bytes before its
+0x428 field. Byte verification confirms all later field accesses remain at
their retail offsets. These are padding adjustments, not recovered field names.

## Owning retirement and verification

- `header_adopt_lane.py accept --class GameModePreferences` passed for every
  source below and retired all twelve of that class's queue rows.
- `header_adopt_lane.py accept --class UserPreferences` passed for
  Rva0044D56ADerived.cpp after explicitly including its base header, retiring
  one additional row. All thirteen removals came from the owning tool.
- Ordinary build verification and strict reusable receipt preparation passed:
  539/539 code rows, four data rows, 357 literals plus 76 empty-string refs,
  and 77 named import refs. All twelve strict provider receipts are reusable.
- `check_csv.py`, `find_declared_unmatched.py` and `git diff --check` pass.
  The frozen-file checker retains PeerThread's existing note about three
  unclaimed definitions; it reports no unmatched definitions requiring repair.
- Ordinary link preview: all twelve units LINKS, preserving 52,420 -> 52,420
  census-linked bytes against index `f12552d0a7` (2026-11-04 20:47).
  Diagnostic variants are classified unreferenced and not blockers by that
  preview. This is a bounded prediction, not a new census or real-link/runtime
  result; no headline linking increase is claimed.

## Final commit hook

The commit hook passed, including all 539 code rows and 95/95 EXACT EH graphs
(zero baselined or non-exact EH graphs). Converged data checking passed across
twelve sources and eleven addresses, with no second names or unjudged entries.
Non-enforcing checks reported nineteen code-identity findings outside the
baseline and two data findings (one outside its baseline). These findings were
not audited against the parent revision in this pass, so their introduction is
undetermined. This work retires only the thirteen header-queue rows; it claims
no code-identity or data-debt retirement.

## Sources

- `Code/GameEngine/Source/Common/AptOnlineCustomMatch_MpOwnerSelectStrategicScenario.cpp`
- `Code/GameEngine/Source/Common/GameModePreferences.cpp`
- `Code/GameEngine/Source/Common/Rva0038169DChatSubmit.cpp`
- `Code/GameEngine/Source/Common/Rva0044D56ADerived.cpp`
- `Code/GameEngine/Source/Common/Rva0059F950.cpp`
- `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchProcessGameSpyResponses.cpp`
- `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenLanLobby.cpp`
- `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MapSelectMenu.cpp`
- `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MapSelectMenu_Rva0050CF3C.cpp`
- `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp`
- `Code/GameEngine/Source/GameNetwork/LANAPI.cpp`
- `Code/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp`

## Strict receipt and build output

```text
link_check: preparing 12 explicit safe provider(s), no extra sources
Source claims: OK (12 sources, scoped byte-verified)
Data rows: OK (4 row(s) byte-verified)
Compile: 0 of 12 TU(s) (deps-cache: 12 current)
Funclet pins: 285 row(s) verified past a renumbered $L label
    $L50028 (Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp): $L50028 was renumbered; verified parent EH data places $L49264 at 0x0078064B
    $L50029 (Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp): $L50029 was renumbered; verified parent EH data places $L49265 at 0x00780655
    $L57707 (Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp): $L57707 was renumbered; verified parent EH data places $L55145 at 0x007808AD
    $L57708 (Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp): $L57708 was renumbered; verified parent EH data places $L55146 at 0x007808B8
    $L58052 (Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp): $L58052 was renumbered; verified parent EH data places $L56666 at 0x0078093F
Functions: OK 539/539 matched across 12 source file(s)
String-ref verify: OK (357 literals + 76 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (77 named imports verified)
link_check: 12 explicit providers byte-verified with strict reusable receipts; census/index/status unchanged, LINK closure not yet checked
```

## Per-unit link predictions

```text
Code/GameEngine/Source/Common/AptOnlineCustomMatch_MpOwnerSelectStrategicScenario.cpp: LINKS  LINKED 64 -> 64 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 64)
Code/GameEngine/Source/Common/GameModePreferences.cpp: LINKS  LINKED 2,676 -> 2,676 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 2,676)
Code/GameEngine/Source/Common/Rva0038169DChatSubmit.cpp: LINKS  LINKED 493 -> 493 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 493)
Code/GameEngine/Source/Common/Rva0044D56ADerived.cpp: LINKS  LINKED 78 -> 78 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 78)
Code/GameEngine/Source/Common/Rva0059F950.cpp: LINKS  LINKED 225 -> 225 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 225)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchProcessGameSpyResponses.cpp: LINKS  LINKED 9,173 -> 9,173 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 9,173)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenLanLobby.cpp: LINKS  LINKED 3,243 -> 3,243 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 3,243)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MapSelectMenu.cpp: LINKS  LINKED 3,397 -> 3,397 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 3,397)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MapSelectMenu_Rva0050CF3C.cpp: LINKS  LINKED 345 -> 345 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 345)
Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp: LINKS  LINKED 18,622 -> 18,622 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 18,622)
Code/GameEngine/Source/GameNetwork/LANAPI.cpp: LINKS  LINKED 8,534 -> 8,534 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 8,534)
Code/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp: LINKS  LINKED 5,570 -> 5,570 bytes (census 2026-11-04 20:47 at f12552d0a7; file's own bytes 5,570)
link_check: 12 of 12 link cleanly; LINKED 52,420 -> 52,420 bytes (7.0s)
```
