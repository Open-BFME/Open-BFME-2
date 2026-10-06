// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva0023ADC8Element {Rva0023ADC8Element();Rva0023ADC8Element(const Rva0023ADC8Element&);Rva0023ADC8Element&operator=(const Rva0023ADC8Element&);~Rva0023ADC8Element(){}char bytes[8]; bool operator==(const Rva0023ADC8Element&)const;};
template class _STL::hash_map<int,Rva0023ADC8Element>;
