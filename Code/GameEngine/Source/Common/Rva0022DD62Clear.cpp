// cl: /MD
// ?rva0022DD62@Rva0022DD62@@QAEXXZ @0x0022DD62 73B: hash-bucket clear over the table at +4/+8 with count at +0x10. Retail loops buckets and walks each chain calling rowed free 0x0022DB8E then nulls the bucket. Same 73B shape as ?rva0022DD19 at 0x0022DD19. Evidence: chain packet calls just-landed 0x0022DB8E; caller at 0x0022DEF6; unblocks 0x0022DEE1.
class Rva0022DB8E
{
public:
	void rva0022DB8E(void *node);
};

class Rva0022DD62
{
public:
	void rva0022DD62();
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void Rva0022DD62::rva0022DD62()
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2); ++i)
	{
		void *cur = m_beginBuckets[i];
		while (cur != 0)
		{
			void *next = *(void **)cur;
			((Rva0022DB8E *)this)->rva0022DB8E(cur);
			cur = next;
		}
		m_beginBuckets[i] = 0;
	}
	m_numElements = 0;
}
