// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B86AA@Rva002B86AA@@QBE_NPAURva002B86AAKey@@PAURva002B86AAVal@@@Z @0x002B86AA 71B. Returns true if map at +0x13c has key a->+0x4c with mapped value == b->+0x14.
// Evidence: equal_range row at 0x004FCD6D plus _M_increment row at 0x00024250 plus ret 8 plus this+0x13c; neighbours are stlport WWLib TUs.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

struct Rva002B86AAKey
{
	unsigned char m_pad[0x4c];
	int m_code;
};

struct Rva002B86AAVal
{
	unsigned char m_pad[0x14];
	int m_value;
};

class Rva002B86AA
{
public:
	bool rva002B86AA(Rva002B86AAKey *a, Rva002B86AAVal *b) const;
private:
	unsigned char m_pad[0x13c];
	_STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > m_map;
};

bool Rva002B86AA::rva002B86AA(Rva002B86AAKey *a, Rva002B86AAVal *b) const
{
	int key = a->m_code;
	_STL::pair<_STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::const_iterator, _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::const_iterator> range = m_map.equal_range(key);
	for (_STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::const_iterator it = range.first; it != range.second; ++it) {
		if ((*it).second == b->m_value)
			return true;
	}
	return false;
}
