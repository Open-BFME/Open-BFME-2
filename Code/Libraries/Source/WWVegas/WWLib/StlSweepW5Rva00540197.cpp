// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00540197Element { char bytes[9];Rva00540197Element();Rva00540197Element(const Rva00540197Element&);~Rva00540197Element();Rva00540197Element&operator=(const Rva00540197Element&); bool operator<(const Rva00540197Element&)const; bool operator==(const Rva00540197Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00540197Element * _STL::__copy_backward_ptrs<Rva00540197Element *, Rva00540197Element *>(Rva00540197Element *, Rva00540197Element *, Rva00540197Element *, _STL::__false_type const &);
