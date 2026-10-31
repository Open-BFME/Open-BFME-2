// cl: /O2 /MD /DNDEBUG /EHsc
// platformsdk
// Split from Rva006C33D0Purge.cpp. The report wrappers now call their
// recovered allocator owners; the lower-level free body remains unrowed.
//
// ?rva006C33D0@Rva006C1F60@@QAEXHH@Z @ 0x006C33D0 643B, ret 8
//
// Debug-allocator delayed-free purge: (policy, limit). Under the scoped
// +0x4E4 lock and with the +0x530 depth counter raised, blocks are taken off
// the front of the delayed-free list (head chunk at +0x548, first block via
// its +0x554 link) and really freed through 0x006C3180, keeping the list's
// block count (+0x558) and byte volume (+0x55C) in step. Policy 0 empties the
// list; 1 stops once the count is within the limit; 2 once the volume is;
// 3 frees blocks whose stored time (the first word of the freed data) is
// later than now + limit seconds, the threshold clamped to 0 on overflow.
// Each block's size comes from 0x00032A20 before it is unlinked.
//
// Evidence: retail body; WorldBuilder's unoptimized twin at 0x00709370 has
// the same four policies with asserts naming the counters
// ("(mDelayedFreeListSize == 0) && (mDelayedFreeVolume == 0)",
// "nUsableSize < 0x40000000"). Its policy-3 loop reads the time into a
// variable first zeroed, and only that spelling gives retail's register
// choice for the chunk and data pointers there. Names are address-derived.

#include <windows.h>
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *);
int Rva00030DF0Release(Rva00030DD0Lock *);

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	void rva00033150(const void *block);
	unsigned rva00032A20(const void *);
	typedef void (*TraceFunction)(const char *text, void *context);
	void *rva00034D10(int blockTypes, bool copy, void *storage, unsigned int storageSize);
	void traceAllocatedMemory(TraceFunction function, void *functionContext, void *context, int blockTypes);
};
} }

struct GeneralAllocatorDebugBlock;

class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator
{
public:
	void rva006C3180(GeneralAllocatorDebugBlock *);
	void *rva006C25F0Run6(void *, int, int, int, unsigned int *, int);
	bool VerifyDelayedFreeFill(void *);
	void rva006C26F0(void *, bool);
};

struct DelayedChunk
{
	unsigned prevSize, size;
	DelayedChunk *prev, *next;
};

struct Guard
{
	Guard(Rva00030DD0Lock *p) : lock(p)
	{
		if (lock)
			Rva00030DD0AddRef(lock);
	}
	~Guard()
	{
		if (lock)
			Rva00030DF0Release(lock);
	}
	Rva00030DD0Lock *lock;
};

class Rva006C1F60 : public GeneralAllocatorDebug
{
public:
	void rva006C33D0(int policy, int limit);
	void *rva00033ED0(unsigned int size, int flags);
	void *rva006C1CC0(unsigned int size, int flags);
	void TraceAllocatedMemory(TraceFunction function, void *functionContext, void *context, int blockTypes);
	void *TakeSnapshot(int blockTypes, bool copy, void *storage, unsigned int storageSize);

	char unknown0[0x4e4];
	Rva00030DD0Lock *lock;
	char unknown4e8[0x530 - 0x4e8];
	unsigned depth;
	char unknown534[0x548 - 0x534];
	DelayedChunk head;
	unsigned count, total;

	__forceinline void remove(DelayedChunk *chunk)
	{
		char *data = (char *)chunk + 8;
		unsigned size = rva00032A20(data);
		chunk->prev->next = chunk->next;
		chunk->next->prev = chunk->prev;
		--count;
		total -= size;
		rva006C3180((GeneralAllocatorDebugBlock *)chunk);
	}
};


// Retail 0x006C3810 (43 B, ret 0x10): purge the whole delayed-free list
// (policy 0) and then forward the four arguments to the allocator body at
// 0x00034D10, returning its result. Its twin 0x006C37E0 does the same in
// front of 0x000353F0. Names address-derived.
void *Rva006C1F60::TakeSnapshot(int blockTypes, bool copy, void *storage, unsigned int storageSize)
{
	rva006C33D0(0, 0);
	return rva00034D10(blockTypes, copy, storage, storageSize);
}

void Rva006C1F60::TraceAllocatedMemory(TraceFunction function, void *functionContext, void *context, int blockTypes)
{
	rva006C33D0(0, 0);
	traceAllocatedMemory(function, functionContext, context, blockTypes);
}

// Retail 0x006C1CC0 (71 B, ret 8), next to the location formatter: allocate
// through 0x00033ED0 (two extra bytes when the flags' sign bit is set) and,
// on success, clear the 16-bit word 10 bytes before the end of the block's
// usable size (header +4 masked 0x7FFFFFF8, plus 4 unless bit 1 is set).
// Name address-derived.
void *Rva006C1F60::rva006C1CC0(unsigned int size, int flags)
{
	if (flags & 0x80000000)
		size += 2;
	void *block = rva00033ED0(size, flags);
	if (block)
	{
		unsigned int header = ((unsigned int *)block)[-1];
		unsigned int usable;
		if ((header & 2) == 0)
			usable = (header & 0x7FFFFFF8) + 4;
		else
			usable = header & 0x7FFFFFF8;
		*(unsigned short *)((char *)block + usable - 0xA) = 0;
	}
	return block;
}

struct GeneralAllocatorDebugBlock
{
	unsigned int previousSize;
	unsigned int flags;
	unsigned char data[1]; // user storage starts after the two header words
};

struct GeneralAllocatorGuardView
{
	unsigned char pad[0x50B];
	unsigned char guardFill;
	unsigned char pad50C[8];
	unsigned int flags; // +0x514
};

class Rva006C2D20Sink
{
public:
	void rva006C2FB0(const char *, const char *);
};
unsigned char rva00030E20Fill(void *, unsigned int, unsigned char);

// Native 006C3180..006C3216, 150 bytes, RET4. Before releasing a chunk,
// check up to 64 guard bytes, starting above the payload's first eight bytes.
// The builder receives the address header+8, rather than a pointer loaded
// there; its real six-argument ABI and the real (chunk, bool) metrics ABI
// reproduce retail's frameless EBP allocation in ordinary C++.
void GeneralAllocatorDebug::rva006C3180(GeneralAllocatorDebugBlock *info)
{
	GeneralAllocatorGuardView *view = (GeneralAllocatorGuardView *)this;
	if (!(info->flags & 4) && (view->flags & 0x800)) {
		unsigned int runLength;
		unsigned char *data = info->data;
		unsigned char *run = (unsigned char *)rva006C25F0Run6(data, 0xB, 0, 0, &runLength, 0);
		if (run) {
			unsigned int length = runLength;
			if (length >= 0x40)
				length = 0x40;
			unsigned char *end = run + length;
			unsigned char *lower = data + 8;
			if (run < lower)
				run = lower;
			if (!rva00030E20Fill(run, end - run, view->guardFill))
				((Rva006C2D20Sink *)this)->rva006C2FB0((const char *)info, "GeneralAllocatorDebug::VerifyGuardFill failure.");
		}
	}
	VerifyDelayedFreeFill(info);
	rva006C26F0(info, false);
	rva00033150(info->data);
}
