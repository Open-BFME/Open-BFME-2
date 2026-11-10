// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native75B listener constructor: real two-slot observer and8-byte records.
#include "../../Include/Common/Rva003FA62B.h"

struct Rva002BA8F1Listener;
#include "../../Include/Common/Rva005A0B4CList.h"
struct Rva003FA62BOwner {
    char m_pad00[0x1C];
    Rva005A0B4CList m_list;
};
Rva003FA62B::Rva003FA62B(Rva003FA62BOwner *owner) : m_owner10(owner)
{
    owner->m_list.append((Rva002BA8F1Listener *)this);
}
