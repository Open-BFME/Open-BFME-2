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

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Player;
struct Coord3D;
class Object
{
public:
	Player *getControllingPlayer() const; // 0x0028AFA9
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
	char m_pad00[0x38];
	Coord3D m_pos; // +0x38
	char m_pad44[0xC8];
	unsigned m_kindOfBits[(0x254 - 0x10C) / 4]; // +0x10C
	BodyView *m_body; // +0x254
	AIView *m_ai; // +0x258
	char m_pad25C[0x1DC];
	unsigned char m_flags438; // +0x438
	char m_pad439[0x3];
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
	unsigned m_transitionTime;			// +0x20
	const FXList *m_transitionFX;			// +0x24
	const FXList *m_onBuffFX;		// +0x28
	const FXList *m_offBuffFX;			// +0x2C
};

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BodyModuleInterface;

// The constructor installs the shared 0x007EFF90 table at +0x0C. Its
// first entry is the null-returning getBody used by this same base view.
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


enum NameKeyType
{
	NK_UNKNOWN = 0
};
class Xfer;
class EntEnragedUpdate : public UpdateModule
{
public:
	EntEnragedUpdate(Thing *, const ModuleData *);
	virtual NameKeyType getModuleNameKey() const;
	// Rowed in EntEnragedUpdateUpdate.cpp: slot 0 of retail's UpdateModuleInterface table 0x00C5693C.
	virtual UpdateSleepTime update();
	bool rva004B25C9();
	bool rva004B266D();
	virtual ~EntEnragedUpdate();
	virtual void rva004B23C5(Xfer *xfer); // slot 3 of 0x00C56948
private:
	unsigned int m_20; // +0x20
	unsigned int m_24; // +0x24
	unsigned int m_28; // +0x28
	bool m_2C; // +0x2C
	bool m_2D; // +0x2D
	bool m_2E; // +0x2E
	bool m_2F; // +0x2F
	bool m_30; // +0x30
	char m_pad31[0x3];
};

UpdateSleepTime EntEnragedUpdate::update()
{
	Object *me = m_object;
	const EntEnragedUpdateModuleData *data = (const EntEnragedUpdateModuleData *)m_moduleData;

	if (me->m_flags438 & 1)
		return UPDATE_SLEEP_FOREVER;

	bool mayRage = m_24 <= TheGameLogic->getFrame() && !me->testStatus(OBJECT_STATUS_AFLAME);
	if (m_2D)
		mayRage = true;

	if (m_2C && mayRage)
	{
		if (m_30)
			m_2F = false;
		if (!m_2F)
		{
			me->setStatus(OBJECT_STATUS_STATUS_54, false);
			me->clearWeaponSetFlag(WEAPONSET_SET_16);
			AIView *ai = me->m_ai;
			if (ai)
				ai->slot142(0);
			m_24 = UPDATE_SLEEP_FOREVER;
			m_28 = TheGameLogic->getFrame() + data->m_timeUntilCanRageAgain;
			m_2C = false;
			m_2E = false;
			if (data->m_offBuffFX)
				FXList::doFXObj(data->m_offBuffFX, me, 0);
		}
	}

	if (m_2C)
		return UPDATE_SLEEP_NONE;

	if (m_28 < TheGameLogic->getFrame() || m_2F)
	{
		bool wantRage = false;
		if (rva004B25C9())
			wantRage = true;
		if (rva004B266D())
			wantRage = true;
		BodyView *body = m_object->m_body;
		if (body && body->getHealthFraction() < 0.5)
			wantRage = true;

		if (m_2E)
		{
			if (!me->isKindOf(KINDOF_KIND_4E))
				wantRage = true;
		}
		else
		{
			if (me->isKindOf(KINDOF_KIND_4E))
				m_2E = true;
		}

		if (me->testStatus(OBJECT_STATUS_AFLAME))
			wantRage = false;
		if (m_2F)
			wantRage = true;
		if (m_2D)
			wantRage = false;

		if (wantRage)
		{
			if (!me->isKindOf(KINDOF_KIND_FA) && !me->testStatus(OBJECT_STATUS_AFLAME))
			{
				me->setSpecialModelConditionState(MODELCONDITION_FLAG_13B, data->m_transitionTime);
				me->setDisabledUntil(DISABLED_TYPE_4, TheGameLogic->getFrame() + data->m_transitionTime);
				if (data->m_transitionFX)
					FXList::doFXObj(data->m_transitionFX, me, 0);
			}
			me->setStatus(OBJECT_STATUS_STATUS_54, true);
			me->setWeaponSetFlag(WEAPONSET_SET_16);
			AIView *ai = me->m_ai;
			if (ai)
				ai->slot142(8);
			m_2C = true;
			m_24 = TheGameLogic->getFrame() + data->m_enragedTime;
			const FXList *fx = data->m_onBuffFX;
			if (fx)
				FXList::doFXObj(fx, me, 0);
		}
	}

	return UPDATE_SLEEP_NONE;
}
