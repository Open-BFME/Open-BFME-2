// cl: /DNDEBUG /MD
// ?xfer@W3DPropDraw@@MAEXPAVXfer@@@Z @0x000B221A 27B
// Slot 3 (offset 0x0C) of vtable 0x007CD328 (class of ??0W3DPropDraw@@QAE@PAVThing@@PBVModuleData@@@Z).
// Donor: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDraw.cpp W3DPropDraw::xfer
// (Version then DrawModule::xfer with no data). Retail: Version1 via rowed 0x000053EE then base DrawModule::xfer via rowed 0x004CBF58.
// Also slot 3 of 0x007C98B0 0x007CCCF8 0x007CD178 0x007CD9B8 (ICF fold); primary landed here.

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

#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

#include "../../../../../../GameEngine/Include/Common/XferVersion.h"

class DrawModule;

#include "../../../../../../GameEngine/Include/Common/ObjectModule.h"

#include "../../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"

#include "../../../../../Include/W3DDevice/GameClient/Module/W3DPropDrawClass.h"

void W3DPropDraw::xfer(Xfer *xfer)
{
	xfer->Version1();
	DrawModule::xfer(xfer);
}
