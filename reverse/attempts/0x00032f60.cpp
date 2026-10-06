// ?rva00032F60@GeneralAllocator@Allocator@EA@@QAEPBUBlockInfo@23@PAXH@Z
// partial score=0.3 date=2026-10-06
// Banked reconstruction attempt for report-next traversal.
// Requires the target layouts declared in memory_pool.cpp.
// ?rva00032F60@GeneralAllocator@Allocator@EA@@QAEPBUBlockInfo@23@PAXH@Z
// The report loop at 0x353F0 passes this allocator, a Snapshot, and the block
// mask. Target reads fix the report state at Snapshot+0x10..0x20, returns the
// entry at +0x24, and traverses the allocator sentinel at +0x448. The helper
// at 0x32EC0 fills each returned BlockInfo; its name and semantics remain
// address-derived from this call and the target field writes.
const BlockInfo *GeneralAllocator::rva00032F60(void *context, int blockTypes)
{
	Snapshot *report = (Snapshot *)context;
	if (report == 0 || report->m_magic != 0x534E4150)
		return 0;
	register unsigned int mask = (unsigned int)blockTypes;
	if (report->m_state[2] != 0)
	{
		mask &= (unsigned int)report->m_arg2;
		ListNode *node = (ListNode *)report->m_values[0];
		while (node != (ListNode *)((char *)this + 0x448))
		{
		unsigned int end = (unsigned int)node + node->m_size - 0x10;
		unsigned int block = report->m_values[1];
		if (block == 0)
			block = node->m_unk0;
		else
			block += *(unsigned int *)(block + 4) & 0x7FFFFFF8;
		report->m_values[1] = block;
		while (block != end)
		{
			unsigned int header = *(unsigned int *)(block + 4);
			if ((blockTypes & 0x10) != 0 || (header & 4) == 0)
			{
				unsigned int size = header & 0x7FFFFFF8;
				unsigned char allocated = (unsigned char)(*(unsigned char *)(block + size + 4) & 1);
				if ((header & 0x80000000) != 0)
					allocated = 0;
				if ((blockTypes & 6) == 6 || ((blockTypes & 2) != 0 && allocated != 0) ||
					((blockTypes & 4) != 0 && allocated == 0))
				{
					BlockInfo *info = (BlockInfo *)((char *)context + 0x24);
					rva00032EC0((const void *)block, info);
					return info;
				}
			}
			block += *(unsigned int *)(block + 4) & 0x7FFFFFF8;
			report->m_values[1] = block;
		}

		if (node->m_size == 0)
			break;
		node = node->m_next;
		report->m_values[0] = (unsigned int)node;
		if (node == (ListNode *)((char *)this + 0x448))
		{
			report->m_values[1] = 0;
			break;
		}
		report->m_values[1] = 0;
	}

		if ((blockTypes & 2) != 0)
	{
		unsigned int external = report->m_values[2];
		if (external != (unsigned int)((char *)this + 0x49C))
		{
			BlockInfo *info = (BlockInfo *)((char *)context + 0x24);
			rva00032EC0((const void *)(external - *(unsigned int *)external), info);
			report->m_values[2] = *(unsigned int *)(external + 0x0C);
			return info;
		}
	}
	}
	while (report->m_values[4] < report->m_values[3])
	{
		BlockInfo *entry = (BlockInfo *)((char *)context + 0x24 + report->m_values[4] * 0x14);
		if ((mask & entry->m_blockType) != 0)
		{
			++report->m_values[4];
			return entry;
		}
		++report->m_values[4];
	}
	return 0;
}

