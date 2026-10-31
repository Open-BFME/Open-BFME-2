// cl: /EHsc
// stlport46
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
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);
struct _iobuf;
extern "C" __declspec(dllimport) int __cdecl fprintf(_iobuf *file, const char *format, ...);

class MemoryPoolFactory;
class Rva00031790;
// placement unverified: no rowed DIR32 site yet; ZH initial value is null.
MemoryPoolFactory *TheMemoryPoolFactory = 0;

class Rva006C1F60 { public: void *rva00033ED0(unsigned int size, int flags); };

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
struct Rva00031BF0Chunk {
 unsigned previousSize;
 unsigned size;
 Rva00031BF0Chunk* previous;
 Rva00031BF0Chunk* next;
};
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
	int rva000321F0(int level);				// heap validator 0x329E0 wraps (address-derived name)
	int rva000327E0(const void *blockData, char *dst, unsigned int left);
	// True (block, dst, left) order proven by the WB debug build; the row
	// below owns this name and address.
	int rva00031430(const void *block, char *dst, unsigned int left);
	unsigned int rva000311E0(const void *src, unsigned int count, char *ascii, unsigned short *wide, unsigned int cap);
	unsigned int rva00032A20(const void *block);		// GetUsableSize-like
	int rva00031D00(void *block);				// chunk check error count, callee of 0x32160 (address-derived name)
	int rva00031F90(void *block);				// locked 0x31D00 count plus used-chunk neighbour checks
	int rva00031E60(const void *block);			// free-chunk check error count over 0x31D00 (address-derived name)
	unsigned int rva00032160(void *block);		// locked 0x31D00 count plus fencepost bit and second-list membership test
	unsigned int rva00032050(void *chunk, unsigned int flags);	// locked per-chunk check count (address-derived name)
	unsigned int rva000320E0(void *chunk, unsigned int flags, bool checkPrev, bool skipPrev);	// locked 0x32050 count plus free-chunk bits
	unsigned int rva006C1D10(const void *block);		// fast usable-size with tail call to 0x32A20 caller 0x6C36FD
	void *rva00031B60(const void *block);
	void *rva00031680(const void *block);	// intrusive-list search unblocking 0x31BB0 0x31D00 0x32920
	void rva00031660(void *node);			// intrusive unlink; called with ecx=this by teardown 0x33D50
	bool rva000316B0(void *block, bool release);	// conditional core-release callback / VirtualFree
	int rva00031BF0(const void *block);
	bool rva00031BB0(const void *block);	// small-block fencepost check via 0x31680 caller 0x3324E
	void rva00033150(const void *block);		// Free engine (address-derived name)
	unsigned int rva00032C60(unsigned int pad);	// core trim (Rva00032C60Purge.cpp)
	void *rva000344A0(unsigned int, unsigned int, unsigned int, int);
	void rva000338F0(void *block);				// Free-like
	void rva000338D0(Snapshot *snapshot);			// snapshot release
	void *rva00035080(unsigned int size, int flags);	// Malloc-like
	void *rva00035190(void *block, unsigned int size, int flags);	// Realloc-like
	void *rva00035210(unsigned int count, unsigned int size, int flags);	// Calloc-like
	void *rva000353B0(void *context, int blockTypes, bool copy, void *storage, unsigned int storageSize);	// ReportBegin-like
	void rva00032EC0(const void *block, BlockInfo *out);	// chunk -> BlockInfo for the report
	const BlockInfo *rva00032F60(void *context, int blockTypes);	// ReportNext-like
	void rva00033E90(void *context);			// ReportEnd-like
	// ReportHeap-like walk over blocks of the given types (unrowed 0x00035540).
	bool reportHeap(bool (*callback)(const BlockInfo *info, void *context), void *context, int blockTypes, bool copy, char *storage, unsigned int storageSize);

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
	// 1 when the chunk lies in none of the sentinel regions from s up to end.
	static int ChunkOutsideRegions(Rva00031BF0Chunk *c, ListNode *listNode, ListNode *end)
	{
		while (listNode != end)
		{
			if ((unsigned int)c >= (unsigned int)listNode &&
				(unsigned int)c < (unsigned int)listNode + listNode->m_size)
				return 0;
			listNode = listNode->m_next;
		}
		return 1;
	}
	unsigned int m_unknown0;
	unsigned int m_maxFastSize;
	Rva00031BF0Chunk* m_fastBins[10];
	Rva00031BF0Chunk* m_bins[256];
	// +0x430: one bit per bin, which 0x321F0 checks against each bin's ring.
	unsigned int m_binmap[4];
	// +0x440: the distinguished chunk 0x31BF0 classifies as kind 3 and
	// 0x31D00 checks for self-linked fd/bk (label descriptive).
	void *m_topChunk;
	char m_pad444[4];
	ListNode m_sentinel;
	// Lock wrapper proven by 0x00032A20: Enter/Leave on the pointer at
	// +0x4E4 with a use count at +0x18 of the wrapper.
	struct Lock
	{
		unsigned char m_pad[0x18];
		int volatile m_count;
	};
public:
	// Option fields written by 0x000317F0 (SetOption-like).
	unsigned int m_option468;
	bool m_state46C;
	bool m_option46D;
	unsigned char m_pad46E[0x470 - 0x46E];
	// +0x470: recursion guard 0x31D00 raises around its checks.
	int m_checkDepth;
	unsigned char m_pad474[0x488 - 0x474];
	// +0x488: count 0x321F0 requires to be non-negative and at most +0x490.
	unsigned int m_count488;
	// +0x48C: bytes of those mapped chunks; 0x33150 drops both on release.
	unsigned int m_bytes48C;
	unsigned int m_option490;
	unsigned int m_option494;
	bool m_option498;
	unsigned char m_pad499[0x49C - 0x499];
	struct RegionLink
	{
		unsigned int m_base;
		unsigned int m_size;	// 0x321F0 counts an error when bit 1 is clear
		unsigned char m_pad[4];
		RegionLink *m_next;
	};
	RegionLink m_regions;
	unsigned char m_pad4AC[0x4B4 - (0x49C + sizeof(RegionLink))];
	unsigned int m_option4B4;
	unsigned char m_pad4B8[0x4C8 - 0x4B8];
	unsigned int m_option4C8;
	unsigned int m_option4CC;
	unsigned int m_unknown4D0;	// 0x321F0 requires it non-zero
	unsigned int m_pageSize;
	unsigned int m_coreSize;
	unsigned int m_growSize;
	bool m_option4E0;
	Lock *m_4E4;
	unsigned char m_lockStorage[0x1C];
public:
	void rva000317F0(int option, unsigned int value);
	friend class ::Rva00031790;
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

