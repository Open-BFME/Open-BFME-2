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

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
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

class AutoPickUpUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	const void *m_20;
	unsigned int m_24;
	bool m_28;
	bool m_29;
};

void AutoPickUpUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	UpdateModule::xfer(xfer);
	*xfer == m_24;
	*xfer == m_28;
	if (version.m_minimum >= 2) {
		*xfer == m_29;
	}
}
