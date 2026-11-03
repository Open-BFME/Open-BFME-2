// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00180AF9@Rva00180AF9@@QAEPAV1@ABV?$RefCountPtr@VTextureClass@@@@@Z @0x00180AF9 50B
// Evidence: unlock lane; TextureClass slot 0x34 identity via 0x41474752 compare;
// callees rowed clear 0x0004D75B and RefCountPtr assign 0x000424D0; caller 0x00180BE0.
class TextureClass
{
public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
};

template <class T>
class RefCountPtr
{
public:
    T *Referent;
    const RefCountPtr &operator=(const RefCountPtr &other);
};

#include "../../../Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h"

class Rva00180AF9
{
public:
    Rva00180AF9 *rva00180AF9(const RefCountPtr<TextureClass> &other);
};

Rva00180AF9 *Rva00180AF9::rva00180AF9(const RefCountPtr<TextureClass> &other)
{
    TextureClass *texture = other.Referent;
    if (texture != 0 && texture->v13() != 0x41474752)
        ((BfmeResetTextureRef *)this)->clear();
    else
        ((RefCountPtr<TextureClass> *)this)->operator=(other);
    return this;
}