// ?rva00031B60@GeneralAllocator@Allocator@EA@@QAEPAXPBX@Z @ 0x00031B60 (75B):
// the chunk containing an address. A block whose first dword is zero, or that
// no core region contains (0x00031680), yields null; otherwise the walk starts
// at the region's first chunk and steps by the masked chunk size until the
// next chunk would pass the address. Class proven by the ecx pass-through to
// 0x00031680; the original method name is unknown.
void *GeneralAllocator::rva00031B60(const void *block)
{
	if (*(const unsigned int *)block > 0)
	{
		void **node = (void **)rva00031680(block);
		if (node != 0)
		{
			char *chunk = (char *)*node;
			if ((unsigned int)block > (unsigned int)chunk)
			{
				char *next = chunk + (*(unsigned int *)(chunk + 4) & 0x7FFFFFF8);
				while ((unsigned int)next < (unsigned int)block)
				{
					chunk = next;
					next += *(unsigned int *)(next + 4) & 0x7FFFFFF8;
				}
				return chunk;
			}
		}
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

// ?rva000327E0@GeneralAllocator@Allocator@EA@@QAEHPBXPADI@Z
// Retail locks with this+0x4E4/+0x18 and forwards all three arguments to
// 0x00031430 after subtracting the chunk header. The formatter's proven
// (block, dst, left) ABI therefore also fixes this wrapper's argument types.
// The allocator receiver and lock layout agree with the 0x32A20 sibling.
int GeneralAllocator::rva000327E0(const void *blockData, char *dst, unsigned int left)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	int result = rva00031430((const char *)blockData - 8, dst, left);
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return result;
}

// ?rva00031430@GeneralAllocator@Allocator@EA@@QAEHPBXPADI@Z @0x00031430 320B
// Block-dump formatter: appends "addr/size/data/attr" lines for one heap
// block into the caller's buffer, returning bytes appended. The WB debug
// build of this same body proves the argument order (block, dst, left),
// the hoisted block+8 data local, the zero-filled 256B text buffer passed
// to the pinned 0x000311E0 hex formatter as (src,count,ascii,wide=0,
// cap=0x100) with the "data:" line reading the text from its start, and the
// if/else "mapped"/"internal" selection whose game.dat release shape is the two
// ternaries below. Target facts: block+4 masked 0x7FFFFFF8 minus 8 is the
// size; the same block+4 word carries flag bits 2/4 (attr line); this+0x474
// is the %c separator reloaded for every _snprintf; thresholds
// 0x12/0x1E/0x10A/0x18 gate each line. Declaring data before size keeps
// block in EDX with retail's spill/lea schedule. The 0x000327E0 sibling
// (same TU) forwards block-8 positionally into this same (block, dst, left)
// order and calls this actual owner directly.
int GeneralAllocator::rva00031430(const void *block, char *dst, unsigned int left)
{
	char *start = dst;
	const char *data = (const char *)block + 8;
	unsigned int size = (*(const unsigned int *)((const char *)block + 4) & 0x7FFFFFF8) - 8;
	if (left >= 0x12)
	{
		int n = _snprintf(dst, left, "addr: 0x%08x%c",
			data, *(const unsigned char *)((const char *)this + 0x474));
		dst += n;
		left -= n;
	}
	if (left >= 0x1E)
	{
		int n = _snprintf(dst, left, "size: %10u (%8x)%c", size, size,
			*(const unsigned char *)((const char *)this + 0x474));
		dst += n;
		left -= n;
	}
	if (left >= 0x10A)
	{
		char text[256] = { 0 };
		rva000311E0(data, size, text, 0, 0x100);
		int n = _snprintf(dst, left, "data: %s%c", text,
			*(const unsigned char *)((const char *)this + 0x474));
		dst += n;
		left -= n;
	}
	unsigned int flags = *(const unsigned int *)((const char *)block + 4);
	if ((flags & 4) || (flags & 2))
	{
		if (left >= 0x18)
		{
			const char *mapped = (flags & 2) ? "mapped" : "";
			const char *which = (flags & 4) ? "internal" : "";
			int n = _snprintf(dst, left, "attr: %s %s%c", which, mapped,
				*(const unsigned char *)((const char *)this + 0x474));
			dst += n;
			left -= n;
		}
	}
	return dst - start;
}

// ?rva00032160@GeneralAllocator@Allocator@EA@@QAEIPAX@Z @0x00032160 137B
// Under the +0x4E4 lock: the 0x31D00 result, plus the inverted bit1 of the
// block's second dword, plus one when the block's (address - first dword) key is
// not found among the +0x49C list entries. The equal-arm on the membership
// compare is a scheduling lever (retail keeps the sentinel test in its own branch).
unsigned int GeneralAllocator::rva00032160(void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	unsigned int result = rva00031D00(block);
	result += ((unsigned char)~(((unsigned int *)block)[1] >> 1)) & 1 && 1;
	RegionLink *sentinel = &m_regions;
	RegionLink *cur = m_regions.m_next;
	if (cur != sentinel)
	{
		unsigned int key = (unsigned int)block - *(unsigned int *)block;
		do
		{
			if ((unsigned int)cur - *(unsigned int *)cur == key)
				break;
			cur = cur->m_next;
		} while (cur != sentinel);
	}
	unsigned int total = result + ((block ? (cur == sentinel) : (cur == sentinel)));
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return total;
}

// ?rva00031F90@GeneralAllocator@Allocator@EA@@QAEHPAX@Z @0x00031F90 179B
// Under the +0x4E4 lock: the 0x31D00 count, plus one when the following
// chunk's in-use bit is clear, plus one when the previous chunk's size does
// not reach this one, plus the top-chunk bit/size checks.
int GeneralAllocator::rva00031F90(void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	int result = rva00031D00(block);
	unsigned int *header = (unsigned int *)block;
	if (!(header[1] & 2))
	{
		result += ((unsigned char)~*((unsigned char *)block + (header[1] & 0x7FFFFFF8) + 4)) & 1 && 1;
		char *next = (char *)block + (header[1] & 0x7FFFFFF8);
		if (!(header[1] & 1))
		{
			char *prev = (char *)block - header[0];
			result += prev + (((unsigned int *)prev)[1] & 0x7FFFFFF8) != (char *)block;
		}
		if (next == *(char **)((char *)this + 0x440))
		{
			unsigned char topByte = *(volatile unsigned char *)(next + 4);
			result += ((unsigned char)~topByte) & 1 && 1;

			unsigned int *pTopWord = (unsigned int *)(next + 4);
			unsigned int topWord = *pTopWord;
			unsigned int topSize = topWord & 0x7FFFFFF8;
			result += (topSize < 0x10) && 1;
		}
	}
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return result;
}

// ?rva000320E0@GeneralAllocator@Allocator@EA@@QAEIPAXI_N1@Z @0x000320E0 128B
// Under the +0x4E4 lock: the 0x32050 count for the chunk, plus one when the
// following chunk's in-use bit is clear (this chunk is free), plus one more
// when the third argument is set, the fourth clear and the chunk's own
// prev-in-use bit is clear. Argument labels are descriptive only.
unsigned int GeneralAllocator::rva000320E0(void *chunk, unsigned int flags, bool checkPrev, bool skipPrev)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	unsigned int *header = (unsigned int *)chunk;
	unsigned int isFree = ((unsigned char)~*((unsigned char *)chunk + (header[1] & 0x7FFFFFF8) + 4)) & 1 && 1;
	unsigned int result = rva00032050(chunk, flags) + isFree;
	if (checkPrev && !skipPrev)
		result += ((unsigned char)~*((unsigned char *)chunk + 4)) & 1 && 1;
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

// ?rva00032EC0@GeneralAllocator@Allocator@EA@@QAEXPBXPAUBlockInfo@23@@Z
// @0x00032EC0 151B, RET8. Fills one heap-report BlockInfo from a chunk; the
// report iterator 0x00032F60 calls it with the chunk and its output slot.
// Header at chunk+4: bit1 marks a mapped chunk, the masked size locates the
// next chunk, whose header bit0 says this one is in use. An in-use chunk
// reports type 2 with its payload (chunk+8) and usable size (0x32A20; a
// mapped one also widens the core by the prefix at chunk+0); a free chunk
// reports type 4 with payload chunk+0x10. Offsets and flags are target
// evidence; the method's original name is unknown.
void GeneralAllocator::rva00032EC0(const void *block, BlockInfo *out)
{
	const char *chunk = (const char *)block;
	unsigned int size = *(const unsigned int *)(chunk + 4);
	unsigned int mapped = size & 2;
	size &= 0x7FFFFFF8;
	if ((*(const unsigned char *)(chunk + size + 4) & 1) != 0)
	{
		void *data = (void *)(chunk + 8);
		unsigned int usable = rva00032A20(data);
		out->m_blockType = 2;
		if (mapped != 0)
		{
			out->m_core = (void *)(chunk - *(const unsigned int *)chunk);
			out->m_blockSize = *(const unsigned int *)chunk + size + 0x10;
			out->m_data = data;
			out->m_dataSize = usable;
			out->m_mapped = true;
		}
		else
		{
			out->m_data = data;
			out->m_blockSize = size;
			out->m_core = (void *)chunk;
			out->m_dataSize = usable;
			out->m_mapped = false;
		}
	}
	else
	{
		out->m_core = (void *)chunk;
		out->m_blockSize = size;
		out->m_blockType = 4;
		out->m_data = (void *)(chunk + 0x10);
		out->m_dataSize = (*(const unsigned int *)(chunk + 4) & 0x7FFFFFF8) - 0x10;
		out->m_mapped = false;
	}
}

// ?rva00032F60@GeneralAllocator@Allocator@EA@@QAEPBUBlockInfo@23@PAXH@Z @0x00032F60 490B
// Report-next (PPMalloc ReportNext-like) over a 'SNAP' report context. Live
// mode (+0x0E set) masks the types with +0x08, walks the core list (current
// core +0x10, current chunk +0x14, sentinel this+0x448, cores linked through
// +0x1C, chunk end core+size-0x10), skipping internal chunks (header bit 2)
// unless type 0x10 is asked and matching in-use (2) or free (4) chunks; a
// hit fills the report's BlockInfo at +0x24 through 0x00032EC0. With the
// walk done and type 2 asked it reports the mapped list (+0x18, sentinel
// this+0x49C, next +0x0C). Copy mode scans the stored 20-byte BlockInfo
// array at +0x24 from index +0x20 below count +0x1C by type. Target bytes
// supply every offset and branch; field labels are descriptive.
static inline int rva00032F60ChunkInUse(const char *chunk)
{
	unsigned int size = *(const unsigned int *)(chunk + 4);
	return (*(const unsigned char *)(chunk + (size & 0x7FFFFFF8) + 4) & 1) && !(size & 0x80000000);
}

const BlockInfo *GeneralAllocator::rva00032F60(void *context, int blockTypes)
{
	Snapshot *snapshot = (Snapshot *)context;
	if (snapshot && snapshot->m_magic == 0x534E4150)
	{
		if (snapshot->m_state[2])
		{
			blockTypes &= (int)snapshot->m_arg2;
			while ((ListNode *)snapshot->m_values[0] != &m_sentinel)
			{
				ListNode *const core = (ListNode *)snapshot->m_values[0];
				const char *chunkEnd = 0;
				if (((ListNode *)snapshot->m_values[0])->m_size)
				{
					chunkEnd = (const char *)core + core->m_size - 0x10;
					if (snapshot->m_values[1])
						snapshot->m_values[1] += *(const unsigned int *)(snapshot->m_values[1] + 4) & 0x7FFFFFF8;
					else
						snapshot->m_values[1] = core->m_unk0;
					while ((const char *)snapshot->m_values[1] != chunkEnd)
					{
						const char *chunk = (const char *)snapshot->m_values[1];
						if ((blockTypes & 0x10) || (*(const unsigned char *)(chunk + 4) & 4) == 0)
						{
							if ((blockTypes & 6) == 6)
								break;
							const int inUse = rva00032F60ChunkInUse(chunk);
							int match;
							if (blockTypes & 2)
								match = inUse;
							else if (blockTypes & 4)
								match = !inUse;
							else
								match = false;
							if (match)
								break;
						}
						snapshot->m_values[1] = (unsigned int)chunk + (*(const unsigned int *)(chunk + 4) & 0x7FFFFFF8);
					}
					if ((const char *)snapshot->m_values[1] != chunkEnd)
						break;
				}
				if (!core->m_size || (const char *)snapshot->m_values[1] == chunkEnd)
				{
					do
						snapshot->m_values[0] = (unsigned int)((ListNode *)snapshot->m_values[0])->m_prev;
					while ((ListNode *)snapshot->m_values[0] != &m_sentinel && !((ListNode *)snapshot->m_values[0])->m_size);
					snapshot->m_values[1] = 0;
				}
			}
			if ((ListNode *)snapshot->m_values[0] != &m_sentinel)
			{
				BlockInfo *const info = (BlockInfo *)(snapshot + 1);
				rva00032EC0((const void *)snapshot->m_values[1], info);
				return info;
			}
			if ((blockTypes & 2) && (RegionLink *)snapshot->m_values[2] != &m_regions)
			{
				RegionLink *const region = (RegionLink *)snapshot->m_values[2];
				BlockInfo *const info = (BlockInfo *)(snapshot + 1);
				rva00032EC0((const char *)region - region->m_base, info);
				snapshot->m_values[2] = (unsigned int)((RegionLink *)snapshot->m_values[2])->m_next;
				return info;
			}
		}
		else
		{
			BlockInfo *const info = (BlockInfo *)(snapshot + 1);
			if (snapshot->m_values[4] < snapshot->m_values[3])
			{
				bool found = false;
				while (snapshot->m_values[4] < snapshot->m_values[3])
				{
					if (info[snapshot->m_values[4]].m_blockType & blockTypes)
					{
						found = true;
						break;
					}
					++snapshot->m_values[4];
				}
			}
			if (snapshot->m_values[4] < snapshot->m_values[3])
				return &info[snapshot->m_values[4]++];
		}
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

// ?rva00033150@GeneralAllocator@Allocator@EA@@QAEXPBX@Z @0x00033150 374B, RET4.
// The free engine (dlmalloc fREe shape with EA extensions); other units reach
// it through the Rva00033E90::freeBlock pin. Small chunks are pushed on a fast
// bin. Others coalesce with a free predecessor and successor (boundary tags),
// then go on the unsorted list (+0x30) or become the top chunk (+0x440); a
// chunk of 64 KB or more that ends a core (0x31BB0) and reaches the trim
// threshold (option 7, +0x4C8) trims through 0x32C60 with the top pad
// (option 8, +0x4CC). Mapped chunks (size bit 1) unlink their trailing fence
// node from the mapped list, drop the mapped count and bytes (+0x488/+0x48C)
// and release the whole mapping. Name and labels are descriptive.
// The __assume states the accounting invariant the mapped arm relies on; it
// generates no code, and without it cl folds the mapping size into the byte
// subtraction (m_bytes48C + (-16 - prevSize - size)) instead of computing it
// with lea ahead of the unlink as retail does. About 60 spellings without it
// (helpers, references, temporaries, statement orders) all stay at 375 B.
void GeneralAllocator::rva00033150(const void *block)
{
	typedef Rva00031BF0Chunk Chunk;
	if (block == 0)
		return;
	Chunk *chunk = (Chunk *)((char *)block - 8);
	unsigned int header = chunk->size;
	unsigned int size = header & 0x7FFFFFF8;
	if (size <= m_maxFastSize)
	{
		m_maxFastSize |= 1;
		Chunk **bin = &m_fastBins[(size >> 3) - 2];
		chunk->next = *bin;
		chunk->size |= 0x80000004;
		*bin = chunk;
		return;
	}
	if ((header & 2) == 0)
	{
		Chunk *next = (Chunk *)((char *)chunk + size);
		unsigned int nextSize = next->size & 0x7FFFFFF8;
		if ((header & 1) == 0)
		{
			unsigned int prevSize = chunk->previousSize;
			chunk = (Chunk *)((char *)chunk - prevSize);
			size += prevSize;
			chunk->size = size | 1;
			next->previousSize = size;
			chunk->previous->next = chunk->next;
			chunk->next->previous = chunk->previous;
		}
		if ((*(unsigned int *)((char *)next + nextSize + 4) & 1) != 0)
		{
			next->size &= ~1u;
			next->previousSize = size;
		}
		else
		{
			next->previous->next = next->next;
			next->next->previous = next->previous;
			size += nextSize;
			chunk->size = size | 1;
			*(unsigned int *)((char *)chunk + size) = size;
		}
		if (chunk != m_topChunk && next != m_topChunk)
		{
			Chunk *unsorted = (Chunk *)((char *)this + 0x30);
			Chunk *first = unsorted->next;
			chunk->previous = unsorted;
			chunk->next = first;
			unsorted->next = chunk;
			first->previous = chunk;
		}
		else
		{
			m_topChunk = chunk;
			chunk->next = chunk;
			chunk->previous = chunk;
			chunk->size = size | 1;
			*(unsigned int *)((char *)chunk + size) = size;
		}
		if (size >= 0x10000)
		{
			if (rva00031BB0((char *)chunk + size) && size >= m_option4C8)
				rva00032C60(m_option4CC);
		}
	}
	else
	{
		Chunk *fence = (Chunk *)((char *)chunk + size);
		unsigned int prevSize = chunk->previousSize;
		void *mapping = (char *)chunk - prevSize;
		unsigned int mappingSize = prevSize + size + 0x10;
		fence->previous->next = fence->next;
		fence->next->previous = fence->previous;
		__assume(m_bytes48C >= mappingSize);
		m_bytes48C -= mappingSize;
		--m_count488;
		VirtualFree(mapping, 0, 0x8000);
	}
}

// ?rva000338D0@GeneralAllocator@Allocator@EA@@QAEXPAUSnapshot@123@@Z @0x000338D0 31B
// Releases a snapshot block: only when its magic is 'SNAP' (the value the
// Snapshot constructor stores at +0) and the first state byte at +0xC is
// clear does it tail-call the free engine 0x00033150 with the
// same this. Reached through the thunk at 0x006C1D50. Name address-derived.
void GeneralAllocator::rva000338D0(Snapshot *snapshot)
{
	if (snapshot->m_magic == 0x534E4150 && snapshot->m_state[0] == 0)
		rva00033150(snapshot);
}

// ?rva000338F0@GeneralAllocator@Allocator@EA@@QAEXPAX@Z @0x000338F0 63B
// Free-like: lock at +0x4E4 with count at +0x18 around the free engine 0x00033150.
// Evidence: caller _Free 0x000305D6 plus 3 unclaimed; Enter/LeaveCriticalSection IAT; inc/dec at +0x18.
__declspec(noinline) void GeneralAllocator::rva000338F0(void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	rva00033150(block);
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
}

// Native 0x000344A0..0x00034797, 759 bytes, RET16. The matched
// 0x00035100 wrapper independently proves the receiver and four arguments.
// Existing 0x00030F10, 0x00033ED0 and 0x00033150 bindings establish the
// size-bin, allocation and free relationships; no new symbol pin is used.
// The original method name is unknown; retain the caller's address name.
// Aligned allocation (size, alignment, offset, flags), dlmalloc's mEMALIGn
// with EA extensions: alignment of at most 8 with no offset is a plain
// allocation (malloc engine 0x00033ED0); otherwise the alignment is raised
// to 16 and rounded up to a power of two, the offset to a multiple of 8.
// Flags bit 2 first looks for an exact-size free chunk whose mem + offset is
// already aligned, in the unsorted list (+0x30) and then in the size's bin.
// Else it over-allocates, gives the misaligned leader back to the free path
// (0x00033150, with +0x478 held at zero) and splits off a trailing remainder
// that coalesces into a free successor or the top chunk (+0x440). Mmapped
// chunks (head bit 1) only shift their prev-size. Evidence: retail body, the
// wrapper 0x00035100 and the sibling malloc/realloc/calloc entries; the name
// is address-derived. GetLargeBinIndexFromChunkSize must be defined earlier
// in this unit: retail keeps the offset in EDX across that call.
// This value describes the two cursors used by one free-list scan. It is
// an implementation value, not a claim about an original EA source type.
struct ChunkScanRange
{
    Rva00031BF0Chunk *end;
    Rva00031BF0Chunk *first;
};

static __forceinline ChunkScanRange MakeChunkScanRange(Rva00031BF0Chunk *p)
{
    ChunkScanRange range = { p, p->next };
    return range;
}

static inline Rva00031BF0Chunk *Rva000344A0Unsorted(void *self)
{
	return (Rva00031BF0Chunk *)((char *)self + 0x30);
}

static inline Rva00031BF0Chunk *Rva000344A0Bin(void *self, unsigned int idx)
{
	return ((Rva00031BF0Chunk **)((char *)self + 0x30))[idx];
}

static inline void *Rva000344A0Take(Rva00031BF0Chunk *p, unsigned int nb)
{
	*(unsigned int *)((char *)p + nb + 4) |= 1;
	void *mem = (char *)p + 8;
	p->previous->next = p->next;
	p->next->previous = p->previous;
	return mem;
}

void *GeneralAllocator::rva000344A0(unsigned int size, unsigned int alignment, unsigned int offset, int flags)
{
	typedef Rva00031BF0Chunk Chunk;
	if (alignment <= 8 && offset == 0)
		return ((::Rva006C1F60 *)this)->rva00033ED0(size, flags);
	if (alignment < 16)
		alignment = 16;
	unsigned int mask = alignment - 1;
	if (alignment & mask)
	{
		mask |= mask >> 1;
		mask |= mask >> 2;
		mask |= mask >> 4;
		mask |= mask >> 8;
		mask |= mask >> 16;
		alignment = mask + 1;
	}
	if (offset & 7)
		offset = (offset + 7) & ~7u;
	unsigned int nb = size + 11;
	nb = nb > 16 ? nb & ~7u : 16;

	if (flags & 4)
	{
		ChunkScanRange range = MakeChunkScanRange(Rva000344A0Unsorted(this));
		Chunk *bin = range.end;
		Chunk *chunk;
		for (chunk = range.first; chunk != bin; chunk = chunk->next)
		{
			if ((chunk->size & 0x7ffffff8) == nb && (alignment == 0 || (((unsigned int)chunk + offset + 8) & (alignment - 1)) == 0))
				return Rva000344A0Take(chunk, nb);
		}
		unsigned int idx = nb < 0x200 ? nb >> 3 : GetLargeBinIndexFromChunkSize(nb);
		range = MakeChunkScanRange(Rva000344A0Bin(this, idx));
		bin = range.end;
		for (chunk = range.first; chunk != bin; chunk = chunk->next)
		{
			if ((chunk->size & 0x7ffffff8) == nb && (alignment == 0 || (((unsigned int)chunk + offset + 8) & (alignment - 1)) == 0))
				return Rva000344A0Take(chunk, nb);
		}
	}

	void *mem = ((::Rva006C1F60 *)this)->rva00033ED0(nb + alignment + offset + 16, flags);
	if (mem != 0)
	{
		Chunk *chunk = (Chunk *)((char *)mem - 8);
		if (((unsigned int)mem + offset) % alignment != 0)
		{
			Chunk *newp = (Chunk *)((((unsigned int)mem + alignment + offset - 1) & -alignment) - offset - 8);
			if ((unsigned int)((char *)newp - (char *)chunk) < 16)
				newp = (Chunk *)((char *)newp + alignment);
			unsigned int leadSize = (char *)newp - (char *)chunk;
			unsigned int newSize = (chunk->size & 0x7ffffff8) - leadSize;
			if (chunk->size & 2)
			{
				newp->previousSize = chunk->previousSize + leadSize;
				newp->size = newSize | 2;
				return (char *)newp + 8;
			}
			newp->size = newSize | 1;
			*(unsigned int *)((char *)newp + newSize + 4) |= 1;
			*(unsigned int *)((char *)newp + newSize) = newSize;
			chunk->size = (chunk->size & 0x80000007) | leadSize;
			newp->previousSize = leadSize;
			int saved = *(int *)((char *)this + 0x478);
			*(int *)((char *)this + 0x478) = 0;
			rva00033150((char *)chunk + 8);
			*(int *)((char *)this + 0x478) = saved;
			chunk = newp;
		}

		unsigned int chunkSize = chunk->size;
		if (!(chunkSize & 2))
		{
			chunkSize &= 0x7ffffff8;
			if (chunkSize > nb + 16)
			{
				unsigned int remSize = chunkSize - nb;
				Chunk *rem = (Chunk *)((char *)chunk + nb);
				rem->size = remSize | 1;
				chunk->size = (chunk->size & 0x80000007) | nb;
				Chunk *next = (Chunk *)((char *)rem + remSize);
				unsigned int nextSize = next->size & 0x7ffffff8;
				if (((Chunk *)((char *)next + nextSize))->size & 1)
				{
					int saved = *(int *)((char *)this + 0x478);
					*(int *)((char *)this + 0x478) = 0;
					rva00033150((char *)rem + 8);
					*(int *)((char *)this + 0x478) = saved;
					return (char *)chunk + 8;
				}
				next->previous->next = next->next;
				next->next->previous = next->previous;
				remSize += nextSize;
				rem->size = remSize | 1;
				*(unsigned int *)((char *)rem + remSize) = remSize;
				Chunk *&top = *(Chunk **)((char *)this + 0x440);
				if (rem == top || next == top)
				{
					top = rem;
					rem->next = rem;
					rem->previous = rem;
					rem->size = remSize | 1;
					*(unsigned int *)((char *)rem + remSize) = remSize;
				}
				else
				{
					Chunk *bck = (Chunk *)m_bins;
					Chunk *fwd = bck->next;
					rem->previous = bck;
					rem->next = fwd;
					bck->next = rem;
					fwd->previous = rem;
				}
			}
		}
		return (char *)chunk + 8;
	}
	return 0;
}


}
}

// ?rva00031660@GeneralAllocator@Allocator@EA@@QAEXPAX@Z @ 0x00031660 (25B):
// intrusive doubly-linked unlink with next at +0x18 and prev at +0x1C.
// Caller 0x00033E05 in 0x00033D50 loads ecx with the allocator before the
// call (byte-matched /Od teardown), so this is a GeneralAllocator member that
// ignores `this`; RET4 with one stack argument. Direct double-load shape
// proves the two one-line stores rather than hoisted temps.
void EA::Allocator::GeneralAllocator::rva00031660(void *node)
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

// 0x00030900 (16B): heap-report callback adding a block's data size to the
// running total its context points at; always continues the walk.
bool rva00030900(const EA::Allocator::BlockInfo *info, void *context)
{
	*(unsigned int *)context += info->m_dataSize;
	return true;
}

// 0x00030910 (90B), unreferenced: the data bytes of every allocated block
// (type 2) across all heaps, summed by walking each allocator's report with
// the callback above and a 512-byte scratch buffer.
unsigned int rva00030910()
{
	unsigned int total = 0;
	char storage[0x200];
	for (int i = 0; i <= g_heaps.m_count; ++i)
		g_heaps.m_allocators[i]->reportHeap(rva00030900, &total, 2, false, storage, sizeof(storage));
	return total;
}

// 0x00030970 (8B), unreferenced: raise the shut-down flag _Free tests.
void rva00030970()
{
	g_heaps.m_shutDown = true;
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
			if (i != 0)
			{
				for (int shift = 0; shift < 32 && (g_heaps.m_records[i - 1].m_id >> shift) != 0; shift += 8)
					*--p = (char)(g_heaps.m_records[i - 1].m_id >> shift);
			}
			else
			{
				p = "def";
			}
			fprintf(file, ",%s core,comm,res,blocks,mmap,bytes,slack,free,waste,percent", p);
		}
		fprintf(file, "\n");
	}

	fprintf(file, "%s", label);
	for (int i = 0; i <= g_heaps.m_count; ++i)
	{
		unsigned int blockBytes = 0;
		unsigned int dataBytes = 0;
		unsigned int usedBytes = 0;
		unsigned int blockCount = 0;
		unsigned int mappedCount = 0;
		unsigned int coreCount = 0;
		unsigned int committed = 0;
		unsigned int reserved = 0;
		unsigned int freeCount = 0;
		unsigned int wasted = 0;
		unsigned int lastFree = 0;

		void *report = g_heaps.m_allocators[i]->rva000353B0(0, 0x1f, true, 0, 0);
		for (;;)
		{
			const EA::Allocator::BlockInfo *block = g_heaps.m_allocators[i]->rva00032F60(report, 0x1f);
			if (block == 0)
				break;
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

		fprintf(file, ",%i,%i,%i,%i,%i,%i,%i,%i,%i,%i", coreCount, committed, reserved, blockCount,
			mappedCount, dataBytes, blockBytes - dataBytes, freeCount, wasted,
			(committed - usedBytes) / (committed / 100));
		g_heaps.m_allocators[i]->rva00033E90(report);
	}
	fprintf(file, "\n");
}

}

