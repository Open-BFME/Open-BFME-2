// cl: /Ireference/shims/bfmelist /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055AFA3@Rva0055B0CC@@QAEXXZ @ 0x0055AFA3, 28 bytes.
// Vtable slot 1 of 0x0086B900 (class of ??0Rva0055B0CC@@QAE@XZ) and siblings.
// Layout from base ctor 0x0055B048 and dtor 0x0055B0CC: list +0x14, float
// +0x18, list +0x1C. Body zeroes +0x18 via SSE then clears both lists,
// second clear tail-jmped. Callees rowed list base clear 0x0023DAA5.
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

class Rva0055B0CC
{
public:
	void rva0055AFA3();
private:
	char m_pad[0x14];
	_STL::list<int, _STL::allocator<int> > m_14;
	float m_18;
	_STL::list<int, _STL::allocator<int> > m_1C;
};

void Rva0055B0CC::rva0055AFA3()
{
	m_18 = 0.0f;
	m_14.clear();
	m_1C.clear();
}
