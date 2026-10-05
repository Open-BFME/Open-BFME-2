// cl: /O1 /DNDEBUG /MD
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

class Object;
class ModuleData;
class Coord3D;

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

class BehaviorModuleInterface : public Rva004C55B2Slots<18>
{
public:
	virtual Rva004C55B2Target *rva004C55B2Slot18() = 0;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleView : public BehaviorModule, public BehaviorModuleInterface
{
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
	BehaviorModuleView **m_behaviors; // +0x244
};

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

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};

class Rva004C55B2Iface20 { public: virtual void slot0(); };
class Rva004C55B2Iface24 { public: virtual void slot0(); };

class Rva00589079 : public UpdateModule, public Rva004C55B2Iface20, public Rva004C55B2Iface24
{
protected:
	unsigned char m_pad28[0x38 - 0x28];
};

class CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class DeflectSpecialPower : public Rva00589079, public CollideModuleInterface
{
public:
	virtual UpdateSleepTime update();
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
private:
	bool m_active; // +0x3C
	bool m_pending; // +0x3D
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
	for (BehaviorModuleView **m = other->m_behaviors; *m; ++m)
	{
		Rva004C55B2Target *target = (*m)->rva004C55B2Slot18();
		if (target)
			target->rva004C55B2Slot5(m_object);
	}
}
