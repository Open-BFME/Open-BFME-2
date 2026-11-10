// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}



struct Rva00332106PointerTarget;
// Retail's list-base ctor for this instantiation (pinned 0x0029FB3B) takes its
// sentinel node from the freelist pool at VA 0x00DA60E8 through rowed
// FreelistPool::pop 0x002393E2, not STLport's node allocator (the same pool
// stlport_pod_list_bodies.cpp's erase returns nodes to).
class FreelistPool { public: void *pop(); int m_00; void *m_04; void *m_head; };
extern FreelistPool g_freelistPool;
namespace _STL {
template <> inline _List_base<Rva00332106PointerTarget *, allocator<Rva00332106PointerTarget *> >::_List_base(const allocator<Rva00332106PointerTarget *> &a)
    : _M_node(_Node_allocator_type(a), (_Node *)0)
{
	_Node *node = (_Node *)g_freelistPool.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
}
template class _STL::list<Rva00332106PointerTarget*>;
