// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005B2B1EElement { char bytes[9];Rva005B2B1EElement();Rva005B2B1EElement(const Rva005B2B1EElement&);~Rva005B2B1EElement();Rva005B2B1EElement&operator=(const Rva005B2B1EElement&); bool operator<(const Rva005B2B1EElement&)const; bool operator==(const Rva005B2B1EElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva005B2B1EElement * _STL::__copy_backward_ptrs<Rva005B2B1EElement *, Rva005B2B1EElement *>(Rva005B2B1EElement *, Rva005B2B1EElement *, Rva005B2B1EElement *, _STL::__false_type const &);
