// cl: /DNDEBUG /MD
//
// ?xfer@InheritUpgradeCreate@@MAEXPAVXfer@@@Z, retail 0x004B94E3, 37 bytes.
// Slot 3 (offset 0x0C) of vtable 0x008596F4 (class of rowed ctor
// ??0InheritUpgradeCreate@@QAE@PAVThing@@PBVModuleData@@@Z in
// InheritUpgradeCreateCtor.cpp): base CreateModule xfer via rowed 0x4B8D4E
// then Version(1,1) via Xfer slot 0x28. Recipe is the InvisibilityUpdateXfer
// slot-3 pattern with base first then Version.

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

#include "../../../../Include/GameLogic/Module/CreateModuleClass.h"

class InheritUpgradeCreate : public CreateModule
{
public:
	InheritUpgradeCreate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);
};

void InheritUpgradeCreate::xfer(Xfer *xfer)
{
	CreateModule::xfer(xfer);
	Xfer::Version version(1, 1);
	*xfer == version;
}
