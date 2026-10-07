// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva0046ACF6@Rva0046ACF6@@QAEHH@Z, retail 0x0046ACF6 34B.
// Map<int int> lookup at this+0x17C via rowed _M_find 0x00388F63: found
// returns second at node+0x14 else 0. Evidence: 12 callers push Object ID
// at +0x74 (e.g. 0x0046BCA7 0x005845D6 0x005860F6) and use return as slot
// index (imul 0x1C/0x54 with jl bounds check). BFME1 donor
// BfmeAODHordeContainOwner::bfmeGetMemberIndex does the same find-or-zero
// over m_memberIndices. Honest address name; owner unproven.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Rva0046ACF6
{
public:
	int rva0046ACF6(int key);

private:
	char m_pad[0x17C];
	_STL::map<int, int> m_map;
};

int Rva0046ACF6::rva0046ACF6(int key)
{
	_STL::map<int, int>::iterator it = m_map.find(key);
	if (it != m_map.end())
		return (*it).second;
	return 0;
}
