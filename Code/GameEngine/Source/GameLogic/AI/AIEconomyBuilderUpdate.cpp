// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common
// AIEconomyBuilder::update, native 004EA7FB..004EA93F (324B).
// WB1382C30 identifies the update. Constructor4EAAF3 and destructor4EA3B8
// establish its secondary receiver at+C. Native bytes establish pending
// farm removal, counters and optional farm initialization; field-purpose
// names not corroborated by a named target remain neutral.
// The zero-op compiler barrier preserves native player+68 store before
// unknown+8 clear. All calls and the complete EH graph use owned providers.
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "GameLogicObjectLookupView.h"
class AIEconomyBuilder;
class Rva002A9BF2;
class AIDifficulty { public: bool allowEconomyUpgrade(Rva002A9BF2 *); };
int Rva0058AEB6Get();
extern GameLogic *TheGameLogic;
class Rva004E9378 { public: bool rva004E9378(); };
class Rva00596F18 { public: void rva00596FF5(unsigned char); };
class Bridge { public: void setBridgeObjectID(ObjectID); };
class ModuleData;
namespace _STL {
template<class T> class allocator {};
template<class T,class A=allocator<T> > class vector { public: T *erase(T *); void push_back(const T &); T *begin,*end,*capacity; };
}
class EconomyUpdateFarm {
public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void start(Rva002A9BF2 *,int);
 void setPlayer(Rva002A9BF2 *p) { player=p; }
 void setUnknown08(int v) { unknown08=v; }
 float priority; int unknown08; AsciiString name; int state;
 char gap14[0x64-0x14]; bool claimed; char gap65[3]; Rva002A9BF2 *player; int workers;
};
class EconomyPrimaryBase { public: virtual void a0(); virtual void a1(); virtual ~EconomyPrimaryBase(); int a4,a8; };
class Rva00506B1B { public: virtual ~Rva00506B1B(); virtual void update(); virtual void reset(); bool flag; };
class AIEconomyBuilder : public EconomyPrimaryBase, public Rva00506B1B { public: virtual void update(); bool needMoreFarms(int *); AsciiString getFarmTemplateName(); class Rva004EA4E5Farm *findAvailableFarm(); Rva002A9BF2 *player; unsigned farms,production; int lastFarm; _STL::vector<void *> pending; };
void AIEconomyBuilder::update() {
 void **it=pending.begin;
 void **end=pending.end;
 while(it!=end) {
  EconomyUpdateFarm *farm=static_cast<EconomyUpdateFarm *>(*it);
  if(reinterpret_cast<Rva004E9378 *>(farm)->rva004E9378()) {
   --production;
   if(farm->state==2) ++farms;
   else if(farm->state==3) { lastFarm=-1; ++farm->workers; farm->claimed=false; }
   it=pending.erase(it);
   end=pending.end;
  } else ++it;
 }
 int priority=0;
 AIEconomyBuilder *owner=this;
 if(owner->needMoreFarms(&priority) && reinterpret_cast<AIDifficulty *>(Rva0058AEB6Get())->allowEconomyUpgrade(player)) {
  EconomyUpdateFarm *farm=reinterpret_cast<EconomyUpdateFarm *>(owner->findAvailableFarm());
  const ModuleData *selected=reinterpret_cast<const ModuleData *>(farm);
  if(farm) {
   AsciiString type=owner->getFarmTemplateName();
   if(reinterpret_cast<const StringBase<char> &>(type).compare(reinterpret_cast<const StringBase<char> &>(AsciiString::TheEmptyString))) {
    farm->priority=static_cast<float>(priority);
    reinterpret_cast<Bridge *>(farm)->setBridgeObjectID(static_cast<ObjectID>(reinterpret_cast<unsigned>(owner)));
    reinterpret_cast<Rva00596F18 *>(farm)->rva00596FF5(1);
    farm->name=type;
    farm->setPlayer(player);_ReadWriteBarrier();
    farm->setUnknown08(0);
    farm->start(player,0);
    ++production;
    reinterpret_cast<_STL::vector<const ModuleData *> &>(pending).push_back(selected);
    lastFarm=TheGameLogic->getFrame();
   }
  }
 }
}
