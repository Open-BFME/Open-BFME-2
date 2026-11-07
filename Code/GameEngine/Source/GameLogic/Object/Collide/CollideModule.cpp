// cl: /DNDEBUG /MD
//
// CollideModule's two Snapshot overrides, slots 1 and 3 of its primary table
// VA 0x00C5A130 (installed by the rowed ctor 0x004BB702). Both are bodies
// retail folds with other modules' identical overrides:
//  - loadPostProcess 0x0058B03E: the tail jump to BehaviorModule::loadPostProcess
//    (UpdateModule's, DamageModule's and CreateModule's rows share it);
//  - xfer 0x004CE56D: Version1, then BehaviorModule::xfer 0x004C9C7D
//    (DamageModule's row shares it).
// Donor: Zero Hour GeneralsMD CollideModule.cpp defines exactly these two (and
// crc, which BFME2's Snapshot has no slot for), with these bodies.
// They make the base calls; select the BehaviorModule declarations they need
// (BehaviorModule.h). No BehaviorModule-derived table is emitted here.
#define BFME_BEHAVIORMODULE_LOADPOSTPROCESS
#define BFME_BEHAVIORMODULE_XFER
#include "../../../../Include/GameLogic/Module/CollideModule.h"

// CollideModule::xfer calls Xfer::Version1; keep its operand types beside the include.
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
#include "../../../../Include/Common/BfmeXfer.h"

// Zero Hour's `CollideModule::loadPostProcess() { BehaviorModule::loadPostProcess(); }`.
void CollideModule::loadPostProcess()
{
	BehaviorModule::loadPostProcess();
}

// Zero Hour's `CollideModule::xfer` with its version-1 stream.
void CollideModule::xfer(Xfer *xfer)
{
	xfer->Version1();
	BehaviorModule::xfer(xfer);
}
