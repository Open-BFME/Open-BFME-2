// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva004AE94DElement { char bytes[84]; bool operator<(const Rva004AE94DElement&)const; bool operator==(const Rva004AE94DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva004AE94DElement * _STL::__uninitialized_fill_n<Rva004AE94DElement *, unsigned int, Rva004AE94DElement>(Rva004AE94DElement *, unsigned int, Rva004AE94DElement const &, _STL::__false_type const &);
