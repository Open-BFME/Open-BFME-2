// cl: /MD
//
// ?xfer@WallHubBehavior@@MAEXPAVXfer@@@Z, retail 0x00452F25, 44 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0083FDBC (VA 0x00C3FDBC, class of
// rowed dtor ??1Rva00452D52@@UAE@XZ in Rva0024A797Grandchildren.cpp): slot 2
// name getter at 0x00452D72 returns WallHubBehavior, slot 4 pool key at
// 0x00452DA3 is WallHubBehavior pool key, slot 0 deleting dtor at 0x00452EC1.
// Version(1,1) via Xfer slot 0x28 then base UpdateModule xfer via rowed
// 0x0044DF9F. No members and no IsLightCRC early-out in retail. Layout is
// UpdateModule base 0x20. Recipe is the Rva0045B134Xfer Version-first slot-3
// pattern with protected xfer.

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

class WallHubBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

void WallHubBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
}
