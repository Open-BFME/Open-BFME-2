// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva00438FC5@@QAE@XZ, retail 0x00438FC5, 47 bytes.
// Non-virtual dtor of a class with list<int> at +0 that explicitly clears it:
// EH prolog, clear via rowed 0x0023DAA5 then List_base dtor via rowed
// 0x004EC395. No vtable, this==member so no offset. Callers 0x439CD2 etc.
// /EHs for list-dtor state stores per 4.6. Honest address name.
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
class Rva00438FC5
{
public:
	~Rva00438FC5();
private:
	_STL::list<int, _STL::allocator<int> > m_list;
};
Rva00438FC5::~Rva00438FC5()
{
	m_list.clear();
}
