// cl: /DNDEBUG /MD
//
// ?xfer@ReplenishUnitsBehavior@@MAEXPAVXfer@@@Z, retail 0x00484365, 37 bytes.
// Slot 3 of ??_7ReplenishUnitsBehavior 0x00C4A034 (slot-2 name getter
// returns "ReplenishUnitsBehavior"; installed by the rowed dtor 0x00484161).
// Version1, the rowed UpdateModule::xfer 0x0044DF9F, then the rowed
// UpgradeMux::upgradeMuxXfer 0x004CE397 on the +0x20 mux base (the
// same transfer used by AudioLoopUpgradeXfer).

// UpgradeMux::upgradeMuxXfer 0x004CE397 on the +0x20 mux subobject (the
// AudioLoopUpgradeXfer view of the mux as a member).
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

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Thing;
class ModuleData;
class Object;
class Xfer;
class ReplenishUnitsBehaviorModuleData;

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

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class UpgradeMux
{
public:
	UpgradeMux();
	virtual bool isUpgradeActive() const = 0;
	void giveSelfUpgrade();

protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class ReplenishUnitsBehavior : public UpdateModule, public UpgradeMux
{
public:
	ReplenishUnitsBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~ReplenishUnitsBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void rva004842DD(Object *target);

protected:
	virtual void xfer(Xfer *xfer);

private:
	const ReplenishUnitsBehaviorModuleData *getReplenishUnitsBehaviorModuleData() const
	{
		return (const ReplenishUnitsBehaviorModuleData *)m_moduleData;
	}
};

// ?xfer@ReplenishUnitsBehavior@@MAEXPAVXfer@@@Z @0x00484365
void ReplenishUnitsBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	UpgradeMux::upgradeMuxXfer(xfer);
}
