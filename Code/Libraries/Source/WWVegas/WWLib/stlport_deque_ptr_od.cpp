// cl: /Od /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// A vendored instantiation unit. It exists so the linker-selected bodies of
// this container appear as COMDATs that build/objplace.py can place against
// unlanded functions; the suffix says which optimisation level, because for
// these containers different bodies survive the link from different units.
#include <deque>
// bfme link decl-only begin
namespace _STL { template <> _Deque_base<void *,_STL::allocator<void *> >::~_Deque_base(); }
namespace _STL { template <> deque<void *,_STL::allocator<void *> >::~deque(); }
namespace _STL { template <> void _Deque_base<void *,_STL::allocator<void *> >::_M_destroy_nodes(void * * *,void * * *); }
namespace _STL { template <> void deque<void *,_STL::allocator<void *> >::_M_pop_back_aux(); }
namespace _STL { template <> void deque<void *,_STL::allocator<void *> >::_M_push_back_aux_v(void * const &); }
namespace _STL { template <> void deque<void *,_STL::allocator<void *> >::_M_reserve_map_at_back(unsigned int); }
namespace _STL { template <> void deque<void *,_STL::allocator<void *> >::push_back(void * const &); }
// Retail's only map reallocation is the optimised body at 0x003B57E5 (pinned
// for this name); this unit's /Od copy (487 bytes) is not it and wins link order.
namespace _STL { template <> void deque<void *,_STL::allocator<void *> >::_M_reallocate_map(unsigned int, bool); }
// bfme link decl-only end
// bfme link decl-only begin
namespace _STL { template <> void _Construct<void *, void *>(void **, void *const &); }
namespace _STL { template <> void _Deque_iterator_base<void *>::_M_advance(int); }
namespace _STL { template <> void _Deque_iterator_base<void *>::_M_increment(); }
namespace _STL { template <> void deque<void *, allocator<void *> >::_M_pop_front_aux(); }
namespace _STL { template <> int _Deque_iterator_base<void *>::_M_subtract(_Deque_iterator_base<void *> const &) const; }
namespace _STL { template <> void deque<void *, allocator<void *> >::clear(); }
namespace _STL { template <> void deque<void *, allocator<void *> >::pop_back(); }
namespace _STL { template <> void deque<void *, allocator<void *> >::pop_front(); }
namespace _STL { template <> unsigned int deque<void *, allocator<void *> >::size() const; }
// bfme link decl-only end
template class _STL::deque<void *, _STL::allocator<void *> >;
// The map copy this unit owns (retail 0x00026FB0); the declared-only map
// reallocation no longer instantiates it.
namespace _STL { template void ***copy<void ***, void ***>(void ***, void ***, void ***); }
