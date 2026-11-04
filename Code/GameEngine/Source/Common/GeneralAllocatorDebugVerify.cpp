// cl: /DNDEBUG /MD
//
// ?rva006C3220@GeneralAllocatorDebug@@QAE_NH@Z, retail 0x006C3220 (429 bytes,
// thiscall ret 4): the reentrancy-guarded debug-allocator verifier. When the
// +0x484 guard flag is clear it sets it, verifies every delayed-free chunk
// through the rowed VerifyDelayedFreeFill 0x006C30C0, and when the level
// argument exceeds 1 it walks every allocated block's guard run (block walk
// 0x000353B0 / 0x00032F60 / 0x00033E90 and the rowed guard-run builder
// 0x006C25F0, kind 0xB) through the rowed fill checker 0x00030E20, reporting
// through the rowed 0x006C2FB0 with the "GeneralAllocatorDebug::VerifyGuardFill
// failure." literal. It then walks the +0x684 record array through the
// GeneralAllocator helper 0x00031F90 (pinned), releases the +0x4E4 lock,
// clears the guard flag and returns false when the base verify 0x000329E0
// fails, else the fill result. Class layout, lock guard and walk idioms follow
// the rowed GeneralAllocatorDebug siblings (Rva006C1F60Finish.cpp,
// Rva006C3020Finish.cpp); the +0x680 flag and +0x684 array/count members
// follow Rva006C21C0.cpp / Rva006C38D0Cluster.cpp. Method name address-derived.
//
// Levers: the base-verify failure assigns ok = false and falls into the one
// return ok (an early return false makes cl store the guard flag and ok as
// immediates instead of sharing the true in AL with the already-verifying
// path), and the guard-run data pointer and the record helper's argument are
// named locals, which puts them in EAX ahead of ECX as retail does.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);
unsigned char rva00030E20Fill(void *memory, unsigned int size, unsigned char value);

class Rva006C2D20Sink
{
public:
	void rva006C2FB0(const char *text, const char *extra);
};

#include "../../Include/Common/GeneralAllocator.h"

namespace EA { namespace Allocator {
struct BlockInfo
{
	void *mpCore; // +0x00
};
}}

struct GeneralAllocatorChunk
{
	unsigned int m_prevSize; // +0x00
	unsigned int m_size; // +0x04
	GeneralAllocatorChunk *m_prev; // +0x08
	GeneralAllocatorChunk *m_next; // +0x0C
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

struct Rva006C17B0
{
	void *m_array; // +0x00
	unsigned char m_pad4; // +0x04
	unsigned char m_pad5[3];
	unsigned int m_count; // +0x08
	int m_padC; // +0x0C
	int m_10; // +0x10
};

// Canonical base fields read here: m_484 the in-verify flag, m_pLock the lock,
// m_508[3] (+0x50B) the guard fill byte.
class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator
{
public:
	bool rva006C3220(int level);
	bool VerifyDelayedFreeFill(void *block);
	void *rva006C25F0Run6(void *runBlock, int kind, int zero3, int zero2,
		unsigned int *outLen, int zero1);
private:
	unsigned char m_pad510[0x548 - 0x510];
	GeneralAllocatorChunk m_delayedFree; // +0x548
	unsigned char m_pad558[0x680 - 0x558];
	bool m_680; // +0x680
	Rva006C17B0 m_records; // +0x684
};

bool GeneralAllocatorDebug::rva006C3220(int level)
{
	bool ok = true;
	if (!m_484)
	{
		m_484 = true;
		{
			GeneralAllocatorDebugLockGuard guard(m_pLock);
			for (GeneralAllocatorChunk *chunk = m_delayedFree.m_next; chunk != &m_delayedFree; chunk = chunk->m_next)
				VerifyDelayedFreeFill(chunk);
			if (level > 1)
			{
				void *walk = rva000353B0(0, 2, false, 0, 0);
				for (const EA::Allocator::BlockInfo *info = rva00032F60(walk, 2); info; info = rva00032F60(walk, 2))
				{
					GeneralAllocatorChunk *core = (GeneralAllocatorChunk *)info->mpCore;
					if (!(core->m_size & 4))
					{
						unsigned int outLen;
						char *data = (char *)core + 8;
						char *run = (char *)rva006C25F0Run6(data, 0xB, 0, 0, &outLen, 0);
						if (run)
						{
							unsigned int len = outLen;
							if (len >= 0x40)
								len = 0x40;
							char *end = run + len;
							if (!rva00030E20Fill(run, end - run, m_508[3]))
							{
								((Rva006C2D20Sink *)this)->rva006C2FB0((const char *)core, "GeneralAllocatorDebug::VerifyGuardFill failure.");
								ok = false;
							}
						}
					}
				}
				rva00033E90(walk);
			}
			if (m_680)
			{
				for (unsigned int index = 0; index < m_records.m_count; ++index)
				{
					for (GeneralAllocatorChunk *record = ((GeneralAllocatorChunk **)m_records.m_array)[index]; record; record = record->m_prev)
						{ char *data = (char *)record->m_size - 8; rva00031F90(data); }
				}
			}
		}
		m_484 = false;
		if (!rva000329E0(level))
			ok = false;
	}
	return ok;
}
