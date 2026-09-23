// ?Compute_Vertex_Normals@MeshGeometryClass@@MAEXPAVVector3@@_N@Z
// partial score=0.8826185102 date=2026-09-23
// Scratch recovery trial for MeshGeometryClass::Compute_Vertex_Normals at
// 0x16CFC0. Target layout comes from the BFME2 matched geometry siblings;
// BFME1 meshgeometry.cpp supplies the accumulation/smoothing semantics.
// cl: /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "multilist.h"
#include "vp.h"

typedef Vector3i16 TriIndex;

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass {
public:
    virtual void Delete_This(void);
    virtual ~MeshGeometryClass(void);
    virtual void Retail_Vtable_Slot_2(void);
protected:
    virtual void Compute_Plane_Equations(Vector4 *array);
    virtual void Compute_Vertex_Normals(Vector3 *array, bool create);
    virtual void Compute_Bounds(Vector3 *array);
    Vector4 *get_planes(bool create);
    uint32 *get_shade_indices(bool create);
public:
    void *MeshName;
    void *UserText;
    int Flags;
    char SortLevel;
    uint32 W3dAttributes;
    int PolyCount;
    int VertexCount;
    ShareBufferClass<TriIndex> *Poly;
};

void MeshGeometryClass::Compute_Vertex_Normals(Vector3 *vnorm, bool)
{
    if (PolyCount == 0 || VertexCount == 0) return;

    const Vector4 *peq = get_planes(true);
    if (peq != NULL && (Flags & 2) != 0) {
        Compute_Plane_Equations(const_cast<Vector4 *>(peq));
    }

    TriIndex *poly = Poly->Get_Array();
    const uint32 *shadeIx = get_shade_indices(false);
    VectorProcessorClass::Clear(vnorm, VertexCount);

    if (shadeIx == NULL) {
        for (int pidx = 0; pidx < PolyCount; ++pidx) {
            vnorm[poly[pidx].I].X += peq[pidx].X;
            vnorm[poly[pidx].I].Y += peq[pidx].Y;
            vnorm[poly[pidx].I].Z += peq[pidx].Z;
            vnorm[poly[pidx].J].X += peq[pidx].X;
            vnorm[poly[pidx].J].Y += peq[pidx].Y;
            vnorm[poly[pidx].J].Z += peq[pidx].Z;
            vnorm[poly[pidx].K].X += peq[pidx].X;
            vnorm[poly[pidx].K].Y += peq[pidx].Y;
            vnorm[poly[pidx].K].Z += peq[pidx].Z;
        }
    } else {
        for (int pidx = 0; pidx < PolyCount; ++pidx) {
            vnorm[shadeIx[poly[pidx].I]].X += peq[pidx].X;
            vnorm[shadeIx[poly[pidx].I]].Y += peq[pidx].Y;
            vnorm[shadeIx[poly[pidx].I]].Z += peq[pidx].Z;
            vnorm[shadeIx[poly[pidx].J]].X += peq[pidx].X;
            vnorm[shadeIx[poly[pidx].J]].Y += peq[pidx].Y;
            vnorm[shadeIx[poly[pidx].J]].Z += peq[pidx].Z;
            vnorm[shadeIx[poly[pidx].K]].X += peq[pidx].X;
            vnorm[shadeIx[poly[pidx].K]].Y += peq[pidx].Y;
            vnorm[shadeIx[poly[pidx].K]].Z += peq[pidx].Z;
        }

        for (unsigned int vidx = 0; vidx < (unsigned int)VertexCount; ++vidx) {
            if (shadeIx[vidx] == vidx) {
                Vector3 &n = vnorm[vidx];
                float len2 = n.X * n.X + n.Y * n.Y + n.Z * n.Z;
                if (len2 != 0.0f) {
                    float inv = WWMath::Inv_Sqrt(len2);
                    n.X *= inv; n.Y *= inv; n.Z *= inv;
                }
            } else {
                vnorm[vidx] = vnorm[shadeIx[vidx]];
            }
        }
    }

    VectorProcessorClass::Normalize(vnorm, VertexCount);
    Flags &= ~4;
}
