# GameSpyInfoInterface queued consumer adoption

Inspected revision: `0afe04e6368294a0a9290ad00c5084edc93524b8`. Date: 2026-11-04.

Scope: the five consumers in the acceptance output below. The shared
`Code/GameEngine/Include/GameNetwork/GameSpyInfoInterface.h` is unchanged.

Target/header facts: the existing header records native vtable placement and
method identities. The retired private views used `hasBuddyRequest` for slot 27
(header `isBuddy`), `premium` for slot 90 (`didPlayerPreorder`),
`_M_slot_120` for slot 72 (`getPingValue`), `setConnected` for slot 98
(`slot98`), and `GetList` for slot 26 (`getBuddyMessages`). Calls now use the
header's declarations. This adoption establishes no additional recovered names.

The buddy map and message-list consumers retain their existing rowed container
views through explicit pointer casts; their template identities are not changed
or claimed recovered here. Only the duplicate interface bodies are removed,
including StagingRoomGameInfo's interface-only virtual padding hierarchy.
No global, pin, alias, provider row, source path or shared header changes.

Initial automatic trials rejected every consumer: obsolete member names,
container pointer mismatches, and a StagingRoomGameInfo layout-probe C1083.
The original staging-room source independently passed all 81 rows. Manual
adoption in that file places the interface include before the local abstract
GameSpyStagingRoom definition: including it later triggers VC7 C2259 on the
interface's by-value room declarations. Its existing platform flags and source
class definitions remain unchanged.

All five sources passed `find_declared_unmatched.py` before and after editing.
The ordinary scoped build verified every row, literals, imports and unwind
bindings. Relevant output from `./build.sh` over the five accepted paths:

```text
Source claims: OK (5 sources, scoped byte-verified)
Compile: 1 of 5 TU(s) (deps-cache: 4 current)
Funclet pins: 98 row(s) verified past a renumbered $L label
    $L623 (Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPushStatsBfme.cpp): $L623 was renumbered; verified parent EH data places $L6661 at 0x00780618
    $L624 (Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPushStatsBfme.cpp): $L624 was renumbered; verified parent EH data places $L6662 at 0x00780623
    ?rva0078060d@@YAXXZ (Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPushStatsBfme.cpp): $L622 was renumbered; verified parent EH data places $L6660 at 0x0078060D
    ?rva0078062e@@YAXXZ (Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPushStatsBfme.cpp): $L625 was renumbered; verified parent EH data places $L6663 at 0x0078062E
    uw_0079397c (Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp): $L1230 was renumbered; verified parent EH data places $L14535 at 0x0079397C
STLport folds: 1 complete emitted constructor(s) verified against retail owners and resolved callees
Functions: OK 144/144 matched across 5 source file(s)
String-ref verify: OK (50 literals + 15 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (16 named imports verified)
```

The owning retirement command was `python3 tools/header_adopt_lane.py accept
--class GameSpyInfoInterface` with the five source paths below. It checks the
shared include and absence of private interface bodies, byte verification,
symbol dependencies and combined ordinary per-unit link previews. Verdict:

```text
PASS Code/GameEngine/Source/GameNetwork/GameSpy/BuddyDefs.cpp
  PASS Code/GameEngine/Source/GameNetwork/GameSpy/RequestBuddyAddRva004178C1.cpp
  PASS Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp
  PASS Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPushStatsBfme.cpp
  PASS Code/Libraries/Source/WWVegas/WWLib/stlport_list_00416a5d_bounded.cpp
  retired 5 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

Five header-queue rows retired by that command. This is header debt retirement
with preserved byte matching and census-linked coverage; no new census,
linked-byte increase, real-link result or smoke result is claimed.
