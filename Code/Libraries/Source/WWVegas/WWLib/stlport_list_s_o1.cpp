// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

// No retail short-list sort identity: native525951 comparator follows a
// payload pointer and compares float10; native52611D is its compatible sort.
// Declaration-only member suppresses both that incorrect instantiation and
// its same-name wrapper; the other five true short-list rows remain here.
namespace _STL {
template<> void list<short, allocator<short> >::sort();
// Use the existing full37B insert provider2ABB61; this shim would inline
// create_node and emit a conflicting copy with the same mangled name.
template<> list<short, allocator<short> >::iterator
list<short, allocator<short> >::insert(iterator, const short &);
}
template class _STL::list<short, _STL::allocator<short > >;
