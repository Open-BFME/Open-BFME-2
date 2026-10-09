// cl: /Ireference/shims/bfmelist /Oy /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /EHs-c-
// stlport
// ?rva0029D7CA@Rva0029D7CA@@QAEXXZ @0x0029D7CA 83B.
// List clearer sibling of 0x0029D3FB at +0x8D0: circular _STL::list<int>
// holding holder pointers as ints; each holder carries the payload object
// pointer at +0, null-checked, slot00(0) on it, then operator delete the
// result plus the holder, then erase. Evidence: rowed list<int>::erase
// 0x00438539, rowed operator delete 0x0002FD60, callers 0x002A5C2C
// 0x002A6109, prev/next.
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

class Rva0029D7CAPayload
{
public:
	virtual void *slot00(int flag);
};

struct Rva0029D7CAHolder
{
	Rva0029D7CAPayload *ptr;
};

class Rva0029D7CA
{
public:
	void rva0029D7CA();
	unsigned char m_pad[0x8D0];
	_STL::list<int> m_8D0; // +0x8D0
};

void __cdecl operator delete(void *p);

void Rva0029D7CA::rva0029D7CA()
{
	_STL::list<int>::iterator it = m_8D0.begin();
	while (it._M_node != m_8D0.end()._M_node) {
		int v = *it;
		Rva0029D7CAHolder *h = (Rva0029D7CAHolder *)v;
		if (h != 0) {
			void *q;
			if (h->ptr != 0)
				q = h->ptr->slot00(0);
			else
				q = 0;
			::operator delete(q);
			::operator delete(h);
		}
		it = m_8D0.erase(it);
	}
}
