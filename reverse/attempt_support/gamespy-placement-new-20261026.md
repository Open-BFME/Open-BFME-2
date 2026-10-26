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
