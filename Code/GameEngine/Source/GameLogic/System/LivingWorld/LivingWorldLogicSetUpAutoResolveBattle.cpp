// ?SetUpAutoResolveBattle@LivingWorldLogic@@QAEXPBV?$vector@PAUSetupPlayer@@V?$allocator@PAUSetupPlayer@@@_STL@@@_STL@@PAUSetupPlayer@@PBV?$vector@PAUSetupArmy@@V?$allocator@PAUSetupArmy@@@_STL@@@3@PAXPAV?$vector@USetupRecord52@@V?$allocator@USetupRecord52@@@_STL@@@3@PAV?$vector@USetupSimulation44@@V?$allocator@USetupSimulation44@@@_STL@@@3@@Z
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native2BC971..2BCCBC, 843B, RET0x18. WB D85CD0 names LivingWorldLogic::SetUpAutoResolveBattle.
// Target reads establish all view offsets. Native52B output records contain a
// 12B round/summary-word tree and a12B bonus-vector header, then three floats,
// two pointers and two ints. Actual application record names remain unknown.
// The actual STL tree insertion definition makes its discarded iterator's
// lifetime visible; no placement construction or explicit stack slot is needed.
// Target accesses establish these record views; WB establishes the method name.
// Schedule globals and calls use existing ledger providers, without new pins.
#include <map>
#include <vector>
#include "ascii_string.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> bool less<int>::operator()(int const &, int const &) const; }
// bfme link decl-only end
struct Rva00318CEBOther {char gap[0x14];int playerID;};
class Rva00318CEB {public:bool rva00318CEB(const Rva00318CEBOther*);};
#include "../../../../Include/GameLogic/Rva002E071E.h"
class Rva0020EB4EOuter {public:void rva0020EB4E(void*);};
class Rva003F7478 {public:void rva003F7465(float);void rva003F7478(float);};
class Rva003F74A0 {public:void rva003F74A0(float);};
class LivingWorldAutoResolveBattleBonus {public:void GetFinalBonuses(float*,float*,float*);};
#include "../../../../Include/GameNetwork/Rva004E05E9DwordField.h"
class LivingWorldAutoResolveReinforcementSchedule {public:int getRoundForArmyNumber(int);};
class LivingWorldAutoResolveResourceBonusSchedule {public:int*getBonusForResourceAmount(int);};
struct Rva00413E27Bucket;
class Rva00413E27 {public:Rva00413E27Bucket*rva00413E27(int);};
class Rva004134E3 {public:int*rva004134E3(int);};
class Rva0022C2A1Subsystem;class Rva0022C316Subsystem;class Rva0022C38BSubsystem;class Rva0022AAC7Subsystem;
extern void *TheLivingWorldAutoResolveReinforcementScheduleStore;
extern Rva0022C316Subsystem *TheLivingWorldAutoResolveResourceBonusScheduleStore;
extern Rva0022C38BSubsystem *TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore;
struct HandicapStore; extern HandicapStore *TheLivingWorldAutoResolveHandicapStore;
enum NameKeyType { NAMEKEY_INVALID=0 };
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator*TheNameKeyGenerator;
#include "../../../../Include/Common/PlayerTemplate.h"
class PlayerTemplateStore {public:const PlayerTemplate*findPlayerTemplate(NameKeyType)const;};extern PlayerTemplateStore*ThePlayerTemplateStore;
struct SetupPlayer {
 char gap00[0x14];int playerID;char gap18[0x38-0x18];int handicap;int opaque3C;int faction;
 char gap44[0x1C8-0x44];float skillPoints;char gap1CC[0x25C-0x1CC];int resources;
 char gap260[8];int weaponPercent,armorPercent,experiencePercent;
};
struct SetupArmy {char gap00[0x18];AsciiString name;char gap1C[0x78-0x1C];int summaryWord;};
struct Rva0040DC56Element {char bytes[16];};
namespace _STL {
 template<> vector<Rva0040DC56Element>&vector<Rva0040DC56Element>::operator=(const vector<Rva0040DC56Element>&);
}
// Transparent no-storage adapter chains the existing44B constructor and54B
// destructor views; it makes no claim about original C++ inheritance.
class Rva002BB281 {public:~Rva002BB281();char opaque00[0x2C];_STL::vector<Rva0040DC56Element> bonuses;};
class Rva002BB7AA : public Rva002BB281 {public:Rva002BB7AA(int,int);};
typedef _STL::pair<const int,int> RoundWordPair;
typedef _STL::_Rb_tree<int,RoundWordPair,_STL::_Select1st<RoundWordPair>,_STL::less<int>,_STL::allocator<RoundWordPair> > RoundWordTree;

struct SetupRecord52 {
 RoundWordTree armies;
 _STL::vector<Rva0040DC56Element> bonuses;
 float weapon,armor,experience;void*science;void*simulation;int side,playerID;
};
typedef _STL::vector<SetupRecord52> OutputVector;
class Rva002BC8C9Vector {public:void resize(unsigned);SetupRecord52*begin,*end,*capacity;};
// 0x003805BB is rowed as Rva00380200::rva003805BB (Rva00380200Getter.cpp).
class Rva00380200 { public: bool rva003805BB(float value, bool flag); };

