// cl: /DNDEBUG /MD
// ?xfer@AutoPickUpUpdate@@MAEXPAVXfer@@@Z retail 0x00495C77 89 bytes.
// AutoPickUpUpdate xfer slot 3 offset 0x0C of vtable 0x0084F06C via rowed ctor
// 0x00495D31: Version(1 2) via Xfer slot 0x28 then base UpdateModule xfer via
// rowed 0x0044DF9F then uint at +0x24 via Xfer slot 0x78 then bool at +0x28
// via Xfer slot 0x90 then version-gated bool at +0x29 via slot 0x90 when
// minimum >= 2. Layout is the rowed 0x2C-byte class (UpdateModule base 0x20
// plus ptr at +0x20 giving +0x24 start). Recipe is the BloodthirstyUpdateXfer
// slot-3 Version-first pattern.
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

#include "../../../../Include/Common/ObjectModule.h"

enum NameKeyType;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
struct AutoPickUpUpdateModuleData
{
	char m_pad00[0x10];
	float m_scanDistance;
};

class BehaviorModule : public ObjectModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class AutoPickUpUpdateInterface
{
public:
	virtual void anchor() = 0;
	virtual void slot1() = 0;
	virtual void rva00495C6E() = 0;
};

class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateInterface
{
public:
	AutoPickUpUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AutoPickUpUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void rva00495C6E();
	virtual UpdateSleepTime update();
	bool rva00495DD4();__forceinline float getScanRange()const{return getAutoPickUpUpdateModuleData()->m_scanDistance;}

	const AutoPickUpUpdateModuleData *getAutoPickUpUpdateModuleData() const
	{
		return (const AutoPickUpUpdateModuleData *)m_moduleData;
	}
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_count24;
	bool m_flag28;
	bool m_flag29;
};

void AutoPickUpUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	UpdateModule::xfer(xfer);
	*xfer == m_count24;
	*xfer == m_flag28;
	if (version.m_minimum >= 2) {
		*xfer == m_flag29;
	}
}
