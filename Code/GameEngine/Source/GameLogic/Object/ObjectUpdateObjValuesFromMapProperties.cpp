// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?updateObjValuesFromMapProperties@Object@@QAEXPAVDict@@@Z, retail 0x002951AB, 1617 bytes.
//
// Identity: the existing pin names 0x002951AB from its REL32 call in
// AIPlayer::onStructureProduced; BridgeCtor.cpp and AIPlayerTeamBuild.cpp call
// it with the object's Dict. Donor: Open-BFME-1 game/GameEngine/Source/
// GameLogic/Object/Object.cpp and ZH Object::updateObjValuesFromMapProperties
// supply the key order and per-key semantics. Every key global below was
// identified from its retail StaticNameKey record (8 bytes: key, name
// pointer) whose name text is the TheKey_ suffix. BFME2-specific facts from
// the target body: experience level through 0x00294759, the +0x250 module's
// slot 0x7C sub-interface taking initial health, the stance module lookup,
// prototype scale on the drawable, time/weather as Object model-condition
// bits 7/8 at +0x10C, the events list through TheLuaScriptEngine, and the
// ambient-sound block factored into the cdecl helper 0x00433796.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_DISABLED = 1,
	OBJECT_STATUS_SCRIPT_UNPOWERED = 2,
	OBJECT_STATUS_SCRIPT_UNSELLABLE = 4,
	OBJECT_STATUS_SCRIPT_TARGETABLE = 0x10
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
	NameKeyType m_key;
	const char *m_name;
};

extern Rva00148F5ECache TheKey_objectName;
extern Rva00148F5ECache TheKey_objectInitialHealth;
extern Rva00148F5ECache TheKey_objectPrototypeScale;
extern Rva00148F5ECache TheKey_objectMaxHPs;
extern Rva00148F5ECache TheKey_objectEnabled;
extern Rva00148F5ECache TheKey_objectIndestructible;
extern Rva00148F5ECache TheKey_objectUnsellable;
extern Rva00148F5ECache TheKey_objectTargetable;
extern Rva00148F5ECache TheKey_objectPowered;
extern Rva00148F5ECache TheKey_objectEventsList;
extern Rva00148F5ECache TheKey_objectAggressiveness;
extern Rva00148F5ECache TheKey_objectInitialStance;
extern Rva00148F5ECache TheKey_objectVisualRange;
extern Rva00148F5ECache TheKey_objectShroudClearingDistance;
extern Rva00148F5ECache TheKey_objectRecruitableAI;
extern Rva00148F5ECache TheKey_objectSelectable;
extern Rva00148F5ECache TheKey_objectTime;
extern Rva00148F5ECache TheKey_objectWeather;
extern Rva00148F5ECache TheKey_objectStoppingDistance;
extern Rva00148F5ECache TheKey_objectGrantUpgrade;
extern Rva00148F5ECache TheKey_objectExperienceLevel;

class Dict
{
public:
	Bool getBool(Int key, Bool *exists) const;
	Int getInt(Int key, Bool *exists) const;
	Real getReal(Int key, Bool *exists) const;
	AsciiString getAsciiString(Int key, Bool *exists) const;
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

struct Rva00336283Element;
class LuaScriptEngine
{
public:
	Rva00336283Element *rva00337DEF(const AsciiString &events);
};
extern LuaScriptEngine *TheLuaScriptEngine;

#define X1_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define X1_SLOTS16(p) X1_SLOTS4(p##0) X1_SLOTS4(p##1) X1_SLOTS4(p##2) X1_SLOTS4(p##3)

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva0010F149Handle
{
	__forceinline Rva0010F149Handle() : referent(0) {}
	Rva0010F149Handle(const Rva0010F149Handle &r);
	~Rva0010F149Handle() { if (referent) referent->Release_Ref(); }
	OpaqueRefCounted *referent;
};
class Rva000A8C9B;
struct OpaqueRefElement4;

class AudioManager
{
public:
	X1_SLOTS16(a) X1_SLOTS16(b) X1_SLOTS16(c) X1_SLOTS16(d)
	X1_SLOTS4(e0) X1_SLOTS4(e1)
	virtual void slot72(); virtual void slot73();
	virtual void rva_slot74(OpaqueRefCounted *info);
};
extern AudioManager *TheAudio;

class ThingTemplate;
class Rva00279354Host
{
public:
	void rva00279797(const OpaqueRefElement4 &info);
};

class Drawable
{
public:
	X1_SLOTS4(a) X1_SLOTS4(b) X1_SLOTS4(c)
	virtual void slot12();
	virtual void rva_slot13();

