// cl: /MD
// ?DoXfer@CellType@PathfindZoneManager@@QAEXPAVXfer@@@Z @ 0x00531978 (204B): __thiscall unpack 20-bit field via Xfer ushort slot 0x80; IsCRC gate slot 0x0C; caller 0x005343BC.
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
#include "../../Include/GameLogic/PathfindZoneManager.h"

void PathfindZoneManager::CellType::DoXfer(Xfer *xfer)
{
	if (!xfer->IsCRC())
		return;
	unsigned short t0 = (unsigned short)(value & 7u);
	*xfer == t0;
	unsigned short t1 = (unsigned short)((value >> 3) & 0x3fu);
	*xfer == t1;
	unsigned short t2 = (unsigned short)((value >> 9) & 0x3fu);
	*xfer == t2;
	unsigned short t3 = (unsigned short)((value >> 15) & 1u);
	*xfer == t3;
	unsigned short t4 = (unsigned short)((value >> 16) & 1u);
	*xfer == t4;
	unsigned short t5 = (unsigned short)((value >> 17) & 3u);
	*xfer == t5;
	unsigned short t6 = (unsigned short)((value >> 19) & 1u);
	*xfer == t6;
}
