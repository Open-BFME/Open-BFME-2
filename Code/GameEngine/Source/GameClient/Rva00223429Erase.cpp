// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00223429@Rva000427195@@QAEHPBVAsciiString@@@Z @0x00223429 145B
// Erase-all by AsciiString key over the Eva bucket vector. Buckets at +4,
// count at +0x10 (proven by rowed bucketIndex 0x00223149 and inserts
// 0x001F8F2A/0x00212A5A/0x0041539F). Walks the chain with rowed StringBase
// compare 0x000069D6, unlinks via prev node, frees via rowed 0x001FD9EF
// (ignores this, called with table this like Clear 0x003A2A41), head last
// via saved byte offset. Returns removed count. Callers 0x000A810D 0x00224BB6.
#include "ascii_string.h"


class Rva001FD9EF
{
public:
	void rva001FD9EF(void *node);
};

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *name);
	int rva00223429(const AsciiString *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

int Rva000427195::rva00223429(const AsciiString *key)
{
	int bucket = bucketIndex(key);
	void *head = m_beginBuckets[bucket];
	int removed = 0;
	if (head != 0)
	{
		void *prev = head;
		void *cur = *(void **)head;
		while (cur != 0)
		{
			if (((StringBase<char> *)((char *)cur + 4))->compare(*(const StringBase<char> *)(const void *)key) == 0)
			{
				*(void **)prev = *(void **)cur;
				((Rva001FD9EF *)this)->rva001FD9EF(cur);
				cur = *(void **)prev;
				++removed;
				--m_numElements;
			}
			else
			{
				prev = cur;
				cur = *(void **)cur;
			}
		}
		if (((StringBase<char> *)((char *)head + 4))->compare(*(const StringBase<char> *)(const void *)key) == 0)
		{
			m_beginBuckets[bucket] = *(void **)head;
			((Rva001FD9EF *)this)->rva001FD9EF(head);
			++removed;
			--m_numElements;
		}
	}
	return removed;
}
