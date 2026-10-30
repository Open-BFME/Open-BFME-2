// cl: /Ireference/shims/bfmelist /Oy /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /EHs-c-
// stlport
// ?rva0029D3FB@Rva0029D3FB@@QAEXXZ @0x0029D3FB 83B.
// List clearer like Rva0029D30A at +0x8A0 but at +0x8CC: circular
// _STL::list<int> holding holder pointers as ints; each holder carries the
// payload object pointer at +0, null-checked, slot00(0) on it, then operator
// delete the result plus the holder, then erase. Evidence: rowed
// list<int>::erase 0x00438539, rowed operator delete 0x0002FD60, callers
// 0x002A5C25 0x002A6102, prev/next.
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

class Rva0029D3FBPayload
{
public:
	virtual void *slot00(int flag);
};

struct Rva0029D3FBHolder
{
	Rva0029D3FBPayload *ptr;
};

class Rva0029D3FB
{
public:
	void rva0029D3FB();
	unsigned char m_pad[0x8CC];
	_STL::list<int> m_8CC; // +0x8CC
};

#include <new>

void Rva0029D3FB::rva0029D3FB()
{
	_STL::list<int>::iterator it = m_8CC.begin();
	while (it._M_node != m_8CC.end()._M_node) {
		int handle = *it;
		Rva0029D3FBHolder *holder = (Rva0029D3FBHolder *)handle;
		if (holder != 0) {
			void *payload;
			if (holder->ptr != 0)
				payload = holder->ptr->slot00(0);
			else
				payload = 0;
			::operator delete(payload);
			::operator delete(holder);
		}
		it = m_8CC.erase(it);
	}
}
