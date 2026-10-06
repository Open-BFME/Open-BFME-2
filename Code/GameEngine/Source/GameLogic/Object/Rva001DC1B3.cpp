// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva001DC1B3@Rva001DC0EC@@QAEXPAV?$list@HV?$allocator@H@_STL@@@_STL@@@Z @0x001DC1B3 46B.
// Copies list<int> at +0 into dest list via push_back loop with rowed push_back
// 0x0005548F. Evidence: caller 0x001DC57C passes [esi+0x24/0x28/0x2C/0x30] as
// this and its arg as dest; layout matches Rva001DC0EC list at +0.
// Honest class reuse from adjacent dtor 0x001DC0EC.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class Rva001DC0EC
{
public:
	void rva001DC1B3(_STL::list<int, _STL::allocator<int> > *dest);
private:
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva001DC0EC::rva001DC1B3(_STL::list<int, _STL::allocator<int> > *dest)
{
	for (_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin(); it != m_list.end(); ++it) {
		int v = *it;
		dest->push_back(v);
	}
}
