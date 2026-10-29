// cl: /DNDEBUG /MD
//
// ?xfer@PartTheHeavensUpdate@@MAEXPAVXfer@@@Z, retail 0x004ACAAA, 48 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00854DA4 (PartTheHeavensUpdate, same
// primary as rowed ctor 0x004AC998 and dtor 0x004AC8EF); ICF twin slot 3 of
// 0x0084F55C (Rva0049669A opaque). Base UpdateModule xfer via rowed
// 0x0044DF9F, IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, then uint at +0x20 via Xfer slot 0x78. Layout is the rowed
// 0x28-byte class (UpdateModule base 0x20 plus frame at +0x20 plus pointee
// at +0x24, see ctor 0x004AC998 and dtor 0x004AC8EF); only the frame is
// xferred. Recipe is the DestroyEnvironmentUpdateXfer slot-3 pattern
// without the ObjectID tail.

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

class PartTheHeavensUpdate : public UpdateModule
{
public:
	PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_frame;
	int m_spare24;
};

void PartTheHeavensUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_frame;
}
