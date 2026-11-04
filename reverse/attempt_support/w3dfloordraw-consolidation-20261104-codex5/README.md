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


## Applied merge and outgoing audit

The supported merge absorbed StlSweepW6Rva000CF529.cpp into its approved
W3DFloorDraw.cpp TU: one fewer source file, the same 19 matched rows across
the two former units. It repointed one functions.csv source cell and one
existing tu_map.csv source cell; no map regeneration or approval change.
The destination build passes 19/19; all four checked EH parents are exact.
Frozen-source and staged TU-ownership checks pass. The construction helper
remains force-inlined, with its existing absent-from-retail marker.

The local previews cover seven units before and six after, all clean.
The destination's 798 -> 835 preview bytes absorb the donor's previous 37;
the whole scope stays at 1,310 bytes. The after preview's list-only baseline
of 1,273 omits the removed donor. This is source consolidation, with no new
linked-byte or census gain. The merge guard additionally judges the combined
object's selected COMDATs and outside consumers before accepting it.

Audited origin/master 7835790240e5fd4eb218f001b3f78dbe40d197f8 through
3bbb6f5099fdad5aaa101b871af753a9aad7be70 plus this staged merge. Pending source-path removals
are StlSweepW6Rva000CF529.cpp, HeaderTemplateManagerRva00201B05.cpp and
AttachUpdateXfer.cpp. A combined search of tools, hooks, workflows, Code,
docs and build/configuration files finds only TU provenance comments for
these old basenames. No include or active tooling consumer needs updating.
The destination already appears in docs/doxygen/sources.cfg. Build and
progress tools discover sources from ledgers or the tracked Code tree.

No removed basename remains in active data, identity, header, Microsoft-header,
flag, hatch or body-owner registers. The STL donor held no such debt keys;
destination header debt is preserved. The merge tool refreshed header and
Microsoft-header reports without changing either queue. No pins, aliases,
fold proofs or hatch lines were removed or added. Historical attempt evidence
and link_status.csv census records intentionally retain original paths.
The consolidation planner was regenerated after the merge and its snapshot
check passes. Pre-push link-batch admission remains the publisher's check.

Applied merge commit: ae62f5a6334afe8bfae55e614bb023ba50ad9366.
