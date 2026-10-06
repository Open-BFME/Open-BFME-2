// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003F7B59@Rva003F7B59@@QAEPAXPBVAsciiString@@H@Z @0x003F7B59 91B
// Eva bucket add: builds a pair<const AsciiString,BfmePod8>{key,{val,0}} on
// the stack, ensures via rowed 0x003F797C on table at +8, bumps node ref at
// +0xc. Evidence: rowed pair ctor 0x003ED3F0, rowed insert 0x003F797C and
// rowed releaseBuffer 0x00036410; caller at 0x005C4590.
#include <map>
#include "ascii_string.h"

struct BfmePod8
{
	int a[2];
};

class Rva000427195
{
public:
	void *rva003F797C(void *out, const AsciiString *key);
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	int m_pad0C;
	int m_size;
};

struct EvaBucketNode
{
	EvaBucketNode *m_next;
	AsciiString m_name;
	int m_val0;
	int m_val1;
};

struct EvaBucketOut
{
	void *m_node;
	void *m_owner;
	unsigned char m_inserted;
};

class Rva003F7B59
{
public:
	void *rva003F7B59(const AsciiString *key, int val);
	char m_pad[8];
	Rva000427195 m_table;
};

void *Rva003F7B59::rva003F7B59(const AsciiString *key, int val)
{
	// Retail builds BfmePod8 {val,0} in the tail of the outgoing
	// insert-result slots (out+4/out+8): the union fixes that overlap so
	// the frame stays 0x18 like retail (high word zeroed first).
	union
	{
		EvaBucketOut out;
		struct
		{
			int m_unusedNode;
			BfmePod8 pod;
		} in;
	} u;
	u.in.pod.a[1] = 0;
	u.in.pod.a[0] = val;
	((Rva000427195 *)((char *)this + 8))->rva003F797C(&u.out, (const AsciiString *)&_STL::pair<const AsciiString, BfmePod8>(*key, u.in.pod));
	EvaBucketNode *node = (EvaBucketNode *)u.out.m_node;
	node->m_val1++;
	return node;
}
