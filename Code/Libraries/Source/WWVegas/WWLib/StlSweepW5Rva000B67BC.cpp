// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva000B67BCElement { char bytes[9];Rva000B67BCElement();Rva000B67BCElement(const Rva000B67BCElement&);~Rva000B67BCElement();Rva000B67BCElement&operator=(const Rva000B67BCElement&); bool operator<(const Rva000B67BCElement&)const; bool operator==(const Rva000B67BCElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva000B67BCElement * _STL::__copy_backward_ptrs<Rva000B67BCElement *, Rva000B67BCElement *>(Rva000B67BCElement *, Rva000B67BCElement *, Rva000B67BCElement *, _STL::__false_type const &);
