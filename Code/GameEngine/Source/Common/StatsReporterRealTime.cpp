// cl: /DNDEBUG /MD /EHs /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "unicode_string.h"
// Target: complete5BF4BC..5BFD35 body and native EH maps. WorldBuilder
// neighbours identify the StatsReporter family; this member name is unknown.
// Reference spine: ZH ScoreScreen.cpp per-player wins/losses and streaks;
// BFME1 donor9cbfb551fe20. BFME2-specific preference updates follow retail.
// Player template+34, side+18, scorekeeper+3BC and accessed counter offsets
// are measured target facts; unused portions of these views remain opaque.
typedef int Int; typedef bool Bool;
class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual void v1();
	virtual bool write();
	virtual void v3();
	virtual void v4();
	virtual float v5(const AsciiString &s, float x);
	virtual int v6(const AsciiString &s, int x);
	virtual void v7();
	virtual AsciiString v8(const AsciiString &key, const AsciiString &def);
	virtual void v9();
	virtual void v10(const AsciiString &s, float x);
	virtual void v11(const AsciiString &s, int x);
	virtual void v12(const AsciiString &a, const AsciiString &b);
	int rva00535CE4(AsciiString arg);
	AsciiString rva00535820();
	void rva00536B3F(AsciiString arg, int x);
	int rva00536B86(AsciiString arg);
	void rva00536BD0(AsciiString arg, int x);
	int rva00536C17(AsciiString arg);
	int rva0053700F();
	int rva005370D2();
	AsciiString rva00537261();
	void rva00537058(int bits);
	void rva0053711B(AsciiString arg, int x, int value);
	UnicodeString rva00535B32(float seconds);
	void rva0053587C(AsciiString arg, int x);
	void rva00535BAF(AsciiString arg, int x);
	void rva00535C9D(AsciiString arg, int x);
	void rva00535D2E(AsciiString arg, int x);
	void rva00535DBF(AsciiString arg, int x);
	void rva00535E50(AsciiString arg, int x);
	void rva00535EE1(AsciiString arg, int x);
	void rva00535F72(int x);
	void rva00536003(int x);
	void rva00536094(int x);
	void rva00536125(int x);
	int rva0053604B();
	int rva005360DC();
	int rva0053616D();
	void rva005361B6(AsciiString arg);
	AsciiString rva0053620F();
	int rva00535FBA();
	int rva005358C3(AsciiString arg);
	int rva00535BF6(AsciiString arg);
	int rva00535C40();
	int rva005373AF();
	int rva0053734E(AsciiString arg);
	int rva00537C28();
	UnicodeString rva00537C3F();
	void rva00536C61(AsciiString arg, int x);
	int rva00536CA8(AsciiString arg);
	void rva00536CF2(AsciiString arg, int x);
	int rva00536D39(AsciiString arg);
	void rva00536D83(AsciiString arg, int x);
	int rva00536DCA(AsciiString arg);
	void rva00536E14(AsciiString arg, int x);
	int rva00536E5B(AsciiString arg);
	void rva00536EA5(AsciiString arg, int x);
	int rva00536EEC(AsciiString arg);
	void rva00536F36(AsciiString arg, int x);
	int rva00536F7D(AsciiString arg);
	void rva00536FC7(int x);
	int rva00535D75(AsciiString arg);
	int rva00535E06(AsciiString arg);
	int rva00535E97(AsciiString arg);
	int rva00535F28(AsciiString arg);
	void rva0053595E(AsciiString arg, float x);
	float rva0053590D(AsciiString arg);
	float rva005359A9(AsciiString arg);
	float rva00535A45(AsciiString arg);
	float rva00535AE1(AsciiString arg);
	void rva005359FA(AsciiString arg, float x);
	void rva00535A96(AsciiString arg, float x);
	void rva00535781();
	int rva00537190(AsciiString arg, int x);
	void rva005372BD(int x);
	int rva00537305();
	void rva00537208(AsciiString arg);
	void rva0053626B(AsciiString arg, int x);
	int rva005362B2(AsciiString arg);
	void rva005362FC(AsciiString arg, int x);
	int rva00536343(AsciiString arg);
	void rva0053638D(AsciiString arg, int x);
	int rva005363D4(AsciiString arg);
	void rva0053641E(AsciiString arg, int x);
	int rva00536465(AsciiString arg);
	void rva005364AF(AsciiString arg, int x);
	int rva005364F6(AsciiString arg);
	void rva00536540(AsciiString arg, int x);
	int rva00536587(AsciiString arg);
	void rva005365D1(AsciiString arg, int x);
	int rva00536618(AsciiString arg);
	void rva00536662(AsciiString arg, int x);
	int rva005366A9(AsciiString arg);
	void rva005366F3(AsciiString arg, int x);
	int rva0053673A(AsciiString arg);
	void rva00536784(AsciiString arg, int x);
	int rva005367CB(AsciiString arg);
	int rva00536815(AsciiString arg);
	void rva0053685F(AsciiString arg, int x);
	int rva005368A6(AsciiString arg);
	void rva005368F0(AsciiString arg, int x);
	int rva00536937(AsciiString arg);
	void rva00536981(AsciiString arg, float x);
	float rva005369CC(AsciiString arg);
	void rva00536A1D(AsciiString arg, int x);
	int rva00536A64(AsciiString arg);
	void rva00536AAE(AsciiString arg, int x);
	int rva00536AF5(AsciiString arg);
 void rva00537A9B(AsciiString,float);
 int rva0053745E(AsciiString,const AsciiString&);
 void rva0053740C(AsciiString,const AsciiString&,int);
 int rva00537505(AsciiString,const AsciiString&);
 void rva005374B3(AsciiString,const AsciiString&,int);
 private: char storage[16];
};
class ProfilePreferences:public UserPreferences {};
class RealTimeStatsPreferences:public ProfilePreferences {
 public: RealTimeStatsPreferences(const UnicodeString&);virtual ~RealTimeStatsPreferences();
};
class SkirmishPreferences:public UserPreferences {
 public: SkirmishPreferences(int);virtual ~SkirmishPreferences();UnicodeString Rva0043B9F5();
 private: char tail[12];
};
class GameSlot {
 public:virtual void reset(); bool isAI()const;bool isOccupied()const;
 int getState()const{return state;} int getPlayerTemplate()const{return playerTemplate;}
 int state; char gap08[16];int playerTemplate;
};
class GameInfo {
 public:
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
 virtual void v12();
 virtual void v13();
 virtual bool isSandbox();
 const GameSlot*getConstSlot(int)const;int rva0040203C();
};
class PlayerTemplate {public:const AsciiString&getSide()const{return side;} char prefix[24];AsciiString side;};
class PlayerTemplateStore {public:const PlayerTemplate*getNthPlayerTemplate(int)const;};
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
class Rva0039B709 {public:unsigned int rva0039B718();};
struct Rva00045411BitSet {unsigned words[7];Rva00045411BitSet(int,int);};
template<int N>class BitFlags {unsigned words[7];};
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
// Verified GameEngine::init registers E03138 with the TheVictoryConditions
// literal and the rowed420353 factory (GameEngineInit.cpp747). The shadow
// data index still assigns this location its older provisional opaque owner.
extern VictoryConditionsInterface*TheVictoryConditions;
extern int g_Va00DBA4E4;

