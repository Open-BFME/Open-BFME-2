// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
//
// ?onVeterancyLevelChanged@Object@@QAEXW4VeterancyLevel@@0@Z
// retail 0x00294F5E..0x002951AB (589 bytes) EH thiscall ret 8.
// Zero Hour Object::onVeterancyLevelChanged without the provideFeedback
// argument: updateUpgradeModules (rowed 0x00292EEA); TheUpgradeCenter
// findVeterancyUpgrade (rowed 0x0026F3D0) then the giveUpgrade row
// 0x00293077; the body module at +0x254 slot 11 (ActiveBody's rowed
// onVeterancyLevelChanged 0x004BE47D takes the same two levels); the stealth
// gate through isLocallyControlled (0x0028B07A) and rva002943B2 (0x002943B2)
// plus the template kindof bit at +0x10D; the per-level weapon set flags
// (rowed set/clear 0x00290963/0x00290A10) and the weapon bonus bits 9..11 of
// the word at +0x380; then with TheGameLogic's draw-icon byte (+0x9A) the
// level-gain animation from TheGlobalData (+0x11C name and +0x120/+0x124
// display time and rise) placed at the position plus the +0x310 offset via
// InGameUI::addWorldAnimation (0x002A0E16) and the misc-audio unit-promoted
// event (+0x64) with the object id at +0x74. WorldBuilder twin 0x00CD3CF0
// has the same call graph.
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

enum VeterancyLevel
{
	LEVEL_REGULAR = 0,
	LEVEL_VETERAN = 1,
	LEVEL_ELITE = 2,
	LEVEL_HEROIC = 3
};

enum WeaponSetType
{
	WEAPONSET_VETERAN = 0,
	WEAPONSET_ELITE = 1,
	WEAPONSET_HERO = 2
};

enum WeaponBonusConditionType
{
	WEAPONBONUSCONDITION_VETERAN = 9,
	WEAPONBONUSCONDITION_ELITE = 10,
	WEAPONBONUSCONDITION_HERO = 11
};

enum WorldAnimationOptions
{
	WORLD_ANIM_NO_OPTIONS = 0,
	WORLD_ANIM_FADE_ON_EXPIRE = 1
};

class Player;
class UpgradeTemplate;
class Anim2DTemplate;
struct Rva002D752DNode;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findVeterancyUpgrade(VeterancyLevel level) const;
};

class Rva002D752D
{
public:
	Rva002D752DNode *rva002D752D(const StringBase<char> &name);
};

class InGameUI
{
public:
	void addWorldAnimation(Anim2DTemplate *animTemplate, const Coord3D *pos,
		WorldAnimationOptions options, float durationInSeconds, float zRisePerSecond);
};

class GlobalData
{
public:
	char m_pad0[0x11C];
	AsciiString m_levelGainAnimationName;	// +0x11C
	float m_levelGainAnimationDisplayTimeInSeconds;	// +0x120
	float m_levelGainAnimationZRisePerSecond;	// +0x124
};

class Anim2DCollection;
class AudioManager;

extern UpgradeCenter *TheUpgradeCenter;
extern GameLogic *TheGameLogic;
extern Anim2DCollection *TheAnim2DCollection;
extern GlobalData *TheWritableGlobalData;
extern InGameUI *TheInGameUI;
extern AudioManager *TheAudio;

struct VeterancyMiscAudioView
{
	char m_pad[0x64];
	OpaqueRefElement4 m_unitPromoted;	// +0x64
};

class VeterancyAudioView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *evt);
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual const VeterancyMiscAudioView *getMiscAudio();
};

class Rva002D9531
{
public:
	void rva002D9531(int id);
};

class BodyModuleInterface
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel);
};

struct CoordMath
{
	static void add(Coord3D &dst, const Coord3D *a)
	{
		dst.x += a->x;
		dst.y += a->y;
		dst.z += a->z;
	}
};

struct ThingTemplate
{
	char m_pad0[0x10D];
	unsigned char m_kindOf10D;	// +0x10D, bit 0x80 is the GUI-ignored kindof
};

class Object
{
public:
	void onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel);

	void updateUpgradeModules();
	void rva00293077(const void *upgrade);
	bool isLocallyControlled() const;
	bool rva002943B2(const Player *player);
	void setWeaponSetFlag(WeaponSetType wst);
	void clearWeaponSetFlag(WeaponSetType wst);

	void setWeaponBonusCondition(WeaponBonusConditionType wst) { m_weaponBonusCondition |= (1 << wst); }
	void clearWeaponBonusCondition(WeaponBonusConditionType wst) { m_weaponBonusCondition &= ~(1 << wst); }

	char m_pad0[4];
	ThingTemplate *m_template;	// +0x04
	char m_pad8[0x38 - 0x08];
	Coord3D m_pos;	// +0x38
	char m_pad44[0x74 - 0x44];
	int m_id;	// +0x74
	char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body;	// +0x254
	char m_pad258[0x310 - 0x258];
	Coord3D m_iconOffset;	// +0x310
	char m_pad31C[0x380 - 0x31C];
	unsigned int m_weaponBonusCondition;	// +0x380
};

