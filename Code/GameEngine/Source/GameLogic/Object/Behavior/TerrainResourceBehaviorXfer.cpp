// cl: /MD
//
// ?xfer@TerrainResourceBehavior@@MAEXPAVXfer@@@Z, retail 0x004821CB, 114 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00849408 (class of rowed dtor
// ??1Rva00481F82@@UAE@XZ in Rva00589079Derived.cpp; same primary as rowed ctor
// 0x0048209B which installs 0x00C49408 plus members +0x28/+0x29/+0x2C).
// Base UpdateModule xfer via rowed 0x0044DF9F first, then Version(1,2) via Xfer
// slot 0x28, then gated bools at +0x28/+0x29 via Xfer slot 0x90, then float at
// +0x2C via Xfer slot 0x70, then old-version migration via IsLoading slot 0x04.
// Layout is UpdateModule base 0x20 plus pointers at +0x20/+0x24 plus bools plus
// float, matching the rowed ctor shape. No BFME1 donor (class is BFME2-new).

class AsciiString;
class UnicodeString;
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
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Thing;
class ModuleData;
class Object;
class TerrainResourceBehaviorModuleData;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

// The module data is +0x04, the object is +0x08 and the update interface is +0x10.
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
	__forceinline void wakeNativeObject(Object *object)
	{
		setWakeFrame(object, UPDATE_SLEEP_NONE);
	}
protected:
	virtual void loadPostProcess();
	void setWakeFrame(Object *object, UpdateSleepTime delay);
	const TerrainResourceBehaviorModuleData *getTerrainResourceBehaviorModuleData() const
	{
		return reinterpret_cast<const TerrainResourceBehaviorModuleData *>(m_moduleData);
	}
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class TRB_Iface3 { public: virtual void slot3(); };
class TRB_Iface4 { public: virtual void slot4(); };

class TerrainResourceBehavior : public UpdateModule, public TRB_Iface3, public TRB_Iface4
{
public:
	TerrainResourceBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~TerrainResourceBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	bool m_registered; // +0x28
	bool m_sleepAfterRegister; // +0x29
	float m_incomeScale; // +0x2C
};

void TerrainResourceBehavior::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	Xfer::Version version(1, 2);
	*xfer == version;
	if (version.m_minimum >= 2) {
		*xfer == m_registered;
	}
	*xfer == m_sleepAfterRegister;
	*xfer == m_incomeScale;
	if (version.m_minimum >= 2)
		return;
	if (xfer->IsLoading())
		m_registered = (m_sleepAfterRegister == 0);
}
