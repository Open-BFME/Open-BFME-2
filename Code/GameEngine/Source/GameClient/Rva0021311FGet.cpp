// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0021311F@Rva0021311F@@QAEPAXPBVAsciiString@@@Z, retail 0x0021311F (41B).
// Lookup in the embedded Rva00056F61 bucket table at +0x280 via rowed
// iterator find 0x0041534B. Returns payload at node+8 or null. Same shape as
// rowed Eva lookups 0x00411112. Caller at 0x004E065B. Chain over just-landed
// 0x0041534B. Owner unproven so honest-address class Rva0021311F. True path
// inline via if != 0 per codegen.
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
class Rva0021311F
{
public:
	void *rva0021311F(const AsciiString *key);
private:
	char m_pad[0x280];
	Rva00056F61 m_table;
};
void *Rva0021311F::rva0021311F(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node != 0)
		return *(void **)((char *)it.m_node + 8);
	return 0;
}
