// cl: /MD
// Each destructor rowed in another unit is only declared here: the inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva006FB9B0@@UAEPAXI@Z, retail 0x006FB980, 35 bytes.
// Scalar deleting destructor for Rva006FB9B0 (vtable 0x008ED808, slot 14
// offset 0x38 per tf.py vslot). Calls the rowed complete dtor at 0x006FB9B0
// (11B vptr store + tail-jmp to pinned base 0x006DE350), then sized release
// through the pinned pool deallocator 0x006DB270 with the pool object at
// 0x00E176E8 and class size 0xC. Sized operator delete inlines to the retail
// mov ecx,[pool] + push 0xC + push this + call shape (SizedDeleteDestructors
// precedent); the dtor stays empty so the local ??1 copy remains 11B.

#include "../../Include/Common/Rva006DE350.h"

#include "../../Include/Common/Rva006DB270.h"

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva006FB9B0 : public Rva006DE350
{
public:
	explicit Rva006FB9B0(int) {}
	virtual ~Rva006FB9B0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[8]; // +0x04..0x0B: sizeof 0xC for the sized delete
};

Rva006FB9B0 *famgenNew_Rva006FB9B0() { return new Rva006FB9B0(0); }

void deleteRva006FB9B0(Rva006FB9B0 *p)
{
	delete p;
}
