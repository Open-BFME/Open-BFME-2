// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct Rva001DF88CEntry { Rva001DF88CEntry(); Rva001DF88CEntry(const Rva001DF88CEntry&); ~Rva001DF88CEntry(); private: unsigned char storage[48]; };
class Rva001DF88CVector { Rva001DF88CEntry*start,*finish,*end; public: void resize(unsigned,Rva001DF88CEntry); void resize(unsigned); };
namespace _STL {
template<> Rva001DF88CEntry*vector<Rva001DF88CEntry>::erase(Rva001DF88CEntry*,Rva001DF88CEntry*);
template<> void vector<Rva001DF88CEntry>::_M_fill_insert(Rva001DF88CEntry*,unsigned,const Rva001DF88CEntry&);
}
void Rva001DF88CVector::resize(unsigned n) {resize(n,Rva001DF88CEntry());}
void Rva001DF88CVector::resize(unsigned n,Rva001DF88CEntry value) {
 _STL::vector<Rva001DF88CEntry>*v=reinterpret_cast<_STL::vector<Rva001DF88CEntry>*>(this);
 if(n<v->size())v->erase(v->begin()+n,v->end());
 else v->insert(v->end(),n-v->size(),value);
}

// Reference: STLport4.5.3 resize semantics. Native ret52 body has
// record stride48 and a single nontrivial cleanup. The default wrapper
// constructs 48 bytes directly at its argument slot. Constructors and
// helper addresses are decoded from each target; opaque storage claims no
// application field layout or original type name. Existing providers are
// linked by aliases wherever a matched native body already owns the call.

#pragma comment(linker, "/alternatename:?erase@?$vector@URva001DF88CEntry@@V?$allocator@URva001DF88CEntry@@@_STL@@@_STL@@QAEPAURva001DF88CEntry@@PAU3@0@Z=?erase@?$vector@URva001DEF38Element@@V?$allocator@URva001DEF38Element@@@_STL@@@_STL@@QAEPAURva001DEF38Element@@PAU3@0@Z")

#pragma comment(linker, "/alternatename:??0Rva001DF88CEntry@@QAE@XZ=??0Rva001DE6E1@@QAE@XZ")
