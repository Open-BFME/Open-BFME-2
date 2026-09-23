// cl: /Ireference/shims/bfmerendobj /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
** BFME1 Reset_Geometry lifecycle adapted to independently verified BFME2 offsets,
** target buffer types, literals, and retail body at RVA 0x0016A320.
*/
#include "rendobj.h"
#include <string.h>
#include "refcount.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "wwdebug.h"
#include "wwmemlog.h"

// The +0x5C slot's source element identity is unknown. Retail construction,
// vtable and allocation establish only a ShareBuffer specialization with
// 16-byte elements and the raw-array lifecycle implemented here.
// Constructor169B00 and dtor169E60 share vtableBD4418; its deleting-dtor
// slot points to169E40, which calls169E60. Names here are descriptive.
struct MeshGeometryOpaqueElement16 { unsigned char bytes[16]; };
class MeshGeometryOpaqueBuffer16 : public RefCountClass {
public:
    MeshGeometryOpaqueBuffer16(int count, const char *name, int alignment = 0);
    // Target keeps this raw-array cleanup out of line.
    __declspec(nothrow) __declspec(noinline) virtual ~MeshGeometryOpaqueBuffer16()
    {
        delete [] RawBuffer;
    }
protected:
    MeshGeometryOpaqueElement16 *RawBuffer;
    MeshGeometryOpaqueElement16 *Array;
    int Count;
    int Alignment;
};

MeshGeometryOpaqueBuffer16::MeshGeometryOpaqueBuffer16(int count, const char *name, int alignment)
    : Count(count), Alignment(alignment)
{
    if (Alignment == 0) {
        RawBuffer = new MeshGeometryOpaqueElement16[Count];
        Array = RawBuffer;
    } else {
        RawBuffer = (MeshGeometryOpaqueElement16 *)new char[Count * sizeof(MeshGeometryOpaqueElement16) + Alignment];
        Array = (MeshGeometryOpaqueElement16 *)(((unsigned int)RawBuffer + Alignment - 1) & ~(Alignment - 1));
    }
}

// Target-local layout view: vptr at 0, MeshName at 0x10; typed vectors retain
// physical array slots +0x30/+0x34 and +0x38/+0x3C. Slot +0x5C is release-only.
class MeshGeometryClass {
public:
    virtual ~MeshGeometryClass();
    void Reset_Geometry(int polycount, int vertcount, bool = true);
    unsigned char pad_04[0x0C];
    ShareBufferClass<char> *MeshName;                  // +0x10
    ShareBufferClass<char> *UserText;                  // +0x14
    unsigned int Flags;                                // +0x18
    unsigned char SortLevel;                           // +0x1C
    unsigned char pad_1D[3];
    unsigned int W3dAttributes;                        // +0x20
    int PolyCount;                                     // +0x24
    int VertexCount;                                   // +0x28
    ShareBufferClass<Vector3i16> *Poly;                // +0x2C
    ShareBufferClass<Vector3> *VertexBuffers[2];       // +0x30,+0x34
    ShareBufferClass<Vector3> *NormalBuffers[2];       // +0x38,+0x3C
    ShareBufferClass<Vector3> *VertexTangents;         // +0x40
    ShareBufferClass<Vector3> *VertexBinormals;        // +0x44
    ShareBufferClass<Vector4> *PlaneEq;                // +0x48
    ShareBufferClass<unsigned int> *VertexShadeIdx;     // +0x4C
    ShareBufferClass<unsigned short> *VertexBoneLink;   // +0x50
    ShareBufferClass<unsigned short> *BoneLinkRuns;        // +0x54
    ShareBufferClass<unsigned char> *PolySurfaceType;   // +0x58
    RefCountClass *Unknown5C;                           // +0x5C
    unsigned char pad_60[0x28];
    RefCountClass *CullTree;                            // +0x88
};

typedef Vector3i16 TriIndex;

void MeshGeometryClass::Reset_Geometry(int polycount, int vertcount, bool)
{
    Flags = 0;
    PolyCount = 0;
    VertexCount = 0;
    SortLevel = 0;

    REF_PTR_RELEASE(MeshName);
    REF_PTR_RELEASE(UserText);
    REF_PTR_RELEASE(Poly);
    REF_PTR_RELEASE(Unknown5C);
    REF_PTR_RELEASE(PolySurfaceType);

    for (int i = 0; i < 2; ++i) {
        REF_PTR_RELEASE(VertexBuffers[i]);
        REF_PTR_RELEASE(NormalBuffers[i]);
    }

    REF_PTR_RELEASE(VertexTangents);
    REF_PTR_RELEASE(VertexBinormals);
    REF_PTR_RELEASE(PlaneEq);
    REF_PTR_RELEASE(VertexShadeIdx);
    REF_PTR_RELEASE(VertexBoneLink);
    REF_PTR_RELEASE(BoneLinkRuns);
    REF_PTR_RELEASE(CullTree);

    PolyCount = polycount;
    VertexCount = vertcount;

    if (PolyCount && VertexCount) {
        Poly = NEW_REF(ShareBufferClass<TriIndex>, (PolyCount, "MeshGeometryClass::Poly"));
        Poly->Clear();
        PolySurfaceType = NEW_REF(ShareBufferClass<unsigned char>, (PolyCount, "MeshGeometryClass::PolySurfaceType"));
        PolySurfaceType->Clear();
        VertexBuffers[0] = NEW_REF(ShareBufferClass<Vector3>, (VertexCount, "MeshGeometryClass::Vertex"));
        VertexBuffers[0]->Clear();
        NormalBuffers[0] = NEW_REF(ShareBufferClass<Vector3>, (VertexCount, "MeshGeometryClass::VertexNorm"));
        NormalBuffers[0]->Clear();
        VertexTangents = NEW_REF(ShareBufferClass<Vector3>, (0, "MeshGeometryClass::VertexTangents"));
        VertexBinormals = NEW_REF(ShareBufferClass<Vector3>, (0, "MeshGeometryClass::VertexBinormals"));
        Unknown5C = NEW_REF(MeshGeometryOpaqueBuffer16, (0, NULL));
    }
}
