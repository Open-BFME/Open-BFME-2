// cl: /DNDEBUG /MD
//
// Two DeflectSpecialPower interface slots, compiled with their subobject this.
// The matched ctor 0x004C545D installs vtables at +0x00 (0x00C5DA7C), +0x0C,
// +0x10 (0x00C5D9B0), +0x20 (0x00C5D98C), +0x24 and +0x38 (0x00C5D974); the
// candidate list had filed these slots under GrabPassengerSpecialPower,
// whose primary vtable 0x00C5D93C directly precedes them.
//
// ?update@DeflectSpecialPower@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004C55FC,
// 117 bytes: slot 0 of the +0x10 vtable 0x00C5D9B0 (UpdateModuleInterface;
// the name is the base-slot name). With neither flag +0x3C nor +0x3D set it
// sleeps forever. When the owner's rowed Object::rva0028B7C8 gate holds
// (that row is filed as returning int; retail tests only AL, so the call is
// narrowed to char here) it drops +0x3C, clears condition bit 4*32+30 and
// sleeps forever; otherwise a pending +0x3D becomes an active +0x3C and sets
// that bit. Both condition changes go through the rowed notifier
// Object::rva0028AE6D only when the bit actually changes.
//
// ?onCollide@DeflectSpecialPower@@UAEXPAVObject@@PBVCoord3D@@1@Z, retail
// 0x004C55B2, 74 bytes: slot 0 of the +0x38 vtable 0x00C5D974. That subobject
// is the collide interface: the ctor first stores the all-purecall 6-slot
// vtable 0x00C40818 there, and the slots after this one are a one-argument
// bool returning false (0x005CB9FF) and four argless false bools, the shape
// of ZH CollideModuleInterface (onCollide, wouldLikeToCollideWith and four
// is*CrateCollide/isRailroad queries) with CollideModule's defaults. Only
// the first argument is read; ret 0xC. While
// +0x3C is active and the Object argument's template has bit 0x40 of its
// +0x114 byte, walks that object's behavior modules (Object+0x244, null
// terminated) and for each one whose BehaviorModuleInterface slot 18 answers
// an interface, calls that interface's slot 5 with the owner.

// Shared DeflectSpecialPower unit view: one declaration of each class for
// every body retail built into this unit. The ctor 0x004C545D installs
// vtables at +0x00, +0x0C, +0x10, +0x20, +0x24 and +0x38: ObjectModule and
// BehaviorModuleInterface (canonical BehaviorModule), UpdateModuleInterface,
// the base's two extra interfaces and the collide interface.

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class Coord3D;
class Xfer;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};

class Rva00589079_E1
{
public:
	virtual void fe() = 0;
};

class Rva00589079_E2
{
public:
	virtual void fe() = 0;
};

class Rva00589079 : public UpdateModule, public Rva00589079_E1, public Rva00589079_E2
{
public:
	virtual ~Rva00589079(); // 0x00589079

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_28;
	int m_2C;
	unsigned int m_30;
	float m_34;
};

// DeflectSpecialPower's direct base: its ctor calls 0x0058959A
// (WeaponModeSpecialPowerUpdateBase's rowed ctor) and its xfer calls
// 0x00589215 (rowed as Rva00589079::xfer). Both placeholder names stay on
// their rows; this view chains them so each call keeps its symbol.
class WeaponModeSpecialPowerUpdateBase : public Rva00589079
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);
};

class CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class DeflectSpecialPower : public WeaponModeSpecialPowerUpdateBase, public CollideModuleInterface
{
public:
	DeflectSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_active; // +0x3C
	bool m_pending; // +0x3D
};

template <int N> class Rva004C55B2Slots : public Rva004C55B2Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C55B2Slots<0>
{
};

class Rva004C55B2Target : public Rva004C55B2Slots<5>
{
public:
	virtual void rva004C55B2Slot5(Object *source) = 0;
};

class ThingTemplateView
{
public:
	unsigned char m_pad000[0x114];
	unsigned char m_114; // +0x114
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	int rva0028B7C8() const;
	void rva0028AE6D();

	unsigned char m_pad000[0x04];
	const ThingTemplateView *m_template; // +0x04
	unsigned char m_pad008[0x10C - 0x08];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x244 - 0x158];
	BehaviorModule **m_behaviors; // +0x244
};

static const int DEFLECT_CONDITION_BIT = 4 * 32 + 30;

// ?update@DeflectSpecialPower@@UAE?AW4UpdateSleepTime@@XZ @0x004C55FC
UpdateSleepTime DeflectSpecialPower::update()
{
	if (!m_active && !m_pending)
		return UPDATE_SLEEP_FOREVER;

	if ((char)m_object->rva0028B7C8())
	{
		if (!m_active)
			return UPDATE_SLEEP_NONE;
		Object *me = m_object;
		m_active = false;
		if (me->m_conditionBits.test(DEFLECT_CONDITION_BIT))
		{
			me->m_conditionBits.clear(DEFLECT_CONDITION_BIT);
			me->rva0028AE6D();
		}
		return UPDATE_SLEEP_FOREVER;
	}

	if (m_pending && !m_active)
	{
		Object *me = m_object;
		m_pending = false;
		m_active = true;
		if (!me->m_conditionBits.test(DEFLECT_CONDITION_BIT))
		{
			me->m_conditionBits.set(DEFLECT_CONDITION_BIT);
			me->rva0028AE6D();
		}
	}
	return UPDATE_SLEEP_NONE;
}

// ?onCollide@DeflectSpecialPower@@UAEXPAVObject@@PBVCoord3D@@1@Z @0x004C55B2
void DeflectSpecialPower::onCollide(Object *other, const Coord3D *, const Coord3D *)
{
	if (!m_active || !other || !(other->m_template->m_114 & 0x40))
		return;
	for (BehaviorModule **behaviorModule = other->m_behaviors; *behaviorModule; ++behaviorModule)
	{
		Rva004C55B2Target *target = static_cast<Rva004C55B2Target *>((*behaviorModule)->slot18());
		if (target)
			target->rva004C55B2Slot5(m_object);
	}
}
