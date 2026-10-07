// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva004F7B42@Rva004F7B42@@QAEHHH@Z @ 0x004F7B42 (41B). Map array indexed by
// (a1+3) with imul 0xc stride matching 12-byte map, upper_bound via rowed
// _M_upper_bound 0x004FF471 then end compare [esi] and return node first
// +0x10 or -1. Evidence: ret 8 two args plus thiscall, same pattern as
// Rva004F76EA m_maps[5], callers 0x004F81CC and 0x005EAB20.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Rva004F7B42
{
public:
	int rva004F7B42(int a1, int a2);
private:
	_STL::map<int, int> m_maps[5];
};

int Rva004F7B42::rva004F7B42(int a1, int a2)
{
	_STL::map<int, int> *m = &m_maps[a1 + 3];
	_STL::map<int, int>::iterator it = m->upper_bound(a2);
	if (it != m->end())
		return it->first;
	return -1;
}
