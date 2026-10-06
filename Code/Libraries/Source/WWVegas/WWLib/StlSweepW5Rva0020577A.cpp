// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva0020577AElement { char bytes[20]; bool operator<(const Rva0020577AElement&)const; bool operator==(const Rva0020577AElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0020577AElement * _STL::__uninitialized_fill_n<Rva0020577AElement *, unsigned int, Rva0020577AElement>(Rva0020577AElement *, unsigned int, Rva0020577AElement const &, _STL::__false_type const &);
