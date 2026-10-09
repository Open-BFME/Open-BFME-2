// cl: /O1 /Oy- /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 003F4D09..003F4DA9 is a complete 160-byte member with no calls.
// LivingWorldBattle and the 28-byte side / 48-byte participant vectors are
// independently established by the WorldBuilder evidence in Rva003F498ALoops.cpp.
// Target-only evidence: region pointer at +24 and its region ID at +13C;
// participant owner pointer at +0 and owner ID at +14. The returned pointer
// belongs to the participant matching that region ID. Original method name
// remains unknown. BFME1 LivingWorldBattle source search supplied no clean
// implementation at donor 9cbfb551fe20dae985f91f2319d8997287b6a705.
#include <vector>
class Rva003F498ACallback;
struct Rva003F498AInner {
    int unk0;
    _STL::vector<int> vals;
    char pad16[12];
    int tail[5];
};

struct Rva003F498AOuter {
    int unk0;
    _STL::vector<Rva003F498AInner> inners;
    _STL::vector<int> ints;
    bool rva003F4342(Rva003F498ACallback *cb);
};

struct Rva003F4D09Region { char pad[0x13c]; int id; };
class LivingWorldBattle {
    char m_pad0[0x18];
    _STL::vector<Rva003F498AOuter> m_outers;
    Rva003F4D09Region *m_region;
public:
    void rva003F498A(Rva003F498ACallback* cb);
    void *rva003F4D09();
    int GetRetreatedPlayerCount(int idx);
    int GetRetreatedPlayerID(int outerIdx, int innerIdx);
    int* rva003F46F2(int outerIdx, int innerIdx);
    void rva003F470E(int outerIdx, int innerIdx, void *p);
    int rva003F48FE(int outerIdx, int middleIdx, int innerIdx);
    int rva003F4921(int outerIdx, int middleIdx, int innerIdx);
    bool rva003F486C(int id);
    bool rva003F48EF(void *p);
    int rva003F4752(void *p);
    int rva003F4798(int outerIdx, int id);
    int rva003F4FAA(int outerIdx, void *p);
    int rva003F47E6(int outerIdx);
    int rva003F4831();
    int rva003F45DF();
    bool rva003F4538();
    int GetTeamNumberForSide(int idx);
    Rva003F498AOuter *rva003F4634(void *p);
    void *rva003F4DEE(void *p);
    void *rva003F4FBD(void *p);
    void rva003F4944(Rva003F498ACallback *cb);
};

void *LivingWorldBattle::rva003F4D09() {
 int id=m_region->id;
 if(id!=-1) {
  for(unsigned i=0;i<m_outers.size();++i) {
   Rva003F498AOuter &side=m_outers[i];
   for(unsigned j=0;j<side.inners.size();++j) {
    Rva003F498AInner &in=side.inners[j];
    if(id==*(int*)((char*)(void*)in.unk0+0x14))
     return (void*)side.inners[j].unk0;
   }
  }
 }
 return 0;
}
