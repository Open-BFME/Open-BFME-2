// ?rva000334A0@GeneralAllocator@Allocator@EA@@QAEPAXI@Z
// partial score=0.5 date=2026-10-07
// Requires the offset-derived ListNode view with size at +4 and committed limit at +8; the FreeChunk overlay uses prev-size/size/next/prev at +0/+4/+8/+C.
// Allocator overlay places the free-bin sentinel at +0x30 and head pointer at +0x440.
// Uses VirtualAlloc at IAT 0xBBA1A4 and the partial helper call at 0x32B00.
// ?rva000334A0@GeneralAllocator@Allocator@EA@@QAEPAXI@Z present-unmatched
// The sole direct caller passes a byte count and treats the return as a chunk
// header. Retail walks the core list at +0x448, commits within a segment, and
// otherwise asks 0x32B00 for a new core. Segment/list labels remain
// offset-derived; the broader allocation algorithm is reconstructed from the
// target's field accesses and control flow.
void *GeneralAllocator::rva000334A0(volatile unsigned int size)
{
	struct Scratch
	{
		char pad[3];
		bool moveHead;
		FreeChunk *oldHead;
		FreeChunk *tail;
	};
	register GeneralAllocator *allocator = this;
	volatile Scratch scratch;
	scratch.moveHead = false;
	register unsigned int commit = 0;
	register ListNode *segment = allocator->m_sentinel.m_next;
	FreeChunk *chunk = 0;
	while (segment != &m_sentinel)
	{
		unsigned int used = segment->m_size;
		unsigned int capacity = segment->m_size8;
		unsigned int available = capacity - used;
		if (size > available)
		{
			segment = segment->m_next;
			continue;
		}

		commit = size;
		unsigned int granularity = *(unsigned int *)((char *)allocator + 0x4DC);
		if (commit < granularity)
			commit = granularity;
		if (commit > available)
			commit = available;
		if (VirtualAlloc((char *)segment + used, commit, 0x1000, 4) == 0)
			segment->m_size8 = used;

		if (used != 0)
		{
			FreeChunk *last = (FreeChunk *)((char *)segment + used - 0x10);
			if ((last->m_size & 1) != 0)
			{
				chunk = last;
				chunk->m_size = commit | 1;
			}
			else
			{
				chunk = (FreeChunk *)((char *)last - last->m_prevSize);
				chunk->m_next->m_prev = chunk->m_prev;
				chunk->m_prev->m_next = chunk->m_next;
				unsigned int total = last->m_prevSize + commit;
				chunk->m_size = total | 1;
				scratch.moveHead = chunk == allocator->m_head440;
				FreeChunk *fence = (FreeChunk *)((char *)chunk + total);
				fence->m_prevSize = total;
				fence->m_size = 8;
				*(unsigned int *)((char *)fence + 8) = 8;
				*(unsigned int *)((char *)fence + 12) = 9;
			}
		}
		else
		{
			unsigned char *data = (unsigned char *)(((unsigned int)segment + 0x27) & 0xFFFFFFF8);
			segment->m_unk0 = (unsigned int)data;
			unsigned int blockSize = (unsigned int)((char *)segment + commit - (char *)data);
			FreeChunk *first = (FreeChunk *)data;
			first->m_prevSize = 0;
			first->m_size = blockSize | 1;
			FreeChunk *fence = (FreeChunk *)(data + (blockSize & 0x7FFFFFF8));
			fence->m_prevSize = blockSize & 0x7FFFFFF8;
			fence->m_size = 8;
			*(unsigned int *)((char *)fence + 8) = 8;
			*(unsigned int *)((char *)fence + 12) = 9;
		}
		segment->m_size = used + commit;
		if (chunk != 0)
			break;
		break;
	}

	if (chunk == 0)
	{
		if (*(void **)((char *)allocator + 0x4AC) != 0)
			return 0;
		chunk = (FreeChunk *)allocator->rva00032B00(size);
		if (chunk == 0)
			return 0;
		scratch.oldHead = allocator->m_head440;
		allocator->m_head440 = chunk;
		chunk->m_prev = chunk;
		chunk->m_next = chunk->m_prev;
		FreeChunk *bin = &allocator->m_bin30;
		if (chunk->m_prev != bin)
		{
			scratch.tail = bin->m_prev;
			scratch.oldHead->m_next = bin;
			scratch.oldHead->m_prev = scratch.tail;
			bin->m_prev = scratch.oldHead;
			scratch.tail->m_next = scratch.oldHead;
		}
		scratch.moveHead = true;
	}

	unsigned int oldSize = chunk->m_size & 0x7FFFFFF8;
	if (oldSize <= size)
		return 0;
	chunk->m_size = size | 1;
	FreeChunk *remainder = (FreeChunk *)((char *)chunk + size);
	unsigned int remainderSize = oldSize - size;
	remainder->m_prevSize = size;
	remainder->m_size = remainderSize;
	*(unsigned int *)((char *)remainder + remainderSize) = remainderSize;
	if (scratch.moveHead)
	{
		allocator->m_head440 = remainder;
		remainder->m_prev = remainder;
		remainder->m_next = remainder->m_prev;
	}
	else
	{
		FreeChunk *bin = &allocator->m_bin30;
		scratch.tail = bin->m_prev;
		remainder->m_next = bin;
		remainder->m_prev = scratch.tail;
		scratch.tail->m_next = remainder;
		bin->m_prev = remainder;
	}
	return chunk;
}

