// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva0022D85DElement {Rva0022D85DElement();Rva0022D85DElement(const Rva0022D85DElement&);Rva0022D85DElement&operator=(const Rva0022D85DElement&);~Rva0022D85DElement(){}char bytes[8]; bool operator==(const Rva0022D85DElement&)const;};
template class _STL::hash_map<int,Rva0022D85DElement>;
