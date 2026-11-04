// cl: /Oy- /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// EA Zero Hour meshmatdesc.h inline single-texture peek, adapted to BFME2 handles.
// Retail D2026: complete 37B body; texture slots at +0x78 with pass/stage indexing.
// ZH's MaterialRemapperClass::Remap_Mesh and MeshModelClass::Peek_Single_Texture
// call Peek_Single_Texture, and their retail bodies call D2026; this /O1 copy is
// the header inline's. The out-of-line Get_Single_Texture is meshmatdesc.cpp's
// /O2 body at 0x15A180, just ahead of Init_Alternate as in ZH's source order.
// The out-of-line handle copy at 424BB is the existing 21B AssetReference copy
// body: copies one pointer and increments its WORD reference count at +4.
// This owning getter is called from model accessor D206A and the material remapper.
#include "MeshMatDescClass.h"

class TextureBaseClass { public: void Add_Ref(); void Release_Ref(); };
class TextureClass : public TextureBaseClass {};

RefCountPtr<TextureClass> MeshMatDescClass::Peek_Single_Texture(int pass,int stage) const {
    return Texture[pass][stage];
}
