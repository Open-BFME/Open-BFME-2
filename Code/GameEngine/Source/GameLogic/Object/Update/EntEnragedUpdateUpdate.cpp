// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX
//
// ?update@EntEnragedUpdate@@UAE?AW4UpdateSleepTime@@XZ
// Retail 0x004B2761..0x004B2987 (550 bytes; the 599-byte inventory extent
// runs into the next body), slot 0 of the UpdateModuleInterface vftable, this
// = the +0x10 base, like the rowed FlammableUpdate::update. The enrage state
// machine of the EntEnragedUpdate module (ctor layout in
// EntEnragedUpdateCtorThunk.cpp: +0x24 next-rage frame, +0x28 cooldown
// frame, flags +0x2C enraged, +0x2D suppressed, +0x2E was-in-kind, +0x2F
// forced, +0x30 one-shot-force).
// Target facts: both scan members are the rowed 0x004B25C9 / 0x004B266D, the
// statuses/flags/kind-ofs are the rowed Object methods and every FX goes
// through the rowed static doFXObj. Module data +0x0C / +0x10 are the enraged
// and re-rage times, +0x20 the stun time and +0x24 / +0x28 / +0x2C the three
// FX lists (data layout: EnragedUpdateModuleDataCtor.cpp). WorldBuilder twin
// 0x01233650 (callgraph lead) gives the statement order, including one
// isKindOf call in each arm of the was-in-kind test. Names for the status /
// kind-of / weapon-set indices and the +0x438 object bit stay offset names.
//
// Object::isKindOf (retail 0x0006F039, rowed in Object.cpp; same bytes here)
// is out of line in retail but visible to this unit: cl then knows it writes
// no memory, merges the two arms' calls ahead of the +0x2E test (MOV ECX
// before PUSH 0x4E at 0x004B2888) and parks the last FX list in the dying
// module-data register (EBP at 0x004B296B).

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_AFLAME = 10,
	OBJECT_STATUS_STATUS_54 = 0x36
};

enum KindOfType
{
	KINDOF_KIND_4E = 0x4e,
	KINDOF_KIND_FA = 0xfa
};

enum WeaponSetType
{
	WEAPONSET_SET_16 = 0x16
};

enum ModelConditionFlagType
{
	MODELCONDITION_FLAG_13B = 0x13b
};

enum DisabledType
{
	DISABLED_TYPE_4 = 4
};

class Thing;
class ModuleData;
class FXList;

// Slot filler: one distinct pure virtual per vtable index, so a view class
// can name a single high slot (the idiom ToggleMountedSpecialAbilityUpdate.cpp
// uses).
template<int N> class Slots : public Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template<> class Slots<0>
{
};

// The Body module at Object+0x254: slot 5 returns the health fraction.
class BodyView : public Slots<5>
{
public:
	virtual float getHealthFraction() = 0;
};

// The AIUpdateInterface at Object+0x258: slot 142 takes a mode (FlammableUpdate
// documents the same slot).
class AIView : public Slots<142>
{
public:
	virtual void slot142(int mode) = 0;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	__declspec(noinline) bool isKindOf(KindOfType kind) const
	{
		return (m_kindOfBits[(unsigned)kind >> 5] & (1 << (kind & 31))) != 0;
	}
	void setStatus(ObjectStatusTypes status, bool set);
	void clearWeaponSetFlag(WeaponSetType set);
	void setWeaponSetFlag(WeaponSetType set);
	void setSpecialModelConditionState(ModelConditionFlagType type, unsigned frames);
	void setDisabledUntil(DisabledType type, unsigned frame);

