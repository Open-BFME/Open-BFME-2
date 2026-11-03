// cl: /MD
// Each destructor rowed in another unit is only declared here: the inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva008A2C80@@UAEPAXI@Z @0x006E6B10, 35B.
// Scalar deleting dtor slot 1 of vtable 0x008EC278; calls rowed ??1 at
// 0x006E5FF0 plus sized pool free via pinned 0x006DB270 with pool at
// 0x00E176E8 and class size 0x38. Same sized-pool recipe as Rva006FBA10.

#include "../../Include/Common/Rva006DB270.h"

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva008A2C80 { public: explicit Rva008A2C80(int) {} virtual ~Rva008A2C80();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[0x38 - 4]; };
Rva008A2C80 *famgenNew_Rva008A2C80() { return new Rva008A2C80(0); }
void deleteRva008A2C80(Rva008A2C80 *p) { delete p; }
