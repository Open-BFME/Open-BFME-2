// cl: /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
typedef bool Bool;
typedef float Real;
#define COORD3D_VIEW_DTOR
#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include "ascii_string.h"
#include "../../../../Include/GameLogic/Weapon.h"

class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Thing;
class ModuleData;
class SpecialPowerTemplate;
class Waypoint;
class FiringTracker;
class Rva00492BEBHolder;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
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

struct Rva004929D1Template
{
	unsigned char m_pad000[0x108];
	unsigned char m_108; // +0x108
	unsigned char m_pad109[0x115 - 0x109];
	unsigned char m_115; // +0x115
};

class Object
{
public:
	void rva0028AE6D();
	void *rva0028C197() const;
	void rva002900E0(int frame);
	Real rva002C97E8(const Coord3D *from, const Coord3D *to) const;
	Drawable *getDrawable() const;
	ObjectID getID() const { return m_74; }
	__forceinline void clearModelCondition(int bit)
	{
		if (m_conditionBits.test(bit))
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
	unsigned char m_pad000[0x04];
	const Rva004929D1Template *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_pos; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_74; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x240 - 0x158];
	FiringTracker *m_240; // +0x240
	unsigned char m_pad244[0x258 - 0x244];
	Rva00492BEBHolder *m_holder; // +0x258
};

// Field names from the parse table 0xBEF0A8 the module data ctor 0x4926CA fills.
class WeaponFireSpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad00[0xC4];
	Bool m_tailC4; // +0xC4
	unsigned char m_padC5[0xC8 - 0xC5];
	AsciiString m_weaponName; // +0xC8
	int m_whichSpecialWeapon; // +0xCC
	Bool m_skipContinue; // +0xD0
	unsigned char m_padD1[0xD4 - 0xD1];
	int m_busyForDuration; // +0xD4
	Bool m_needLivingTargets; // +0xD8
	Bool m_playWeaponPreFireFX; // +0xD9
};

// The data ledger names this class's vftables after these four vptr holders
// (0x00C4E090, 0x00C4D640, 0x00C4E080, 0x00C4E05C), so they keep those names.
class WFS_RootBase
{
public:
	virtual ~WFS_RootBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class WFS_Iface1
{
public:
	virtual void slot();	// slot 0 of 0x00C4D640
};

class WFS_Iface2
{
public:
	virtual UpdateSleepTime update() = 0;	// slot 0 of 0x00C4E080
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

// Retail's table at +0x20 (0x00C4E05C, base 0x00C552A4) has 9 slots; only the two with rows of this class chain are declared.
class WFS_Iface3
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions,
		const Waypoint *way);	// slot 0
	virtual Bool rva0044EDA6(int value);	// slot 8
};

// Primary table: retail's 0x00C4E090 has 23 slots (base 0x00C3FBA8); the retail slot numbers of the declared ones are noted.
class SpecialAbilityUpdate : public WFS_RootBase, public WFS_Iface1, public WFS_Iface2, public WFS_Iface3
{
public:
	virtual ~SpecialAbilityUpdate();	// 0x00451F45
protected:
	virtual void xfer(Xfer *xfer);	// slot 3, 0x0044F996
public:
	virtual NameKeyType getModuleNameKey() const;	// slot 4, 0x0044F054
protected:
	virtual void onExit(bool a, bool b);	// slot 13, 0x004502CE
public:
	virtual Bool continuePreparation();	// slot 16, 0x0044FC52
	virtual void triggerAbilityEffect();	// slot 17, 0x0045108D
	virtual void startPacking(Bool flag);	// slot 21, 0x00450635
	virtual void startUnpacking();	// slot 22, 0x004508B7
	virtual UpdateSleepTime update();	// 0x00451FA2
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions,
		const Waypoint *way);	// 0x004500A3
	virtual Bool rva0044EDA6(int value);	// 0x0044EDA6
protected:
	int m_24; // +0x24
	unsigned char m_pad28[0x30 - 0x28];
	int m_packingState; // +0x30
	unsigned char m_pad34[0x40 - 0x34];
	ObjectID m_targetID; // +0x40
	Coord3D m_targetPos; // +0x44
	unsigned char m_pad50[0x88 - 0x50];
};

// The spelling the derived ctors use for SpecialAbilityUpdate's ctor (row 0x0044EF5E);
// SpecialAbilityUpdateDtor.cpp binds its complete dtor to 0x00451F45.
class Rva0044EF5E : public SpecialAbilityUpdate
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
};

