// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00469C85Element { char bytes[9];Rva00469C85Element();Rva00469C85Element(const Rva00469C85Element&);~Rva00469C85Element();Rva00469C85Element&operator=(const Rva00469C85Element&); bool operator<(const Rva00469C85Element&)const; bool operator==(const Rva00469C85Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00469C85Element * _STL::__copy_backward_ptrs<Rva00469C85Element *, Rva00469C85Element *>(Rva00469C85Element *, Rva00469C85Element *, Rva00469C85Element *, _STL::__false_type const &);
