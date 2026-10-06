// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00223736@Rva00223591@@QAEHPBVAsciiString@@@Z @0x00223736 145B
// Erase-all by AsciiString key over the pair<TreeHintRef00222C5A> bucket vector. Buckets at +4 count at +0x10.
// Evidence: caller chain from 0x0022380B clear; rowed bucketIndex 0x00223149 plus rowed StringBase compare 0x000069D6 plus just-landed free-node 0x00223591; same shape as rowed ?rva00223429@Rva000427195@@QAEHPBVAsciiString@@@Z 0x00223429.
#include "ascii_string.h"

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *name);
};

class Rva00223591
{
public:
	int rva00223736(const AsciiString *key);
	void rva00223591(void *node);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

int Rva00223591::rva00223736(const AsciiString *key)
{
	int bucket = ((Rva000427195 *)this)->bucketIndex(key);
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
				rva00223591(cur);
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
			rva00223591(head);
			++removed;
			--m_numElements;
		}
	}
	return removed;
}
