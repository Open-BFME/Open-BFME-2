// cl: /O1 /G7 /arch:SSE /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Counted area-map value used by retail 0x001711A6 (WB TexturePacker::
// UpdateResultTexture). The unsigned key and counted texture value are
// established by the retail construction and cleanup call sites.
#include <map>

class TextureClass {
public:
    void Release_Ref();
    void Add_Ref() {
        ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this)+4);
    }
};
#include "../../../../GameEngine/Include/Common/AssetReference.h"

typedef _STL::pair<unsigned,AssetReference> AreaMutablePair;
template AreaMutablePair::pair(const unsigned &,const AssetReference &);
