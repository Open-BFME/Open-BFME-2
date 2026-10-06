// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva001F8F2A@Rva000427195@@QAE?AUInsertRet001F8F2A@@PBX@Z, retail 0x001F8F2A 124B.
// Hashtable insert_unique for the AsciiString-keyed 12-byte node family
// (next+pair) shared with NewNode 0x002ACFD6 and bucketIndex 0x00223149.
// Buckets at +4/+8, count at +0x10 (inc shape). Walks the bucket chain with
// rowed StringBase compare 0x000069D6; on miss allocates via member twin
// ?rva002ACFD6@Rva000427195@@QAEPAXPBX@Z pinned at 0x002ACFD6 (same 12B node;
// free body ignores the dead this in ecx) and links it; fills the 9-byte
// pair<iterator,bool> out-param (node+table+found) and returns it in eax.
// Caller at 0x001F93BA. Same 124B shape as rva00212A5A and rva0041539F.
#include "ascii_string.h"


#pragma pack(push, 1)
struct InsertRet001F8F2A
{
	InsertRet001F8F2A(void *node, void *owner, unsigned char found)
		: m_node(node), m_owner(owner), m_found(found) {}
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};
#pragma pack(pop)

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *name);
	void *rva002ACFD6(const void *src);
	InsertRet001F8F2A rva001F8F2A(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet001F8F2A Rva000427195::rva001F8F2A(const void *key)
{
	int bucket = bucketIndex((const AsciiString *)key);
	void *head = m_beginBuckets[bucket];
	void *cur = head;
	if (cur != 0)
	{
		do
		{
			if (((const StringBase<char> *)((const char *)cur + 4))->compare(*(const StringBase<char> *)key) == 0)
				return InsertRet001F8F2A(cur, this, 0);
			cur = *(void **)cur;
		} while (cur != 0);
	}
	void *node = rva002ACFD6(key);
	*(void **)node = head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return InsertRet001F8F2A(node, this, 1);
}
