// cl: /Ireference/shims/bfme2_ascii /MD /GX
//
// doSpecialPowerAtLocation overrides of four BFME2 area powers: slot 12 of
// each class's +0x10 special-power interface vftable (the slot
// InvisibilitySpecialPower's rowed doSpecialPowerAtLocation fills), so `this`
// is that subobject (module data at -0x0C, Object at -0x08). All four follow
// the Zero Hour override shape: nothing while the Object is disabled
// (Object +0x1C8, the rowed BitFlags<11>::any) or without a location, then
// SpecialPowerModule::doSpecialPowerAtLocation 0x004949D8, then the class's
// own placement helper on the primary this (pinned by address on their
// bodies, each taking the location).
//
// DarknessSpecialPower 0x004C4F1C (71 bytes, vftable 0x00C5D7F0): helper
// 0x004C4E93, then clears +0x98 of TheTriggerManager (0x00DFEC68).
// TaintSpecialPower 0x004C4B3C (74 bytes, vftable 0x00C5D568): also nothing
// while the module data's +0x7C name is empty; helper 0x004C49AE.
// FreezingRainSpecialPower 0x004C4D22 (79 bytes, vftable 0x00C5D700):
// helper 0x004C4C99, then hands the module data's +0x84 value to the
// TheTriggerManager (0x00DFEC68), via 0x00287519.
// ElvenWoodSpecialPower 0x004C3CFF (77 bytes, vftable 0x00C5CE28): Taint's
// shape with the name at module data +0x88 and helper 0x004C3B17.
// ElvenWoodSpecialPower slots 10 and 11 are also the slot-10/11 entries of
// the CloudBreak, Taint and FreezingRain vftables (identical code folded to
// one copy): slot 10 0x004C4C4B (78 bytes, doSpecialPower) places the power
// at a copy of the Object's own position, slot 11 0x004C4E63 (48 bytes,
// doSpecialPowerAtObject) at the target Object's position, both through the
// virtual slot 12 and both nothing while the Object is disabled.
// CloudBreakSpecialPower 0x004C482B (80 bytes, vftable 0x00C5D3C8): helpers
// 0x004C4621 (with the location) and 0x004C4582, then clears +0x98 of the
// TheTriggerManager (0x00DFEC68).
#include "../../../../../Libraries/Include/Lib/Coord3D.h"


#include "../../../../../Libraries/Include/Lib/Region3D.h"
#include "string_base.h"
#include <string.h>
#include "../../../Common/Thing/thing.h"

class Player;
class Team;
class AsciiString;
enum ObjectStatusTypes
{
	OBJECT_STATUS_0x54 = 0x54
};

template <int N> class BitFlags
{
public:
	// Retail's guarded static of this type carries no EH state.
	__declspec(nothrow) BitFlags() { clear(); }
	bool any() const;	// 0x0023C58B for N = 11
	bool setBitByName(const char *token);
	void clear() { memset(m_words, 0, sizeof(m_words)); }
private:
	unsigned int m_words[N == 11 ? 1 : 19];
};

enum WeaponSetType { WEAPONSET_FIRST = 0 };
enum DisabledType { DISABLED_FIRST = 0 };
enum ModelConditionFlagType { MODELCONDITION_FIRST = 0 };

class Object : public Thing
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void rva0028EC68(int a, void *b, int c);
	void setTeam(Team *);
	Team *getTeam() const { return m_team; }
	bool isDisabled() const { return m_disabledMask.any(); }
	void setWeaponSetFlag(WeaponSetType type);
	void clearWeaponSetFlag(WeaponSetType type);
	void rva001E42F2(const int *mask);
	bool addAttributeModifierToPool(const AsciiString &name, int n);
	void setDisabledUntil(DisabledType type, unsigned int frame);
	void setSpecialModelConditionState(ModelConditionFlagType set, unsigned int frames);
private:
	char m_pad60[0x74 - 0x60];
