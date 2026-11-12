// cl: /MD
// ?xfer@Rva004DF81B@@QAEXPAVXfer@@@Z, retail 0x004DF81B 27B: slot-3 xfer calls rowed Xfer::Version1 then rowed UpdateModule::xfer.
// Evidence: vslot 3 of 0x007FBCF0 plus 0x0084867C plus 0x0084AF64 plus 0x0084B2F8 plus 0x0084BF90
// plus callers 0x004DE913 0x004DF777 0x004DF88E plus rowed callees 0x000053EE and 0x0044DF9F;
// class unproven so honest Rva name.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/GameLogic/Module/UpdateModule.h"
#include "../../Include/Common/Rva004DF81B.h"

void Rva004DF81B::xfer(Xfer *xfer)
{
	xfer->Version1();
	((UpdateModule *)this)->UpdateModule::xfer(xfer);
}

// ObjectHelper's own slot-1 override, 0x00497805: `jmp 0x0058B03E` to
// UpdateModule::loadPostProcess (slot 1 of ObjectHelper's table 0x00BFBCF0;
// the same 5 bytes serve many module tables, ICF). The derived helpers'
// 0x00483CEF jumps here. This unit is ObjectHelper's xfer (slot 3 above).
#include "../../Include/GameLogic/Module/ObjectHelper.h"

void ObjectHelper::loadPostProcess()
{
	UpdateModule::loadPostProcess();
}

// ObjectHelper's own slot-3 override, 0x004DF81B: the body Rva004DF81B::xfer
// above compiles to (retail folds it across several module tables, ICF), in
// slot 3 of ObjectHelper's table 0x00BFBCF0.
void ObjectHelper::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
}