// ??0Rva00031790@@QAE@PAX@Z @ 0x00031790 (35B): scoped counted lock.
// The constructor stores the lock at +0 and, when non-null, enters it as a
// critical section and bumps the use count at +0x18, returning this. It is
// a constructor by target evidence: 0x000317F0 calls it on a stack object and
// sets the EH state live right after the call, and its unwind funclet destroys
// that object through 0x000317C0 (the inline destructor below; 21 B, exact).
// Class name unknown (address-derived); PPMalloc's scoped mutex shape.
class Rva00031790
{
public:
	void *m_0000;
	Rva00031790(void *param);
	~Rva00031790()
	{
		EA::Allocator::GeneralAllocator::Lock *lock = (EA::Allocator::GeneralAllocator::Lock *)m_0000;
		if (lock != 0)
		{
			--lock->m_count;
			LeaveCriticalSection(lock);
		}
	}
};

Rva00031790::Rva00031790(void *param)
{
	m_0000 = param;
	if (param != 0)
	{
		EnterCriticalSection(param);
		++((EA::Allocator::GeneralAllocator::Lock *)param)->m_count;
	}
}

// Native 0x00030D10..0x00030D4E, RET4: retain bit0 of word +4;
// zero clears its size bits, otherwise clamp to 80, add 11, round down
// to a multiple of 8, and impose a minimum of 16. Unsigned comparisons
// and the receiver/one-word ABI are target facts; class/name remain unknown.
class Rva00030D10 {
public: void rva00030D10(unsigned int size);
private: unsigned int unknown00, sizeAndFlag;
};
// ?nonzero30D10 absent-from-retail - source-only inline calculation
inline unsigned int nonzero30D10(unsigned int size) {
 if(size>80) size=80;
 size+=11;
 if(size>16) return size & ~7u;
 return 16;
}
void Rva00030D10::rva00030D10(unsigned int size) {
 unsigned flag=sizeAndFlag&1;
 if(size) sizeAndFlag=nonzero30D10(size)|flag;
 else sizeAndFlag=flag;
}


