// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00586DDCElement { char bytes[9];Rva00586DDCElement();Rva00586DDCElement(const Rva00586DDCElement&);~Rva00586DDCElement();Rva00586DDCElement&operator=(const Rva00586DDCElement&); bool operator<(const Rva00586DDCElement&)const; bool operator==(const Rva00586DDCElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00586DDCElement * _STL::__copy_backward_ptrs<Rva00586DDCElement *, Rva00586DDCElement *>(Rva00586DDCElement *, Rva00586DDCElement *, Rva00586DDCElement *, _STL::__false_type const &);
