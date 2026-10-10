// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <deque>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

// The verified unsigned max provider is at 0x00013740. This /Ob0 unit
// must call that body rather than offer its own conflicting COMDAT.
namespace _STL {
template <> const unsigned int& max<unsigned int>(const unsigned int&, const unsigned int&);
}






struct Rva00002926Element { _STL::list<short> values[1]; bool operator==(const Rva00002926Element&) const; };
template class _STL::deque<Rva00002926Element>;
