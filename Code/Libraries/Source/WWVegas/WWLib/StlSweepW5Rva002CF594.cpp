// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002CF594Element { char bytes[9];Rva002CF594Element();Rva002CF594Element(const Rva002CF594Element&);~Rva002CF594Element();Rva002CF594Element&operator=(const Rva002CF594Element&); bool operator<(const Rva002CF594Element&)const; bool operator==(const Rva002CF594Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva002CF594Element * _STL::__copy_backward_ptrs<Rva002CF594Element *, Rva002CF594Element *>(Rva002CF594Element *, Rva002CF594Element *, Rva002CF594Element *, _STL::__false_type const &);
