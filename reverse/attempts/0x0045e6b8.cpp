// ?onDie@SlowDeathBehavior@@UAEXPBVDamageInfo@@@Z
// partial score=0.99 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
//
// ?update@SlowDeathBehavior@@UAE?AW4UpdateSleepTime@@XZ @0x0045DB0B 858B
// Identity: SlowDeathBehavior::update, the UpdateModuleInterface override
// (this is the +0x10 subobject; moduleData at -0x0C, object at -0x08). It
// sits in the retail SlowDeathBehavior.cpp block between the rowed
// calcRandomForce 0x0045D636 and the ModuleData ctor 0x0045E386, calls the
// phase helper 0x0045D97A with phases 3, 1 and 2 on the full object, and
// follows the Zero Hour update statement for statement. Donor for the BFME
// additions is BFME 1's SlowDeathBehaviorUpdate.cpp (retail 0x00208A50):
// timescale rescaling of a fourth (+0x34) and fifth (+0x4C) frame, the
// landing phase gated by the +0x40 flag the rowed ctor 0x0045D4B4 sets from
// the phase-3 effect lists, the drawable fade at the +0x4C frame (sentinel
// 0xFACADE00) and the terrain-clamped sink. BFME2 deltas read from retail:
// the slow-death scale lives at TheGameLODManager +0x179C; the frame is
// TheGameLogic +0x40; the fade length is ModuleData +0x184 scaled by the int
// at TheGameEngine +0x38; the sink holds the object only when its physics
// (Object +0x25C, rowed 0x0039051E) is not set, status bit 3 of +0x1C8 is
// clear and it is not significantly above terrain, then sets status 0x38;
// BFME 1's shadow and module notifications are gone. Model condition flags
// are the 19-word mask at Object +0x10C (bits 5, 120, 121, 153).
//
// ?doPhaseStuff@SlowDeathBehavior@@IAEXW4SlowDeathPhaseType@@@Z @0x0045D97A 401B
// Identity: the phase helper update calls above, ZH doPhaseStuff plus BFME 1's
// per-phase sound (SlowDeathBehavior_doPhaseStuff_Thunk.cpp, 0x002080B0):
// four 12-byte STLport vectors per phase at ModuleData +0x58 (FX, client
// random), +0x88 (OCL, logic random), +0xB8 (weapons, logic random) and
// +0xE8 (sound handles, client random), gated by the loaded-effects mask at
// +0x18C. Lines 531/541/551/564 are the retail random-value call sites. The
// sound plays through the rowed native audio event ctor 0x002DA461 with the
// object ID (+0x74) and TheAudio slot 25. Real STLport vectors give retail's
// register choice for the weapon and sound picks.
//
// ?beginSlowDeath@SlowDeathBehavior@@UAEXPBVDamageInfo@@@Z @0x0045DE65 1070B
// Identity: slot 0 of the SlowDeathBehaviorInterface vtable 0xC42020 (this
// is the +0x24 subobject; moduleData -0x20, object -0x1C), ends in the
// rowed doPhaseStuff(SDPHASE_INITIAL) and follows ZH beginSlowDeath with the
// BFME 1 additions from SlowDeathBehavior_beginSlowDeath.cpp (retail
// 0x00209BB0): clear condition 37, store the rowed 0x0028B875 result at
// +0x44, apply the ModuleData status mask (+0x174, rowed _M_is_any) and
// condition mask (+0x128, rowed 0x000B3EB3 and pinned 0x001E431E, then set
// condition 62), drop shadows unless +0x18D, the drawable 0.0f/-0.2f fade
// target, the dying frame (+0x54 delay) and fade frame (+0x188 delay,
// sentinel 0xFACADE00), and the landing wake. BFME2 deltas read from retail:
// the hulk override is TheGameLogic +0xA0 with frames from the logic frame
// rate int 0x009BA4E4; KINDOF bit 82 of the template mask at +0x108; the
// fling path feeds the force to the physics consumer 0x003909FA, faces the
// object with atan2f and Thing::setOrientation and sets condition 120 on the
// object. Lines 420/421/423 are the retail random-value call sites. EH:
// FuncInfo states 0 and 1 have no action and no code, state 2 guards the
// SlavedUpdate key; the two empty states are modelled as in the BFME 1
// donor by two lifetimes in a branch the optimizer removes.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include <vector>

