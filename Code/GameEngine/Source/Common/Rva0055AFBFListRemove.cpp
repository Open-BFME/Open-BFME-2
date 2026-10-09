// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055AFBF@Rva0055AFBF@@QAEXH@Z @ 0x0055AFBF, 50 bytes.
// Removes the first matching value from a list at +0x14, but does not call
// erase when no match exists. The reciprocal-list cleanup at 0x0055B01F
// calls this on each peer stored in its +0x1C list, passing its own address.
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


class Rva0055AFBF
{
public:
	void rva0055AFBF(int value);
	char m_pad[0x14];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva0055AFBF::rva0055AFBF(int value)
{
	_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin();
	while (it != m_list.end() && *it != value) {
		++it;
	}
	if (it != m_list.end()) {
		m_list.erase(it);
	}
}
