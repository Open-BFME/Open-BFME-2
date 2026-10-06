// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Oi /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003F421DElement { Rva003F421DElement();Rva003F421DElement(const Rva003F421DElement&);~Rva003F421DElement();Rva003F421DElement&operator=(const Rva003F421DElement&);char bytes[104]; bool operator<(const Rva003F421DElement&)const; bool operator==(const Rva003F421DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva003F421DElement * _STL::__copy<Rva003F421DElement *, Rva003F421DElement *, int>(Rva003F421DElement *, Rva003F421DElement *, Rva003F421DElement *, _STL::random_access_iterator_tag const &, int *);
