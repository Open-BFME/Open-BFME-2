// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva00213925@Rva000427195@@QAE?AUInsertRet00212A5A@@PBX@Z retail 0x00213925 36 bytes.
// Hashtable insert with grow: loads count at +0x10 inc calls pinned grow
// rva00212858 at 0x00212858 then tail-returns rowed insert rva00212A5A at
// 0x00212A5A with the same hidden return and key. Class proven by +0x10
// count and both callee owners. Callers at 0x00213E05 0x002140B8 0x00214133 0x002141AE.
// Evidence: callees 0x00212858 pinned 0x00212A5A rowed ret 8 struct-return.
// Precedent: Code/GameEngine/Source/GameClient/Rva001F93A3Insert.cpp.
#include "ascii_string.h"

#pragma pack(push, 1)
struct InsertRet00212A5A
{
	InsertRet00212A5A(void *node, void *owner, unsigned char found)
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
	InsertRet00212A5A rva00212A5A(const void *key);
	InsertRet00212A5A rva00213925(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet00212A5A Rva000427195::rva00213925(const void *key)
{
	rva00212858(m_numElements + 1);
	return rva00212A5A(key);
}
