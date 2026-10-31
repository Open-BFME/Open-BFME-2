// cl: /MD /EHsc
// platformsdk
// /EHsc retains the original nonthrowing C API contract for the lock calls.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <new>
//
// ?rva00034D10@GeneralAllocator@Allocator@EA@@QAEPAXH_NPAXI@Z retail 0x00034D10..0x00035071
// (865 bytes thiscall ret 0x10). The heap-snapshot builder behind the
// ReportBegin-like 0x000353B0 (PPMalloc GeneralAllocator; snapshot magic
// "PANS"). Under the counted lock at +0x4E4 it either makes a header-only
// snapshot (0x38 bytes; core list +0x464 and large list +0x4A8 recorded) or
// with the copy flag makes two passes over the core blocks (+0x464 list to
// the +0x448 sentinel; next at +0x1C) and their chunks (in use / free by
// the next chunk's bit 0; flags 8 core 2 used 4 free 0x10 internal) and the
// large-chunk list (+0x4A8 to +0x49C): the first counts, the second
// allocates count+4 0x14-byte records after the 0x24-byte header (the
// caller's storage when big enough, else 0x00033ED0 with 0x80000000),
// constructs the Snapshot (0x00031570) and fills the records (core blocks
// inline, chunks through 0x00032EC0). Names are address-derived.
class Rva00035080Lock
{
public:
	void *m_obj;
	Rva00035080Lock(void *obj) : m_obj(obj)
	{
		if (m_obj)
		{
			EnterCriticalSection(static_cast<CRITICAL_SECTION *>(m_obj));
			++*(volatile int *)((char *)m_obj + 0x18);
		}
	}
	~Rva00035080Lock()
	{
		if (m_obj)
		{
			--*(volatile int *)((char *)m_obj + 0x18);
			LeaveCriticalSection(static_cast<CRITICAL_SECTION *>(m_obj));
		}
	}
};

class Rva00034C90
{
public:
	void consolidate();
};

class Rva006C1F60
{
public:
	void *rva00033ED0(unsigned int size, int flags);
};

namespace EA { namespace Allocator {
struct BlockInfo
{
	void *m_core; // +0x00
	unsigned int m_blockSize; // +0x04
	void *m_data; // +0x08
	unsigned int m_dataSize; // +0x0C
	char m_blockType; // +0x10
	bool m_mapped; // +0x11
	char m_pad12[2];
};

} }

struct Rva00034D10Snapshot
{
	unsigned int m_magic; // +0x00
	unsigned int m_size; // +0x04
	void *m_context; // +0x08
	unsigned char m_external; // +0x0C
	unsigned char m_0D; // +0x0D
	unsigned char m_headerOnly; // +0x0E
	unsigned char m_0F; // +0x0F
	void *m_coreList; // +0x10
	unsigned int m_14; // +0x14
	void *m_largeList; // +0x18
	unsigned int m_count; // +0x1C
	unsigned int m_20; // +0x20
	EA::Allocator::BlockInfo m_info[1]; // +0x24
};

struct Rva00034D10Chunk
{
	unsigned int m_prevSize; // +0x00
	unsigned int m_size; // +0x04
	Rva00034D10Chunk *m_fd; // +0x08
	Rva00034D10Chunk *m_bk; // +0x0C
};

struct Rva00034D10Core
{
	Rva00034D10Chunk *m_first; // +0x00
	unsigned int m_size; // +0x04
	unsigned int m_08; // +0x08
	char m_pad0C[0x1c - 0xc];
	Rva00034D10Core *m_next; // +0x1C
};

struct Rva00034D10Large
{
	unsigned int m_offset; // +0x00
	unsigned int m_flags; // +0x04
	char m_pad08[4];
	Rva00034D10Large *m_next; // +0x0C
};

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	struct Snapshot
	{
		unsigned int m_magic;
		unsigned int m_size;
		void *m_arg2;
		unsigned char m_state[4];
		unsigned int m_values[5];
		// memory_pool.cpp's rowed constructor only clears and initializes
		// the supplied storage; placement construction needs no failure cleanup.
		__declspec(nothrow) Snapshot(unsigned int size, void *context);
	};
	void *rva00034D10(int blockTypes, bool copy, void *storage, unsigned int storageSize);
	void rva00032EC0(const void *chunk, BlockInfo *info);

private:
	char m_pad000[4];
	unsigned int m_flags; // +0x004
	char m_pad008[0x448 - 8];
	Rva00034D10Core m_coreSentinel; // +0x448
	char m_pad468[0x49c - 0x468];
	Rva00034D10Large m_largeSentinel; // +0x49C
	char m_pad4AC[0x4e4 - 0x4ac];
	void *m_lock; // +0x4E4
};

} }

