// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0038151EElement { char bytes[9];Rva0038151EElement();Rva0038151EElement(const Rva0038151EElement&);~Rva0038151EElement();Rva0038151EElement&operator=(const Rva0038151EElement&); bool operator<(const Rva0038151EElement&)const; bool operator==(const Rva0038151EElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0038151EElement * _STL::__copy_backward_ptrs<Rva0038151EElement *, Rva0038151EElement *>(Rva0038151EElement *, Rva0038151EElement *, Rva0038151EElement *, _STL::__false_type const &);
