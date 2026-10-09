// ?rva006C1F60@Rva006C1F60@@QAEHI@Z @ 0x006C1F60 113B chain of 0x00030DF0
// Release. AddRef at +0x4e4 Release guarded float clamp via __ftol2 returning
// clamped int. Evidence: calls AddRef 0x00030DD0 Release 0x00030DF0 __ftol2
// rowed; flag bit 0x800 at +0x514 scale float at +0x534 min at +0x538 max at
// +0x53c; caller at 0x006C2463. Honest address-derived method of Rva006C1F60.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);
extern "C" int __cdecl __ftol2(float f);
class Rva006C1F60
{
public:
	int rva006C1F60(unsigned int v);
private:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;
	unsigned char m_pad1[0x514 - 0x4e4 - 4];
	int m_flags;
	unsigned char m_pad2[0x534 - 0x514 - 4];
	float m_scale;
	unsigned int m_min;
	unsigned int m_max;
};
int Rva006C1F60::rva006C1F60(unsigned int v)
{
	Rva00030DD0Lock *lock = m_lock;
	if (lock != 0)
		Rva00030DD0AddRef(lock);
	unsigned int result = 0;
	if ((m_flags & 0x800) != 0) {
		float f = (float)v * m_scale;
		result = (unsigned int)(int)f;
		if (result < m_min)
			result = m_min;
		if (result > m_max)
			result = m_max;
	}
	if (lock != 0)
		Rva00030DF0Release(lock);
	return (int)result;
}

//
// ?rva006C2AA0@GeneralAllocatorDebug@@QAEXEEEEE@Z, retail 0x006C2AA0 (638 bytes). The
// retail body runs to its `ret 0x14` at 0x006C2D1B, 638 bytes (the Ghidra
// boundary stops three bytes short at 635). Takes five fill bytes for the
// allocator's fill slots +0x508..+0x50C (the debug constructor 0x006C4A50
// sets them to DD DE CD AB FE) and refills existing memory where a value
// changes, under the +0x4E4 lock (rowed AddRef 0x00030DD0 / Release
// 0x00030DF0; the unwind state releases it). Target evidence:
//  - +0x50A and +0x50C are stored directly;
//  - a new +0x508 value is written over every free chunk of every core block
//    (core list sentinel +0x448; next +0x1C; first chunk +0; size +4)
//    after its 16-byte header;
//  - a new +0x509 value (1 also clears +0x540) is written over each block of
//    the delayed-free list (sentinel +0x548; next +0x0C) past its two link
//    words, sized inline from the debug trailer or else through the rowed
//    GetBlockSize 0x00032A20;
//  - a new +0x50B value (1 also clears flag 0x800 of +0x514) is written over
//    each allocated block's guard run: the pinned block walk 0x000353B0 /
//    0x00032F60 / 0x00033E90 and the pinned guard-run builder 0x006C25F0
//    (kind 0xB) as in the rowed VerifyGuardFill 0x006C3020.
// The fills are the intrinsic memset. Method name address-derived.

#include <string.h>
#pragma intrinsic(memset)

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

namespace EA { namespace Allocator {
struct BlockInfo
{
	void *mpCore; // +0x00
};
class GeneralAllocator
{
public:
	unsigned int rva00032A20(const void *block);
	void *rva000353B0(void *core, int types, bool b, void *d, unsigned int e);
	const BlockInfo *rva00032F60(void *handle, int types);
	void rva00033E90(void *handle);
};
}}

struct GeneralAllocatorChunk
{
	unsigned int m_prevSize; // +0x00
	unsigned int m_size; // +0x04
	GeneralAllocatorChunk *m_prev; // +0x08
	GeneralAllocatorChunk *m_next; // +0x0C
};

struct GeneralAllocatorCore
{
	char *m_first; // +0x00
	unsigned int m_size; // +0x04
	unsigned char m_pad08[0x1C - 0x08];
	GeneralAllocatorCore *m_next; // +0x1C
};

class GeneralAllocatorDebugLockGuard
{
public:
	GeneralAllocatorDebugLockGuard(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~GeneralAllocatorDebugLockGuard()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}
private:
	Rva00030DD0Lock *m_lock;
};

