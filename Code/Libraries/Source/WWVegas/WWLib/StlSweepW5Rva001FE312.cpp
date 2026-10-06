// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva001FE312Element {Rva001FE312Element();Rva001FE312Element(const Rva001FE312Element&);Rva001FE312Element&operator=(const Rva001FE312Element&);~Rva001FE312Element(){}char bytes[8]; bool operator==(const Rva001FE312Element&)const;};
template class _STL::hash_map<int,Rva001FE312Element>;
