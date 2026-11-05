# Geometry collision/contact canonical-header attempt, 2026-11-05

Inspected revision: `d51d8d64d1`. Source: `Code/GameEngine/Source/Common/System/GeometryInfoCollidesWith.cpp`. This is header cleanup of existing matched rows, not recovery of an unrowed body.

The original owner verifies all three bodies (transform `0x006BE190`, 132 bytes; collision `0x006BEB80`, 821 bytes; contact selector `0x006BEF80`, 1082 bytes), its origin data row, four string literals plus the empty string, and nine float literals.

Replacing the private GeometryInfo with the canonical header preserves transform and collision bytes. Direct Coord3D references to the canonical tail floats disturb copy scheduling. A typed tail view beginning at +0x38 restores copies but emits a 1074-byte selector. Including the existing three shape-vector slots before that tail, and casting canonical `field2c`, restores the selector's full 1082-byte shape. See [the unlanded trial patch](canonical-tail.patch).

The full-sized trial differs only at selector offsets +0x2DB and +0x2E4: target `lea edi,[ebx+edx]` / `lea edi,[ebx+eax]`, trial `lea edi,[edx+ebx]` / `lea edi,[eax+ebx]`. These equivalent address calculations still fail exact verification. Reversing the accessor's addition operands, and using an explicit `i + begin()` element pointer in each label arm, do not close the difference. No compiler profile, pin, alias, shared header, ledger row or debt register was changed.

The source was restored to its original verified contents; no nonmatching trial remains under Code. Header debt is retained. Next step: resolve these two address-generation encodings in the native typed-tail consumer, then run normal byte/data/reference verification, compare object link facts, and use `header_adopt_lane.py accept`. This does not clear the broader Geometry TU profile/view obstacle or claim a link/census/source-count gain.
