// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002D06CA@Rva002D06CA@@QAEPAXPBVAsciiString@@@Z, retail 0x002D06CA (38B).
// Lookup in the embedded Rva00056F61 bucket table at +0x14 via rowed
// iterator find 0x0041534B. Returns payload at node+8 or null. Sibling of
// rowed 0x002130F6 (+0x26c) 0x0021311F (+0x280) 0x00213148 (+0x294) same
// recipe with 3-byte add encoding explaining 38B vs 41B. Callers at 0x001E0243
// and 0x001E052A via global 0x00DFF000 plus INI parse 0x0033947E and 209-function
// unlock fanout. Owner unproven so honest-address class Rva002D06CA.
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
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
	bool rva002D06AA(const AsciiString *key);
private:
	char m_pad[0x14];
	Rva00056F61 m_table;
};
void *Rva002D06CA::rva002D06CA(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node != 0)
		return *(void **)((char *)it.m_node + 8);
	return 0;
}
bool Rva002D06CA::rva002D06AA(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	return it.m_node != 0;
}
