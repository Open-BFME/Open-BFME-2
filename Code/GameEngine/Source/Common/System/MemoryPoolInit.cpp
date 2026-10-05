// cl: /O2 /MD /EHsc
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
#include <new>
extern "C" __declspec(dllimport) char *__stdcall GetCommandLineA();
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *, const char *);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void *, const char *, const char *, unsigned int);
extern "C" __declspec(dllimport) void *__stdcall HeapCreate(unsigned long, unsigned int, unsigned int);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(void *, unsigned long, unsigned int);
extern "C" __declspec(dllimport) unsigned long __stdcall TlsAlloc();
void Rva002253C2Init();
// ?MemoryPoolAllocatorAssertion present-unmatched
// Empty callback: native pointer VA00A9E440 is the shared ICF RET.
static void MemoryPoolAllocatorAssertion() {}
namespace EA { namespace Allocator {
class GeneralAllocator { public: void SetAssertionFailureFunction(void *, void *); };
}}
class Rva00033B90Allocator {
public:
 Rva00033B90Allocator(void *, unsigned int, bool, void *, void *, void *);
private: char m_data[0x510];
};
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
	void *m_win32Heap;
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
    Rva002253C2Init();
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

#pragma comment(linker, "/alternatename:?g_heapTlsIndex@MemoryPool@@3KA=?g_Va00DB35A4@@3KA")
