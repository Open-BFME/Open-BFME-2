# STLport allocator adoption, qc-12
Basee78b61f1b2; queue5081 served four units. Glo012F1024Item.cpp and
FXShaderRenderer.cpp already include real vector/allocator headers on this
base; no new adoption credit for those. The remaining two private primaries
are in LivingWorldCampaignAct.cpp and FXShaderRendererFlushRenderingTasks.cpp.

First donor: replace the empty private _STL::allocator primary in the flusher
with an explicit include of the pinned STLport stl/_alloc.h and its required
STLport compile context. Existing private vector and sort declarations are
unchanged; allocator template arguments keep the same library-qualified names.
The allocator is nonpolymorphic and has no donor virtual slots to replace.
No library header, specializations, hatches, aliases, pins or tool code changes.

Baseline allfour units118/118 code and1data row pass. First adoption3/3 exact;
header acceptPASS. All externally defined CODE bodies in the flusher retain
identical complete bytes and relocation triples (attached proof), with no added
or lost functions. Frozen checks pass before/after. This is standard upstream
allocator identity from the pinned header, not an inferred private class layout.
Second donor is handled separately; no progress is claimed for an unverified
trial. Shared obstacle register remains held elsewhere; this is proposed entry.
No census or full-image linking gain is claimed from link-check acceptance.
