// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0029F93A@Rva0029F93A@@QAEXH@Z @0x0029F93A 26B
// Guarded list<int>::remove via rowed 0x0047BAF7 on member at +0x9C4.
// Skips when arg is 0; callers 0x00489DA0 0x0048A38D; unblocks 0x0048A15A.
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}

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
