// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva000B6569Element { char bytes[9];Rva000B6569Element();Rva000B6569Element(const Rva000B6569Element&);~Rva000B6569Element();Rva000B6569Element&operator=(const Rva000B6569Element&); bool operator<(const Rva000B6569Element&)const; bool operator==(const Rva000B6569Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva000B6569Element * _STL::__copy_backward_ptrs<Rva000B6569Element *, Rva000B6569Element *>(Rva000B6569Element *, Rva000B6569Element *, Rva000B6569Element *, _STL::__false_type const &);
