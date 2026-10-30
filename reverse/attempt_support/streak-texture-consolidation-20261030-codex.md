# Streak texture getter consolidation, 2026-10-30

Inspected base: `1b0276b877`. Owner: `yasinschroeder-codex`.
No census or image-ownership measurement is recorded by this work.

## Verified prerequisite

The default picker claimed streak.cpp and its destructor/getter donors. The
WW3D2 evidence planner records the getter and destructor as whole-file
candidates for streak.cpp, with placement, declaration and compiler blockers.
The supported merge rebuilds current TU assignments in memory; the committed
TU map is not regenerated. Its initial trial rejects the getter solely for
`-O2 -G7 -arch:SSE` versus the seed's `-arch:SSE -G7`, and the destructor for
C2908 (explicit SimpleVec destructor specialization after instantiation).

The build's base command already supplies /O2. Removing the getter's redundant
/O2 and ordering /arch:SSE /G7 like the seed preserves its effective settings.
`flag_defaults.py propose` verifies current/default variants and records the
new override spelling: one row, one default-lost row, unchanged scope.

The seed's ZH-derived shared StreakLine view declared Get_Texture as a raw
pointer. BFME 2's already-rowed 33-byte getter at 0x00741750 instead returns
ParticleBufferClass::TextureHandleClass through its caller buffer and calls
the owned BFMELineRendererTexture getter at 0x00191210. The seed now carries
the donor view locally, with its attribution and license, and changes that
one return declaration to the existing target-proven handle type. All other
fields, methods and inheritance are retained. The getter uses its existing
pointer view of LineRenderer at +0x100, allowing composition with the complete
seed view without changing shared renderer headers. No layout or BFME 2
original header recovery is inferred from the external donor.

The normal build verifies all 67 affected rows, 11 floating literals and one
named import. EH verification reports three EXACT graphs. Both prerequisite
objects retain every external COMDAT name, size and byte/relocation digest:
275 for streak.cpp and one for the getter. Their complete external symbol
facts and relocation-root/edge graphs are identical before and after.
Strict baseline receipts had verified all 68 rows across the three inputs.
The three current previews retain LINKS for 5,575 authored bytes against
index `6fe1089c24` (2026-10-30 04:25). This is prediction, not a new census.
No data/header/identity debt is retired, and no hatch or pin is added.

The destructor's separate inline/out-of-line template cleanup contract and
the mixed Common getter files remain outside this prerequisite.
