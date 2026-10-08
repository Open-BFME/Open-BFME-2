// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.18 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
//
// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
// Target identity: slot 0 of RampageBehavior's UpdateModuleInterface table
// (secondary vtable at 0x00C40DA8); the callback's this pointer is the
// interface subobject at complete-object +0x10. The target reads module data
// from this-0x0C and Object from this-0x08. The vtable owner and module-data
// layout are independently established by the rowed constructor and data
// constructor.
//
// Reference evidence: GeneralsMD AIRampageStateUpdate/OnEnter establish the
// rampage state purpose and frame-timer behavior. This BFME2 method is not a
// donor-body match: its upgrade gate, health ratio, weapon commands, condition
// bits and timer fields are reconstructed from this body's calls and offsets.
// Names for the two BodyModuleInterface float slots and Object condition bits
// remain address-derived; the target calls below use only rowed helpers.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum WeaponSetType
{
	WEAPONSET_7 = 7,
	WEAPONSET_8 = 8
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Thing;
class ModuleData;
class Object;
class UpgradeTemplate;
class AsciiString;

class Drawable
{
public:
	void rva00274176(Bool force);
};

class ObjectModuleBase
{
public:
	virtual void objectModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class BehaviorModule : public ObjectModuleBase, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

private:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	UnsignedInt m_updateState;
};

class RampageBehaviorModuleDataView
{
public:
	unsigned char m_pad00[8];
	const unsigned char *m_requiredUpgradeStart;
	const unsigned char *m_requiredUpgradeFinish;
	const unsigned char *m_requiredUpgradeEnd;
	float m_healthThreshold;
	Int m_lifeTimer;
	Int m_angryLifeTimer;
	Int m_resetTimer;
	float m_enemyCheckRange;
	Int m_enemyThreshold;
};

class BodyModuleFloatInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual float rva0048F64EGetA();
	virtual void slot14();
	virtual float rva0048F64EGetB();
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
	void aiAttackPosition(const Coord3D *position, Int maxShots,
		CommandSourceType source);
	void rva0045003E(Int value, CommandSourceType source);
};

class AIUpdateInterfaceView
{
public:
	unsigned char m_pad00[0x20];
	AICommandInterface *m_commands;
};

class Rva0028B7AELeaGetter
{
public:
	void *get() const;
};

class Rva0028BD3AInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void set(Bool enabled);
};

class Thing
{
public:
	Drawable *getDrawable() const;
	void *m_vtable;
	const void *m_template;
	unsigned char m_pad08[0x30];
	Coord3D m_position;
	unsigned char m_pad44[4];
};

