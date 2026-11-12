// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva004DD619Footprint@@YAPAVXfer@@PAV1@PAH@Z @ 0x004DD619 (30B).
// Free XferEnum helper moving 4 bytes through slot-37 XferEnum with the
// "PathfinderFootprintAngle" label, returning the Xfer for chaining.
// Evidence: string literal in .rdata; slot 0x94 proven by XferEnumHelpers;
// callers at 0x004DD67B plus 0x004DD69E use the return for the next Xfer call.

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

#include "../../../../Libraries/Include/Lib/ICoord3D.h"

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/Region3D.h"

struct IRegion3D
{
	ICoord3D lo;
	ICoord3D hi;
};

#include "../../../../Libraries/Include/Lib/Region2D.h"

#include "../../../../Libraries/Include/Lib/IRegion2D.h"

#include "../../../Include/Common/RealRange.h"

#include "../../../../Libraries/Include/Lib/RGBColor.h"

struct RGBAColorReal
{
	float red;
	float green;
	float blue;
	float alpha;
};

#include "../../../Include/Common/RGBAColorInt.h"

class Xfer;

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

#include "../../../Include/Common/BfmeXfer.h"

Xfer * __cdecl Rva004DD619Footprint(Xfer *xfer, int *value)
{
	xfer->XferEnum("PathfinderFootprintAngle", value, 4);
	return xfer;
}
