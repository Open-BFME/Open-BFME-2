// cl: /MD
// ?rva0022DD19@Rva0022DD19@@QAEXXZ @0x0022DD19 73B
// Hash-bucket clear over the table at +4/+8 with count at +0x10.
// Evidence: chain lane calls rowed free 0x0022DB72; layout matches rowed
// ?rva0022DB29 0x0022DB29 and twin clear ?rva00224163 0x00224163; caller at
// 0x0022DEBD; unblocks 0x0022DEA8.
class Rva0022DB72
{
public:
	void rva0022DB72(void *node);
};

class Rva0022DD19
{
public:
	void rva0022DD19();
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void Rva0022DD19::rva0022DD19()
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2); ++i)
	{
		void *cur = m_beginBuckets[i];
		while (cur != 0)
		{
			void *next = *(void **)cur;
			((Rva0022DB72 *)this)->rva0022DB72(cur);
			cur = next;
		}
		m_beginBuckets[i] = 0;
	}
	m_numElements = 0;
}
