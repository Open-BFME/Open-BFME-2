// ?ProcessStrategicSinglePlayerGame@StatsReporter@@SAXPAVLivingWorldPlayer@@@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "unicode_string.h"
#include <new>
// stlport
#include <vector>
#include <string.h>
// WB name lead5BFD35 identifies StatsReporter::ProcessStrategicSinglePlayerGame.
// Target bytes establish the player guard3C5, lost flag3C4, side owner40,
// scorekeeper2C8, logic players8C and frameFC. Unknown counter fields retain
// offset names. ZH ScoreScreen.cpp supplies the shared wins/losses/streak
// reference spine; BFME1 donor9cbfb551fe20.
typedef int Int; typedef bool Bool;
#include "../../Include/Common/UserPreferences.h"
class ProfilePreferences:public UserPreferences {};
class StrategicStatsPreferences:public ProfilePreferences {
 public: StrategicStatsPreferences(const UnicodeString&);virtual ~StrategicStatsPreferences();
};
#include "../../Include/GameClient/SkirmishPreferencesClass.h"
enum NameKeyType {NAMEKEY_INVALID=0};
#include "../../Include/Common/NameKeyGenerator.h"
class PlayerTemplate {public:const AsciiString&getSide()const{return side;}char gap[24];AsciiString side;};
class PlayerTemplateStore {public:const PlayerTemplate*findPlayerTemplate(NameKeyType)const;};
class Rva004EE35D;class Rva004EE3AB;class Rva004EE3F9;class Rva004EE447;class Rva004EE485;class Rva004EE4C3;
template<int N>class BitFlags {unsigned words[7];};
#include "../../Include/GameLogic/Module/Rva00045411BitSet.h"
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
#include "../../Include/GameLogic/LivingWorldPlayer.h"
class Rva002E2903Player;
#include "../../Include/GameLogic/Rva002BA8F1Logic.h"
#include "../../Include/GameLogic/Rva002E071E.h"
class Rva0009AAA4DwordField {public:int get()const;};
class Rva0021937DTarget;
class Rva0021937D
{
public:
	void rva002193D9(Rva0021937DTarget*);
	void rva00219407(Rva0021937DTarget*);
	void rva0021937D(Rva0021937DTarget*);
	void rva002193AB(Rva0021937DTarget*);
};
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
extern BitFlags<116>KINDOFMASK_NONE; // 0x009FEFA4, defined by ThingIsAnyKindOf.cpp
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Player;
class StatsReporter
{
public:
	static void ProcessOnlineGameResults(Player*);
	static void ProcessStrategicSinglePlayerGame(LivingWorldPlayer*);
};
template<class T>inline const T&counterMax(const T&a,const T&b){return a>b?a:b;}
inline bool isLost(const LivingWorldPlayer*player){return player->field3C4;}
inline bool isGuarded(const LivingWorldPlayer*player){return player->field3C5;}
inline bool allied(const LivingWorldPlayer*firstPlayer,const LivingWorldPlayer*secondPlayer){return reinterpret_cast<const Rva002E071E*>(firstPlayer)->rva002E071E(reinterpret_cast<const Rva002E071E*>(secondPlayer));}
inline const int&clampPoints(const int&points,const int&minimum){return points<minimum?minimum:points;}
inline int difficultyPoints(const int*difficultyCounts){int middle=difficultyCounts[3];middle+=difficultyCounts[5]*2;return middle*2+difficultyCounts[4]*3+difficultyCounts[2];}
void StatsReporter::ProcessStrategicSinglePlayerGame(LivingWorldPlayer*player) {
 if(isGuarded(player))return;
 LivingWorldScoreKeeper*m_scoreKeeper=reinterpret_cast<LivingWorldScoreKeeper*>(player->field2B8+0x10);
 const PlayerTemplate*playerTemplate=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(static_cast<const LivingWorldSideView*>(player->field40)->getName()));
 if(!playerTemplate)return;
 const AsciiString&side=playerTemplate->getSide();
 SkirmishPreferences profile(1);
 StrategicStatsPreferences prefs(profile.Rva0043B9F5());
 prefs.rva005378E9(side,TheLivingWorldLogic->getFrame()+1);
 unsigned int firstSeconds=m_scoreKeeper->rva004EE037();
 firstSeconds+=m_scoreKeeper->rva004EE016();
 prefs.rva00537A9B(side,(float)firstSeconds);
 if(!isLost(player)) {
  prefs.rva00535BAF(side,prefs.rva00535BF6(side)+1);
  prefs.rva00535D2E(side,prefs.rva00535D75(side)+1);
  prefs.rva00535E50(side,counterMax(prefs.rva00535E97(side),prefs.rva00535D75(side)));
  prefs.rva00535F72(prefs.rva00535FBA()+1);
  prefs.rva00536003(counterMax(prefs.rva0053604B(),prefs.rva00535FBA()));
  prefs.rva00535DBF(side,0);prefs.rva00536094(0);
  reinterpret_cast<Rva0021937D*>(TheCreateAHeroManager)->rva0021937D(static_cast<Rva0021937DTarget*>(player->rva002E06EF()));
 }else {
  prefs.rva00535C9D(side,prefs.rva00535CE4(side)+1);
  prefs.rva00535DBF(side,prefs.rva00535E06(side)+1);
  prefs.rva00535EE1(side,counterMax(prefs.rva00535F28(side),prefs.rva00535E06(side)));
  prefs.rva00536094(prefs.rva005360DC()+1);
  prefs.rva00536125(counterMax(prefs.rva0053616D(),prefs.rva005360DC()));
  prefs.rva00535D2E(side,0);prefs.rva00535F72(0);
  reinterpret_cast<Rva0021937D*>(TheCreateAHeroManager)->rva002193AB(static_cast<Rva0021937DTarget*>(player->rva002E06EF()));
 }
 if(!isLost(player)) {
  int enemies[7];int allies[7];memset(enemies,0,sizeof(enemies));memset(allies,0,sizeof(allies));
  int numEnemies=0;
  for(int i=0;i<TheLivingWorldLogic->getPlayerCount();++i) {
   LivingWorldPlayer*otherPlayer=reinterpret_cast<LivingWorldPlayer*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->GetPlayerAtIndex(i));
   if(otherPlayer!=player && otherPlayer->field44==1) {
    int difficulty=reinterpret_cast<const Rva0009AAA4DwordField*>(otherPlayer)->get();
    if(allied(otherPlayer,player))++allies[difficulty];
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
  LivingWorldPlayer*otherPlayer=reinterpret_cast<LivingWorldPlayer*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->GetPlayerAtIndex(i));
  if(!allied(otherPlayer,player)) {
   const PlayerTemplate*enemyTemplate=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(static_cast<const LivingWorldSideView*>(otherPlayer->field40)->getName()));
   if(enemyTemplate) {
    const AsciiString&enemy=enemyTemplate->getSide();
    if(!isLost(player))prefs.rva0053740C(side,enemy,prefs.rva0053745E(side,enemy)+1);
    else if(!isLost(otherPlayer))prefs.rva005374B3(side,enemy,prefs.rva00537505(side,enemy)+1);
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
 prefs.rva0053626B(side,prefs.rva005362B2(side)+reinterpret_cast<Rva004EE35D*>(m_scoreKeeper)->rva004EE35D(mask,reinterpret_cast<const Rva00045411BitSet&>(KINDOFMASK_NONE)));
 prefs.rva005362FC(side,prefs.rva00536343(side)+reinterpret_cast<Rva004EE3AB*>(m_scoreKeeper)->rva004EE3AB(mask,reinterpret_cast<const Rva00045411BitSet&>(KINDOFMASK_NONE)));
 prefs.rva0053638D(side,prefs.rva005363D4(side)+reinterpret_cast<Rva004EE3F9*>(m_scoreKeeper)->rva004EE3F9(mask,reinterpret_cast<const Rva00045411BitSet&>(KINDOFMASK_NONE)));
 prefs.rva0053641E(side,prefs.rva00536465(side)+reinterpret_cast<Rva004EE447*>(m_scoreKeeper)->rva004EE447());
 prefs.rva005364AF(side,prefs.rva005364F6(side)+reinterpret_cast<Rva004EE485*>(m_scoreKeeper)->rva004EE485());
 prefs.rva00536540(side,prefs.rva00536587(side)+reinterpret_cast<Rva004EE4C3*>(m_scoreKeeper)->rva004EE4C3());
 prefs.rva00536A1D(side,prefs.rva00536A64(side)+m_scoreKeeper->counter94);
 prefs.rva00536AAE(side,prefs.rva00536AF5(side)+m_scoreKeeper->counter98);
 prefs.rva00536C61(side,prefs.rva00536CA8(side)+m_scoreKeeper->counterDC);
 prefs.rva00536CF2(side,prefs.rva00536D39(side)+m_scoreKeeper->counterD8);
 prefs.rva00536D83(side,prefs.rva00536DCA(side)+m_scoreKeeper->counterE4);
 prefs.rva00536E14(side,prefs.rva00536E5B(side)+m_scoreKeeper->counterE0);
 prefs.rva00536EA5(side,prefs.rva00536EEC(side)+m_scoreKeeper->counterE8);
 prefs.rva00536F36(side,prefs.rva00536F7D(side)+m_scoreKeeper->counterECValue());
 prefs.UserPreferences::write();
}
