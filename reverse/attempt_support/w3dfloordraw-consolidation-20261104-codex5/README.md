# W3DFloorDraw consolidation prerequisite

Inspected revision: 394c96f5b0; 2026-11-04; worker yasinschroeder-codex5.

The supported consolidation planner and current in-memory TU map approve
0x000CF529 for the floor-draw TU. This is an existing row, not new coverage.
Its eight-byte neutral element footprint and call to Rva000CF4D6Construct
are target facts; the original element identity remains unknown.

After the construction specialization in 394c96f5b0, the combined object
still emitted a 75-byte exception-enabled __uninitialized_fill_n body:
EH_prolog, the placement-copy call at +0x22, and a cleanup/rethrow path.
The native body is a 37-byte loop without that handler. The containing TU
has included <vector> before the donor's exception-disabling define could
have any effect. No row extent should change to accommodate this mismatch.

Specializing the fill loop directly removes the empty cleanup/rethrow
handler for this trivially destructible element. Construction still calls
the same rowed provider; exceptions propagate directly. The local current
iterator preserves the native register allocation. ./build.sh verified 1/1
rows; find_declared_unmatched.py passed; the link preview stayed clean,
37 -> 37 bytes, against census 2026-11-03 20:03 at 8661f15284.

The supported merge dry run accepts the floor-draw TU plus the STL donor,
with 19 matched rows and its census-linked-unit guard passing. The other
five standalone donors remain compile-blocked by inconsistent private
W3DFloorDraw views: missing constructor/xfer declarations, typed module-data
pointer mismatch, or conflicting drawable declarations. The canonical
class scope is held by another worker. Do not hand-merge these donors or
split the mixed-file donors inside a merge; reconcile their views through
the header lane first. No census or real-link gain is claimed here.
