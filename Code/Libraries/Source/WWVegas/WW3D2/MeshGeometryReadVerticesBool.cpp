// cl: /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// auto_inline(off) keeps that /O1 iterator out of line: otherwise the /O2
// ShareBufferClass<Vector3> constructor inlines it and drops the Vector3
// construction loop that retail's copy (0x00169780) still calls ??_H for.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
#pragma auto_inline(off)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma auto_inline(on)
#pragma optimize("", on)

// Their byte-matched specializations live in MeshGeometryShareBufferInstantiations.cpp.
// Do not implicitly re-emit their virtual destructors in this TU.
template <> ShareBufferClass<Vector3>::~ShareBufferClass();

// Keep the reference RefCountClass inline definitions and the canonical list base.
#define BFME2_WWLIB_REFCOUNTDATA_H
#include "../WWLib/MultiListObjectClass.h"
#define MULTILIST_H
#include "MeshGeometryClass.h"

// ?read_vertices@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@_N@Z
bool MeshGeometryClass::read_vertices(ChunkLoadClass &cload, bool use_secondary)
{
    Vector3 *loc;
    if (use_secondary) {
        if (slot34 == NULL) {
            slot34 = NEW_REF(ShareBufferClass<Vector3>,
                (VertexCount, "MeshGeometryClass::Vertex"));
            int buffer_count = slot34->Get_Count();
            Vector3 *buffer_array = slot34->Get_Array();
            memset(buffer_array, 0, buffer_count * sizeof(Vector3));
        }
        loc = slot34->Get_Array();
    } else {
        loc = Vertex->Get_Array();
    }

    bool matched = cload.Read(loc, Get_Vertex_Count() * sizeof(Vector3))
        == Get_Vertex_Count() * sizeof(Vector3);
    return matched;
}
