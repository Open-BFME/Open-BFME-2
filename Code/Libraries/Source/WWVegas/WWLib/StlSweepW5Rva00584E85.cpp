// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>

struct Rva00584E85Element { int word0;int word1;char tail[1]; bool operator<(const Rva00584E85Element&)const; bool operator==(const Rva00584E85Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> > _STL::__copy<_STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> >, _STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> >, int>(_STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> >, _STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> >, _STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> >, _STL::random_access_iterator_tag const &, int *);
