// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/
// Trial A (shared offset/CSE cause test, seat-13-r9): 0x0016AE70 194B.
// Target facts: VertexCount +0x28 (shared with MeshModel +0x28 and 16AF40),
// false path via +0x30, true path NEW_REF ShareBuffer at +0x34 with literal
// "MeshGeometryClass::Vertex" then zeroing, bulk Read via 0x6151A0, ret8.
// Donor facts: BFME1 MeshGeometryReadVertices.cpp (bool, chunk 0x02/0xC00)
// uses NEW_REF + Get_Count + Get_Array + memset(buffer,0,bufcount*sizeof)
// then per-vertex loop (target is bulk, no loop/SKIN per bank evidence).
// Shared-cause hypothesis under test: retail keeps count (not byte_count)
// enregistered and emits lea+add+add TWICE (rep-stos dword-count + Read
// byte-count); merged single-lea shape is 191B bank, reload shape is 201B.
// This spelling separates the zeroing product (buffer_count via Get_Count)
// from the Read/compare products (Get_Vertex_Count() twice, 16AF40 pattern)
// so the compiler cannot merge them into one kept byte_count.
#include "always.h"
// Retail's out-of-line RefCountClass deleting-dtor copy is the /O1 form
// (pop ecx after the delete call); this TU builds /G7 which emits add esp,4
// instead. Compile just the base class for size so our COMDAT matches the
// first copy in link order. Code this TU's rows inline keeps this TU's flags.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "vector3.h"
#include "w3d_file.h"
#include "sharebuf.h"
#include "chunkio.h"
#include <string.h>

// Their byte-matched specializations live in MeshGeometryShareBufferInstantiations.cpp.
// Do not implicitly re-emit their virtual destructors in this TU.
template <> ShareBufferClass<Vector3>::~ShareBufferClass();

class MeshGeometryClass {
protected:
    bool read_vertices(ChunkLoadClass &cload, bool use_secondary);

    char pad_00[0x28];
    int VertexCount;                          // target this+0x28
    void *Slot2C;                             // field identity unproven
    ShareBufferClass<Vector3> *VertexSlot30;  // target this+0x30
    ShareBufferClass<Vector3> *VertexSlot34;  // target this+0x34
    int Get_Vertex_Count() const { return VertexCount; }
};

// ?read_vertices@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@_N@Z
bool MeshGeometryClass::read_vertices(ChunkLoadClass &cload, bool use_secondary)
{
    Vector3 *loc;
    if (use_secondary) {
        if (VertexSlot34 == NULL) {
            VertexSlot34 = NEW_REF(ShareBufferClass<Vector3>,
                (VertexCount, "MeshGeometryClass::Vertex"));
            int buffer_count = VertexSlot34->Get_Count();
            Vector3 *buffer_array = VertexSlot34->Get_Array();
            memset(buffer_array, 0, buffer_count * sizeof(Vector3));
        }
        loc = VertexSlot34->Get_Array();
    } else {
        loc = VertexSlot30->Get_Array();
    }

    bool matched = cload.Read(loc, Get_Vertex_Count() * sizeof(Vector3))
        == Get_Vertex_Count() * sizeof(Vector3);
    return matched;
}
