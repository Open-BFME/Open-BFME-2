// cl: /MD
// Each destructor rowed in another unit is only declared here: the inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva006F8460@@UAEPAXI@Z @0x006F8490 35B.
// Scalar deleting dtor calls rowed ??1 at 0x006F8460 plus sized pool free
// via pinned 0x006DB270 with pool at 0x00E176E8 and class size 0x18.
#include "../../Include/Common/Rva006DB270.h"
// Existing Apt pool provider; retail callers load this global at VA 0x00E176E8.
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006F8460
{
public:
	explicit Rva006F8460(int) {}
	virtual ~Rva006F8460();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[0x18 - 4];
};
Rva006F8460 *famgenNew_Rva006F8460() { return new Rva006F8460(0); }
void deleteRva006F8460(Rva006F8460 *p) { delete p; }
