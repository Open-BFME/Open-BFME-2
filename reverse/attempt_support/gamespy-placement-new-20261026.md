# GameSpy consumers use the toolchain's placement new

The Microsoft-header lane served `GameSpyStagingRoomCopy.cpp` on upstream
`2edd747b85`. Its whole source was claimed and read; its sole queued local
Microsoft definition was placement `operator new(unsigned int, void *)`.
The VS 2003 toolchain's `new.h` supplies the same inline pointer-return body
and the corresponding placement delete. The source now includes that header
and removes its local copy, without changing compiler flags or shared headers.

Normal before/after gates preserve all six rows (405 bytes), including the
345-byte copy constructor at `0x003835F4..0x0038374D`. The final parent EH
graph is EXACT; the normal gate verifies all four renumbered cleanup labels
through the parent, without changing ledger labels or adding pins. The
frozen-file check passes with the same existing emission-use marker.

`ms_header_audit.py scan` finishes with zero local Microsoft definitions or
declarations and zero failed classifications for this source. The ordinary
link preview remains clean at 355 -> 355 authored nonpadding bytes against
index `f995f30157` (2026-10-25 21:36). Credit is one removed local definition;
no generated queue, register, hatch, matched-byte or census gain is claimed.

## Buddy request helpers

The adjacent queued `BuddyRequestDequePushBackAux.cpp` has the same local
placement-new definition. Its whole source was separately claimed and read.
Replacing only that definition with `<new.h>` preserves both matched rows:
the 24-byte `_Construct` at `0x00550798..0x005507B0` and 23-byte
`_M_set_node` at `0x005507E7..0x005507FE`. The old comment about a larger
push-back body is not evidence that this file owns such a row.

Before/after normal and frozen-file checks pass. The Microsoft-header scan
reports zero local definitions/declarations and zero failed classifications.
The ordinary preview remains clean at 47 -> 47 authored bytes against the
same index. This removes one additional local definition, with no row, pin,
shared-header, flag or register change.
