# Chunk stream terrain consumer (root20, 2026-11-14)

W3DTerrainVisualLoad.cpp now includes the registered ChunkInputStreamClass.h
instead of its incomplete three-slot private declaration. The sole seek(0) call
becomes absoluteSeek(0), matching canonical slot2 (+8). Native load9213F uses
thiscall and passes one zero dword; its return is unused. Unsigned conversion of
zero and the Boolean return add no caller instructions. This caller alone does
not recover signedness or return type: those come from the shared interface's
native/donor contract. No virtual destructor is introduced.

Normal ./build.sh passes all6 rows, zero string/float refs and one named import.
The complete load EH graph is EXACT. All13 external COMDATs retain their bytes
and relocation identities; none is added or removed. No table is emitted.
Owning adopt --apply and accept both pass; accept retires exactly one of four
served header queue rows. Source, header and object fingerprints are adjacent.
This is shared-source/debt repair, not new unique bytes or a game-runtime result.

## Remaining served consumers

SidesListDataChunks.cpp, SidesListParseCastleTemplateMaps.cpp and
BaseTemplateLibraryParseBaseTemplateFiles.cpp retain their original views and
queue rows. A fresh class:Rva00240000 claim was refused because its footprint
is held by another worker. No source trial or mutation was started there.

Read-only native analysis establishes ctor240000 stores a primary vptr+0,
constructs the vector+4, installs the inner interface+10 and clears+14/+18/+1C:
32B total. Four forwarders24002E/35/3D/45 add+10 and dispatch slots0/1/2/3.
A prospective consumer correction is a4B canonical base plus1C opaque tail,
with all4 nonconst overrides declared, keeping existing constructor throw()
specifications and nonvirtual out-of-line destruction. This preserves the native
extent and zero-offset upcast; it has NOT been compiled or adopted here. Check
that no consumer table appears and preserve all code/data/EH before acceptance.
The provider's flat view and any other source debt remain separate work.

Scratch evidence: build/root-chunk-stream/terrain-before.log,
terrain-prepare.log, terrain-adopt.log, terrain-final.log, terrain-proof.json
and terrain-accept.log. No shared header, provider or ledger was changed.
