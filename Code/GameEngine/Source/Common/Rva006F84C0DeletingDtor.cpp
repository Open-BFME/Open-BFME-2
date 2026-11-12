// cl: /O1 /MD
// ??_GRva006F84C0@@UAEPAXI@Z, retail 0x006F84C0, 35 bytes.
// Scalar deleting destructor: calls complete dtor at 0x006F8460
// (??1Rva006F8460 rowed 37B) then sized pool release via pinned
// 0x006DB270 with pool at 0x00E176E8 and class size 0x1C.

inline void *operator new(unsigned int, void *p) { return p; }

#include "../../Include/Common/Rva006DB270.h"

// Existing Apt pool provider; retail callers load this global at VA 0x00E176E8.
extern Rva006DB270 *g_pChainBlockAllocator;

// Rva006F8460's row (AptDisplayList.cpp) is the complete dtor retail calls:
// this class's implicit destructor has no vptr reset and inlines into the
// deleting dtor as that call, so no destructor of its own is emitted.
// Constructing the derived class also emits the base's vtable and its
// ??_GRva006F8460 COMDAT, so the base carries the class's pool release as
// AptDisplayList.cpp and Rva006F6A50Cluster.cpp declare it: retail 0x006F8490
// frees through freeBlock, never the global operator delete.
class Rva006F8460
{
public:
	virtual ~Rva006F8460();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
private:
	char m_pad[0x18 - 4];
};

class Rva006F84C0 : public Rva006F8460
{
public:
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad18[0x1C - 0x18]; // sizeof 0x1C for the sized delete
};

// ?bfmeAnchorRva006F84C0Vtable absent-from-retail
// Constructing one emits the vtable, and with it the scalar deleting dtor.
void bfmeAnchorRva006F84C0Vtable(Rva006F84C0 *p)
{
	new (p) Rva006F84C0;
}
