// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>

struct Rva00421E7EElement { char bytes[1]; bool operator<(const Rva00421E7EElement&)const; bool operator==(const Rva00421E7EElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<_STL::_Deque_iterator<Rva00421E7EElement, _STL::_Nonconst_traits<Rva00421E7EElement> > >(_STL::_Deque_iterator<Rva00421E7EElement, _STL::_Nonconst_traits<Rva00421E7EElement> >, _STL::_Deque_iterator<Rva00421E7EElement, _STL::_Nonconst_traits<Rva00421E7EElement> >, _STL::__false_type const &);
