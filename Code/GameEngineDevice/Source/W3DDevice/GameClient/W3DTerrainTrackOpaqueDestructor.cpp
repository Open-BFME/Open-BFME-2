// cl: /O1 /G7 /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Reference review: BFME1 575ba2b0 TerrainTracksRenderObjClassDtor.cpp
// supplies the reset/release cleanup pattern, with a different track layout.
// Native 00084096..000840D5 and WB 008BAC50 independently establish the
// reset call, texture pointer at +2C, and RefCountClass base teardown.
// The original owner name remains unknown; retain its existing opaque name.
// RefCountClass uses the same shared header as the rowed hlod.cpp provider.
#include "refcount.h"

class TextureClass { public: void Release_Ref(); };
class Rva00083CB2 { public: void rva00083CB2(); };

// A partial receiver view: only the proven base and texture field are named.
class Rva0084096 : public RefCountClass
{
public:
    virtual ~Rva0084096();
private:
    char pad08[0x2c - 8];
    TextureClass *texture;
};

Rva0084096::~Rva0084096()
{
    ((Rva00083CB2 *)this)->rva00083CB2();
    if (texture)
        texture->Release_Ref();
}
