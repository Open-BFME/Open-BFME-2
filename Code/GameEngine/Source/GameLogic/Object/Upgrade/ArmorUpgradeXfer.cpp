// cl: /MD
//
// ?xfer@ArmorUpgrade@@MAEXPAVXfer@@@Z, retail 0x004B8710, 27 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x008570A0 (class of rowed dtor
// ??1ArmorUpgrade@@MAE@XZ at 0x004B33FD in ArmorUpgradeDtor.cpp): Version1
// via rowed 0x000053EE then base UpgradeModule xfer via rowed 0x004CE3F9.
// Layout is the rowed ctor class (UpgradeModule base 0x1C with no extra
// xferred members). Identity is slot 3 plus the UpgradeModule base call;
// donor is BFME1 StatusBitsUpgrade xfer shape (Version plus base) with
// Version1 helper. Shared by many simple Upgrade vtables via ICF.

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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/GameLogic/Module/UpgradeModule.h"

class ArmorUpgrade : public UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

void ArmorUpgrade::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpgradeModule::xfer(xfer);
}
