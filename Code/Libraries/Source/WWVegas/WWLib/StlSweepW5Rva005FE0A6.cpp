// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005FE0A6Element {Rva005FE0A6Element();Rva005FE0A6Element(const Rva005FE0A6Element&);Rva005FE0A6Element&operator=(const Rva005FE0A6Element&);~Rva005FE0A6Element(){}char bytes[12]; bool operator==(const Rva005FE0A6Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::fill<Rva005FE0A6Element *, Rva005FE0A6Element>(Rva005FE0A6Element *, Rva005FE0A6Element *, Rva005FE0A6Element const &);
