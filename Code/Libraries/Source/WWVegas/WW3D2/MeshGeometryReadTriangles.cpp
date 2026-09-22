// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME1 MeshGeometryLoading.cpp triangle reader, adapted to BFME2.
// Target read_chunks dispatches chunk 0x20 to this body at call 0x16D3C3.
// Target chunk reads use 32-byte W3dTriStruct records, 16-bit indices and
// plane equations. Target PolySurfaceType is at +0x58; /G7 /arch:SSE matches
// the scalar SSE copies and distance negation. Full body: RVA 0x16B020, 191B.
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "vector3.h"
#include "sphere.h"
#include "multilist.h"
#include "chunkio.h"
#include "sharebuf.h"
#include "vector4.h"
#include "vector3i.h"
#include "w3d_file.h"

typedef Vector3i16 TriIndex;

class MeshGeometryClass
{
protected:
    bool read_triangles(ChunkLoadClass &cload);
    enum FlagsType { DIRTY_PLANES = 0x00000002 };
    void Set_Flag(int flag, bool onoff)
    {
        if (onoff) Flags |= flag;
        else Flags &= ~flag;
    }
    int Get_Polygon_Count(void) const { return PolyCount; }
    TriIndex *get_polys(void) { return Poly->Get_Array(); }
    Vector4 *get_planes(bool create = true);
    uint8 *Get_Poly_Surface_Type_Array(void) { return PolySurfaceType->Get_Array(); }

    char BeforeFlags[0x18];
    int Flags;
    char BeforePolyCount[8];
    int PolyCount;
    int VertexCount;
    ShareBufferClass<TriIndex> *Poly;
    char BeforeSurfaceTypes[0x58 - 0x30];
    ShareBufferClass<uint8> *PolySurfaceType;
};

// ?read_triangles@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_triangles(ChunkLoadClass &cload)
{
    W3dTriStruct tri;

    TriIndex *vi = get_polys();
    Set_Flag(DIRTY_PLANES, false);
    Vector4 *peq = get_planes();
    uint8 *surface_types = Get_Poly_Surface_Type_Array();

    for (int i = 0; i < Get_Polygon_Count(); i++) {
        if (cload.Read(&tri, sizeof(W3dTriStruct)) != sizeof(W3dTriStruct)) {
            return false;
        }

        vi[i].I = tri.Vindex[0];
        vi[i].J = tri.Vindex[1];
        vi[i].K = tri.Vindex[2];

        peq[i].X = tri.Normal.X;
        peq[i].Y = tri.Normal.Y;
        peq[i].Z = tri.Normal.Z;
        peq[i].W = -tri.Dist;

        surface_types[i] = (uint8)tri.Attributes;
    }

    return true;
}
