// cl: /DNDEBUG /MD /EHsc
// NetCommandMsg::detach at RVA 0x004D55BC, full 26-byte retail body.
// BFME's de-pooled command has its count at +0x18 and frees it with a
// global-scope delete: the slot-0 deleting dtor with flags=0 destroys
// without freeing and returns the instance, which ::operator delete frees.
// Sibling detach@NetCommandNode (rowed 0x58B8AE) tail-calls into this body.
#include "../../Include/GameNetwork/NetCommandMsg.h"

void NetCommandMsg::detach()
{
    if (--m_referenceCount == 0 || m_referenceCount < 0)
        ::delete this;
}
