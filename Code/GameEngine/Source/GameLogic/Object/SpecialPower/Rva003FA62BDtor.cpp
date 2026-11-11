// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native86B destructor; observer tableC62A20 has two RET8 callbacks.
#include "../../../../Include/Common/Rva003FA62B.h"

class CreateAHeroData;
#include "../../../../Include/Common/Rva002B7250.h"
struct Rva003FA62BOwner {
    unsigned char m_pad00[0x1C];
    Rva002B7250 m_listeners1C;
};
Rva003FA62B::~Rva003FA62B()
{
    m_owner10->m_listeners1C.rva002B7250((CreateAHeroData *)this);
    clear();
}