class Object : public Thing
{
public:
	Int rva0028B7C8() const;
	void rva0028AE6D();
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	void clearWeaponSetFlag(WeaponSetType type);
	void setWeaponSetFlag(WeaponSetType type);
	void *rva0028BD3A() const;
	const UnsignedInt *getWeaponSetFlags() const
	{
		return (const UnsignedInt *)((const Rva0028B7AELeaGetter *)this)->get();
	}
	const Coord3D *getPosition() const { return &m_position; }
	__forceinline void clearConditionWord5Bit2()
	{
		if (m_conditionWords[5] & 4) {
			m_conditionWords[5] &= ~4U;
			rva0028AE6D();
		}
	}
	__forceinline void setConditionWord5Bit2()
	{
		if (!(m_conditionWords[5] & 4)) {
			m_conditionWords[5] |= 4;
			rva0028AE6D();
		}
	}
	__forceinline void clearConditionWord5Bit0()
	{
		if (m_conditionWords[5] & 1) {
			m_conditionWords[5] &= ~1U;
			rva0028AE6D();
		}
	}
	__forceinline void clearConditionWord5Byte1Bits()
	{
		unsigned char *bytes = (unsigned char *)&m_conditionWords[5];
		if (bytes[1] & 0x10) {
			bytes[1] &= 0xEF;
			rva0028AE6D();
		}
		if (bytes[1] & 0x20) {
			bytes[1] &= 0xDF;
			rva0028AE6D();
		}
		if (bytes[1] & 0x40) {
			bytes[1] &= 0xBF;
			rva0028AE6D();
		}
		if (bytes[1] & 0x80) {
			bytes[1] &= 0x7F;
			rva0028AE6D();
		}
	}
	__forceinline Bool hasStatusBit1() const { return (m_status438 & 1) != 0; }
	__forceinline Bool hasWeaponSet(WeaponSetType type) const
	{
		return ((*getWeaponSetFlags() >> type) & 1) != 0;
	}

private:
	unsigned char m_pad48[0x10C - 0x48];
	UnsignedInt m_conditionWords[19];
	unsigned char m_pad158[0x254 - 0x158];
	public:
	BodyModuleFloatInterface *m_body;
	AIUpdateInterfaceView *m_ai;
	private:
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_status438;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;
extern float g_Va00BBB8D8;

class Rva00458BE1
{
public:
	unsigned char rva00458BE1();
};

class RampageBehavior
{
public:
	virtual UpdateSleepTime update();

private:
	unsigned char m_pad04[0x10 - 4];
	float m_10;
	Int m_14;
	Int m_18;
};

UpdateSleepTime RampageBehavior::update()
{
	Object *owner = *(Object **)((char *)this - 8);
	AIUpdateInterfaceView *ai = owner->m_ai;
	BodyModuleFloatInterface *body = owner->m_body;
	Drawable *drawable = owner->getDrawable();
	if (!body || !ai || !drawable)
		return UPDATE_SLEEP_FOREVER;

	const RampageBehaviorModuleDataView *data =
		(const RampageBehaviorModuleDataView *)*(const ModuleData **)((char *)this - 0xC);
	for (const unsigned char *upgrade = data->m_requiredUpgradeStart;
		upgrade != data->m_requiredUpgradeFinish; upgrade += 4) {
			const UpgradeTemplate *required = TheUpgradeCenter->findUpgrade(
				*(const AsciiString *)upgrade);
			if (!owner->rva00290D2B(required))
				return UPDATE_SLEEP_NONE;
	}

	float health = body->rva0048F64EGetA();
	float maxHealth = body->rva0048F64EGetB();
	float divisor = g_Va00BBB8D8;
	const float *divisorPointer = &divisor;
	if (maxHealth > 1.0f)
		divisorPointer = &maxHealth;
	float healthRatio = health / *divisorPointer;

	if (m_14 > 0) {
		--m_14;
		if (m_14 > 0) {
			if (!owner->hasStatusBit1() && !owner->rva0028B7C8())
				goto updateResetTimer;
			if (owner->hasWeaponSet(WEAPONSET_8))
				owner->clearWeaponSetFlag(WEAPONSET_8);
			if (!owner->hasStatusBit1() && !owner->rva0028B7C8())
				ai->m_commands->aiIdle(CMD_FROM_AI);
		}
		m_14 = 0;
		m_18 = data->m_resetTimer;
		owner->clearConditionWord5Bit2();
		drawable->rva00274176(false);
		goto updateResetTimer;
	}

	if (data->m_healthThreshold <= healthRatio
		|| owner->hasStatusBit1()
		|| owner->hasWeaponSet(WEAPONSET_8)
		|| m_10 <= healthRatio
		|| m_18 != 0)
		goto updateResetTimer;

	if (((Rva00458BE1 *)((char *)this - 0x10))->rva00458BE1()) {
		owner->clearWeaponSetFlag(WEAPONSET_7);
		owner->setWeaponSetFlag(WEAPONSET_8);
		ai->m_commands->aiAttackPosition(owner->getPosition(), 0x0FFFFFFE,
			CMD_FROM_AI);
		m_14 = data->m_lifeTimer;
	} else {
		owner->setConditionWord5Bit2();
		ai->m_commands->rva0045003E(0, CMD_FROM_AI);
		m_14 = data->m_angryLifeTimer;
	}
	owner->clearConditionWord5Bit0();
	owner->clearConditionWord5Byte1Bits();
	Rva0028BD3AInterface *iface = (Rva0028BD3AInterface *)owner->rva0028BD3A();
	if (iface)
		iface->set(false);
	drawable->rva00274176(false);

updateResetTimer:
	if (m_18 > 0) {
		--m_18;
		if (m_18 <= 0)
			m_10 = healthRatio;
	}
	return UPDATE_SLEEP_NONE;
}
