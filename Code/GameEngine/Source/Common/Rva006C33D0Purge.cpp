// cl: /MD /DNDEBUG /EHsc
// platformsdk
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

void Rva006C1F60::rva006C33D0(int policy, int limit)
{
	Guard guard(lock);
	++depth;
	if (policy == 0) {
		while (head.next != &head)
			remove(head.next);
	} else if (policy == 1) {
		while (head.next != &head) {
			if (count <= (unsigned)limit)
				break;
			remove(head.next);
		}
	} else if (policy == 2) {
		while (head.next != &head) {
			if (total <= (unsigned)limit)
				break;
			remove(head.next);
		}
	} else if (policy == 3) {
		unsigned now = GetTickCount() / 1000;
		unsigned threshold = now + (unsigned)limit;
		if (threshold < now)
			threshold = 0;
		while (head.next != &head) {
			DelayedChunk *chunk = head.next;
			char *data = (char *)chunk + 8;
			unsigned size = rva00032A20(data);
			unsigned freedTime = 0;
			freedTime = (unsigned)chunk->prev;
			if (freedTime <= threshold)
				break;
			chunk->prev->next = chunk->next;
			chunk->next->prev = chunk->prev;
			--count;
			total -= size;
			rva006C3180((GeneralAllocatorDebugBlock *)chunk);
		}
	}
	--depth;
}



