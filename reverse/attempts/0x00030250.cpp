// ?_DumpFragmentation@MemoryPool@@YAXPAU_iobuf@@_NPBD@Z
// partial score=0.95 date=2026-09-23
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
// The contiguous addresses are modelled as one object, HeapTable at
// 0x00DE0414: _AddHeap (banked, not yet exact) only reloads its bucket head
// after the record stores when the records and buckets share one object.
// The variable names are descriptive; retail's are not recoverable.

extern "C" __declspec(dllimport) void *__stdcall TlsGetValue(unsigned long index);

struct _iobuf;
extern "C" __declspec(dllimport) int __cdecl fprintf(_iobuf *file, const char *format, ...);

namespace EA
{
namespace Allocator
{
// One entry of a PPMalloc heap report, as _DumpFragmentation reads it.
struct BlockInfo
{
	void *m_core;
	unsigned int m_blockSize;
	void *m_data;
	unsigned int m_dataSize;
	char m_blockType;	// 2 allocated, 4 free, 8 core
	bool m_mapped;
};

// PPMalloc's allocator. Its methods are named by address: the call shapes fit
// the public PPMalloc API (noted beside each), but nothing in this binary
// names them.
class GeneralAllocator
{
public:
	bool rva00032830(const void *block, int addressType);	// ValidateAddress-like
	bool rva00032920(const void *block);			// owns-address test
	bool rva000329E0(int level);				// ValidateHeap-like
	unsigned int rva00032A20(const void *block);		// GetUsableSize-like
	void rva000338F0(void *block);				// Free-like
	void *rva00035080(unsigned int size, int flags);	// Malloc-like
	void *rva00035190(void *block, unsigned int size, int flags);	// Realloc-like
	void *rva00035210(unsigned int count, unsigned int size, int flags);	// Calloc-like
	void *rva000353B0(void *context, int blockTypes, bool copy, void *storage, unsigned int storageSize);	// ReportBegin-like
	const BlockInfo *rva00032F60(void *context, int blockTypes);	// ReportNext-like
	void rva00033E90(void *context);			// ReportEnd-like
};
}
}

namespace MemoryPool
{

enum AllocType
{
};

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
	EA::Allocator::GeneralAllocator *m_allocators[MAX_HEAPS + 1];
	EA::Allocator::GeneralAllocator *m_defaultAllocator;
	bool m_clearAllocations;
	int m_initCount;
	bool m_shutDown;
	bool m_addingHeaps;
};

extern HeapTable g_heaps;
extern unsigned long g_heapTlsIndex;

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

void *_Allocate(unsigned int size, AllocType type, unsigned int heap)
{
	EA::Allocator::GeneralAllocator *allocator = _GetHeapAllocator(heap);
	if (g_heaps.m_clearAllocations)
		return allocator->rva00035210(size, 1, 0);
	return allocator->rva00035080(size, 0);
}

void *_Reallocate(void *block, unsigned int size, AllocType type, unsigned int heap)
{
	EA::Allocator::GeneralAllocator *allocator = _GetHeapAllocator(heap);
	return allocator->rva00035190(block, size, 0);
}

void _Free(void *block, AllocType type)
{
	if (g_heaps.m_shutDown)
		return;
	if (block == 0)
		return;
	for (int i = 0; i <= g_heaps.m_count; ++i)
	{
		if (g_heaps.m_allocators[i]->rva00032920(block))
		{
			g_heaps.m_allocators[i]->rva000338F0(block);
			return;
		}
	}
}

bool _IsValidBlock(void *block, unsigned int heap)
{
	EA::Allocator::GeneralAllocator *allocator = _GetHeapAllocator(heap);
	return allocator->rva00032830(block, 1);
}

unsigned int _GetBlockSize(void *block, unsigned int heap)
{
	if (block == 0)
		return 0;
	EA::Allocator::GeneralAllocator *allocator = _GetHeapAllocator(heap);
	return allocator->rva00032A20(block);
}

unsigned int _GetBlockHeap(void *block)
{
	if (block == 0)
		return 0;
	for (int i = 0; i <= g_heaps.m_count; ++i)
	{
		if (g_heaps.m_allocators[i]->rva00032920(block))
		{
			if (i == 0)
				return 0;
			return g_heaps.m_records[i - 1].m_id;
		}
	}
	return 0;
}

