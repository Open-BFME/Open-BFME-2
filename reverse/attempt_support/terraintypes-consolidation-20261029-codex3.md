# TerrainTypes consolidation, 2026-10-29

Prerequisite base: `fd13749022`; merge base after runner rebase: `be006165be`.
Census index: `85f6b7f40c` (2026-10-29 15:08).
The current committed TU map is stale; `tu_skeleton.py` rebuilt approval in
memory. No regenerated map is included. The Common consolidation planner's
original-path and donor evidence was reviewed; its stale-map routes are hints,
while the merge tool's rebuilt approval governs movement into `TerrainTypes.cpp`.

## Verified prerequisite

`stlport_vector_nocasepair_allocate_copy.cpp`, native `0x00317D5C` (45 bytes),
now uses the existing STLport vector, allocator, pair and dispatch-tag headers.
It retains the existing allocator binding and rowed `0x00317CF2` copy worker.
An ordinary default-initialized empty tag preserves retail's uninitialized tag
storage; value initialization introduced an extra byte store. The duplicated
allocator alternatename directive was removed, retaining one binding.

`./build.sh` matches 1/1 rows, frozen-file validation passes, and `link_check.py`
predicts LINKS, 45 -> 45 bytes against the index above. These are local checks,
not a new census result.

## Remaining donors

The initial supported merge dry run accepted no donors:

- Allocation and assignment donors both privately redeclared STLport templates,
  conflicting with the seed's full headers. The allocation prerequisite above
  removes its compile barrier.
- `tu_views.py --dry-run --class TerrainType` reports a real type conflict at
  +0x10: the constructor/destructor use `vector<ScienceType>`, while assignment
  uses a private `vector<int>` view. The second vector at +0x24 also has
  inconsistent ScienceType, pair-vector and external-cleanup views. Retail
  calls the same folded empty-base constructor at `0x00211E58` for both fields;
  that fact alone does not prove their element identities.
- The seed's `TerrainType` is a padded lookup/assignment view. It needs the
  verified member layout and virtual destructor before ctor/dtor composition.
  Its next pointer at +0x20 must retain its identity.
- `NoCaseTreeValue4` views already agree on their sole four-byte field; a
  cosmetic rewrite alone does not resolve any rejected donor.

A full-header assignment trial declared the existing allocation, clear,
const-reference copy-dispatch and uninitialized-copy providers explicitly.
The existing bfmealloc shim's by-value copy-dispatch overload requires selecting
the const-reference overload deliberately. A public using-declaration in a
derived access bridge avoided changing the protected clear provider's identity.
VC7.1 then failed with C1001 in `Utc/src/P2/main.c:148` at the call to the
declaration-only member-template specialization `_M_allocate_and_copy`.
An explicit template argument and a noinline declaration did not avoid the
failure. The assignment donor was restored; no nonmatching trial remains in
`Code/`. A future trial should isolate that old-compiler specialization issue
before attempting the broader TerrainType layout reconciliation.

The earlier `uw_0077a797` deferral still applies: do not repoint its generated
owner merely because the constructor's EH graph matches; its relocation needs
the correct member destructor binding (LINK-095).

## Applied consolidation and compatibility audit

The refreshed Common planner snapshot passed `name_lane.py consolidate --check`
before applying the supported merge. Its quoted-include review covers the
existing `ascii_string.h` and `subsystem_interface.h` shim search paths; the
merged object was compiled at its final path with the combined include flags.
`tu_skeleton.py --merge Code/GameEngine/Source/Common/TerrainTypes.cpp` accepted
the seed and allocation helper, rejected the other four donors on their known
private-view conflicts, and left all three mixed sources intact. It removes one
source file, retaining 24/24 matched rows. Approval was rebuilt in memory; the
only committed TU-map edit repoints the moved row's source column.

`./build.sh` passes 24/24, three literals and one empty-string reference.
Renumbered unwind labels are verified through parent EH data. Declared-unmatched,
`check_csv.py`, staged TU ownership and code identity pass (24 rows, zero new
identity findings); shadow data checking reports zero findings. Ordinary
`link_check.py` predicts LINKS, 796 -> 841 authored bytes, including the absorbed
45-byte helper. The merge guard preserves the six census-linked candidate units
and their existing provider bindings. These are local proofs, not a new census
or a linked-byte gain.

The complete pending batch was audited against `origin/master` at `f014d1c08f`,
through `be006165be` plus this merge. Its sole source-path deletion is the
allocation helper absorbed into TerrainTypes. Repository-wide old-path/basename
searches cover active tools, hooks, workflows, includes, build/configuration
files, source registries and docs. No active path consumer needs adjustment.
Remaining mentions are the merge provenance comment, this historical handoff
and `reverse/link_status.csv`'s last-census record; the scheduled census owns
that snapshot. The active functions ledger, TU-map source and hatch register
now name the destination. There are no data/identity baseline or header-queue
keys for either owner. The merger refreshed destination header and Microsoft
header classifications, preserving unrelated queue entries; neither queue
needed a diff. The existing allocator alternatename transfers with its count
kept at one; no debt key is retired by the merge.

Strict preparation passes the five pending changed providers (202/202 rows)
and the directly affected NoCase assignment provider (1/1), without changing
census/index/status. The final outgoing link audit remains INCONCLUSIVE: its
index predates the outgoing base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and the changed provider scopes into the next
scheduled census. No full consumer closure or new census result is claimed.
