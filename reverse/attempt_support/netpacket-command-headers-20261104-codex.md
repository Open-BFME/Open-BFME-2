# NetPacket command-message header acceptance

2026-11-04; inspected base `1179e72d1d513cbdff16cdc29412c150f22d4fe3`.
Scope: `Code/GameEngine/Source/GameNetwork/NetPacket.cpp`.

Replaced its private `NetFrameCommandMsg` declaration with the registered
`GameNetwork/NetFrameCommandMsg.h`. The reader's three stores now name
`m_frame`, `m_playerFrame`, and `m_commandCount`; the writer uses the corresponding
canonical getters. These are the existing header's evidenced +0x1C/+0x20/+0x24
dwords. Changes are bounded to the two frame-message functions; the similarly
spelled fields of other message classes are untouched.

`NetGameCommandMsg.h` and `NetWrapperCommandMsg.h` were already included, with no
private copies of those classes in this source. Their queue rows were stale.
`header_adopt_lane.py accept --class CLASS Code/GameEngine/Source/GameNetwork/NetPacket.cpp`
retired each of those rows, and the frame row after adoption (three rows total).
All three accept verdicts pass on the final source. No manual queue deletion.
No other NetPacket header-queue rows remain.

The constructor and destructor prerequisites in LINK-188/LINK-196 are unchanged;
no retry of their unchanged failed trials was made. No shared header, pin,
alternate-name route, source path or ledger row changed. The initial W3DGameClient
picker lead already previewed LINKS 0 -> 351 bytes before this work and its claim
was released without an edit.

## Verification

`find_declared_unmatched.py` passes before and after. `check_csv.py` passes
(99,438 function rows, 9,341 symbol rows, 2,269 data rows).

`./build.sh Code/GameEngine/Source/GameNetwork/NetPacket.cpp`:

```text
Source claims: OK (1 sources, scoped byte-verified)
Funclet pins: 46 row(s) verified past a renumbered $L label
    $L10032 (Code/GameEngine/Source/GameNetwork/NetPacket.cpp): $L10032 was renumbered; verified parent EH data places $L16382 at 0x0079D003
    $L10033 (Code/GameEngine/Source/GameNetwork/NetPacket.cpp): $L10033 was renumbered; verified parent EH data places $L16383 at 0x0079D00D
    $L10213 (Code/GameEngine/Source/GameNetwork/NetPacket.cpp): $L10213 was renumbered; verified parent EH data places $L14318 at 0x0079CF07
    $L9922 (Code/GameEngine/Source/GameNetwork/NetPacket.cpp): $L9922 was renumbered; verified parent EH data places $L14076 at 0x0079CF1B
    $L9934 (Code/GameEngine/Source/GameNetwork/NetPacket.cpp): $L9934 was renumbered; verified parent EH data places $L14088 at 0x0079CF2F
Functions: OK 209/209 matched across 1 source file(s)
String-ref verify: OK (0 literals + 7 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```

Final acceptance verdicts (NetGameCommandMsg, NetWrapperCommandMsg, NetFrameCommandMsg):

```text
  PASS Code/GameEngine/Source/GameNetwork/NetPacket.cpp
  PASS Code/GameEngine/Source/GameNetwork/NetPacket.cpp
  PASS Code/GameEngine/Source/GameNetwork/NetPacket.cpp
  retired 1 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

Ordinary link preview before:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameNetwork/NetPacket.cpp: LINKS  LINKED 33,226 -> 33,226 bytes (census 2026-11-04 02:25 at 5a13f2cd61; file's own bytes 33,226)
link_check: 1 of 1 link cleanly; LINKED 33,226 -> 33,226 bytes (4.4s)
```

Ordinary link preview after:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameNetwork/NetPacket.cpp: LINKS  LINKED 33,226 -> 33,226 bytes (census 2026-11-04 02:25 at 5a13f2cd61; file's own bytes 33,226)
link_check: 1 of 1 link cleanly; LINKED 33,226 -> 33,226 bytes (3.8s)
```

The preview preserves this unit's 33,226 census-linked bytes against the
2026-11-04 02:25 census at `5a13f2cd61`. It is a scoped prediction, not a new
census or real-link result. Debt decreases by three header-queue rows; no
coverage or linking gain is claimed. The outgoing batch audit still decides
provider/consumer preservation; any inconclusive scope belongs in the next
scheduled census.
