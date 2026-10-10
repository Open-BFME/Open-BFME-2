// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

struct Rva0054D71BElement { double words[1];bool operator<(const Rva0054D71BElement&)const;bool operator==(const Rva0054D71BElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva0054D71BElement, _STL::allocator<Rva0054D71BElement> >::_M_insert_dispatch<_STL::_List_iterator<Rva0054D71BElement, _STL::_Const_traits<Rva0054D71BElement> > >(_STL::_List_iterator<Rva0054D71BElement, _STL::_Nonconst_traits<Rva0054D71BElement> >, _STL::_List_iterator<Rva0054D71BElement, _STL::_Const_traits<Rva0054D71BElement> >, _STL::_List_iterator<Rva0054D71BElement, _STL::_Const_traits<Rva0054D71BElement> >, _STL::__false_type const &);
