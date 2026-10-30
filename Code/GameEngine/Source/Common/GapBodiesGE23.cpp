// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// platformsdk
// Small heap-allocator bodies from .text gaps no Ghidra function covers
// (twenty-third batch; see GapBodiesGE01.cpp), all inside the run of
// memory_pool.cpp's EA::Allocator::GeneralAllocator rows (0x00030D10..
// 0x00031BF0). Each begins after its neighbour's padding and ends in its own
// ret. Retail bytes establish every shape: chunks carry a previous-size word
// and a size word whose low three bits and top bit are flags (mask
// 0x7FFFFFF8), free chunks a forward (+8) and back (+0x0C) link; core blocks
// form a ring through +0x18/+0x1C around a sentinel at heap +0x448. The
// heap's own member names are not recovered, so each body keeps an
// address-derived name and the view below holds only the members they touch.

#include <windows.h>

struct GapChunk
{
	unsigned int m_prevSize;
	unsigned int m_size;
	GapChunk *m_fd;											// +0x08
	GapChunk *m_bk;											// +0x0C
};

struct GapCore
{
	char *m_base;
	unsigned int m_size;									// +0x04
	char m_pad08[0x18 - 0x08];
	GapCore *m_prev;										// +0x18
	GapCore *m_next;										// +0x1C
};

#define GAP_CHUNK_AT(p, offset) ((GapChunk *)((char *)(p) + (offset)))
#define GAP_CHUNK_SIZE(p) ((p)->m_size & 0x7FFFFFF8)

// --- 0x000309D0 (12B): is x eight-byte aligned (the low three bits clear).
int rva000309D0(unsigned int alignmentValue)
{
	return (alignmentValue & 7) == 0;
}

// --- 0x000309E0 (17B): is x a multiple of the power-of-two a.
bool IsAligned(unsigned int alignmentCandidate, unsigned int alignment)
{
	return (alignmentCandidate & (alignment - 1)) == 0;
}

// --- 0x00030A00 (18B): round x up to the power-of-two a.
unsigned int AlignUp(unsigned int unalignedValue, unsigned int requiredAlignment)
{
	return (unalignedValue + requiredAlignment - 1) & ~(requiredAlignment - 1);
}

// --- 0x00030B00 (21B): in-use bit of a chunk, kept in the next chunk's size.
int rva00030B00(GapChunk *chunk)
{
	return GAP_CHUNK_AT(chunk, GAP_CHUNK_SIZE(chunk))->m_size & 1;
}

// --- 0x00030B20 (21B): set it.
void SetChunkInUse(GapChunk *chunk)
{
	GAP_CHUNK_AT(chunk, GAP_CHUNK_SIZE(chunk))->m_size |= 1;
}

// --- 0x00030B40 (16B) / 0x00030B50 (14B): the same bit of the chunk at an
// explicit offset.
int rva00030B40(GapChunk *chunk, unsigned int offset)
{
	return GAP_CHUNK_AT(chunk, offset)->m_size & 1;
}

void rva00030B50(GapChunk *chunk, unsigned int offset)
{
	GAP_CHUNK_AT(chunk, offset)->m_size |= 1;
}

// --- 0x00030B60 (14B): clear that bit of the chunk at an explicit offset.
void rva00030B60(GapChunk *chunk, unsigned int offset)
{
	GAP_CHUNK_AT(chunk, offset)->m_size &= ~1u;
}

// --- 0x00030B70 (23B): store a size keeping the flag bits.
void SetChunkSize(GapChunk *chunk, unsigned int size)
{
	chunk->m_size = (chunk->m_size & 0x80000007) | size;
}

// --- 0x00030B90 (12B): write a chunk's size as the previous-size word of
// the chunk that follows it.
void setChunkFooter(GapChunk *chunk, unsigned int size)
{
	GAP_CHUNK_AT(chunk, size)->m_prevSize = size;
}

// --- 0x00030BA0 (25B): link a chunk between fd and bk.
void LinkChunk(GapChunk *chunk, GapChunk *fd, GapChunk *bk)
{
	chunk->m_fd = fd;
	chunk->m_bk = bk;
	fd->m_bk = chunk;
	bk->m_fd = chunk;
}

// --- 0x00030BC0 (23B): unlink a chunk.
void UnlinkChunk(GapChunk *chunk)
{
	chunk->m_fd->m_bk = chunk->m_bk;
	chunk->m_bk->m_fd = chunk->m_fd;
}

// --- 0x000310F0 (36B): two fencepost chunks (8 then 9) after n bytes.
void rva000310F0(GapChunk *chunk, unsigned int chunkSize)
{
	GapChunk *post = GAP_CHUNK_AT(chunk, chunkSize);
	post->m_prevSize = chunkSize;
	post->m_size = 8;
	post = GAP_CHUNK_AT(post, 8);
	post->m_prevSize = 8;
	post->m_size = 9;
}

