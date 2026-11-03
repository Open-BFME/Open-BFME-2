# W3DStreakDraw module-data consolidation, 2026-11-03

`tu_skeleton.py --merge` absorbed `W3DStreakDrawModuleDataDtor.cpp` into
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DStreakDraw.cpp`.
This removes one source file and moves five code rows (0x000D057C, 0x000D0673,
0x007628A9, 0x007628B1, 0x007628BC) into their approved retail TU. The preceding
ownership reconciliation is e49a5abf75. No new donor path or layout provenance
is claimed: the owning module-data/vector declarations reconcile existing
verified bodies.

Verification: [build.log](build.log) records 20/20 code rows and the existing
128-byte data table passing; [eh.log](eh.log) records all three EH graphs EXACT.
`find_declared_unmatched.py` and `check_csv.py` pass (99431 functions unchanged).
The merge engine's census-linked guard accepted both input units.
[link-preview.log](link-preview.log) records a clean targeted link prediction
against the 2026-11-03 20:03 census index, 8661f15284; this is not a census or
real-link measurement. [provider-comparison.json](provider-comparison.json)
compares COFF external definitions in the saved pre-reconciliation seed and
donor objects with the final object: no lost or added providers.

Batch audit after fetching origin/master at 9f938bbe30, outgoing HEAD
e49a5abf75 plus this staged merge: the removed donor is the only source path
change. Combined searches of the old path/basename and directory consumers
found no active tool, hook, workflow, include or build/config consumer requiring
an edit. Intentional old mentions remain in the merge provenance comment,
W3DLaserDraw's historical family comment and reverse/link_status.csv's census
history. functions.csv and tu_map.csv repoint exactly these five rows; the map
was not regenerated. No donor header, Microsoft-header, data-identity or
code-identity debt keys need transferring. The destination's existing
DrawModule, RTS3DScene and W3DStreakDraw header-queue entries remain; a scoped
ms_header_audit scan refreshed its queue with no change. The destination's
existing CameraMarker binding shadow findings remain outside this change.
No pins, aliases or hatch totals change. Byte, data and EH checks verify the
destination afresh; provider selection and affected consumers also receive
the normal outgoing hook audit.

Remaining prerequisites from the dry run: canonical W3DStreakDraw adoption
conflicts with the constructor's RefCountPtr ownership; the separate destructor
needs BfmeStreakObject/Release_Ref lifetime reconciliation; the body uses a
conflicting module-data color projection; ModuleDataCtor2 has a different
base/vector lifetime model. Five donors are left untouched and three mixed
sources remain excluded. Reconcile these views in verified prerequisite
commits before another merge. The earlier canonical-header handoff is
[streakdraw-canonical-qc10-20261031](../streakdraw-canonical-qc10-20261031/README.md).
