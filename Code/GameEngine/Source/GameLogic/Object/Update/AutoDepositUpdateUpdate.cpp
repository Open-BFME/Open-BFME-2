// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
//
// AutoDepositUpdate::update (BFME 2), from the Generals Zero Hour
// AutoDepositUpdate.cpp.
//
// Target facts. update is slot 0 of AutoDepositUpdate's UpdateModuleInterface
// vftable; the deposit frame is at +0x20 and the award-initial-capture-bonus
// and initialized bytes at +0x24/+0x25, in the ZH order. The module data
// (field table 0x00BF1CC8) holds DepositTiming +8, DepositAmount +0xC,
// InitialCaptureBonus +0x10, Upgrade +0x14, UpgradeBonusPercent +0x18,
// UpgradeMustBePresent +0x1C, GiveNoXP +0x20 and OnlyWhenGarrisoned +0x21.
// BFME 2 rewrites the ZH body after the construction check:
// - OnlyWhenGarrisoned gates on Object::isKindOf(10); three more bits of the
//   same +0x10C mask (5, 59, 60), read inline, skip the deposit.
// - The amount is DepositAmount times a multiplier: 1.0 run through the
//   object's modifier query 0x0028C15E (type 13), times UpgradeBonusPercent
//   when the controlling player has Upgrade (0x002AB87D) and passes the
//   UpgradeMustBePresent check (0x002AB2D9). In a multiplayer game
//   (GameLogic 0x0023C6FD) it is scaled by the slot's money multiplier, then by
//   Player::ScaleMoney, and deposited with the player's score record
//   (SalvageCrateCollide::doMoney's sequence).
// - Unless GiveNoXP, a trainable experience tracker (+0x264) gains the
//   multiplied deposit as experience.
// - The cash text no longer depends on stealth and shows at the object's
//   position raised by 10, in the player's color (+0x280) with alpha 230.
#include "ascii_string.h"
#include "unicode_string.h"
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef Int Color;

#define TRUE 1
#define NULL 0

#define CONSTRUCTION_COMPLETE -1.0f
#define GameMakeColor(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

class ModuleData;
class UpgradeTemplate;
class BfmeTab1026;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum KindOfType
{
	KINDOF_0A = 10
};

class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, Bool *exists);
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
#define IGUI_SLOTS10(n) virtual void s##n##0(); virtual void s##n##1(); virtual void s##n##2(); \
	virtual void s##n##3(); virtual void s##n##4(); virtual void s##n##5(); virtual void s##n##6(); \
	virtual void s##n##7(); virtual void s##n##8(); virtual void s##n##9();
	IGUI_SLOTS10(0) IGUI_SLOTS10(1) IGUI_SLOTS10(2) IGUI_SLOTS10(3) IGUI_SLOTS10(4)
	IGUI_SLOTS10(5) IGUI_SLOTS10(6) IGUI_SLOTS10(7) IGUI_SLOTS10(8) IGUI_SLOTS10(9)
#undef IGUI_SLOTS10
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103();
	virtual void addFloatingText(const UnicodeString &text, const Coord3D *pos, Color color); // slot 104 (+0x1A0)
};
extern InGameUI *TheInGameUI;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	char rva0023C6FD(); // 0x0023C6FD, true in a multiplayer game

private:
	char m_unknown00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class PlayerList
{
public:
	int rva002A7C0B(bool flag); // 0x002A7C0B
};
extern PlayerList *ThePlayerList;

class MultiPlayMults
{
public:
	float getMoneyMult(int slot) const; // 0x00235971
};

class GlobalData
{
public:
	char m_pad000[0xEC4];
	MultiPlayMults m_multiPlayMults; // +0xEC4
};
extern class GlobalData *TheWritableGlobalData;

class Rva0039B7AD
{
	char m_pad[4];
};

class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *score, bool flag); // 0x003B0D7C
	char m_pad[4];
};

class Player
{
public:
	int ScaleMoney(int amount); // 0x002A9E36
	Bool rva002AB87D(const UpgradeTemplate *upgrade) const; // 0x002AB87D
	Bool rva002AB2D9(BfmeTab1026 *mustBePresent, Bool flag) const; // 0x002AB2D9
	Color getPlayerColor() const { return m_color; }

	char m_pad000[0x90];
	Rva003B0D7C m_money; // +0x90
	char m_pad094[0x280 - 0x94];
	Color m_color; // +0x280
	char m_pad284[0x3BC - 0x284];
	Rva0039B7AD m_3BC; // +0x3BC
};

class ExperienceTracker
{
public:
	Bool rva0039AE04() const; // 0x0039AE04
	void rva0039B315(Real experience, Bool flag1, Bool flag2, Bool flag3, Bool unused); // 0x0039B315
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	Bool isKindOf(KindOfType kind) const; // 0x0006F039
	// the same +0x10C mask isKindOf tests, read inline
	Bool testKindOfBit(Int bit) const { return (m_kindOf[bit >> 5] >> (bit & 31)) & 1; }
	Bool isNeutralControlled() const;
	Real getConstructionPercent() const { return m_constructionPercent; }
	Player *getControllingPlayer() const;
	Bool rva0028C15E(Int type, Real *value, Int a, Int b); // 0x0028C15E
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }

