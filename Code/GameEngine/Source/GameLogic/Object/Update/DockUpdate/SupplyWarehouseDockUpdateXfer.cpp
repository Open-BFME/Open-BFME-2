// cl: /DNDEBUG /MD /EHsc
//
// ?xfer@SupplyWarehouseDockUpdate@@MAEXPAVXfer@@@Z, retail 0x004A7D7B, 42 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00853790 (class of rowed dtor
// ??1SupplyWarehouseDockUpdate@@UAE@XZ in Rva0058A0F4Derived.cpp). Version1 via rowed
// 0x53EE then base DockUpdate xfer via rowed 0x58A410 then int at +0x88 via
// Xfer slot 0x7C. Layout is single inheritance from DockUpdate per ZH donor
// (no adjustment) with int m_boxesStored at +0x88 giving 0x8C total (factory
// news 0x8C per SupplyWarehouseDockUpdateFriendNew.cpp). Donor is ZH
// SupplyWarehouseDockUpdate::xfer (Version plus base plus xferInt). Recipe is
// DeletionUpdateXfer slot-3 pattern with DockUpdate base.

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

#include "../../../../../Include/Common/BfmeXfer.h"

#include "SupplyWarehouseDockUpdateNative.h"

void SupplyWarehouseDockUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	DockUpdate::xfer(xfer);
	*xfer == m_boxesStored;
}
