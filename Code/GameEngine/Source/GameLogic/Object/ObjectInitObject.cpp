// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?initObject@Object@@QAEXXZ, retail 0x002934E7, 1087 bytes.
//
// Identity: existing pin ?initObject@Object@@QAEXXZ. Donor: Open-BFME-1
// game/GameEngine/Source/GameLogic/Object/Object.cpp and ZH Object::initObject
// supply the opening sequence (weapon-condition reset, sendObjectCreated,
// updateUpgradeModules, difficulty bonus and battle plans, special-power mask
// from behavior modules, projectile/inert script notification, weapon set
// update). Everything after the weapon set is BFME2-only and follows the target
// body: two template-driven extra weapons (+0x600/+0x604 -> +0x39C/+0x3A0),
// emotion/hero/radar registration, experience tracker reset, the War of the
// Ring player attribute modifier "AttributeMod_WOTR_Player_%d", the weather
// system hook and the "HandicapPercent%d" modifier. Helper identities that the
// ledger does not resolve keep address-derived names.
//
// Codegen notes: isKindOf goes through the getTemplate() accessor (as in the
// matched setTriggerAreaFlagsForChangeInPosition unit); inlined directly, cl
// folds the KINDOF 8..11 tests into one `test byte [t+0x109],0xF` where
// retail keeps four. The modifier pointer is assigned in an if/else (keeps
// retail's xor ebx,ebx after the modName dtor), and the handicap goes through
// a raw temporary before the negation as the WorldBuilder twin 0x00CBD700
// does (retail's neg eax / mov ecx,eax). Both string literals were checked
// against retail 0x00BFC0E0 and 0x00BFC0CC.
// class-gate: allow GameLogic canonical view lacks rva0023FABE (the donor sendObjectCreated slot) and rva0023C6FD and the +0x6F flag and +0x180 trigger-change frame this body reads and writes

#include <string.h>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector;
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Object;
class Weapon;
class WeaponTemplate;

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
};
extern WeaponStore *TheWeaponStore;

class Weapon
{
public:
	void loadAmmoNow(const Object *source);
	char m_pad00[8];
	Int m_ownerID;
};

class WeaponSet
{
public:
	void updateWeaponSet(const Object *obj);
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(Int k) const { return m_kindOf[k >> 5] & (1U << (k & 0x1f)); }
	char m_pad000[0x108];
	UnsignedInt m_kindOf[8];
	char m_pad128[0x600 - 0x128];
	const WeaponTemplate *m_extraWeaponTemplates[2];
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class SpecialPowerTemplate : public Overridable
{
public:
	UnsignedInt getSpecialPowerType() const
	{
		return static_cast<const SpecialPowerTemplate *>(friend_getFinalOverride())->m_type;
	}
	char m_pad00[0x1C];
	UnsignedInt m_type;
};

class SpecialPowerModuleInterface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2();
	virtual void s3(); virtual void s4(); virtual void s5();
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
};

class BehaviorModuleInterface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual SpecialPowerModuleInterface *getSpecialPower();
};

class ObjectModuleView
{
public:
	virtual void s0();
	char m_pad04[0x0C - 0x04];
};

class BehaviorModule : public ObjectModuleView, public BehaviorModuleInterface
{
};

class Rva0039CBCE
{
public:
	void rva0039CBCE(Object *obj, Int flag);
};

class Player
{
public:
	void applyBattlePlanBonusesForObject(Object *obj) const;
	Int getNumBattlePlansActive() const
	{
		return m_battlePlansB4 + m_battlePlansB0 + m_battlePlansAC;
	}
	char m_pad000[0xAC];
	Int m_battlePlansAC;
	Int m_battlePlansB0;
	Int m_battlePlansB4;
	char m_pad0B8[0x27C - 0xB8];
	Int m_handicap;
	char m_pad280[0x3AC - 0x280];
	Int m_3ac;
	char m_pad3B0[0x3BC - 0x3B0];
	Rva0039CBCE m_3bc;
};

class GameLogic
{
public:
	void rva0023FABE(Object *obj);
	char rva0023C6FD();
	char m_pad000[0x40];
	UnsignedInt m_frame;
	char m_pad044[0x6F - 0x44];
	Bool m_6f;
	char m_pad070[0x114 - 0x70];
	Int m_114;
	char m_pad118[0x180 - 0x118];
	UnsignedInt m_frameObjectsChangedTriggerAreas;
};
extern GameLogic *TheGameLogic;

class Rva002034E9Host
{
public:
	Bool rva002034E9();
};

