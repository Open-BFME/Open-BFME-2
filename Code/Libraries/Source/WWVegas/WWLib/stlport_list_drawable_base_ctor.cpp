// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// list<Drawable *>'s base constructor, native 0x00239BB0..0x00239BD8 (40B).
// Identity: the byte-verified AIUpdateInterface voice-response bodies
// 0x0026B25A-0x0026B403 call it through this symbol's REL32.
// It is the STLport _List_base constructor, except that the sentinel node
// comes from the 12-byte node pool at VA 0x00DBA5E0, the same pool the
// matched list<Drawable *> node creator (InGameUISelectDrawable.cpp) pops,
// instead of allocator<char>::allocate. The specialization below states that
// retail fact for this one element type; the alloc-proxy constructor is the
// rowed ICF-shared 0x0014F3C4.
#include <list>

class Drawable;
class FreelistPool { public: void *pop(); };
extern FreelistPool g_pool00239BD8;

namespace _STL
{
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_pool00239BD8.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
}

template class _STL::_List_base<Drawable *, _STL::allocator<Drawable *> >;
