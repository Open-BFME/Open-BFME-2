// ?AddHordeMember@SlaughterHordeContain@@QAEXPAVObject@@@Z
// partial score=0.9113924798525276 date=2026-10-10
// ?AddHordeMember@SlaughterHordeContain@@QAEXPAVObject@@@Z
// partial score=0.95 date=2026-10-10
// cl: /O1 /Ob2 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /ICode/GameEngine/Source/Common
// stlport
// ?AddHordeMember@SlaughterHordeContain@@QAEXPAVObject@@@Z retail 0x004808E8..0x00480DF4 (1292 bytes).
// WorldBuilder twin 0x011B5900 is SlaughterHordeContain::AddHordeMember
// (callgraph match / assert lines 254..347 of HordeContain/SlaughterHordeContain.cpp).
#include <math.h>
#include <bitset>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
enum CommandSourceType{CMD_FROM_AI=2};enum ObjectStatusTypes{STATUS_NONE=0};
enum DamageType{DAMAGE_NONE=0};enum DeathType{DEATH_NONE=0};
class Object;class Team;class ThingTemplate;class Player;
class Rva0039B7AD;
class Rva003B0D7C{public:void rva003B0D7C(int,Rva0039B7AD*,bool);};
class ScoreKeeper{public:void addObjectLost(const Object*);};
class Player{public:int ScaleMoney(int);float getProductionCostChangeBasedOnTemplate(const ThingTemplate*,bool);
 char pad[0x90];Rva003B0D7C money;char pad91[0x280-0x91];int color;
 char pad284[0x3bc-0x284];ScoreKeeper score;};
