// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Retain native inlined reference operations without competing external
// copies; whole-body verification also checks that no imported call remains.
// EA Zero Hour meshmatdesc.cpp setters adapted to BFME2 owning handles.
// Single slots at +0x78; indexed buffer array pointer at +8. Each assignment
// AddRefs the new texture before releasing the old one and replacing the slot.
// Release_Ref at61ED10 and Get_Texture_Array at15D360 are existing matched bodies.
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {
public: __declspec(dllimport) __forceinline void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this)+4); }
};
#include "MeshMatDescClass.h"
// TU-local completion of the descriptor's texture buffer: its element array at +8.
class TexBufferClass {
    char prefix[8];
    RefCountPtr<TextureClass> *Array;
public: RefCountPtr<TextureClass> *Get_Array() { return Array; }
};
void MeshMatDescClass::Set_Single_Texture(const RefCountPtr<TextureClass>& texture,int pass,int stage) {
    Texture[pass][stage] = texture;
}
void MeshMatDescClass::Set_Texture(int index,const RefCountPtr<TextureClass>& texture,int pass,int stage) {
    Get_Texture_Array(pass,stage,true)->Get_Array()[index] = texture;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Set_Single_Texture@MeshMatDescClass@@QAEXABVBfmeHandleCX@@HH@Z=?Set_Single_Texture@MeshMatDescClass@@QAEXABV?$RefCountPtr@VTextureClass@@@@HH@Z")
#pragma comment(linker, "/alternatename:?Set_Texture@MeshMatDescClass@@QAEXHABVBfmeHandleCX@@HH@Z=?Set_Texture@MeshMatDescClass@@QAEXHABV?$RefCountPtr@VTextureClass@@@@HH@Z")
