// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Neutral view of the 16-byte state owned at MeshMatDesc+0x0C;
// its original source type name is unknown. Reset15D140 destroys it.
// Dtor15B660 releases +0x0C, then destroys two four-byte texture handles
// via the matched callback17098D. Scalar deletion at15D120 calls this dtor.
class RefCountClass {
public:
    void Add_Ref() { ++NumRefs; }
    void Release_Ref() { --NumRefs; if (NumRefs == 0) Delete_This(); }
    virtual void Delete_This();
private:
    int NumRefs;
};
// Only the target texture's reference-counted prefix is needed here.
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
    RefCountPtr &operator=(const RefCountPtr &that) {
        if (that.Referent) that.Referent->Add_Ref();
        if (Referent) Referent->Release_Ref();
        Referent = that.Referent;
        return *this;
    }
    ~RefCountPtr() { if (Referent) { Referent->Release_Ref(); Referent = 0; } }
private:
    T *Referent;
};
class MeshMatDescRendererState {
public:
    ~MeshMatDescRendererState();
    MeshMatDescRendererState &operator=(const MeshMatDescRendererState &that);
private:
    RefCountPtr<TextureClass> Textures[2];
    unsigned Unknown08;
    RefCountClass *OwnedRef0C;
};
MeshMatDescRendererState::~MeshMatDescRendererState()
{
    if (OwnedRef0C) {
        OwnedRef0C->Release_Ref();
    }
}
void __cdecl operator delete(void *);
// Force emission of the compiler-generated scalar-deleting destructor.
__declspec(noinline) void ForceRendererStateDelete(MeshMatDescRendererState *state)
{
    delete state;
}


typedef char RendererStateSize16[(sizeof(MeshMatDescRendererState) == 16) ? 1 : -1];

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
