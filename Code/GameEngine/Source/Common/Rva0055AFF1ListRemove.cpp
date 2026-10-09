// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055AFF1@Rva0055AFF1@@QAEXH@Z @ 0x0055AFF1, 46 bytes.
// Single-erase of int value from list at +0x1C. Evidence: retail walks nodes
// via [eax+8] comparing to [ebp+8] then calls rowed list<int>::erase
// 0x438539; caller 0x55B0FB passes its arg through.
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


class Rva0055AFF1
{
public:
	void rva0055AFF1(int value);
	char m_pad[0x1C];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva0055AFF1::rva0055AFF1(int value)
{
	_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin();
	while (it != m_list.end() && *it != value) {
		++it;
	}
	m_list.erase(it);
}