// Lock provider rows of Rva00030DD0AddRef.cpp (create, lock, unlock).
struct Rva00030DD0Lock;
Rva00030DD0Lock *Rva00030D90Init(Rva00030DD0Lock *storage);
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);
class Rva00034C90 { public: void consolidate(); };	// pinned callee 0x00033930
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *section);

inline unsigned int rva000317F0Align(unsigned int size, unsigned int alignment)
{
	return (size + alignment - 1) & ~(alignment - 1);
}

namespace EA
{
namespace Allocator
{
// ?rva000317F0@GeneralAllocator@Allocator@EA@@QAEXHI@Z @ 0x000317F0 (872B
// with its 13-entry jump table).
void GeneralAllocator::rva000317F0(int option, unsigned int value)
{
	switch (option)
	{
	case 1:
		if (value)
		{
			if (!m_4E4)
				m_4E4 = (Lock *)Rva00030D90Init((Rva00030DD0Lock *)m_lockStorage);
		}
		else if (m_4E4)
		{
			Rva00030DD0AddRef((Rva00030DD0Lock *)m_4E4);
			Lock *lock = m_4E4;
			m_4E4 = 0;
			Rva00030DF0Release((Rva00030DD0Lock *)lock);
			DeleteCriticalSection(lock);
		}
		break;
	case 2:
	{
		Rva00031790 guard(m_4E4);
		if (value)
		{
			if (!m_state46C && !m_option468)
				m_option468 = 1;
		}
		else
			m_option468 = 0;
		break;
	}
	case 3:
		m_option46D = value != 0;
		break;
	case 4:
		if (!value)
			m_coreSize = 0x1000000;
		else
		{
			m_coreSize = rva000317F0Align(value > m_pageSize ? value : m_pageSize, m_pageSize);
		}
		break;
	case 5:
		if (!value)
			m_growSize = 0x400000;
		else
		{
			m_growSize = value > m_pageSize ? value : m_pageSize;
			m_growSize = rva000317F0Align(m_growSize, m_pageSize);
			if (m_growSize > m_coreSize)
				m_growSize = m_coreSize;
		}
		break;
	case 6:
	{
		Rva00031790 guard(m_4E4);
		((Rva00034C90 *)this)->consolidate();
		((Rva00030D10 *)this)->rva00030D10(value);
		break;
	}
	case 7: m_option4C8 = value; break;
	case 8: m_option4CC = value; break;
	case 9: m_option494 = value; break;
	case 10: m_option490 = value; break;
	case 11: m_option498 = value != 0; break;
	case 12: m_option4E0 = value != 0; break;
	case 13: m_option4B4 = value; break;
	}
}
}
}



