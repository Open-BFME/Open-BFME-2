# GameSlot base adoption, 2026-11-04

Inspected revision: `987170dc1a36103c0cb2ff1a69179cfb9af6cb58`.
Scope: the queued GameSlot adoptions in LANGameInfoSlots.cpp,
LANGameSlotIsLocalPlayer.cpp and NATUpdateBfme.cpp, all under
Code/GameEngine/Source/GameNetwork/. The canonical GameInfo.h is unchanged.

## Target facts and repair

GameInfo.h records the native GameSlot extent (0x1AC), the address dword
and port at +0x38/+0x3C, and the named isHuman/unAccept providers.
The existing LANGameInfoSlots bodies walk 0x1D0-byte LAN slots. Their old
empty GameSlot base left the complete extent in derived padding. With the
canonical base, only `0x1D0 - sizeof(GameSlot)` bytes remain in that padding.

LANGameSlotIsLocalPlayer's native address comparison uses the existing base
storage at +0x38, rather than an additional derived address member. The
typed address view now starts at GameSlot::m_field38. The volatile copy and
barrier that preserve the native retry sequence remain in place.

NATUpdateBfme's old GameSpyGameSlot view placed profile after 0x1AC bytes
of padding over an empty base. The canonical base supplies that extent,
so profile directly follows it. No donor identity or complete derived-class
layout is inferred from this adoption.

## Verification

- Before and after editing, find_declared_unmatched.py reports all defined
  functions already matched for each of the three files.
- `./build.sh` for the two LAN files: 4/4 functions exact.
- `./build.sh` for NATUpdateBfme.cpp: 25/25 functions and one data row exact;
  seven funclet rows verify through the parent EH graph after label renumbering.
- `header_adopt_lane.py accept --class GameSlot` passes all three units and
  retires exactly their three rows from reverse/header_queue.tsv.
- Ordinary `link_check.py` against the 2026-11-04 20:47 census at `f12552d0a7`:
  LANGameInfoSlots.cpp LINKS 118 -> 118 B;
  LANGameSlotIsLocalPlayer.cpp LINKS 100 -> 100 B;
  NATUpdateBfme.cpp LINKS 3,392 -> 3,392 B.

All three current objects link in the preview. This preserves 3,610 historical
census-linked bytes; it is not a new census or a headline linking gain.
No pins, aliases, source paths or ledger identities changed.

## Remaining scope

Other GameSlot header-queue entries are not cleared. In this selected cohort,
the constructor and LAN callback views still have aggregate padding or private
accessors that need reconciliation; this pass did not repeat their recorded
failed trials. Continue through their queue diagnostics, adjusting actual
member uses and derived extents before retrying. No shared-header expansion
is needed for the three accepted consumers.
