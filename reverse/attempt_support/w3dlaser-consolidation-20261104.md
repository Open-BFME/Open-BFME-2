# W3DLaserDraw consolidation prerequisites, 2026-11-04

Inspected revision: `ced2472c437d38a56b4811f6186f9416d73f1e3b`.
Scope: the approved `W3DLaserDraw.cpp` TU and its four clean donors,
selected and file-claimed by `next_work.py --claim`.

## Verified cleanup

`Code/Libraries/Source/WWVegas/WWLib/stlport_vector_assetreference_overflow.cpp`
uses a local `__forceinline` unsigned `max` helper instead of three optimisation
pragmas. `./build.sh` passes both rows: overflow at RVA 0x000C9C17 (178 bytes)
and push_back at RVA 0x000C9D01 (55 bytes), including string, float and import
reference checks. `find_declared_unmatched.py` finds no unrowed definitions.
Both ordinary and converged `data_check.py` pass with zero findings.
`hatch_counters.py --update` confirms pragma_optimize 1768 -> 1765.
Only those three hatch keys leave in this change; two unrelated stale
W3DModelDraw present-unmatched keys found by the full scan are preserved.
No source paths, ledger rows, symbols or aliases move.

`link_check.py` against the published-index revision `5a13f2cd61`
(2026-11-04 02:25) reports this source LINKS, 233 -> 233 predicted linked
bytes; its current object comes from the verified source/dependency cache.
This is a per-unit preview, not a new census measurement. `check_csv.py`
passes (99,433 function rows).

## Consolidation trial (no merge applied)

The supported planner was run under the Drawable/Draw directory; its packet
retains stale-map and mixed-routing warnings. `tu_skeleton.py` rebuilt the
TU map in memory, found 38 approved rows, and rejected all four clean donors:

- BfmeConstructor: duplicate RefCountPtr template from
  BFME2ParticleTextureHandles.h versus the seed's ref_ptr.h.
- BfmeDoDraw: duplicate AsciiString through the Zero Hour include environment.
- Destructor: its void-pointer Rva000C9A12 view conflicts with the seed's
  typed RefCountPtr<TextureClass> vector view.
- AssetReference overflow: byte mismatch in the composed unit.

The merge guard identified all five original units as census-linked. These
are source-consolidation prerequisites, not newly demonstrated link losses.
No file-count, TU-approval, linked-byte or census gain is claimed.

`tu_views.py` cannot unify the major laser/module-data classes because their
base clauses differ. The OrnamentData trial was restored after one byte
failure (the shared declaration also introduces its default constructor);
LaserDrawInterface already has identical declarations.

## Header-lane false rejection

An explicit `const AssetReference *` receiver removes the existing chained
member-binding ambiguity in BfmeConstructor. The next adoption trial stops
before compilation: the include scanner follows Ole2.h's inactive Macintosh
include `macname1.h`, which is absent from this SDK. The receiver-only edit
was restored too. The blocked verdict is recorded with `re_log.py`; no
AssetReference header-queue row retires.

Next useful work: repair that include-scan false rejection independently,
then retry AssetReference adoption. Reconcile RefCountPtr/AsciiString include
environments and the typed vector view before repeating the TU merge.
