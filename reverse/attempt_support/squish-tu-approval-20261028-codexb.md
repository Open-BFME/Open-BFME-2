# SquishCollide TU-approval prerequisites

Inspected base: `ea3b1c0c93`, 2026-10-28. This is an evidence handoff;
no source, name, placement or coverage changed.

The default picker served six proposed code rows in four sources for
`Code/GameEngine/Source/GameLogic/Object/Collide/SquishCollide.cpp`.
The supported `name_lane.py consolidate --under
Code/GameEngine/Source/GameLogic/Object/Collide/` survey was generated and
its SquishCollide packet reviewed. Its committed-map information is stale;
`tu_skeleton.py --plan` rebuilt from current inputs and approved only nine
rows, leaving the six served rows unapproved.

The leading boundary is `??1Rva004BB949@@UAE@XZ` at `0x004BB949`, a
25-byte destructor in `Common/Rva004BB68EDerived.cpp`. The proposed K route
is followed by five C rows at `0x004BB962`, `0x004BB968`, `0x004BB96F`,
`0x004BB976` and `0x004BB980`, ending at the approved module-name getter
at `0x004BB98A`. The deleting destructor at `0x004BB9F9` is separately
approved between the real constructor and onCollide anchors; that does not
approve the earlier boundary.

Target facts: the leading body has three vptr stores and an opaque-base
tail call. The getter at `0x004BB962` returns the SquishCollide literal.
The WorldBuilder lead rows for `0x004BB949`, `0x004BB962` and `0x004BB9F9`
still carry PLACEHOLDER names, scores 1/2/1 and no named file witness.
`name_evidence.py --out build/squish-name-evidence.tsv` produces no
candidate for any of the six proposed addresses or SquishCollide. There
is no cached ZH same-body sweep; the available BFME 1 sweep does not yield
a witness for this scope.

Donor facts: Zero Hour defines an empty SquishCollide destructor in its
SquishCollide.cpp. BFME 1's reconstructed SquishCollideDestructor.cpp
describes a 25-byte destructor with three vptr stores, backed there by
its own ILT evidence. Neither the similar body shape nor BFME 1's ILT
proves this BFME 2 placeholder's identity. In particular, this body is
below the naming tool's 32-byte specific-body threshold. Module identity,
adjacency and same-name donor paths must not be promoted into a canonical
same-body witness.

Remaining work: establish an independently checkable BFME 2 naming witness
for the leading boundary, then use the supported naming tools and rerun
the current-input TU plan. No map was regenerated on disk. The existing
constructor donor has an opaque explicit-vptr view while the destination
uses SquishCollideView.h; any later merge also needs its own view and
provider verification. No merge was attempted here.

Checks: `check_csv.py` passes (98,945 function rows); the destination's
`find_declared_unmatched.py` passes. Existing onCollide byte-matching and
link-repair history was read; the proposed rows are existing placeholder
cleanup, not lost coverage or a regression.
