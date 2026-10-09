// ?ProcessStrategicSinglePlayerGame@StatsReporter@@SAXPAVLivingWorldPlayer@@@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "unicode_string.h"
#include <new>
// stlport
#include <vector>
extern "C" void * __cdecl memset(void*,int,unsigned int);
// WB name lead5BFD35 identifies StatsReporter::ProcessStrategicSinglePlayerGame.
// Target bytes establish the player guard3C5, lost flag3C4, side owner40,
// scorekeeper2C8, logic players8C and frameFC. Unknown counter fields retain
// offset names. ZH ScoreScreen.cpp supplies the shared wins/losses/streak
// reference spine; BFME1 donor9cbfb551fe20.
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
 void rva005378E9(AsciiString,int);
 private: char storage[16];
};
class ProfilePreferences:public UserPreferences {};
class StrategicStatsPreferences:public ProfilePreferences {
 public: StrategicStatsPreferences(const UnicodeString&);virtual ~StrategicStatsPreferences();
};
class SkirmishPreferences:public UserPreferences {
 public: SkirmishPreferences(int);virtual ~SkirmishPreferences();UnicodeString Rva0043B9F5();
 private: char tail[12];
};
enum NameKeyType {NAMEKEY_INVALID=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const AsciiString&);};
class PlayerTemplate {public:const AsciiString&getSide()const{return side;}char gap[24];AsciiString side;};
class PlayerTemplateStore {public:const PlayerTemplate*findPlayerTemplate(NameKeyType)const;};
class Rva004EE35D;class Rva004EE3AB;class Rva004EE3F9;class Rva004EE447;class Rva004EE485;class Rva004EE4C3;
template<int N>class BitFlags {unsigned words[7];};
struct Rva00045411BitSet {unsigned words[7];Rva00045411BitSet(int,int);};
class Rva004EE35D {public:int rva004EE35D(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva004EE3AB {public:int rva004EE3AB(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva004EE3F9 {public:int rva004EE3F9(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva004EE447 {public:int rva004EE447();};
class Rva004EE485 {public:int rva004EE485();};
class Rva004EE4C3 {public:int rva004EE4C3();};
class LivingWorldScoreKeeper {
 public:unsigned int rva004EE037();int rva004EE016();
 int counterECValue()const{return counterEC;}
 char before94[0x94];int counter94,counter98;
 char beforeD8[0x3c];int counterD8,counterDC,counterE0,counterE4,counterE8,counterEC;
};
class LivingWorldSideView {public:char beforeName[4];AsciiString name;const AsciiString&getName()const{return name;}};
class LivingWorldPlayer {
 public:
 bool isLost()const{return lost;}bool isGuarded()const{return guarded;}
 LivingWorldScoreKeeper*getScoreKeeper(){return &score;}
 const LivingWorldSideView*getSide()const{return side;}
 int getPlayerKind()const{return playerKind;}
 char prefix[0x40];LivingWorldSideView*side;int playerKind;
 char beforeScore[0x280];LivingWorldScoreKeeper score;
 char beforeFlags[0xC];bool lost,guarded;
};
class Rva002E2903Player;
class Rva002BA8F1Logic {public:Rva002E2903Player*rva002B52A8(int);};
class Rva002E071E {public:bool rva002E071E(const Rva002E071E*)const;};
class Rva002E06B8 {public:void*rva002E06EF();};
class Rva0009AAA4DwordField {public:int get()const;};
class Rva0021937DTarget;
class Rva0021937D {public:void rva0021937D(Rva0021937DTarget*);void rva002193AB(Rva0021937DTarget*);};
class LivingWorldLogic {public:
 char beforePlayers[0x8c];_STL::vector<LivingWorldPlayer*>players;
 char beforeFrame[0x64];int frame;
 int getFrame()const{return frame;}
 int getPlayerCount()const{return players.size();}
};
extern LivingWorldLogic*TheLivingWorldLogic;
extern PlayerTemplateStore*ThePlayerTemplateStore;
extern NameKeyGenerator*TheNameKeyGenerator;
class CreateAHeroManager;
extern CreateAHeroManager*TheCreateAHeroManager;
extern const BitFlags<116>g_defaultStorage009FEFA4;
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class StatsReporter {public:static void ProcessStrategicSinglePlayerGame(LivingWorldPlayer*);};
template<class T>inline const T&counterMax(const T&a,const T&b){return a>b?a:b;}
inline bool allied(const LivingWorldPlayer*a,const LivingWorldPlayer*b){return reinterpret_cast<const Rva002E071E*>(a)->rva002E071E(reinterpret_cast<const Rva002E071E*>(b));}
inline const int&clampPoints(const int&points,const int&minimum){return points<minimum?minimum:points;}
inline int difficultyPoints(const int*n){int middle=n[3];middle+=n[5]*2;return middle*2+n[4]*3+n[2];}
void StatsReporter::ProcessStrategicSinglePlayerGame(LivingWorldPlayer*player) {
 if(player->isGuarded())return;
 LivingWorldScoreKeeper*s=player->getScoreKeeper();
 const PlayerTemplate*playerTemplate=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(player->getSide()->getName()));
 if(!playerTemplate)return;
 const AsciiString&side=playerTemplate->getSide();
 SkirmishPreferences profile(1);
 StrategicStatsPreferences prefs(profile.Rva0043B9F5());
 prefs.rva005378E9(side,TheLivingWorldLogic->getFrame()+1);
 unsigned int firstSeconds=s->rva004EE037();
 firstSeconds+=s->rva004EE016();
 prefs.rva00537A9B(side,(float)firstSeconds);
 if(!player->isLost()) {
  prefs.rva00535BAF(side,prefs.rva00535BF6(side)+1);
  prefs.rva00535D2E(side,prefs.rva00535D75(side)+1);
  prefs.rva00535E50(side,counterMax(prefs.rva00535E97(side),prefs.rva00535D75(side)));
  prefs.rva00535F72(prefs.rva00535FBA()+1);
  prefs.rva00536003(counterMax(prefs.rva0053604B(),prefs.rva00535FBA()));
  prefs.rva00535DBF(side,0);prefs.rva00536094(0);
  reinterpret_cast<Rva0021937D*>(TheCreateAHeroManager)->rva0021937D(static_cast<Rva0021937DTarget*>(reinterpret_cast<Rva002E06B8*>(player)->rva002E06EF()));
 }else {
  prefs.rva00535C9D(side,prefs.rva00535CE4(side)+1);
  prefs.rva00535DBF(side,prefs.rva00535E06(side)+1);
  prefs.rva00535EE1(side,counterMax(prefs.rva00535F28(side),prefs.rva00535E06(side)));
  prefs.rva00536094(prefs.rva005360DC()+1);
  prefs.rva00536125(counterMax(prefs.rva0053616D(),prefs.rva005360DC()));
  prefs.rva00535D2E(side,0);prefs.rva00535F72(0);
  reinterpret_cast<Rva0021937D*>(TheCreateAHeroManager)->rva002193AB(static_cast<Rva0021937DTarget*>(reinterpret_cast<Rva002E06B8*>(player)->rva002E06EF()));
 }
 if(!player->isLost()) {
  int enemies[7];int allies[7];memset(enemies,0,sizeof(enemies));memset(allies,0,sizeof(allies));
  int numEnemies=0;
  for(int i=0;i<TheLivingWorldLogic->getPlayerCount();++i) {
   LivingWorldPlayer*p=reinterpret_cast<LivingWorldPlayer*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B52A8(i));
   if(p!=player && p->getPlayerKind()==1) {
    int difficulty=reinterpret_cast<const Rva0009AAA4DwordField*>(p)->get();
    if(allied(p,player))++allies[difficulty];
    else {++numEnemies;++enemies[difficulty];}
   }
  }
  if(numEnemies>0) {
   int minimum;int points;
   {
    const int &enemyPoints=difficultyPoints(enemies);
    const int &allyPoints=difficultyPoints(allies);
    // Retail keeps the minimum in ECX while the computed score stays in EAX.
    int difference=enemyPoints-allyPoints; _ReadWriteBarrier();minimum=1;points=difference;
   }
   int earned=counterMax(minimum,points);
   prefs.rva0053587C(side,prefs.rva005358C3(side)+earned);
  }
 }
 for(int i=0;i<TheLivingWorldLogic->getPlayerCount();++i) {
  LivingWorldPlayer*p=reinterpret_cast<LivingWorldPlayer*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B52A8(i));
  if(!allied(p,player)) {
   const PlayerTemplate*enemyTemplate=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(p->getSide()->getName()));
   if(enemyTemplate) {
    const AsciiString&enemy=enemyTemplate->getSide();
    if(!player->isLost())prefs.rva0053740C(side,enemy,prefs.rva0053745E(side,enemy)+1);
    else if(!p->isLost())prefs.rva005374B3(side,enemy,prefs.rva00537505(side,enemy)+1);
   }
  }
 }
 AsciiString favorite=prefs.rva0053620F();
 if(favorite!=AsciiString::TheEmptyString) {
  int oldGames=prefs.rva00535BF6(favorite)+prefs.rva00535CE4(favorite);
  int games=prefs.rva00535BF6(side)+prefs.rva00535CE4(side);
  if(games>oldGames)prefs.rva005361B6(side);
 }else prefs.rva005361B6(side);
 Rva00045411BitSet buildMask(0,7);
 const Rva00045411BitSet&mask=buildMask;
 prefs.rva0053626B(side,prefs.rva005362B2(side)+reinterpret_cast<Rva004EE35D*>(s)->rva004EE35D(mask,reinterpret_cast<const Rva00045411BitSet&>(g_defaultStorage009FEFA4)));
 prefs.rva005362FC(side,prefs.rva00536343(side)+reinterpret_cast<Rva004EE3AB*>(s)->rva004EE3AB(mask,reinterpret_cast<const Rva00045411BitSet&>(g_defaultStorage009FEFA4)));
 prefs.rva0053638D(side,prefs.rva005363D4(side)+reinterpret_cast<Rva004EE3F9*>(s)->rva004EE3F9(mask,reinterpret_cast<const Rva00045411BitSet&>(g_defaultStorage009FEFA4)));
 prefs.rva0053641E(side,prefs.rva00536465(side)+reinterpret_cast<Rva004EE447*>(s)->rva004EE447());
 prefs.rva005364AF(side,prefs.rva005364F6(side)+reinterpret_cast<Rva004EE485*>(s)->rva004EE485());
 prefs.rva00536540(side,prefs.rva00536587(side)+reinterpret_cast<Rva004EE4C3*>(s)->rva004EE4C3());
 prefs.rva00536A1D(side,prefs.rva00536A64(side)+s->counter94);
 prefs.rva00536AAE(side,prefs.rva00536AF5(side)+s->counter98);
 prefs.rva00536C61(side,prefs.rva00536CA8(side)+s->counterDC);
 prefs.rva00536CF2(side,prefs.rva00536D39(side)+s->counterD8);
 prefs.rva00536D83(side,prefs.rva00536DCA(side)+s->counterE4);
 prefs.rva00536E14(side,prefs.rva00536E5B(side)+s->counterE0);
 prefs.rva00536EA5(side,prefs.rva00536EEC(side)+s->counterE8);
 prefs.rva00536F36(side,prefs.rva00536F7D(side)+s->counterECValue());
 prefs.UserPreferences::write();
}
