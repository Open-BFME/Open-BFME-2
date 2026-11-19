// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
// bfme link decl-only begin
// operator+ calls _Deque_iterator_base<void *>::_M_advance out of line. This unit's /Oy- copy keeps a
// frame retail's 92-byte body does not have; stlport_deque_ptr_o1.cpp emits and rows retail's.
namespace _STL { template <> void _Deque_iterator_base<void *>::_M_advance(int); }
// bfme link decl-only end


// Instantiate the recovered operation and its required template dependencies.
template _STL::_Deque_iterator<void *, _STL::_Const_traits<void *> > _STL::_Deque_iterator<void *, _STL::_Const_traits<void *> >::operator+(int) const;
