// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001DD339Element { char bytes[9];Rva001DD339Element();Rva001DD339Element(const Rva001DD339Element&);~Rva001DD339Element();Rva001DD339Element&operator=(const Rva001DD339Element&); bool operator<(const Rva001DD339Element&)const; bool operator==(const Rva001DD339Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva001DD339Element * _STL::__copy_backward_ptrs<Rva001DD339Element *, Rva001DD339Element *>(Rva001DD339Element *, Rva001DD339Element *, Rva001DD339Element *, _STL::__false_type const &);
