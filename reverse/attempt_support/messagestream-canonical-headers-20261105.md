# MessageStream canonical-header prerequisite (2026-11-05)

Inspected revision: `46781e709071d7d75b6c30c3708b2b7ec3895d76`.
Provider index: 2026-11-05 15:52, revision `112a456a2c`.

## Applied scope

`Code/GameEngine/Source/Common/MessageStream_propagateMessages.cpp`
now includes the canonical MessageStream and CommandList headers. Removed its
private GameMessage, CommandList, GameMessageList and MessageStream declarations,
and replaced MessageTranslatorNode with the canonical TranslatorData type.
The translator interface and propagation algorithm are unchanged.

`./build.sh` preserves the 101-byte row at 0x00310FF5. Header-queue retirement
passed `header_adopt_lane.py accept` separately for CommandList, GameMessage and
MessageStream, retiring all three rows. Final ordinary link preview: LINKS,
LINKED 101 -> 101 bytes against the above index (1/1 units); this is a preview,
not a fresh census.

## Reverted destructor trial

`MessageStreamDtor.cpp` passed both existing rows before and after replacing its
private classes with the canonical MessageStream header (112 matched bytes).
However, `link_check.py` predicted LINKED 112 -> 0, reporting duplicate
`MessageStream::init`, `MessageStream::reset` and `MessageStream::update`.
`header_adopt_lane.py accept --class GameMessage` refused retirement for that
link loss. The entire destructor source change was reverted; its queue row stays.
These lifecycle functions are defined out of line in the legacy seed
`MessageStream.cpp`, while the canonical header defines them inline. Reconcile
their emitted bodies/providers before retrying this destructor adoption. Do not
retire its debt on byte matching alone.

## Consolidation boundary

The current MessageStream.cpp merge dry run accepts no donors. It still rejects
CommandList_appendMessageList, GameMessageAllocArg, GameMessageStructArgs,
MessageStreamDtor and GameMessageCopy for legacy/canonical declaration conflicts;
MessageStreamCommandName differs in bytes. Before this repair, the propagation
donor additionally failed assigning TranslatorData* to MessageTranslatorNode*.
The applied type reconciliation removes that specific source-level conflict.
A whole-TU merge has not been applied or claimed successful. Migrate the seed's
legacy header dependencies and reconcile compilation flags before retrying the
remaining donors. No new census measurement or linked-byte gain is claimed.
