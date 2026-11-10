// Player::doBountyForKill, native 0x002AB63D..0x002AB7D5 (408 bytes).
// Reference semantics: ZH Player.cpp::doBountyForKill and BFME1
// game/GameEngine/Source/Common/RTS/PlayerDoBountyForKill.cpp at
// 9cbfb551fe20dae985f91f2319d8997287b6a705. Target kill-accounting caller,
// under-construction predicate, money deposit and GUI:AddCash establish the
// identity independently; the target adds attribute17 and campaign scaling.
// Target offsets are the existing SalvageCrateCollide BFME2 views plus the
// native bounty percentage access at Player+0x314.
// The cached victim remains live while its dead parameter home holds the
// percentage; the dead killer home holds the awarded bounty. Retail reuses
// those same argument slots. The donor's x87 round helper is required:
// a C++ integer cast instead calls _ftol2 rather than emitting native fistp.
// cl: /I. /Ireference/shims/bfme2_ascii /MD /EHs /O1 /arch:SSE
#include "unicode_string.h"
typedef unsigned int UnsignedInt;
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <math.h>
__forceinline int bountyRound(float value) {
 int result;
 __asm {fld value}
 __asm {fistp result}
 return result;
}
#include "../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "../../../Include/Common/BfmeGlob939D.h"
extern GameLogic *TheGameLogic;

#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../../Include/Common/MultiPlayMults.h"

#include "../../../Include/Common/GlobalData.h"
extern class GlobalData *TheWritableGlobalData;

class Rva0039B7AD
{
	char m_pad[4];
};

class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *score, bool flag);	// 0x003B0D7C
	char m_pad[4];
};

class Object;
class Player
{
public:
	void doBountyForKill(const Object *, const Object *);
	int ScaleMoney(int amount);	// 0x002A9E36
	char m_pad000[0x5C];
	int m_5C;			// +0x5C (1 a computer player)
	char m_pad060[0x90 - 0x60];
	Rva003B0D7C m_money;		// +0x90
	char m_pad094[0x314 - 0x94];
 float m_cashBountyPercent;
 char m_pad318[0x3BC - 0x318];
	Rva0039B7AD m_3BC;		// +0x3BC
};


enum ObjectStatusTypes {UnderConstruction=2};
class Rva0028D796 {public:int rva0028D796();};
class Object {
public:
 bool testStatus(ObjectStatusTypes) const;
 bool rva0028C149(int,float *,int);
 char padding[0x38];
 Coord3D pos;
};
#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;
void Player::doBountyForKill(const Object *killer,const Object *victim)
{
 register const Object *killerObject=killer;
 if(!killerObject) return;
 register const Object *victimObject=victim;
 if(!victimObject) return;
 if(victimObject->testStatus(UnderConstruction)) return;
 int zero=0;
 int victimBounty=((Rva0028D796 *)victimObject)->rva0028D796();
 unsigned &bounty=*(unsigned *)&killer;
 float &percent=*(float *)&victim;
 ((Object *)killerObject)->rva0028C149(17,&percent,0);
 if(percent==0.0f) percent=m_cashBountyPercent;
 float rounded=(float)ceil((float)(unsigned)victimBounty*percent);
 bounty=(unsigned)bountyRound(rounded);
 if(((BfmeGlob939D *)TheGameLogic)->bfmeCall939D()) {
  int playerIndex=ThePlayerList->rva002A7C0B(false);
  float mult=TheWritableGlobalData->m_multiPlayMults.getMoneyMult(playerIndex);
  bounty=(unsigned)(bounty*mult);
 }
 bounty=(unsigned)ScaleMoney((int)bounty);
 if(bounty==zero) return;
 m_money.rva003B0D7C(bounty,&m_3BC,true);
 { Coord3D pos;
  UnicodeString moneyString;
  moneyString.format(TheGameText->fetchPtr("GUI:AddCash",0),bounty);
  pos.x=victimObject->pos.x;pos.y=victimObject->pos.y;pos.z=victimObject->pos.z;
  pos.z+=10.0f;
  TheInGameUI->addFloatingText(moneyString,&pos,0xffffff00);
 }
}
