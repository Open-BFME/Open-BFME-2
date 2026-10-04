// cl: /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// MeshGeometryClass normal accumulation, retail RVA 0x0016CFC0..0x0016D336.
// BFME1 meshgeometry.cpp provides the accumulation and smoothing algorithm;
// donor revision 6583b3c1ff21db4a561285717028fdafc780b7db. Target identity is
// independently established by vtable VA 0x00BD43D0 slot +0x10 and the normal
// accessor at RVA 0x0016AB90. RET8 establishes the extra bool parameter.
// Target siblings establish Flags +0x18, counts +0x24/+0x28 and Poly +0x2C.
// The bool is unused in this implementation. The unnamed vtable slot remains
// opaque. Keep helpers declaration-only: retail calls get_planes and the plane
// computation instead of inlining their definitions from the home unit.
// Volatile scalar accesses preserve retail's SSE operand order, following the
// already verified MeshGeometryClass::Scale technique. No assembly is used.

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
            *reinterpret_cast<volatile float *>(&vnorm[shadeIx[poly[pidx].I]].X) += peq[pidx].X;
            *reinterpret_cast<volatile float *>(&vnorm[shadeIx[poly[pidx].I]].Y) += peq[pidx].Y;
            vnorm[shadeIx[poly[pidx].I]].Z = *reinterpret_cast<const volatile float *>(&peq[pidx].Z) + vnorm[shadeIx[poly[pidx].I]].Z;
            vnorm[shadeIx[poly[pidx].J]].X += peq[pidx].X;
            *reinterpret_cast<volatile float *>(&vnorm[shadeIx[poly[pidx].J]].Y) += peq[pidx].Y;
            vnorm[shadeIx[poly[pidx].J]].Z += peq[pidx].Z;
            *reinterpret_cast<volatile float *>(&vnorm[shadeIx[poly[pidx].K]].X) += peq[pidx].X;
            *reinterpret_cast<volatile float *>(&vnorm[shadeIx[poly[pidx].K]].Y) += peq[pidx].Y;
            vnorm[shadeIx[poly[pidx].K]].Z = *reinterpret_cast<const volatile float *>(&peq[pidx].Z) + vnorm[shadeIx[poly[pidx].K]].Z;
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
