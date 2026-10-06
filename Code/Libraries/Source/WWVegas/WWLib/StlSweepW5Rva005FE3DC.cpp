// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005FE3DCElement { char bytes[9];Rva005FE3DCElement();Rva005FE3DCElement(const Rva005FE3DCElement&);~Rva005FE3DCElement();Rva005FE3DCElement&operator=(const Rva005FE3DCElement&); bool operator<(const Rva005FE3DCElement&)const; bool operator==(const Rva005FE3DCElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva005FE3DCElement * _STL::vector<Rva005FE3DCElement, _STL::allocator<Rva005FE3DCElement> >::_M_allocate_and_copy<Rva005FE3DCElement const *>(unsigned int, Rva005FE3DCElement const *, Rva005FE3DCElement const *);
