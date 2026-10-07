// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// CreateAHeroManager::CreateAHeroSubClass::rva0021BD22 @0x0021BD22 31B (unnamed in
// WB; the attribute lookup WB's CreateAHeroSubClass::GetAttributeMinValue calls)
// __thiscall map-find wrapper: map<int,int> at +0x54, returns &value (node+0x14)
// or null via rowed _M_find 0x00388F63. Evidence: ecx+0x54 map, lea/push key,
// cmp found vs [map], je null else add 0x14, ret 4; callers 0x0021BDD3/0x0021BDFB.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class CreateAHeroManager
{
public:
	struct CreateAHeroSubClass;
};

struct CreateAHeroManager::CreateAHeroSubClass
{
	char pad[0x54];
	_STL::map<int, int> m_map;
	int *rva0021BD22(int key) const;
};

int *CreateAHeroManager::CreateAHeroSubClass::rva0021BD22(int key) const
{
	_STL::map<int, int> &map = const_cast<_STL::map<int, int> &>(m_map);
	_STL::map<int, int>::iterator it = map.find(key);
	if (it != map.end())
		return &(*it).second;
	return 0;
}
