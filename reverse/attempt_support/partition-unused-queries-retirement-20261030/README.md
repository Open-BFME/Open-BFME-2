# Retire four unused donor queries and their private callback

Remove iterateAllObjects (199 B), tryPosition (1,050 B), getMostValuableLocation
(653 B) and getNearestGroupWithValue (380 B). These are compiled donor-entry
sizes, not newly recovered retail bytes. Each entry has only a debug incoming
reference, no other indexed touching object and no row/pin. Remove the latter
query's private cellValueProc callback (306 B), declaration and unused parameter
struct too: its only runtime address reference is inside that removed query.
This makes no retail-dead-strip or target method-identity claim.

The two query EH graphs are retired by their COFF parent associations, including
their two SafeSEH records. GeometryInfo's five-byte destructor copy is referenced
only by the removed tryPosition cleanup. One 99999.0 literal has only that
parent's reference. Every remaining parent EH graph is compared by parent and
associated-section identity, not label adjacency. All four native rows and
549 retained external code bodies/relocations are unchanged; every remaining
loadable definition, non-debug section and symbolic relocation is preserved.

Other naturally unused copies disappear: Object's AI getter, AI's locomotor
getter, PathfindCell's enum getter and Coord3D::set. AI's remaining provider is
an identical seven-byte copy. The fresh 35-byte native Coord3D owner at
0x000036AE precedes Partition and stays selected. Both remaining PathfindCell
copies are current and debug-only; they read dword+0x0C whereas Partition's
copy read byte+6. No layout, native identity or byte equivalence is claimed for
that changed but unreferenced selection. The fresh owner/consumer controls
and the before/after bounded preview are recorded in proof.json.

Five undefined references disappear; only the relationship-list and quick-path
ones were unresolved. The final bounded result is U8 -> U6; all other blockers
and 4,593 authored linking bytes in the five-source cohort remain unchanged.
The 31 retained parent EH graphs are identical. Normal/strict verification
passes all four source rows; fresh controls verify the native 35-byte
coordinate owner and both remaining enum-getter units. Keep the six
remaining names and their live users: PossibleToEnter, FreeOfFog, distance
dispatch, getClosestObjects, AcceptOnSquad and contact processing/update.
Retire only the four existing query markers via the hatch tool with their
bodies. No native coverage, full-image clearance or census gain is claimed.
