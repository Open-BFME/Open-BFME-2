# NetWrapperCommandMsg header queue reconciliation

Inspected revision: `51570733cfc318a8b18db83ca0de87607d6085e2`.
Date: 2026-11-04. Seat: codexb4. Model: gpt-6.1-sol.

## Accepted existing adoptions

These files already include the registered header and have no private
`NetWrapperCommandMsg` body:

- `Code/GameEngine/Source/GameLogic/Object/Upgrade/ObjectCreationUpgrade.cpp`
- `Code/GameEngine/Source/GameNetwork/ConnectionManager_requestFrameData.cpp`
- `Code/GameEngine/Source/GameNetwork/NetPacket.cpp`

`header_adopt_lane.py adopt --apply` reported "no private view found" for
each. `header_adopt_lane.py accept --class NetWrapperCommandMsg` on these
three files passed individually and retired exactly their three queue rows.
The acceptance includes byte verification and the lane's link-preservation
check; it is not a new link census. No source, header, function row, pin or
hatch changed.

An explicit `./build.sh` of the same three sources passed **236/236** rows.
String-reference verification passed (3 literals and 7 empty-string
references), as did float-reference verification (2 compiler literals).
`find_declared_unmatched.py` reported all defined functions already matched
for the six-file cohort before the trial.

## Remaining structural refusals

The six-file adoption trial wrote no sources. Its other verdicts were:

- `FillBufferWithFrameCommand.cpp` (RVA `0x0058C80F`, 213 bytes):
  `NetWrapperCommandMsg::m_vptr (+0x0, 4 bytes) has no canonical field of
  that offset and size`.
- `Rva0058CD6AWrite.cpp` (RVA `0x0058CD6A`, 185 bytes): the same vptr
  refusal. Its queued narrower refusal also identifies the incompatible
  2-byte field at +0x20.
- `NetCommandMsgCtor.cpp` (wrapper constructor RVA `0x004D5844`, 45 bytes):
  `m_20 is also a member of Rva004D580E; a token rename would reach it`.
  Resolving that token collision alone does not resolve the existing base
  destructor problem recorded in LINK-188. No new destructor trial was run.

Target/source facts for the serializers:

- The frame serializer reads dwords +0x1C, +0x20 and +0x24. The already
  matched `NetPacket::FillBufferWithCommand` dispatches type 3 to it.
  The canonical `NetFrameCommandMsg.h` documents the retail type-3
  constructor and these three fields. In contrast, the wrapper contract
  has a data pointer at +0x1C and six trailing dwords/word through +0x34.
- The serializer at `0x0058CD6A` reads a dword +0x1C, word +0x20, buffer
  pointer +0x24 and length +0x28. That matches the layout used by
  `NetHeroCommandMsg` in `NetPacket.cpp` and its separate destructor source;
  it differs from the wrapper header's data pointer +0x1C and length +0x20.

These comparisons identify an incorrect shared nominal view; matching field
offsets alone do not prove a new donor name or justify changing any ledger
symbol. Next work should reconcile each serializer's receiver identity and
`NetCommandRef` declaration with its dispatch/reader evidence, then use the
canonical-header lane's normal checks. Do not cast pointer-valued wrapper
fields into integers merely to make the unrelated serializers adopt, and do
not delete their remaining queue rows by hand.

The three remaining queue rows are retained. No claim is made about
class-wide closure, a new census, or a real executable link.
