// cl: /MD
//
// ?xfer@QueueProductionExitUpdate@@MAEXPAVXfer@@@Z, retail 0x004A0057, 107 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x008519C8 (class of rowed dtor
// ??1QueueProductionExitUpdate@@MAE@XZ at 0x0049FFF7). Base UpdateModule xfer
// via rowed 0x44DF9F then IsLightCRC early-out via Xfer slot 0x10 then
// Version1 via rowed 0x53EE then uint at +0x24 via Xfer slot 0x78 plus Coord
// at +0x28 via Xfer slot 0x60 plus bool at +0x34 via Xfer slot 0x90 plus float
// at +0x38 via Xfer slot 0x70 plus ObjectID at +0x40 via rowed XferObjectID
// 0x003060B2 plus uint at +0x3C via Xfer slot 0x78 last. Layout is the rowed
// 0x44-byte class from QueueProductionExitUpdateCtor.cpp 0x4A010E (UpdateModule
// base 0x20 plus ExitInterface vptr at +0x20 giving +0x24 start). Donor is ZH
// QueueProductionExitUpdate::xfer (5 members) plus BFME2 IsLightCRC and Version1
// order plus new ObjectID member. Recipe is SlowDeathBehaviorXfer slot-3 pattern.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"
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

#include "../../../../Include/Common/BehaviorModuleBase.h"

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


#include "../../../../Include/GameLogic/Module/ExitInterface.h"

class QueueProductionExitUpdate : public UpdateModule, public ExitInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_currentDelay;
	Coord3DBase m_rallyPoint;
	bool m_rallyPointExists;
	unsigned char m_pad35[3];
	float m_creationClearDistance;
	unsigned int m_currentBurstCount;
	ObjectID m_objectID;
};

void QueueProductionExitUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_currentDelay;
	*xfer == m_rallyPoint;
	*xfer == m_rallyPointExists;
	*xfer == m_creationClearDistance;
	XferObjectID(xfer, &m_objectID);
	*xfer == m_currentBurstCount;
}
