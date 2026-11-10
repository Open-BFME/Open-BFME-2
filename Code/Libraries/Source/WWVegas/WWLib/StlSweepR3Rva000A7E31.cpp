// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <set>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}










struct Rva000A7E31Key { int word; bool operator<(const Rva000A7E31Key&b)const{return word<b.word;} bool operator==(const Rva000A7E31Key&b)const{return word==b.word;} };
// Instantiate the recovered member; retain only its required template dependencies.
template unsigned int _STL::_Rb_tree<Rva000A7E31Key, Rva000A7E31Key, _STL::_Identity<Rva000A7E31Key>, _STL::less<Rva000A7E31Key>, _STL::allocator<Rva000A7E31Key> >::erase(Rva000A7E31Key const &);
