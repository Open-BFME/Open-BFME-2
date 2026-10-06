// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva003F631BElement { char bytes[28]; bool operator<(const Rva003F631BElement&)const; bool operator==(const Rva003F631BElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva003F631BElement * _STL::__uninitialized_fill_n<Rva003F631BElement *, unsigned int, Rva003F631BElement>(Rva003F631BElement *, unsigned int, Rva003F631BElement const &, _STL::__false_type const &);
