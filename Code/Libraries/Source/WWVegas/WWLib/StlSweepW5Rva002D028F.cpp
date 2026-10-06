// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <string>

struct Rva002D028FElement { unsigned prefix[1];_STL::basic_string<wchar_t> strings[1];unsigned suffix[1]; bool operator<(const Rva002D028FElement&)const; bool operator==(const Rva002D028FElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<Rva002D028FElement *>(Rva002D028FElement *, Rva002D028FElement *, _STL::__false_type const &);
