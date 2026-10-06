// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00255CFAElement { char bytes[9];Rva00255CFAElement();Rva00255CFAElement(const Rva00255CFAElement&);~Rva00255CFAElement();Rva00255CFAElement&operator=(const Rva00255CFAElement&); bool operator<(const Rva00255CFAElement&)const; bool operator==(const Rva00255CFAElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00255CFAElement * _STL::__copy_backward_ptrs<Rva00255CFAElement *, Rva00255CFAElement *>(Rva00255CFAElement *, Rva00255CFAElement *, Rva00255CFAElement *, _STL::__false_type const &);
