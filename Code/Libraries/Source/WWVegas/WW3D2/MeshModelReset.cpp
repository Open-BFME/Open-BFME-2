// cl: /Ireference/shims/meshgeom /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
** BFME1 model reset adapted to target teardown and fourth bool argument.
*/
// Descriptor +0x0C is guarded before renderer teardown; the descriptor Reset
// at15D140 destroys it separately. UV buffers start at+0x10, not this slot.
// BFME1 MeshModelClass::Reset adapted to the BFME2 bool ABI and target teardown order.
#include "meshgeometry.h"

void __cdecl operator delete(void *block);

class MeshModelClass;

class MeshMatDescClass {
public:
    ~MeshMatDescClass();
    void Reset(int polycount, int vertcount, int passcount);
    int PassCount;
    int VertexCount;
    int PolyCount;
    void *RendererState; // +0x0C; original type unknown
};
class MaterialInfoClass {
public:
    void Reset() { Free(); }
private:
    void Free();
};
class DX8MeshRendererClass {
public:
    void Unregister_Mesh_Type(MeshModelClass *model);
};
class Rva00DF6F94GapFillerContext {
public:
    void DeleteModelGapFiller(MeshModelClass *model);
};
extern DX8MeshRendererClass *TheDX8MeshRenderer;
extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;
bool __cdecl Rva00199FA5TeardownMeshMatDescRenderers(MeshMatDescClass *matdesc);
class MeshModelClass : public MeshGeometryClass {
public:
    void Reset(int polycount, int vertcount, int passcount, bool skinned);
private:
    MeshMatDescClass *DefMatDesc;
    MeshMatDescClass *AlternateMatDesc;
    MeshMatDescClass *CurMatDesc;
    MaterialInfoClass *MatInfo;
};

typedef char MeshModelClass_base_size_check[(sizeof(MeshGeometryClass) == 0x8C) ? 1 : -1];
void MeshModelClass::Reset(int polycount, int vertcount, int passcount, bool skinned)
{
    Reset_Geometry(polycount, vertcount, skinned);
    if (TheDX8MeshRenderer != NULL) {
        TheDX8MeshRenderer->Unregister_Mesh_Type(this);
    }
    if (TheMeshGapFillerContext != NULL) {
        TheMeshGapFillerContext->DeleteModelGapFiller(this);
    }
    if (CurMatDesc->RendererState != NULL) {
        Rva00199FA5TeardownMeshMatDescRenderers(CurMatDesc);
    }
    MatInfo->Reset();
    DefMatDesc->Reset(polycount, vertcount, passcount);
    if (AlternateMatDesc != NULL) {
        delete AlternateMatDesc;
        AlternateMatDesc = NULL;
    }
    CurMatDesc = DefMatDesc;
}