	char m_unknown00[0x10C];
	unsigned m_kindOfBits[(0x254 - 0x10C) / 4];	// +0x10C
	BodyView *m_body;	// +0x254
	AIView *m_ai;		// +0x258
	char m_unknown25C[0x438 - 0x25C];
	unsigned char m_flags438;
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary = 0);
};

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class EntEnragedUpdateModuleData
{
public:
	char m_unknown00[0x0C];
	unsigned m_enragedTime;			// +0x0C
	unsigned m_timeUntilCanRageAgain;	// +0x10
	char m_unknown14[0x20 - 0x14];
	unsigned m_stunTime;			// +0x20
	const FXList *m_fxStun;			// +0x24
	const FXList *m_fxEnrage;		// +0x28
	const FXList *m_fxCalm;			// +0x2C
};

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void slot(); };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public PB_DeepBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
private:
	unsigned int m_field14;
	int m_field18;
	int m_field1C;
};

class EntEnragedUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	bool rva004B25C9();
	bool rva004B266D();

private:
	int m_value;
	unsigned int m_sleepTime;
	unsigned int m_field28;
	bool m_field2C;
	bool m_field2D;
	bool m_field2E;
	bool m_field2F;
	bool m_field30;
};

UpdateSleepTime EntEnragedUpdate::update()
{
	Object *me = m_object;
	const EntEnragedUpdateModuleData *data = (const EntEnragedUpdateModuleData *)m_moduleData;

	if (me->m_flags438 & 1)
		return UPDATE_SLEEP_FOREVER;

	bool mayRage = m_sleepTime <= TheGameLogic->getFrame() && !me->testStatus(OBJECT_STATUS_AFLAME);
	if (m_field2D)
		mayRage = true;

	if (m_field2C && mayRage)
	{
		if (m_field30)
			m_field2F = false;
		if (!m_field2F)
		{
			me->setStatus(OBJECT_STATUS_STATUS_54, false);
			me->clearWeaponSetFlag(WEAPONSET_SET_16);
			AIView *ai = me->m_ai;
			if (ai)
				ai->slot142(0);
			m_sleepTime = UPDATE_SLEEP_FOREVER;
			m_field28 = TheGameLogic->getFrame() + data->m_timeUntilCanRageAgain;
			m_field2C = false;
			m_field2E = false;
			if (data->m_fxCalm)
				FXList::doFXObj(data->m_fxCalm, me, 0);
		}
	}

	if (m_field2C)
		return UPDATE_SLEEP_NONE;

	if (m_field28 < TheGameLogic->getFrame() || m_field2F)
	{
		bool wantRage = false;
		if (rva004B25C9())
			wantRage = true;
		if (rva004B266D())
			wantRage = true;
		BodyView *body = m_object->m_body;
		if (body && body->getHealthFraction() < 0.5)
			wantRage = true;

		if (m_field2E)
		{
			if (!me->isKindOf(KINDOF_KIND_4E))
				wantRage = true;
		}
		else
		{
			if (me->isKindOf(KINDOF_KIND_4E))
				m_field2E = true;
		}

		if (me->testStatus(OBJECT_STATUS_AFLAME))
			wantRage = false;
		if (m_field2F)
			wantRage = true;
		if (m_field2D)
			wantRage = false;

		if (wantRage)
		{
			if (!me->isKindOf(KINDOF_KIND_FA) && !me->testStatus(OBJECT_STATUS_AFLAME))
			{
				me->setSpecialModelConditionState(MODELCONDITION_FLAG_13B, data->m_stunTime);
				me->setDisabledUntil(DISABLED_TYPE_4, TheGameLogic->getFrame() + data->m_stunTime);
				if (data->m_fxStun)
					FXList::doFXObj(data->m_fxStun, me, 0);
			}
			me->setStatus(OBJECT_STATUS_STATUS_54, true);
			me->setWeaponSetFlag(WEAPONSET_SET_16);
			AIView *ai = me->m_ai;
			if (ai)
				ai->slot142(8);
			m_field2C = true;
			m_sleepTime = TheGameLogic->getFrame() + data->m_enragedTime;
			const FXList *fx = data->m_fxEnrage;
			if (fx)
				FXList::doFXObj(fx, me, 0);
		}
	}

	return UPDATE_SLEEP_NONE;
}
