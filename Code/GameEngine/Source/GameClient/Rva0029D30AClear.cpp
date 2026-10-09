// cl: /Ireference/shims/bfmelist /Oy /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /EHs-c-
// stlport
//
// ?rva0029D30A@Rva0029D30A@@QAEXXZ @0x0029D30A 72B.
// InGameUI-adjacent list clearer: circular _STL::list<int> at +0x8A0 holding
// object pointers as ints (payload at node +8); erase each node, call slot 0
// on the payload with 0, then operator delete the result. Evidence: rowed
// list<int>::erase 0x00438539, rowed operator delete 0x0002FD60, prev/next.

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

class Rva0029D30APayload
{
public:
	virtual void *slot00(int flag);
};

class Rva0029D30A
{
public:
	void rva0029D30A();
	unsigned char m_pad[0x8A0];
	_STL::list<int> m_8A0; // +0x8A0
};

void __cdecl operator delete(void *p);

void Rva0029D30A::rva0029D30A()
{
	_STL::list<int>::iterator it = m_8A0.begin();
	while (it._M_node != m_8A0.end()._M_node) {
		int v = *it;
		it = m_8A0.erase(it);
		Rva0029D30APayload *p = (Rva0029D30APayload *)v;
		void *q;
		if (p)
			q = p->slot00(0);
		else
			q = 0;
		::operator delete(q);
	}
}
