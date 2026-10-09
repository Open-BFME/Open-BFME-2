// cl: /O1 /Oy- /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Native215AF1..215B14 resize and215B14..215C38 append-or-replace parser.
// Existing parser callback215C38 and find215479 bind the PlayerAITypeSet.
// Target record copy2154F3 and destructor2154BE establish the name and
// owning library vector. Rva15334F default construction clears that same16B
// prefix. Borrowed storage views retain existing provider ABI spellings;
// these equivalent prefix views do not prove a source-level inheritance tree.
// The ordinary Rva15334F destructor is a full53B relocation twin of2154BE.
// Resize semantics follow clean BF1 BfmeConv1950; native parser independently
// establishes growth size+size/2+8 and ownership swaps. End before destination
// iterator initialization restores retail instruction scheduling.
// Its ordinary inline library view remains visible for allocator lifetimes.
// The29B provider is instantiated in PlayerAITypeSetVectorBase.cpp; this
// frame-pointer TU emits an unclaimed32B COMDAT that must lose to the
// retail-proven29B copy. No link-census credit is asserted without its index.
#include "ascii_string.h"
#include <vector>
class Rva0015334F { public: __declspec(nothrow) Rva0015334F(); public: __declspec(noinline) ~Rva0015334F(); private: AsciiString name; _STL::vector<AsciiString> libraries; };
struct BfmeItemERE : Rva0015334F { __declspec(nothrow) __forceinline BfmeItemERE():Rva0015334F(){} BfmeItemERE(const BfmeItemERE&); ~BfmeItemERE(); };
class BfmeVecERE {public:void bfmeResizeERE(unsigned count,BfmeItemERE item);};
class Rva00215AF1 { public: void rva00215AF1(unsigned count); };
void Rva00215AF1::rva00215AF1(unsigned count) { ((BfmeVecERE*)this)->bfmeResizeERE(count,BfmeItemERE()); }

class INI;
struct BfmeVectorRecord0002154F3 : Rva0015334F { __declspec(nothrow) __forceinline BfmeVectorRecord0002154F3():Rva0015334F(){} BfmeVectorRecord0002154F3(const BfmeVectorRecord0002154F3&); ~BfmeVectorRecord0002154F3(); };
struct Rva0021582CRecord { char storage[16]; };
struct BfmeE12 { float x,y,z; };
namespace _STL { template<> vector<BfmeVectorRecord0002154F3>::~vector(); template<> void vector<BfmeVectorRecord0002154F3>::push_back(const BfmeVectorRecord0002154F3&); template<> void vector<Rva0021582CRecord>::reserve(unsigned); }
class Rva0021572A : public BfmeVectorRecord0002154F3 { public:Rva0021572A(INI*); __forceinline ~Rva0021572A(){} };
class Rva0021545C { public:void rva0021545C(Rva0021545C*); };
class PlayerAITypeSet { public:void rva00215B14(INI*); int rva00215479(const AsciiString&);private: char prefix[12]; _STL::vector<BfmeVectorRecord0002154F3> records; };
void PlayerAITypeSet::rva00215B14(INI *ini) {
 Rva0021572A parsed(ini);
 int index=rva00215479(reinterpret_cast<const AsciiString&>(parsed));
 if(index==-1) {
  if(records.size()>=records.capacity()) {
   _STL::vector<BfmeVectorRecord0002154F3> tmp;
   reinterpret_cast<_STL::vector<Rva0021582CRecord>&>(tmp).reserve(records.size()+records.size()/2+8);
   reinterpret_cast<Rva00215AF1&>(tmp).rva00215AF1(records.size());
   BfmeVectorRecord0002154F3 *p=records.begin(),*end=records.end(),*dst=tmp.begin();
   for(;p!=end;++p,++dst)
    reinterpret_cast<Rva0021545C*>(dst)->rva0021545C(reinterpret_cast<Rva0021545C*>(p));
   reinterpret_cast<_STL::vector<BfmeE12>&>(records).swap(reinterpret_cast<_STL::vector<BfmeE12>&>(tmp));
  }
  index=records.size();
  records.push_back(*reinterpret_cast<const BfmeVectorRecord0002154F3*>(&Rva0015334F()));
 }
 reinterpret_cast<Rva0021545C*>(&records[index])->rva0021545C(reinterpret_cast<Rva0021545C*>(&parsed));
}



__declspec(noinline) Rva0015334F::~Rva0015334F() {}
