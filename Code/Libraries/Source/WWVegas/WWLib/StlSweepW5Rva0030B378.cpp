// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0030B378Element { char bytes[9];Rva0030B378Element();Rva0030B378Element(const Rva0030B378Element&);~Rva0030B378Element();Rva0030B378Element&operator=(const Rva0030B378Element&); bool operator<(const Rva0030B378Element&)const; bool operator==(const Rva0030B378Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0030B378Element * _STL::__copy_backward_ptrs<Rva0030B378Element *, Rva0030B378Element *>(Rva0030B378Element *, Rva0030B378Element *, Rva0030B378Element *, _STL::__false_type const &);
