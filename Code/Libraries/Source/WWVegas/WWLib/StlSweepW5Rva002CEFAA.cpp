// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <string>
#include <utility>

struct Rva002CEFAAElement { char bytes[1]; Rva002CEFAAElement();Rva002CEFAAElement(const Rva002CEFAAElement&);~Rva002CEFAAElement();Rva002CEFAAElement& operator=(const Rva002CEFAAElement&); };
template class _STL::map<_STL::pair<int,int>,Rva002CEFAAElement>;
