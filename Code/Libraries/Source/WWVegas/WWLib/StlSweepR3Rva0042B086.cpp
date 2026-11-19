// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Drawable element identity is proven by CommandTranslator::translateGameMessage
// selected-drawable list copy and AIUpdateInterface voice-response list operations.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// TU-local overload avoids exporting an unrelated max instantiation.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <list>
// list<Drawable *>'s base destructor is retail's pooled body 0x00239AF4, defined
// in InGameUICtor.cpp; this unit's allocator shims would emit a raw-free copy.
class Drawable;
namespace _STL { template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base(); }

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}




// The pooled Drawable sentinel teardown is supplied by InGameUICtor.cpp.
namespace _STL { template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base(); }
// Nodes come from the freelist pool at VA 0x00DBA5E0 (pop 0x002393E2, head
// at +0x08); erase relinks the node onto that head inline (retail 0x0029DFE9).
#include "../../../../GameEngine/Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> inline
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> list<Drawable *>::iterator list<Drawable *>::erase(iterator __position)
{
	_List_node_base *__prev_node = __position._M_node->_M_prev;
	_List_node_base *__next_node = __position._M_node->_M_next;
	__prev_node->_M_next = __next_node;
	__next_node->_M_prev = __prev_node;
	*(void **)__position._M_node = g_freelistPool00DBA5E0.m_head;
	g_freelistPool00DBA5E0.m_head = __position._M_node;
	return iterator((_List_node<Drawable *> *)__next_node);
}
template<> __declspec(noinline) _List_node<Drawable*>* list<Drawable*>::_M_create_node(Drawable*const &value) {
 _List_node<Drawable*>* node=(_List_node<Drawable*>*)g_freelistPool00DBA5E0.pop();
 if(&node->_M_data!=0) node->_M_data=value;
 return node;
}
}

template class _STL::list<Drawable*>;
