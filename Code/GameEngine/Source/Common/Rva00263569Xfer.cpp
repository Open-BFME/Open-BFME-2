// cl: /DNDEBUG /MD
// ?Rva00263569Xfer@@YAPAVXfer@@PAV1@PAH@Z
//
// retail 0x00263569 (89 bytes). Xfer GuardTargetType[2] with version 2 check
// via slot 0x78, throw via bfmeFormatText plus _CxxThrow on version mismatch,
// then loop 2 via XferGuardTargetType. From banked stash 0x00263569 (score
// 0.93): register allocation ebx-vs-edi. Evidence: callee 0x0060C36E rowed
// plus pins 0x00629094 and 0x00305E5A rowed; caller at 0x00268024;
// XferException's throw information in use.
class Xfer;

void __cdecl XferGuardTargetType(Xfer *xfer, int *value);

#include "../../Include/Common/XferException.h"



class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
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

Xfer *__cdecl Rva00263569Xfer(Xfer *xfer, int *values)
{
	int version = 2;
	Xfer *x = xfer;
	(*x == reinterpret_cast<unsigned int &>(version));
	if (version != 2) {
		throw XferException(0, 0);
	}
	int *p = values;
	int count = 2;
	do {
		XferGuardTargetType(x, p);
		++p;
		--count;
	} while (count != 0);
	return x;
}
