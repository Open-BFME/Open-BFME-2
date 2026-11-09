// cl: /DNDEBUG /MD
//
// ?xfer@AttributeModifierAuraUpdate@@MAEXPAVXfer@@@Z, retail 0x0049B66B, 67 bytes.
// Slot 3 of the vftable 0x00C50D2C whose slot-2 name getter returns
// "AttributeModifierAuraUpdate". The rowed UpdateModule::xfer 0x0044DF9F,
// the light-CRC out, Version(1,2), then from version 2 the upgrade mux on
// the +0x20 subobject (rowed upgradeMuxXfer 0x004CE397).

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

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"
#include "../../../../Include/GameLogic/Module/AttributeModifierAuraUpdate.h"

// ?xfer@AttributeModifierAuraUpdate@@MAEXPAVXfer@@@Z @0x0049B66B
void AttributeModifierAuraUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	if (version.m_minimum >= 2)
		UpgradeMux::upgradeMuxXfer(xfer);
}