	void rva00274176(Bool b);
	// Retail stores the new +0x200 instance scale, then refreshes through
	// 0x00274176(true); the old scale is read into its own temporary first.
	void setInstanceScale(Real f) { m_scale = f; rva00274176(true); }
	void rva002785FB(Bool b);
	void rva0027974B();
	void rva002781DA(Rva0010F149Handle info);

	ThingTemplate *m_template;
	char m_pad08[0x200 - 0x08];
	Real m_scale;
	char m_pad204[0x448 - 0x204];
	Bool m_448;
};

void rva00433796(Dict *properties, Drawable *draw, ThingTemplate *tmpl,
	Bool *forcedOff, Rva000A8C9B *info, Bool *enabled);

class Locomotor
{
public:
	char m_pad[0x3C];
	Real m_closeEnoughDist;
};

class AIUpdateInterface
{
public:
	void rva0026DE3B(Int attitude);
	char m_pad[0x1F0];
	Locomotor *m_curLocomotor;
	char m_pad1F4[0x3BE - 0x1F4];
	Bool m_isRecruitable;
};

class Rva002628B6DwordSlot
{
public:
	void set(Int value);
};

class StancesBehavior
{
public:
	void rva0045F084(Int stance);
};
NameKeyType Rva0045EE2CGet();

class HealthTarget
{
public:
	X1_SLOTS16(a) X1_SLOTS16(b) X1_SLOTS16(c) X1_SLOTS16(d)
	X1_SLOTS16(e) X1_SLOTS16(f)
	virtual void slot96(); virtual void slot97(); virtual void slot98();
	virtual void slot99(); virtual void slot100(); virtual void slot101();
	virtual void setInitialHealth(Int health);
};

class Module250
{
public:
	X1_SLOTS16(a) X1_SLOTS4(b0) X1_SLOTS4(b1) X1_SLOTS4(b2)
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual HealthTarget *slot31();
};

class BodyModuleInterface
{
public:
	X1_SLOTS16(a)
	X1_SLOTS4(b0)
	virtual void slot20();
	virtual void setInitialHealth(Real health, Int change);
	virtual void setMaxHealth(Real health, Int change);
	X1_SLOTS4(c0) X1_SLOTS4(c1)
	virtual void slot31(); virtual void slot32();
	virtual void setIndestructible(Bool indestructible);
};

class Rva00294759
{
public:
	void rva00294759(Int level);
};

class Module;

// The +0x10C model-condition word array; bitset-style accessors test and
// modify the word in memory.
class ModelConditionBits
{
public:
	UnsignedInt test(UnsignedInt i) const { return m_words[i >> 5] & (1U << (i & 0x1f)); }
	void set(UnsignedInt i) { m_words[i >> 5] |= 1U << (i & 0x1f); }
	void clear(UnsignedInt i) { m_words[i >> 5] &= ~(1U << (i & 0x1f)); }
private:
	UnsignedInt m_words[10];
};

class Object
{
public:
	void updateObjValuesFromMapProperties(Dict *properties);
	Bool isSelectable() const;
	void setSelectable(Bool selectable);
	void setScriptStatus(ObjectScriptStatusBit bit, Bool set);
	void rva00293077(const void *upgrade);
	void rva0028AE6D();

	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Drawable *getDrawable() const { return m_drawable; }
	__forceinline HealthTarget *getHealthTarget() const { return m_250 ? m_250->slot31() : 0; }
	__forceinline void setModelConditionBit(UnsignedInt bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionBit(UnsignedInt bit)
	{
		if (m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.clear(bit);
			rva0028AE6D();
		}
	}

protected:
	Module *findModule(NameKeyType key) const;

private:
	char m_pad00[0x84];
	Drawable *m_drawable;
	AsciiString m_name;
	char m_pad8C[0x10C - 0x8C];
	ModelConditionBits m_modelConditionFlags;
	char m_pad134[0x1B0 - 0x134];
	Real m_visionRange;
	Real m_shroudClearingRange;
	char m_pad1B8[0x250 - 0x1B8];
	Module250 *m_250;
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
};

enum
{
	MODELCONDITION_NIGHT_BIT = 7,
	MODELCONDITION_SNOW_BIT = 8
};

void Object::updateObjValuesFromMapProperties(Dict *properties)
{
	Bool exists;

	AsciiString valStr;
	Bool valBool = false;
	Int valInt = 0;
	Real valReal = 0.0f;

	valStr = properties->getAsciiString(TheKey_objectName.get(), &exists);
	if (exists)
		m_name = valStr;

	valInt = properties->getInt(TheKey_objectMaxHPs.get(), &exists);
	if (exists && valInt >= 0)
	{
		BodyModuleInterface *body = getBodyModule();
		if (body)
			body->setMaxHealth((Real)valInt, 0);
	}

	HealthTarget *healthTarget = getHealthTarget();
	if (healthTarget)
	{
		healthTarget->setInitialHealth(properties->getInt(TheKey_objectInitialHealth.get(), &exists));
	}
	else
	{
		valInt = properties->getInt(TheKey_objectInitialHealth.get(), &exists);
		if (exists)
		{
			BodyModuleInterface *body = getBodyModule();
			if (body)
				body->setInitialHealth((Real)valInt, 0);
		}
	}

	valInt = properties->getInt(TheKey_objectExperienceLevel.get(), &exists);
	if (exists)
		reinterpret_cast<Rva00294759 *>(this)->rva00294759(valInt);

	valInt = properties->getInt(TheKey_objectAggressiveness.get(), &exists);
	if (exists)
	{
		AIUpdateInterface *ai = getAIUpdateInterface();
		if (ai)
			ai->rva0026DE3B(valInt);
	}

	valInt = properties->getInt(TheKey_objectInitialStance.get(), &exists);
	if (exists)
	{
		StancesBehavior *stances = reinterpret_cast<StancesBehavior *>(findModule(Rva0045EE2CGet()));
		if (stances)
			stances->rva0045F084(valInt);
	}

	valBool = properties->getBool(TheKey_objectRecruitableAI.get(), &exists);
	if (exists)
	{
		if (getAIUpdateInterface())
			getAIUpdateInterface()->m_isRecruitable = valBool;
	}

	valBool = properties->getBool(TheKey_objectSelectable.get(), &exists);
	if (exists)
	{
		if (valBool != isSelectable())
			setSelectable(valBool);
	}

	valReal = properties->getReal(TheKey_objectStoppingDistance.get(), &exists);
	if (exists && valReal >= 0.5f)
	{
		if (getAIUpdateInterface() && getAIUpdateInterface()->m_curLocomotor)
		{
			Locomotor *loco = getAIUpdateInterface()->m_curLocomotor;
			loco->m_closeEnoughDist = valReal;
		}
	}

	valBool = properties->getBool(TheKey_objectEnabled.get(), &exists);
	if (exists)
		setScriptStatus(OBJECT_STATUS_SCRIPT_DISABLED, !valBool);

	valBool = properties->getBool(TheKey_objectPowered.get(), &exists);
	if (exists)
		setScriptStatus(OBJECT_STATUS_SCRIPT_UNPOWERED, !valBool);

	valBool = properties->getBool(TheKey_objectIndestructible.get(), &exists);
	if (exists)
	{
		BodyModuleInterface *body = getBodyModule();
		if (body)
			body->setIndestructible(valBool);
	}

	valBool = properties->getBool(TheKey_objectUnsellable.get(), &exists);
	if (exists)
		setScriptStatus(OBJECT_STATUS_SCRIPT_UNSELLABLE, valBool);

	valBool = properties->getBool(TheKey_objectTargetable.get(), &exists);
	if (exists)
	{
		setScriptStatus(OBJECT_STATUS_SCRIPT_TARGETABLE, valBool);
		if (getDrawable())
			getDrawable()->rva_slot13();
	}

	valInt = properties->getInt(TheKey_objectVisualRange.get(), &exists);
	if (exists)
	{
		if (valInt < 0)
			valInt = 0;
		m_visionRange = (Real)valInt;
	}

	valInt = properties->getInt(TheKey_objectShroudClearingDistance.get(), &exists);
	if (exists)
	{
		if (valInt < 0)
			valInt = 0;
		m_shroudClearingRange = (Real)valInt;
	}

	Int upgradeNum = 0;
	do
	{
		AsciiString keyName;
		keyName.format("%s%d", TheNameKeyGenerator->keyToName(TheKey_objectGrantUpgrade.get()).str(), upgradeNum);
		valStr = properties->getAsciiString(TheNameKeyGenerator->nameToKey(keyName), &exists);
		if (exists)
		{
			const UpgradeTemplate *ut = TheUpgradeCenter->findUpgrade(valStr);
			if (ut)
				rva00293077(ut);
		}
		else
		{
			valStr.clear();
		}
		++upgradeNum;
	} while (!valStr.isEmpty());

	Drawable *drawable = getDrawable();
	if (drawable)
	{
		Real scale = properties->getReal(TheKey_objectPrototypeScale.get(), &exists);
		if (exists && scale != 1.0f)
		{
			Real oldScale = drawable->m_scale;
			drawable->setInstanceScale(oldScale * scale);
		}

		valInt = properties->getInt(TheKey_objectTime.get(), &exists);
		if (exists)
		{
			switch (valInt)
			{
			case 1:
				clearModelConditionBit(MODELCONDITION_NIGHT_BIT);
				break;
			case 2:
				setModelConditionBit(MODELCONDITION_NIGHT_BIT);
				break;
			}
		}

		valInt = properties->getInt(TheKey_objectWeather.get(), &exists);
		if (exists)
		{
			switch (valInt)
			{
			case 1:
				clearModelConditionBit(MODELCONDITION_SNOW_BIT);
				break;
			case 2:
				setModelConditionBit(MODELCONDITION_SNOW_BIT);
				break;
			}
		}

		valStr = properties->getAsciiString(TheKey_objectEventsList.get(), &exists);
		if (exists && !valStr.isEmpty())
		{
			Rva002628B6DwordSlot *ai = reinterpret_cast<Rva002628B6DwordSlot *>(getAIUpdateInterface());
			Rva00336283Element *events = TheLuaScriptEngine->rva00337DEF(valStr);
			if (ai)
				ai->set(reinterpret_cast<Int>(events));
		}

		Bool forcedOff = false;
		Bool enabled = false;
		Rva0010F149Handle info;
		ThingTemplate *tmpl = drawable->m_template;
		rva00433796(properties, drawable, tmpl, &forcedOff,
			reinterpret_cast<Rva000A8C9B *>(&info), &enabled);
		if (forcedOff)
		{
			drawable->rva0027974B();
		}
		else
		{
			if (!enabled)
				drawable->rva002785FB(false);
			if (info.referent)
			{
				drawable->rva002781DA(info);
				TheAudio->rva_slot74(info.referent);
				reinterpret_cast<Rva00279354Host *>(drawable)->rva00279797(
					*reinterpret_cast<const OpaqueRefElement4 *>(&info));
			}
			if (enabled && !drawable->m_448)
				drawable->rva002785FB(true);
		}
	}
}
