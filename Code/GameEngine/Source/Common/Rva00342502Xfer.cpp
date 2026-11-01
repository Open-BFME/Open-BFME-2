// cl: /MD
//
// ?xfer@Rva00342502@@MAEXPAVXfer@@@Z, retail 0x00342502, 42 bytes.
// Chain from 0x0033FF76 (AIInternalMoveToState::xfer). Derived xfer calling
// Xfer::Version1 via rowed 0x000053EE then base AIInternalMoveToState xfer via rowed
// 0x0033FF76 then bool at +0x4C via Xfer slot 0x90 with add edi tail.
// Prev is Rva00341E22Xfer (/O1 /MD). Layout is base 0x4C plus bool.
// Identity is base-call plus Version1 plus bool; class stays honest Rva
// with proven xfer name like Rva0045ADC1.

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

class AIInternalMoveToState
{
public:
	virtual ~AIInternalMoveToState();

protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[0x4C - 0x04];
};

class Rva00342502 : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_4C;
};

void Rva00342502::xfer(Xfer *xfer)
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	*xfer == m_4C;
}
