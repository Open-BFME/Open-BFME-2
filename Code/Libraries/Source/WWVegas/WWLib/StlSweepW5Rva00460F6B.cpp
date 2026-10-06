// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00460F6BElement {Rva00460F6BElement();Rva00460F6BElement(const Rva00460F6BElement&);Rva00460F6BElement&operator=(const Rva00460F6BElement&);~Rva00460F6BElement(){}char bytes[12]; bool operator==(const Rva00460F6BElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00460F6BElement * _STL::__uninitialized_fill_n<Rva00460F6BElement *, unsigned int, Rva00460F6BElement>(Rva00460F6BElement *, unsigned int, Rva00460F6BElement const &, _STL::__false_type const &);
