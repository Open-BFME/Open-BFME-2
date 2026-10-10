// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>


// Emit the sole ledger body, not every member of seven element families.
// The broad instantiations emitted a non-retail integer-tree copy constructor
// that took precedence over the rowed 207-byte provider at 0x00620CA0.
//
// The tree constructor it calls (0x002F1C5F -> base 0x002F0C32) takes its
// header node from the int-keyed tree node pool g_IntKeyedTreeNodePool
// (0x00DBD4B0) through 0x002EB448, so its allocator is not std::allocator<int>:
// that one allocates through allocator<char>::allocate (0x000307F0), the
// 0x002F0BF4/0x00382A6E pair. The pool allocator's real spelling is unknown;
// this address-named view keeps the two families apart.
template<class T> class Rva002F0C32Allocator : public _STL::allocator<T>
{
public:
 template<class U> struct rebind {typedef Rva002F0C32Allocator<U> other;};
 Rva002F0C32Allocator() throw() {}
 Rva002F0C32Allocator(const Rva002F0C32Allocator&) throw() {}
 template<class U> Rva002F0C32Allocator(const Rva002F0C32Allocator<U>&) throw() {}
};

template _STL::multiset<int, _STL::less<int>, Rva002F0C32Allocator<int> >::multiset();
