// ?_AddHeap@MemoryPool@@YAXII@Z
// partial score=0.97 date=2026-09-23
// BFME 2's memory-pool entry points. `namespace MemoryPool` is retail's own
// name: every `_`-prefixed function here is exported under it
// (reverse/exports.csv), and 0x00030730 resolves each export back out of the
// running module by name with GetProcAddress. Unlike BFME 1's memory_pool.cpp,
// the heaps are EA::Allocator::GeneralAllocator instances (the export
// signatures name that type), one default heap plus up to thirty more
// registered by id through _AddHeap during _Init.
//
// The heap table is read off the code that addresses it:
//   0x00DE0418  number of registered heaps (index 0, the default, is extra)
//   0x00DE0420  thirty 16-byte records: hash-chain link, id, size, allocator
//   0x00DE0600  101 hash buckets keyed by id % 101
//   0x00DE0798  allocator by index; [0] is the default heap
//   0x00DB35A0  default heap size (_AddHeap with id 0)
//   0x00DB35A4  TLS slot holding the calling thread's current heap id
//   0x00DE0821  set only while _Init runs; _AddHeap is ignored otherwise
// The variable names are descriptive; retail's are not recoverable.

extern "C" __declspec(dllimport) void *__stdcall TlsGetValue(unsigned long index);

namespace EA
{
namespace Allocator
{
class GeneralAllocator;
}
}

namespace MemoryPool
{

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
};

extern HeapTable g_heaps;
extern unsigned int g_defaultHeapSize;
extern unsigned long g_heapTlsIndex;
extern bool g_addingHeaps;

EA::Allocator::GeneralAllocator *_GetHeapAllocator(unsigned int id)
{
	if (id == 0 && g_heapTlsIndex != (unsigned long)-1)
		id = (unsigned int)TlsGetValue(g_heapTlsIndex);

	for (HeapRecord *record = g_heaps.m_buckets[id % HEAP_BUCKETS]; record != 0; record = record->m_next)
	{
		if (record->m_id == id)
			return record->m_allocator;
	}
	return g_heaps.m_allocators[0];
}

EA::Allocator::GeneralAllocator *_GetHeapAllocatorByIndex(unsigned int index)
{
	if (index <= (unsigned int)g_heaps.m_count)
		return g_heaps.m_allocators[index];
	return 0;
}

void _AddHeap(unsigned int id, unsigned int size)
{
	if (!g_addingHeaps)
		return;
	int count = g_heaps.m_count;
	if (count >= MAX_HEAPS)
		return;
	if (id == 0)
	{
		g_defaultHeapSize = size;
		return;
	}

	HeapRecord **bucket = &g_heaps.m_buckets[id % HEAP_BUCKETS];
	for (HeapRecord *record = *bucket; record != 0; record = record->m_next)
	{
		if (record->m_id == id)
		{
			record->m_size = size;
			return;
		}
	}

	HeapRecord *record = &g_heaps.m_records[count++];
	record->m_size = size;
	record->m_next = *bucket;
	record->m_id = id;
	g_heaps.m_count = count;
	*bucket = record;
}

}
