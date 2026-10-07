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
//   0x00DE0798  allocator by index; [0] is the default heap (one unread
//               dword sits between it and the buckets)
//   0x00DB35A0  default heap size (_AddHeap with id 0)
//   0x00DB35A4  TLS slot holding the calling thread's current heap id
//   0x00DE0821  set only while _Init runs; _AddHeap is ignored otherwise
// The contiguous addresses are modelled as one object, HeapTable at
// 0x00DE0414: _AddHeap (banked, not yet exact) only reloads its bucket head
// after the record stores when the records and buckets share one object.
// The variable names are descriptive; retail's are not recoverable.

#include <string.h>

// Native [0x00030E20,0x00030E88): cdecl byte predicate used by allocator
// guard checks. The existing address-derived callee spelling is retained;
// retail reads the buffer and never writes a fill. Aligned spans compare
// four repeated bytes at a time, then compare the remaining bytes.
unsigned char rva00030E20Fill(void *memory, unsigned int size, unsigned char value)
{
	unsigned char *p = (unsigned char *)memory;
	unsigned char *end = p + size;
	unsigned char *wordEnd = p + (size / 4) * 4;
	if (size >= 4 && ((unsigned int)p & 3) == 0)
	{
		unsigned int pattern = value;
		pattern = (pattern << 8) | value;
		pattern = (pattern << 8) | value;
		pattern = (pattern << 8) | value;
		while (p < wordEnd)
		{
			unsigned int word = *(unsigned int *)p;
			p += 4;
			if (word != pattern)
				return 0;
		}
	}
	while (p < end)
	{
		unsigned char byte = *p++;
		if (byte != value)
			return 0;
	}
	return 1;
}

extern "C" __declspec(dllimport) void *__stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);
extern "C" __declspec(dllimport) int __stdcall VirtualFree(void *address, unsigned int size, unsigned int type);

class MemoryPoolFactory;
// placement unverified: no rowed DIR32 site yet; ZH initial value is null.
MemoryPoolFactory *TheMemoryPoolFactory = 0;

class Rva00033E90
{
public:
	void freeBlock(void *p);
};

namespace EA
{
namespace Allocator
{
// One entry of a PPMalloc heap report (layout as _DumpFragmentation reads it).
struct BlockInfo
{
	void *m_core;
	unsigned int m_blockSize;
	void *m_data;
	unsigned int m_dataSize;
	char m_blockType;	// 2 allocated, 4 free, 8 core
	bool m_mapped;
};

// PPMalloc's allocator. Most methods remain address-named; a few now have
// donor PDB names backed by exact target bodies and boundaries.
class GeneralAllocator
{
public:
	struct Snapshot
	{
		// The type name is donor-derived. Target evidence establishes these
		// offsets and writes; field labels below are descriptive only.
		unsigned int m_magic;
		unsigned int m_size;
		void *m_arg2;
		unsigned char m_state[4];
		unsigned int m_values[5];

		Snapshot(unsigned int size, void *context);
	};

