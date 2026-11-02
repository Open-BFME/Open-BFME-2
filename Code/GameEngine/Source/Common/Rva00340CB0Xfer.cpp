// cl: /MD
// ?xfer@Rva00340D1F@@MAEXPAVXfer@@@Z @ 0x00340CB0 111B: slot 3 xfer of vtable 0x00810E?? family.
// Version(1,2) via Xfer slot 0x28 then base AIInternalMoveToState xfer via rowed 0x0033FF76,
// IsLightCRC via slot 0x10, int at +0x4C via slot 0x7C, bools at +0x50/+0x51 via
// slot 0x90, version>=2 int at +0x54 via slot 0x7C. Evidence: rowed base xfer
// 0x0033FF76 plus Xfer slots 0x28/0x10/0x7C/0x90 plus caller 0x0034253E.
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

typedef unsigned int AudioHandle;

#include "../../../Libraries/Include/Lib/Coord3DBase.h"

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

#include "../../Include/GameLogic/AIInternalMoveToState.h"

class Rva00340D1F : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_4C;
	bool m_50;
	bool m_51;
	char m_pad52[2];
	int m_54;
};

void Rva00340D1F::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	AIInternalMoveToState::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_4C;
	*xfer == m_50;
	*xfer == m_51;
	if (version.m_minimum >= 2)
		*xfer == m_54;
}
