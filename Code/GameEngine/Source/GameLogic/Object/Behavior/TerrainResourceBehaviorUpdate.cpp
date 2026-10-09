// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc
//
// ?update@TerrainResourceBehavior@@UAE?AW4UpdateSleepTime@@XZ retail
// 0x004822A5..0x00482551 (684 bytes, EH, plain RET).
// - It is slot 0 of the +0x10 update-interface vtable 0x008493FC of the class
//   whose rowed ctor 0x0048209B installs it, so this-0x10 is the module.
// - The layout follows the rowed TerrainResourceBehavior ctor, xfer and
//   module-data ctor:
//   - module data: +0x08 Radius, +0x0C MaxIncome, +0x10 IncomeInterval,
//     +0x14 / +0x15 bytes, +0x18 UpgradeMustBePresent, +0x1C Upgrade,
//     +0x20 UpgradeBonusPercent;
//   - module: bools at +0x28 / +0x29 and a float at +0x2C.
// - WorldBuilder 0x011B96C0 has the same body.
//
// What the body does:
// - On the first update it registers the object with GameLogic's +0x170
//   manager (rowed 0x0035A238, as the sibling Rva00482172.cpp does). It then
//   sleeps forever when +0x29 is set.
// - With a controlling player whose +0x34 data exists:
//   - Income = MaxIncome * scale * the rowed Object::rva0028C15E(13) value
//     * UpgradeBonusPercent (the bonus applies only when both rowed Player
//     upgrade checks pass), rounded up.
//   - When the player's filter (+0x1C8) is valid and accepts this object, the
//     income is scaled by a per-count percentage. The count comes from
//     Player::iterateObjects with callback 0x00482002 (defined above update), which is unrowed and
//     declared here only. The percentage is entry count of the +0x1CC int
//     table, or the last entry less 2% per extra count, clamped at zero.
//   - The amount is paid through the rowed money member at player +0x90
//     (0x003B0D7C) and shown as GUI:AddCash floating text above the object's
//     geometry top. The colour is player +0x280 with alpha 0xE6.
//   - The experience tracker at object +0x264 gets the amount as experience.
// - It returns IncomeInterval.
//
// Matching notes:
// - REAL_TO_INT_CEIL is Zero Hour's fast_float2long_round(fast_float_ceil(x)),
//   with BFME 2's CRT ceil.
// - The getData()->getFilter() accessors and the callback record declared at
//   the top of the player block are what give retail its register and stack
//   allocation.
#include <math.h>
#include "unicode_string.h"
#include "Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef int Color;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
__forceinline Real fast_float_ceil(Real f)
{
	return (Real)ceil((double)f);
}
#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))

class GameLogic;
extern GameLogic *TheGameLogic;
class Object;
class Player;
class UpgradeTemplate;
class BfmeTab1026;
class Rva0039B7AD;

struct Rva0035A238Argument;
class Rva0035A238
{
public:
	void rva0035A238(Rva0035A238Argument *argument, float value, bool flag, bool front);
};
struct TerrainResourceLogicView
{
	char unknown00[0x170];
	Rva0035A238 *manager;							// +0x170
	Rva0035A238 *getManager() const { return manager; }
};

class ObjectFilter
{
public:
	Bool isValid() const;
};
struct Rva2225E0Filter
{
	Bool accepts(Object *obj, Player *player);
};

struct TerrainResourceIntVector
{
	Int *m_start;
	Int *m_finish;
	Int *m_endOfStorage;
	Int size() const { return m_finish - m_start; }
	const Int &operator[](Int i) const { return m_start[i]; }
};

struct TerrainResourcePlayerData
{
	char unknown000[0x1C8];
	ObjectFilter m_filter;							// +0x1C8
	char unknown1C9[0x1CC - 0x1C9];
	TerrainResourceIntVector m_percents;			// +0x1CC
	ObjectFilter *getFilter() { return &m_filter; }
};

class Rva003B0D7C
{
public:
	void rva003B0D7C(Int amount, Rva0039B7AD *stats, Bool flag);
};

class Player
{
public:
	Bool rva002AB87D(const UpgradeTemplate *upgrade) const;
	Bool rva002AB2D9(BfmeTab1026 *tab, Bool flag) const;
	Int iterateObjects(Int (*func)(Object *obj, void *userData), void *userData) const;
	char unknown000[0x34];
	TerrainResourcePlayerData *m_data;				// +0x34
	TerrainResourcePlayerData *getData() const { return m_data; }
	char unknown038[0x90 - 0x38];
	Rva003B0D7C m_money;							// +0x90
	char unknown091[0x280 - 0x91];
	Color m_color;									// +0x280
	char unknown284[0x3BC - 0x284];
	char m_stats[4];								// +0x3BC
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class ExperienceTracker
{
public:
	Bool rva0039AE04() const;
	void rva0039B315(Real amount, Bool a, Bool b, Bool c, Bool d);
};

enum ObjectStatusTypes { OBJECT_STATUS_TYPES_ANY };

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	Bool rva0028C15E(Int type, Real *value, Int a, Int b);
	char unknown000[0x38];
	Coord3D m_pos;									// +0x38
	char unknown044[0xA8 - 0x44];
	GeometryInfo m_geometryInfo;					// +0xA8
	char unknown0A9[0x264 - 0xA9];
	ExperienceTracker *m_experienceTracker;			// +0x264
};

class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16();
	virtual const UnicodeString *fetch(const char *label, Bool *exists);	// slot 17 (+0x44)
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V10(0) V10(1) V10(2) V10(3) V10(4) V10(5) V10(6) V10(7) V10(8) V10(9)
	V(100) V(101) V(102) V(103)
	virtual void addFloatingText(const UnicodeString &text, const Coord3D *pos, Color color);	// slot 104
