# Typed CarryoverUnit uninitialized fill

Native 1EBA5F, 40 bytes: straight uninitialized-fill loop. The native fill-insert uses the
same CarryoverUnit vector and live copy-constructed temporary established by
the separate assignment/typeflow evidence. The copy and fill workers call
typed placement construction at 1EB9E6; the wrapper calls the worker at 1EBA5F.
All changed callee names resolve to independently verified native owners.

The two worker specializations spell the target's straight loops explicitly.
No nothrow, throw() or compiler exception-suppression promise is introduced.
If construction throws, earlier output elements are not cleaned up by these
native workers. The wrapper uses the ordinary STLport template. Its first
private gate miss was an unavailable not-yet-admitted worker name, while all
27 raw code bytes were already identical. Admission order resolves that name
without changing code or creating a pin.

The immutable private candidate for this stage preserves all 157 original
rows, all 511 complete prior code definitions, existing data and all ten old
EH graphs. The new worker/wrapper has no EH data and matches its entire
native body. Each earlier typed stage remains present. Normal/strict source
verification and current-peer link checks pass. The original generic providers
and all existing callers remain intact; no row, pin, hatch or source path moves.
The generic-template home is unchanged, with no retail TU assertion. Folded
instances add no unique/global coverage or census claim. Wider consumer
clearance remains for the outgoing batch audit and next scheduled census.
