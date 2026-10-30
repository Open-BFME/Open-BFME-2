# Quadruped vector reconciliation and consolidation

Scope: `W3DQuadrupedDraw.cpp` and its approved `Coord3DVectorResizeValue.cpp`
donor. Starting revision: `383fb1b98d`. Claims: codex3's file scopes for the
seed and four candidate donors.

## Evidence and prerequisite

Target facts: the row at 0x000CA2F3 is a 73-byte by-value
`_STL::vector<Coord3D>::resize(unsigned, Coord3D)`; its calls resolve to
`vector<Gen_p12pod>::erase` and `Rva000CA1EEVector::fillInsert`. The latter
is the existing 256-byte row at 0x000CA1EE. The resize's pointer arithmetic
and the insertion's accesses establish three pointers and a 12-byte stride.
They do not establish the complete original class definition.

The vendored generic vector declares resize with a const-reference argument.
The old resize donor instead redeclared the allocator and vector templates,
which collided with the seed's STLport headers. Give the two views an
identical explicit Coord3D vector specialization using the real allocator and
allocation proxy. Retain the vendored inline helper bodies, including overflow:
a declaration-only overflow changes temporary-tag initialization and loses the
fill-insertion match. This is a local evidenced view, not a recovered upstream
source definition. No original BFME translation-unit path is newly claimed.

Verification before consolidation:

- `./build.sh` verifies 7/7 rows, one string, and the parent-owned EH funclet.
- Both frozen-file checks report all defined functions already matched.
- Strict preparation accepts both explicit providers with reusable receipts.
- Before/after object facts retain all 18 seed definitions' normalized
  code/relocation digests, its strong names, undefineds, roots and reference edges.
  Resize retains its one definition's digest and two undefined targets; as an
  out-of-line member of the explicit class specialization, it becomes strong
  instead of a discardable template instantiation. Its two existing call edges
  therefore become roots. No new symbol name or dependency is introduced.
- Ordinary before/after previews against index `12b9e7a7c0` both retain
  two clean units and 440 bytes (367 + 73); no census gain is claimed.
- `tu_skeleton.py --merge ... --dry-run` accepts the seed and resize donor,
  preserving all seven rows and its census link guard.

Remaining candidates: the constructor requires reconciliation of the actual
W3DScriptedModelDraw hierarchy and vtable views; the default resize retains a
conflicting private vector template and constructor view; foot locations needs
Matrix3D/Vector4 adoption and its own draw-interface/vector declarations
reconciled. Seven mixed files stay outside this merge. These are existing
cleanup prerequisites, not lost coverage.

The committed TU map is stale; the merge tool rebuilds approval in memory.
The destination is approved provisionally, rather than by a retail __FILE__
anchor. WorldBuilder's related path is evidence for that binary only.
