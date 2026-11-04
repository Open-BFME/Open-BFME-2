# W3DGameClient canonical factory adoption: object boundary

2026-11-04; inspected revision `1115c5a243`. No source, row, pin or hatch change retained.

Prior evidence: [native identity audit](../w3d-gameclient-native-boundaries-20261103/README.md).
Target facts and the registered interface identify the Ray call at 0x0004C805 as
ThingFactory::newDrawable at 0x002CF21B, already provided by Rva002CF21BGet.cpp.
The existing BFMEThingFactory pin names that provider under a private receiver.

The [candidate](candidate.patch) gets beyond the prior include failures:
canonical ThingFactory first supplies canonical SubsystemInterface and AsciiString;
legacy include guards prevent their second definitions; INI/SpecialPowerType restore
the transitive declarations and a CommandButton forward declaration is sufficient.
`__PLACEMENT_VEC_NEW_INLINE` keeps <new> from redefining the placement-array operators
already supplied by GameMemory (the existing W3DScene TU uses the same switch).
Canonical SubsystemInterface is 12 bytes versus the old view's 8. Reducing opaque
Snow/Keyboard tails by four retains their existing absolute-size assertions.

[Normal build trial](build-trial.log): object generation succeeds, with only
createGameDisplay (0x0008FCAE, 53 bytes) failing. Its allocation changes D8 to DC;
the other five rows, including the 148-byte Ray call using the canonical callee,
remain exact. No complete provider comparison or current-image closure is claimed.
The display's inherited subsystem size is the immediate mismatch. Prior native
facts already refute this row's W3DGameClient/W3DDisplay identities. Changing a
shared display header or inventing another product view merely to retain D8 would
not establish the true owner. Next: paired receiver/product identity correction,
provider and consumer proof, and approved TU placement before retrying this patch.

The candidate was reverted. [Restored verification](build-restored.log): 6/6 exact,
string/float/import gates pass; find_declared_unmatched is clean.
[Restored preview](link-restored.log), published index 8661f15284 (2026-11-03 20:03):
0 -> 0 linked bytes of 351; unresolved BFMEThingFactory call, duplicate setFrameRate,
and wrong-selected createGameDisplay remain. The duplicate is index-relative after
the existing row carve, not evidence of a new source regression. No alias or pin
was removed. No census, real-link or runtime gain is claimed.
