// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>

struct Rva0054A461Element { char bytes[1]; bool operator<(const Rva0054A461Element&)const; bool operator==(const Rva0054A461Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<_STL::_Deque_iterator<Rva0054A461Element, _STL::_Nonconst_traits<Rva0054A461Element> > >(_STL::_Deque_iterator<Rva0054A461Element, _STL::_Nonconst_traits<Rva0054A461Element> >, _STL::_Deque_iterator<Rva0054A461Element, _STL::_Nonconst_traits<Rva0054A461Element> >, _STL::__false_type const &);
