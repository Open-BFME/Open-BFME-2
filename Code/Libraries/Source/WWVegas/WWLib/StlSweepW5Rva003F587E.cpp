// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva003F587EElement { char bytes[48]; bool operator<(const Rva003F587EElement&)const; bool operator==(const Rva003F587EElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva003F587EElement * _STL::__uninitialized_fill_n<Rva003F587EElement *, unsigned int, Rva003F587EElement>(Rva003F587EElement *, unsigned int, Rva003F587EElement const &, _STL::__false_type const &);
