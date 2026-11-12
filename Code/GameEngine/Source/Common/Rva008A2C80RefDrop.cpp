// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??1Rva00171DB0 (0x00171DB0, Q4OwnedPtrDtors.cpp); same
// single-vtable shape, chaining to the base destructor already landed as
// ??1Gen_008AC620@@QAE@XZ, but the owned member here is a plain refcounted
// pointer decremented via Rva00894D90Accessor::decrement and dropped via
// bfmeDropVGO when the count reaches zero (instead of a two-vcall release).

#include "../../Include/Common/Rva00894D90Accessor.h"

void bfmeDropVGO(void *p);

// The base dtor this chains to (0x006ED150) is rowed as Rva006ED150's.
class Rva006ED150
{
public:
	virtual ~Rva006ED150();
};

#include "../../Include/Common/Rva006DB270.h"
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva008A2C80 : public Rva006ED150
{
public:
	virtual ~Rva008A2C80();

private:
	unsigned char m_pad[0x34 - 4];
	int *m_ptr;
public:
	static void operator delete(void *p, unsigned int size) { g_pChainBlockAllocator->freeBlock(p, size); }
};

// ??1Rva008A2C80@@UAE@XZ
Rva008A2C80::~Rva008A2C80()
{
	if (m_ptr)
	{
		if (Rva00894D90Accessor::decrement(m_ptr) == 0)
			bfmeDropVGO(m_ptr);
	}
}