class WeaponFireSpecialAbilityUpdate : public Rva0044EF5E
{
public:
	WeaponFireSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~WeaponFireSpecialAbilityUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual Bool continuePreparation();
	virtual void triggerAbilityEffect();
	virtual void startPacking(Bool flag);
	virtual void startUnpacking();
	virtual UpdateSleepTime update();
	virtual Bool rva0044EDA6(int value);

protected:
	virtual void xfer(Xfer *xfer);
	virtual void onExit(bool a, bool b);

private:
	const WeaponFireSpecialAbilityUpdateModuleData *getWeaponFireModuleData() const
	{
		return reinterpret_cast<const WeaponFireSpecialAbilityUpdateModuleData *>(m_moduleData);
	}

	Weapon *m_weapon; // +0x88
};

extern GameLogic *TheGameLogic;

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

class FiringTracker
{
	friend class WeaponFireSpecialAbilityUpdate;
	void coolDown(Bool flag);
public:
	void shotFired(const Weapon *weapon, ObjectID victim, const Coord3D *pos, Bool flag);
};

class Rva00492A72Redirect
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual Object *s68();
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void rva15(Real value);
};

class Rva0044E633
{
public:
	void *rva0044E633();
};

// ?triggerAbilityEffect@WeaponFireSpecialAbilityUpdate@@UAEXXZ, retail
// 0x00492A72, 377 bytes: slot 17 of WeaponFireSpecialAbilityUpdate's primary
// vtable 0x00C4E090 (ctors 0x0049257C, 0x00492736), the override of the
// SpecialAbilityUpdate slot-17 base 0x0045108D (triggerAbilityEffect), as in
// ScaleWallSpecialAbilityUpdateSlot17.cpp. BFME 1 names the same slot
// WeaponFireSpecialAbilityUpdate::triggerAbilityEffect; the WB twin 0x011E40A0
// gives the statement shape. Cools the Object's +0x240 FiringTracker
// (0x004DEC88), then, unless the Object's template has bit 5 of +0x115 and
// the module data's +0xC4 flag, looks up the target (+0x40), redirecting
// through the target's +0x250 interface (0x0028C197, its slot 68) when the
// target's template has the same bit; with a ready Weapon (+0x88) it stamps
// the Object's ID into the Weapon's +0x08 and fires at the target
// (0x002CE6C5) or, with no target, forces a shot at +0x44 (the Object's own
// position when that is zero or the data's +0xD8 flag is set), reports it
// to the tracker (0x004DEECB) and hands the Object (0x002900E0) the frame
// plus the data's +0xD4. Then the base, and 1.0f to slot 15 of the module
// 0x0044E633 finds.
//
// The zero position is a Coord3D(0, 0, 0) temporary inside the && of the
// use-target test: retail's Coord3D has an empty user destructor, so cl
// keeps a construction flag for it, and its zero store at entry
// (`and [ebp-8], 0`) survives in the slot the module data later spills to.
void WeaponFireSpecialAbilityUpdate::triggerAbilityEffect()
{
	const WeaponFireSpecialAbilityUpdateModuleData *data = getWeaponFireModuleData();
	Object *obj = m_object;
	if (obj->m_240)
		obj->m_240->coolDown(true);
	if (!(obj->m_template->m_115 & 0x20) || !data->m_tailC4)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		ObjectID targetID = target ? target->getID() : INVALID_OBJECT_ID;
		if (target && (target->m_template->m_115 & 0x20))
		{
			Rva00492A72Redirect *redirect = (Rva00492A72Redirect *)target->rva0028C197();
			if (redirect)
			{
				Object *other = redirect->s68();
				if (other)
				{
					target = other;
					targetID = other->getID();
				}
			}
		}
		if (m_weapon && m_weapon->getStatus() == READY_TO_FIRE)
		{
			m_weapon->m_ownerID = obj->getID();
			if (target)
			{
				m_weapon->rva002CE6C5(obj, targetID, target, 0);
				if (obj->m_240)
					obj->m_240->shotFired(m_weapon, targetID, 0, true);
			}
			else
			{
				Bool useTargetPos = !(m_targetPos == Coord3D(0.0f, 0.0f, 0.0f)) && !data->m_needLivingTargets;
				const Coord3D *pos = useTargetPos ? &m_targetPos : &obj->m_pos;
				m_weapon->forceFireWeapon(obj, pos);
				if (obj->m_240)
					obj->m_240->shotFired(m_weapon, INVALID_OBJECT_ID, pos, true);
			}
			obj->rva002900E0(TheGameLogic->getFrame() + getWeaponFireModuleData()->m_busyForDuration);
		}
	}
	SpecialAbilityUpdate::triggerAbilityEffect();
	SpecialPowerModuleInterface *spm = (SpecialPowerModuleInterface *)reinterpret_cast<Rva0044E633 *>(this)->rva0044E633();
	if (spm)
		spm->rva15(1.0f);
}
