// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva004E1A04@@QAE@XZ, RVA 0x004E1A04, 47B. Unlock lane: non-virtual dtor
// releasing two narrow StringBase members twice through rowed narrow
// releaseBuffer at 0x00036410, first call under EH state 0 then state -1.
// Callers at 0x004E1A87/0x0052BBBE/0x0052CEE6 plus jmps. Owner unproven so
// honest address-derived name.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"



class Rva004E1A04
{
public:
	~Rva004E1A04();
private:
	StringBase<char> m_a;
};

Rva004E1A04::~Rva004E1A04()
{
	m_a.~StringBase<char>();
}
