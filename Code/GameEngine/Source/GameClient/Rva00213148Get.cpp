// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00213148@Rva00213148@@QAEPAXPBVAsciiString@@@Z, retail 0x00213148 (41B).
// Lookup in the embedded Rva00056F61 bucket table at +0x294 via rowed
// iterator find 0x0041534B. Returns payload at node+8 or null. Sibling of
// 0x002130F6 (+0x26c) and 0x0021311F (+0x280) same recipe. Caller at
// 0x004FC1A8. Chain over 0x0041534B. Owner unproven so honest-address.
#include "ascii_string.h"
class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};
class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};
class Rva00213148
{
public:
	void *rva00213148(const AsciiString *key);
private:
	char m_pad[0x294];
	Rva00056F61 m_table;
};
void *Rva00213148::rva00213148(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node != 0)
		return *(void **)((char *)it.m_node + 8);
	return 0;
}
