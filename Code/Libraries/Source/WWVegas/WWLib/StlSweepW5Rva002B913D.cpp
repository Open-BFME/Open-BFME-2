// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002B913DElement { char bytes[9];Rva002B913DElement();Rva002B913DElement(const Rva002B913DElement&);~Rva002B913DElement();Rva002B913DElement&operator=(const Rva002B913DElement&); bool operator<(const Rva002B913DElement&)const; bool operator==(const Rva002B913DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva002B913DElement * _STL::__copy_backward_ptrs<Rva002B913DElement *, Rva002B913DElement *>(Rva002B913DElement *, Rva002B913DElement *, Rva002B913DElement *, _STL::__false_type const &);
