// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0025BF40Element { char bytes[9];Rva0025BF40Element();Rva0025BF40Element(const Rva0025BF40Element&);~Rva0025BF40Element();Rva0025BF40Element&operator=(const Rva0025BF40Element&); bool operator<(const Rva0025BF40Element&)const; bool operator==(const Rva0025BF40Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0025BF40Element * _STL::__copy_backward_ptrs<Rva0025BF40Element *, Rva0025BF40Element *>(Rva0025BF40Element *, Rva0025BF40Element *, Rva0025BF40Element *, _STL::__false_type const &);
