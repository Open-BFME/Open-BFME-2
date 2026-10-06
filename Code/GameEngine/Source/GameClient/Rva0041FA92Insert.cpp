// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva0041FA92@Rva000427195@@QAE?AUInsertRet0041FA92@@PBX@Z @0x0041FA92 124B.
// Hashtable insert_unique for the AsciiString-keyed 12-byte node family
// shared with NewNode 0x0041FA34 and bucketIndex 0x00223149. Buckets at
// +4, count at +0x10. Walks chain with StringBase compare 0x000069D6; on
// miss allocates via twin ?rva0041FA34@Rva0041FA34@@QAEPAXPBX@Z and links
// it; fills 9-byte pair<iterator,bool> out-param and returns it. Caller at
// 0x0041FC8E. Same shape as rva001F8F2A at 0x001F8F2A.
#include "ascii_string.h"


#pragma pack(push, 1)
struct InsertRet0041FA92
{
	InsertRet0041FA92(void *node, void *owner, unsigned char found)
		: m_node(node), m_owner(owner), m_found(found) {}
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};
#pragma pack(pop)

class Rva0041FA34
{
public:
	void *rva0041FA34(const void *src);
};

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *name);
	InsertRet0041FA92 rva0041FA92(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet0041FA92 Rva000427195::rva0041FA92(const void *key)
{
	int bucket = bucketIndex((const AsciiString *)key);
	void *head = m_beginBuckets[bucket];
	void *cur = head;
	if (cur != 0)
	{
		do
		{
			if (((const StringBase<char> *)((const char *)cur + 4))->compare(*(const StringBase<char> *)key) == 0)
				return InsertRet0041FA92(cur, this, 0);
			cur = *(void **)cur;
		} while (cur != 0);
	}
	void *node = ((Rva0041FA34 *)this)->rva0041FA34(key);
	*(void **)node = head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return InsertRet0041FA92(node, this, 1);
}
