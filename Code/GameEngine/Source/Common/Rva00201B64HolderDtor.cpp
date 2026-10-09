// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00201B64@@QAE@XZ, retail 0x00201B64, 108B.
// Holder dtor: deletes Owner heap objects held as ints in list<int>,
// erases nodes, then destroys list via rowed List_base dtor.
// Evidence: calls rowed Owner dtor E19E1 plus delete plus list erase.
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

class Rva0048C200Owner
{
public:
	~Rva0048C200Owner();
};

class Rva00201B64
{
public:
	Rva00201B64();
	~Rva00201B64();
private:
	_STL::list<int> m_list00;
};

Rva00201B64::Rva00201B64()
{
}

Rva00201B64::~Rva00201B64()
{
	for (_STL::list<int>::iterator it = m_list00.begin(); it._M_node != m_list00.end()._M_node;)
	{
		int v = *it;
		if (v != 0)
		{
			Rva0048C200Owner *o = (Rva0048C200Owner *)v;
			*(void **)o = 0;
			delete o;
		}
		it = m_list00.erase(it);
	}
}