void *EA::Allocator::GeneralAllocator::rva00034D10(int blockTypes, bool copy, void *storage, unsigned int storageSize)
{
	Rva00035080Lock lock(m_lock);
	Rva00034D10Snapshot *snapshot = 0;
	if (copy)
	{
		if (m_flags & 1)
			reinterpret_cast<Rva00034C90 *>(this)->consolidate();
		unsigned int count = 0;
		for (unsigned int pass = 0; pass < 2; pass++)
		{
			unsigned int i = 0;
			if (pass)
			{
				count += 4;
				unsigned int size = count * sizeof(EA::Allocator::BlockInfo) + sizeof(Rva00034D10Snapshot);
				if (storage && (unsigned int)storageSize < size)
					storage = 0;
				void *snapshotStorage = storage ? (void *)storage : reinterpret_cast<Rva006C1F60 *>(this)->rva00033ED0(size, 0x80000000);
				if (snapshotStorage)
				{
					((unsigned int *)snapshotStorage)[-1] |= 4;
					snapshot = (Rva00034D10Snapshot *)new (snapshotStorage) EA::Allocator::GeneralAllocator::Snapshot(size, (void *)blockTypes);
					snapshot->m_size = size;
					snapshot->m_external = storage != 0;
					snapshot->m_headerOnly = 0;
					snapshot->m_count = count;
					snapshot->m_20 = 0;
				}
				if (count == 4)
					break;
			}

			for (Rva00034D10Core *core = m_coreSentinel.m_next; core != &m_coreSentinel; core = core->m_next)
			{
				if (blockTypes & 8)
				{
					if (pass && i < count)
					{
						EA::Allocator::BlockInfo *info = &snapshot->m_info[i];
						info->m_blockType = 8;
						info->m_core = core->m_first;
						info->m_blockSize = core->m_size;
						info->m_dataSize = core->m_08;
						info->m_mapped = 0;
					}
					i++;
				}
				if (blockTypes & 6)
				{
					Rva00034D10Chunk *end = (Rva00034D10Chunk *)((char *)core + core->m_size - 0x10);
					Rva00034D10Chunk *chunk = core->m_first;
					if (chunk < end)
					{
						do
						{
							unsigned int inUse = ((Rva00034D10Chunk *)((char *)chunk + (chunk->m_size & 0x7ffffff8)))->m_size & 1;
							if (inUse)
							{
								if ((blockTypes & 2) && ((blockTypes & 0x10) || !(chunk->m_size & 4)))
								{
									if (pass && i < count)
										rva00032EC0(chunk, &snapshot->m_info[i]);
									i++;
								}
							}
							else
							{
								if ((blockTypes & 4) && ((blockTypes & 0x10) || !(chunk->m_size & 4)))
								{
									if (pass && i < count)
										rva00032EC0(chunk, &snapshot->m_info[i]);
									i++;
								}
							}
							if (!inUse && chunk == chunk->m_bk)
								break;
							chunk = (Rva00034D10Chunk *)((char *)chunk + (chunk->m_size & 0x7ffffff8));
						} while (chunk < end);
					}
				}
			}

			if (blockTypes & 2)
			{
				for (Rva00034D10Large *large = m_largeSentinel.m_next; large != &m_largeSentinel; large = large->m_next)
				{
					void *chunk = (char *)large - large->m_offset;
					if ((blockTypes & 0x10) || !(large->m_flags & 4))
					{
						if (pass && i < count)
							rva00032EC0(chunk, &snapshot->m_info[i]);
						i++;
					}
				}
			}
			count = i;
			if (pass)
				snapshot->m_count = i;
		}
	}
	else
	{
		unsigned int size = 0x38;
		if (storage && (unsigned int)storageSize < size)
			storage = 0;
		void *snapshotStorage = storage ? (void *)storage : reinterpret_cast<Rva006C1F60 *>(this)->rva00033ED0(size, 0x80000000);
		if (snapshotStorage)
		{
			((unsigned int *)snapshotStorage)[-1] |= 4;
			Rva00034D10Snapshot *s = (Rva00034D10Snapshot *)new (snapshotStorage) EA::Allocator::GeneralAllocator::Snapshot(size, (void *)blockTypes);
			s->m_size = size;
			s->m_external = storage != 0;
			s->m_headerOnly = 1;
			s->m_coreList = m_coreSentinel.m_next;
			s->m_14 = 0;
			snapshot = s;
			s->m_largeList = m_largeSentinel.m_next;
		}
	}
	return snapshot;
}

// The free-list termination guard also consumes inUse after classification.
// The large-list predicate uses only the internal-block flag at bit 4.
// Records are addressed as &snapshot->m_info[i]; cl strength-reduces the
// index into the EBP record pointer after hoisting the bit-4 mask, which
// gives retail's preheader order and the dword TEST EBX,EBX.
