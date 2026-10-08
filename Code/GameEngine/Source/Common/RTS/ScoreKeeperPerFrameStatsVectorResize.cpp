// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// Clean reference: BF1 ba7ddda Coord3DVectorResizeThunk.cpp establishes the
// retail by-value resize variant of STLport4.5.3. Here native39D170..39D1D0
// takes a20-byte owned fill argument (ret24); WBFA55B0 confirms by-value
// storage and erase/fill-insert calls. C1AD6C names PerFrameStats. Retain
// existing address-named record/erase providers and canonical Snapshot
// cleanup. The old bank guessed five independent ints and lost this EH frame.
// This recovery is96 new bytes; the record destructor already has a real row.
#include <vector>
#include "Common/Snapshot.h"
class __declspec(novtable) Rva0039B893 : public Snapshot { public: Rva0039B893(); virtual __forceinline ~Rva0039B893(){}; int field04; float field08; short field0C,field0E,field10; protected: virtual void loadPostProcess();virtual void crc(Xfer*);virtual void xfer(Xfer*); };

// The default record constructor is visible here because native39D1D0 keeps
// its receiver in EDX across this call. This complete34-byte body also matches
// retail39B7FB and its C1AD6C snapshot vtable; no guessed constructor is used.
__declspec(noinline) Rva0039B893::Rva0039B893()
 : field04(0),field08(0.0f),field0C(0),field0E(0),field10(0) {}

struct Rva0039C415Element {unsigned words[5];};
namespace _STL {template<>void vector<Rva0039C415Element>::_M_fill_insert(Rva0039C415Element*,unsigned int,const Rva0039C415Element&);}
class Rva0039C190 {
public:
 Rva0039B893 *rva0039C190(Rva0039B893*,Rva0039B893*);
 void rva0039D170(unsigned int n,Rva0039B893 value);
 Rva0039B893 *start,*finish,*capacity;
};
void Rva0039C190::rva0039D170(unsigned int n,Rva0039B893 value){
 if(n<(unsigned int)(finish-start))rva0039C190(start+n,finish);
 else reinterpret_cast<_STL::vector<Rva0039C415Element>*>(this)->_M_fill_insert(reinterpret_cast<Rva0039C415Element*>(finish),n-(unsigned int)(finish-start),reinterpret_cast<const Rva0039C415Element&>(value));
}
