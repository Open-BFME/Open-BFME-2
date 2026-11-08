// cl: /DNDEBUG /MD
//
// ?xfer@BridgeTowerBehavior@@MAEXPAVXfer@@@Z, retail 0x004587CD,
// 62 bytes. Slot 3 (offset 0x0C) of vtable 0x00840D64 (class of rowed ctor
// ??0BridgeTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z in
// BridgeTowerBehaviorCtor.cpp): Version1 via rowed 0x000053EE then base
// BehaviorModule xfer via rowed 0x004C9C7D then IsLightCRC early-out via
// Xfer slot 0x10 then ObjectID at +0x1C via rowed XferObjectID 0x003060B2
// then tower type at +0x20 via rowed XferBridgeTowerType 0x0030609A.
// Layout is the rowed ctor shape (BehaviorModule base 0x10 plus three
// secondary slots at +0x10/+0x14/+0x18 giving +0x1C start); donor is ZH
// BridgeTowerBehavior::xfer (xferVersion plus xferObjectID plus xferUser)
// with BFME2 Version1-first plus light-CRC plus labelled-enum order.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
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
void XferBridgeTowerType(Xfer *xfer, int *value);

// BehaviorModule's xfer is the base call below; no BehaviorModule-derived table is emitted here.
#define BFME_BEHAVIORMODULE_XFER
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class BridgeTowerBehavior : public BehaviorModule
{
public:
	BridgeTowerBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	const void *m_10;
	const void *m_14;
	const void *m_18;
	ObjectID m_bridgeID;	// +0x1C
	int m_type;		// +0x20 BridgeTowerType
};

void BridgeTowerBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	BehaviorModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	XferObjectID(xfer, &m_bridgeID);
	XferBridgeTowerType(xfer, &m_type);
}
