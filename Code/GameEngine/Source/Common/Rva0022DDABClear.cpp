// cl: /MD
// ?rva0022DDAB@Rva0022DDAB@@QAEXXZ @0x0022DDAB 73B: hash-bucket clear over the table at +4/+8 with count at +0x10. Retail loops buckets and walks each chain calling just-landed free 0x0022DBAA then nulls the bucket. Same 73B shape as ?rva0022DD62 at 0x0022DD62. Evidence: chain packet calls just-landed 0x0022DBAA; caller at 0x0022DF2F; unblocks 0x0022DF1A.
class Rva0022DBAA
{
public:
	void rva0022DBAA(void *node);
};

class Rva0022DDAB
{
public:
	void rva0022DDAB();
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void Rva0022DDAB::rva0022DDAB()
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2); ++i)
	{
		void *cur = m_beginBuckets[i];
		while (cur != 0)
		{
			void *next = *(void **)cur;
			((Rva0022DBAA *)this)->rva0022DBAA(cur);
			cur = next;
		}
		m_beginBuckets[i] = 0;
	}
	m_numElements = 0;
}
