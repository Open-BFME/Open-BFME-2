// cl: /DNDEBUG /MD
//
// ?xfer@WallUpgradeUpdate@@MAEXPAVXfer@@@Z, retail 0x004AB273, 95 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00854780 (class of rowed dtor
// ??1Rva004AB246@@UAE@XZ and rowed ctor ??0WallUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// at 0x004AB317). Version(1,1) via Xfer slot 0x28 then base UpdateModule xfer
// via rowed 0x0044DF9F then ObjectID at +0x28 via rowed XferObjectID 0x003060B2
// plus int at +0x2C via Xfer slot 0x7C plus bools at +0x30/+0x31 via Xfer slot
// 0x90. Layout is the rowed 0x34-byte class (UpdateModule base 0x20 plus
// trailing vptrs at +0x20/+0x24 plus m_28/m_2C/m_30/m_31) from
// WallUpgradeUpdateBehaviorCtor.cpp. Recipe is the BloodthirstyUpdateXfer
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

#include "../../../../Include/Common/XferVersion.h"

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class WallUpgradeTrailing1 { public: virtual void trailingSlot1(); };
class WallUpgradeTrailing2 { public: virtual void trailingSlot2(); };

#include "../../../../Include/GameLogic/Module/WallUpgradeUpdate.h"

void WallUpgradeUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	XferObjectID(xfer, &m_28);
	*xfer == m_2C;
	*xfer == m_30;
	*xfer == m_31;
}
