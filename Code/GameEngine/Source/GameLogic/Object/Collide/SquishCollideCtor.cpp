// cl: /DNDEBUG /MD
//
// ??0SquishCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004BB9CF, 42 bytes.
// SquishCollide behavior ctor over the rowed CollideModule base (0x4BB702,
// thing plus data), then the class's three vftables: 0x00C5A204 at +0,
// CollideModule's 0x00C5A040 at +0x0C and 0x00C5A1EC at +0x10. The class is
// declared over the canonical CollideModule.h, so the compiler stores the
// vptrs. The name getter 0x004BB962 ("SquishCollide") proves the class; the
// rowed instance factory 0x00250FE6 is the sole raw caller. Donor: BFME1
// SquishCollideConstructor.cpp inits CollideModule directly.
//
// Retail 0x00C5A204 (12 slots): deleting dtor 0x004BB9F9, loadPostProcess
// 0x00497805 (`jmp 0x0058B03E`, CollideModule's own; inherited here), the name
// getter 0x004BB962, xfer 0x0045CE8C (Version1, then CollideModule::xfer; one
// body with BoneFXDamage::xfer), getModuleNameKey 0x004BB98A, then
// CollideModule's slots. 0x00C5A1EC: onCollide 0x004BBA65, then
// CollideModule's five defaults.

#include "../../../../Include/GameLogic/Module/CollideModule.h"

// SquishCollide::xfer calls Xfer::Version1; keep its operand types beside the include.
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
#include "../../../../Include/Common/BfmeXfer.h"

class SquishCollide : public CollideModule
{
public:
	SquishCollide(Thing *thing, const ModuleData *moduleData);
	virtual ~SquishCollide();

	virtual NameKeyType getModuleNameKey() const;
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);

protected:
	virtual void xfer(Xfer *xfer);
};

// ??0SquishCollide@@QAE@PAVThing@@PBVModuleData@@@Z @0x4BB9CF
SquishCollide::SquishCollide(Thing *thing, const ModuleData *moduleData)
	: CollideModule(thing, moduleData)
{
}

// Slot 3 of retail table 0x00C5A204: 0x0045CE8C, Zero Hour's SquishCollide::xfer
// (version 1, then CollideModule::xfer 0x004CE56D). Retail folds it with
// BoneFXDamage::xfer, whose base call lands on the same body.
void SquishCollide::xfer(Xfer *xfer)
{
	xfer->Version1();
	CollideModule::xfer(xfer);
}