// Native 31BF0..31CF4 including the final RET4, 260B (inventory stops
// before that return). The allocator's fast and circular-bin searches
// classify its chunk pointer as 1, 2, or the +440 distinguished chunk as 3.
// Provider identity follows the adjacent rowed GeneralAllocator methods;
// the API name and chunk-kind enum labels remain unresolved.
namespace EA
{
namespace Allocator
{
int GeneralAllocator::rva00031BF0(const void* block) {
 typedef Rva00031BF0Chunk Chunk;
 const Chunk* chunk=(const Chunk*)block;
 if(chunk==*(Chunk**)((char*)this+0x440)) return 3;
 unsigned size=chunk->size&0x7ffffff8;
 
 if(size>=0x10 && size<=m_maxFastSize) {
  for(Chunk* p=m_fastBins[(size>>3)-2];p;p=p->next)
   if(p==chunk) return 1;
 }
 
 unsigned index;
 if((unsigned)chunk>=(unsigned)m_bins && (unsigned)chunk<(unsigned)this+0x430)
  index=(((const char*)chunk-(const char*)this-0x30)>>4)+2;
 else if(size<0x200) index=size>>3;
 else index=GetLargeBinIndexFromChunkSize(size);
 Chunk* head=m_bins[index];
 for(Chunk* p=head->next;p!=head;p=p->next)
  if(p==chunk) return 2;
 for(int i=0;i<10;++i)
  for(Chunk* p=m_fastBins[i];p;p=p->next)
   if(p==chunk) return 1;
 for(int i=2;i<256;i+=2) {
  Chunk* head=m_bins[i];
  for(Chunk* p=head->next;p!=head;p=p->next)
   if(p==chunk) return 2;
 }
 return 0;
}

// ?rva00031D00@GeneralAllocator@Allocator@EA@@QAEHPAX@Z @0x00031D00 351B
// Native 31D00..31E5F RET4. Under the +0x4E4 lock, and only while the +0x470
// recursion guard is at most one, counts failed consistency checks of the
// chunk at the argument: size range; for a mapped chunk (size bit 2) region
// membership via 0x31680 and +0x4D4-unit alignment of both ends plus 8-byte
// alignment; otherwise containment in the 0x31680 region, plus self-linked
// list words, minimum size and a clear in-use bit for the +0x440 chunk, or
// the region-start and fencepost bounds when the region list holds one entry.
// Each check is spelled (cond) && 1: that keeps retail's one-add-per-check
// order (a plain (cond) term lets the optimizer pair the adds), and the
// in-use bit is re-read as a byte as retail does. Check meanings follow the
// dlmalloc-family chunk checks; only offsets and operations are target facts.
int GeneralAllocator::rva00031D00(void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	int errors = 0;
	int depth = m_checkDepth;
	if (depth <= 1)
	{
		++depth;
		m_checkDepth = depth;
		const unsigned int *header = (const unsigned int *)block;
		unsigned int size = header[1] & 0x7FFFFFF8;
		errors += (size >= 0x40000000) && 1;
		if ((header[1] & 2) != 0)
		{
			errors += (rva00031680(block) != 0) && 1;
			errors += ((((unsigned int)block - header[0]) & (m_pageSize - 1)) != 0) && 1;
			errors += ((((unsigned int)block + size + 0x10) & (m_pageSize - 1)) != 0) && 1;
			errors += (((unsigned char)(unsigned int)block & 7) != 0) && 1;
		}
		else
		{
			ListNode *region = (ListNode *)rva00031680(block);
			errors += (region == 0) && 1;
			errors += ((unsigned int)block < region->m_unk0) && 1;
			unsigned int regionEnd = region->m_unk0 + region->m_size;
			errors += ((unsigned int)block >= regionEnd) && 1;
			unsigned int blockEnd = (unsigned int)block + size;
			errors += (blockEnd >= regionEnd) && 1;
			if (block == m_topChunk)
			{
				errors += (header[2] != (unsigned int)block || header[3] != (unsigned int)block) && 1;
				errors += (size < 0x10) && 1;
				errors += (((unsigned char)~*(const unsigned char *)(header + 1)) & 1) && 1;
			}
			else if (m_sentinel.m_prev == m_sentinel.m_next)
			{
				errors += ((unsigned int)block < region->m_unk0) && 1;
				errors += ((unsigned int)region + region->m_size - 0x10 < blockEnd) && 1;
			}
		}
		m_checkDepth = depth - 1;
	}
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return errors;
}

// ?rva00031E60@GeneralAllocator@Allocator@EA@@QAEHPBX@Z @0x00031E60 301B
// Native 31E60..31F8D RET4. Under the +0x4E4 lock, the 0x31D00 count for the
// chunk plus one per failed free-chunk consistency check: clear in-use bit
// (next chunk's prev-in-use), clear bit 1; for sizes of at least 0x10 the size
// and address alignment, footer equal to the size, set prev-in-use, the
// chunk being the +0x440 chunk or its successor in use, and self-consistent
// fd/bk links (with the single-entry and +0x440 cases); a smaller chunk must
// be at most 4. Each check is counted through CheckCount, which keeps
// retail's per-check 0/1 adds and the zero-then-one block order of the
// two-term successor check. Check meanings follow the dlmalloc-family free
// chunk check; only offsets and operations are target facts.
static inline int CheckCount(bool ok)
{
	if (ok)
		return 0;
	return 1;
}

// ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z @0x00032050 140B
// Locked chunk checks. The final count survives lock teardown separately
// from the intermediate sum; the last check uses the requested size argument.
unsigned int GeneralAllocator::rva00032050(void *block, unsigned int requested)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	unsigned int size = ((const unsigned int *)block)[1] & 0x7FFFFFF8;
	int result = rva00031F90(block);
	result += CheckCount(((unsigned char)size & 7) == 0);
	result += CheckCount(size >= 0x10);
	result += CheckCount(((unsigned char)(unsigned int)block & 7) == 0);
	result += CheckCount(size >= 8);
	unsigned int total = result + CheckCount(size < requested + 0x10);

	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return total;
}

int GeneralAllocator::rva00031E60(const void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	unsigned int size = ((const unsigned int *)block)[1] & 0x7FFFFFF8;
	unsigned int blockEnd = (unsigned int)block + size;
	int errors = rva00031D00((void *)block);
	unsigned int header = ((const unsigned int *)block)[1];
	errors += CheckCount(!(*(const unsigned char *)((header & 0x7FFFFFF8) + (unsigned int)block + 4) & 1));
	errors += CheckCount(!((unsigned char)(header >> 1) & 1));
	if (size >= 0x10)
	{
		errors += CheckCount(((unsigned char)size & 7) == 0);
		errors += CheckCount(((unsigned char)(unsigned int)block & 7) == 0);
		errors += CheckCount(*(const unsigned int *)blockEnd == size);
		errors += CheckCount((*(const unsigned char *)((const char *)block + 4) & 1) != 0);
		errors += CheckCount(block == m_topChunk || (*(const unsigned char *)((*(const unsigned int *)(blockEnd + 4) & 0x7FFFFFF8) + blockEnd + 4) & 1));
		const unsigned int *next = *(const unsigned int **)((const char *)block + 8);
		const unsigned int *previous = *(const unsigned int **)((const char *)block + 0xC);
		errors += CheckCount(previous[2] == (unsigned int)block);
		errors += CheckCount(next[3] == (unsigned int)block);
		if (block == previous || block == next)
		{
			errors += CheckCount(next == previous);
			errors += CheckCount(block == m_topChunk);
		}
	}
	else
		errors += CheckCount(size <= 4);
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return errors;
}

// One bin's ring: its first node and the bin header the ring must contain.
struct Rva000321F0BinRing
{
	Rva00031BF0Chunk *first;
	Rva00031BF0Chunk *head;
};

// Native 321F0..327C7 RET4, the heap validator behind 0x329E0: failed checks per level under the +0x4E4
// lock. Check meanings follow dlmalloc's state check; only offsets and operations are target facts.
int GeneralAllocator::rva000321F0(int level)
{
	int errors = 0;
	int index;
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	if (level >= 1)
	{
		unsigned int totalFast = 0;
		if (m_topChunk == 0 || m_topChunk == (void *)m_bins)
		{
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return 0;
		}
		unsigned int maxFast = m_maxFastSize;
		errors += CheckCount(maxFast < 0x50);
		if (level >= 2)
		{
			// Fast-bin chains: each node must live inside a sentinel region and
			// carry the expected size flags.
			for (index = 0; index < 10; ++index)
			{
				Rva00031BF0Chunk *c = m_fastBins[index];
				int guard = 0;
				while (c != 0)
				{
					if (guard >= 0x1e8480)
						break;
					errors += ChunkOutsideRegions(c, m_sentinel.m_next, &m_sentinel);
					unsigned int size = c->size;
					c = c->next;
					errors += CheckCount(((int)size & (int)0x80000000) != 0);
					errors += CheckCount((size & 4) != 0);
					++guard;
					errors += CheckCount(guard < 0x1e8480);
				}
			}

			Rva00031BF0Chunk **link;
			for (index = 0, link = m_bins; index < 0x100; index += 2, link += 2)
			{
				Rva00031BF0Chunk *c = *link;
				if (index < 2)
					errors += CheckCount(c == 0);
				else
				{
					Rva000321F0BinRing ring = { c, (Rva00031BF0Chunk *)((char *)link - 8) };
					errors += CheckCount(ring.first != 0);
					Rva00031BF0Chunk *p = ring.first->next;
					int count = 0;
					if (p == ring.head)
						count = 1;
					while (p != ring.first)
					{
						if (p == ring.head)
							++count;
						else
						{
							errors += ChunkOutsideRegions(p, m_sentinel.m_next, &m_sentinel);
						}
						p = p->next;
					}
					errors += CheckCount(count != 0);
				}
			}

			errors += CheckCount(m_option4CC < 0x186a0);
			errors += CheckCount(m_unknown4D0 != 0);
			errors += CheckCount((m_pageSize & (m_pageSize - 1)) == 0);
			maxFast &= ~1u;
			int maxFastIndex = (maxFast >> 3) - 2;
			errors += CheckCount(maxFast <= 0x58);
			for (index = 0; index < 10; ++index)
			{
				Rva00031BF0Chunk *c = m_fastBins[index];
				if (index > maxFastIndex)
					errors += CheckCount(c == 0);
				while (c != 0)
				{
					unsigned int size = c->size;
					c = c->next;
					totalFast += size & 0x7ffffff8u;
					errors += CheckCount(((size >> 3) & 0x0fffffffu) - 2 == (unsigned int)index);
				}
			}
			if (totalFast != 0)
				errors += CheckCount((m_maxFastSize & 1) != 0);

			// Bin heads and the binmap must agree, and every bin list node
			// must be a valid chunk of its bin's size class.
			for (index = 1; index < 0x80; ++index)
			{
				Rva00031BF0Chunk *head = (Rva00031BF0Chunk *)((char *)&m_bins[index << 1] - 8);
				if (index >= 2)
				{
					bool binbit = (m_binmap[index >> 5] & (1u << (index & 0x1f))) != 0;
					bool nonEmpty = head != head->previous;
					if (!binbit)
						errors += CheckCount(!nonEmpty);
					else if (nonEmpty)
						errors += CheckCount(binbit);
				}
				Rva00031BF0Chunk *c = head->previous;
				while (c != head)
				{
					errors += rva00031E60(c);
					unsigned int size = c->size & 0x7ffffff8u;
					if (index >= 2)
					{
						unsigned int idx;
						if (size < 0x200)
							idx = size >> 3;
						else if ((size >> 6) <= 0x20)
							idx = (size >> 6) + 0x38;
						else if ((size >> 9) <= 0x14)
							idx = (size >> 9) + 0x5b;
						else if ((size >> 12) <= 0x0a)
							idx = (size >> 12) + 0x6e;
						else if ((size >> 15) <= 4)
							idx = (size >> 15) + 0x77;
						else if ((size >> 18) <= 2)
							idx = (size >> 18) + 0x7c;
						else
							idx = 0x7e;
						errors += CheckCount(idx == (unsigned int)index);
						if (size >= 0x200)
						{
							Rva00031BF0Chunk *next = c->previous;
							errors += CheckCount(next == head || (next->size & 0x7ffffff8u) >= size);
						}
					}

					// Walk the chunk run behind every bin node.
					Rva00031BF0Chunk *run = (Rva00031BF0Chunk *)((char *)c + size);
					for (;;)
					{
						unsigned int runSize = run->size & 0x7ffffff8u;
						if (runSize < 0x10)
						{
							ListNode *listNode = m_sentinel.m_next;
							for (; listNode != &m_sentinel; listNode = listNode->m_next)
							{
								if ((unsigned int)run >= (unsigned int)listNode &&
									(unsigned int)run < (unsigned int)listNode + listNode->m_size)
								{
									if ((unsigned int)run >= (unsigned int)listNode + listNode->m_size - 0x10)
										goto runDone;
									break;
								}
							}
						}
						if ((*(unsigned char *)((char *)run + runSize + 4) & 1) == 0 || runSize < 0x10)
							break;
						errors += rva00031F90(run);
						run = (Rva00031BF0Chunk *)((char *)run + (run->size & 0x7ffffff8u));
					}
runDone:
					c = c->previous;
				}
			}

			// Sentinel region counters.
			RegionLink *regionLink = m_regions.m_next;
			RegionLink *rend = &m_regions;
			while (regionLink != rend)
			{
				errors += CheckCount((regionLink->m_size & 2) != 0);
				unsigned int base = regionLink->m_base;
				Rva00031BF0Chunk *prev = (Rva00031BF0Chunk *)((char *)regionLink - base);
				regionLink = regionLink->m_next;
				errors += CheckCount((prev->size & 2) != 0);
			}
		}
		errors += rva00031D00(m_topChunk);
		errors += CheckCount((int)m_count488 >= 0);
		errors += CheckCount((int)m_count488 <= (int)m_option490);
	}

	if (level >= 3)
	{
		// Region link list: each link must report a valid owner.
		RegionLink *regionLink = m_regions.m_next;
		RegionLink *rend = &m_regions;
		while (regionLink != rend)
		{
			void *owner = (char *)regionLink - regionLink->m_base;
			errors += rva00032160(owner);
			regionLink = regionLink->m_next;
		}

		// Full sentinel walk: every chunk run must be valid and end at the top.
		ListNode *listNode = m_sentinel.m_prev;
		ListNode *end = &m_sentinel;
		while (listNode != end)
		{
			unsigned int size = listNode->m_size;
			Rva00031BF0Chunk *c = (Rva00031BF0Chunk *)listNode->m_unk0;
			unsigned int endAddr = (unsigned int)listNode + size - 0x10;
			while ((unsigned int)c < endAddr)
			{
				unsigned int csize = c->size & 0x7ffffff8u;
				int inUse = (*(unsigned int *)((char *)c + csize + 4) & 1);
				if (inUse)
					errors += rva00031F90(c);
				else
					errors += rva00031E60(c);
				if (!inUse && c == c->next)
				{
					errors += CheckCount(c == m_topChunk);
					break;
				}
				c = (Rva00031BF0Chunk *)((char *)c + (c->size & 0x7ffffff8u));
			}
			listNode = listNode->m_prev;
		}
	}

	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return errors;
}
}
}

