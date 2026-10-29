// cl: /DNDEBUG /MD
//
// ?xfer@ReplenishUnitsBehavior@@MAEXPAVXfer@@@Z, retail 0x00484365, 37 bytes.
// Slot 3 of ??_7ReplenishUnitsBehavior 0x00C4A034 (slot-2 name getter
// returns "ReplenishUnitsBehavior"; installed by the rowed dtor 0x00484161).
// Version1, the rowed UpdateModule::xfer 0x0044DF9F, then the rowed
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

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class ReplenishUnitsBehavior;

class UpgradeMux
{
	friend class ReplenishUnitsBehavior;
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class ReplenishUnitsBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UpgradeMux m_20;
};

// ?xfer@ReplenishUnitsBehavior@@MAEXPAVXfer@@@Z @0x00484365
void ReplenishUnitsBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	m_20.UpgradeMux::upgradeMuxXfer(xfer);
}
