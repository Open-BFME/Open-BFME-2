// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
#include <memory>

struct Rva00380DA3Element { unsigned words[4];Rva00380DA3Element();Rva00380DA3Element(const Rva00380DA3Element&b){words[0]=b.words[0];words[1]=b.words[1];words[2]=b.words[2];words[3]=b.words[3];}bool operator<(const Rva00380DA3Element&)const;bool operator==(const Rva00380DA3Element&)const; };
template class _STL::hash_map<int,Rva00380DA3Element>;