public:
	int m_id; // +0x74
private:
	char m_pad78[0x1C8 - 0x78];
	BitFlags<11> m_disabledMask; // +0x1C8
	char m_pad1CC[0x304 - 0x1CC];
	Team *m_team; // +0x304
};

// Object's disabled mask is at +0x1C8. Retail forms its address (and the
// Taint module data's +0x7C name) by adding the offset to the pointer loaded
// straight into ecx (mov ecx, [esi-8] / add ecx, 0x1C8); cl 7.1 emits that for
// byte-pointer arithmetic written in the body, while a typed member access
// or an inline accessor gives lea from another register instead.

class Rva00287519Host
{
public:
	void rva00287519(int value);	// 0x00287519
	void clear98() { m_98 = 0; }
private:
	unsigned char m_pad00[0x98];
	int m_98;			// +0x98
};
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;

class ModuleData;
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
	virtual void doSpecialPowerUsingWaypoints(void *target, float angle, int commandOptions) = 0;
};

class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
	virtual void doSpecialPower(unsigned int options);	// 0x0049490F
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);	// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
	virtual void pauseCountdown(bool pause);	// 0x00492FC2
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class ElvenWoodSpecialPower : public SpecialPowerModule
{
public:
	ElvenWoodSpecialPower( Thing *thing, const ModuleData *moduleData );
	Object *addObject(const Coord3D *position, const AsciiString *name);

	void rva004C3C36(const Coord3D *position);

	void rva004C3B17(const Coord3D *position);
	virtual void doSpecialPower(unsigned int options);
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);

protected:
	virtual ~ElvenWoodSpecialPower();
public:
	virtual NameKeyType getModuleNameKey() const;
};

class CloudBreakSpecialPower : public SpecialPowerModule
{
public:
	CloudBreakSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;

	// Rowed helpers: they stay out of line under this unit's /Ob2.
	__declspec(noinline) void rva004C4582();

	void rva004C4621(const Coord3D *position);
	__declspec(noinline) void rva004C45CF(const Coord3D *position, const AsciiString *name);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);

protected:
	virtual ~CloudBreakSpecialPower();
};

class TaintSpecialPower : public SpecialPowerModule
{
public:
	TaintSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;

	void rva004C49AE(const Coord3D *position);
	Object *addObject(const Coord3D *position, const AsciiString &name);
	Object *getObject() const { return m_object; }
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);

protected:
	virtual ~TaintSpecialPower();
};

class DarknessSpecialPower : public SpecialPowerModule
{
public:
	DarknessSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C4E93(const Coord3D *loc);

protected:
	virtual ~DarknessSpecialPower();
};

class FreezingRainSpecialPowerModuleData;
class FreezingRainSpecialPower : public SpecialPowerModule
{
public:
	FreezingRainSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C4C99(const Coord3D *loc);
	const FreezingRainSpecialPowerModuleData *getData() const
	{
		return (const FreezingRainSpecialPowerModuleData *)m_moduleData;
	}

protected:
	virtual ~FreezingRainSpecialPower();
};








class FXList;
class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
};

class FreezingRainSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	FreezingRainSpecialPowerModuleData();

	float m_freezingRainRadius; // +0x7C
	const FXList *m_freezingRainFX; // +0x80
	int m_burnRateModifier; // +0x84
};



void DarknessSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (loc == 0)
		return;
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C4E93(loc);
	((Rva00287519Host *)TheTriggerManager)->clear98();
}

void TaintSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (loc == 0)
		return;
	const void *data = m_moduleData;
	const StringBase<char> *name = (const StringBase<char> *)((const char *)data + 0x7C);
	if (name->isEmpty())
		return;
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C49AE(loc);
}

void FreezingRainSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (loc == 0)
		return;
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C4C99(loc);
	((Rva00287519Host *)TheTriggerManager)->rva00287519(getData()->m_burnRateModifier);
}

void CloudBreakSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (loc == 0)
		return;
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C4621(loc);
	rva004C4582();
	((Rva00287519Host *)TheTriggerManager)->clear98();
}

void ElvenWoodSpecialPower::doSpecialPower(unsigned int options)
{
	Object *object = m_object;
	if (object->isDisabled())
		return;
	Coord3D pos;
	pos.x = object->getPosition()->x;
	pos.y = object->getPosition()->y;
	pos.z = object->getPosition()->z;
	doSpecialPowerAtLocation(&pos, options);
}

void ElvenWoodSpecialPower::doSpecialPowerAtObject(Object *obj, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (obj == 0)
		return;
	doSpecialPowerAtLocation(obj->getPosition(), options);
}

void ElvenWoodSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	const void *object = m_object;
	const BitFlags<11> *disabled = (const BitFlags<11> *)((const char *)object + 0x1C8);
	if (disabled->any())
		return;
	if (loc == 0)
		return;
	const void *data = m_moduleData;
	const StringBase<char> *name = (const StringBase<char> *)((const char *)data + 0x88);
	if (name->isEmpty())
		return;
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C3B17(loc);
}

// Native 4C4C99..4C4D22 and 4C4E93..4C4F1C: paired weather FX helpers.
// WB12611A0 proves the weather2 path and map-centre/local-height geometry.
// The original helper names remain unknown. Native supplies FX+80, state+10,
// terrain slot20 and the shared half literal; the point lives through one FX
// call. Expressing its initialization as a temporary preserves native argument
// scheduling. No global address alias or canonical-header change is needed.
struct WeatherPoint : Coord3D
{
 __forceinline WeatherPoint(float xCoord, float yCoord, float zCoord) { x = xCoord; y = yCoord; z = zCoord; }
};
struct GlobalWeatherState
{
 unsigned char m_pad00[0x10];
 int m_currentWeather;
};
class GlobalWeatherSystem;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual float getGroundHeight( float x, float y, Coord3D *normal ) const;
	virtual void v07();
	virtual void getExtent( Region3D *extent ) const;
	void addTree(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva00280176(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva0027D3D9(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva0027F28E(const Coord3D *loc, float radius, int flag);
	void rva0027D1A4(const Coord3D *loc, float radius, int flag);
};
extern TerrainLogic *TheTerrainLogic;
class Matrix3D;
class FXList
{
public:
	static void doFXPos( const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx = 0, const float primarySpeed = 0.0f, const Coord3D *secondary = 0 );
};
struct DarknessSpecialPowerFXData
{
 unsigned char m_pad00[0x80];
 const FXList *m_fx;
};

void FreezingRainSpecialPower::rva004C4C99(const Coord3D *loc)
{
 if (((const GlobalWeatherState *)TheGlobalWeatherSystem)->m_currentWeather == 2)
  return;
 const FreezingRainSpecialPowerModuleData *data = getData();
 if (data->m_freezingRainFX == 0)
  return;
 Region3D extent;
 TheTerrainLogic->getExtent(&extent);
 FXList::doFXPos(data->m_freezingRainFX,
  &WeatherPoint((extent.lo.x + extent.hi.x) * 0.5f,
   (extent.lo.y + extent.hi.y) * 0.5f, loc->z), 0, 0.0f, 0);
}

void DarknessSpecialPower::rva004C4E93(const Coord3D *loc)
{
 if (((const GlobalWeatherState *)TheGlobalWeatherSystem)->m_currentWeather == 1)
  return;
 const DarknessSpecialPowerFXData *data = (const DarknessSpecialPowerFXData *)m_moduleData;
 if (data->m_fx == 0)
  return;
 Region3D extent;
 TheTerrainLogic->getExtent(&extent);
 FXList::doFXPos(data->m_fx,
  &WeatherPoint((extent.lo.x + extent.hi.x) * 0.5f,
   (extent.lo.y + extent.hi.y) * 0.5f, loc->z), 0, 0.0f, 0);
}
