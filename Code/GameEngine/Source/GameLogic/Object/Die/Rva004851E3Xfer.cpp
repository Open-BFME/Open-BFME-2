// cl: /MD
//
// ?xfer@Rva004851E3@@MAEXPAVXfer@@@Z, retail 0x004851E3 27B: Version1 plus base CreateModule xfer.
// Evidence: slot 3 of 8 vtables including Create subclasses; rowed Version1 0x000053EE plus rowed CreateModule xfer 0x004B8D4E; no members.
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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/GameLogic/Module/CreateModuleClass.h"

class Rva004851E3 : public CreateModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva004851E3::xfer(Xfer *xfer)
{
	xfer->Version1();
	CreateModule::xfer(xfer);
}