	// Godfather PPMalloc 1.03.01 PDB name; retail stores the two arguments
	// at +0x4B8 and +0x4BC. Their callback contract remains donor-derived.
	void SetAssertionFailureFunction(void *function, void *context);
	// Donor PDB name; target caller at 0x32D7F and the chunk-header stores
	// support the fencepost role. The precise chunk type remains unknown.
	static void AddDoubleFencepost(void *chunk, unsigned int flags);
	// Donor PDB name; target allocator call sites and the size-bin thresholds
	// support its role. Its parameter meaning is carried from the donor.
	static unsigned int GetLargeBinIndexFromChunkSize(unsigned int size);
	bool rva00032830(const void *block, int addressType);	// ValidateAddress-like
	bool rva00032920(const void *block);			// owns-address test
	bool rva000329E0(int level);				// ValidateHeap-like
	int rva000327E0(const void *blockData, unsigned int left, char *dst);
	int rva00031430(const void *block, unsigned int left, char *dst);
	unsigned int rva00032A20(const void *block);		// GetUsableSize-like
	unsigned int rva006C1D10(const void *block);		// fast usable-size with tail call to 0x32A20 caller 0x6C36FD
	void *rva00031680(const void *block);	// intrusive-list search unblocking 0x31BB0 0x31D00 0x32920
	bool rva000316B0(void *block, bool release);	// conditional core-release callback / VirtualFree
	bool rva00031BB0(const void *block);	// small-block fencepost check via 0x31680 caller 0x3324E
	void rva000338F0(void *block);				// Free-like
	void *rva00035080(unsigned int size, int flags);	// Malloc-like
	void *rva00035190(void *block, unsigned int size, int flags);	// Realloc-like
	void *rva00035210(unsigned int count, unsigned int size, int flags);	// Calloc-like
	void *rva000353B0(void *context, int blockTypes, bool copy, void *storage, unsigned int storageSize);	// ReportBegin-like
	const BlockInfo *rva00032F60(void *context, int blockTypes);	// ReportNext-like
	void rva00033E90(void *context);			// ReportEnd-like

private:
	// Intrusive list node proven by 0x00031680 (size at +4 next at +0x18)
	// and 0x00031660 (next at +0x18 prev at +0x1C); sentinel embedded
	// at +0x448 with its next at +0x460 (0x448+0x18) and prev at +0x464.
	// Labels are descriptive; only offsets are target facts.
	struct ListNode
	{
		unsigned int m_unk0;
		unsigned int m_size;
		// 0x316B0 independently consumes these fields. Names describe their
		// observed use; the original field names and flag meanings are unknown.
		unsigned int m_releaseSize;
		unsigned char m_unknownC;
		bool m_releaseDirect;
		bool m_releaseAllowed;
		unsigned char m_unknownF;
		void (__cdecl *m_releaseCallback)(GeneralAllocator *, void *, unsigned int, void *);
		void *m_releaseContext;
		ListNode *m_next;
		ListNode *m_prev;
	};
	unsigned char m_pad0[0x448];
	ListNode m_sentinel;
	// Lock wrapper proven by 0x00032A20: Enter/Leave on the pointer at
	// +0x4E4 with a use count at +0x18 of the wrapper.
	struct Lock
	{
		unsigned char m_pad[0x18];
		int volatile m_count;
	};
	unsigned char m_pad468[0x4E4 - (0x448 + sizeof(ListNode))];
	Lock *m_4E4;
};

GeneralAllocator::Snapshot::Snapshot(unsigned int size, void *context)
{
	memset(this, 0, size);
	m_size = size;
	m_arg2 = context;
	m_state[0] = 0;
	m_state[1] = 0;
	m_state[2] = 0;
	m_values[0] = 0;
	m_values[1] = 0;
	m_values[2] = 0;
	m_values[3] = 0;
	m_values[4] = 0;
	m_magic = 0x534E4150;
}

void GeneralAllocator::SetAssertionFailureFunction(void *function, void *context)
{
	char *const fields = reinterpret_cast<char *>(this) + 0x4B8;
	*reinterpret_cast<void **>(fields) = function;
	*reinterpret_cast<void **>(fields + 4) = context;
}

void GeneralAllocator::AddDoubleFencepost(void *chunk, unsigned int flags)
{
	unsigned int *const header = static_cast<unsigned int *>(chunk);
	unsigned int size = header[1];
	unsigned int fencepostOffset = (size & 0x7FFFFFF8) - 9;
	fencepostOffset &= 0xFFFFFFF8;
	header[1] = (size & 0x80000007) | fencepostOffset;
	unsigned int *const fencepost = reinterpret_cast<unsigned int *>(
		reinterpret_cast<char *>(chunk) + fencepostOffset);
	fencepost[0] = fencepostOffset;
	fencepost[1] = flags | 8;
	fencepost[2] = 8;
	fencepost[3] = 9;
}

unsigned int GeneralAllocator::GetLargeBinIndexFromChunkSize(unsigned int size)
{
	unsigned int index = size >> 6;
	if (index <= 0x20)
		return index + 0x38;

	index = size >> 9;
	if (index <= 0x14)
		return index + 0x5B;

	index = size >> 12;
	if (index <= 0x0A)
		return index + 0x6E;

	index = size >> 15;
	if (index <= 4)
		return index + 0x77;

	index = size >> 18;
	if (index <= 2)
		return index + 0x7C;

	return 0x7E;
}

// Native [0x316B0,0x31701), RET8. GeneralAllocator's teardown calls it at
// 0x33E13 with the same receiver and a node unlinked by 0x31660. This proves
// the node ABI independently of the descriptive release-field labels.
// Success means that a release was attempted; VirtualFree's result is ignored.
bool GeneralAllocator::rva000316B0(void *block, bool release)
{
	ListNode *core = (ListNode *)block;
	bool result = false;
	if (core->m_releaseDirect || (release && core->m_releaseAllowed))
	{
		if (core->m_releaseCallback)
			core->m_releaseCallback(this, block, core->m_releaseSize, core->m_releaseContext);
		else
			VirtualFree(block, core->m_releaseSize, 0x8000);
		result = true;
	}
	return result;
}

// ?rva00031680@GeneralAllocator@Allocator@EA@@QAEPAXPBX@Z @ 0x00031680 (47B):
// intrusive circular-list search returning the node containing the address or
// null. Class proven by callers 0x00031BB0 0x00031D00 0x00032920 passing the
// same GeneralAllocator this through; head at +0x460 is sentinel.next
// (+0x448+0x18); node size at +4 and next at +0x18.
void *GeneralAllocator::rva00031680(const void *block)
{
	ListNode *cur = m_sentinel.m_next;
	ListNode *sentinel = &m_sentinel;
	while (cur != sentinel)
	{
		if ((unsigned int)block >= (unsigned int)cur)
		{
			unsigned int end = (unsigned int)cur + cur->m_size;
			if ((unsigned int)block < end)
				return cur;
		}
		cur = cur->m_next;
	}
	return 0;
}

// ?rva00031BB0@GeneralAllocator@Allocator@EA@@QAE_NPBX@Z @ 0x00031BB0 (51B):
// small-block check calling 0x00031680 then requiring the address to lie in
// the last 0x10 bytes of the containing node. Class proven by this
// pass-through (ecx preserved for the 0x31680 call) and caller 0x0003324E
// passing GeneralAllocator this; bool return from al 1/0 shape.
bool GeneralAllocator::rva00031BB0(const void *block)
{
	unsigned int size = *(const unsigned int *)((const char *)block + 4) & 0x7FFFFFF8;
	if (size < 0x10)
	{
		void *node = rva00031680(block);
		if (node != 0)
		{
			unsigned int nodeSize = *(unsigned int *)((char *)node + 4);
			const void *limit = (const char *)node + nodeSize - 0x10;
			if ((unsigned int)block >= (unsigned int)limit)
				return true;
		}
	}
	return false;
}

// ?rva000327E0@GeneralAllocator@Allocator@EA@@QAEHPBXIPAD@Z
// Target evidence: retail locks with this+0x4E4/+0x18 around the call to
// 0x00031430, passing blockData-8, left, and dst. The same allocator this and
// lock layout are established by the matched 0x32A20 sibling; the helper's
// address-derived role as the block formatter is supported by 0x353F0.
int GeneralAllocator::rva000327E0(const void *blockData, unsigned int left, char *dst)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	int result = rva00031430((const char *)blockData - 8, left, dst);
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return result;
}

// ?rva00032A20@GeneralAllocator@Allocator@EA@@QAEIPBX@Z @0x00032A20 146B
// GetUsableSize-like: lock at +0x4E4 with count at +0x18, header at block-4
// masked with 0x7FFFFFF8, bit1 set returns size-8, else bit0 at
// [masked+block-4] gates size-4, else 0. Caller _GetBlockSize at 0x0003061D.
unsigned int GeneralAllocator::rva00032A20(const void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	if (block != 0)
	{
		unsigned int header = *(const unsigned int *)((const char *)block - 4);
		unsigned int size = header & 0x7FFFFFF8;
		if ((header & 2) != 0)
		{
			unsigned int usable = size - 8;
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return usable;
		}
		unsigned int header2 = *(const volatile unsigned int *)((const char *)block - 4);
		unsigned int masked = header2 & 0x7FFFFFF8;
		if ((*(const unsigned char *)(void *)(masked + (unsigned int)block - 4) & 1) != 0)
		{
			unsigned int usable = size - 4;
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return usable;
		}
	}
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return 0;
}

// ?rva006C1D10@GeneralAllocator@Allocator@EA@@QAEIPBX@Z @0x006C1D10 59B
// Fast usable-size: header at block-4, sign check tail-calls 0x32A20,
// bit1 selects masked size else masked+4, then short at [size+block-0xA]
// bounds-checks against block, returning the offset or tail-calling 0x32A20.
// Caller at 0x006C36FD. Same GeneralAllocator this as 0x32A20 (ecx pass-through).
unsigned int GeneralAllocator::rva006C1D10(const void *block)
{
	unsigned int header = *(const unsigned int *)((const char *)block - 4);
	if ((header & 0x80000000) != 0)
		return rva00032A20(block);
	unsigned int size;
	if ((header & 2) == 0)
		size = (header & 0x7FFFFFF8) + 4;
	else
		size = header & 0x7FFFFFF8;
	const unsigned short *field = (const unsigned short *)(size + (unsigned int)block - 0xA);
	unsigned int base = (unsigned int)field - *field;
	if (base >= (unsigned int)block)
		return base - (unsigned int)block;
	return rva00032A20(block);
}

// ?rva000338F0@GeneralAllocator@Allocator@EA@@QAEXPAX@Z @0x000338F0 63B
// Free-like: lock at +0x4E4 with count at +0x18 around Rva00033E90::freeBlock pin 0x00033150.
// Evidence: caller _Free 0x000305D6 plus 3 unclaimed; Enter/LeaveCriticalSection IAT; inc/dec at +0x18.
__declspec(noinline) void GeneralAllocator::rva000338F0(void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	((::Rva00033E90 *)this)->freeBlock(block);
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
}

}
}

