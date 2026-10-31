// cl: /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
typedef bool Bool;
typedef float Real;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
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

// Two WeaponFireSpecialAbilityUpdate primary-vtable (0x00C4E090) slots that
// defer to the SpecialAbilityUpdate base entries of 0x00C3FBA8, rowed as
// continuePreparation (0x0044FC52) and startPacking (0x00450635):
// - slot 16, retail 0x004927D0 (26 bytes): false while the module data's
//   +0xD0 flag is set and the +0x24 state is 2, else the base 0x0044FC52;
// - slot 21, retail 0x004925DB (10 bytes): ignores its flag and runs the
//   base 0x00450635 with true.
Bool WeaponFireSpecialAbilityUpdate::continuePreparation()
{
	if (getWeaponFireModuleData()->m_skipContinue && m_24 == 2)
		return false;
	return SpecialAbilityUpdate::continuePreparation();
}
void WeaponFireSpecialAbilityUpdate::startPacking(Bool)
{
	SpecialAbilityUpdate::startPacking(true);
}
