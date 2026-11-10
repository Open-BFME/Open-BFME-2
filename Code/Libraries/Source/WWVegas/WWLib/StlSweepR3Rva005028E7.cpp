// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <map>



struct Rva005028E7Record {  int word0;int word1;int word2; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<pair<const int, Rva005028E7Record> , pair<const int, Rva005028E7Record> >(pair<const int, Rva005028E7Record>  *, const pair<const int, Rva005028E7Record>  &); }


// Instantiate the recovered member; retain only its required template dependencies.
// The node's element copy is retail 0x00502667, rowed as _Construct<Rva00502667Element>; bind the
// call to that row instead of emitting this unit's own _Construct copy.
struct Rva00502667Element;
namespace _STL { template <> void _Construct<Rva00502667Element, Rva00502667Element>(Rva00502667Element *, const Rva00502667Element &); }
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(_STL::pair<int const, Rva005028E7Record> *dest, const _STL::pair<int const, Rva005028E7Record> &source)
{
	_Construct<Rva00502667Element, Rva00502667Element>(reinterpret_cast<Rva00502667Element *>(dest), *reinterpret_cast<const Rva00502667Element *>(&source));
}
}
template _STL::_Rb_tree_node<_STL::pair<int const, Rva005028E7Record> > * _STL::_Rb_tree<int, _STL::pair<int const, Rva005028E7Record>, _STL::_Select1st<_STL::pair<int const, Rva005028E7Record> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva005028E7Record> > >::_M_create_node(_STL::pair<int const, Rva005028E7Record> const &);
