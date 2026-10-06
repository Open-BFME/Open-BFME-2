// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <set>

struct Rva0051C04AElement { int words[1]; bool operator<(const Rva0051C04AElement&b)const { return words[0]<b.words[0]; } bool operator==(const Rva0051C04AElement&b)const {return words[0]==b.words[0];} };
template class _STL::set<Rva0051C04AElement>;