class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator
{
public:
	void rva006C2AA0(unsigned char fillFree, unsigned char fillDelayedFree,
		unsigned char fillNew, unsigned char fillGuard, unsigned char fillUnusedCore);
	void *rva006C25F0Run6(void *runBlock, int kind, int zero3, int zero2,
		unsigned int *outLen, int zero1);
private:
	unsigned int getDebugDataSize(char *data)
	{
		unsigned int sizeField = ((GeneralAllocatorChunk *)(data - 8))->m_size;
		if (!(sizeField & 0x80000000))
		{
			unsigned int chunkSize;
			if (!(sizeField & 2))
				chunkSize = (sizeField & 0x7FFFFFF8) + 4;
			else
				chunkSize = sizeField & 0x7FFFFFF8;
			char *trailer = data + chunkSize - 10;
			char *end = trailer - *(unsigned short *)trailer;
			if (end >= data)
				return end - data;
		}
		return rva00032A20(data);
	}

	unsigned char m_base000[0x448];
	GeneralAllocatorCore m_coreSentinel; // +0x448
	unsigned char m_pad468[0x4E4 - 0x468];
	Rva00030DD0Lock *m_lock; // +0x4E4
	unsigned char m_pad4E8[0x508 - 0x4E8];
	unsigned char m_fillFree; // +0x508
	unsigned char m_fillDelayedFree; // +0x509
	unsigned char m_fillNew; // +0x50A
	unsigned char m_fillGuard; // +0x50B
	unsigned char m_fillUnusedCore; // +0x50C
	unsigned char m_pad50D[0x514 - 0x50D];
	unsigned int m_flags; // +0x514
	unsigned char m_pad518[0x540 - 0x518];
	unsigned int m_delayedFreeTotal; // +0x540
	unsigned int m_544;
	GeneralAllocatorChunk m_delayedFree; // +0x548
};

void GeneralAllocatorDebug::rva006C2AA0(unsigned char fillFree, unsigned char fillDelayedFree,
	unsigned char fillNew, unsigned char fillGuard, unsigned char fillUnusedCore)
{
	GeneralAllocatorDebugLockGuard guard(m_lock);

	m_fillNew = fillNew;
	m_fillUnusedCore = fillUnusedCore;

	if (m_fillFree != fillFree)
	{
		m_fillFree = fillFree;
		for (GeneralAllocatorCore *core = m_coreSentinel.m_next; core != &m_coreSentinel; core = core->m_next)
		{
			char *end = (char *)core + core->m_size - 0x10;
			for (char *chunk = core->m_first; chunk < end;
				chunk += ((GeneralAllocatorChunk *)chunk)->m_size & 0x7FFFFFF8)
			{
				unsigned int size = ((GeneralAllocatorChunk *)chunk)->m_size & 0x7FFFFFF8;
				if (!(((GeneralAllocatorChunk *)(chunk + size))->m_size & 1))
					memset(chunk + 0x10, m_fillFree, size - 0x10);
			}
		}
	}

	if (m_fillDelayedFree != fillDelayedFree)
	{
		m_fillDelayedFree = fillDelayedFree;
		if (fillDelayedFree == 1)
			m_delayedFreeTotal = 0;
		for (GeneralAllocatorChunk *chunk = m_delayedFree.m_next; chunk != &m_delayedFree; chunk = chunk->m_next)
		{
			char *data = (char *)chunk + 8;
			unsigned int size = getDebugDataSize(data);
			memset(data + 8, m_fillDelayedFree, size - 8);
		}
	}

	if (m_fillGuard != fillGuard)
	{
		m_fillGuard = fillGuard;
		if (fillGuard == 1)
			m_flags &= ~0x800;
		void *walk = rva000353B0(0, 2, false, 0, 0);
		for (const EA::Allocator::BlockInfo *info = rva00032F60(walk, 2); info; info = rva00032F60(walk, 2))
		{
			GeneralAllocatorChunk *chunk = (GeneralAllocatorChunk *)info->mpCore;
			char *data = (char *)chunk + 8;
			unsigned int len;
			char *run = (char *)rva006C25F0Run6(data, 0xB, 0, 0, &len, 0);
			if (run)
			{
				char *end = run + len;
				if (run < data + 8)
					run = data + 8;
				memset(run, m_fillGuard, end - run);
			}
		}
		rva00033E90(walk);
	}
}
