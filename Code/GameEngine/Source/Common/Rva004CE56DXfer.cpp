// cl: /MD
// ?xfer@Rva004CE56D@@QAEXPAVXfer@@@Z, retail 0x004CE56D 27B: slot-3 xfer calls rowed Xfer::Version1 then rowed BehaviorModule::xfer.
// Evidence: vslot 3 for DamageModule/DieModule/WargBehavior/RunOffMapBehavior/CollideModule plus 9 callers incl 0x004BACA4
// plus rowed callees 0x000053EE and 0x004C9C7D; class unproven so honest Rva name.
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
#include "../../Include/Common/BfmeXfer.h"

// The placeholder stands for a fold of several modules' xfer overrides (no
// one class), so it is no BehaviorModule here: it is the base's friend and
// calls the protected virtual base xfer qualified (direct call, same this).
class Rva004CE56D;

class BehaviorModule {
	friend class Rva004CE56D;
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva004CE56D {
public:
	void xfer(Xfer *xfer);
};

void Rva004CE56D::xfer(Xfer *xfer)
{
	xfer->Version1();
	((BehaviorModule *)this)->BehaviorModule::xfer(xfer);
}
