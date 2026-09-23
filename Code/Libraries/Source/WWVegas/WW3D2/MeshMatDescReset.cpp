// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
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
class RefCountClass {
public:
    void Release_Ref() { --NumRefs; if (NumRefs == 0) Delete_This(); }
    virtual void Delete_This();
private:
    int NumRefs;
};
class TextureClass;
template <class T> class RefCountPtr {
public:
    ~RefCountPtr();
private:
    T *Referent;
};
class MeshMatDescRendererState {
public:
    ~MeshMatDescRendererState();
private:
    RefCountPtr<TextureClass> Textures[2];
    unsigned Unknown08;
    RefCountClass *OwnedRef0C;
};
class TextureBaseClass { public: void Release_Ref(); };
class TextureHandle {
public:
    void Reset() { if (Referent) { Referent->Release_Ref(); Referent = 0; } }
private:
    TextureBaseClass *Referent;
};
class MeshMatDescClass {
public:
    void Reset(int polycount, int vertcount, int passcount);
    int PassCount;
    int VertexCount;
    int PolyCount;
    MeshMatDescRendererState *RendererState;
    RefCountClass *UV[8];
    int UVSource[4][2];
    RefCountClass *ColorArray[2];
    int DCGSource[4];
    int DIGSource[4];
    TextureHandle Texture[4][2];
    unsigned Shader[4];
    RefCountClass *Material[4];
    RefCountClass *OpaquePassBuffers[4];
    RefCountClass *TextureArray[4][2];
    RefCountClass *MaterialArray[4];
    RefCountClass *ShaderArray[4];
    RefCountClass *OpaqueTailBuffers[4];
};

typedef char MeshMatDescClass_size_check[(sizeof(MeshMatDescClass) == 0x118) ? 1 : -1];
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
            Texture[pass][stage].Reset();
            if (TextureArray[pass][stage]) { TextureArray[pass][stage]->Release_Ref(); TextureArray[pass][stage] = 0; }
        }
        DCGSource[pass] = 0;
        DIGSource[pass] = 0;
        Shader[pass] = 0;
        if (ShaderArray[pass]) { ShaderArray[pass]->Release_Ref(); ShaderArray[pass] = 0; }
        if (Material[pass]) { Material[pass]->Release_Ref(); Material[pass] = 0; }
        if (MaterialArray[pass]) { MaterialArray[pass]->Release_Ref(); MaterialArray[pass] = 0; }
        if (OpaquePassBuffers[pass]) { OpaquePassBuffers[pass]->Release_Ref(); OpaquePassBuffers[pass] = 0; }
        if (OpaqueTailBuffers[pass]) { OpaqueTailBuffers[pass]->Release_Ref(); OpaqueTailBuffers[pass] = 0; }
    }
    if (RendererState) {
        delete RendererState;
    }
    RendererState = 0;
}
