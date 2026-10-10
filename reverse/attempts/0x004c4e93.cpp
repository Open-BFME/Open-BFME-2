// ?rva004C4E93@DarknessSpecialPower@@QAEXPBUCoord3D@@@Z
// partial score=0.99 date=2026-10-10
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
//
// The two weather placement helpers share one shape (137 bytes each, only the
// weather-state constant differs): while the global weather state is not
// already the power's own (2 observed for FreezingRain, 1 for Darkness) and
// the module data names an FX list at +0x80, fetch the map extent through
// TerrainLogic slot 8 (getExtent, Region3D), halve the diagonal into a
// position at the location's height, and play the FX there through the rowed
// FXList::doFXPos. The 0.5 factor is the shared .rdata float at 0x00BC26F0.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

extern const float g_00BC26F0;

template <int N> class BitFlags
{
public:
	bool any() const;	// 0x0023C58B for N = 11
private:
	unsigned int m_bits[1];
};

#include "string_base.h"

class Object
{
public:
	bool isDisabled() const { return m_disabledMask.any(); }
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad000[0x38];
	Coord3D m_position;		// +0x38
	unsigned char m_pad044[0x1C8 - 0x44];
	BitFlags<11> m_disabledMask;	// +0x1C8
};

// Object's disabled mask is at +0x1C8. Retail forms its address (and the
// Taint module data's +0x7C name) by adding the offset to the pointer loaded
// straight into ecx (mov ecx, [esi-8] / add ecx, 0x1C8); cl 7.1 emits that for
// byte-pointer arithmetic written in the body, while a typed member access
// or an inline accessor gives lea from another register instead.

class Rva00285D34
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
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
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
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
};

class ElvenWoodSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C3B17(const Coord3D *loc);
};

class FXList;
class Matrix3D;

struct DarknessSpecialPowerModuleData
{
	unsigned char m_pad00[0x80];
	const FXList *m_fx;		// +0x80
};

class DarknessSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C4E93(const Coord3D *loc);
	const DarknessSpecialPowerModuleData *getData() const
	{
		return (const DarknessSpecialPowerModuleData *)m_moduleData;
	}
};

class TaintSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C49AE(const Coord3D *loc);
};

struct FreezingRainSpecialPowerModuleData
{
	unsigned char m_pad00[0x80];
	const FXList *m_fx;		// +0x80
	int m_84;			// +0x84
};

class FreezingRainSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C4C99(const Coord3D *loc);
	const FreezingRainSpecialPowerModuleData *getData() const
	{
		return (const FreezingRainSpecialPowerModuleData *)m_moduleData;
	}
};

class CloudBreakSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C4621(const Coord3D *loc);
	void rva004C4582();
};

// The weather placement helpers read these three singletons. The spellings
// match the census owners of each address (GlobalWeatherSystem.cpp,
// TerrainLogic_setActiveBoundary.cpp, FXListStaticDoFXPos.cpp); the views
// only cover what the helpers touch.
struct GlobalWeatherState
{
	unsigned char m_pad00[0x10];
	int m_state10;		// +0x10
};
class GlobalWeatherSystem;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;

struct Region3D
{
	float lo[3];
	float hi[3];
};

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void getExtent(Region3D *extent) = 0;	// slot 8 (+0x20)
};
extern TerrainLogic *TheTerrainLogic;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *pos, const Matrix3D *mtx, float speed, const Coord3D *secondary);	// 0x00094C29
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
	((Rva00285D34 *)TheTriggerManager)->clear98();
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
	((Rva00285D34 *)TheTriggerManager)->rva00287519(getData()->m_84);
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
	((Rva00285D34 *)TheTriggerManager)->clear98();
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

void FreezingRainSpecialPower::rva004C4C99(const Coord3D *loc)
{
	if (((const GlobalWeatherState *)TheGlobalWeatherSystem)->m_state10 == 2)
		return;
	const FreezingRainSpecialPowerModuleData *data = getData();
	if (data->m_fx == 0)
		return;
	Region3D extent;
	TheTerrainLogic->getExtent(&extent);
	Coord3D pos;
	pos.x = (extent.lo[0] + extent.hi[0]) * g_00BC26F0;
	pos.y = (extent.lo[1] + extent.hi[1]) * g_00BC26F0;
	pos.z = loc->z;
	FXList::doFXPos(data->m_fx, &pos, 0, 0.0f, 0);
}

void DarknessSpecialPower::rva004C4E93(const Coord3D *loc)
{
	if (((const GlobalWeatherState *)TheGlobalWeatherSystem)->m_state10 == 1)
		return;
	const DarknessSpecialPowerModuleData *data = getData();
	if (data->m_fx == 0)
		return;
	Region3D extent;
	TheTerrainLogic->getExtent(&extent);
	Coord3D pos;
	pos.x = (extent.lo[0] + extent.hi[0]) * g_00BC26F0;
	pos.y = (extent.lo[1] + extent.hi[1]) * g_00BC26F0;
	pos.z = loc->z;
	FXList::doFXPos(data->m_fx, &pos, 0, 0.0f, 0);
}

// The 0.5 factor above is the shared .rdata float owned by the FX particle
// system; bind this unit's spelling to it.
#pragma comment(linker, "/alternatename:?g_00BC26F0@@3MB=?g_Va007C26F0@@3MA")
