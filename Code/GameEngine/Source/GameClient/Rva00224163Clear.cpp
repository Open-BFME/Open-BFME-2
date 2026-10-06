// cl: /MD
// ?rva00224163@Rva00224163@@QAEXXZ @0x00224163 73B
// Hash-bucket clear over the table at +4/+8 with count at +0x10.
// Evidence: chain lane calls rowed free 0x00223898; layout matches rowed Rva00223591 and twin clear 0x003A2A41; caller at 0x00224989.
class Rva00223898
{
public:
	void rva00223898(void *node);
};

class Rva00224163
{
public:
	void rva00224163();
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void Rva00224163::rva00224163()
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2); ++i)
	{
		void *cur = m_beginBuckets[i];
		while (cur != 0)
		{
			void *next = *(void **)cur;
			((Rva00223898 *)this)->rva00223898(cur);
			cur = next;
		}
		m_beginBuckets[i] = 0;
	}
	m_numElements = 0;
}
