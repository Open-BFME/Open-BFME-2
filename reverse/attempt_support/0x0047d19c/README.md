# Containment crew restoration

The served WB queue identifies native `0047D19C..0047D246` as
`HordeSiegeEngineContain::LoadPostProcess` (WB `011AF450`, vtable score 19).
The whole existing rider translation unit and WB body were inspected. Native
evidence establishes owner +8, crew list +128, saved-ID list +140, object field
+274, status bit 3D and primary virtual slot 24. WB's +12C/+144/+27C fields
are not used as target offsets. The slot's two zero arguments remain unnamed.

An earlier attempt stopped at the unrowed base call. Native `00479D68..00479D6D`
is now separately recovered as clean C++ in the neighboring Garrison xfer home;
its unchanged receiver and no-argument tail call to `004783D7` are established
by native bytes and WB `011A1210`. It uses the existing provider spelling from
`Rva004697E1Gate.cpp`; no new pin or guessed folded class identity was added.
The downstream OpenContain load body is independently recovered at 463C6E;
its separate evidence record explains the enclosing-container walk.

The first isolated rider-file trial emitted 286 bytes. `/O1 /G7` made the load
routine exact without forcing a frame on the three existing rider methods.
Explicit `/Oy-` was rejected because it changed a rider prologue. The ownership
report identified the approved main class home, so the body was moved there
before publication and the rider file restored. The main home's existing
`/O1 /arch:SSE` settings reproduce all three methods; `/G7` is unnecessary.
All eight bodies across the main, rider and base homes pass normal verification; the
emitted alignment byte immediately beyond the 170-byte routine was also
compared with retail and matches. EH verification reports no EH-bearing rows.
The actual XferException constructor, throw type, list operations, GameLogic
lookup and Object status provider are reused. No data address is invented.

This is byte and relocation verification, not a fresh link census or runtime
result. The existing unowned base pin remains an explicit dependency.

The related served lead `SiegeEngineContain::LoadPostProcess`, WB `011ABDE0`
with vtable score 18, was independently reconstructed in its complete existing
home. Native `0047C173..0047C21D` establishes list +11C, saved IDs +134 and
the unchanged-receiver base call to +4783D7; owner +8, object +274, status 3D
and virtual slot 24 are separately verified there. Its 170 bytes and emitted
alignment byte match exactly, as do both existing home bodies (60 and 75 bytes).
It uses the existing base provider pin and adds no pins. The sibling is banked
in its own normal commit.
