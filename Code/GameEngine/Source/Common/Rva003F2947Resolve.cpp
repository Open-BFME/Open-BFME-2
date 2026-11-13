// cl: /DNDEBUG /MD
//
// ?rva003F2947@Rva003F2352@@QAEPAV1@PAV1@@Z @0x003F2947 33B, dump range 18.
// Same-class sibling of the rowed 0x003F2352 assign-through-hook: builds an
// uninitialized 8-byte Rva003F2352 temporary in the push-reserved frame
// slot, resolves it through this->rva003F2352, copies the resolved +0x04
// back over this, and returns this. Membership in Rva003F2352 is inferred
// from the identical head[4]+val[4] layout, the rowed (obj, obj) call, and
// the +0x04 traffic; the byte gate is the proof.
#include "../../Include/Common/Rva003F2352.h"

Rva003F2352 *Rva003F2352::rva003F2947(Rva003F2352 *src)
{
	Rva003F2352 tmp;
	Rva003F2352 *r = rva003F2352(&tmp, src);
	m_val = r->m_val;
	return this;
}