enum ObjectID
{
	INVALID_ID = 0
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
int GetGameClientRandomValue(int lo, int hi, char *file, int line);
// Retail source line numbers are passed explicitly.
#define GameLogicRandomValue(lo, hi, line) GetGameLogicRandomValue(lo, hi, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\SlowDeathBehavior.cpp", line)
#define GameClientRandomValue(lo, hi, line) GetGameClientRandomValue(lo, hi, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\SlowDeathBehavior.cpp", line)

class ModuleData;
class Object;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class ObjectCreationList
{
public:
	void create(void *primary, void *secondary, void *lifetime);
	static void create(const ObjectCreationList *ocl, Object *primary, Object *secondary)
	{
		if (ocl)
			((ObjectCreationList *)ocl)->create(primary, secondary, 0);
	}
};

class WeaponTemplate;
class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos);
};
extern WeaponStore *TheWeaponStore;

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
	AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
	AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23)
	AUDIO_SLOT(24)
#undef AUDIO_SLOT
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
};
extern AudioManager *TheAudio;

// One refcounted audio-event-info handle; the copy is the rowed 0x000A8C7C.
class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str()
	{
		if (m_item)
			m_item->Release_Ref();
	}
	OpaqueRefCounted *m_item;
};

class Drawable
{
public:
	void fadeOut(UnsignedInt frames);
	void rva00272A02(Bool enable);
};

// The two-float drawable setter the slow death starts with (0.0f, -0.2f).
class Rva00270644
{
public:
	void rva00270644(Real a, Real b);
};

class PhysicsBehavior;
// The +0x25C physics consumer that takes the fling force.
class Rva003909FAObj
{
public:
	void consume(void *force, int a, int b);
};

namespace _STL
{
template <unsigned N> struct _Base_bitset;
template <> struct _Base_bitset<4>
{
	unsigned long _M_w[4];
	bool _M_is_any() const;
};
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

extern "C" float __cdecl atan2f(float y, float x);
void calcRandomForceRva0045D636(Real minMag, Real maxMag, Real minPitch, Real maxPitch, Coord3D *force);
// Logic frames per second.
extern int g_Va00DBA4E4;

enum KindOfType
{
	KINDOF_HULK = 82
};
class ThingTemplate
{
public:
	unsigned int isKindOf(KindOfType t) const
	{
		return m_kindOf[t >> 5] & (1U << (t & 0x1f));
	}
	Bool isSelectableWhenDead() const { return m_byte632 != 0; }

private:
	unsigned char m_pad00[0x108];
	unsigned int m_kindOf[4]; // +0x108
	unsigned char m_pad118[0x632 - 0x118];
	unsigned char m_byte632; // +0x632
};

class AIUpdateInterface
{
public:
	Bool isAiInDeadState() const { return m_isAiDead; }
	void markAsDead();

private:
	unsigned char m_pad00[0x3BD];
	Bool m_isAiDead; // +0x3BD
};

class BodyModuleInterface
{
public:
	virtual void bodySlot00();
	virtual void bodySlot01();
	virtual void bodySlot02();
	virtual void bodySlot03();
	virtual void bodySlot04();
	virtual void bodySlot05();
	virtual Real getMaxHealth() const;
};

class DamageInfo
{
public:
	unsigned char m_pad00[0x70];
	Real m_actualDamageDealt; // +0x70
	Real m_actualDamageClipped; // +0x74
};

class BehaviorModule;

class PhysicsBehavior
{
public:
	Bool rva0039051E() const;
};

enum DisabledType
{
	DISABLED_HELD = 3
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_SLOW_DEATH_SINKING = 0x38
};

struct Rva0028F59A
{
	unsigned m_bits[19];
	Rva0028F59A(int unused, int bit);
};

enum ModelConditionFlagType
{
	MODELCONDITION_SLOW_DEATH_FALLING = 5,
	MODELCONDITION_BIT37 = 37,
	MODELCONDITION_BIT62 = 62,
	MODELCONDITION_EXPLODED_FLAILING = 120,
	MODELCONDITION_EXPLODED_BOUNCING = 121,
	MODELCONDITION_DYING = 153
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
	Bool rva000B3EB3() const;

private:
	unsigned int m_words[19];
};

class Thing
{
public:
	Bool isAboveTerrain() const;
	Real getHeightAboveTerrain() const;
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
	Drawable *getDrawable() const;
};

class Module;

class Object : public Thing
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	PhysicsBehavior *getPhysics() const { return m_physics; }
	unsigned int isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	const ThingTemplate *getTemplate() const { return m_template; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	BehaviorModule **getBehaviorModules() const { return m_behaviorModules; }
	void setSelectable(Bool selectable);
	Bool isSignificantlyAboveTerrain() const;
	void setDisabled(DisabledType type);
	void setStatus(ObjectStatusTypes status, Bool set);
	Int rva0028B511() const;
	void rva0028CFB2(const int *clr, const int *set);
	void rva0028AE6D();
	Int rva0028B875() const;
	void rva0028CDEB(const _STL::_Base_bitset<4> *mask, Bool set);
	void rva001E431E(const int *mask);
	__forceinline void clearModelConditionState(ModelConditionFlagType flag)
	{
		if (m_modelConditionFlags.test(flag) != 0)
		{
			m_modelConditionFlags.clear(flag);
			rva0028AE6D();
		}
	}
	__forceinline void setModelConditionState(ModelConditionFlagType flag)
	{
		if (m_modelConditionFlags.test(flag) == 0)
		{
			m_modelConditionFlags.set(flag);
			rva0028AE6D();
		}
	}
	UnsignedInt getStatusBits() const { return m_status; }

protected:
	friend class SlowDeathBehavior;
	Module *findModule(NameKeyType key) const;

private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x1C8 - 0x158];
	UnsignedInt m_status; // +0x1C8
	unsigned char m_pad1CC[0x244 - 0x1CC];
	BehaviorModule **m_behaviorModules; // +0x244
	unsigned char m_pad248[0x254 - 0x248];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	PhysicsBehavior *m_physics; // +0x25C
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
	void deselectObject(Object *obj, UnsignedInt playerMask, Bool affectClient);
	UnsignedInt getFrame() const { return m_frame; }
	Int getHulkMaxLifetimeOverride() const { return m_hulkMaxLifetimeOverride; }

private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
	unsigned char m_pad44[0xA0 - 0x44];
	Int m_hulkMaxLifetimeOverride; // +0xA0
};
extern GameLogic *TheGameLogic;

