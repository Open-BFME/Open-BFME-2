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

## Applied merge and compatibility audit

`tu_skeleton.py --merge` absorbs only the resize donor and repoints its sole
function and TU-map source cell. The committed map is not regenerated. This
removes one Code source file, retaining all seven rows. The new source passes
its frozen check, normal byte build, strict provider preparation, string and
import/float-reference checks. The ordinary preview retains 440 authored bytes
in the destination (367 seed + 73 donor); this is relocation of existing
coverage, not a linking gain.

The merged object's 19 normalized code/relocation definitions, strong names,
roots and reference edges exactly equal the two reconciled objects' union.
The only removed undefined is fillInsert, now defined in the same object.
The resize's erase target stays with Rva007D85C0FilterShutdown.cpp at 0x002A133B;
the fill target is the unchanged 0x000CA1EE body in the destination. The merge's
census LinkGuard accepts the retired-donor composition and selected-provider
bindings. Broader outgoing-consumer confirmation is separately qualified below.

Register review: neither source has code-identity, data-check, hatch, flag,
canonical-header or Microsoft-header queue keys to transfer or retire. The
seed's two pool-name/guard globals in data_ledger.csv retain their owner.
The Matrix3D/Vector4 queue entries stay on the rejected foot-location source.
No baseline or whitelist is edited; the Microsoft-header check passes.

The path-consumer audit covers both deletions pending over origin/master
(e1f46279c7): this resize donor and the previously queued Rva00451EACMethod.cpp
SpecialAbilityUpdate donor. Searches of tools, hooks, workflows, source includes,
docs and reverse registers find only source provenance comments, historical
attempt evidence, documentation and the last census's link_status.csv. No active
old-path tool/include/build consumer needs a change. Historical references and
census status are retained. Both moved rows resolve to their current source
owners. The consolidation planner is regenerated after composition and its
`--check build/consolidation` currency check passes. The tool's single-cell
TU-map repoint accompanies the core ledger change; no approval is invented.

Strict preparation also verifies 68/68 rows in the five explicitly required
current providers/callers (HugeFourLegs, DockUpdateCtor, default resize,
SpecialAbilityUpdate and its Run helper). A bounded ordinary preview is 4/4
LINKS for the merged seed, HugeFourLegs, DockUpdateCtor and default resize:
3,272 bytes after composition equals their previous 3,199 plus the absorbed
73-byte donor. This is the same census cohort, not a headline measurement.

The staged-tree outgoing batch audit is **INCONCLUSIVE**: the available index
is still `12b9e7a7c0`, older than outgoing base `e1f46279c7`, and the broader
affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt.
The five initial missing receipts were prepared successfully before this verdict.
Do not treat it as full-image clearance. Carry the pending published source
moves, resize callers and wider selected-provider/consumer scope into the next
scheduled census. No direct census or smoke runner is started here.
