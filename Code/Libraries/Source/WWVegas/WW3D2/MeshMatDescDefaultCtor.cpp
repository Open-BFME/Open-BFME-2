// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeshader /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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
// Retail texture references count in a word at +4 (operator= at 0x15D800
// adds to it inline) and release out of line through 0x61ED10.
class TextureBaseClass {
public:
    void Release_Ref();
protected:
    void *VTable;
    unsigned short NumRefs;
};
class TextureClass : public TextureBaseClass {
public:
    void Add_Ref() { ++NumRefs; }
};
template <class T> class RefCountPtr {
public:
    RefCountPtr() : Referent(0) {}
    RefCountPtr &operator=(const RefCountPtr &that) {
        if (that.Referent) that.Referent->Add_Ref();
        if (Referent) Referent->Release_Ref();
        Referent = that.Referent;
        return *this;
    }
    T *Get() const { return Referent; }
    ~RefCountPtr() { if (Referent) { Referent->Release_Ref(); Referent = 0; } }
    void Clear() { if (Referent) { Referent->Release_Ref(); Referent = 0; } }
private:
    T *Referent;
};

#include "shader.h"

class RefCountClass {
public:
    void Add_Ref() { ++NumRefs; }
    void Release_Ref() { --NumRefs; if (NumRefs == 0) Delete_This(); }
    virtual void Delete_This();
protected:
    int NumRefs;
};
class VertexMaterialClass : public RefCountClass {};

// The buffer copies operator= makes: the ShareBufferClass copy constructors
// are out of line (0x15AE10, 0x15AB50, 0x15CE00, 0x15ACB0); the derived ones
// inline, installing vtables 0xBD3CF4, 0xBD3C9C and 0xBD3CA4. The texture
// base copy already references its elements; the material and FX shader
// buffer copies add a reference per element as BFME1's MatBufferClass does.
template <class T> class ShareBufferClass : public RefCountClass {
public:
    ShareBufferClass(const ShareBufferClass &that);
    virtual ~ShareBufferClass();
protected:
    T *RawBuffer;
    T *Array;
    int Count;
    int Alignment;
};
class TexBufferClass : public ShareBufferClass<TextureClass *> {
public:
    TexBufferClass(const TexBufferClass &that) : ShareBufferClass<TextureClass *>(that) {}
    virtual ~TexBufferClass();
};
class MatBufferClass : public ShareBufferClass<VertexMaterialClass *> {
public:
    MatBufferClass(const MatBufferClass &that) : ShareBufferClass<VertexMaterialClass *>(that) {
        for (int i = 0; i < Count; i++) {
            if (RawBuffer[i] != 0) RawBuffer[i]->Add_Ref();
        }
    }
    virtual ~MatBufferClass();
};
class OpaqueRefBuffer : public ShareBufferClass<RefCountClass *> {
public:
    OpaqueRefBuffer(const OpaqueRefBuffer &that) : ShareBufferClass<RefCountClass *>(that) {
        for (int i = 0; i < Count; i++) {
            if (RawBuffer[i] != 0) RawBuffer[i]->Add_Ref();
        }
    }
    virtual ~OpaqueRefBuffer();
};

// Neutral view of the 16-byte state owned at MeshMatDesc+0x0C; its original
// source type name is unknown. Reset15D140 destroys it through the scalar
// deleting destructor at 0x15D120; operator= (0x15D800) inlines its
// construction and destruction and calls its assignment (0x15B5E0).
class MeshMatDescRendererState {
public:
    MeshMatDescRendererState();
    ~MeshMatDescRendererState();
    MeshMatDescRendererState &operator=(const MeshMatDescRendererState &that);
private:
    RefCountPtr<TextureClass> Textures[2];
    unsigned Unknown08;
    RefCountClass *OwnedRef0C;
};
typedef char RendererStateSize16[(sizeof(MeshMatDescRendererState) == 16) ? 1 : -1];

MeshMatDescRendererState::MeshMatDescRendererState() : Unknown08(0x10441b), OwnedRef0C(0)
{
}

// Descriptor assignment calls15B5E0 after allocating16 bytes for its+C state.
MeshMatDescRendererState &MeshMatDescRendererState::operator=(const MeshMatDescRendererState &that)
{
    for (int i = 0; i < 2; ++i) Textures[i] = that.Textures[i];
    Unknown08 = that.Unknown08;
    if (&OwnedRef0C != &that.OwnedRef0C) {
        if (that.OwnedRef0C) that.OwnedRef0C->Add_Ref();
        if (OwnedRef0C) OwnedRef0C->Release_Ref();
        OwnedRef0C = that.OwnedRef0C;
    }
    return *this;
}

// Dtor15B660 releases +0x0C, then destroys two four-byte texture handles
// via the matched callback17098D.
MeshMatDescRendererState::~MeshMatDescRendererState()
{
    if (OwnedRef0C) {
        OwnedRef0C->Release_Ref();
    }
}