#undef V10
#undef V
};
extern InGameUI *TheInGameUI;

struct TerrainResourceBehaviorModuleData
{
	void *m_vtable;
	Int m_unused04;
	Real m_radius;									// +0x08
	Int m_maxIncome;								// +0x0C
	Int m_incomeInterval;							// +0x10
	Bool m_highPriority;							// +0x14
	Bool m_visible;									// +0x15
	BfmeTab1026 *upgradeMustBePresent() const { return (BfmeTab1026 *)&m_upgradeMustBePresent; }
	Int m_upgradeMustBePresent;						// +0x18
	const UpgradeTemplate *m_upgrade;				// +0x1C
	Real m_upgradeBonusPercent;						// +0x20
};

struct TerrainResourceCountData
{
	Rva2225E0Filter *filter;
	Int count;
};
// ?Rva00482002CountMatching@@YAHPAVObject@@PAX@Z, retail 0x00482002..0x0048202F
// (45 bytes), cdecl: the Player::iterateObjects callback the update below passes
// by address. A live object (status 2 clear, rowed Object::testStatus) that the
// player data's filter accepts (rowed 0x00362437) bumps the count; it always
// answers 1 to keep iterating. No WorldBuilder twin; the name is address-derived.
Int Rva00482002CountMatching(Object *obj, void *userData)
{
	if (!obj->testStatus((ObjectStatusTypes)2))
	{
		TerrainResourceCountData *data = (TerrainResourceCountData *)userData;
		if (data->filter->accepts(obj, 0))
			++data->count;
	}
	return 1;
}

class TRB_DeepBase
{
public:
	virtual ~TRB_DeepBase();
protected:
	const TerrainResourceBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;										// +0x08
};
class TRB_Iface1 { public: virtual void slot(); };
class TRB_Iface2 { public: virtual UpdateSleepTime update() = 0; };
class TRB_Iface3 { public: virtual void slot3(); };
class TRB_Iface4 { public: virtual void slot4(); };

class UpdateModule : public TRB_DeepBase, public TRB_Iface1, public TRB_Iface2
{
protected:
	Object *getObject() const { return m_object; }
	const TerrainResourceBehaviorModuleData *getTerrainResourceBehaviorModuleData() const { return m_moduleData; }
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class TerrainResourceBehavior : public UpdateModule, public TRB_Iface3, public TRB_Iface4
{
public:
	virtual UpdateSleepTime update();
private:
	Bool m_registered;								// +0x28
	Bool m_sleepAfterRegister;						// +0x29
	Real m_incomeScale;								// +0x2C
};

UpdateSleepTime TerrainResourceBehavior::update()
{
	const TerrainResourceBehaviorModuleData *d = getTerrainResourceBehaviorModuleData();
	Object *obj = getObject();
	if (!m_registered)
	{
		reinterpret_cast<TerrainResourceLogicView *>(TheGameLogic)->getManager()->rva0035A238(
			reinterpret_cast<Rva0035A238Argument *>(obj), d->m_radius, d->m_visible, d->m_highPriority);
		m_registered = true;
		if (m_sleepAfterRegister)
			return UPDATE_SLEEP_FOREVER;
	}

	Player *player = obj->getControllingPlayer();
	if (player && player->m_data)
	{
		TerrainResourceCountData data;
		Real bonus = 1.0f;
		if (d->m_upgrade && player->rva002AB87D(d->m_upgrade) && player->rva002AB2D9(d->upgradeMustBePresent(), true))
			bonus = d->m_upgradeBonusPercent;

		Real percent = 0.0f;
		obj->rva0028C15E(0x0D, &percent, 0, 1);

		Real factor = 1.0f;
		ObjectFilter *filter = player->getData()->getFilter();
		if (filter->isValid() && reinterpret_cast<Rva2225E0Filter *>(filter)->accepts(obj, player))
		{
			data.filter = reinterpret_cast<Rva2225E0Filter *>(filter);
			data.count = 0;
			player->iterateObjects(Rva00482002CountMatching, &data);
			const TerrainResourceIntVector &percents = player->m_data->m_percents;
			Int numPercents = percents.size();
			if (data.count < numPercents)
				factor = percents[data.count] * 0.01f;
			else
			{
				factor = percents[numPercents - 1] * 0.01f - (data.count - numPercents) * 0.02f;
				if (factor < 0.0f)
					factor = 0.0f;
			}
		}

		Int amount = REAL_TO_INT_CEIL(d->m_maxIncome * m_incomeScale * percent * bonus);
		if (amount > 0)
		{
			amount = REAL_TO_INT_CEIL(amount * factor);
			if (amount <= 0)
				amount = 1;
			player->m_money.rva003B0D7C(amount, (Rva0039B7AD *)player->m_stats, true);

			UnicodeString moneyString;
			moneyString.format(TheGameText->fetch("GUI:AddCash", 0), amount);
			Coord3D pos;
			pos.x = obj->m_pos.x;
			pos.y = obj->m_pos.y;
			pos.z = obj->m_pos.z;
			pos.z += obj->m_geometryInfo.getMaxHeightAbovePosition();
			Color color = player->m_color | 0xE6000000;
			TheInGameUI->addFloatingText(moneyString, &pos, color);
		}

		ExperienceTracker *tracker = obj->m_experienceTracker;
		if (tracker && tracker->rva0039AE04())
			tracker->rva0039B315((Real)amount, true, true, true, false);
	}
	return (UpdateSleepTime)d->m_incomeInterval;
}