// --- 0x00031160 (70B): shrink a core's top chunk to the flagged size less
// nine, rounded down to eight, and close it with the 8/8/9 fencepost words.
GapChunk *rva00031160(GapChunk *chunk, unsigned int size, unsigned int flags)
{
	unsigned int value = size | flags;
	unsigned int n = ((value & 0x7FFFFFF8) - 9) & ~7u;
	chunk->m_size = (value & 0x80000007) | n;
	chunk->m_prevSize = 0;
	GapChunk *post = GAP_CHUNK_AT(chunk, n);
	post->m_prevSize = n;
	post->m_size = 8;
	*(unsigned int *)&post->m_fd = 8;
	*(unsigned int *)&post->m_bk = 9;
	return chunk;
}

struct GapBlockInfo
{
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
};

struct GapBlockReport
{
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned char m_type;									// +0x10
	unsigned char m_flag;									// +0x11
};

class Rva00030C50Heap
{
public:
	void rva00030C50(int bin);
	unsigned int rva00030C80(int bin);
	void rva00030CC0(bool on);
	bool rva00030CE0() const;
	void SetMallocFailureFunction(int mallocFailureFunction, int mallocFailureContext);
	void SetTraceFunction(int traceFunction, int traceContext);
	void rva00030ED0(unsigned char fieldDelimiter, unsigned char recordDelimiter);
	void initializeFreeChunk(GapChunk *chunk, unsigned int size);
	void rva000311B0(const GapBlockInfo *info, GapBlockReport *report);
	void rva00031400(int value);
	bool rva000315C0(const char *checkedAddress) const;
	void rva00031610(int a, unsigned int b);
	void insertCoreBefore(GapCore *core, GapCore *before);
	void *rva00031710(unsigned int size, unsigned int *outSize);
	int rva00031750(void *coreAddress, unsigned int size);
	GapChunk *rva00030BF0(int bin);
	bool rva00031080(void *a, void *b, void *c);
	GapChunk *rva00030F60();
private:
	int m_00;
	unsigned int m_04;
	char m_pad08[0x30 - 0x08];
	GapChunk *m_bins[256];									// +0x30
	unsigned int m_binBits[4];								// +0x430
	GapChunk *m_top;										// +0x440
	unsigned int m_444;
	GapCore m_cores;										// +0x448
	char *m_468;
	char m_pad46C[0x474 - 0x46C];
	unsigned char m_fieldDelimiter;
	unsigned char m_recordDelimiter;
	char m_pad476[0x478 - 0x476];
	int m_478;
	unsigned int m_47C;
	int m_480;
	char m_pad484[0x498 - 0x484];
	bool m_topDown;											// +0x498
	char m_pad499[0x4AC - 0x499];
	int m_mallocFailureFunction;
	int m_mallocFailureContext;
	char m_pad4B4[0x4B8 - 0x4B4];
	void (__cdecl *m_callback)(int value, int context);	// +0x4B8
	int m_callbackContext;									// +0x4BC
	int m_traceFunction;
	int m_traceContext;
};

// --- 0x00030C50 (33B): set a bin bitmap bit.
void Rva00030C50Heap::rva00030C50(int bin)
{
	Rva00030C50Heap *self = this;
	int word = bin >> 5;
	self->m_binBits[word] |= 1 << (bin & 31);
}

// --- 0x00030C80 (35B): test a bin bitmap bit.
unsigned int Rva00030C50Heap::rva00030C80(int bin)
{
	return (1 << (bin & 31)) & m_binBits[bin >> 5];
}

// --- 0x00030CC0 (29B): bit 0 of the +4 word.
void Rva00030C50Heap::rva00030CC0(bool on)
{
	if (on)
		m_04 |= 1;
	else
		m_04 &= ~1u;
}

// --- 0x00030CE0 (18B): the core ring's two links agree.
bool Rva00030C50Heap::rva00030CE0() const
{
	return m_cores.m_next == m_cores.m_prev;
}

// --- 0x00030E90 / 0x00030EB0 / 0x00030ED0 (23B each): pair setters.
void Rva00030C50Heap::SetMallocFailureFunction(int mallocFailureFunction, int mallocFailureContext)
{
	m_mallocFailureFunction = mallocFailureFunction;
	m_mallocFailureContext = mallocFailureContext;
}

void Rva00030C50Heap::SetTraceFunction(int traceFunction, int traceContext)
{
	m_traceFunction = traceFunction;
	m_traceContext = traceContext;
}

void Rva00030C50Heap::rva00030ED0(unsigned char fieldDelimiter, unsigned char recordDelimiter)
{
	m_fieldDelimiter = fieldDelimiter;
	m_recordDelimiter = recordDelimiter;
}

