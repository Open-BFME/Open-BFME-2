# Tree-header constructor binding, 2026-10-30

Base `b4c2cc394c`, reference `1d5131d3f193cdf01a99da66ccd6828639585650`,
index `12b9e7a7c0` (10:11). This repairs the existing constructor view without
renaming rows, changing its calling interface or moving sources.

Target facts: the 25-byte wrapper at 0x004DA329 calls the 51-byte constructor
0x004D9B18. That calls the 36-byte storage constructor at 0x004D9A8B, which
allocates 56 bytes through the established allocator and constructs its proxy
through 0x0014F3C4. The outer constructor zeros the count, copies one byte
from its first argument into offset 8, and initializes the header links.

STLport facts: its node links occupy 16 bytes and its constructor initializes
the same header/count fields. The previous opaque eight-byte value reserved
only a 24-byte node, and its empty-comparator copy was elided: the emitted
constructor was 42 rather than 51 bytes. Reserving 40 bytes and explicitly
copying the comparator representation reproduces the native operation.
The independent voice-tree node provider at 0x004D9CD1 also allocates 56 bytes
and constructs a rowed 40-byte value. These are storage/operation constraints,
not proof of the original element, comparator or enclosing container names.
No comparator-byte meaning or initialization is claimed.

The original 25-byte owned copy is unchanged. Both complete emitted helper
bodies, 51 and 36 bytes, resolve exactly to retail with no masking or missing
callee; their actual kept definitions have one variant and certify as retail.
The storage constructor's existing-name fold was admitted by pin_admission
with a whole-body source proof. This adds one checked pin, no alias or row.
The unnecessary tree destructor is declared only, suppressing unused element
destruction machinery. Neither existing owner source is edited.

Normal strict preparation passes 84 function rows and one data row over the
wrapper, the two existing constructor owners and PickAndPlayUnitVoiceResponse.
All four EH graphs are EXACT; frozen-source and pin consistency checks pass.
The bounded preview reports 4/4 LINKS: 8,237 -> 8,262 authored bytes, preserving
the voice caller's 8,150 bytes and both existing owners. This is a 25-byte
preview improvement, not a census or recovered-name gain. Both address routes
remain unapproved, so no consolidation or TU-placement clearance is claimed.

The staged outgoing audit is INCONCLUSIVE on the older index and affected
consumer Common/0CreateAHeroManager21FE49.cpp without a strict receipt. Carry
the corrected construction chain, its new fold binding and affected consumers
into the next scheduled census; full consumer closure remains unmeasured.

Private trials are retained under `build/tree-4da329-20261030/`: changing only
the allocation extent leaves the missing representation copy; memcpy emits
a 61-byte body. A neutral signature rewrite was considered but not applied
because the naming lane cannot establish original class/signature identities.
The chosen existing-symbol specialization avoids those renames.
[proof.json](proof.json) records complete bodies and kept-definition receipts.
No link cycle, nightly measurement or smoke runner was started.