// Export-named native _AddHeap at 000306B0..00030730. The table fields
// are shared with the existing heap operations above; the +40D flag is
// set while _Init accepts registrations. A compiler fence preserves retail
// scheduling when linking the new record into its hash bucket.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
namespace MemoryPool {
extern unsigned int g_defaultHeapSize;
void _AddHeap(unsigned int id, unsigned int size)
{
	if (!g_heaps.m_addingHeaps)
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
	HeapRecord *record = &g_heaps.m_records[count];
	record->m_size = size;
	HeapRecord *head = *bucket;
	++count;
	record->m_id = id;
	g_heaps.m_count = count;
	_ReadWriteBarrier();
	record->m_next = head;
	*bucket = record;
}
}

// Retail 0x006C1BE0 (219 B, __stdcall ret 0x14), beside the allocator's
// 0x006C1AA0 and GeneralAllocator 0x006C1D10: formats a source location into
// a bounded buffer. It writes the file's base name (after the last '\\' or
// '/'), then ", " and the line through sprintf("%d"), then, when a function
// name is given, ", " and the name, copied up to the buffer end without a NUL
// test as retail does; returns the characters written. Name address-derived.
extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);

unsigned int __stdcall Rva006C1BE0FormatLocation(char *buffer, unsigned int size, const char *file, int line, const char *function)
{
	char *p = buffer;
	char *end = buffer + size - 1;
	*buffer = 0;
	if (file)
	{
		const char *name = file + strlen(file);
		while (name >= file && *name != '\\' && *name != '/')
			--name;
		++name;
		while (p < end && *name)
			*p++ = *name++;
		if (p + 2 < end)
		{
			*p++ = ',';
			*p++ = ' ';
		}
		char number[32];
		sprintf(number, "%d", line);
		for (const char *n = number; p < end && *n; )
			*p++ = *n++;
	}
	if (function)
	{
		if (file && p + 2 < end)
		{
			*p++ = ',';
			*p++ = ' ';
		}
		while (p < end)
			*p++ = *function++;
	}
	*p = 0;
	return p - buffer;
}

// Release game code calls MemoryPool::GetHeapAllocatorByIndex through a
// stub that only returns no allocator (W3DDisplay::gatherDebugStats at
// +0x5B5/+0x5E4); retail folds it into the shared zero-return body.
namespace MemoryPool {
EA::Allocator::GeneralAllocator *Rva0065CE90(unsigned int index)
{
	return 0;
}
}
