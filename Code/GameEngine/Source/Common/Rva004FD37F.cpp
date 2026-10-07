// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FD5C7@Rva004FD37F@@QBE_NPAVRva002E1001@@@Z @0x004FD5C7 76B.
// Const multimap<int int> query at this+0x50 looping equal_range of key at arg+0x34
// calling rowed rva004FC8D6 and returning true on first true. Evidence: rowed
// equal_range 0x004FCD6D _M_increment 0x00024250 rva004FC8D6 0x004FC8D6; map at
// +0x50 matches sibling Rva004FD37F 0x50/0x74 spacing vs LivingWorldScenario::Scenario 0x5c/0x80
// and Rva004FD448 0x68/0x8c; caller 0x002B9F08; neighbours carry /O1 /GX /MD.
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
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class ModuleData;

class Rva002E1001
{
public:
	char m_pad00[0x34];
	int m_key;
};

class Rva004FC8D6
{
public:
	bool rva004FC8D6(Rva002E1001 *p);
};

class Rva004FD37F
{
public:
	bool rva004FD5C7(Rva002E1001 *p) const;
	void rva004FD37F(const ModuleData *p);
private:
	char m_pad00[0x50];
	_STL::multimap<int, int> m_map;
	char m_pad1[0x74 - 0x50 - sizeof(_STL::multimap<int, int>)];
	_STL::vector<const ModuleData *> m_vec;
};

struct Rva004FCD49Vec
{
	void *vtbl;
	_STL::vector<int> m_vec;
	int m_10;
};

bool Rva004FD37F::rva004FD5C7(Rva002E1001 *p) const
{
	int key = p->m_key;
	_STL::pair<_STL::multimap<int, int>::const_iterator, _STL::multimap<int, int>::const_iterator> r = m_map.equal_range(key);
	for (_STL::multimap<int, int>::const_iterator it = r.first; it != r.second; ++it) {
		Rva004FC8D6 *cand = (Rva004FC8D6 *)(*it).second;
		if (cand->rva004FC8D6(p))
			return true;
	}
	return false;
}

// ?rva004FD37F@Rva004FD37F@@QAEXPBVModuleData@@@Z @0x004FD37F 99B.
// Multimap<int int> insert per int plus vector<ModuleData*> push_back at
// 0x50/0x74 spacing (sibling 0x004FD3E2 is 0x5c/0x80 102B). Evidence: caller
// 0x004FD752 in Rva003F9258Siblings.cpp; rowed insert_equal 0x004FF876 and
// rowed push_back 0x004DFCB0; neighbours carry /O1 /GX /MD.
void Rva004FD37F::rva004FD37F(const ModuleData *p)
{
	if (!p)
		return;
	const _STL::vector<int> &vec = ((const Rva004FCD49Vec *)p)->m_vec;
	for (unsigned int i = 0; i < vec.size(); ++i) {
		int v = vec[i];
		m_map.insert(_STL::multimap<int, int>::value_type(v, (int)p));
	}
	m_vec.push_back(p);
}
