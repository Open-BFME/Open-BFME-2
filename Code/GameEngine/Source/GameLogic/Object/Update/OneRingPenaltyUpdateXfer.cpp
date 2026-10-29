// cl: /DNDEBUG /MD

// ?xfer@OneRingPenaltyUpdate@@MAEXPAVXfer@@@Z, retail 0x0049995A, 82 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00850260 installed by the rowed ctor
// 0x00499A70 (news 0x34). Base UpdateModule xfer via rowed 0x0044DF9F then
// IsLightCRC early-out via Xfer slot 0x10 then Version1 via rowed 0x000053EE
// then ObjectID at +0x24 via rowed XferObjectID 0x003060B2 plus uint at +0x28
// via Xfer slot 0x78 plus float at +0x2C via Xfer slot 0x70 plus uint at +0x30
// via Xfer slot 0x78. Layout is the rowed 0x34-byte class from
// OneRingPenaltyUpdateCtor.cpp (UpdateModule base 0x20 plus trailing +0x20
// plus ObjectID uint float uint). Recipe is the DestroyEnvironmentUpdateXfer
// slot-3 pattern.

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

class OneRingPenaltyUpdate : public UpdateModule
{
public:
	OneRingPenaltyUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	const void *m_20;
	ObjectID m_objectID;
	unsigned int m_28;
	float m_2C;
	unsigned int m_30;
};

void OneRingPenaltyUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	XferObjectID(xfer, &m_objectID);
	*xfer == m_28;
	*xfer == m_2C;
	*xfer == m_30;
}
