// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva0041557A@Rva000427195@@QAE?AUInsertRet0041539F@@PBX@Z retail 0x0041557A 36 bytes.
// Hashtable insert with grow: loads count at +0x10, inc, calls rowed-pinned
// grow rva00212858 at 0x00212858, then tail-returns rowed insert rva0041539F
// at 0x0041539F with the same hidden return and key. Class proven by +0x10
// count and both callee owners; callers at 0x0041566A 0x00415DE3.
// Evidence: callees 0x00212858 pinned 0x0041539F rowed, ret 8 struct-return.
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
	void rva00212858(unsigned int newSize);
	InsertRet0041539F rva0041539F(const void *key);
	InsertRet0041539F rva0041557A(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet0041539F Rva000427195::rva0041557A(const void *key)
{
	rva00212858(m_numElements + 1);
	return rva0041539F(key);
}
