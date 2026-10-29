// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
//
// A vendored instantiation unit. It exists so the linker-selected bodies of
// this container appear as COMDATs that build/objplace.py can place against
// unlanded functions; the suffix says which optimisation level, because for
// these containers different bodies survive the link from different units.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
// Owned elsewhere: copy<void***> (stlport_deque_ptr_od.cpp) and the map
// reallocation (retail's 0x003B57E5 body). Call them, emit no copies.
// bfme link decl-only begin
namespace _STL { template <> void deque<void *, allocator<void *> >::_M_reallocate_map(unsigned int, bool); }
namespace _STL { template <> void ***copy<void ***, void ***>(void ***, void ***, void ***); }
namespace _STL { template <> unsigned int deque<void *, allocator<void *> >::max_size() const; }
// bfme link decl-only end

// Defer allocator workers to their existing providers; the local copies
// compete with those selected by the link (allocate owns retail 0x00620180).
namespace _STL {
template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() _STLP_NOTHROW {}
template <> __declspec(dllimport) __forceinline void **allocator<void *>::allocate(size_type __n, void const *) {
  return __n != 0 ? __REINTERPRET_CAST(value_type*, allocator<char>::allocate(__n * sizeof(value_type), 0)) : 0;
}
}

// Native 0x0038938C: STLport4.5.3 pointer queue pop forwarding to its owned provider.
#include <queue>
template void _STL::queue<void*,_STL::deque<void*,_STL::allocator<void*> > >::pop();

// Instantiate only the members this unit owns; a whole-class instantiation
// also emitted copies of members other units own, which lose to them.
namespace _STL { template void _Deque_iterator_base<void *>::_M_advance(int); }
namespace _STL { template void deque<void *, allocator<void *> >::clear(); }
namespace _STL { template void deque<void *, allocator<void *> >::_M_pop_back_aux(); }
namespace _STL { template void deque<void *, allocator<void *> >::_M_pop_front_aux(); }
namespace _STL { template int _Deque_iterator_base<void *>::_M_subtract(_Deque_iterator_base<void *> const &) const; }
namespace _STL { template void swap<_Deque_iterator<void *, _Nonconst_traits<void *> > >(_Deque_iterator<void *, _Nonconst_traits<void *> > &, _Deque_iterator<void *, _Nonconst_traits<void *> > &); }
namespace _STL { template void _Deque_iterator_base<void *>::_M_increment(); }
namespace _STL { template void _Deque_base<void *, allocator<void *> >::_M_destroy_nodes(void ***, void ***); }
namespace _STL { template _Deque_base<void *, allocator<void *> >::~_Deque_base(); }
namespace _STL { template void deque<void *, allocator<void *> >::_M_push_back_aux_v(void *const &); }
namespace _STL { template void fill<void **, void *>(void **, void **, void *const &); }
namespace _STL { template void deque<void *, allocator<void *> >::pop_front(); }
namespace _STL { template void deque<void *, allocator<void *> >::pop_back(); }
namespace _STL { template void _Construct<void *, void *>(void **, void *const &); }
namespace _STL { template void deque<void *, allocator<void *> >::_M_reserve_map_at_back(unsigned int); }
namespace _STL { template void queue<void *, deque<void *, allocator<void *> > >::pop(); }
namespace _STL { template _Deque_iterator<void *, _Nonconst_traits<void *> > & _Deque_iterator<void *, _Nonconst_traits<void *> >::operator++(); }
namespace _STL { template deque<void *, allocator<void *> >::~deque(); }
namespace _STL { template void deque<void *, allocator<void *> >::push_back(void *const &); }
namespace _STL { template unsigned int deque<void *, allocator<void *> >::size() const; }
