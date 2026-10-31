// cl: /Ireference/open-bfme-1/inputs/vendor /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
template<class T> class Rva001EB984PoolAllocator;
namespace _STL {
template<class A,class B> Rva001EB984PoolAllocator<B> &__stl_alloc_rebind(Rva001EB984PoolAllocator<A> &,const B *);
template<class A,class B> Rva001EB984PoolAllocator<B> __stl_alloc_create(const Rva001EB984PoolAllocator<A> &,const B *);
}
// stlport
// STLport 4.6 template implementation over the existing pooled Object-list view.
// Pooled Object-list array copy: native 0x004703B1 (47B), 0x00474125 (29B).
// Allocator spelling is a source-derived view, not a recovered retail name.
// Original physical source retained pending TU approval.
#include "stlport/stl/_algobase.h"
#include <algorithm>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


// Existing pooled Object-list allocator ABI; implementation remains with its native providers.
class Object;
template<class T> class Rva001EB984PoolAllocator {
public:
    typedef T value_type; typedef T *pointer; typedef const T *const_pointer;
    typedef T &reference; typedef const T &const_reference;
    typedef unsigned int size_type; typedef int difference_type;
    template<class U> struct rebind { typedef Rva001EB984PoolAllocator<U> other; };
    Rva001EB984PoolAllocator();
    template<class U> Rva001EB984PoolAllocator(const Rva001EB984PoolAllocator<U> &);
    Rva001EB984PoolAllocator(const Rva001EB984PoolAllocator &);
    ~Rva001EB984PoolAllocator();
    T *allocate(unsigned int, const void * = 0);
    void deallocate(T *,unsigned int);
    void construct(T *,const T &); void destroy(T *);
    unsigned int max_size() const;
};
namespace _STL {
template<class T,class U> struct _Alloc_traits<T,Rva001EB984PoolAllocator<U> > {
    typedef Rva001EB984PoolAllocator<U> _Orig;
    typedef Rva001EB984PoolAllocator<T> allocator_type;
    static allocator_type create_allocator(const _Orig &a) { return allocator_type(a); }
};
}
typedef _STL::list<Object *,Rva001EB984PoolAllocator<Object *> > NativePooledObjectList;
typedef char NativePooledObjectListExtent[sizeof(NativePooledObjectList)==4 ? 1 : -1];
namespace _STL {
template <> NativePooledObjectList::iterator NativePooledObjectList::erase(NativePooledObjectList::iterator);
template <> NativePooledObjectList::iterator NativePooledObjectList::insert(NativePooledObjectList::iterator,Object *const &);
}

namespace _STL { template <> NativePooledObjectList &NativePooledObjectList::operator=(const NativePooledObjectList &); }
typedef NativePooledObjectList PoolList;
template PoolList *_STL::copy<PoolList *, PoolList *>(PoolList *, PoolList *, PoolList *);
