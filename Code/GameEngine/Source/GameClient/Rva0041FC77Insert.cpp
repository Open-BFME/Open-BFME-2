// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva0041FC77@Rva000427195@@QAE?AUInsertRet0041FA92@@PBX@Z @0x0041FC77 36B.
// Hash-map insert wrapper: reserve(count+1) via 0x00212858 then hashtable
// insert_unique 0x0041FA92. Buckets at +4, count at +0x10. Fills 9-byte
// pair<iterator,bool> out-param and returns it. Caller at 0x0041FCDE and
// 0x0041FDB4. Same shape as other Eva reserve-plus-insert wrappers.
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

class Rva000427195
{
public:
	void rva00212858(unsigned int newSize);
	InsertRet0041FA92 rva0041FA92(const void *key);
	InsertRet0041FA92 rva0041FC77(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet0041FA92 Rva000427195::rva0041FC77(const void *key)
{
	rva00212858(m_numElements + 1);
	return rva0041FA92(key);
}
