// cl: /G7 /DNDEBUG /MD /EHsc
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// BFME1 semantic donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp Get_Texture.
// BFME2 owning-handle type follows matched MeshMatDescClass::Get_Single_Texture
// and MeshModelClass texture accessors; target Remap_Mesh 0x16F35C proves the
// hidden return ABI. Target TextureArray +0xC8, single texture handles +0x78.
class TextureClass {
public:
    void Add_Ref() { ++RefCount; }
    void Release_Ref();
private:
    void *VTable;
    unsigned short RefCount; // target +4
};
template<class T> class RefCountPtr {
public:
    T *p;
    RefCountPtr() : p(0) {}
    RefCountPtr(RefCountPtr const &other) : p(other.p) { if (p) p->Add_Ref(); }
    ~RefCountPtr() { if (p) p->Release_Ref(); }
};
class TexBufferClass {
    char prefix[8];
    RefCountPtr<TextureClass> *RawBuffer;
public:
    RefCountPtr<TextureClass> Get_Element(int index);
};
// Keep this body visible: target Get_Texture relies on its register use.
RefCountPtr<TextureClass> TexBufferClass::Get_Element(int index)
{
    return RawBuffer[index];
}
class MeshMatDescClass {
    char padding_to_single_textures[0x78];
    RefCountPtr<TextureClass> Texture[4][2];
    char padding_to_texture_array[0x30];
    TexBufferClass *TextureArray[4][2];
public:
    RefCountPtr<TextureClass> Get_Texture(int index, int pass, int stage) const;
};
RefCountPtr<TextureClass> MeshMatDescClass::Get_Texture(int index, int pass, int stage) const
{
    if (TextureArray[pass][stage] != 0) {
        return TextureArray[pass][stage]->Get_Element(index);
    }
    return Texture[pass][stage];
}
