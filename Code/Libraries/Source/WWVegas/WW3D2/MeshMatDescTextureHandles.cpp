// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// BFME1 semantic donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp Get_Texture.
// BFME2 owning-handle type follows matched MeshMatDescClass::Get_Single_Texture
// and MeshModelClass texture accessors; target Remap_Mesh 0x16F35C proves the
// hidden return ABI. Target TextureArray +0xC8, single texture handles +0x78.
#include "MeshMatDescClass.h"

class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {
public:
    __declspec(dllimport) __forceinline void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this)+4); }
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
RefCountPtr<TextureClass> MeshMatDescClass::Get_Texture(int index, int pass, int stage) const
{
    if (TextureArray[pass][stage] != 0) {
        return TextureArray[pass][stage]->Get_Element(index);
    }
    return Texture[pass][stage];
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeGet@Gen_009299D0@@QBE?AVBfmeHandleCX@@HHH@Z=?Get_Texture@MeshMatDescClass@@QBE?AV?$RefCountPtr@VTextureClass@@@@HHH@Z")
