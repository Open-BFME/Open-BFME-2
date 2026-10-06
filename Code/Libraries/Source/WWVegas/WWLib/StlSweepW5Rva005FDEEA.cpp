// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005FDEEAElement {Rva005FDEEAElement();Rva005FDEEAElement(const Rva005FDEEAElement&);Rva005FDEEAElement&operator=(const Rva005FDEEAElement&);~Rva005FDEEAElement(){}char bytes[12]; bool operator==(const Rva005FDEEAElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva005FDEEAElement * _STL::__copy_backward<Rva005FDEEAElement *, Rva005FDEEAElement *, int>(Rva005FDEEAElement *, Rva005FDEEAElement *, Rva005FDEEAElement *, _STL::random_access_iterator_tag const &, int *);
