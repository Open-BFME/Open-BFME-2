// cl: /O1 /DNDEBUG /MD
//
// ?xfer@GameState@@MAEXPAVXfer@@@Z @0x002DBCCA 31B: GameState::xfer, slot 3
// (Snapshot xfer) of ??_7GameState@@6BRva002DE58DBaseC@@@ 0x0080401C, the only
// table that holds it (this is that Snapshot subobject). Retail calls the pinned 0x00053EE
// on the arg, then invokes vtable slot 12 of the arg with this+0x18. The
// arg class is carried as 12 pure-virtual fillers plus the slot-12 view so
// no dummy definitions are emitted. Honest address-derived names.

// The first call is the rowed Xfer::Version1 (0x000053EE).
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

class Rva002DBCCAArg
{
public:
	void rva000053EE();
	virtual void vf00() = 0;
	virtual void vf01() = 0;
	virtual void vf02() = 0;
	virtual void vf03() = 0;
	virtual void vf04() = 0;
	virtual void vf05() = 0;
	virtual void vf06() = 0;
	virtual void vf07() = 0;
	virtual void vf08() = 0;
	virtual void vf09() = 0;
	virtual void vf10() = 0;
	virtual void vf11() = 0;
	virtual void vf12(void *x);
};

#include "../../Include/Common/GameState.h"

// ?xfer@GameState@@MAEXPAVXfer@@@Z
void GameState::xfer(Xfer *xfer)
{
	xfer->Version1();
	// Retail's this is the Snapshot base at +0xC, so its this+0x18 is GameState+0x24.
	((Rva002DBCCAArg *)xfer)->vf12((char *)this + 0x24);
}
