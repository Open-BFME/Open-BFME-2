// cl: /DNDEBUG /MD
//
// ?xfer@DestroyEnvironmentUpdate@@MAEXPAVXfer@@@Z, retail 0x004AC6CB, 60 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00854D64, same primary as rowed ctor
// 0x004AC63A (68B) and poolkey 0x004AC686. Base UpdateModule xfer via rowed
// 0x0044DF9F, IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, then uint at +0x20 via Xfer slot 0x78 plus ObjectID at +0x24
// via rowed XferObjectID 0x003060B2. Layout is the rowed 0x28-byte class
// (UpdateModule base 0x20 plus frame plus ObjectID); BFME1 donor calls the
// second member m_flags but the destructor thunk proves ObjectID so retail
// is followed. Recipe is the RainOfFireUpdateXfer slot-3 pattern.

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

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

class DestroyEnvironmentUpdate : public UpdateModule
{
public:
	DestroyEnvironmentUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_frame;
	ObjectID m_objectID;
};

void DestroyEnvironmentUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_frame;
	XferObjectID(xfer, &m_objectID);
}
