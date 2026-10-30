// cl: /EHsc /MD /Ireference/shims/bfme2_ascii
// ??1Rva003F0C6C@@QAE@XZ retail 0x003F0C6C 53B
// Non-virtual dtor destroying two StringBase<char> members at +0 and +4
// via rowed releaseBuffer 0x00036410 (reverse order +4 then +0) with
// __EH_prolog frame 0x00629188. Evidence: two releaseBuffer calls with
// lea ecx,[esi+4] then mov ecx,esi plus and/or EH states; no vptr store;
// callers at 0x003F1183 0x003F1A4F; neighbour 0x003F0442 image getter.
// Honest Rva name following Rva00466E23 precedent.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"


class Rva003F0C6C
{
public:
	~Rva003F0C6C();
private:
	StringBase<char> m_00;
	StringBase<char> m_04;
};
Rva003F0C6C::~Rva003F0C6C()
{
}