void _VerifyIntegrity()
{
	for (int i = 0; i <= g_heaps.m_count; ++i)
		g_heaps.m_allocators[i]->rva000329E0(3);
}

void _Exit()
{
	if (--g_heaps.m_initCount != 0)
		return;

	for (int i = 0; i <= g_heaps.m_count; ++i)
	{
		// The heap's four-character id, spelled for a log line the release
		// build compiles out; only the byte stores survive.
		char name[8];
		char *p = &name[4];
		// Retail walks a pointer to this record's id and reads the previous
		// record's (heap i is record i-1; heap 0 is the default and has none).
		unsigned int *ids = &g_heaps.m_records[i].m_id;
		if (ids != &g_heaps.m_records[0].m_id)
		{
			unsigned int id = ids[-(int)(sizeof(HeapRecord) / sizeof(unsigned int))];
			for (int shift = 0; shift < 32; shift += 8)
			{
				unsigned int c = id >> shift;
				if (c == 0)
					break;
				*--p = (char)c;
			}
		}

		void *report = g_heaps.m_allocators[i]->rva000353B0(0, 0x1f, true, 0, 0);
		for (const EA::Allocator::BlockInfo *block = g_heaps.m_allocators[i]->rva00032F60(report, 0x1f); block != 0;
			block = g_heaps.m_allocators[i]->rva00032F60(report, 0x1f))
		{
		}
		g_heaps.m_allocators[i]->rva00033E90(report);
	}
}

void _DumpFragmentation(_iobuf *file, bool header, const char *label)
{
	if (header)
	{
		fprintf(file, "info");
		for (int i = 0; i <= g_heaps.m_count; ++i)
		{
			char name[8];
			char *p = &name[4];
			*p = 0;
			const char *text;
			if (i != 0)
			{
				unsigned int id = g_heaps.m_records[i - 1].m_id;
				for (int shift = 0; shift < 32; shift += 8)
				{
					unsigned int c = id >> shift;
					if (c == 0)
						break;
					*--p = (char)c;
				}
				text = p;
			}
			else
			{
				text = "def";
			}
			fprintf(file, ",%s core,comm,res,blocks,mmap,bytes,slack,free,waste,percent", text);
		}
		fprintf(file, "\n");
	}

	fprintf(file, "%s", label);
	for (int i = 0; i <= g_heaps.m_count; ++i)
	{
		unsigned int committed = 0;
		unsigned int blockBytes = 0;
		unsigned int usedBytes = 0;
		unsigned int blockCount = 0;
		unsigned int mappedCount = 0;
		unsigned int coreCount = 0;
		unsigned int dataBytes = 0;
		unsigned int reserved = 0;
		unsigned int freeCount = 0;
		unsigned int wasted = 0;
		unsigned int lastFree = 0;

		void *report = g_heaps.m_allocators[i]->rva000353B0(0, 0x1f, true, 0, 0);
		for (const EA::Allocator::BlockInfo *block = g_heaps.m_allocators[i]->rva00032F60(report, 0x1f); block != 0;
			block = g_heaps.m_allocators[i]->rva00032F60(report, 0x1f))
		{
			if (block->m_blockType == 2)
			{
				blockBytes += block->m_blockSize;
				dataBytes += block->m_dataSize;
				++blockCount;
				if (block->m_mapped)
					++mappedCount;
				else
					usedBytes += block->m_dataSize;
				lastFree = 0;
			}
			else if (block->m_blockType == 8)
			{
				++coreCount;
				committed += block->m_blockSize;
				reserved += block->m_dataSize;
				lastFree = 0;
			}
			else if (block->m_blockType == 4)
			{
				++freeCount;
				wasted += block->m_blockSize;
				lastFree = block->m_blockSize;
			}
			else
			{
				lastFree = 0;
			}
		}
		if (lastFree != 0)
		{
			--freeCount;
			wasted -= lastFree;
		}

		unsigned int percent = (committed - usedBytes) / (committed / 100);
		fprintf(file, ",%i,%i,%i,%i,%i,%i,%i,%i,%i,%i", coreCount, committed, reserved, blockCount,
			mappedCount, dataBytes, blockBytes - dataBytes, freeCount, wasted, percent);
		g_heaps.m_allocators[i]->rva00033E90(report);
	}
	fprintf(file, "\n");
}

}
