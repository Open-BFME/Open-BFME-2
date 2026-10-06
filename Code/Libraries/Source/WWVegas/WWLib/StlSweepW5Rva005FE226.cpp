// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005FE226Element {Rva005FE226Element();Rva005FE226Element(const Rva005FE226Element&);Rva005FE226Element&operator=(const Rva005FE226Element&);~Rva005FE226Element(){}char bytes[12]; bool operator==(const Rva005FE226Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva005FE226Element * _STL::__uninitialized_copy<Rva005FE226Element const *, Rva005FE226Element *>(Rva005FE226Element const *, Rva005FE226Element const *, Rva005FE226Element *, _STL::__false_type const &);
