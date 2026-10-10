// ?rva006C3220@GeneralAllocatorDebug@@QAE_NH@Z
// partial score=0.84 date=2026-10-10
// ?rva006C3220@GeneralAllocatorDebug@@QAE_NH@Z @ 0x006C3220 (429B).
// Reentrancy-guarded debug-allocator verifier. When the +0x484 guard flag is
// clear it sets it, verifies every delayed-free chunk through the rowed
// VerifyDelayedFreeFill 0x006C30C0, and when the level argument exceeds 1 it
// walks every allocated block's guard run (pinned block walk 0x000353B0 /
// 0x00032F60 / 0x00033E90 and the rowed guard-run builder 0x006C25F0, kind
// 0xB) through the rowed fill checker 0x00030E20, reporting through the rowed
// 0x006C2FB0 with the owned "GeneralAllocatorDebug::VerifyGuardFill
// failure." literal at 0x008E7C0C. It then walks the +0x684 record array
// through the pinned 0x00031F90 helper, releases the +0x4E4 lock, clears the
// guard flag and returns the rowed base verify 0x000329E0 combined with the
// fill result. Class layout, lock guard and walk idioms follow the rowed
// GeneralAllocatorDebug siblings (Rva006C1F60Finish.cpp,
// Rva006C3020Finish.cpp); the +0x680 flag and +0x684 array/count members
// follow Rva006C21C0.cpp / Rva006C38D0Cluster.cpp. The 0x00031F90 helper is
// a fresh pin (in-image code, lock-scoped size probe). Method name
// address-derived on the retail-proven class.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);
unsigned char rva00030E20Fill(void *memory, unsigned int size, unsigned char value);

class Rva006C2D20Sink
{
public:
	void rva006C2FB0(const char *text, const char *extra);
};

namespace EA { namespace Allocator {
struct BlockInfo
{
	void *mpCore; // +0x00
};
class GeneralAllocator
{
public:
	void *rva000353B0(void *core, int types, bool b, void *d, unsigned int e);
	const BlockInfo *rva00032F60(void *handle, int types);
	void rva00033E90(void *handle);
	bool rva000329E0(int level);
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

struct Rva006C17B0
{
	void *m_array; // +0x00
	unsigned char m_pad4; // +0x04
	unsigned char m_pad5[3];
	unsigned int m_count; // +0x08
	int m_padC; // +0x0C
	int m_10; // +0x10
};

class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator
{
public:
	bool rva006C3220(int level);
	bool VerifyDelayedFreeFill(void *block);
	void *rva006C25F0Run6(void *runBlock, int kind, int zero3, int zero2,
		unsigned int *outLen, int zero1);
	int rva00031F90(int size);
private:
	unsigned char m_base000[0x448];
	GeneralAllocatorCore m_coreSentinel; // +0x448
	unsigned char m_pad468[0x484 - 0x468];
	bool m_inVerify; // +0x484
	unsigned char m_pad485[0x4E4 - 0x484 - 1];
	Rva00030DD0Lock *m_lock; // +0x4E4
	unsigned char m_pad4E8[0x508 - 0x4E8];
	unsigned char m_fillFree; // +0x508
	unsigned char m_fillDelayedFree; // +0x509
	unsigned char m_fillNew; // +0x50A
	unsigned char m_fillGuard; // +0x50B
	unsigned char m_fillUnusedCore; // +0x50C
	unsigned char m_pad50D[0x548 - 0x50D];
	GeneralAllocatorChunk m_delayedFree; // +0x548
	unsigned char m_pad558[0x680 - 0x558];
	bool m_680; // +0x680
	Rva006C17B0 m_records; // +0x684
};

bool GeneralAllocatorDebug::rva006C3220(int level)
{
bool ok = 1;
	if (!m_inVerify)
	{
	m_inVerify = true;
	int validateLevel = 0;
	{
		GeneralAllocatorDebugLockGuard guard(m_lock);
		GeneralAllocatorChunk *chunk = m_delayedFree.m_next;
		GeneralAllocatorChunk *sentinel = &m_delayedFree;
		while (chunk != sentinel)
		{
			VerifyDelayedFreeFill(chunk);
			chunk = chunk->m_next;
		}
		if (level > 1)
		{
			void *walk = rva000353B0(0, 2, false, 0, 0);
			for (const EA::Allocator::BlockInfo *info = rva00032F60(walk, 2); info; info = rva00032F60(walk, 2))
			{
				GeneralAllocatorChunk *core = (GeneralAllocatorChunk *)info->mpCore;
				if (!(core->m_size & 4))
				{
					char *data = (char *)core + 8;
					unsigned int outLen;
					char *run = (char *)rva006C25F0Run6(data, 0xB, 0, 0, &outLen, 0);
					if (run)
					{
						unsigned int len = outLen;
						if (len >= 0x40)
							len = 0x40;
						char *end = run + len;
						if (!rva00030E20Fill(run, end - run, m_fillGuard))
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
			unsigned int count = m_records.m_count;
			unsigned int index = 0;
			if (count > 0)
			{
				do
				{
					GeneralAllocatorChunk *record = ((GeneralAllocatorChunk **)m_records.m_array)[index];
					if (record)
					{
						do
						{
							rva00031F90(record->m_size - 8);
							record = record->m_next;
						} while (record);
					}
					++index;
				} while (index < m_records.m_count);
			}
		}
	}
	m_inVerify = false;
	if (!rva000329E0(validateLevel))
		return false;
	}
	return ok;
}
