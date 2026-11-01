// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002D342AXfer20@@YAPAVXfer@@PAV1@PA_N@Z @ 0x002D342A 95B
// Free Xfer helper that checks a uint count of 20 through slot 30 then moves twenty bools through slot 36.
// Evidence: same shape as rowed Rva0060BC53Xfer3 0x0060BC53 (uint count check plus loop plus XferException plus bfmeFormatText plus XferException's throw information)
// plus slot map from Xfer.cpp reverse order (slot 30 uint slot 36 bool) plus caller 0x002D64A8 plus prev Rva002D337FThunk /O1 plus next Rva002D3489Find.
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
struct Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
class Snapshot;
struct XferUnknown11;

#include "../../../Include/Common/XferException.h"


#include "../../../Include/Common/BfmeXfer.h"

Xfer *__cdecl Rva002D342AXfer20(Xfer *xfer, bool *data)
{
	unsigned int count = 20;
	xfer->operator==(count);
	if (count != 20)
	{
		throw XferException(0, 0);
	}
	for (unsigned int i = 0; i < 20; ++i)
	{
		xfer->operator==(data[i]);
	}
	return xfer;
}
