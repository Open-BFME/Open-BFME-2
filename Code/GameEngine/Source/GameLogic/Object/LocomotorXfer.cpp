// cl: /O1 /MD
//
// ?xfer@Locomotor@@MAEXPAVXfer@@@Z, retail 0x00341E2D, 27 bytes: Locomotor's
// snapshot xfer (vtable slot 3, protected virtual as Locomotor.h declares it),
// identical-code-folded with Rva0033F701::xfer (Rva00341E22Xfer.cpp). BFME2's
// Locomotor keeps no xfer state: IsLightCRC early-out via Xfer slot 0x10, then
// Version1 (0x000053EE). Zero Hour's member-by-member body in Locomotor.cpp is
// not retail's. Same flags and Xfer view as the fold owner.

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
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/GameLogic/LocomotorClass.h"

void Locomotor::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
}
