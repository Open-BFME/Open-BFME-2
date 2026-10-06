// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva002AE98B@Rva002AE98B@@QAEMPBVAsciiString@@@Z @0x002AE98B 45B: float accessor via rowed Rva00056F61::rva0041534B table at +0x294; null node returns BfmeZeroRange else payload float at node+8. Evidence: callee comment names 0x002AE98B add ecx 0x294 read node out+0 payload node+8 plus sibling Rva00223D02 table+0x48 pattern plus 3 unclaimed callers plus prev AICommandInterface next Rva002AF1ECDtor.
#include "ascii_string.h"

// The data ledger identifies the shared read-only operand as float +0.0.

struct Rva0041534BIter
{
	void *m_node;
	void *m_table;
};

class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

class Rva002AE98B
{
public:
	float rva002AE98B(const AsciiString *key);
private:
	char m_pad[0x294];
	Rva00056F61 m_table;
};

float Rva002AE98B::rva002AE98B(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node != 0)
		return *(float *)((char *)it.m_node + 8);
	return 0.0f;
}
