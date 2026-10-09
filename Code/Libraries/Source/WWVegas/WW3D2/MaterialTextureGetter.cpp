// cl: /O2 /G7 /Oy /MD /EHs
// Complete37B native16EE40..16EE65 RET8; WB A085F0 MaterialInfoClass::Get_Texture.
// Clean BFME1 0bef414b matinfo.cpp/owning collector handles supply semantics.
// Native+WB prove array24, stride4, hidden result and WORD acquisition at +4.
// MSVC's hidden-return construction flag accounts for the stack DWORD zero.
#include "MaterialTextureGetterView.h"
FloorMaterialHandle Rva00016EE40::getTexture(int index) { return textures[index]; }