class GameLODManager
{
public:
	Real getSlowDeathScale() const { return m_slowDeathScale; }

private:
	unsigned char m_pad00[0x179C];
	Real m_slowDeathScale; // +0x179C
};
extern GameLODManager *TheGameLODManager;

class GameEngine
{
public:
	Int getFramesPerSecondLimit() const { return m_maxFPS; }

private:
	unsigned char m_pad00[0x38];
	Int m_maxFPS; // +0x38
};
extern GameEngine *TheGameEngine;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual Real getLayerHeight(Real x, Real y, Int layer, Coord3D *normal, Bool clip);
};
extern TerrainLogic *TheTerrainLogic;

class SlowDeathBehaviorModuleData
{
public:
	Bool hasNonLodEffects() const { return (m_maskOfLoadedEffects & 6) != 0; }

	unsigned char m_pad00[0x38];
	Real m_sinkRate; // +0x38
	Int m_probabilityModifier; // +0x3C
	Real m_modifierBonusPerOverkillPercent; // +0x40
	UnsignedInt m_sinkDelay; // +0x44
	UnsignedInt m_sinkDelayVariance; // +0x48
	UnsignedInt m_destructionDelay; // +0x4C
	UnsignedInt m_destructionDelayVariance; // +0x50
	UnsignedInt m_dyingDelay; // +0x54
	std::vector<const FXList *> m_fx[4]; // +0x58
	std::vector<const ObjectCreationList *> m_ocls[4]; // +0x88
	std::vector<const WeaponTemplate *> m_weapons[4]; // +0xB8
	std::vector<Rva0036CA00Str> m_sounds[4]; // +0xE8
	Real m_flingForce; // +0x118
	Real m_flingForceVariance; // +0x11C
	Real m_flingPitch; // +0x120
	Real m_flingPitchVariance; // +0x124
	ModelConditionFlags m_modelConditionMask; // +0x128
	_STL::_Base_bitset<4> m_statusMask; // +0x174
	UnsignedInt m_fadeTime; // +0x184
	UnsignedInt m_fadeDelay; // +0x188
	unsigned char m_maskOfLoadedEffects; // +0x18C
	Bool m_keepShadows; // +0x18D
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
	Object *getObject() const { return m_object; }

protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class SlowDeathBehaviorInterface;
class BehaviorModuleInterface
{
public:
#define BMI_SLOT(n) virtual void behaviorModuleInterfaceSlot##n();
	BMI_SLOT(00) BMI_SLOT(01) BMI_SLOT(02) BMI_SLOT(03) BMI_SLOT(04) BMI_SLOT(05)
	BMI_SLOT(06) BMI_SLOT(07) BMI_SLOT(08) BMI_SLOT(09) BMI_SLOT(10) BMI_SLOT(11)
	BMI_SLOT(12) BMI_SLOT(13) BMI_SLOT(14) BMI_SLOT(15) BMI_SLOT(16) BMI_SLOT(17)
	BMI_SLOT(18) BMI_SLOT(19) BMI_SLOT(20) BMI_SLOT(21) BMI_SLOT(22)
#undef BMI_SLOT
	virtual SlowDeathBehaviorInterface *getSlowDeathBehaviorInterface();
};
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

private:
	unsigned char m_pad14[0x20 - 0x14];
};

