// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0022105BElement { char bytes[9];Rva0022105BElement();Rva0022105BElement(const Rva0022105BElement&);~Rva0022105BElement();Rva0022105BElement&operator=(const Rva0022105BElement&); bool operator<(const Rva0022105BElement&)const; bool operator==(const Rva0022105BElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0022105BElement * _STL::vector<Rva0022105BElement, _STL::allocator<Rva0022105BElement> >::_M_allocate_and_copy<Rva0022105BElement const *>(unsigned int, Rva0022105BElement const *, Rva0022105BElement const *);
