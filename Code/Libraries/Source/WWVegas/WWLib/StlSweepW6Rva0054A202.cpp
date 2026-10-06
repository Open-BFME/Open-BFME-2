// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <memory>

struct Rva0054A202Element { unsigned opaque;bool operator<(const Rva0054A202Element&)const;bool operator==(const Rva0054A202Element&)const; };


// Instantiate the recovered operation and its required template dependencies.
template _STL::_Deque_iterator<Rva0054A202Element *, _STL::_Const_traits<Rva0054A202Element *> > _STL::_Deque_iterator<Rva0054A202Element *, _STL::_Const_traits<Rva0054A202Element *> >::operator+(int) const;
