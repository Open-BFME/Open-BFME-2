// cl: /MD
//
// ?xfer@Rva003424B1@@MAEXPAVXfer@@@Z, retail 0x003424B1, 81 bytes.
// Chain from 0x0033FF76 (AIInternalMoveToState::xfer). Derived xfer calling
// Xfer::Version1 via rowed 0x000053EE then bools at +0x55/+0x54/+0x4C via
// slot 0x90 then int at +0x50 via slot 0x7C then base AIInternalMoveToState xfer via
// rowed 0x0033FF76 last. Prev/next are Rva00341E22Xfer/Rva00342502Xfer
// (/O1 /MD). Layout is base 0x4C plus bool plus pad plus int plus bools.
// Identity is base-call plus Version1; class stays honest Rva with xfer.

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

#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferVersion.h"

#include "../../Include/GameLogic/AIInternalMoveToState.h"

class Rva003424B1 : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_4C;
	char m_pad4D[0x50 - 0x4D];
	int m_50;
	bool m_54;
	bool m_55;
};

void Rva003424B1::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_55;
	*xfer == m_54;
	*xfer == m_4C;
	*xfer == m_50;
	AIInternalMoveToState::xfer(xfer);
}
