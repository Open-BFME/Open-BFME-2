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

Second donor: campaign act replaces its private allocator primary with the same
real header and required STLport include context. Its custom vector/storage
views and verified lifetime provider names are untouched. 48/48 native code
rows and1data row pass; header accept and post-edit frozen check PASS.
All40 prior complete externally defined code functions retain identical bytes
and relocations, with none removed or changed. The public header additionally
emits its empty allocator<BfmeE16> destructor (single RET). Every COFF reference
to that body/section was checked: its sole incoming relocation is .debug$F,
with zero runtime code/data/EH references. No import-inline suppression or
other hatch is introduced to hide it. Proofs are campaign-code-comparison.json
and allocator-dtor-reach.json. Real allocator lifetime/state is empty, and all
native member cleanup paths and complete EH graphs must still pass the hooks.
Both real private allocator copies served by5081 are now replaced. The other
two served sources already used public headers and earn no new adoption credit.
