// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva002E01F7@Rva000427195@@QAE?AUInsertRet002E01F7@@PBX@Z, retail 0x002E01F7 124B.
// Hashtable insert_unique for the AsciiString-keyed 12-byte node family
// (next+pair) shared with rowed NewNode 0x002230FF and rowed bucketIndex
// 0x00223149. Buckets at +4/+8, count at +0x10 (inc shape). Walks the bucket
// chain with rowed StringBase compare 0x000069D6; on miss allocates via rowed
// ?rva002230FF@Rva002230FF@@QAEPAXPBX@Z (same 12B node) and links it; fills
// the 9-byte pair<iterator,bool> out-param (node+table+found) and returns it
// in eax. Caller at 0x002E0372. Same 124B shape as rva00212A5A rva001F8F2A
// rva0041539F. Evidence: ret-8 thiscall with hidden return at +8 and key at
// +0xC (pair* doubling as AsciiString*).
#include "ascii_string.h"


#pragma pack(push, 1)
struct InsertRet002E01F7
{
	InsertRet002E01F7(void *node, void *owner, unsigned char found)
		: m_node(node), m_owner(owner), m_found(found) {}
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};
#pragma pack(pop)

class Rva002230FF
{
public:
	void *rva002230FF(const void *src);
};

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *name);
	void rva00212858(unsigned int newSize);
	InsertRet002E01F7 rva002E01F7(const void *key);
	InsertRet002E01F7 rva002E035B(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet002E01F7 Rva000427195::rva002E01F7(const void *key)
{
	int bucket = bucketIndex((const AsciiString *)key);
	void *head = m_beginBuckets[bucket];
	void *cur = head;
	if (cur != 0)
	{
		do
		{
			if (((const StringBase<char> *)((const char *)cur + 4))->compare(*(const StringBase<char> *)key) == 0)
				return InsertRet002E01F7(cur, this, 0);
			cur = *(void **)cur;
		} while (cur != 0);
	}
	void *node = ((Rva002230FF *)this)->rva002230FF(key);
	*(void **)node = head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return InsertRet002E01F7(node, this, 1);
}

InsertRet002E01F7 Rva000427195::rva002E035B(const void *key)
{
	rva00212858(m_numElements + 1);
	return rva002E01F7(key);
}
