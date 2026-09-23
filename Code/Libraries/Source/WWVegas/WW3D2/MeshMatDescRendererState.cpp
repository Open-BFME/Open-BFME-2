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
    void Release_Ref() { --NumRefs; if (NumRefs == 0) Delete_This(); }
    virtual void Delete_This();
private:
    int NumRefs;
};
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template <class T> class RefCountPtr {
public:
    ~RefCountPtr() { if (Referent) { Referent->Release_Ref(); Referent = 0; } }
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
