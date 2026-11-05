// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?xfer@Rva00492C59@@MAEXPAVXfer@@@Z 0x00492E10 51B evidence: slot 3 of vtable 0x0084E1A8 class of Rva00492C59 ctor; Version 1 1 via Xfer slot 0x28 plus base SpecialAbilityUpdate xfer rowed 0x0044F996 plus IsCRC slot 0xC; siblings ReplaceObjectUpdateXfer WoundArrowUpdateXfer same recipe
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
#include "../../../../Include/Common/BfmeXfer.h"
#include "../../../../Include/Common/XferVersion.h"
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
class Rva00492C59 : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};
void Rva00492C59::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	SpecialAbilityUpdate::xfer(xfer);
	xfer->IsCRC();
}
