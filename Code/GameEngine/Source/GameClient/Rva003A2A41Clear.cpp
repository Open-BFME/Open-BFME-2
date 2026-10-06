// cl: /MD
// ?rva003A2A41@Rva000427195@@QAEXXZ @0x003A2A41 73B
// Hash-bucket clear for the AsciiString-keyed table at +4/+8 with count at
// +0x10. Buckets proven by rowed bucketIndex 0x00223149 and insert
// 0x00212A5A; node free is rowed 0x001FD9EF which clears the key at +4 then
// frees. Called by 27 waiting 57B dtors that then free the bucket array.

class Rva001FD9EF
{
public:
	void rva001FD9EF(void *node);
};

class Rva000427195
{
public:
	void rva003A2A41();
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void Rva000427195::rva003A2A41()
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2); ++i)
	{
		void *cur = m_beginBuckets[i];
		while (cur != 0)
		{
			void *next = *(void **)cur;
			((Rva001FD9EF *)this)->rva001FD9EF(cur);
			cur = next;
		}
		m_beginBuckets[i] = 0;
	}
	m_numElements = 0;
}
