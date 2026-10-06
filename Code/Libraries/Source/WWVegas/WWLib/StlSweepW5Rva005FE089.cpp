// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005FE089Element { char bytes[9];Rva005FE089Element();Rva005FE089Element(const Rva005FE089Element&);~Rva005FE089Element();Rva005FE089Element&operator=(const Rva005FE089Element&); bool operator<(const Rva005FE089Element&)const; bool operator==(const Rva005FE089Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva005FE089Element * _STL::__copy_backward_ptrs<Rva005FE089Element *, Rva005FE089Element *>(Rva005FE089Element *, Rva005FE089Element *, Rva005FE089Element *, _STL::__false_type const &);
