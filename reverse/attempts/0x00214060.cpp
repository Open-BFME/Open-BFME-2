// ?rva00214060@Rva00214060@@QAEPAVRva003F9FA9@@ABVAsciiString@@@Z
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ?rva00214060@Rva00214060@@QAEPAVRva003F9FA9@@ABVAsciiString@@@Z @0x00214060 123B
// Factory method: news a 0x30-byte Rva003F9FA9 from AsciiString arg, copies arg
// to a temp for hashtable insert at this+0x26c, returns new object.
// Evidence: callees operator new 0x0002FDA0 Rva003F9FA9 ctor 0x003F9FA9
// StringBase copy 0x000365F0 insert 0x00213925 releaseBuffer 0x00036410 all
// rowed; caller 0x003F9F49; container offset 0x26c.
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
	InsertRet00212A5A rva00213925(const void *key);
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

class Rva003F9FA9
{
public:
	Rva003F9FA9(const AsciiString &s);
	char m_pad[0x30];
};

class Rva00214060
{
public:
	Rva003F9FA9 *rva00214060(const AsciiString &s);
	char m_pad00[0x26c];
	Rva000427195 m_map;
};

// ?rva00214060@Rva00214060@@QAEPAVRva003F9FA9@@ABVAsciiString@@@Z present-unmatched
Rva003F9FA9 *Rva00214060::rva00214060(const AsciiString &s)
{
	const AsciiString *ps = &s;
	Rva003F9FA9 *obj = new Rva003F9FA9(*ps);
	const AsciiString tmp(*ps);
	m_map.rva00213925(&tmp);
	return obj;
}
