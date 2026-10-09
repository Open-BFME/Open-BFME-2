// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0037BD64@FXList@@QAEHXZ @0x0037BD64 29B: pop front int from list at +4 else 0; calls rowed list<int>::pop_front at 0x0037BCF9.
// Evidence: caller 0x0037D0A7 passes FXList* at +0xC both to FXList::addFXNugget and here; retail add ecx 4 empty-check cmp [eax] eax front at +8 pop_front.
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
class FXList
{
public:
	int rva0037BD64();
private:
	int m_unused00;
	_STL::list<int> m_nuggets;
};
int FXList::rva0037BD64()
{
	if (m_nuggets.empty())
		return 0;
	int v = m_nuggets.front();
	m_nuggets.pop_front();
	return v;
}
