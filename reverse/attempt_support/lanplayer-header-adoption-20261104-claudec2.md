# LANPlayer header adoption, 2026-11-04 (claudec2, Opus 5.5)

Scope: the five LANPlayer header-queue units served by `next_work.py --tier header`.
`header_adopt_lane.py adopt` refused all five on token-rename collisions
(`m_ip -> ip`, `address` also an allocator member, unmatched `m_IP`/`m_body`
fields), so each was tried by hand.

Accepted (header_adopt_lane.py accept PASS, rows byte-exact):
- `Code/GameEngine/Source/GameNetwork/LANPlayer_copy.cpp`: LANPlayer and
  BfmeNetAddress views replaced by the canonical headers; 2/2 exact.
- `Code/GameEngine/Source/GameNetwork/LANGameInfo.cpp`: LANPlayer view and a
  dword-port BfmeNetAddress replaced; 17/17 exact; two LANPlayer rows and one
  BfmeNetAddress row retired.

Not adopted:
- `Code/GameEngine/Source/GameClient/GUI/ChatWindowsLan.cpp`: with the canonical
  word port, `ChatWindowsLan::GetLobbyPlayers` compiles `0f b7 47 04 50`
  (movzx + push) where retail has `ff 77 04 ff 37` (push dword [edi+4];
  push dword [edi]). The callee, the 5-argument `BfmeStringRecord005D511F`
  constructor (0x005D516E, rowed in StringRecordInlineCopyBFME2.cpp as
  `...@ABVUnicodeString@@II0I@Z`), stores [ebp+0xC] and [ebp+0x10] to +4/+8 as
  dwords with no extension, so neither parameter is 16-bit. The pair of
  pushes is the shape of an 8-byte BfmeNetAddress passed by value
  (structural inference, not yet tried): the constructor is likely
  `(const UnicodeString &, BfmeNetAddress, const UnicodeString &, unsigned)`.
  Next step: retype it (mangled-name change in the definer and its callers
  0x005D5604/0x005D5692, plus the record's +4/+8 fields), then adopt.
- `Code/GameEngine/Source/GameNetwork/LANAPI.cpp` and `LANAPIhandlers.cpp`:
  their BfmeNetAddress view derives from the empty `Rva00248CDD` (the 0x00248CDD
  inequality test, called as `getAddress(p)->Rva00248CDD::rva00248CDD(none)`),
  has `(ip, port)` constructors and a `self()` used on temporaries
  (`BfmeNetAddress(0,0).self()`). The canonical `BfmeNetAddress.h` has none of
  these, and LANPlayerClass.h includes it, so these units first need the
  canonical struct extended (16 includers; full-gate header edit) or their
  call sites rewritten.
