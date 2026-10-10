// ??0GeneralAllocatorDebug@@QAE@PAXI_N000@Z
// partial score=1.0 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD /EHsc
// GeneralAllocatorDebug construction and table callbacks. Identity comes
// from the owned VerifyGuardFill failure string and the debug-allocator
// destructor's base/member unwind actions. The original bank supplies the
// structural guide; every field offset and callback ABI is target evidence.
// Constructor 006C4A50..006C4C0C: reference-bound table keeps state-1 and setup
// pushes after scalar initialization; reference-bound clear pointer inside
// the initialization branch preserves LEA before REP STOSD setup.
// Callback slots are native DIR32 values AC3D20 and AC2240. They use the same
// 678 self-provider and 510 initialization state as the constructor.
// No donor names or inferred base member layouts are claimed as target facts.

#include <string.h>
#pragma intrinsic(memset)

class Rva00033E90 { public: void freeBlock(void *); };
namespace EA { namespace Allocator {
class GeneralAllocator { public: void rva000338F0(void *); };
} }
class Rva006C39F0Owner { public: void *rva006C3940Alloc(unsigned int); };

class Rva00033B90Allocator
{
public:
	Rva00033B90Allocator(void *a, unsigned int size, bool b, void *c, void *d, void *e);
	~Rva00033B90Allocator();
	void rva00033700(void *a, unsigned int size, bool b, void *c, void *d, void *e);
protected:
	unsigned char m_base000[0x508];
	unsigned char m_fill508; // +0x508
	unsigned char m_fill509; // +0x509
	unsigned char m_fill50A; // +0x50A
	unsigned char m_fill50B; // +0x50B
	unsigned char m_fill50C; // +0x50C
	unsigned char m_pad50D[3];
};

// Hash table whose rowed clear 0x006C21B0 is its unwind action.
class Rva006C17B0
{
public:
	Rva006C17B0()
		: m_array(0), m_04(false), m_count(0), m_capacity(0x1000), m_10(0),
		  m_allocate(0), m_free(0), m_context(0)
	{
	}
	~Rva006C17B0();
	void **m_array; // +0x00
	bool m_04; // +0x04
	unsigned int m_count; // +0x08
	unsigned int m_capacity; // +0x0C
	unsigned int m_10; // +0x10
	void *(__cdecl *m_allocate)(unsigned int size, void *context); // +0x14
	void (__cdecl *m_free)(void *p, void *context); // +0x18
	void *m_context; // +0x1C
};

struct GeneralAllocatorDebugList
{
	void *m_head; // +0x00
	unsigned int m_capacity; // +0x04
	void *m_first; // +0x08
	void *m_last; // +0x0C
	unsigned int m_10; // +0x10
	unsigned int m_14; // +0x14
	bool m_18; // +0x18
};

class GeneralAllocatorDebug : public Rva00033B90Allocator
{
public:
	GeneralAllocatorDebug(void *a, unsigned int size, bool b, void *c, void *d, void *e);
	static void *__cdecl rva006C3D20(unsigned int size, void *context);
	static void __cdecl rva006C2240(void *p, void *context);
private:
	bool m_debugInitialized; // +0x510
	unsigned int m_514[8]; // +0x514
	float m_534; // +0x534
	unsigned int m_538; // +0x538
	unsigned int m_53C; // +0x53C
	unsigned int m_540; // +0x540
	unsigned int m_544; // +0x544
	GeneralAllocatorDebugList m_list; // +0x548
	unsigned int m_564;
	unsigned int m_568; // +0x568
	unsigned int m_56C; // +0x56C
	unsigned int m_debugBlock[0x40]; // +0x570
	unsigned int m_670; // +0x670
	unsigned int m_674; // +0x674
	GeneralAllocatorDebug *m_self; // +0x678
	unsigned int m_67C; // +0x67C
	bool m_680; // +0x680
	Rva006C17B0 m_table; // +0x684
};

GeneralAllocatorDebug::GeneralAllocatorDebug(void *a, unsigned int size, bool b, void *c, void *d, void *e)
	: Rva00033B90Allocator(a, size, b, c, d, e)
{
	Rva006C17B0 &block = m_table;
	m_debugInitialized = false;
	m_514[0] = 0;
	m_514[1] = 0;
	m_514[2] = 0;
	m_514[3] = 0;
	m_514[4] = 0;
	m_514[5] = 0;
	m_514[6] = 0;
	m_514[7] = 0;
	m_534 = 0.25f;
	m_538 = 8;
	m_53C = 10000;
	m_fill508 = 0xDD;
	m_fill509 = 0xDE;
	m_fill50A = 0xCD;
	m_fill50B = 0xAB;
	m_fill50C = 0xFE;
	m_540 = 0;
	m_544 = 0;
	m_list.m_head = 0;
	m_list.m_capacity = 0x10;
	m_list.m_first = &m_list;
	m_list.m_last = &m_list;
	m_list.m_10 = 0;
	m_list.m_14 = 0;
	m_list.m_18 = false;
	m_568 = 0;
	m_56C = 0;
	m_self = this;
	m_67C = 0;
	m_680 = false;
	block.m_allocate = rva006C3D20;
	block.m_free = rva006C2240;
	block.m_context = this;
	rva00033700(0, 0, true, 0, 0, 0);
	if (!m_debugInitialized)
	{
		unsigned int *const & buffer = m_debugBlock;
		m_debugInitialized = true;
		memset(buffer, 0, sizeof(m_debugBlock));
		m_670 = 0;
		m_674 = 0;
	}
}

void *__cdecl GeneralAllocatorDebug::rva006C3D20(unsigned int size, void *context)
{
    return ((Rva006C39F0Owner *)context)->rva006C3940Alloc(size);
}

void __cdecl GeneralAllocatorDebug::rva006C2240(void *p, void *context)
{
    GeneralAllocatorDebug *allocator = (GeneralAllocatorDebug *)context;
    if (allocator->m_self == allocator)
    {
        if (allocator->m_debugInitialized)
            ((Rva00033E90 *)allocator)->freeBlock(p);
    }
    else
        ((EA::Allocator::GeneralAllocator *)allocator->m_self)->rva000338F0(p);
}
