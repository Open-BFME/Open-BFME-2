// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0029F93A@Rva0029F93A@@QAEXH@Z @0x0029F93A 26B
// Guarded list<int>::remove via rowed 0x0047BAF7 on member at +0x9C4.
// Skips when arg is 0; callers 0x00489DA0 0x0048A38D; unblocks 0x0048A15A.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


struct Rva0029F93A
{
	char m_pad[0x9C4];
	_STL::list<int> m_list;
	void rva0029F93A(int v);
};

void Rva0029F93A::rva0029F93A(int v)
{
	if (v != 0)
		m_list.remove(v);
}
