### LINK-557: MessageStream canonical destructor adoption duplicates lifecycle methods
Status: Cleared for the lifecycle duplicates and the destructor/constructor adoption (2026-11-07, seat halilkkaya-lk52);
the TU merge stays blocked on the seed's legacy header. Updated: 2026-11-07; base `a5400a0ae4`.
Evidence / affected units: MessageStreamDtor.cpp, MessageStreamListCtors.cpp and legacy MessageStream.cpp; [trial and consolidation boundary](../../reverse/attempt_support/messagestream-canonical-headers-20261105.md).
Completed (2026-11-05): Propagation adopts canonical MessageStream/CommandList types; the destructor adoption was reverted after matching both rows but predicting LINKED 112 -> 0 from duplicate init/reset/update.

**Completed (2026-11-07, halilkkaya-lk52).**
- Retail decides the lifecycle methods: MessageStream's table 0x00C09890 holds the shared empty body 0x000B3FD0 in
  init/reset/update's slots (1, 9, 10), and CommandList's 0x00C098E0 holds it in init/update's (1, 10); none has an
  address of its own, so all are inline (as canonical MessageStream.h/CommandList.h have them). The seed
  MessageStream.cpp's five out-of-line Zero Hour bodies (present-unmatched, no row) are gone, its TU-scoped shim
  (`reference/shims/bfme2_message_stream`) declares them inline, and the hatch register shrinks by five. Only
  CommandList::reset (0x00311092, a tail jump to destroyAllMessages) has an address and stays declared out of line.
- MessageStreamDtor.cpp then adopts canonical MessageStream.h: 2/2 rows exact, LINKS 112 -> 112, its
  `??_7MessageStream@@6B@` goes from the 10-slot Zero Hour view to retail's 20 slots, and
  `header_adopt_lane.py accept --class GameMessage` retires its row.
- MessageStreamListCtors.cpp adopts canonical MessageStream.h and CommandList.h: 19/19 rows exact, LINKS 758 -> 758.
  The constructor 0x0030F697 now stores `??_7MessageStream@@6B@` (DIR32 at +0x12, after the translator clears as in
  retail) instead of the zero int `s_messageStreamVtable`, which is deleted (LINK-625's boot-path item). The unit's
  `??_7GameMessageList@@6B@` and `??_7CommandList@@6B@` grow from 3 slots to retail's 18; its
  `??_7MessageStream@@6B@` is identical to MessageStreamDtor.cpp's. A message is destroyed by `::delete msg` (slot 0
  with flag 0, then operator delete of the return), which is what the private `deleteInstance(int)` spelled.
  Accept retires its CommandList, GameMessage and MessageStream rows.
- Slot check against retail, all three tables: slot 0 (`??_E`) and the rowed slots 2, 14, 15, 18, 19 resolve to rows at
  retail's words; the inline SubsystemInterface/list slots are byte-identical to retail's slot targets (`c3`,
  `32c0c20400`, `32c0c3`, `33c0c3`, `c20400`).
- Verification each step: `./build.sh` exact, find_declared_unmatched clean, scoped DIR32 OK, and link_check over
  MessageStream, MessageStreamDtor, MessageStreamListCtors, propagateMessages, createMessageStream,
  CommandList_appendMessageList, VslotSmallBodiesAJ, GameClientDrawableTOC, GameEngineInit and SubsystemInterface.cpp:
  all LINKS, bytes unchanged. Note: the fetched census index still held the seed's out-of-line definitions, so a
  single-unit preview of the destructor reported the old duplicates; `link_check.py --update-index` (or naming
  MessageStream.cpp in the same run) reads the current seed object.

**Remaining wrong slots (runtime).** Slots 16/17 of all three tables name `GameMessageList::removeMessage` and
`containsMessageOfType`, which only the seed defines, from the Zero Hour layout: they address the list at +0x08/+0x0C,
retail's 0x0030F642/0x0030F679 at +0x0C/+0x10. Retail's bodies are rowed under the placeholders
`Rva0030F642::rva0030F642(Rva0030F642Node *)`/`rva0030F679(int) const` in MessageStream.cpp (approved TU for both).
`rename.py function --to-class` cannot move them (their parameters differ from the real signatures), and a definition
under the real class needs a unit with the canonical list layout, which MessageStream.cpp gets only by moving onto
the canonical header. The real link's vtable bridge places retail's copies of all three tables first (bridge queue:
bridged), so the image runs the right bodies meanwhile; the bridge cannot retire while these two slots stay.
CommandList's slot 9 was the seed's `CommandList::reset`, jumping to the seed's own Zero Hour `destroyAllMessages`
(protected, +0x08 offsets): fixed 2026-11-07 by `rename.py function --to-class` (row 0x00311092
`Rva00311092::rva00311092` becomes `CommandList::reset` in VslotSmallBodiesAJ.cpp, which jumps to the rowed
0x0030F854; the seed's two Zero Hour bodies are gone).

Remaining / next check: the TU merge dry run (`tu_skeleton.py --merge Code/GameEngine/Source/Common/MessageStream.cpp
--dry-run`, 2026-11-07) still accepts no donor: every donor that includes the canonical header
(CommandList_appendMessageList, GameMessageAllocArg, MessageStreamDtor, propagateMessages) collides with the seed's
Zero Hour `GameMessage` (C2011), GameMessageStructArgs/GameMessageCopy with its Coord3D, and MessageStreamCommandName
differs in bytes. The seed MessageStream.cpp must move onto the canonical headers (GameMessage arguments, the list
layout at +0x0C) before any merge; that also lets it give retail's bodies their real names.
Clearance: lifecycle duplicates and destructor header debt cleared (rows retired by accept); merge pending.
Census confirmation: None claimed (link_check previews only).
