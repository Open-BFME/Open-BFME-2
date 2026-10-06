// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00151E4DElement {Rva00151E4DElement();Rva00151E4DElement(const Rva00151E4DElement&);Rva00151E4DElement&operator=(const Rva00151E4DElement&);~Rva00151E4DElement(){}char bytes[36]; bool operator==(const Rva00151E4DElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00151E4DElement * _STL::__copy<Rva00151E4DElement *, Rva00151E4DElement *, int>(Rva00151E4DElement *, Rva00151E4DElement *, Rva00151E4DElement *, _STL::random_access_iterator_tag const &, int *);
