// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva001F93A3@Rva000427195@@QAE?AUInsertRet001F8F2A@@PBX@Z retail 0x001F93A3 36 bytes.
// Hashtable insert with grow: loads count at +0x10 inc calls pinned grow
// rva00212858 at 0x00212858 then tail-returns rowed insert rva001F8F2A at
// 0x001F8F2A with the same hidden return and key. Class proven by +0x10
// count and both callee owners. Callers at 0x001FA467 0x001FC2DF 0x001FCFC6.
// Evidence: callees 0x00212858 pinned 0x001F8F2A rowed ret 8 struct-return.
// Precedent: Code/GameEngine/Source/GameClient/Rva0041557AInsert.cpp.
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
	void rva00212858(unsigned int newSize);
	InsertRet001F8F2A rva001F8F2A(const void *key);
	InsertRet001F8F2A rva001F93A3(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet001F8F2A Rva000427195::rva001F93A3(const void *key)
{
	rva00212858(m_numElements + 1);
	return rva001F8F2A(key);
}