class DamageInfo;
class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};
class SlowDeathBehaviorInterface
{
public:
	virtual void beginSlowDeath(const DamageInfo *damageInfo) = 0;
	virtual Int getProbabilityModifier(const DamageInfo *damageInfo) const = 0;
	virtual Bool isDieApplicable(const DamageInfo *damageInfo) const = 0;
	// Slot 3: the folded constant-true predicate 0x0050B5C6 in this vtable.
	virtual Bool rva0050B5C6() const = 0;
};

class SlavedUpdateInterface
{
public:
	virtual ObjectID getSlaverID() const = 0;
	virtual void onEnslave(const Object *slaver) = 0;
	virtual void onSlaverDie(const DamageInfo *info) = 0;
};
class SlavedUpdate : public UpdateModule, public SlavedUpdateInterface
{
};

// Retail unwind states 0 and 1 of beginSlowDeath are two class-typed
// lifetimes in a scope the optimizer deleted (no code, no cleanup action);
// only their count is recoverable.
struct Rva0045DE65EliminatedLifetime
{
	~Rva0045DE65EliminatedLifetime();
};
void rva0045de65EliminatedSink(const void *, const void *);

enum SlowDeathPhaseType
{
	SDPHASE_INITIAL = 0,
	SDPHASE_MIDPOINT = 1,
	SDPHASE_FINAL = 2,
	SDPHASE_LANDED = 3
};

class SlowDeathBehavior : public UpdateModule, public DieModuleInterface, public SlowDeathBehaviorInterface
{
public:
	virtual UpdateSleepTime update();
	virtual void beginSlowDeath(const DamageInfo *damageInfo);
	virtual Int getProbabilityModifier(const DamageInfo *damageInfo) const;
	virtual void onDie(const DamageInfo *damageInfo);
	const SlowDeathBehaviorModuleData *getSlowDeathBehaviorModuleData() const
	{
		return (const SlowDeathBehaviorModuleData *)m_moduleData;
	}

protected:
	void doPhaseStuff(SlowDeathPhaseType sdphase);

private:
	enum
	{
		SLOW_DEATH_ACTIVATED = 0,
		MIDPOINT_EXECUTED = 1,
		FLUNG_INTO_AIR = 2,
		BOUNCED = 3
	};
	UnsignedInt m_sinkFrame; // +0x28
	UnsignedInt m_midpointFrame; // +0x2C
	UnsignedInt m_destructionFrame; // +0x30
	UnsignedInt m_dyingFrame; // +0x34
	Real m_acceleratedTimeScale; // +0x38
	UnsignedInt m_flags; // +0x3C
	Bool m_needsLanding; // +0x40
	Int m_44; // +0x44
	Bool m_fadeStarted; // +0x48
	UnsignedInt m_fadeFrame; // +0x4C
};

