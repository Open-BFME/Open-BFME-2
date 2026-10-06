// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
#include <memory>

struct Rva0033C432Element { unsigned prefix[2];int key;bool operator<(const Rva0033C432Element&b)const {return key<b.key;}bool operator==(const Rva0033C432Element&b)const {return key==b.key;} };
template class _STL::set<Rva0033C432Element>;
