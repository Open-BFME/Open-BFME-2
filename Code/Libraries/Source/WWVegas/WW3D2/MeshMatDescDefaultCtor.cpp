// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeshader /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// MeshModel default ctor1727E0 allocates118 bytes and calls15B480.
// The complete target body ends at15B5A2; the inventory's275B size is short.
// Target-shaped view of the BFME1 MeshMatDescClass default constructor.
// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp.
// Retail-only field identities remain neutral where target evidence establishes
// slots but not original names.
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template <class T> class RefCountPtr {
public:
    RefCountPtr() : Referent(0) {}
    ~RefCountPtr() { if (Referent) { Referent->Release_Ref(); Referent = 0; } }
    void Clear() { if (Referent) { Referent->Release_Ref(); Referent = 0; } }
private:
    T *Referent;
};

#include "shader.h"

class MeshMatDescRendererState;
class MeshMatDescClass {
public:
    MeshMatDescClass();
private:
    enum { MAX_PASSES = 4, MAX_TEX_STAGES = 2, MAX_UV_ARRAYS = 8 };
    int PassCount, VertexCount, PolyCount;
    MeshMatDescRendererState *RendererState; // +0x0C; neutral lifecycle view, original name unknown
    void *UV[MAX_UV_ARRAYS];              // +0x10
    int UVSource[MAX_PASSES][2];          // +0x30
    void *ColorArray[2];                  // +0x50
    int DCGSource[MAX_PASSES];            // +0x58
    int DIGSource[MAX_PASSES];            // +0x68
    RefCountPtr<TextureClass> Texture[MAX_PASSES][2]; // +0x78
    ShaderClass Shader[MAX_PASSES];       // +0x98
    void *Material[MAX_PASSES];           // +0xA8
    void *UnknownPassBufferB8[MAX_PASSES];// +0xB8; target slot, name unknown
    void *TextureArray[MAX_PASSES][2];    // +0xC8
    void *MaterialArray[MAX_PASSES];     // +0xE8
    void *ShaderArray[MAX_PASSES];       // +0xF8
    void *UnknownPassBuffer108[MAX_PASSES];// +0x108; target slot, name unknown
};
typedef char MeshMatDescTargetSizeCheck[(sizeof(MeshMatDescClass) == 0x118) ? 1 : -1];

MeshMatDescClass::MeshMatDescClass() : PassCount(1), VertexCount(0), PolyCount(0), RendererState(0) {
    int pass, stage, array;
    for (array=0; array<2; ++array) ColorArray[array] = 0;
    for (array=0; array<MAX_UV_ARRAYS; ++array) UV[array] = 0;
    for (pass=0; pass<MAX_PASSES; ++pass) {
        for (stage=0; stage<MAX_TEX_STAGES; ++stage) {
            UVSource[pass][stage] = -1;
            Texture[pass][stage].Clear();
            TextureArray[pass][stage] = 0;
        }
        DCGSource[pass] = 0;
        DIGSource[pass] = 0;
        Shader[pass] = 0; //ShaderClass::_PresetOpaqueSolidShader;
        Material[pass] = 0;
        UnknownPassBufferB8[pass] = 0;
        ShaderArray[pass] = 0;
        MaterialArray[pass] = 0;
        UnknownPassBuffer108[pass] = 0;
    }
}
