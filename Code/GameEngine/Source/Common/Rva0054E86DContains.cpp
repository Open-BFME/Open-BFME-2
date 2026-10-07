// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// ?rva0054E86D@Rva0054F434@@UAE_NH@Z @0x0054E86D 47B
// Rva0054F434 slot 10 (vtable 0x0086AA10) bool contains over set<int> at +0x58.
// Evidence: calls rowed _STL::find 0x0054E82C (set<int> const iterators) with
// begin at [header+8] end header; returns find != end via setne; chain from 0x0054E82C.
#include <set>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Rva0054F434
{
public:
	virtual bool rva0054E86D(int key);
private:
	unsigned char m_pad[0x54];
	_STL::set<int, _STL::less<int>, _STL::allocator<int> > m_set;
};

bool Rva0054F434::rva0054E86D(int key)
{
	_STL::set<int, _STL::less<int>, _STL::allocator<int> >::iterator it = _STL::find(m_set.begin(), m_set.end(), key);
	return it != m_set.end();
}
