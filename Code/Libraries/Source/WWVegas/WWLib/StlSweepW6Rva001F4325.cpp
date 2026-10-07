// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_set>
#include <memory>
#include <string>

struct Rva001F4325Element { unsigned words[1];operator unsigned() const {return words[0];}bool operator<(const Rva001F4325Element& b)const{return words[0]<b.words[0];}bool operator==(const Rva001F4325Element& b)const{return words[0]==b.words[0];} };
template class _STL::hash_set<Rva001F4325Element,_STL::hash<unsigned> >;