void SlowDeathBehavior::doPhaseStuff(SlowDeathPhaseType sdphase)
{
	const SlowDeathBehaviorModuleData *d = getSlowDeathBehaviorModuleData();
	Int idx, listSize;

	if (!d->m_maskOfLoadedEffects)
		return;

	listSize = d->m_fx[sdphase].size();
	if (listSize > 0)
	{
		idx = GameClientRandomValue(0, listSize - 1, 531);
		const FXList *fxl = d->m_fx[sdphase][idx];
		FXList::doFXObj(fxl, getObject(), 0);
	}

	listSize = d->m_ocls[sdphase].size();
	if (listSize > 0)
	{
		idx = GameLogicRandomValue(0, listSize - 1, 541);
		const ObjectCreationList *ocl = d->m_ocls[sdphase][idx];
		ObjectCreationList::create(ocl, getObject(), 0);
	}

	listSize = d->m_weapons[sdphase].size();
	if (listSize > 0)
	{
		idx = GameLogicRandomValue(0, listSize - 1, 551);
		const WeaponTemplate *wt = d->m_weapons[sdphase][idx];
		if (wt)
			TheWeaponStore->createAndFireTempWeapon(wt, getObject(), getObject()->getPosition());
	}

	listSize = d->m_sounds[sdphase].size();
	if (listSize > 0)
	{
		idx = GameClientRandomValue(0, listSize - 1, 564);
		Rva0036CA00Str sound = d->m_sounds[sdphase][idx];
		if (sound.m_item && TheAudio)
		{
			BfmeAudioEventPrefix136 event((const OpaqueRefElement4 &)sound, getObject()->getID());
			TheAudio->addAudioEvent(&event);
		}
	}
}

UpdateSleepTime SlowDeathBehavior::update()
{
	const SlowDeathBehaviorModuleData *d = getSlowDeathBehaviorModuleData();
	Object *obj = getObject();
	if (!obj)
		return UPDATE_SLEEP_FOREVER;

	Real timeScale = TheGameLODManager->getSlowDeathScale();

	if (timeScale != 1.0f && m_acceleratedTimeScale == 1.0f && !d->hasNonLodEffects())
	{
		if (timeScale == 0)
		{
			TheGameLogic->destroyObject(obj);
			return UPDATE_SLEEP_NONE;
		}

		m_sinkFrame = (Real)m_sinkFrame * timeScale;
		m_midpointFrame = (Real)m_midpointFrame * timeScale;
		m_destructionFrame = (Real)m_destructionFrame * timeScale;
		m_dyingFrame = (Real)m_dyingFrame * timeScale;
		m_acceleratedTimeScale = timeScale;
		m_fadeFrame = (Real)m_fadeFrame * timeScale;
	}

	UnsignedInt now = TheGameLogic->getFrame();

	if ((m_flags & (1 << FLUNG_INTO_AIR)) != 0 && (m_flags & (1 << BOUNCED)) == 0)
	{
		++m_sinkFrame;
		++m_midpointFrame;
		++m_destructionFrame;
		++m_fadeFrame;
		if (m_dyingFrame)
			++m_dyingFrame;
		if (!obj->isAboveTerrain())
		{
			obj->rva0028CFB2((const int *)&Rva0028F59A(0, MODELCONDITION_EXPLODED_FLAILING), (const int *)&Rva0028F59A(0, MODELCONDITION_EXPLODED_BOUNCING));
			m_flags |= (1 << BOUNCED);
		}
	}

	if (m_needsLanding)
	{
		obj->clearModelConditionState(MODELCONDITION_SLOW_DEATH_FALLING);
		if (obj->getHeightAboveTerrain() < 1.0f)
		{
			m_needsLanding = false;
			doPhaseStuff(SDPHASE_LANDED);
			obj->setModelConditionState(MODELCONDITION_SLOW_DEATH_FALLING);
		}
	}

	Drawable *drawable = obj->getDrawable();
	if (drawable && now >= m_fadeFrame && d->m_fadeDelay != 0xFACADE00 && !m_fadeStarted)
	{
		m_fadeStarted = true;
		drawable->fadeOut((Real)TheGameEngine->getFramesPerSecondLimit() * d->m_fadeTime);
	}

	if (now >= m_sinkFrame && d->m_sinkRate > 0.0f)
	{
		PhysicsBehavior *phys = obj->getPhysics();
		if (!(phys && phys->rva0039051E()) && !(obj->getStatusBits() & 8) && !obj->isSignificantlyAboveTerrain())
			obj->setDisabled(DISABLED_HELD);
		obj->setStatus(OBJECT_STATUS_SLOW_DEATH_SINKING, true);
		Coord3D pos;
		pos.x = obj->getPosition()->x;
		pos.y = obj->getPosition()->y;
		pos.z = obj->getPosition()->z;
		pos.z -= d->m_sinkRate / m_acceleratedTimeScale;
		if (TheTerrainLogic->getLayerHeight(pos.x, pos.y, obj->rva0028B511(), 0, true) < pos.z)
			pos.z -= 5.7f;
		obj->setPosition(&pos);
	}

	if (now >= m_midpointFrame && (m_flags & (1 << MIDPOINT_EXECUTED)) == 0)
	{
		doPhaseStuff(SDPHASE_MIDPOINT);
		m_flags |= (1 << MIDPOINT_EXECUTED);
	}

	if (now >= m_destructionFrame)
	{
		doPhaseStuff(SDPHASE_FINAL);
		TheGameLogic->destroyObject(obj);
	}

	if (m_dyingFrame && now >= m_dyingFrame)
		obj->setModelConditionState(MODELCONDITION_DYING);

	return UPDATE_SLEEP_NONE;
}

