// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00223A9F@Rva00223A9F@@QAEPAXPBVAsciiString@@@Z @0x00223A9F 37B
// Find-payload over table at +0x90 via rowed Iter find 0x0041534B.
// Evidence: add ecx 0x90 then call rowed Rva00056F61::rva0041534B with hidden
// Iter out {node table}; null node returns 0 else payload at node+8. Same shape
// as callers at 0x00223D02 and 0x002AE98B and neighbour +0x90 thunk 0x00223A94.
// Caller 0x005B232E in 0x005B2295. Adjacent to 0x00223A94 so same offset.
#include "ascii_string.h"

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

class Rva00223A9F
{
public:
	void *rva00223A9F(const AsciiString *key);

	char m_pad[0x90];
	Rva00056F61 m_table;
};

void *Rva00223A9F::rva00223A9F(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node == 0)
		return 0;
	return *(void **)((char *)it.m_node + 8);
}
