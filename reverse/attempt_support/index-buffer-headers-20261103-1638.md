# Canonical IndexBufferClass adoption, 20261103-1638

The supported WW3D2 consolidation planner and fresh in-memory TU map put both
WriteLock bodies in dx8indexbuffer.cpp. Dry composition is currently blocked
first by the void/bool mutex declaration, with three header prerequisites.
Adopt existing IndexBufferClass.h in DynamicIBAccessWriteLock.cpp. The header
establishes the20-byte base and its RefCountClass primary base: count at+4,
engine_refs+8, index_count+12, type+16, Delete_This slot0. Both derived pointers
remain at+20. No allocation, vtable definition or class identity is invented.

The prior TU-only release member avoids a known losing COMDAT. Preserve its
decrement/zero-test/Delete_This through a TU-local static fastcall helper with
the existing helper spelling; ECX remains the receiver. This removes no
genuine call and adds no dummy anchor. Both complete retail bodies,218B ctor
and120B destructor, pass the normal native relocation/EH checks and the frozen
gate. The owning header verdict PASS retires exactly one IndexBufferClass
queue row. This is not338 new bytes. The raw BfmeIndexBuffer9 call-table view,
mutex lifetime, aliases and compiler flags remain. Complete COFF comparison
records the helper's changed C++ linkage separately from the retail row checks.

The canonical mutex-header return mismatch cannot be repaired in this pass:
TerrainTracksRenderObjClassCreateBuffers.cpp is held by another contributor.
The shared header and every affected source remain unchanged; scope claims
were released. Native provider dx8wrapper.cpp returns bool at0x00120F50;
the guard header declares void. Resolve that shared declaration consistently
once all affected scopes are available, not by weakening the merge check.
No source moves, full-link, runtime, RAM or crash improvement is claimed.
