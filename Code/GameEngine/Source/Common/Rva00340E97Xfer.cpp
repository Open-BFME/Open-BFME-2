// cl: /MD
// ?xfer@Rva00345CAB@@MAEXPAVXfer@@@Z @ 0x00340E97 142B: slot 3 xfer of vtable 0x00813548.
// Version(1,2) via Xfer slot 0x28 then base AIInternalMoveToState xfer via rowed 0x0033FF76,
// IsLightCRC via slot 0x10, uint at +0x58 via slot 0x78, int at +0x5C via slot
// 0x7C, Snapshot ptr at +0x54 via slot 0x30, Coord at +0x60 via slot 0x60,
// ObjectID at +0x6C via rowed XferObjectID 0x003060B2, bool at +0x4A via slot
// 0x90, version>=2 int at +0x50 via rowed XferCommandSourceType 0x00305C02.
// Evidence: vtable 0x00813548 slot 3 plus rowed base xfer plus Xfer slots.
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

#include "../../../Libraries/Include/Lib/Coord3DBase.h"

enum ObjectID
{
	OBJECTID_NONE = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);
void XferCommandSourceType(Xfer *xfer, int *value);

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

#include "../../Include/GameLogic/AIInternalMoveToState.h"

class Rva00345CAB : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad4C[0x50 - 0x4C];
	int m_50;
	Snapshot *m_ptr54;
	unsigned int m_58;
	int m_5C;
	Coord3DBase m_60;
	ObjectID m_6C;
};

void Rva00345CAB::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	AIInternalMoveToState::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_58;
	*xfer == m_5C;
	*xfer == *m_ptr54;
	*xfer == m_60;
	XferObjectID(xfer, &m_6C);
	*xfer == m_tryOneMoreRepath;
	if (version.m_minimum >= 2)
		XferCommandSourceType(xfer, &m_50);
}
