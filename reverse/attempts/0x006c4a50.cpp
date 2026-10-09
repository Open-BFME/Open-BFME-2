// ??0GeneralAllocatorDebug@@QAE@PAXI_N000@Z
// partial score=0.95 date=2026-10-09
// cl: /O2 /G6 /DNDEBUG /MD /EHsc
//
// ??0GeneralAllocatorDebug@@QAE@PAXI_N000@Z, retail 0x006C4A50 (444 bytes).
// The debug allocator's constructor (class name from the retail failure
// string of its rowed VerifyGuardFill 0x006C3020). Target evidence:
//  - forwards its six arguments to the rowed base allocator constructor
//    0x00033B90 (Rva00033B90Allocator in MemoryPoolInit.cpp; unwind state 0
//    runs the base destructor 0x00034D00);
//  - constructs the hash table at +0x684 (unwind state 1 runs the rowed
//    clear 0x006C21B0 on it): zero words with capacity 0x1000 at +0x690;
//  - body: debug scalars from +0x510 (0.25f at +0x534 8 at +0x538 and 10000
//    at +0x53C); the base's five fill bytes +0x508..+0x50C (DD DE CD AB FE);
//    an empty list at +0x548 (capacity 16 with first and last at its head);
//    a self pointer at +0x678; the table's allocate/free callbacks
//    0x006C3D20 and 0x006C2240 with this as context;
//  - then the base's pinned setup 0x00033700 with (0 0 true 0 0 0) and the
//    one-time clear of the 0x100-byte block at +0x570.
// Region flags /O2 /G6 (flag_regions.csv says /arch:SSE but the 0.25f store is an
// integer immediate which only the x87 build emits).
//
// NEAR: 444 of 444 bytes compile; the only difference is scheduling. Retail
// keeps `push 0; push 0; mov ecx,esi` and the EH state-1 store after the body's
// field stores (just before the table callbacks), this source hoists those
// four instructions above the field stores. Tried: mem-initializers (moves
// the scalars before the table), an intermediate base for the scalars (moves
// the table block after them), an inline helper, argument sources, /G5 /G7 /Ox.

#include <string.h>
#pragma intrinsic(memset)

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
	m_table.m_allocate = rva006C3D20;
	m_table.m_free = rva006C2240;
	m_table.m_context = this;
	rva00033700(0, 0, true, 0, 0, 0);
	if (!m_debugInitialized)
	{
		m_debugInitialized = true;
		memset(m_debugBlock, 0, sizeof(m_debugBlock));
		m_670 = 0;
		m_674 = 0;
	}
}
