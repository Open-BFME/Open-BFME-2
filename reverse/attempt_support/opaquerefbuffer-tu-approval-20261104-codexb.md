# OpaqueRefBuffer TU approval investigation, 2026-11-04

Inspected HEAD: 465b7dc3f84ed06b5025e3a7d9cd39d1f0c5e870. No source or map edits.

The TU-approval picker served `Code/Libraries/Source/WWVegas/WW3D2/OpaqueRefBuffer.cpp`
for fourteen proposed rows across six sources. That TU path does not exist.
`name_lane.py consolidate --under Code/Libraries/Source/WWVegas/WW3D2/`
recomputed the evidence packet; its groups are investigations, not approvals.
`tu_skeleton.py --plan` rebuilt the stale committed map in memory and returned
only four approved P-group EH rows in two mixed sources, with zero donor files.
The code rows remain proposed/noncontiguous, so a merge is not authorized.

Target facts: the committed map places the OpaqueRefBuffer constructor,
copy constructor and destructor at 0x0015B230/0x0015B390/0x0015B3D0 by N hints;
the intervening MatBufferClass copies at 0x0015B2C0/0x0015B300 have Z/S anchors
to meshmatdesc.cpp. More descriptor rows bracket both sides. The buffer's source
comment explicitly leaves the original class and pointee names unknown.
These facts do not prove a separate retail OpaqueRefBuffer.cpp, nor prove a new
name or TU assignment for the buffer. No apparent missing body was treated as a
regression.

Verification: `./build.sh Code/Libraries/Source/WWVegas/WW3D2/MeshMatDescOpaqueBuffer.cpp`
passes all 11 rows, including the compiler-renumbered funclet via parent EH data;
`find_declared_unmatched.py` reports all defined functions already matched.

Next: establish a re-checkable target identity/anchor before changing the N hints
or moving rows. The existing header-adoption attempt at 0x0015B7A0 separately
records the RefCountData.h versus donor refcount/sharebuf prerequisite; that
unchanged issue was not retried. Do not rename the neutral buffer merely to make
the proposed span contiguous. Claims released; byte coverage retained.