private:
	char m_unknown00[0x38];
	Coord3D m_position; // +0x38
	char m_unknown44[0x10C - 0x44];
	UnsignedInt m_kindOf[7]; // +0x10C
	char m_unknown128[0x264 - 0x128];
	ExperienceTracker *m_experienceTracker; // +0x264
	char m_unknown268[0x280 - 0x268];
	Real m_constructionPercent; // +0x280
};

class AutoDepositUpdateModuleData
{
public:
	char m_unknown00[0x08];
	UnsignedInt m_depositFrame; // +0x08
	Int m_depositAmount; // +0x0C
	Int m_initialCaptureBonus; // +0x10
	const UpgradeTemplate *m_upgrade; // +0x14
	Real m_upgradeBonusPercent; // +0x18
	char m_upgradeMustBePresent[4]; // +0x1C
	Bool m_giveNoXP; // +0x20
	Bool m_onlyWhenGarrisoned; // +0x21
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class AutoDepositUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

protected:
	const AutoDepositUpdateModuleData *getAutoDepositUpdateModuleData() const
	{
		return (const AutoDepositUpdateModuleData *)m_moduleData;
	}

	UnsignedInt m_depositOnFrame; // +0x20
	Bool m_awardInitialCaptureBonus; // +0x24
	Bool m_initialized; // +0x25
};

// ?update@AutoDepositUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0049A3AE 660B
UpdateSleepTime AutoDepositUpdate::update( void )
{
	if( TheGameLogic->getFrame() >= m_depositOnFrame )
	{
		if (!m_initialized) {
			// Note - we have to set these in update, because during load the team is set,
			// and we don't want to award initial bonus on load.  jba :)
			m_awardInitialCaptureBonus = TRUE;
			m_initialized = TRUE;
		}
		m_depositOnFrame = TheGameLogic->getFrame() + getAutoDepositUpdateModuleData()->m_depositFrame;

		if( getAutoDepositUpdateModuleData()->m_onlyWhenGarrisoned && !getObject()->isKindOf( KINDOF_0A ) )
			return UPDATE_SLEEP_NONE;

		if( getObject()->isNeutralControlled() || getAutoDepositUpdateModuleData()->m_depositAmount <= 0 )
			return UPDATE_SLEEP_NONE;

		// makes sure that buildings under construction do not get a bonus CCB
		if( getObject()->getConstructionPercent() != CONSTRUCTION_COMPLETE )
			return UPDATE_SLEEP_NONE;

		Bool kind05 = getObject()->testKindOfBit( 5 );
		Bool kind59 = getObject()->testKindOfBit( 59 );
		Bool kind60 = getObject()->testKindOfBit( 60 );
		if( kind05 || kind59 || kind60 )
			return UPDATE_SLEEP_NONE;

		Real multiplier = 1.0f;
		getObject()->rva0028C15E( 13, &multiplier, 0, 1 );

		Player *player = getObject()->getControllingPlayer();
		const UpgradeTemplate *upgrade = getAutoDepositUpdateModuleData()->m_upgrade;
		if( upgrade && player && player->rva002AB87D( upgrade )
			&& player->rva002AB2D9( (BfmeTab1026 *)getAutoDepositUpdateModuleData()->m_upgradeMustBePresent, false ) )
			multiplier *= getAutoDepositUpdateModuleData()->m_upgradeBonusPercent;

		UnsignedInt moneyAmount = (UnsignedInt)( getAutoDepositUpdateModuleData()->m_depositAmount * multiplier );
		if( TheGameLogic->rva0023C6FD() )
		{
			Real moneyMult = TheWritableGlobalData->m_multiPlayMults.getMoneyMult( ThePlayerList->rva002A7C0B( false ) );
			moneyAmount = (UnsignedInt)( moneyAmount * moneyMult );
		}
		moneyAmount = player->ScaleMoney( moneyAmount );
		player->m_money.rva003B0D7C( moneyAmount, &player->m_3BC, true );

		ExperienceTracker *xp = getObject()->getExperienceTracker();
		if( !getAutoDepositUpdateModuleData()->m_giveNoXP && xp && xp->rva0039AE04() )
			xp->rva0039B315( getAutoDepositUpdateModuleData()->m_depositAmount * multiplier, true, true, true, false );

		if( getAutoDepositUpdateModuleData()->m_depositAmount > 0 )
		{
			UnicodeString moneyString;
			moneyString.format( TheGameText->slot44( "GUI:AddCash", NULL ), moneyAmount );
			Coord3D pos;
			pos.x = getObject()->getPosition()->x;
			pos.y = getObject()->getPosition()->y;
			pos.z = getObject()->getPosition()->z;
			pos.z += 10.0f; //add a little z to make it show up above the unit.

			Color color = getObject()->getControllingPlayer()->getPlayerColor() | GameMakeColor( 0, 0, 0, 230 );
			TheInGameUI->addFloatingText( moneyString, &pos, color );
		}
	}

	return UPDATE_SLEEP_NONE;
}
