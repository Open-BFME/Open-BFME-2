// cl: /DNDEBUG /MD
//
// ?attach@RvaSmartPtr12@@QAEXXZ, retail 0x0004CB9A (38 bytes).
//
// Intrusive-list attach for the 12-byte smart pointer (RvaSmartPtr12/Bfme
// handle at +0x15C of Rva003FDA90SmartField): links the fresh copy into the
// owner ParticleSystem chain whose head lives at +0x9C/+0xA0 (cf.
// ParticleSystemHandle_dtor.cpp). Retail loads last via add eax,0xA0, zeroes
// +8 with and [m],0, stores prev, publishes this to last, then patches
// prev->next or first. Callers are the rowed copy ctor 0x4CC19 and the rowed
// assignment 0x4CC3D plus the dtor TU 0x4CC04. Same flags as SmartPtrCopyCtor.

struct ParticleSystemChain
{
	char m_pad[0x9C];
	class RvaSmartPtr12 *m_first; // +0x9C
	class RvaSmartPtr12 *m_last; // +0xA0
};

#include "../../../Include/Common/RvaSmartPtr12.h"

void RvaSmartPtr12::attach() throw()
{
	ParticleSystemChain *sys = (ParticleSystemChain *)field00;
	RvaSmartPtr12 *last = sys->m_last;
	field08 = 0;
	field04 = last;
	sys->m_last = this;
	if (field04 != 0)
		field04->field08 = this;
	else
		((ParticleSystemChain *)field00)->m_first = this;
}
