// cl: /O2 /MD /EHsc
// platformsdk
// PC export ?_Init@MemoryPool@@YAXXZ, RVA00030000, complete 406-byte body.
// Audit lead: docs/audits/2026-10-05-openbfme2, direct-export-symbols.json.
// Target evidence: the entry increments DE081C on repeat calls; otherwise it
// checks -startPaused, invokes the rowed setup through thunk179A -> 2253C2,
// builds the default and registered allocators, and allocates a TLS slot.
// HeapTable is the view already established by memory_pool.cpp. The allocator
// extent510 and six constructor arguments are read from this body. Pointer
// argument roles remain unknown, so its constructor keeps an address identity.
// BFME1 _Init was reviewed at 6583b3c1ff21db4a561285717028fdafc780b7db;
// its different pool/guard-word implementation is not used as layout evidence.
#include <windows.h>
#include <new>
#include <string.h>
#pragma intrinsic(memset)
void Rva0000179A();
// ?MemoryPoolAllocatorAssertion present-unmatched
// Empty callback: native pointer VA00A9E440 is the shared ICF RET.
static void MemoryPoolAllocatorAssertion() {}
#include "../../../Include/Common/GeneralAllocator.h"
namespace EA { namespace Allocator {
}}
// Native ctor33B90 zeroes these member blocks separately. The template
// expresses initialization; widths and every scalar offset are target facts.
template<int N> struct AllocatorZeroWords
{
    unsigned int words[N];
    AllocatorZeroWords() { memset(words, 0, sizeof(words)); }
};
void Rva000327D0Assertion(const char *);
void rva00031420(const char *);

// The lock the allocator creates on first setup: a CRITICAL_SECTION at +0
// whose initialize/addref/release helpers are the rowed 0x30D90/0x30DD0/
// 0x30DF0 family. Layout from that unit: 0x18-byte section, int at +0x18.
struct Rva00030DD0Lock
{
    CRITICAL_SECTION m_cs;
    volatile int m_ref;
};
Rva00030DD0Lock *Rva00030D90Init(Rva00030DD0Lock *lock);

// Linked-list headers embedded in the zero blocks. m_448's first 8 dwords
// zero and its +0x18/+0x1C slots self-link; m_49c's first 4 dwords zero and
// its +8/+0xC slots self-link. Default construction zeroes the whole list
// header exactly as the AllocatorZeroWords blocks do.
struct Rva00033B90ListHead
{
    unsigned int m_words[6];
    void *m_first;
    void *m_last;
    Rva00033B90ListHead() { memset(this, 0, sizeof(*this)); }
};
struct Rva00033B90BinHead
{
    unsigned int m_words[2];
    void *m_first;
    void *m_last;
    Rva00033B90BinHead() { memset(this, 0, sizeof(*this)); }
};

class Rva00033B90Allocator {
public:
 Rva00033B90Allocator(void *, unsigned int, bool, void *, void *, void *);
 bool rva00033700(void *, unsigned int, bool, void *, void *, void *);
private:
 bool m_0; unsigned int m_4;
 AllocatorZeroWords<10> m_8;
 AllocatorZeroWords<256> m_30;
 AllocatorZeroWords<4> m_430;
 unsigned int m_440,m_444;
 Rva00033B90ListHead m_448;
 unsigned int m_468;
 bool m_46c,m_46d;
 unsigned int m_470;
 unsigned char m_474,m_475;
 unsigned int m_478,m_47c,m_480;
 bool m_484;
 unsigned int m_488,m_48c,m_490,m_494;
 bool m_498;
 Rva00033B90BinHead m_49c;
 unsigned int m_4ac,m_4b0,m_4b4;
 void (*m_4b8)(const char *); void *m_4bc;
 void (*m_4c0)(const char *); void *m_4c4;
 unsigned int m_4c8,m_4cc,m_4d0,m_4d4,m_4d8,m_4dc;
 bool m_4e0; void *m_4e4;
 AllocatorZeroWords<8> m_4e8;

 unsigned char m_508,m_509,m_50a,m_50b,m_50c;
};
// Complete445B ctor called by _Init; zero blocks and default constants precede
// installing the diagnostic callbacks and forwarding six arguments to33700.
Rva00033B90Allocator::Rva00033B90Allocator(
    void *a, unsigned int size, bool b, void *c, void *d, void *e) :
    m_0(false), m_4(0), m_440(0), m_444(0), m_468(0),
    m_46c(false), m_46d(true), m_470(0), m_474(9), m_475(10),
    m_478(0), m_47c(0), m_480(0), m_484(false),
    m_488(0), m_48c(0), m_490(0), m_494(0), m_498(false),
    m_4ac(0), m_4b0(0), m_4b4(0x100), m_4c8(0), m_4cc(0), m_4d0(0),
    m_4d4(0x1000), m_4d8(0x1000000), m_4dc(0x400000),
    m_4e0(false), m_4e4(0), m_508(0xdd), m_509(0xde),
    m_50a(0xcd), m_50b(0xab), m_50c(0xfe)
{
    m_4b8 = Rva000327D0Assertion;
    m_4bc = this;
    m_4c0 = rva00031420;
    m_4c4 = this;
    rva00033700(a, size, b, c, d, e);
}
typedef char AllocatorExtentMustBe510[sizeof(Rva00033B90Allocator) == 0x510 ? 1 : -1];