void SlowDeathBehavior::beginSlowDeath(const DamageInfo *damageInfo)
{
	if ((m_flags & (1 << SLOW_DEATH_ACTIVATED)) == 0)
	{
		const SlowDeathBehaviorModuleData *d = getSlowDeathBehaviorModuleData();
		Object *obj = getObject();
		if (!obj)
			return;

		obj->clearModelConditionState(MODELCONDITION_BIT37);
		m_44 = obj->rva0028B875();
		if (d->m_statusMask._M_is_any())
			obj->rva0028CDEB(&d->m_statusMask, true);

		Drawable *draw = obj->getDrawable();
		if (d->m_modelConditionMask.rva000B3EB3())
		{
			obj->rva001E431E((const int *)&d->m_modelConditionMask);
			obj->setModelConditionState(MODELCONDITION_BIT62);
		}
		if (draw)
		{
			if (!d->m_keepShadows)
				obj->getDrawable()->rva00272A02(false);
			((Rva00270644 *)draw)->rva00270644(0.0f, -0.2f);
		}

		Real timeScale = TheGameLODManager->getSlowDeathScale();
		m_acceleratedTimeScale = 1.0f;

		if (timeScale == 0.0f && !d->hasNonLodEffects())
		{
			TheGameLogic->destroyObject(obj);
			return;
		}

		if (getObject()->isKindOf(KINDOF_HULK) && TheGameLogic->getHulkMaxLifetimeOverride() != -1)
		{
			m_sinkFrame = 1;
			m_midpointFrame = (g_Va00DBA4E4 / 2) + 1;
			m_destructionFrame = g_Va00DBA4E4 + 1;
			m_acceleratedTimeScale = 1.0f;
		}
		else
		{
			m_sinkFrame = timeScale * (d->m_sinkDelay + GameLogicRandomValue(0, d->m_sinkDelayVariance, 420));
			m_destructionFrame = timeScale * (d->m_destructionDelay + GameLogicRandomValue(0, d->m_destructionDelayVariance, 421));
			m_dyingFrame = timeScale * d->m_dyingDelay;
			m_midpointFrame = GameLogicRandomValue(0.35f * m_destructionFrame, 0.65f * m_destructionFrame, 423);
			m_acceleratedTimeScale = timeScale;
		}

		if (d->m_fadeDelay != 0xFACADE00)
			m_fadeFrame = timeScale * d->m_fadeDelay;

		UnsignedInt now = TheGameLogic->getFrame();

		if (d->m_flingForce > 0)
		{
			if (0)
			{
				Rva0045DE65EliminatedLifetime eliminated0;
				Rva0045DE65EliminatedLifetime eliminated1;
				rva0045de65EliminatedSink(&eliminated0, &eliminated1);
			}

			if (obj->getStatusBits() & 8)
			{
				static NameKeyType key_SlavedUpdate = TheNameKeyGenerator->nameToKey("SlavedUpdate");
				SlavedUpdate *slave = (SlavedUpdate *)obj->findModule(key_SlavedUpdate);
				if (slave)
					slave->onSlaverDie(0);
			}

			PhysicsBehavior *physics = obj->getPhysics();
			if (physics)
			{
				const Real MIN_ALTITUDE = 1.0f;
				if (obj->getHeightAboveTerrain() < MIN_ALTITUDE)
				{
					Coord3D pos;
					pos.x = obj->getPosition()->x;
					pos.y = obj->getPosition()->y;
					pos.z = obj->getPosition()->z;
					pos.z += MIN_ALTITUDE;
					obj->setPosition(&pos);
				}

				Coord3D force;
				calcRandomForceRva0045D636(d->m_flingForce, d->m_flingForce + d->m_flingForceVariance,
					d->m_flingPitch, d->m_flingPitch + d->m_flingPitchVariance, &force);
				((Rva003909FAObj *)physics)->consume(&force, 0, 0);
				Real orientation = atan2f(force.y, force.x);
				obj->setOrientation(orientation);
				obj->setModelConditionState(MODELCONDITION_EXPLODED_FLAILING);
				m_flags |= (1 << FLUNG_INTO_AIR);
			}
			setWakeFrame(obj, UPDATE_SLEEP_NONE);
		}
		else if (m_needsLanding)
		{
			setWakeFrame(obj, UPDATE_SLEEP_NONE);
		}
		else
		{
			UnsignedInt whenToWakeTime = m_sinkFrame;
			if (whenToWakeTime > m_destructionFrame)
				whenToWakeTime = m_destructionFrame;
			if (whenToWakeTime > m_midpointFrame)
				whenToWakeTime = m_midpointFrame;
			if (m_dyingFrame && whenToWakeTime > m_dyingFrame)
				whenToWakeTime = m_dyingFrame;
			setWakeFrame(obj, (UpdateSleepTime)whenToWakeTime);
		}

		m_sinkFrame += now;
		m_destructionFrame += now;
		m_midpointFrame += now;
		if (m_dyingFrame)
			m_dyingFrame += now;
		m_fadeFrame += now;

		m_flags |= (1 << SLOW_DEATH_ACTIVATED);

		doPhaseStuff(SDPHASE_INITIAL);
	}
}

