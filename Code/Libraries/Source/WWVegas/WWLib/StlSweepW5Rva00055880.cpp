// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <string>

struct Rva00055880Element { _STL::basic_string<wchar_t> strings[1]; bool operator<(const Rva00055880Element&)const; bool operator==(const Rva00055880Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy<_STL::_Deque_iterator<Rva00055880Element, _STL::_Nonconst_traits<Rva00055880Element> >, Rva00055880Element>(_STL::_Deque_iterator<Rva00055880Element, _STL::_Nonconst_traits<Rva00055880Element> >, _STL::_Deque_iterator<Rva00055880Element, _STL::_Nonconst_traits<Rva00055880Element> >, Rva00055880Element *);
