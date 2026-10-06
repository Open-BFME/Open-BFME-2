// ?rva000332D0@GeneralAllocator@Allocator@EA@@QAE_NHHHHHH@Z
// partial score=0.5 date=2026-10-07
// Banked C++ candidate for 0x000332D0. Reapply in memory_pool.cpp, where the
// GeneralAllocator lock/layout and existing 0x31010 method declaration live.
extern "C" __declspec(dllimport) unsigned long __stdcall VirtualQuery(const void *address, void *information, unsigned long informationSize);

struct Rva00031010Node
{
	unsigned char m_pad[8];
	Rva00031010Node *m_link8;
	Rva00031010Node *m_linkC;
};
class Rva00031010
{
public:
	void rva00031010(Rva00031010Node *node, bool flag);
private:
	unsigned char m_pad0[0x30];
	Rva00031010Node m_bin;
	unsigned char m_pad1[0x440 - 0x30 - sizeof(Rva00031010Node)];
	Rva00031010Node *m_head;
};

namespace EA { namespace Allocator {
// ?rva000332D0@GeneralAllocator@Allocator@EA@@QAE_NHHHHHH@Z present-unmatched
// The caller at 0x00033700 forwards six integer arguments. Target bytes
// establish this allocator through its lock at +0x4E4, use count at +0x18,
// descriptor list at +0x448, and bin links at +0x30/+0x440. The labels below
// describe target stores; they do not claim donor field names.
bool GeneralAllocator::rva000332D0(int coreInfo, int coreSize, int blockType,
	int blockFlags, int context, int arg6)
{
	GeneralAllocator *const allocator = this;
	Lock *lock = allocator->m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	if (coreInfo != 0)
	{
		unsigned char *const record = reinterpret_cast<unsigned char *>(coreInfo);
		unsigned int size = static_cast<unsigned int>(coreSize);
		if (size < 0x40)
		{
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return false;
		}

		unsigned int granularity = *reinterpret_cast<unsigned int *>(
		reinterpret_cast<char *>(allocator) + 0x4D4);
		if (size % granularity != 0)
			size &= ~(granularity - 1);
		if ((size & 0xF) != 0)
			size = (size >> 4) << 4;

		record[0xD] = static_cast<unsigned char>(blockType);
		record[0xE] = static_cast<unsigned char>(blockType);
		unsigned char *const data = reinterpret_cast<unsigned char *>(
			(reinterpret_cast<unsigned int>(record) + 0x27) & ~7);
		*reinterpret_cast<int *>(record + 0x14) = arg6;
		*reinterpret_cast<unsigned char **>(record) = data;

		unsigned char *const descriptorHead = reinterpret_cast<unsigned char *>(allocator) + 0x448;
		unsigned char *const oldFirst = *reinterpret_cast<unsigned char **>(descriptorHead + 0x18);
		*reinterpret_cast<unsigned char **>(record + 0x1C) = descriptorHead;
		*reinterpret_cast<unsigned int *>(record + 4) = size;
		*reinterpret_cast<unsigned int *>(record + 8) = size;
		record[0xC] = 0;
		record[0xF] = static_cast<unsigned char>(blockFlags);
		*reinterpret_cast<int *>(record + 0x10) = context;
		*reinterpret_cast<unsigned char **>(record + 0x18) = oldFirst;
		*reinterpret_cast<unsigned char **>(descriptorHead + 0x18) = record;
		*reinterpret_cast<unsigned char **>(oldFirst + 0x1C) = record;

		if (context == 0)
		{
			unsigned char information[0x1C];
			*reinterpret_cast<void **>(information) = record;
			VirtualQuery(record, information, 0x1C);
			if (*reinterpret_cast<unsigned int *>(information + 0x10) == 0x2000)
				*reinterpret_cast<unsigned int *>(record + 4) = 0;
		}

		unsigned int *const header = reinterpret_cast<unsigned int *>(data);
		unsigned int fenceSize = size - (reinterpret_cast<unsigned int>(data) -
			reinterpret_cast<unsigned int>(record));
		unsigned int taggedSize = fenceSize | 1;
		unsigned int fencepostOffset = (taggedSize & 0x7FFFFFF8) - 9;
		fencepostOffset &= 0xFFFFFFF8;
		header[0] = 0;
		header[1] = (taggedSize & 0x80000007) | fencepostOffset;
		unsigned int *const fencepost = reinterpret_cast<unsigned int *>(data + fencepostOffset);
		fencepost[0] = fencepostOffset;
		fencepost[1] = 8;
		fencepost[2] = 8;
		fencepost[3] = 9;

		Rva00031010Node *const oldBinHead = *reinterpret_cast<Rva00031010Node **>(
		reinterpret_cast<char *>(allocator) + 0x440);
		Rva00031010Node *const binSentinel = reinterpret_cast<Rva00031010Node *>(
			reinterpret_cast<char *>(allocator) + 0x30);
		reinterpret_cast<Rva00031010 *>(allocator)->rva00031010(
			reinterpret_cast<Rva00031010Node *>(data), oldBinHead != binSentinel);

		if (lock != 0)
		{
			--lock->m_count;
			LeaveCriticalSection(lock);
		}
		return true;
	}

	if (static_cast<unsigned int>(coreSize) != 0)
	{
		unsigned int granularity = *reinterpret_cast<unsigned int *>(
			reinterpret_cast<char *>(allocator) + 0x4D4);
		unsigned int roundedSize = (granularity + static_cast<unsigned int>(coreSize) - 1) & ~(granularity - 1);
		void *const block = allocator->rva00032B00(roundedSize);
		if (block != 0)
		{
			Rva00031010Node *const oldHead = *reinterpret_cast<Rva00031010Node **>(
				reinterpret_cast<char *>(allocator) + 0x440);
			*reinterpret_cast<void **>(reinterpret_cast<char *>(allocator) + 0x440) = block;
			*reinterpret_cast<void **>(reinterpret_cast<char *>(block) + 0xC) = block;
			Rva00031010Node *const newHead = *reinterpret_cast<Rva00031010Node **>(
				reinterpret_cast<char *>(allocator) + 0x440);
			newHead->m_link8 = newHead->m_linkC;
			Rva00031010Node *const binSentinel = reinterpret_cast<Rva00031010Node *>(
				reinterpret_cast<char *>(allocator) + 0x30);
			if (oldHead != binSentinel)
			{
				Rva00031010Node *const oldLast = binSentinel->m_linkC;
				oldHead->m_link8 = binSentinel;
				oldHead->m_linkC = oldLast;
				binSentinel->m_linkC = oldHead;
				oldLast->m_link8 = oldHead;
			}
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return true;
		}
	}

	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return false;
}


} }
