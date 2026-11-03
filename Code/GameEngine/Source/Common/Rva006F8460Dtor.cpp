// cl: /MD
//
// ??1Rva006F8460@@UAE@XZ retail 0x006F8460 37B dtor.
// Evidence: vtable 0x008EC9CC at +0; m_10 freed via member dtor 0x0070A840
// plus pool freeBlock 0x006DB270 size 0x14 with pool 0x00A176E8.
class Rva0070A840
{
public:
	~Rva0070A840();
};
#include "../../Include/Common/Rva006DB270.h"
// Existing Apt pool provider; retail callers load this global at VA 0x00E176E8.
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006F8460
{
public:
	virtual ~Rva006F8460();
	// Pooled like FamilyDeletingDtors_Rva006F8460.cpp's view: retail's deleting
	// dtor 0x006F8490 frees the 0x18-byte object to the chain-block pool.
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
private:
	char m_pad[0x0C];
	Rva0070A840 *m_10;
	char m_pad14[0x18 - 0x14];
};

// Not expanded into the deleting dtor: retail 0x006F8490 calls it.
__declspec(noinline) Rva006F8460::~Rva006F8460()
{
	Rva0070A840 *p = m_10;
	if (p != 0) {
		p->Rva0070A840::~Rva0070A840();
		g_pChainBlockAllocator->freeBlock(p, 0x14);
	}
}
