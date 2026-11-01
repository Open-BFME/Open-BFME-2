// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// ?Rva005BF28EIsAlly@@YA_NPBVGameInfo@@PBVGameSlot@@@Z @0x005BF28E 57B: GameInfo local-ally team check via getLocalSlotNum slot 13 (+0x34) and rowed getConstSlot; evidence retail virtual call + getConstSlot row + team at +0x1c.

typedef int Int;
typedef bool Bool;

#include "../../Include/GameNetwork/GameInfo.h"


// Reference spine: ZH ScoreScreen.cpp updateChallengeMedals; BFME 2 replaces
// the medal bit mask with per-map difficulty counters in UserPreferences.
// Target facts: eight slots; AI states 2..5; local-ally helper5BF28E;
// by-value map key23E943; preference getter537190/setter53711B.
// Donor revision: BFME1 9cbfb551fe20. Target name remains unknown.
extern GameInfo *TheGameInfo;
Bool Rva005BF28EIsAlly(const GameInfo *, const GameSlot *);
class UserPreferences {
public:
 Int rva00537190(AsciiString,int);
 void rva0053711B(AsciiString,int,int);
};
template<class T> inline const T &counterMax(const T &lhs,const T &rhs) { return lhs>rhs?lhs:rhs; }
void Rva005BF2C7Update(UserPreferences *prefs) {
 unsigned int easy=0,normal=0,hard=0;
 Int brutal=0;
 Bool allied=false;
 for(Int i=0;i<8;++i) {
  const GameSlot *slot=TheGameInfo->getConstSlot(i);
  if(slot->isAI() && !Rva005BF28EIsAlly(TheGameInfo,slot)) {
   if(TheGameInfo->getConstSlot(i)->getState()==2)++easy;
   if(TheGameInfo->getConstSlot(i)->getState()==3)++normal;
   if(TheGameInfo->getConstSlot(i)->getState()==4)++hard;
   if(TheGameInfo->getConstSlot(i)->getState()==5)++brutal;
  } else if(slot->isAI()) allied=true;
 }
 if(!allied && (easy || normal || hard || brutal)) {
  Int oldEasy=prefs->rva00537190(TheGameInfo->getMap(),2);
  Int oldNormal=prefs->rva00537190(TheGameInfo->getMap(),3);
  Int oldHard=prefs->rva00537190(TheGameInfo->getMap(),4);
  Int oldBrutal=prefs->rva00537190(TheGameInfo->getMap(),5);
  if(TheGameInfo->getMaxPlayers()-1==brutal)
   prefs->rva0053711B(TheGameInfo->getMap(),6,counterMax(oldBrutal,brutal));
  else if(brutal)
   prefs->rva0053711B(TheGameInfo->getMap(),5,counterMax(oldBrutal,brutal));
  else if(hard)
   prefs->rva0053711B(TheGameInfo->getMap(),4,counterMax(oldHard,Int(hard)));
  else if(normal)
   prefs->rva0053711B(TheGameInfo->getMap(),3,counterMax(oldNormal,Int(normal)));
  else if(easy)
   prefs->rva0053711B(TheGameInfo->getMap(),2,counterMax(oldEasy,Int(easy)));
 }
}
