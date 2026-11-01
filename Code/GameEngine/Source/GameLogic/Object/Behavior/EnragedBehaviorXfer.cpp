// cl: /DNDEBUG /MD
//
// ?xfer@EnragedBehavior@@MAEXPAVXfer@@@Z, retail 0x00459047, 39 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00840FBC: Version1 via rowed 0x000053EE,
// base UpdateModule xfer via rowed 0x0044DF9F, then float at +0x20 via Xfer
// slot 0x70. Layout is the rowed EnragedBehavior class (float m_20).

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

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class EnragedBehavior : public UpdateModule
{
public:
	EnragedBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	float m_20;
};

void EnragedBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_20;
}
