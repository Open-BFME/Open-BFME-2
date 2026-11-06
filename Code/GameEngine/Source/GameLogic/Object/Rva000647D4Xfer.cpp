// cl: /MD
//
// ?xfer@Rva000647D4@@MAEXPAVXfer@@@Z, retail 0x000647E6, 27 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x007C5A5C (class of rowed dtor
// ??1Rva000647D4@@UAE@XZ in LocomotorDerivedDtors.cpp, same primary; gap
// between 0x000647D4/18 and 0x00064809/28). Body is Version1 via rowed
// 0x000053EE then base Locomotor xfer via pinned 0x00341E2D (ICF twin of
// rowed AIGoingIdleState xfer 27B; IsLightCRC-plus-Version1 root). Identity is
// slot 3 plus the Version1-plus-base shape; flags copy the neighbour
// LocomotorDerivedDtors.cpp (/O1 /MD).

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
#include "../../../Include/Common/BfmeXfer.h"

// The base view only spells the call target. 0x00341E2D is one ICF body
// rowed twice, as AIGoingIdleState::xfer and Locomotor::xfer, so naming the
// AIGoingIdleState row proves no AIGoingIdleState base for this class.
class AIGoingIdleState
{
protected:
	virtual ~AIGoingIdleState();
	virtual void xfer(Xfer *xfer);
};

class Rva000647D4_B
{
public:
	virtual void f();
};

class Rva000647D4 : public AIGoingIdleState, public Rva000647D4_B
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva000647D4::xfer(Xfer *xfer)
{
	xfer->Version1();
	AIGoingIdleState::xfer(xfer);
}
