// cl: /DNDEBUG /MD /EHs /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport46
#include "../../Include/GameClient/SkirmishPreferencesClass.h"
#include "../../Include/Common/UserPreferences.h"
#include "ascii_string.h"
#include "unicode_string.h"
// Target: complete5BF4BC..5BFD35 body and native EH maps. WorldBuilder
// neighbours identify the StatsReporter family; this member name is unknown.
// Reference spine: ZH ScoreScreen.cpp per-player wins/losses and streaks;
// BFME1 donor9cbfb551fe20. BFME2-specific preference updates follow retail.
// Player template+34, side+18, scorekeeper+3BC and accessed counter offsets
// are measured target facts; unused portions of these views remain opaque.
typedef int Int; typedef bool Bool;

class ProfilePreferences:public UserPreferences {};
class RealTimeStatsPreferences:public ProfilePreferences {
 public: RealTimeStatsPreferences(const UnicodeString&);virtual ~RealTimeStatsPreferences();
};

#include "../../Include/GameNetwork/GameInfo.h"
class PlayerTemplate {public:const AsciiString&getSide()const{return side;} char prefix[24];AsciiString side;};
#include "../../Include/Common/PlayerTemplateStore.h"
class VictoryConditionsInterface {public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void va();
 virtual void vb();
 virtual void vc();
 virtual void vd();
 virtual void ve();
 virtual void vf();
 virtual void v10();
 virtual void v11();
 virtual bool isLocalAlliedVictory();virtual bool isLocalAlliedDefeat();
};
#include "../../Include/Common/Rva0039B709.h"
struct Rva00045411BitSet {unsigned words[7];Rva00045411BitSet(int,int);};
#include "../../Include/Common/BitFlagsTemplate.h"
class Rva0039BF22 {public:int rva0039BF22(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva0039BF50 {public:int rva0039BF50(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class ScoreKeeper {
 public:int rva0039B749();int rva0039B773();
 int counter1e0Value()const{return counter1e0;}
 char pad000[0x114]; int counter114;
 char pad118[0x50]; int counter168;int counter16c;
 char pad170[0x50]; int counter1c0;int counter1c4;
 char pad1c8[0x18];int counter1e0;
};
class Player {public:char pad000[0x34];PlayerTemplate*playerTemplate;
 char pad038[0x384];ScoreKeeper score;
};
extern GameInfo*TheGameInfo;
extern PlayerTemplateStore*ThePlayerTemplateStore;
// GameEngine::init registers this storage with the TheVictoryConditions literal
// and rowed420353 factory. Use the ledger's existing opaque pointer owner;
// the accessed interface slots above remain proven by this retail body.
class VictoryConditionsInterface; extern VictoryConditionsInterface *TheVictoryConditions;
extern int BfmeLogicFramesPerSecond;

Bool Rva005BF28EIsAlly(const GameInfo*,const GameSlot*);
void Rva005BF2C7Update(UserPreferences*);
template<class T>inline const T&counterMax(const T&lhs,const T&rhs){return lhs>rhs?lhs:rhs;}
inline const BitFlags<116>&mask(const Rva00045411BitSet&x){return reinterpret_cast<const BitFlags<116>&>(x);}
void Rva005BF4BCProcess(Player*player) {
 if(TheGameInfo->isSandbox())return;
 SkirmishPreferences profile(0);
 RealTimeStatsPreferences prefs(profile.Rva0043B9F5());
 const AsciiString&side=player->playerTemplate->getSide();
 if(reinterpret_cast<VictoryConditionsInterface*>(TheVictoryConditions)->isLocalAlliedVictory()) {
  bool easy=false,normal=false,hard=false;
  int brutal=0;
  bool allied=false;
  for(int i=0;i<8;++i) {
   const GameSlot*slot=TheGameInfo->getConstSlot(i);
   int state=slot->getState();
   bool ally=Rva005BF28EIsAlly(TheGameInfo,slot);
   bool ai=slot->isAI();
   if(slot->isOccupied()&&!ally) {
    const AsciiString&enemy=ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate())->getSide();
    prefs.rva0053740C(side,enemy,prefs.rva0053745E(side,enemy)+1);
   }
   if(ai) {
    if(!ally&&slot->isOccupied()) {
     if(state==2)easy=true;
     else if(state==3)normal=true;
     else if(state==4)hard=true;
     else if(state==5)++brutal;
    }else if(ally)allied=true;
   }
  }
  if(!allied) {
   if(TheGameInfo->getMaxPlayers()-1==brutal)prefs.rva0053587C(side,prefs.rva005358C3(side)+4);
   else if(hard)prefs.rva0053587C(side,prefs.rva005358C3(side)+3);
   else if(normal)prefs.rva0053587C(side,prefs.rva005358C3(side)+2);
   else if(easy)prefs.rva0053587C(side,prefs.rva005358C3(side)+1);
  }
  prefs.rva00535BAF(side,prefs.rva00535BF6(side)+1);
  prefs.rva00535D2E(side,prefs.rva00535D75(side)+1);
  prefs.rva00535E50(side,counterMax(prefs.rva00535E97(side),prefs.rva00535D75(side)));
  prefs.rva00535F72(prefs.rva00535FBA()+1);
  prefs.rva00536003(counterMax(prefs.rva0053604B(),prefs.rva00535FBA()));
  prefs.rva00535DBF(side,0);prefs.rva00536094(0);
  Rva005BF2C7Update(&prefs);
 }else if(reinterpret_cast<VictoryConditionsInterface*>(TheVictoryConditions)->isLocalAlliedDefeat()) {
  for(int i=0;i<8;++i) {
   const GameSlot*slot=TheGameInfo->getConstSlot(i);
   bool ally=Rva005BF28EIsAlly(TheGameInfo,slot);
   if(slot->isOccupied()&&!ally) {
    const AsciiString&enemy=ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate())->getSide();
    prefs.rva005374B3(side,enemy,prefs.rva00537505(side,enemy)+1);
   }
  }
  prefs.rva00535C9D(side,prefs.rva00535CE4(side)+1);
  prefs.rva00535DBF(side,prefs.rva00535E06(side)+1);
  prefs.rva00535EE1(side,counterMax(prefs.rva00535F28(side),prefs.rva00535E06(side)));
  prefs.rva00536094(prefs.rva005360DC()+1);
  prefs.rva00536125(counterMax(prefs.rva0053616D(),prefs.rva005360DC()));
  prefs.rva00535D2E(side,0);prefs.rva00535F72(0);
 }
 AsciiString favorite=prefs.rva0053620F();
 if(favorite!=AsciiString::TheEmptyString) {
  int oldGames=prefs.rva00535BF6(favorite)+prefs.rva00535CE4(favorite);
  int games=prefs.rva00535BF6(side)+prefs.rva00535CE4(side);
  if(games>oldGames)prefs.rva005361B6(side);
 }else prefs.rva005361B6(side);
 AsciiString oldFaction=prefs.rva00537261();
 prefs.rva00537208(player->playerTemplate->getSide());
 if(oldFaction!=prefs.rva00537261())prefs.rva005372BD(0);
 else prefs.rva005372BD(prefs.rva00537305()+1);
 ScoreKeeper*scoreKeeper=&player->score;
 prefs.rva00537A9B(side,(float)(reinterpret_cast<Rva0039B709*>(scoreKeeper)->rva0039B718()/(unsigned int)BfmeLogicFramesPerSecond));
 prefs.rva005366F3(side,prefs.rva0053673A(side)+reinterpret_cast<Rva0039BF22*>(scoreKeeper)->rva0039BF22(Rva00045411BitSet(0,90),Rva00045411BitSet(0,179)));
 prefs.rva00536784(side,prefs.rva005367CB(side)+reinterpret_cast<Rva0039BF50*>(scoreKeeper)->rva0039BF50(Rva00045411BitSet(0,90),Rva00045411BitSet(0,179)));
 prefs.rva0053626B(side,prefs.rva005362B2(side)+scoreKeeper->counter168);
 prefs.rva005362FC(side,prefs.rva00536343(side)+scoreKeeper->counter16c);
 prefs.rva0053638D(side,prefs.rva005363D4(side)+scoreKeeper->rva0039B749());
 prefs.rva0053641E(side,prefs.rva00536465(side)+scoreKeeper->counter1c0);
 prefs.rva005364AF(side,prefs.rva005364F6(side)+scoreKeeper->counter1c4);
 prefs.rva00536540(side,prefs.rva00536587(side)+scoreKeeper->rva0039B773());
 prefs.rva005365D1(side,prefs.rva00536618(side)+scoreKeeper->counter114);
 int total=prefs.rva005366A9(side);
 if(total<0)total=prefs.rva00536618(side);
 prefs.rva00536662(side,total+scoreKeeper->counter1e0Value());
 prefs.UserPreferences::write();
}
