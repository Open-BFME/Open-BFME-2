// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?xfer@ScaleWallSpecialAbilityUpdate@@MAEXPAVXfer@@@Z, retail 0x00494E57, 44 bytes.
// Slot 3 of the vftable 0x00C4EB40 whose slot-2 name getter returns
// "ScaleWallSpecialAbilityUpdate". Version(1,1) then the rowed
// SpecialAbilityUpdate::xfer 0x0044F996. No members of its own.

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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class ScaleWallSpecialAbilityUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

// ?xfer@ScaleWallSpecialAbilityUpdate@@MAEXPAVXfer@@@Z @0x00494E57
void ScaleWallSpecialAbilityUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	SpecialAbilityUpdate::xfer(xfer);
}
