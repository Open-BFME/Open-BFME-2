// cl: /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
** BFME1 MeshGeometry assignment adapted to BFME2's verified vector slots,
** +0x54 ushort buffer, and +0x5C opaque release-only buffer.
*/
#include "rendobj.h"
// Keep aabtree.h from pulling the BFME1 MeshGeometryClass body into this view.
#define MESHGEOMETRY_H
#include "refcount.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "multilist.h"
#include "always.h"
typedef Vector3i16 TriIndex;
// Retail allocates the culling tree through global operator new.
#pragma push_macro("W3DMPO_GLUE")
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "aabtree.h"
#pragma pop_macro("W3DMPO_GLUE")

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass {
public:
    virtual ~MeshGeometryClass();
    MeshGeometryClass(const MeshGeometryClass &that);
    MeshGeometryClass &operator=(const MeshGeometryClass &that);

private:
    ShareBufferClass<char> *MeshName;               // +0x10
    ShareBufferClass<char> *UserText;               // +0x14
    unsigned int Flags;                             // +0x18
    char SortLevel;                                 // +0x1C
    unsigned char pad_1D[3];
    unsigned int W3dAttributes;                     // +0x20
    int PolyCount;                                  // +0x24
    int VertexCount;                                // +0x28
    ShareBufferClass<Vector3i16> *Poly;             // +0x2C
    ShareBufferClass<Vector3> *VertexBuffers[2]; // +0x30/+0x34
    ShareBufferClass<Vector3> *NormalBuffers[2]; // +0x38/+0x3C
    ShareBufferClass<Vector3> *VertexTangents;      // +0x40
    ShareBufferClass<Vector3> *VertexBinormals;     // +0x44
    ShareBufferClass<Vector4> *PlaneEq;             // +0x48
    ShareBufferClass<unsigned int> *VertexShadeIdx; // +0x4C
    ShareBufferClass<unsigned short> *VertexBoneLink;// +0x50
    ShareBufferClass<unsigned short> *UnknownBuffer54;// +0x54
    ShareBufferClass<unsigned char> *PolySurfaceType;// +0x58
    RefCountClass *UnknownBuffer5C;                 // +0x5C
    Vector3 BoundBoxMin;                            // +0x60
    Vector3 BoundBoxMax;                            // +0x6C
    Vector3 BoundSphereCenter;                      // +0x78
    float BoundSphereRadius;                        // +0x84
    AABTreeClass *CullTree;                         // +0x88
};

typedef char MeshGeometryClass_size_check[(sizeof(MeshGeometryClass) == 0x8C) ? 1 : -1];

MeshGeometryClass::MeshGeometryClass(const MeshGeometryClass &that) :
    MeshName(NULL),
    UserText(NULL),
    Flags(0),
    SortLevel(0),
    W3dAttributes(0),
    PolyCount(0),
    VertexCount(0),
    Poly(NULL),
    VertexTangents(NULL),
    VertexBinormals(NULL),
    PlaneEq(NULL),
    VertexShadeIdx(NULL),
    VertexBoneLink(NULL),
    UnknownBuffer54(NULL),
    PolySurfaceType(NULL),
    UnknownBuffer5C(NULL),
    BoundBoxMin(0,0,0),
    BoundBoxMax(1,1,1),
    BoundSphereCenter(0,0,0),
    BoundSphereRadius(1),
    CullTree(NULL)
{
    for (int i = 0; i < 2; ++i) {
        VertexBuffers[i] = NULL;
        NormalBuffers[i] = NULL;
    }
    *this = that;
}

MeshGeometryClass &MeshGeometryClass::operator=(const MeshGeometryClass &that)
{
    if (this != &that) {
        Flags = that.Flags;
        SortLevel = that.SortLevel;
        W3dAttributes = that.W3dAttributes;
        PolyCount = that.PolyCount;
        VertexCount = that.VertexCount;

        BoundBoxMin = that.BoundBoxMin;
        BoundBoxMax = that.BoundBoxMax;
        BoundSphereCenter = that.BoundSphereCenter;
        BoundSphereRadius = that.BoundSphereRadius;

        REF_PTR_SET(MeshName, that.MeshName);
        REF_PTR_SET(UserText, that.UserText);
        REF_PTR_SET(Poly, that.Poly);
        REF_PTR_SET(UnknownBuffer5C, that.UnknownBuffer5C);
        REF_PTR_SET(PolySurfaceType, that.PolySurfaceType);

        // Retail preserves a destination slot when its source is null.
        for (int i = 0; i < 2; ++i) {
            if (that.VertexBuffers[i]) REF_PTR_SET(VertexBuffers[i], that.VertexBuffers[i]);
            if (that.NormalBuffers[i]) REF_PTR_SET(NormalBuffers[i], that.NormalBuffers[i]);
        }

        REF_PTR_SET(VertexTangents, that.VertexTangents);
        REF_PTR_SET(VertexBinormals, that.VertexBinormals);
        REF_PTR_SET(PlaneEq, that.PlaneEq);
        REF_PTR_SET(VertexShadeIdx, that.VertexShadeIdx);
        REF_PTR_SET(VertexBoneLink, that.VertexBoneLink);
        REF_PTR_SET(UnknownBuffer54, that.UnknownBuffer54);

        REF_PTR_RELEASE(CullTree);
        if (that.CullTree) {
            CullTree = NEW_REF(AABTreeClass, ());
            *CullTree = *that.CullTree;
            CullTree->Set_Mesh(this);
        }
    }
    return *this;
}