// ?Rva00031660Unlink@@YGXPAX@Z @ 0x00031660 (25B):
// intrusive doubly-linked unlink with next at +0x18 and prev at +0x1C.
// Caller 0x00033E05 in 0x00033D50; direct double-load shape proves the two
// one-line stores rather than hoisted temps.
void __stdcall Rva00031660Unlink(void *node)
{
	*(void **)((char *)*(void **)((char *)node + 0x18) + 0x1C) = *(void **)((char *)node + 0x1C);
	*(void **)((char *)*(void **)((char *)node + 0x1C) + 0x18) = *(void **)((char *)node + 0x18);
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
	unsigned int m_unknown380;	// 0x00DE0794: nothing here reads it
	EA::Allocator::GeneralAllocator *m_allocators[MAX_HEAPS + 1];
	EA::Allocator::GeneralAllocator *m_defaultAllocator;
	bool m_clearAllocations;
	int m_initCount;
	bool m_shutDown;
	bool m_addingHeaps;
};

extern HeapTable g_heaps;
HeapTable g_heaps;
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

}

// ?rva00031790@Rva00031790@@QAEPAXPAX@Z @ 0x00031790 (35B):
// lock-holder setter: stores param at +0 then when non-null enters it as a
// critical section and bumps the use count at +0x18 returning this.
// Class unproven by callers (both call sites unclaimed) so honest
// address-derived owner; EnterCriticalSection via dllimport like neighbours.
class Rva00031790
{
public:
	void *m_0000;
	void *rva00031790(void *param);
};

void *Rva00031790::rva00031790(void *param)
{
	m_0000 = param;
	if (param != 0)
	{
		EnterCriticalSection(param);
		int count = *(volatile int *)((char *)param + 0x18);
		*(volatile int *)((char *)param + 0x18) = count + 1;
	}
	return this;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_heapTlsIndex@MemoryPool@@3KA=?g_Va00DB35A4@@3KA")