class MeshMatDescClass {
public:
    MeshMatDescClass();
    bool Is_Empty();
    MeshMatDescClass(const MeshMatDescClass &that);
    MeshMatDescClass &operator=(const MeshMatDescClass &that);
private:
    enum { MAX_PASSES = 4, MAX_TEX_STAGES = 2, MAX_UV_ARRAYS = 8 };
    int PassCount, VertexCount, PolyCount;
    MeshMatDescRendererState *RendererState; // +0x0C; neutral lifecycle view, original name unknown
    RefCountClass *UV[MAX_UV_ARRAYS];     // +0x10
    int UVSource[MAX_PASSES][2];          // +0x30
    RefCountClass *ColorArray[2];         // +0x50
    int DCGSource[MAX_PASSES];            // +0x58
    int DIGSource[MAX_PASSES];            // +0x68
    RefCountPtr<TextureClass> Texture[MAX_PASSES][2]; // +0x78
    ShaderClass Shader[MAX_PASSES];       // +0x98
    VertexMaterialClass *Material[MAX_PASSES]; // +0xA8
    RefCountClass *UnknownPassBufferB8[MAX_PASSES];// +0xB8; target slot, name unknown
    TexBufferClass *TextureArray[MAX_PASSES][2]; // +0xC8
    MatBufferClass *MaterialArray[MAX_PASSES];  // +0xE8
    ShareBufferClass<ShaderClass> *ShaderArray[MAX_PASSES]; // +0xF8
    OpaqueRefBuffer *UnknownPassBuffer108[MAX_PASSES];// +0x108; FX shader array, class name unknown
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

MeshMatDescClass::MeshMatDescClass(const MeshMatDescClass &that) : PassCount(1), VertexCount(0), PolyCount(0), RendererState(0) {
    int pass, stage, array;
    // init everything to NULL
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
        Shader[pass] = 0;
        Material[pass] = 0;
        UnknownPassBufferB8[pass] = 0;
        ShaderArray[pass] = 0;
        MaterialArray[pass] = 0;
        UnknownPassBuffer108[pass] = 0;
    }
    // copy
    *this = that;
}

// BFME1 meshmatdesc.cpp operator= with the BFME2 members: the +0xB8 single
// and +0x108 FX shader buffers follow Material and ShaderArray, and the
// +0x0C state is rebuilt from the source's.
MeshMatDescClass &MeshMatDescClass::operator=(const MeshMatDescClass &that) {
    if (this != &that) {
        PassCount = that.PassCount;
        VertexCount = that.VertexCount;
        PolyCount = that.PolyCount;

        for (int array=0; array<2; array++) {
            if (that.ColorArray[array]) that.ColorArray[array]->Add_Ref();
            if (ColorArray[array]) ColorArray[array]->Release_Ref();
            ColorArray[array] = that.ColorArray[array];
        }
        for (int uvarray=0; uvarray<MAX_UV_ARRAYS; uvarray++) {
            if (that.UV[uvarray]) that.UV[uvarray]->Add_Ref();
            if (UV[uvarray]) UV[uvarray]->Release_Ref();
            UV[uvarray] = that.UV[uvarray];
        }
        for (int pass=0; pass<MAX_PASSES; pass++) {
            for (int stage=0; stage<MAX_TEX_STAGES; stage++) {
                UVSource[pass][stage] = that.UVSource[pass][stage];
                Texture[pass][stage] = that.Texture[pass][stage];

                if (TextureArray[pass][stage]) { TextureArray[pass][stage]->Release_Ref(); TextureArray[pass][stage] = 0; }
                if (that.TextureArray[pass][stage]) {
                    TextureArray[pass][stage] = new TexBufferClass(*that.TextureArray[pass][stage]);
                }
            }
            DCGSource[pass] = that.DCGSource[pass];
            DIGSource[pass] = that.DIGSource[pass];
            Shader[pass] = that.Shader[pass];

            if (that.Material[pass]) that.Material[pass]->Add_Ref();
            if (Material[pass]) Material[pass]->Release_Ref();
            Material[pass] = that.Material[pass];

            if (that.UnknownPassBufferB8[pass]) that.UnknownPassBufferB8[pass]->Add_Ref();
            if (UnknownPassBufferB8[pass]) UnknownPassBufferB8[pass]->Release_Ref();
            UnknownPassBufferB8[pass] = that.UnknownPassBufferB8[pass];

            if (MaterialArray[pass]) { MaterialArray[pass]->Release_Ref(); MaterialArray[pass] = 0; }
            if (that.MaterialArray[pass]) {
                MaterialArray[pass] = new MatBufferClass(*that.MaterialArray[pass]);
            }
            if (ShaderArray[pass]) { ShaderArray[pass]->Release_Ref(); ShaderArray[pass] = 0; }
            if (that.ShaderArray[pass]) {
                ShaderArray[pass] = new ShareBufferClass<ShaderClass>(*that.ShaderArray[pass]);
            }
            if (UnknownPassBuffer108[pass]) { UnknownPassBuffer108[pass]->Release_Ref(); UnknownPassBuffer108[pass] = 0; }
            if (that.UnknownPassBuffer108[pass]) {
                UnknownPassBuffer108[pass] = new OpaqueRefBuffer(*that.UnknownPassBuffer108[pass]);
            }
        }

        delete RendererState;
        RendererState = 0;
        if (that.RendererState) {
            RendererState = new MeshMatDescRendererState;
            *RendererState = *that.RendererState;
        }
    }
    return *this;
}

bool MeshMatDescClass::Is_Empty() {
    for (int array=0; array<2; ++array) if (ColorArray[array]) return false;
    for (int uvarray=0; uvarray<8; ++uvarray) if (UV[uvarray]) return false;
    for (int pass=0; pass<4; ++pass) {
        for (int stage=0; stage<2; ++stage) {
            if (Texture[pass][stage].Get()) return false;
            if (TextureArray[pass][stage]) return false;
        }
        if (Material[pass]) return false;
        if (MaterialArray[pass]) return false;
        if (UnknownPassBufferB8[pass]) return false;
        if (UnknownPassBuffer108[pass]) return false;
    }
    return true;
}
