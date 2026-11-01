// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// Retail 0x003063A9, 112 bytes.
// Free Xfer helper for ThingTemplate*: copies the template name at +0x64 or
// the empty string, xfers it as AsciiString (Xfer slot 0x6c), and on load
// looks it up via the factory at 0x009FF000 (rowed 0x002D06CA).
// Evidence: callers WorkOrder::xfer 0x004F073B and Rva00468FB4 0x00468FC5;
// immediates AsciiString::TheEmptyString 0x009E0878 and g_009FF000;
// callees StringBase copy 0x000365F0, Xfer slots 0x6c/0x4, factory 0x002D06CA,
// releaseBuffer 0x00036410; LINK BONUS 2 files.
#include "ascii_string.h"

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

#include "../../../Include/Common/ThingTemplate.h"

#include "../../../Include/Common/ThingFactory.h"
extern class ThingFactory *TheThingFactory;

void Rva003063A9XferThingTemplate(Xfer *xfer, const ThingTemplate **thing)
{
	AsciiString tmp = (*thing ? *(const AsciiString *)((const char *)*thing + 0x64) : AsciiString::TheEmptyString);
	xfer->operator==(tmp);
	if (!xfer->IsLoading())
		return;
	*thing = TheThingFactory->findTemplate(tmp);
}