// --- 0x00031060 (28B): a free chunk of size n linked to itself, with the
// prev-in-use bit and the trailing size word.
void Rva00030C50Heap::initializeFreeChunk(GapChunk *chunk, unsigned int size)
{
	chunk->m_bk = chunk;
	chunk->m_fd = chunk;
	chunk->m_size = size | 1;
	GAP_CHUNK_AT(chunk, size)->m_prevSize = size;
}

// --- 0x000311B0 (35B): fill a block report of type 8.
void Rva00030C50Heap::rva000311B0(const GapBlockInfo *info, GapBlockReport *report)
{
	report->m_type = 8;
	report->m_00 = info->m_00;
	report->m_04 = info->m_04;
	report->m_0C = info->m_08;
	report->m_flag = 0;
}

// --- 0x00031400 (30B): forward a value to the optional callback.
void Rva00030C50Heap::rva00031400(int value)
{
	if (m_callback)
		m_callback(value, m_callbackContext);
}

// --- 0x000315C0 (69B): find the core holding p; true when p lies past the
// +0x468 mark.
bool Rva00030C50Heap::rva000315C0(const char *checkedAddress) const
{
	for (const GapCore *core = m_cores.m_next; core != &m_cores; core = core->m_next)
		if (checkedAddress >= core->m_base && checkedAddress < core->m_base + core->m_size)
			return m_468 < checkedAddress;
	return false;
}

// --- 0x00031610 (42B): a value and a count of at least one; clear +0x480.
void Rva00030C50Heap::rva00031610(int a, unsigned int b)
{
	if (b <= 0)
		b = 1;
	m_47C = b;
	m_478 = a;
	m_480 = 0;
}

// --- 0x00031640 (29B): insert a core ahead of another in the ring.
void Rva00030C50Heap::insertCoreBefore(GapCore *core, GapCore *before)
{
	core->m_next = before;
	core->m_prev = before->m_prev;
	before->m_prev = core;
	core->m_prev->m_next = core;
}

// --- 0x00031710 (55B): commit a core with VirtualAlloc (top-down when +0x498
// is set) and report its size.
void *Rva00030C50Heap::rva00031710(unsigned int size, unsigned int *outSize)
{
	unsigned long type = 0x3000;
	if (m_topDown)
		type = 0x103000;
	void *coreMemory = VirtualAlloc(0, size, type, 4);
	if (coreMemory && outSize)
		*outSize = size;
	return coreMemory;
}

// --- 0x00031750 (21B): release a core.
int Rva00030C50Heap::rva00031750(void *coreAddress, unsigned int size)
{
	return VirtualFree(coreAddress, 0, 0x8000);
}

// --- 0x00030A30 (22B): a request's chunk size: the request plus eleven
// bytes of overhead rounded down to eight, never below the 16-byte minimum.
unsigned int rva00030A30(unsigned int size)
{
	unsigned int chunk = size + 0xB;
	if (chunk > 0x10)
		return chunk & ~7u;
	return 0x10;
}

// --- 0x00030A50 (15B): a request plus 0x1F bytes of overhead, rounded up to
// whole 4 KB pages.
unsigned int rva00030A50(unsigned int size)
{
	return (size + 0x1F + 0xFFF) & ~0xFFFu;
}

// --- 0x00030A60 (11B): fast-bin index of a chunk size (sixteen bytes is 0).
unsigned int getFastBinIndexFromChunkSize(unsigned int size)
{
	return (size >> 3) - 2;
}

// --- 0x00030A70 / 0x00030A80 / 0x00030A90 (11B each): the three low flag
// bits of a chunk's own size word.
int rva00030A70(GapChunk *chunk)
{
	return chunk->m_size & 1;
}

int rva00030A80(GapChunk *chunk)
{
	return chunk->m_size & 2;
}

int rva00030A90(GapChunk *chunk)
{
	return chunk->m_size & 4;
}

// --- 0x00030AA0 (9B): set flag bit 2.
void rva00030AA0(GapChunk *chunk)
{
	chunk->m_size |= 4;
}

// --- 0x00030AB0 (13B): the top flag bit.
unsigned int rva00030AB0(GapChunk *chunk)
{
	return chunk->m_size & 0x80000000;
}

// --- 0x00030AC0 (13B): the chunk size without its flag bits.
unsigned int GetChunkSize(GapChunk *chunk)
{
	return GAP_CHUNK_SIZE(chunk);
}

// --- 0x00030AD0 (15B): the chunk that follows.
GapChunk *GetNextChunk(GapChunk *chunk)
{
	return GAP_CHUNK_AT(chunk, GAP_CHUNK_SIZE(chunk));
}

