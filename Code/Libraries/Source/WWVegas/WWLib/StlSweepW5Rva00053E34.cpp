// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00053E34Element { char bytes[9];Rva00053E34Element();Rva00053E34Element(const Rva00053E34Element&);~Rva00053E34Element();Rva00053E34Element&operator=(const Rva00053E34Element&); bool operator<(const Rva00053E34Element&)const; bool operator==(const Rva00053E34Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00053E34Element * _STL::__copy_backward_ptrs<Rva00053E34Element *, Rva00053E34Element *>(Rva00053E34Element *, Rva00053E34Element *, Rva00053E34Element *, _STL::__false_type const &);
