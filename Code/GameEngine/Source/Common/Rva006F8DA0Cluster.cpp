// cl: /MD /Oy /EHs
//
// ??1Rva006F8D70@@UAE@XZ @0x006F8DA0 103B: complete destructor of the
// Rva006F8D70 family (vtable 0x008EC9CC, deleting dtor 0x006F8D70, size 0x20).
// Target evidence: destroys the sub-object at +0x1C through the pinned
// destructor 0x006F84F0, stores the shared vtable 0x008EC9CC (DIR32, masked),
// then destroys the +0x10 pointer through rowed 0x0070A840 and releases it
// with size 0x14 through the pinned 0xE176E8 pool. The base sub-object body is
// the rowed Rva006F8460 dtor at 0x006F8460 and is inlined here; the base is
// renamed Rva006F8460Base so this TU does not re-emit that rowed symbol.
// /Oy is what the bytes force: retail carries the frame-pointer-less manual
// SEH prolog (`push -1 / push scope / mov eax,fs:[0]`) and no ebp frame.
// Names are address-derived; the near file's Rva006DE350 scaffold is only the
// deleting-dtor recipe and does not describe these members.

#include "../../Include/Common/Rva0070A840.h"

#include "../../Include/Common/Rva006DB270.h"

// Existing Apt pool provider; retail callers load this global at VA 0x00E176E8.
extern Rva006DB270 *g_pChainBlockAllocator;

class AptDisplayList	// dtor 0x006F84F0 is rowed as ??1AptDisplayList
{
public:
	~AptDisplayList();
};

class Rva006F8460Base
{
public:
	virtual ~Rva006F8460Base()
	{
		Rva0070A840 *block = m_10;
		if (block != 0) {
			block->Rva0070A840::~Rva0070A840();
			g_pChainBlockAllocator->freeBlock(block, 0x14);
		}
	}

private:
	char m_pad[0x0C];
	Rva0070A840 *m_10;
};

class __declspec(novtable) Rva006F8D70 : public Rva006F8460Base
{
public:
	virtual ~Rva006F8D70();

private:
	char m_pad14[0x8];
	AptDisplayList m_1c;
};

Rva006F8D70::~Rva006F8D70()
{
}
