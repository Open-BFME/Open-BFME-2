// cl: /Ireference/shims/bfme2_ascii /O1 /GX-
// stlport
// ?rva0059A71C@Rva0059A71C@@QAEXPAUArg@@@Z @0x0059A71C (90B)
// Thiscall takes one pointer arg with AsciiString at +0x14. Loads chain
// [this+0x14]->+0x2ec->+0x30 for other string or TheEmptyString then
// arg+0x14 compare via rowed StringBase compare. If equal return. Else
// _STL find CreateAHeroData range [this+8 this+0xc) for arg and if found
// return else vector ModuleData push_back at this+8. Ret 4. Caller
// 0x0059A85C unblocks 0x0059A85C. Evidence unlock lane plus compare find
// push_back rows plus TheEmptyString extern plus ret N thiscall.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include <algorithm>
#include "ascii_string.h"
class CreateAHeroData;
class ModuleData;
struct Leaf
{
	char m_pad[0x14];
	StringBase<char> m_name;
};
struct Mid2
{
	char m_pad[0x30];
	Leaf *m_leaf;
};
struct Mid1
{
	char m_pad[0x2ec];
	Mid2 *m_mid;
};
struct Arg
{
	char m_pad[0x14];
	StringBase<char> m_name;
};
class Rva0059A71C
{
public:
	void rva0059A71C(Arg *arg);
private:
	char m_pad0[8];
	_STL::vector<const ModuleData *> m_vec;
	Mid1 *m_obj;
};
void Rva0059A71C::rva0059A71C(Arg *arg)
{
	Mid2 *mid = m_obj->m_mid;
	Leaf *leaf = mid->m_leaf;
	StringBase<char> *other;
	if (leaf == 0)
		other = (StringBase<char> *)&AsciiString::TheEmptyString;
	else
		other = &leaf->m_name;
	if (arg->m_name.compare(*other) == 0)
		return;
	CreateAHeroData **beg = (CreateAHeroData **)m_vec.begin();
	CreateAHeroData **end = (CreateAHeroData **)m_vec.end();
	CreateAHeroData **found = _STL::find(beg, end, (CreateAHeroData * const &)arg);
	if (found != end)
		return;
	m_vec.push_back((const ModuleData * const &)arg);
}
