// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva00212A5A@Rva000427195@@QAE?AUInsertRet00212A5A@@PBX@Z, retail 0x00212A5A 124B.
// Hashtable insert_unique for the AsciiString-keyed 12-byte node family
// (next+pair) shared with new_node 0x00212354 and resize 0x00212858.
// Buckets at +4/+8 (proven by rowed bucketIndex 0x00223149), count at +0x10
// (inc shape). Walks the bucket chain with rowed StringBase compare
// 0x000069D6; on miss allocates via the pinned member twin of free NewNode
// 0x00212354 (same 12B node; free body ignores the dead this in ecx) and
// links it; fills the 9-byte pair<iterator,bool> out-param (node+table+found)
// and returns it in eax. Caller at 0x0021393C. Evidence: ret-8 thiscall with
// hidden return at +8 and key at +0xC (pair* doubling as AsciiString*).
#include "ascii_string.h"


#include "../../Include/GameClient/InsertRet00212A5A.h"

#include "../../Include/GameLogic/Rva000427195.h"

InsertRet00212A5A Rva000427195::rva00212A5A(const void *key)
{
	int bucket = bucketIndex((const AsciiString *)key);
	void *head = m_beginBuckets[bucket];
	void *cur = head;
	if (cur != 0)
	{
		do
		{
			if (((const StringBase<char> *)((const char *)cur + 4))->compare(*(const StringBase<char> *)key) == 0)
				return InsertRet00212A5A(cur, this, 0);
			cur = *(void **)cur;
		} while (cur != 0);
	}
	void *node = rva00212354(key);
	*(void **)node = head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return InsertRet00212A5A(node, this, 1);
}
