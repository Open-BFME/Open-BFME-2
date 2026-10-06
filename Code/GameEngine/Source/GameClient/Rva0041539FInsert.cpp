// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva0041539F@Rva000427195@@QAE?AUInsertRet0041539F@@PBX@Z, retail 0x0041539F 124B.
// Hashtable insert_unique for the AsciiString-keyed 12-byte node family
// (next+pair) shared with new_node 0x004152E6. Buckets at +4/+8 (proven by
// rowed bucketIndex 0x00223149), count at +0x10 (inc shape). Walks the bucket
// chain with rowed StringBase compare 0x000069D6; on miss allocates via the
// pinned member twin of free NewNode 0x004152E6 (same 12B node; free body
// ignores the dead this in ecx) and links it; fills the 9-byte
// pair<iterator,bool> out-param (node+table+found) and returns it in eax.
// Caller at 0x00415591. Same shape as rowed 0x00212A5A. Evidence: ret-8
// thiscall with hidden return at +8 and key at +0xC (pair doubling as
// AsciiString). Chain over just-landed 0x004152E6.
#include "ascii_string.h"


#pragma pack(push, 1)
struct InsertRet0041539F
{
	InsertRet0041539F(void *node, void *owner, unsigned char found)
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
	void *rva004152E6(const void *src);
	InsertRet0041539F rva0041539F(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet0041539F Rva000427195::rva0041539F(const void *key)
{
	int bucket = bucketIndex((const AsciiString *)key);
	void *head = m_beginBuckets[bucket];
	void *cur = head;
	if (cur != 0)
	{
		do
		{
			if (((const StringBase<char> *)((const char *)cur + 4))->compare(*(const StringBase<char> *)key) == 0)
				return InsertRet0041539F(cur, this, 0);
			cur = *(void **)cur;
		} while (cur != 0);
	}
	void *node = rva004152E6(key);
	*(void **)node = head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return InsertRet0041539F(node, this, 1);
}
