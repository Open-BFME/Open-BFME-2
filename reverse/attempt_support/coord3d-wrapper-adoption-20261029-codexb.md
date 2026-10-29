# Coord3D wrapper adoption and deferred retirements

Base: `a2e9c2b5b2`, 2026-10-29. Published preview index:
`85f6b7f40c`, census 2026-10-29 15:08. Claimed scope: `class:Coord3D`.

`Common/Rva004EBF4BCopy.cpp` now includes the existing
`Lib/Coord3DCtorView.h` instead of defining Coord3DBase and Coord3D locally.
Its scalar return construction uses the shared three-float constructor;
the TU-specific BfmeTagBldr constructor is removed. The include directory
is explicit. No shared header, ledger symbol, pin or source path changes.
The 72-byte row at 0x004EBF4B remains exact. The shared non-POD constructor
contract preserves the native return-copy phase; this is distinct from the
previous failed aggregate-return trial. This change establishes no new name
or source-provenance claim for the address-named wrapper.

The owning `header_adopt_lane.py accept --class Coord3D` command passes and
retires five queue entries. Four are already-adopted companion users whose
source files are unchanged; the newer census supplies clean per-unit previews
where previous publication attempts could not establish them.

| Source basename | Ordinary linked-byte preview |
| --- | ---: |
| Rva004EBF4BCopy.cpp | 72 -> 72 |
| Rva003A35A0Element.cpp | 1,032 -> 1,032 |
| Rva00506CF5HomePoint.cpp | 763 -> 763 |
| stlport_vector_geometryshape_base.cpp | 121 -> 121 |
| AIStructureCreepTactic.cpp | 4,226 -> 4,226 |

Verification: the changed source passes `find_declared_unmatched.py` before
and after the edit and `./build.sh` passes its complete row. Strict preparation
of all five accepted sources passes 77/77 function rows, six literal references,
one empty-string reference and nine compiler literals. The byte verifier
resolves 29 renamed funclet labels through their parent EH graphs. Ordinary
preview preserves 6,214 authored bytes across all five units. Acceptance,
not a manual edit, removes every queue entry.

The staged-tree `link_batch_audit.py` result is INCONCLUSIVE: the published
index predates this base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and the changed wrapper's provider scope into
the next scheduled census. No full consumer closure, newly linked census
bytes or image-ownership gain is claimed.

Six Coord3D queue entries remain. Matrix4D and the copy/Bezier family still
require the documented class-key/owner reconciliation; library members and
the weapon constructor require coordinated interface/identity work. The
Matrix4D and shared-member-growth failures in LINK-018 were not repeated.
