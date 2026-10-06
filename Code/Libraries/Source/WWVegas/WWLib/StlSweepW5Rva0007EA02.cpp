// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0007EA02Element { char bytes[9];Rva0007EA02Element();Rva0007EA02Element(const Rva0007EA02Element&);~Rva0007EA02Element();Rva0007EA02Element&operator=(const Rva0007EA02Element&); bool operator<(const Rva0007EA02Element&)const; bool operator==(const Rva0007EA02Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0007EA02Element * _STL::__copy_backward_ptrs<Rva0007EA02Element *, Rva0007EA02Element *>(Rva0007EA02Element *, Rva0007EA02Element *, Rva0007EA02Element *, _STL::__false_type const &);