class Rva003805BB {public:
 virtual void slot0();virtual void slot1();virtual void update(int);
};
// 0x002E6A93 (store +0x18) is ICF-folded with GameSlot::setTeamNumber.
class GameSlot {public:void setTeamNumber(int teamNumber);};
struct SetupSimulation44 {Rva003805BB object;const void*templateValues;char gap08[0x14-8];int team;char gap18[0x2C-0x18];};
struct SimulationHeader {SetupSimulation44 *begin,*end,*capacity;};
typedef _STL::vector<SetupSimulation44> SetupSimulationVector;
#include "../../../../Include/GameLogic/LivingWorldLogic.h"
static __forceinline void Scale(float factor,float &value){const float &original=value;value=original*factor;}
static __forceinline void ScaleX(float &value,float factor){value=value*factor;}
void LivingWorldLogic::SetUpAutoResolveBattle(const _STL::vector<SetupPlayer*>*players,SetupPlayer*sidePlayer,const _STL::vector<SetupArmy*>*armies,void*context,OutputVector*out,SetupSimulationVector*simulation)
{
 unsigned count=players->size();((Rva002BC8C9Vector*)out)->resize(count);
 if(!sidePlayer) sidePlayer=(*players)[0];
 for(unsigned i=0;i<count;++i) {
  SetupPlayer*player=(*players)[i];
  int side=!((Rva002E071E*)player)->rva002E071E((Rva002E071E*)sidePlayer);
  out->begin()[i].side=side;int id=player->playerID;out->begin()[i].playerID=id;
  LivingWorldAutoResolveReinforcementSchedule *schedule=(LivingWorldAutoResolveReinforcementSchedule*)((char*)TheLivingWorldAutoResolveReinforcementScheduleStore+0x0C+side*16);
  int number=0;
  for(unsigned j=0;j<armies->size();++j) {
   SetupArmy*army=(*armies)[j];
   if(((Rva00318CEB*)army)->rva00318CEB((const Rva00318CEBOther*)player)) {
    int round;
    if(!army->name.isEmpty())round=schedule->getRoundForArmyNumber(number++);else round=0;
    int summary=army->summaryWord;RoundWordPair value(round,summary);SetupRecord52 *base=out->begin();base[i].armies.insert_equal(value);
   }
  }
  Rva002BB7AA bonus((int)context,(int)player);
  ((Rva0020EB4EOuter *)fieldB0)->rva0020EB4E(&bonus);
  ((Rva003F7478*)&bonus)->rva003F7465(player->weaponPercent*0.01f+1.0f);
  ((Rva003F7478*)&bonus)->rva003F7478(player->armorPercent*0.01f+1.0f);
  ((Rva003F74A0*)&bonus)->rva003F74A0(player->experiencePercent*0.01f+1.0f);
  ((LivingWorldAutoResolveBattleBonus*)&bonus)->GetFinalBonuses(&out->begin()[i].weapon,&out->begin()[i].armor,&out->begin()[i].experience);
  out->begin()[i].bonuses=bonus.bonuses;
  Rva00413E27Bucket *bucket=((Rva00413E27*)TheLivingWorldAutoResolveResourceBonusScheduleStore)->rva00413E27(player->faction);
  if(bucket) {
   int*word=((LivingWorldAutoResolveResourceBonusSchedule*)bucket)->getBonusForResourceAmount(player->resources);
   if(word) {ScaleX(out->begin()[i].weapon,((float*)word)[1]);Scale(((float*)word)[2],out->begin()[i].armor);}
  }
  int*handicap=((Rva004134E3*)TheLivingWorldAutoResolveHandicapStore)->rva004134E3(player->handicap);
  Scale(((float*)handicap)[1],out->begin()[i].weapon);Scale(((float*)handicap)[2],out->begin()[i].armor);Scale(((float*)handicap)[3],out->begin()[i].experience);
  if(simulation) {
   int faction=player->faction;SetupRecord52 *records=out->begin();records[i].science=((Rva00413E27*)TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore)->rva00413E27(faction);
   const PlayerTemplate*pt=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(*(AsciiString*)((char*)player->faction+4)));
   if(pt){SetupSimulation44 *sim=((SimulationHeader*)simulation)->begin+i;sim->templateValues=(const void*)((char*)pt+0x154);}
   ((Rva00380200*)&((SimulationHeader*)simulation)->begin[i].object)->rva003805BB(player->skillPoints,false);
   ((GameSlot*)&simulation->begin()[i].object)->setTeamNumber(((SimulationHeader*)simulation)->begin[i].team);
   simulation->begin()[i].object.update(((Rva004E05E9DwordField*)player)->get());
   out->begin()[i].simulation=((SimulationHeader*)simulation)->begin+i;
  }
 }
}
