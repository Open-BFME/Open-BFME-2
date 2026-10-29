// cl: /MD
//
// ?xfer@Rva0048D742@@MAEXPAVXfer@@@Z, retail 0x0048DBC4, 42 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0084C770 (class of rowed dtor ??1Rva0048D742
// at 0x0048D742). Version1 via rowed 0x000053EE then base UpdateModule xfer
// via rowed 0x0044DF9F then bool at +0x20 via Xfer slot 0x90. Layout is
// UpdateModule base 0x20 plus m_flag20 at +0x20. Recipe follows
// DemoTrapUpdateXfer (Version1 plus base plus member runs) and
// DeletionUpdateXfer (frameless single-member shape).

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

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "../../Include/Common/ObjectModule.h"

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

class Rva0048D742 : public UpdateModule
{
public:
	Rva0048D742(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_flag20;
};

void Rva0048D742::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_flag20;
}