class MultiPlayMults{public:float getMoneyMult(int)const;};
class GlobalData{public:char pad[0xec4];MultiPlayMults mults;};extern GlobalData *TheWritableGlobalData;
class PlayerList{public:int rva002A7C0B(bool);};extern PlayerList *ThePlayerList;
class BfmeGlob939D{public:char bfmeCall939D();};
class ExperienceTracker{public:void rva0039B315(float,bool,bool,bool,int);};
class Rva0039ADF3{public:bool rva0039AE04()const;};
class Rva0028D796{public:int rva0028D796();};
class Drawable {public:void setDrawableHidden(bool);};
class Thing{public:Drawable *getDrawable()const;};
class Rva002716Holder{public:void rva00271601(unsigned char);};
class AICommandInterface{public:void aiIdle(CommandSourceType);};
class AIUpdateInterface{public:AICommandInterface *commands(){return (AICommandInterface*)((char*)this+0x20);}};
class Rva002AA292{public:bool rva002AA292(const int*)const;};
class Object{public:Player *getControllingPlayer()const;bool rva0028C15E(int,float*,int,int);
 bool testStatus(ObjectStatusTypes)const;void updateUpgradeModules();void rva0028DA28();void kill(DamageType,DeathType);void rva0028AFE7(Object*);const ThingTemplate *getTemplate()const{return tmplate;}Team *getTeam()const{return team;}
 char pad[4];ThingTemplate *tmplate;char pad8[0x38-8];Coord3D position;
 char pad44[0x74-0x44];ObjectID id;char pad78[4];ObjectID builder;char pad80[0x258-0x80];AIUpdateInterface *ai;
 char pad25C[0x264-0x25c];ExperienceTracker *tracker;char pad268[0x274-0x268];Object *containedBy;
 char pad278[0x284-0x278];_STL::_Base_bitset<32> upgrades;
 Team *team;
};
template<int N>class SlaughterAddSlots:public SlaughterAddSlots<N-1>{public:virtual void gap(char(*)[N]);};template<>class SlaughterAddSlots<0>{};
class GameTextInterface:public SlaughterAddSlots<17>{public:virtual const UnicodeString *text(const char*,bool*);};extern GameTextInterface *TheGameText;
class InGameUI:public SlaughterAddSlots<104>{public:virtual void floating(const UnicodeString*,const Coord3D*,unsigned int);};extern InGameUI *TheInGameUI;
struct BfmeDelayedLuaEventList{BfmeDelayedLuaEventList();~BfmeDelayedLuaEventList();char data[0x4c];};
class BfmeObjectEventDispatch{public:void rva003360D2(int,void*,BfmeDelayedLuaEventList*);};
class LuaScriptEngine;extern LuaScriptEngine *TheLuaScriptEngine;extern GameLogic *TheGameLogic;
float GetGameClientRandomValueReal(float,float,char*,int);
class Rva004783F4{public:Team *rva004783F4();};
class HordeGarrisonContain{public:virtual void rva00479ADA(Object*);virtual void rva00479B7F(Object*);};
class SlaughterAddTeam:public SlaughterAddSlots<21>{public:virtual void change(Team*);};
class Rva00588E44Contain:public SlaughterAddSlots<61>{public:virtual unsigned char test();};
class SlaughterAddCount:public SlaughterAddSlots<96>{public:virtual unsigned count(int);};
class Rva0047A040Base9E0{public:Rva00588E44Contain *rva00588BF3(void*,Object*);};
struct SlaughterAddData{char pad[0xd4];float multiplier;};
class SlaughterHordeContain:public SlaughterAddSlots<32>{public:
 virtual void remove(Object*);virtual bool consume(Object*);
 void AddHordeMember(Object*);
 const SlaughterAddData *data;Object *object;char padC[0x9e0-0xc];Rva0047A040Base9E0 base;
 unsigned int count;AsciiString templateName;
 private:void rva004804DD(Object*);
};
namespace _STL{template<>void _Base_bitset<32>::_M_do_or(const _Base_bitset<32>&);}
__forceinline long fast_float2long_round(float f)
{
 long i;
 __asm {
  fld [f]
  fistp [i]
 }
 return i;
}
__forceinline float fast_float_ceil(float f){return (float)ceil((double)f);}
#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))
void SlaughterHordeContain::AddHordeMember(Object *member)
{
 if(!member)return;Player *player=member->getControllingPlayer();if(!player)return;
 Object *me=object;bool consumeMember=consume(member);const SlaughterAddData *md=data;
 int value=((Rva0028D796*)member)->rva0028D796();
 if(consumeMember && value>0 && md->multiplier>0){
   float money=(float)REAL_TO_INT_CEIL(value*md->multiplier);
   Rva003B0D7C *wallet=&player->money;
   if(wallet){
     if(((BfmeGlob939D*)TheGameLogic)->bfmeCall939D())money*=TheWritableGlobalData->mults.getMoneyMult(ThePlayerList->rva002A7C0B(false));
     float mult=1.0f;if(me->rva0028C15E(13,&mult,0,1))money*=mult;
     money=(float)player->ScaleMoney(REAL_TO_INT_CEIL(player->getProductionCostChangeBasedOnTemplate(me->getTemplate(),true)*money));
     typedef void (Rva003B0D7C::*UnsignedDeposit)(unsigned int,Rva0039B7AD*,bool);
     (wallet->*reinterpret_cast<UnsignedDeposit>(&Rva003B0D7C::rva003B0D7C))(money,(Rva0039B7AD*)&player->score,true);
   }
   UnicodeString moneyString;moneyString.format(TheGameText->text("GUI:AddCash",0),REAL_TO_INT_CEIL(money));
   Coord3D pos;const Coord3D *src=&member->position;pos.x=src->x;pos.y=src->y;pos.z=src->z;
   char *file="C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\SlaughterHordeContain.cpp";
   pos.x+=GetGameClientRandomValueReal(-10,10,file,254);
   pos.y+=GetGameClientRandomValueReal(-10,10,file,255);
   pos.z+=GetGameClientRandomValueReal(10,20,file,256);
   unsigned int color=(unsigned)me->getControllingPlayer()->color|0xe6000000;TheInGameUI->floating(&moneyString,&pos,color);
   ExperienceTracker *tracker=me->tracker;
   if(tracker && ((Rva0039ADF3*)tracker)->rva0039AE04())tracker->rva0039B315((float)REAL_TO_INT_CEIL(money),true,true,true,0);
 }
 Drawable *draw=((Thing*)member)->getDrawable();if(draw && consumeMember)draw->setDrawableHidden(true);
 bool transfer=md->multiplier==0;
 if(transfer){
rva004804DD(member);bool changed=false;
   if(((Rva004783F4*)this)->rva004783F4()!=member->getTeam()){me->rva0028DA28();changed=true;((SlaughterAddTeam*)((char*)this+0x20))->change(member->getTeam());}
   if(!((Rva002AA292*)&(me?me:me)->upgrades)->rva002AA292((const int*)&member->upgrades)){me->upgrades._M_do_or(member->upgrades);changed=true;}
   if(changed)me->updateUpgradeModules();
 }
 if(member->testStatus((ObjectStatusTypes)38)){
   ((HordeGarrisonContain*)this)->HordeGarrisonContain::rva00479ADA(member);
   if(consumeMember)player->score.addObjectLost(member);
 }else if(consumeMember){
   BfmeDelayedLuaEventList list;*(ObjectID*)(list.data+0x10)=me->id;*(int*)(list.data+0x18)=3;
   ((BfmeObjectEventDispatch*)TheLuaScriptEngine)->rva003360D2(14,member,&list);
   member->kill((DamageType)8,(DeathType)23);TheGameLogic->destroyObject(member);player->score.addObjectLost(member);
 }else{
   ((HordeGarrisonContain*)this)->HordeGarrisonContain::rva00479B7F(member);remove(member);
 }
 if(transfer){
   if(me->ai)me->ai->commands()->aiIdle(CMD_FROM_AI);
   ObjectID id=me->builder;if(id && id!=me->id){Object *builder=TheGameLogic->findObjectByID(id);if(builder){builder->kill((DamageType)8,(DeathType)0);me->rva0028AFE7(0);}}
 }
 Rva00588E44Contain *horde=base.rva00588BF3(this,member);
 if(horde && horde->test()==1){
   if(transfer){count=((SlaughterAddCount*)horde)->count(0);templateName=*(AsciiString*)((char*)member->tmplate+0x64);}
   Object *parent=member->containedBy;
   if(parent){if(consumeMember){player->score.addObjectLost(parent);TheGameLogic->destroyObject(parent);}else remove(parent);}
 }
}
