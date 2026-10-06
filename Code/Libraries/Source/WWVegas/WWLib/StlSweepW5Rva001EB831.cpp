// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001EB831Element { char bytes[9];Rva001EB831Element();Rva001EB831Element(const Rva001EB831Element&);~Rva001EB831Element();Rva001EB831Element&operator=(const Rva001EB831Element&); bool operator<(const Rva001EB831Element&)const; bool operator==(const Rva001EB831Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva001EB831Element * _STL::__copy_backward_ptrs<Rva001EB831Element *, Rva001EB831Element *>(Rva001EB831Element *, Rva001EB831Element *, Rva001EB831Element *, _STL::__false_type const &);
