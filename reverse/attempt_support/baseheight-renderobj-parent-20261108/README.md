# Terrain destructor adopts its real RenderObj parent

The served BaseHeightMapRenderObjClass primary table used a one-slot RO0
view that placed the deleting destructor at slot zero. The destructor source
now includes canonical rendobj.h with BFME_RO_DTOR_DECL_ONLY, removing the
RO0/RO8/ROC4 and private RenderObjClass declarations. An explicit two-slot
DX8_CleanupHook view, already proved by the canonical BaseHeightMap header
and retail's +0xC4 table, preserves the actual cleanup interface and offsets.
Its ReleaseResources/ReAcquireResources declarations use the existing rowed
virtual spellings. No names, rows, pins or global bindings are changed.

Both private and normal builds preserve all 26 code rows. The normal EH
verifier (positional source argument, not --sources-from) proves the one
parent graph EXACT; all parent-proven funclets remain exact. The source is
not frozen. Private LinkGuard passes; ordinary current-index prediction
preserves 817 linked bytes. Owning RenderObjClass header acceptance retires
exactly its one source queue row. The BaseHeightMap class queue row stays.

The source primary table grows from one slot to 129, with Delete_This at
slot zero and the deleting destructor at slot one. Its cleanup table now
contains the two rowed resource callbacks instead of a destructor. This is
source inheritance/ABI repair, not a claim that the entire terrain table is
recovered: retail's primary has 148 slots, and SnapC8 still exposes only one
of Snapshot's four slots. The remaining BaseHeightMap member/lifetime and
full interface adoption must preserve these exact destructor/EH bodies.
The bounding-getter alignment refusal is also separate (LINK-619).

The old RO0/RO8/ROC4 data-ledger spellings are retained as historical ownership;
current compiler table names come from the row's actual DIR32 bindings. No
data row is deleted to silence the queue. Actual image binding and runtime,
and the next real-link queue outcome, remain unverified. Gate results and
table extents support only the scope stated here.
