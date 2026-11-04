// cl: /Oy- /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Reference meshmdl.h current-description single-texture forwarding shape.
// BFME2 D206A is a complete 35B owning-handle return via CurMatDesc at +0x94.
// Its callee is the MeshMatDesc peek D2026, as ZH meshmdl.h forwards.
// Keep the callee out of this TU so the retail call and register saves survive.
#include "MeshMatDescClass.h"

class TextureBaseClass { public: void Add_Ref(); void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
#include "MeshModelClass.h"
// Emitted as a noinline inline COMDAT so MaterialCollectorCollectMaterials.cpp's
// visible in-class copy (kept there for its codegen) folds instead of colliding.
inline __declspec(noinline) RefCountPtr<TextureClass> MeshModelClass::Peek_Single_Texture(int pass,int stage) const {
    return CurMatDesc->Peek_Single_Texture(pass,stage);
}
static RefCountPtr<TextureClass> (MeshModelClass::*s_anchor_Peek_Single_Texture)(int,int) const = &MeshModelClass::Peek_Single_Texture;
