// ?action@SupplyCenterDockUpdate@@UAE_NPAVObject@@0@Z
// partial score=0.97 date=2026-10-09
// Donor: BFME1 f98983a7 SupplyCenterDockUpdateAction.cpp; native WB identity and vtable slot 12.
// Native 0x004A0EAD..0x004A10D5 establishes every adjusted object/player offset and call.
// Only the inline rounding helper uses x87 assembly: existing BaseType.h / Player::ScaleMoney pattern reproduces native fistp.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "../../reference/shims/bfme2_ascii/unicode_string.h"
#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
typedef float Real;
struct Coord3D { float x, y, z; };
enum ScienceType { SCIENCE_INVALID = -1 };
class Rva0039B7AD;
class Rva003B0D7C { public: void rva003B0D7C(int, Rva0039B7AD *, bool); };
class Player {
public:
 int getSupplyBoxValue(); int ScaleMoney(int); bool hasScience(ScienceType) const;
 Rva003B0D7C *getMoney() { return (Rva003B0D7C *)((char *)this + 0x90); }
 Rva0039B7AD *getScoreKeeper() { return (Rva0039B7AD *)((char *)this + 0x3bc); }
 unsigned int getPlayerColor() const { return m_color; }
private: char pad[0x280]; unsigned int m_color;
};
class SupplyTruckAIInterface { public: virtual void s0(); virtual void s1(); virtual bool loseOneBox(); };
class BFMEAIUpdateInterface {
public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual void s48();
 virtual void s49();
 virtual void s50();
 virtual void s51();
 virtual void s52();
 virtual void s53();
 virtual void s54();
 virtual void s55();
 virtual void s56();
 virtual void s57();
 virtual void s58();
 virtual void s59();
 virtual void s60();
 virtual void s61();
 virtual void s62();
 virtual void s63();
 virtual void s64();
 virtual void s65();
 virtual void s66();
 virtual void s67();
 virtual void s68();
 virtual void s69();
 virtual void s70();
 virtual void s71();
 virtual void s72();
 virtual void s73();
 virtual void s74();
 virtual void s75();
 virtual void s76();
 virtual void s77();
 virtual void s78();
 virtual void s79();
 virtual void s80();
 virtual void s81();
 virtual void s82();
 virtual void s83();
 virtual void s84();
 virtual void s85();
 virtual void s86();
 virtual void s87();
 virtual void s88();
 virtual void s89();
 virtual void s90();
 virtual void s91();
 virtual void s92();
 virtual void s93();
 virtual void s94();
 virtual SupplyTruckAIInterface *getSupplyTruckAIInterface();
};
class ExperienceTracker { public: bool rva0039AE04() const; void rva0039B315(float, bool, bool, bool, bool); };
class Object {
public:
 Player *getControllingPlayer() const; bool rva0028C15E(int, float *, int, int);
 const Coord3D *getPosition() const { return (const Coord3D *)((char *)this + 0x38); }
};
inline BFMEAIUpdateInterface *bfmeGetAI(const Object *o) { return *(BFMEAIUpdateInterface **)((char *)o + 0x258); }
inline ExperienceTracker *bfmeGetExperienceTracker(const Object *o) { return *(ExperienceTracker **)((char *)o + 0x264); }
class BfmeGlob939D { public: char bfmeCall939D(); };
class PlayerList { public: int rva002A7C0B(bool); };
class MultiPlayMults { public: float getMoneyMult(int) const; };
extern GameLogic *TheGameLogic; extern PlayerList *ThePlayerList;
class GlobalData; extern GlobalData *TheGlobalData;
class GameText {
public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual const UnicodeString *fetch(const char *, bool = false);
};
extern GameText *TheGameText;
class TerrainLogic {
public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual float getGroundHeight(float, float, void * = 0) const;
};
extern TerrainLogic *TheTerrainLogic;
class InGameUI {
public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual void s48();
 virtual void s49();
 virtual void s50();
 virtual void s51();
 virtual void s52();
 virtual void s53();
 virtual void s54();
 virtual void s55();
 virtual void s56();
 virtual void s57();
 virtual void s58();
 virtual void s59();
 virtual void s60();
 virtual void s61();
 virtual void s62();
 virtual void s63();
 virtual void s64();
 virtual void s65();
 virtual void s66();
 virtual void s67();
 virtual void s68();
 virtual void s69();
 virtual void s70();
 virtual void s71();
 virtual void s72();
 virtual void s73();
 virtual void s74();
 virtual void s75();
 virtual void s76();
 virtual void s77();
 virtual void s78();
 virtual void s79();
 virtual void s80();
 virtual void s81();
 virtual void s82();
 virtual void s83();
 virtual void s84();
 virtual void s85();
 virtual void s86();
 virtual void s87();
 virtual void s88();
 virtual void s89();
 virtual void s90();
 virtual void s91();
 virtual void s92();
 virtual void s93();
 virtual void s94();
 virtual void s95();
 virtual void s96();
 virtual void s97();
 virtual void s98();
 virtual void s99();
 virtual void s100();
 virtual void s101();
 virtual void s102();
 virtual void s103();
 virtual void addFloatingText(const UnicodeString &, const Coord3D *, unsigned int);
};
extern InGameUI *TheInGameUI;
extern "C" __declspec(dllimport) double __cdecl ceil(double);
__forceinline long fast_float2long_round(float f) { long i; __asm { fld [f] } __asm { fistp [i] } return i; }
struct SupplyCenterDockUpdateModuleData { char pad[0x10]; float m_valueMultiplier; int m_bonusScience; float m_bonusScienceMultiplier; };
class SupplyCenterDockUpdate {
public:
 virtual bool action(Object *, Object *);
 SupplyCenterDockUpdateModuleData *getSupplyCenterDockUpdateModuleData() const { return *(SupplyCenterDockUpdateModuleData **)((char *)this - 0x1c); }
 Object *getObject() const { return *(Object **)((char *)this - 0x18); }
};
bool SupplyCenterDockUpdate::action(Object *docker, Object *drone)
{
	SupplyTruckAIInterface *supplyTruckAI = 0;
	BFMEAIUpdateInterface *ai = bfmeGetAI(docker);
	if (ai == 0)
		return false;

	supplyTruckAI = ai->getSupplyTruckAIInterface();
	if (supplyTruckAI == 0)
		return false;

	float value = 0.0f;
	Player *ownerPlayer = getObject()->getControllingPlayer();
	while (supplyTruckAI->loseOneBox())
	{
		value += (Real)(unsigned int)ownerPlayer->getSupplyBoxValue();
	}

	if (!(value > 0.0f))
		return false;

	float multiplier = 1.0f;
	getObject()->rva0028C15E(0xd, &multiplier, 0, 1);
	value *= multiplier;
	Rva003B0D7C *ownerPlayerMoney = ownerPlayer->getMoney();
	value *= getSupplyCenterDockUpdateModuleData()->m_valueMultiplier;

	if (((BfmeGlob939D *)TheGameLogic)->bfmeCall939D())
	{
		int playerCount = ThePlayerList->rva002A7C0B(false);
		float scale = ((MultiPlayMults *)((char *)TheGlobalData + 0xec4))->getMoneyMult(playerCount);
		value *= scale;
	}

	value = (Real)ownerPlayer->ScaleMoney((int)value);

	if (ownerPlayer->hasScience((ScienceType)getSupplyCenterDockUpdateModuleData()->m_bonusScience))
	{
		value *= getSupplyCenterDockUpdateModuleData()->m_bonusScienceMultiplier;
	}

	int finalValue = fast_float2long_round((Real)ceil(value));

	ownerPlayerMoney->rva003B0D7C(finalValue, ownerPlayer->getScoreKeeper(), true);

	ExperienceTracker *tracker = bfmeGetExperienceTracker(getObject());
	if (tracker != 0 && tracker->rva0039AE04())
	{
		tracker->rva0039B315(value, true, true, true, false);
	}

	UnicodeString moneys;
	moneys.format(TheGameText->fetch("GUI:AddCash"), finalValue);

	Coord3D pos;
	const Coord3D *dockerPos = docker->getPosition();
	pos.x = dockerPos->x;
	pos.y = dockerPos->y;
	pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);

	unsigned int color = ownerPlayer->getPlayerColor() | 0xe6000000;
	TheInGameUI->addFloatingText(moneys, &pos, color);

	return false;
}