class ScriptEngine
{
public:
	char m_pad[0x1A4D5];
	Bool m_objectsShouldReceiveDifficultyBonus;
};
extern ScriptEngine *TheScriptEngine;

class Rva002039B6Host
{
public:
	void rva002039B6();
};

class EmotionSystem
{
public:
	void RegisterScaryObject(Object *obj);
};
extern EmotionSystem *TheEmotionSystem;

class CreateAHeroManager
{
public:
	void BindHeroToObjectAndUpdate(Object *obj);
};
extern CreateAHeroManager *TheCreateAHeroManager;

struct Obj00526309;
class Rva002D3726
{
public:
	void rva002D3726(Obj00526309 *obj);
};
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Rva0020E89C
{
public:
	char m_pad[0x14];
	AsciiString m_name;
};

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(Int id);
};

class Rva002E2903Player
{
public:
	char m_pad[0x284];
	Int m_284;
	Int m_288;
	Int m_28c;
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(Int id, UnsignedInt *index);
};

class LivingWorldLogic
{
public:
	char m_pad[0xB0];
	Rva0020EAF6View *m_b0;
	char m_padB4[4];
	Int m_b8;

	Rva0020EAF6View *getRegionManager() const { return m_b0; }
	Int getCurrentRegionID() const { return m_b8; }
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva004045B4
{
public:
	void rva004045B4(Int type, Real value,
		const _STL::vector<AsciiString, _STL::allocator<AsciiString> > *names);
};

class AttributeModifierStore
{
public:
	Int rva00214713(Int key);
	void *rva002149A5(Int index);
};
extern AttributeModifierStore *TheAttributeModifierStore;

class GlobalWeatherSystem;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
class Rva00318333
{
public:
	void rva00318333(Object *obj, Bool flag);
};

class Rva003BD306Target
{
public:
	void rva0039B28F(Int value);
};
class Rva0039B20C
{
public:
	void rva0039B246();
};

class Object
{
public:
	void initObject();
	void updateUpgradeModules();
	Player *getControllingPlayer() const;
	void rva0028DA67();
	Bool rva0028D491() const;
	void setReceivingDifficultyBonus(Bool receive);
	Bool addAttributeModifierToPool(const AsciiString &name, Int duration);

	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline UnsignedInt isKindOf(Int k) const { return getTemplate()->isKindOf(k); }
	Bool getReceivingDifficultyBonus() const { return m_receivingDifficultyBonus; }
	__forceinline void createExtraWeapon(Int index)
	{
		const WeaponTemplate *tmpl = m_template->m_extraWeaponTemplates[index];
		if (tmpl)
		{
			Weapon *weapon = TheWeaponStore->allocateNewWeapon(tmpl, PRIMARY_WEAPON);
			Int id = m_id;
			m_extraWeapons[index] = weapon;
			m_extraWeapons[index]->m_ownerID = id;
			m_extraWeapons[index]->loadAmmoNow(this);
		}
	}

private:
	char m_pad000[4];
	const ThingTemplate *m_template;
	char m_pad008[0x74 - 0x08];
	Int m_id;
	char m_pad078[0x244 - 0x78];
	BehaviorModule **m_behaviors;
	char m_pad248[0x264 - 0x248];
	void *m_experienceTracker;
	char m_pad268[0x330 - 0x268];
	WeaponSet m_weaponSet;
	char m_pad331[0x384 - 0x331];
	unsigned short m_lastWeaponCondition[3];
	char m_pad38A[0x39C - 0x38A];
	Weapon *m_extraWeapons[2];
	UnsignedInt m_specialPowerBits[2];
	char m_pad3AC[0x43C - 0x3AC];
	Bool m_receivingDifficultyBonus;
	char m_pad43D[0x478 - 0x43D];
	AsciiString m_478;
};

enum
{
	KINDOF_BIT_7 = 7,
	KINDOF_BIT_8 = 8,
	KINDOF_BIT_9 = 9,
	KINDOF_BIT_10 = 10,
	KINDOF_BIT_11 = 11,
	KINDOF_PROJECTILE_BIT = 25,
	KINDOF_INERT_BIT = 89,
	KINDOF_BIT_90 = 90,
	KINDOF_BIT_128 = 128,
	KINDOF_BIT_144 = 144,
	KINDOF_BIT_190 = 190
};

void Object::initObject()
{
	for (Int i = 0; i < 3; ++i)
		m_lastWeaponCondition[i] = 0xFFFF;

	TheGameLogic->rva0023FABE(this);

	updateUpgradeModules();

	Player *controller = getControllingPlayer();
	if (controller)
	{
		rva0028DA67();
		if (!getReceivingDifficultyBonus() && TheScriptEngine->m_objectsShouldReceiveDifficultyBonus)
			setReceivingDifficultyBonus(true);

		if (controller->getNumBattlePlansActive() > 0)
			controller->applyBattlePlanBonusesForObject(this);
	}

	for (BehaviorModule **m = m_behaviors; *m; ++m)
	{
		SpecialPowerModuleInterface *sp = (*m)->getSpecialPower();
		if (!sp)
			continue;

		const SpecialPowerTemplate *spTemplate = sp->getSpecialPowerTemplate();
		if (spTemplate)
		{
			UnsignedInt type = spTemplate->getSpecialPowerType();
			m_specialPowerBits[type >> 5] |= 1U << (type & 0x1f);
		}
	}

	if (!isKindOf(KINDOF_PROJECTILE_BIT) && !isKindOf(KINDOF_INERT_BIT))
	{
		reinterpret_cast<Rva002039B6Host *>(TheScriptEngine)->rva002039B6();
		TheGameLogic->m_frameObjectsChangedTriggerAreas = TheGameLogic->m_frame;
	}

	m_weaponSet.updateWeaponSet(this);

	createExtraWeapon(0);
	createExtraWeapon(1);

	if (isKindOf(KINDOF_BIT_144) || isKindOf(KINDOF_BIT_90))
		TheEmotionSystem->RegisterScaryObject(this);

	if (isKindOf(KINDOF_BIT_128) && reinterpret_cast<Rva002034E9Host *>(TheGameLogic)->rva002034E9())
	{
		Rva0020E89C *region = TheLivingWorldLogic->getRegionManager()->rva0020EAF6(
			TheLivingWorldLogic->getCurrentRegionID());
		m_478 = region ? region->m_name : AsciiString::TheEmptyString;
	}

	if (isKindOf(KINDOF_BIT_190) && !TheGameLogic->m_6f)
		TheCreateAHeroManager->BindHeroToObjectAndUpdate(this);

	if (theRadarWindowOverrideSource)
		reinterpret_cast<Rva002D3726 *>(theRadarWindowOverrideSource)->rva002D3726(
			reinterpret_cast<Obj00526309 *>(this));

	void *&tracker = m_experienceTracker;
	if (tracker)
	{
		reinterpret_cast<Rva003BD306Target *>(tracker)->rva0039B28F(0);
		reinterpret_cast<Rva0039B20C *>(tracker)->rva0039B246();
	}

	if (TheGameLogic->m_114 != 3 && !isKindOf(KINDOF_BIT_90) && !isKindOf(KINDOF_BIT_7))
	{
		UnsignedInt index = 0;
		Int playerID = getControllingPlayer()->m_3ac;
		Rva002E2903Player *wotrPlayer = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(
			playerID, &index);
		if (wotrPlayer)
		{
			AsciiString modName;
			modName.format("AttributeMod_WOTR_Player_%d", index);
			Int modIndex = TheAttributeModifierStore->rva00214713(TheNameKeyGenerator->nameToKey(modName));
			Rva004045B4 *mod;
			if (modIndex != -1)
				mod = (Rva004045B4 *)TheAttributeModifierStore->rva002149A5(modIndex);
			else
				mod = 0;
			if (mod)
			{
				mod->rva004045B4(3, wotrPlayer->m_284 * 0.01f + 1.0f, 0);
				mod->rva004045B4(1, wotrPlayer->m_288 * 0.01f, 0);
				mod->rva004045B4(6, wotrPlayer->m_28c * 0.01f + 1.0f, 0);
				addAttributeModifierToPool(modName, -1);
			}
		}
	}

	reinterpret_cast<Rva00318333 *>(TheGlobalWeatherSystem)->rva00318333(this, false);

	if (TheGameLogic->rva0023C6FD())
	{
		if (isKindOf(KINDOF_BIT_7) || rva0028D491() || isKindOf(KINDOF_BIT_8) ||
			isKindOf(KINDOF_BIT_9) || isKindOf(KINDOF_BIT_10) || isKindOf(KINDOF_BIT_11) ||
			isKindOf(KINDOF_BIT_90))
		{
			Int raw = controller->m_handicap;
			Int handicap = -raw;
			if (handicap > 0 && handicap <= 100 && handicap % 5 == 0)
			{
				AsciiString modName;
				modName.format("HandicapPercent%d", handicap);
				addAttributeModifierToPool(modName, -1);
			}
		}
	}

	Player *owner = getControllingPlayer();
	owner->m_3bc.rva0039CBCE(this, 1);
}