void Object::onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel)
{
	updateUpgradeModules();

	const UpgradeTemplate *up = TheUpgradeCenter->findVeterancyUpgrade(newLevel);
	if (up)
		rva00293077(up);

	BodyModuleInterface *body = m_body;
	if (body)
		body->onVeterancyLevelChanged(oldLevel, newLevel);

	bool hideAnimationForStealth = false;
	if (!isLocallyControlled() && rva002943B2(0))
		hideAnimationForStealth = true;

	bool doAnimation = (!hideAnimationForStealth
		&& newLevel > oldLevel
		&& !(m_template->m_kindOf10D & 0x80));

	switch (newLevel)
	{
		case LEVEL_REGULAR:
			clearWeaponSetFlag(WEAPONSET_VETERAN);
			clearWeaponSetFlag(WEAPONSET_ELITE);
			clearWeaponSetFlag(WEAPONSET_HERO);
			clearWeaponBonusCondition(WEAPONBONUSCONDITION_VETERAN);
			clearWeaponBonusCondition(WEAPONBONUSCONDITION_ELITE);
			clearWeaponBonusCondition(WEAPONBONUSCONDITION_HERO);
			doAnimation = false;
			break;
		case LEVEL_VETERAN:
			setWeaponSetFlag(WEAPONSET_VETERAN);
			clearWeaponSetFlag(WEAPONSET_ELITE);
			clearWeaponSetFlag(WEAPONSET_HERO);
			setWeaponBonusCondition(WEAPONBONUSCONDITION_VETERAN);
			clearWeaponBonusCondition(WEAPONBONUSCONDITION_ELITE);
			clearWeaponBonusCondition(WEAPONBONUSCONDITION_HERO);
			break;
		case LEVEL_ELITE:
			clearWeaponSetFlag(WEAPONSET_VETERAN);
			setWeaponSetFlag(WEAPONSET_ELITE);
			clearWeaponSetFlag(WEAPONSET_HERO);
			clearWeaponBonusCondition(WEAPONBONUSCONDITION_VETERAN);
			setWeaponBonusCondition(WEAPONBONUSCONDITION_ELITE);
			clearWeaponBonusCondition(WEAPONBONUSCONDITION_HERO);
			break;
		case LEVEL_HEROIC:
			clearWeaponSetFlag(WEAPONSET_VETERAN);
			clearWeaponSetFlag(WEAPONSET_ELITE);
			setWeaponSetFlag(WEAPONSET_HERO);
			clearWeaponBonusCondition(WEAPONBONUSCONDITION_VETERAN);
			clearWeaponBonusCondition(WEAPONBONUSCONDITION_ELITE);
			setWeaponBonusCondition(WEAPONBONUSCONDITION_HERO);
			break;
	}

	if (doAnimation && TheGameLogic->getDrawIconUI())
	{
		if (TheAnim2DCollection && !TheWritableGlobalData->m_levelGainAnimationName.isEmpty())
		{
			Anim2DTemplate *animTemplate = reinterpret_cast<Anim2DTemplate *>(
				reinterpret_cast<Rva002D752D *>(TheAnim2DCollection)->rva002D752D(
					*reinterpret_cast<const StringBase<char> *>(&TheWritableGlobalData->m_levelGainAnimationName)));

			Coord3D iconPosition;
			iconPosition.x = m_pos.x;
			iconPosition.y = m_pos.y;
			iconPosition.z = m_pos.z;
			CoordMath::add(iconPosition, &m_iconOffset);

			TheInGameUI->addWorldAnimation(animTemplate, &iconPosition, WORLD_ANIM_FADE_ON_EXPIRE,
				TheWritableGlobalData->m_levelGainAnimationDisplayTimeInSeconds,
				TheWritableGlobalData->m_levelGainAnimationZRisePerSecond);
		}

		BfmeAudioEventPrefix136 soundToPlay(reinterpret_cast<VeterancyAudioView *>(TheAudio)->getMiscAudio()->m_unitPromoted, 0);
		reinterpret_cast<Rva002D9531 *>(&soundToPlay)->rva002D9531(m_id);
		reinterpret_cast<VeterancyAudioView *>(TheAudio)->addAudioEvent(&soundToPlay);
	}
}
