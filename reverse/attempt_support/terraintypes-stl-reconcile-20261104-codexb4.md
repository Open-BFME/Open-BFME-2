# TerrainTypes STL assignment reconciliation, 2026-11-04

Prerequisite base: `ea93f15894`. Scope: `Common/TerrainTypes.cpp` and
`WWLib/stlport_vector_nocasepair_assign.cpp`, assignment native `0x00317EBB`
(180 bytes). Claims use `yasinschroeder-codexb4`.

The assignment donor now includes STLport's real vector, allocator, pair and
dispatch-tag definitions instead of privately redeclaring them. It preserves
the existing rowed clear, copy, destruction and allocation workers. A derived
using-declaration exposes the protected clear worker without adding a body.
An explicit function-pointer cast selects the existing const-reference copy
overload when the seed's allocator shim also supplies a by-value overload.
Default initialization of the empty dispatch tag preserves retail's stack
storage; value initialization adds a non-retail store.

VC7.1 C1001 at the declaration-only member-template specialization is avoided
by providing the existing allocation specialization's full body. Both units
use the same inline/noinline definition: COMDAT emission permits their shared
provider, while noinline preserves the assignment's out-of-line call. Explicit
instantiation in TerrainTypes retains its independently rowed allocation body.
The eight-byte copy-element view and placement-copy specialization agree with
the seed and preserve the existing worker identities. These facts establish
compatibility with existing target rows, not a recovered donor type name.

`./build.sh` verifies 31/31 rows across both units, including three literals,
one empty string and the parent's unwind graph. Declared-unmatched checks pass
for both files. `link_check.py` predicts LINKS for both (1051 -> 1051 and
180 -> 180 authored bytes) against census index `40fe1783d7`,
2026-11-04 12:23. This is a local preview, not a census gain. No alias or pin
was added or removed; TerrainTypes keeps its existing allocator alias.

The Common consolidation planner was refreshed after the source changes.
The supported merger rebuilds current TU approvals in memory. TerrainType's
private vector-base destructor remains a separate composition prerequisite;
LINK-095's destructor-binding prerequisite is unchanged.
