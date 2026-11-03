// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00526275@@QAE@XZ @0x00526275 74B evidence: member +0 Rva00330757Member 0x00330757 size 0x10 then lists +0x10/+0x14 via rowed Coord3D List_base 0x00280A8D then zero +0x18; factory 0x00526F46 allocs 0x1c.
// Honest-address ctor (naming rule).
#include <list>

#include "../../../Include/Lib/Coord3D.h"

// Retail inlines list<Coord3D>'s node deallocate everywhere and has no
// out-of-line copy; another unit's copy is first in link order, so dllimport
// keeps this unit's inline-only.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<Coord3D> >::deallocate(_List_node<Coord3D> *__p, size_t) const
{ if (__p != 0) ::free((void *)__p); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<Coord3D> *, _List_node<Coord3D>, allocator<_List_node<Coord3D> > >::deallocate(_List_node<Coord3D> *__p, size_t __n)
{ allocator<_List_node<Coord3D> >::deallocate(__p, __n); }
}

#include "../../../../GameEngine/Include/Common/Rva00330757Member.h"

class Rva00526275
{
public:
	Rva00526275();
private:
	Rva00330757Member m_head;
	_STL::list<Coord3D> m_list10;
	_STL::list<Coord3D> m_list14;
	int m_18;
};

Rva00526275::Rva00526275() : m_head(), m_list10(), m_list14()
{
	m_18 = 0;
}
