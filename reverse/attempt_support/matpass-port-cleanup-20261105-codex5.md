# MaterialPass port cleanup, 2026-11-05

Inspected parent: `2032dce9c5f749286da6034c89e235b3192cc50d`.
Scope: `Code/Libraries/Source/WWVegas/WW3D2/matpass.cpp`.

Removed the three unrowed Zero Hour pointer-signature accessor definitions and
their existing `present-unmatched` markers:

- `?Set_Texture@MaterialPassClass@@QAEXPAVTextureClass@@H@Z`
- `?Get_Texture@MaterialPassClass@@QBEPAVTextureClass@@H@Z`
- `?Get_Material@MaterialPassClass@@QBEPAVVertexMaterialClass@@XZ`

These definitions have no rows under those names. Current coverage already
contains a native owning-wrapper texture setter at 0x0013EEB0 in
`Rva0013EEB0Cluster.cpp`, a wrapper getter at 0x0013EF40 in
`Rva0013EF40Siblings.cpp`, and a material accessor at 0x0013EF70 in
`MaterialPassClassDestructor.cpp`. Those bodies and their current identities
are untouched; the nearby placement and semantic leads do not establish the
removed donor signatures as BFME 2's signatures.

## Verification

- `./build.sh Code/Libraries/Source/WWVegas/WW3D2/matpass.cpp`: 3/3 exact,
  72 bytes; string, float and import-reference checks pass.
- `find_declared_unmatched.py`: all defined functions accounted for. The existing
  absent-from-retail Peek_Texture emission anchor remains.
- Compared the saved pre-edit object with the normal build's object using
  `link_census.comdat_bodies` and `object_symbols`: 11 -> 8 COMDATs; all eight
  retained digests/sizes identical. Exactly the three names above disappear;
  no added definitions, changed references, weak routes, aliases or /INCLUDEs.
- Fixed-string search for those three decorated names across all 25,275 cached
  `build/match/**/*.obj` files after rebuilding: zero occurrences. This is a
  compiled-cache consumer check, not a new game census.
- The existing array anchor and optimization pragmas stay: a trial removal
  changed the shared `??_H` COMDAT despite matching all three rows. Restoring
  the block restores its original digest.
- `link_check.py --prepare-current`: strict current byte-verification receipt.
  Ordinary `link_check.py`: LINKS, 72 -> 72 bytes against census
  2026-11-05 05:17 at `c95fcfcfcd`. No linked-byte gain is claimed.
- `data_check.py`: zero findings. `--converged`: 11 addresses, zero second
  names and zero unjudged rows. No data/identity/header register keys for this
  source were removed.
- `hatch_counters.py --update`: present_unmatched 2322 -> 2319; only these
  three keys retire. Both optimization entries remain.

## Consolidation prerequisite

The six-donor matpass dry-run did not merge: carried compiler flags lose rows,
private reference-count views collide, and the sibling accessor units need
compiler/layout reconciliation. No source paths or ledger rows moved. This
cleanup retires seed debt without claiming that those blockers are resolved.
