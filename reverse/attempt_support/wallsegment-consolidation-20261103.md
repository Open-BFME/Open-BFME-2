# Wall-segment consolidation prerequisites

Inspected revision: `63fe3535f5d2899c9027d89817af2b5cf726290b`.
Target: `Code/GameEngine/Source/GameLogic/SkirmishAI/AIWallBuilder/AIBuildableWallSegment.cpp`.
Donor: `Code/GameEngine/Source/Common/Rva00596CEAXfer.cpp`.

The current in-memory TU map approves the donor's 147-byte row at
`0x00596CEA` for the destination. Both source files pass
`find_declared_unmatched.py`; no source, ledger or register changes were applied.

`tu_skeleton.py --merge <target> --dry-run` accepts no donor. Composition
fails with C2039: `rva00573DCD` is not a member of `Rva00573B23`.
`tu_views.py <target>` reports conflicts for both `Rva00573B23` and
`Rva00596CDF`: destination declares structs, donor declares classes, and no
matched mangled name determines their class key. It keeps zero accepted donors
before and after reconciliation.

The source views also differ structurally: the destination's `Rva00573B23`
has a virtual destructor and opaque bytes through +0x40, while the donor
models inheritance from `Rva0055B0CC`, transfer slots and concrete fields.
The destination's +0x40 position has an inline zeroing constructor used by its
matched wall-segment constructor; the donor uses the plain `Coord3DBase` triple.
These are observations from the current reconstructed sources, not proof of
retail class spelling or complete layout.

Next step: reconcile the constructor/destructor/transfer views and their
virtual-slot providers in a separate verified source change. Preserve the
position-member initialization and check emitted vtable dependencies before
retrying the merge. Changing only class keys does not establish compatible
bases or virtual slots. No link regression or headline progress is claimed.
