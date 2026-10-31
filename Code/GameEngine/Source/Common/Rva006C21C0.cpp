// cl: /O2 /DNDEBUG /MD /EHsc
// ?rva006C21C0@Rva006C17B0@@QAE_NIPAX@Z 0x006C21C0 118B hash insert with resize check via rowed 0x006C1920 and alloc via +0x14; after rva006C21B0 0x006C21B0; caller 0x006C39F0
struct Rva006C17B0Node
{
	void *m_pad0;
	void *m_data;
	Rva006C17B0Node *m_next;
};

// Hash table whose rowed clear 0x006C21B0 is its unwind action.
class Rva006C17B0
{
public:
	void rva006C17B0(bool flag1, bool flag2);
	void rva006C21B0();
	bool rva006C21C0(unsigned int len, void *buf);
	Rva006C17B0()
		: m_array(0), m_pad4(false), m_count(0), m_padC(0x1000), m_10(0),
		  m_alloc(0), m_callback(0), m_cbArg(0)
	{
	}
	~Rva006C17B0();
	void **m_array; // +0x00
	bool m_pad4; // +0x04
	unsigned int m_count; // +0x08
	unsigned int m_padC; // +0x0C
	unsigned int m_10; // +0x10
	void *(__cdecl *m_alloc)(unsigned int size, void *context); // +0x14
	void (__cdecl *m_callback)(void *p, void *context); // +0x18
	void *m_cbArg; // +0x1C
};


class Rva006C1850
{
public:
	bool rva006C1920(unsigned int newSize);
};

bool Rva006C17B0::rva006C21C0(unsigned int len, void *buf)
{
	unsigned int bucketCount = m_count;
	unsigned int size = m_10;
	unsigned int newBuckets = bucketCount * 2;
	unsigned int need = size * 4 + 4;
	if (need >= newBuckets) {
		unsigned int cap = m_padC;
		unsigned int trySize = newBuckets + 1;
		if (trySize < cap)
			trySize = cap;
		if (!((Rva006C1850 *)this)->rva006C1920(trySize))
			return false;
	}
	Rva006C17B0Node *node = (Rva006C17B0Node *)m_alloc(12, m_cbArg);
	if (node) {
		unsigned int h = (len >> 3) % m_count;
		Rva006C17B0Node *head = ((Rva006C17B0Node **)m_array)[h];
		node->m_pad0 = (void *)len;
		node->m_data = buf;
		node->m_next = head;
		((Rva006C17B0Node **)m_array)[h] = node;
		++m_10;
	}
	return node != 0;
}

// GeneralAllocatorDebug constructor and callback family; full boundaries
// 6C4A50..6C4C0C (444B),6C2240..6C2270 (48B),6C3D20..6C3D2F (15B).
// Target VerifyGuardFill string and owned destructor establish the debug
// allocator identity; scalar offsets/callback slots and table ABI are native.
// Shared 32-byte hash-table view reconciled with this unit's existing118B
// insert owner. This unit already preserves its library /O2 x87 G6 settings.
// /EHsc enables the constructor's owned base/table unwind actions.
#include <string.h>
#pragma intrinsic(memset)

namespace EA { namespace Allocator {
class GeneralAllocator { public: void rva00033150(const void *block); void rva000338F0(void *); bool rva00033D50(); };
} }
class Rva006C39F0Owner { public: void *rva006C3940Alloc(unsigned int); };

class Rva00033B90Allocator
{
public:
	Rva00033B90Allocator(void *a, unsigned int size, bool b, void *c, void *d, void *e);
	// Retail's base destructor 0x00034D00 is a tail jump to the rowed teardown 0x00033D50.
	~Rva00033B90Allocator() { ((EA::Allocator::GeneralAllocator *)this)->rva00033D50(); }
	bool rva00033700(void *a, unsigned int size, bool b, void *c, void *d, void *e);
protected:
	unsigned char m_base000[0x508];
	unsigned char m_fill508; // +0x508
	unsigned char m_fill509; // +0x509
	unsigned char m_fill50A; // +0x50A
	unsigned char m_fill50B; // +0x50B
	unsigned char m_fill50C; // +0x50C
	unsigned char m_pad50D[3];
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
	unsigned __int64 getSequence() const;
	static void *__cdecl rva006C3D20(unsigned int size, void *context);
	static void __cdecl rva006C2240(void *block, void *context);
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
	unsigned __int64 m_sequence; // +0x568, returned in EDX:EAX by6C1B50
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
	m_sequence = 0;
	m_self = this;
	m_67C = 0;
	m_680 = false;
	block.m_alloc = rva006C3D20;
	block.m_callback = rva006C2240;
	block.m_cbArg = this;
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

void __cdecl GeneralAllocatorDebug::rva006C2240(void *block, void *context)
{
    GeneralAllocatorDebug *allocator = (GeneralAllocatorDebug *)context;
    if (allocator->m_self == allocator)
    {
        if (allocator->m_debugInitialized)
            ((EA::Allocator::GeneralAllocator *)allocator)->rva00033150(block);
    }
    else
        ((EA::Allocator::GeneralAllocator *)allocator->m_self)->rva000338F0(block);
}

// Native6C1B50..6C1B5D,13B, between CC alignment regions. Returns the
// debug sequence pair568/56C in EDX:EAX; the constructor initializes both,
// and record writer6C3D30 uses this pair for debug field9. API name unresolved.
unsigned __int64 GeneralAllocatorDebug::getSequence() const
{
    return m_sequence;
}
