// ?rva00215B14@PlayerAITypeSet@@QAEXPAVINI@@@Z
// partial score=0.95 date=2026-10-10
// cl: /O1 /Oy- /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include "ascii_string.h"
#include <vector>
class Rva0015334F { public: __declspec(nothrow) Rva0015334F(); public: __forceinline ~Rva0015334F(); private: char storage[16]; };
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
   BfmeVectorRecord0002154F3 *dst=tmp.begin();
   for(BfmeVectorRecord0002154F3 *p=records.begin(),*end=records.end();p!=end;++p,++dst)
    reinterpret_cast<Rva0021545C*>(dst)->rva0021545C(reinterpret_cast<Rva0021545C*>(p));
   reinterpret_cast<_STL::vector<BfmeE12>&>(records).swap(reinterpret_cast<_STL::vector<BfmeE12>&>(tmp));
  }
  index=records.size();
  records.push_back(*reinterpret_cast<const BfmeVectorRecord0002154F3*>(&Rva0015334F()));
 }
 reinterpret_cast<Rva0021545C*>(&records[index])->rva0021545C(reinterpret_cast<Rva0021545C*>(&parsed));
}

__forceinline Rva0015334F::~Rva0015334F() { reinterpret_cast<BfmeVectorRecord0002154F3*>(this)->BfmeVectorRecord0002154F3::~BfmeVectorRecord0002154F3(); }
