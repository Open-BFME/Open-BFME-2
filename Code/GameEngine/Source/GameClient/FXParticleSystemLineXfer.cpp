// cl: /MD
// ?rva0055CD38@Rva0055CD38@@UAEXPAVXfer@@@Z at 0x0055CD38 size 56
// Evidence: vslot slot3 of 0x0081D02C and 0x0081C750 Line info; Version1 rowed 0x000053EE plus 3 Xfer slots 0x90/0x60/0x60 over +0x20/+0x24/+0x30; xfer recipe.

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
class Thing;
class ModuleData;
class Object;
class DamageInfo;

#include "../../Include/Common/BfmeXfer.h"
#include "../../../Libraries/Include/Lib/Coord3DBase.h"

class Rva0055CD38
{
public:
	virtual void rva0055CD38(Xfer *xfer);
private:
	char m_pad[0x1C];
	bool m_20;
	Coord3DBase m_startPoint;
	Coord3DBase m_endPoint;
};

void Rva0055CD38::rva0055CD38(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_20;
	*xfer == m_startPoint;
	*xfer == m_endPoint;
}
