// cl: /DNDEBUG /MD /GX
// stlport
//
// ?xfer@ObjectModule@@QAEXPAVXfer@@@Z retail 0x00560AE1
// 18 bytes. ObjectModule base xfer terminating the behavior xfer chain
// (BehaviorModule::xfer rowed over its pin; row supersedes that pin here).
// Retail transfers two fixed 1/1 Version pairs back to back; both lower to
// the rowed Version1 helper. Version1 resolves via its row.

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

class ObjectModule
{
public:
	void xfer(Xfer *xfer);
};

// ?xfer@ObjectModule@@QAEXPAVXfer@@@Z @0x00560AE1
void ObjectModule::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->Version1();
}

#include "../../../../Include/Common/DrawableModule.h"

// ?xfer@DrawableModule@@MAEXPAVXfer@@@Z @0x00560AE1: slot 3 of retail's table 0x00C07E54, folded with the above.
void DrawableModule::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->Version1();
}
