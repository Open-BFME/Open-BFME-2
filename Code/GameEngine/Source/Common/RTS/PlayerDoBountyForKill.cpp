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
extern "C" __declspec(dllimport) double __cdecl ceil(double);
__forceinline int bountyRound(float value) {
 int result;
 __asm {fld value}
 __asm {fistp result}
 return result;
}
class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
class BfmeGlob939D {public: char bfmeCall939D();};
extern GameLogic *TheGameLogic;

class PlayerList
{
public:
	int rva002A7C0B(bool flag);	// 0x002A7C0B
};
extern PlayerList *ThePlayerList;

class MultiPlayMults
{
public:
	float getMoneyMult(int slot) const;	// 0x00235971
};

class GlobalData
{
public:
	char m_pad000[0xEC4];
	MultiPlayMults m_multiPlayMults;	// +0xEC4
};
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
class InGameUI {
public:
 virtual void slot000();
 virtual void slot001();
 virtual void slot002();
 virtual void slot003();
 virtual void slot004();
 virtual void slot005();
 virtual void slot006();
 virtual void slot007();
 virtual void slot008();
 virtual void slot009();
 virtual void slot010();
 virtual void slot011();
 virtual void slot012();
 virtual void slot013();
 virtual void slot014();
 virtual void slot015();
 virtual void slot016();
 virtual void slot017();
 virtual void slot018();
 virtual void slot019();
 virtual void slot020();
 virtual void slot021();
 virtual void slot022();
 virtual void slot023();
 virtual void slot024();
 virtual void slot025();
 virtual void slot026();
 virtual void slot027();
 virtual void slot028();
 virtual void slot029();
 virtual void slot030();
 virtual void slot031();
 virtual void slot032();
 virtual void slot033();
 virtual void slot034();
 virtual void slot035();
 virtual void slot036();
 virtual void slot037();
 virtual void slot038();
 virtual void slot039();
 virtual void slot040();
 virtual void slot041();
 virtual void slot042();
 virtual void slot043();
 virtual void slot044();
 virtual void slot045();
 virtual void slot046();
 virtual void slot047();
 virtual void slot048();
 virtual void slot049();
 virtual void slot050();
 virtual void slot051();
 virtual void slot052();
 virtual void slot053();
 virtual void slot054();
 virtual void slot055();
 virtual void slot056();
 virtual void slot057();
 virtual void slot058();
 virtual void slot059();
 virtual void slot060();
 virtual void slot061();
 virtual void slot062();
 virtual void slot063();
 virtual void slot064();
 virtual void slot065();
 virtual void slot066();
 virtual void slot067();
 virtual void slot068();
 virtual void slot069();
 virtual void slot070();
 virtual void slot071();
 virtual void slot072();
 virtual void slot073();
 virtual void slot074();
 virtual void slot075();
 virtual void slot076();
 virtual void slot077();
 virtual void slot078();
 virtual void slot079();
 virtual void slot080();
 virtual void slot081();
 virtual void slot082();
 virtual void slot083();
 virtual void slot084();
 virtual void slot085();
 virtual void slot086();
 virtual void slot087();
 virtual void slot088();
 virtual void slot089();
 virtual void slot090();
 virtual void slot091();
 virtual void slot092();
 virtual void slot093();
 virtual void slot094();
 virtual void slot095();
 virtual void slot096();
 virtual void slot097();
 virtual void slot098();
 virtual void slot099();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void addFloatingText(const UnicodeString &,const Coord3D *,unsigned);
};
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
  moneyString.format(TheGameText->slot44("GUI:AddCash",0),bounty);
  pos.x=victimObject->pos.x;pos.y=victimObject->pos.y;pos.z=victimObject->pos.z;
  pos.z+=10.0f;
  TheInGameUI->addFloatingText(moneyString,&pos,0xffffff00);
 }
}
