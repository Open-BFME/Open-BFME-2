// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0051FBFFElement { char bytes[9];Rva0051FBFFElement();Rva0051FBFFElement(const Rva0051FBFFElement&);~Rva0051FBFFElement();Rva0051FBFFElement&operator=(const Rva0051FBFFElement&); bool operator<(const Rva0051FBFFElement&)const; bool operator==(const Rva0051FBFFElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0051FBFFElement * _STL::__copy_backward_ptrs<Rva0051FBFFElement *, Rva0051FBFFElement *>(Rva0051FBFFElement *, Rva0051FBFFElement *, Rva0051FBFFElement *, _STL::__false_type const &);
