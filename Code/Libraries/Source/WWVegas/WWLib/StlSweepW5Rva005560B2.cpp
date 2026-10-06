// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <string>

struct Rva005560B2Element { _STL::basic_string<wchar_t> strings[1]; bool operator<(const Rva005560B2Element&)const; bool operator==(const Rva005560B2Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy<_STL::_Deque_iterator<Rva005560B2Element, _STL::_Nonconst_traits<Rva005560B2Element> >, Rva005560B2Element>(_STL::_Deque_iterator<Rva005560B2Element, _STL::_Nonconst_traits<Rva005560B2Element> >, _STL::_Deque_iterator<Rva005560B2Element, _STL::_Nonconst_traits<Rva005560B2Element> >, Rva005560B2Element *);
