// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
** BFME1 meshmatdesc.cpp Reset adapted to the BFME2 descriptor layout.
*/
// MeshModel::Reset calls15D140 through its default descriptor at+8C.
// The target establishes the counts and release loops below; buffers at
// +B8/+108 and the state at+C retain descriptive names, not donor identities.
// Texture slots hold four-byte owning handles. Their Reset method preserves
// the target release-before-null operation; other buffers use RefCountClass.
// Match the retail RefCountClass release helper at 0x5D1A7D.
// Its declaration uses the verified provider's size context; callers retain theirs.
#pragma optimize("gsy", on)
#include "../WWLib/RefCountData.h"
#pragma optimize("", on)
#include "MeshMatDescClass.h"
// TU-local completions of the descriptor's forward-declared buffer and state
// types: Reset needs only their RefCountClass release and the state's dtor.
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
class MeshMatDescRendererState {
public:
    ~MeshMatDescRendererState();
private:
    RefCountPtr<TextureClass> Textures[2];
    unsigned Unknown08;
    RefCountClass *OwnedRef0C;
};
class UVBufferClass : public RefCountClass {};
class TexBufferClass : public RefCountClass {};
class MatBufferClass : public RefCountClass {};
class OpaqueRefBuffer : public RefCountClass {};
template <class T> class ShareBufferClass : public RefCountClass {};

void MeshMatDescClass::Reset(int polycount, int vertcount, int passcount)
{
    PolyCount = polycount;
    VertexCount = vertcount;
    PassCount = passcount;
    for (int array = 0; array < 2; ++array) {
        if (ColorArray[array]) { ColorArray[array]->Release_Ref(); ColorArray[array] = 0; }
    }
    for (int uvarray = 0; uvarray < 8; ++uvarray) {
        if (UV[uvarray]) { UV[uvarray]->Release_Ref(); UV[uvarray] = 0; }
    }
    for (int pass = 0; pass < 4; ++pass) {
        for (int stage = 0; stage < 2; ++stage) {
            UVSource[pass][stage] = -1;
            Texture[pass][stage].Clear();
            if (TextureArray[pass][stage]) { TextureArray[pass][stage]->Release_Ref(); TextureArray[pass][stage] = 0; }
        }
        DCGSource[pass] = VertexMaterialClass::MATERIAL;
        DIGSource[pass] = VertexMaterialClass::MATERIAL;
        Shader[pass] = 0;
        if (ShaderArray[pass]) { ShaderArray[pass]->Release_Ref(); ShaderArray[pass] = 0; }
        if (Material[pass]) { Material[pass]->Release_Ref(); Material[pass] = 0; }
        if (MaterialArray[pass]) { MaterialArray[pass]->Release_Ref(); MaterialArray[pass] = 0; }
        if (field_B8[pass]) { field_B8[pass]->Release_Ref(); field_B8[pass] = 0; }
        if (field_108[pass]) { field_108[pass]->Release_Ref(); field_108[pass] = 0; }
    }
    if (field_0C) {
        delete field_0C;
    }
    field_0C = 0;
}
