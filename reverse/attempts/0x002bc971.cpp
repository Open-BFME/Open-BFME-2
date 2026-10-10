// ?rva002BC971@LivingWorldLogic@@QAEXPBV?$vector@PAUSetupPlayer@@V?$allocator@PAUSetupPlayer@@@_STL@@@_STL@@PAUSetupPlayer@@PBV?$vector@PAUSetupArmy@@V?$allocator@PAUSetupArmy@@@_STL@@@3@PAXPAVRva002BC8C9Vector@@PAUSetupSimulationVector@@@Z
// partial score=0.8 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native2BC971..2BCCBA RET24. WB D85CD0 names LivingWorldLogic::SetUpAutoResolveBattle.
// Target reads establish all view offsets. Native52B output records contain a
// 12B round/summary-word tree and a12B bonus-vector header, then three floats,
// two pointers and two ints. Actual application record names remain unknown.
#include <map>
#include <vector>
#include "ascii_string.h"
struct Rva00318CEBOther {char gap[0x14];int playerID;};
class Rva00318CEB {public:bool rva00318CEB(const Rva00318CEBOther*);};
class Rva002E071E {public:bool rva002E071E(const Rva002E071E*) const;};
class Rva0020EB4EOuter {public:void rva0020EB4E(void*);};
class Rva003F7478 {public:void rva003F7465(float);void rva003F7478(float);};
class Rva003F74A0 {public:void rva003F74A0(float);};
class LivingWorldAutoResolveBattleBonus {public:void GetFinalBonuses(float*,float*,float*);};
class Rva004E05E9DwordField {public:int get()const;};
class LivingWorldAutoResolveReinforcementSchedule {public:int getRoundForArmyNumber(int);};
class LivingWorldAutoResolveResourceBonusSchedule {public:int*getBonusForResourceAmount(int);};
struct Rva00413E27Bucket;
class Rva00413E27 {public:Rva00413E27Bucket*rva00413E27(int);};
class Rva004134E3 {public:int*rva004134E3(int);};
class Rva0022C2A1Subsystem;class Rva0022C316Subsystem;class Rva0022C38BSubsystem;class Rva0022AAC7Subsystem;
extern Rva0022C2A1Subsystem *TheLivingWorldAutoResolveReinforcementScheduleStore;
extern Rva0022C316Subsystem *TheLivingWorldAutoResolveResourceBonusScheduleStore;
extern Rva0022C38BSubsystem *TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore;
extern Rva0022AAC7Subsystem *TheLivingWorldAutoResolveHandicapStore;
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const AsciiString&);};extern NameKeyGenerator*TheNameKeyGenerator;
class PlayerTemplate {public:char gap[0x154];};
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
namespace _STL {template<> RoundWordTree::iterator RoundWordTree::insert_equal(const RoundWordPair&);}
struct SetupRecord52 {
 RoundWordTree armies;
 _STL::vector<Rva0040DC56Element> bonuses;
 float weapon,armor,experience;void*science;void*simulation;int side,playerID;
};
class Rva002BC8C9Vector {public:void resize(unsigned);SetupRecord52*begin,*end,*capacity;};
class Rva003805BB {public:
 virtual void slot0();virtual void slot1();virtual void update(int);
 bool rva003805BB(float,bool);void rva002E6A93(int);
};
struct SetupSimulation44 {Rva003805BB object;const void*templateValues;char gap08[0x14-8];int team;char gap18[0x2C-0x18];};
struct SetupSimulationVector {SetupSimulation44 *begin,*end,*capacity;};
class LivingWorldLogic {public:
 void rva002BC971(const _STL::vector<SetupPlayer*>*,SetupPlayer*,const _STL::vector<SetupArmy*>*,void*,Rva002BC8C9Vector*,SetupSimulationVector*);
 char gap00[0xB0];Rva0020EB4EOuter*regionBonuses;
};
void LivingWorldLogic::rva002BC971(const _STL::vector<SetupPlayer*>*players,SetupPlayer*sidePlayer,const _STL::vector<SetupArmy*>*armies,void*context,Rva002BC8C9Vector*out,SetupSimulationVector*simulation)
{
 unsigned count=players->size();out->resize(count);
 if(!sidePlayer) sidePlayer=(*players)[0];
 for(unsigned i=0;i<count;++i) {
  SetupPlayer*player=(*players)[i];
  int side=!((Rva002E071E*)player)->rva002E071E((Rva002E071E*)sidePlayer);
  out->begin[i].side=side;out->begin[i].playerID=player->playerID;
  LivingWorldAutoResolveReinforcementSchedule *schedule=(LivingWorldAutoResolveReinforcementSchedule*)((char*)TheLivingWorldAutoResolveReinforcementScheduleStore+0x0C+side*16);
  int number=0;
  for(unsigned j=0;j<armies->size();++j) {
   SetupArmy*army=(*armies)[j];
   if(((Rva00318CEB*)army)->rva00318CEB((const Rva00318CEBOther*)player)) {
    int round;
    if(!army->name.isEmpty())round=schedule->getRoundForArmyNumber(number++);else round=0;
    RoundWordPair value(round,army->summaryWord);out->begin[i].armies.insert_equal(value);
   }
  }
  Rva002BB7AA bonus((int)context,(int)player);
  regionBonuses->rva0020EB4E(&bonus);
  ((Rva003F7478*)&bonus)->rva003F7465(player->weaponPercent*0.01f+1.0f);
  ((Rva003F7478*)&bonus)->rva003F7478(player->armorPercent*0.01f+1.0f);
  ((Rva003F74A0*)&bonus)->rva003F74A0(player->experiencePercent*0.01f+1.0f);
  ((LivingWorldAutoResolveBattleBonus*)&bonus)->GetFinalBonuses(&out->begin[i].weapon,&out->begin[i].armor,&out->begin[i].experience);
  out->begin[i].bonuses=bonus.bonuses;
  Rva00413E27Bucket *bucket=((Rva00413E27*)TheLivingWorldAutoResolveResourceBonusScheduleStore)->rva00413E27(player->faction);
  if(bucket) {
   int*word=((LivingWorldAutoResolveResourceBonusSchedule*)bucket)->getBonusForResourceAmount(player->resources);
   if(word) {out->begin[i].weapon*=((float*)word)[1];out->begin[i].armor*=((float*)word)[2];}
  }
  int*handicap=((Rva004134E3*)TheLivingWorldAutoResolveHandicapStore)->rva004134E3(player->handicap);
  out->begin[i].weapon*=((float*)handicap)[1];out->begin[i].armor*=((float*)handicap)[2];out->begin[i].experience*=((float*)handicap)[3];
  if(simulation) {
   out->begin[i].science=((Rva00413E27*)TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore)->rva00413E27(player->faction);
   const PlayerTemplate*pt=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(*(AsciiString*)((char*)player->faction+4)));
   if(pt)simulation->begin[i].templateValues=(const void*)((char*)pt+0x154);
   simulation->begin[i].object.rva003805BB(player->skillPoints,false);
   simulation->begin[i].object.rva002E6A93(simulation->begin[i].team);
   simulation->begin[i].object.update(((Rva004E05E9DwordField*)player)->get());
   out->begin[i].simulation=simulation->begin+i;
  }
 }
}
