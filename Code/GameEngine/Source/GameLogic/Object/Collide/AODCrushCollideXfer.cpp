// cl: /DNDEBUG /MD
//
// ?xfer@AODCrushCollide@@MAEXPAVXfer@@@Z, retail 0x004BBF03, 65 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0085A31C (class of rowed dtor
// ??1AODCrushCollide@@UAE@XZ in AODCrushCollideDtor.cpp). Version1 via rowed
// 0x000053EE, base UpdateModule xfer via rowed 0x0044DF9F, then uint at +0x24
// via Xfer slot 0x78, ObjectID at +0x28 via rowed XferObjectID 0x003060B2,
// bool at +0x2C via Xfer slot 0x90. Layout is the rowed 0x30-byte class from
// AODCrushCollideCtor.cpp (UpdateModule base 0x20 plus trailing vptr at +0x20
// giving +0x24 start plus uint/ObjectID/bool). Donor is BFME1
// AODCrushCollideConstructor.cpp (CrushCollide level adds +0x20 interface
// plus +0x24/+0x28/+0x2C fields). Recipe is the FoundationAIUpdateXfer
// trailing-vptr plus BloodthirstyUpdateXfer ObjectID-bool tail.

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

class CrushTrailing { public: virtual void trailingSlot(); };

class AODCrushCollide : public UpdateModule, public CrushTrailing
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_24;
	ObjectID m_28;
	bool m_2C;
};

void AODCrushCollide::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_24;
	XferObjectID(xfer, &m_28);
	*xfer == m_2C;
}