Bool Rva005BF28EIsAlly(const GameInfo*,const GameSlot*);
void Rva005BF2C7Update(UserPreferences*);
template<class T>inline const T&counterMax(const T&a,const T&b){return a>b?a:b;}
inline const BitFlags<116>&mask(const Rva00045411BitSet&x){return reinterpret_cast<const BitFlags<116>&>(x);}
void Rva005BF4BCProcess(Player*player) {
 if(TheGameInfo->isSandbox())return;
 SkirmishPreferences profile(0);
 RealTimeStatsPreferences prefs(profile.Rva0043B9F5());
 const AsciiString&side=player->playerTemplate->getSide();
 if(TheVictoryConditions->isLocalAlliedVictory()) {
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
   if(TheGameInfo->rva0040203C()-1==brutal)prefs.rva0053587C(side,prefs.rva005358C3(side)+4);
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
 }else if(TheVictoryConditions->isLocalAlliedDefeat()) {
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
 ScoreKeeper*s=&player->score;
 prefs.rva00537A9B(side,(float)(reinterpret_cast<Rva0039B709*>(s)->rva0039B718()/(unsigned int)g_Va00DBA4E4));
 prefs.rva005366F3(side,prefs.rva0053673A(side)+reinterpret_cast<Rva0039BF22*>(s)->rva0039BF22(Rva00045411BitSet(0,90),Rva00045411BitSet(0,179)));
 prefs.rva00536784(side,prefs.rva005367CB(side)+reinterpret_cast<Rva0039BF50*>(s)->rva0039BF50(Rva00045411BitSet(0,90),Rva00045411BitSet(0,179)));
 prefs.rva0053626B(side,prefs.rva005362B2(side)+s->counter168);
 prefs.rva005362FC(side,prefs.rva00536343(side)+s->counter16c);
 prefs.rva0053638D(side,prefs.rva005363D4(side)+s->rva0039B749());
 prefs.rva0053641E(side,prefs.rva00536465(side)+s->counter1c0);
 prefs.rva005364AF(side,prefs.rva005364F6(side)+s->counter1c4);
 prefs.rva00536540(side,prefs.rva00536587(side)+s->rva0039B773());
 prefs.rva005365D1(side,prefs.rva00536618(side)+s->counter114);
 int total=prefs.rva005366A9(side);
 if(total<0)total=prefs.rva00536618(side);
 prefs.rva00536662(side,total+s->counter1e0Value());
 prefs.UserPreferences::write();
}
