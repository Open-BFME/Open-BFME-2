// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// ?Rva005BF28EIsAlly@@YA_NPBVGameInfo@@PBVGameSlot@@@Z @0x005BF28E 57B: GameInfo local-ally team check via getLocalSlotNum slot 13 (+0x34) and rowed getConstSlot; evidence retail virtual call + getConstSlot row + team at +0x1c.

typedef int Int;
typedef bool Bool;

class GameSlot
{
public:
	virtual void reset();
	Bool isAI() const;
	Int getState() const { return m_state; }
	Int getTeamNumber() const { return m_teamNumber; }

private:
	Int m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	char m_pad0A[2];
	Int m_color;
	Int m_startPos;
	char m_pad14[4];
	Int m_playerTemplate;
	Int m_teamNumber;
};

class GameInfo
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual Int getLocalSlotNum() const = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual Bool rva003FF3B5() = 0;

	const GameSlot *getConstSlot(Int slotNum) const;
	AsciiString getMap() const;
	Int rva0040203C();
};

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
template<class T> inline const T &counterMax(const T &a,const T &b) { return a>b?a:b; }
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
  if(TheGameInfo->rva0040203C()-1==brutal)
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