// --- 0x00030BF0 (11B): the head of bin n, addressed so that its fd/bk links
// overlay the bin's two pointer slots.
GapChunk *Rva00030C50Heap::rva00030BF0(int bin)
{
	return (GapChunk *)((char *)&m_bins[bin << 1] - 8);
}

// --- 0x00030C00 (13B): a chunk size served by the small bins.
int rva00030C00(unsigned int size)
{
	return size < 0x200;
}

// --- 0x00030C10 (8B): small-bin index of a chunk size.
unsigned int getSmallBinIndexFromChunkSize(unsigned int size)
{
	return size >> 3;
}

// --- 0x00030C20 (12B): the last sixteen bytes of a core.
GapChunk *rva00030C20(GapCore *core)
{
	return (GapChunk *)((char *)core + core->m_size - 0x10);
}

// --- 0x00030C30 (8B): the bitmap word holding a bin's bit.
int rva00030C30(int bin)
{
	return bin >> 5;
}

// --- 0x00031090 (94B): does a chunk pass a block-type filter? Unless bit 4
// is set, a chunk with size bit 2 never passes; bits 1 and 2 together pass
// anything; otherwise the chunk is in use when the next chunk's size word
// has bit 0 set and its own size word is non-negative, and bit 1 asks for
// in-use chunks, bit 2 for free ones. Any other filter passes nothing.
int rva00031090(const GapChunk *chunk, unsigned int flags)
{
	if (!(flags & 0x10) && (chunk->m_size & 4))
		return 0;
	if ((flags & 6) == 6)
		return 1;
	unsigned int size = chunk->m_size;
	const GapChunk *next = (const GapChunk *)((const char *)chunk + (size & 0x7FFFFFF8));
	int inUse = ((next->m_size & 1) && !(size & 0x80000000)) ? 1 : 0;
	if (flags & 2)
		return inUse;
	if (flags & 4)
		return inUse == 0;
	return 0;
}

// --- 0x00031080 (5B): an always-true three-argument check.
bool Rva00030C50Heap::rva00031080(void *a, void *b, void *c)
{
	return true;
}

namespace EA
{
namespace Allocator
{
// Only the static bin-index helper rowed in memory_pool.cpp (0x00030F10).
class GeneralAllocator
{
public:
	static unsigned int GetLargeBinIndexFromChunkSize(unsigned int size);
};
}
}

// --- 0x00031770 (24B): bin index of any chunk size: small sizes index by
// eight-byte steps, larger ones go to the large-bin helper (a tail call).
unsigned int GetBinIndexFromChunkSize(unsigned int size)
{
	if (size < 0x200)
		return size >> 3;
	return EA::Allocator::GeneralAllocator::GetLargeBinIndexFromChunkSize(size);
}

// --- 0x00030F60 (165B): choose and return a new top chunk. Walk every core's chunks
// (through the +0x18 link, from the sentinel's) for the largest free one,
// taking the first free chunk over 0x2000 bytes or the one ending at the
// core's last sixteen bytes outright; unlink the choice into a ring of its
// own. With none found the top stays the bin-1 head.
inline unsigned int gapChunkSize(const GapChunk *chunk)
{
	return chunk->m_size & 0x7FFFFFF8;
}

inline GapChunk *gapNextChunk(GapChunk *chunk)
{
	return GAP_CHUNK_AT(chunk, gapChunkSize(chunk));
}

inline int gapPrevInUse(const GapChunk *chunk)
{
	return chunk->m_size & 1;
}

GapChunk *Rva00030C50Heap::rva00030F60()
{
	GapChunk *best = (GapChunk *)((char *)&m_bins[2] - 8);
	unsigned int bestSize = 0;
	for (GapCore *core = m_cores.m_prev; core != &m_cores; core = core->m_prev)
	{
		GapChunk *end = (GapChunk *)((char *)core + core->m_size - 0x10);
		for (GapChunk *chunk = (GapChunk *)core->m_base; chunk < end;)
		{
			GapChunk *next = gapNextChunk(chunk);
			if (!gapPrevInUse(gapNextChunk(chunk)))
			{
				unsigned int size = gapChunkSize(chunk);
				if (size > 0x2000 || next == end)
				{
					best = chunk;
					goto found;
				}
				if (size > bestSize)
				{
					best = chunk;
					bestSize = size;
				}
			}
			chunk = next;
		}
	}
found:
	if (best != (GapChunk *)((char *)&m_bins[2] - 8))
	{
		best->m_fd->m_bk = best->m_bk;
		best->m_bk->m_fd = best->m_fd;
		best->m_bk = best;
		best->m_fd = best;
	}
	m_top = best;
	return best;
}

// --- 0x00030D50 (8B): the negation of a flag passed in ecx (__fastcall).
int __fastcall rva00030D50(bool flag)
{
	return !flag;
}