// ZH max(x,y) is ((x)>(y)) ? (x) : (y); retail compares through reference temporaries.
template <class T> inline const T &sdbMax(const T &a, const T &b) { return a > b ? a : b; }

Int SlowDeathBehavior::getProbabilityModifier(const DamageInfo *damageInfo) const
{
	Int overkillDamage = damageInfo->m_actualDamageDealt - damageInfo->m_actualDamageClipped;
	Real overkillPercent = (Real)overkillDamage / getObject()->getBodyModule()->getMaxHealth();
	Int overkillModifier = overkillPercent * getSlowDeathBehaviorModuleData()->m_modifierBonusPerOverkillPercent;

	return sdbMax(getSlowDeathBehaviorModuleData()->m_probabilityModifier + overkillModifier, 1);
}

void SlowDeathBehavior::onDie(const DamageInfo *damageInfo)
{
	if (!isDieApplicable(damageInfo))
		return;

	AIUpdateInterface *ai = getObject()->getAIUpdateInterface();
	if (ai)
	{
		if (ai->isAiInDeadState())
			return;
		ai->markAsDead();
	}

	TheGameLogic->deselectObject(getObject(), 0xFFFFF, true);

	const ThingTemplate *tmpl = getObject()->getTemplate();
	if (tmpl && !tmpl->isSelectableWhenDead())
		getObject()->setSelectable(false);

	Int total = 0;
	std::vector<Int> probabilities;
	std::vector<SlowDeathBehaviorInterface *> behaviors;
	for (BehaviorModule **update = getObject()->getBehaviorModules(); *update; ++update)
	{
		SlowDeathBehaviorInterface *sdu = (*update)->getSlowDeathBehaviorInterface();
		if (sdu != 0 && sdu->isDieApplicable(damageInfo))
		{
			Int probability = sdu->getProbabilityModifier(damageInfo);
			total += probability;
			probabilities.push_back(probability);
			behaviors.push_back(sdu);
		}
	}

	while (!behaviors.empty())
	{
		Int roll = GameLogicRandomValue(0, total - 1, 811);
		std::vector<Int>::iterator it = probabilities.begin();
		for (; it != probabilities.end(); ++it)
		{
			if (roll < *it)
				break;
			roll -= *it;
		}
		total -= *it;
		Int index = it - probabilities.begin();

		SlowDeathBehaviorInterface *sdu = behaviors[index];
		if (sdu && sdu->isDieApplicable(damageInfo) && sdu->rva0050B5C6())
		{
			sdu->beginSlowDeath(damageInfo);
			return;
		}

		behaviors[index] = behaviors.back();
		behaviors.pop_back();
		probabilities[index] = probabilities.back();
		probabilities.pop_back();
	}
}
