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

class RvaSmartPtr12
{
public:
	void attach();

private:
	void *m_ptr; // +0x0
	int m_pad04; // +0x4
	int m_pad08; // +0x8
};

void RvaSmartPtr12::attach()
{
	ParticleSystemChain *sys = (ParticleSystemChain *)m_ptr;
	RvaSmartPtr12 *last = sys->m_last;
	m_pad08 = 0;
	m_pad04 = (int)last;
	sys->m_last = this;
	if (m_pad04 != 0)
		((RvaSmartPtr12 *)m_pad04)->m_pad08 = (int)this;
	else
		((ParticleSystemChain *)m_ptr)->m_first = this;
}
