// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<Object*>::insert calls the out-of-line create_node (landed alongside
// at 0x5EB9AC), mirroring stlport_list_int_insert.cpp.
#include <list>

class Object;
// Native Object-pointer nodes use the dedicated freelist provider.
namespace _STL {
template <> _List_node<Object *> *list<Object *, allocator<Object *> >::_M_create_node(Object *const &);
}

// list<Object *>'s base constructor, native 0x001EB984 (40B), which the copy
// constructor 0x004702FB calls: stock STLport except that the sentinel node
// comes from the Object-pointer node pool at VA 0x00DB8FEC (the pool the
// out-of-line create_node 0x001EB9AC pops) instead of allocator<char>.
// Same shape as list<Drawable *>'s base constructor 0x00239BB0.
#include "../../../../GameEngine/Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DB8FEC;
namespace _STL {
template <> __declspec(noinline)
_List_base<Object *, allocator<Object *> >::_List_base(const allocator<Object *> &__a)
	: _M_node(allocator<_List_node<Object *> >(__a), (_List_node<Object *> *)0)
{
	_List_node<Object *> *node = (_List_node<Object *> *)g_freelistPool00DB8FEC.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Object;
template class _STL::list<Object *, _STL::allocator<Object *> >;
