// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <set>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct Rva00463D59Element {
 Rva00463D59Element(); Rva00463D59Element(const Rva00463D59Element&);
 ~Rva00463D59Element(); Rva00463D59Element&operator=(const Rva00463D59Element&);
 char bytes[8];
};
bool operator<(const Rva00463D59Element&,const Rva00463D59Element&);
// MSVC also instantiates the unused member-tree destructor with this constructor.
// Keep that operation external; this unit recovers only default construction.
namespace _STL { template <> _Rb_tree<Rva00463D59Element, Rva00463D59Element, _Identity<Rva00463D59Element>, less<Rva00463D59Element>, allocator<Rva00463D59Element> >::~_Rb_tree(); }

// Emit only the rowed constructor; unrelated set operations require element bodies.
template _STL::set<Rva00463D59Element>::set();
