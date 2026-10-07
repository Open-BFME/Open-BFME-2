// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O2 /Og- /EHsc /MD /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>

struct Rva00023AB0Element { char bytes[1]; bool operator<(const Rva00023AB0Element&)const; bool operator==(const Rva00023AB0Element&)const; };
template class _STL::map<int,Rva00023AB0Element>;
