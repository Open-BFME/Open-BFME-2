// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002130F6@Rva002130F6@@QAEPAXPBVAsciiString@@@Z, retail 0x002130F6 (41B).
// Lookup in the embedded Rva00056F61 bucket table at +0x26c via rowed
// iterator find 0x0041534B. Returns payload at node+8 or null. Sibling of
// rowed 0x0021311F (table at +0x280 same recipe). Caller at 0x00319362.
// Chain over 0x0041534B. Owner unproven so honest-address class Rva002130F6.
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
class Rva002130F6
{
public:
	void *rva002130F6(const AsciiString *key);
private:
	char m_pad[0x26c];
	Rva00056F61 m_table;
};
void *Rva002130F6::rva002130F6(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node != 0)
		return *(void **)((char *)it.m_node + 8);
	return 0;
}
