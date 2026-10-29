// cl: /O1 /MD
// ??_GRva006F84C0@@UAEPAXI@Z, retail 0x006F84C0, 35 bytes.
// Scalar deleting destructor: calls complete dtor at 0x006F8460
// (??1Rva006F8460 rowed 37B) then sized pool release via pinned
// 0x006DB270 with pool at 0x00E176E8 and class size 0x1C.

inline void *operator new(unsigned int, void *p) { return p; }

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

// Existing Apt pool provider; retail callers load this global at VA 0x00E176E8.
extern Rva006DB270 *g_pChainBlockAllocator;

// Rva006F8460's row (Rva006F8460Dtor.cpp) is the complete dtor retail calls:
// this class's implicit destructor has no vptr reset and inlines into the
// deleting dtor as that call, so no destructor of its own is emitted.
class Rva006F8460
{
public:
	virtual ~Rva006F8460();
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
