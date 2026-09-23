// ?read_vertices@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@_N@Z
// partial score=0.8402061856 date=2026-09-23
// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/
// Candidate identity: BFME1 MeshGeometryClass::read_vertices semantics paired
// with BFME2 target 0x16AE70 by read_chunks: W3D chunk 0x02 dispatches through
// 0x16D385 and calls this body with (cload, false).
// Target evidence: VertexCount is read at this+0x28; the false path reads via
// the pointer at +0x30. The true path allocates a ShareBuffer at +0x34 using
// target literal "MeshGeometryClass::Vertex" and zeroes it before reading.
// Offsets/behavior are target facts; member labels are not confirmed donor
// layout. BFME1 meshgeometry.cpp::read_vertices reads W3dVectorStruct data;
// the bool selector and +0x34 allocation are target-specific adaptation.
// Ghidra boundary 0x16AE70, 194B; ret 8 at 0x16AF2F..31 (end 0x16AF32). This C++ candidate
// has the correct target behavior but compiles to a 191B near match so far.
#include "always.h"
#include "refcount.h"
#include "vector3.h"
#include "w3d_file.h"
#include "sharebuf.h"
#include "chunkio.h"
#include <string.h>

class MeshGeometryClass {
protected:
    bool read_vertices(ChunkLoadClass &cload, bool use_secondary);

    char pad_00[0x28];
    int VertexCount;                          // target this+0x28
    void *Slot2C;                             // field identity unproven
    ShareBufferClass<Vector3> *VertexSlot30;  // target this+0x30
    ShareBufferClass<Vector3> *VertexSlot34;  // target this+0x34
};

bool MeshGeometryClass::read_vertices(ChunkLoadClass &cload, bool use_secondary)
{
    Vector3 *loc;
    if (use_secondary) {
        if (VertexSlot34 == NULL) {
            VertexSlot34 = NEW_REF(ShareBufferClass<Vector3>,
                (VertexCount, "MeshGeometryClass::Vertex"));
            VertexSlot34->Clear();
        }
        loc = VertexSlot34->Get_Array();
    } else {
        loc = VertexSlot30->Get_Array();
    }

    unsigned int byte_count = VertexCount * sizeof(W3dVectorStruct);
    return cload.Read(loc, byte_count) == byte_count;
}
