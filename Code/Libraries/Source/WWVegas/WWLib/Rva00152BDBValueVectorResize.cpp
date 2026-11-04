// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct Rva00152BDBEntry { Rva00152BDBEntry(); Rva00152BDBEntry(const Rva00152BDBEntry&); ~Rva00152BDBEntry(); private: unsigned char storage[36]; };
class Rva00152BDBVector
{
public:
	void resize(unsigned);
	void resize(unsigned,Rva00152BDBEntry);
private:
	Rva00152BDBEntry *start; // +0x00
	Rva00152BDBEntry *finish; // +0x04
	Rva00152BDBEntry *end; // +0x08
};
// Native1524F9 owns the fill helper for the same36-byte element frame.
// Keep this caller's opaque value type and bind only that operation.
struct Rva001524F9Element;
namespace _STL {
template<> void vector<Rva001524F9Element>::_M_fill_insert(Rva001524F9Element*,unsigned,const Rva001524F9Element&);
template<> Rva00152BDBEntry*vector<Rva00152BDBEntry>::erase(Rva00152BDBEntry*,Rva00152BDBEntry*);
template<> void vector<Rva00152BDBEntry>::_M_fill_insert(Rva00152BDBEntry*,unsigned,const Rva00152BDBEntry&);
}
// Inline ABI adapter, with the caller's original argument evaluation types.
class Native36ByteFillView {
public:
 __forceinline void fill(Rva00152BDBEntry *position,unsigned count,const Rva00152BDBEntry &value) {
  reinterpret_cast<_STL::vector<Rva001524F9Element>*>(this)->_M_fill_insert(
   reinterpret_cast<Rva001524F9Element*>(position),count,
   reinterpret_cast<const Rva001524F9Element&>(value));
 }
};
void Rva00152BDBVector::resize(unsigned n) {resize(n,Rva00152BDBEntry());}
void Rva00152BDBVector::resize(unsigned n,Rva00152BDBEntry value) {
 _STL::vector<Rva00152BDBEntry>*v=reinterpret_cast<_STL::vector<Rva00152BDBEntry>*>(this);
 if(n<v->size())v->erase(v->begin()+n,v->end());
 else reinterpret_cast<Native36ByteFillView*>(this)->fill(v->end(),n-v->size(),value);
}

// Reference: STLport4.5.3 resize semantics. Native ret40 body has
// record stride36 and a single nontrivial cleanup. The default wrapper
// constructs 36 bytes directly at its argument slot. Constructors and
// helper addresses are decoded from each target; opaque storage claims no
// application field layout or original type name. Existing providers are
// linked by aliases wherever a matched native body already owns the call.

#pragma comment(linker, "/alternatename:?erase@?$vector@URva00152BDBEntry@@V?$allocator@URva00152BDBEntry@@@_STL@@@_STL@@QAEPAURva00152BDBEntry@@PAU3@0@Z=?EraseRange@Rva0015229CVector@@QAEPAURva0007BB16Record@@PAU2@0@Z")

#pragma comment(linker, "/alternatename:??1Rva00152BDBEntry@@QAE@XZ=??1Rva0007BB16Record@@QAE@XZ")

#pragma comment(linker, "/alternatename:??0Rva00152BDBEntry@@QAE@XZ=??0Rva00151248@@QAE@XZ")
