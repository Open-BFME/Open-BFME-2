// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <string>

struct Rva0021FDD3Element { unsigned prefix[1];_STL::basic_string<wchar_t> strings[2];unsigned suffix[1]; bool operator<(const Rva0021FDD3Element&)const; bool operator==(const Rva0021FDD3Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<Rva0021FDD3Element *>(Rva0021FDD3Element *, Rva0021FDD3Element *, _STL::__false_type const &);