// Native 0x0033700..0x00338BF (447B): one-time allocator setup, thiscall
// ret 0x18. Retail returns true on every path (mov al,1 at 0x338B9): the
// void pin signature was wrong and is renamed to bool. The 0x006FFD20
// WorldBuilder pair is the derived debug ctor, not this body.
bool Rva00033B90Allocator::rva00033700(void *a, unsigned int size, bool b,
    void *c, void *d, void *e)
{
    if (m_0)
        goto tail;
    m_0 = true;
    if (!m_4e4)
        m_4e4 = Rva00030D90Init((Rva00030DD0Lock *)&m_4e8);

    Rva00030DD0Lock *lock = (Rva00030DD0Lock *)m_4e4;
    if (lock != 0)
    {
        EnterCriticalSection(&lock->m_cs);
        lock->m_ref = lock->m_ref + 1;
    }

    m_4 = 0x40;
    memset(&m_8, 0, sizeof(m_8));
    memset(&m_30, 0, sizeof(m_30));

    // 0x7F self-linked 8-byte nodes; each node's next/prev point at the
    // 8-byte slot before it (the array header walks back to &m_30).
    unsigned int *node = (unsigned int *)&m_30;
    for (int i = 0; i < 0x7F; ++i)
    {
        node[2] = (unsigned int)node;
        node[3] = (unsigned int)node;
        node += 2;
    }

    memset(&m_430, 0, sizeof(m_430));
    m_440 = (unsigned int)(unsigned int *)&m_30;
    m_444 = 0;
    memset(&m_448, 0, sizeof(m_448));
    m_448.m_first = &m_448;
    m_448.m_last = &m_448;

    m_4 = (m_4 & 1) | 0x48;
    m_468 = 0;
    m_46c = false;
    m_488 = 0;
    m_48c = 0;
    m_490 = 0x10000;
    m_494 = 0x20000;
    m_498 = false;
    memset(&m_49c, 0, sizeof(m_49c));
    m_49c.m_first = &m_49c;
    m_49c.m_last = &m_49c;
    m_4c8 = 0x20000;
    m_4cc = 0x10000;
    m_4d0 = m_440;

    SYSTEM_INFO info;
    GetSystemInfo(&info);
    m_4d4 = info.dwPageSize;

    if (lock != 0)
    {
        lock->m_ref = lock->m_ref - 1;
        LeaveCriticalSection(&lock->m_cs);
    }

tail:
    if (a != 0 || size != 0)
        ((EA::Allocator::GeneralAllocator *)this)->rva000332D0(
            a, size, b, *(bool *)&c, d, e);
    return true;
}

namespace MemoryPool {
struct HeapRecord
{
	HeapRecord *m_next;
	unsigned int m_id;
	unsigned int m_size;
	EA::Allocator::GeneralAllocator *m_allocator;
};

enum
{
	MAX_HEAPS = 30,
	HEAP_BUCKETS = 101
};

struct HeapTable
{
	HANDLE m_win32Heap;
	int m_count;
	int m_reserved;
	HeapRecord m_records[MAX_HEAPS];
	HeapRecord *m_buckets[HEAP_BUCKETS];
	unsigned int m_unknown380;	// 0x00DE0794: nothing here reads it
	EA::Allocator::GeneralAllocator *m_allocators[MAX_HEAPS + 1];
	EA::Allocator::GeneralAllocator *m_defaultAllocator;
	bool m_clearAllocations;
	int m_initCount;
	bool m_shutDown;
	bool m_addingHeaps;
};

extern HeapTable g_heaps;
extern unsigned long g_heapTlsIndex;


// Native data at VA00DB35A0 starts at 8 MiB; setup may replace it.
unsigned int g_defaultHeapSize = 0x800000;
void _Init()
{
    if (g_heaps.m_initCount)
    {
        ++g_heaps.m_initCount;
        return;
    }
    if (strstr(GetCommandLineA(), "-startPaused"))
        MessageBoxA(0, "Waiting...", "Paused", 0);

    g_heaps.m_addingHeaps = true;
    Rva0000179A();
    g_heaps.m_addingHeaps = false;
    ++g_heaps.m_initCount;

    g_heaps.m_win32Heap = HeapCreate(5, 0x10000, 0);
    g_heaps.m_allocators[0] = (EA::Allocator::GeneralAllocator *)
        new (HeapAlloc(g_heaps.m_win32Heap, 0, 0x510))
            Rva00033B90Allocator(0, g_defaultHeapSize, true, 0, 0, 0);
    g_heaps.m_allocators[0]->SetAssertionFailureFunction(
        (void *)MemoryPoolAllocatorAssertion, 0);
    g_heaps.m_defaultAllocator = g_heaps.m_allocators[0];

    for (int i = 0; i < g_heaps.m_count; ++i)
    {
        EA::Allocator::GeneralAllocator *allocator = (EA::Allocator::GeneralAllocator *)
            new (HeapAlloc(g_heaps.m_win32Heap, 0, 0x510))
                Rva00033B90Allocator(0, g_heaps.m_records[i].m_size, true, 0, 0, 0);
        g_heaps.m_allocators[i + 1] = allocator;
        g_heaps.m_records[i].m_allocator = allocator;
        allocator->SetAssertionFailureFunction((void *)MemoryPoolAllocatorAssertion, 0);
    }
    g_heapTlsIndex = TlsAlloc();
}
}


// Retail 0x000327D0 (13 bytes): the assertion callback the allocator
// constructor above installs at +0x4B8 with the allocator as its +0x4BC
// context. It writes the expression to the debugger and breaks; the context
// argument is unused (the default assertion handler of EA's allocator).
void Rva000327D0Assertion(const char *expression)
{
    OutputDebugStringA(expression);
    __debugbreak();
}
