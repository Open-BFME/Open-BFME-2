// cl: /MD
//
// ?xfer@Rva00341930@@MAEXPAVXfer@@@Z,
// retail 0x00341930, 73 bytes. Dedicated TU.
// Version(1,2) via Xfer slot 0x28 then base AIInternalMoveToState xfer via rowed
// 0x0033FF76 then ObjectID at +0x4C via rowed XferObjectID 0x003060B2
// then version>=2 uint at +0x50 via Xfer slot 0x78. Prev is our
// Rva00341557 (/O1 /MD) and next is Rva0049B47CDerived (/O1 /MD).
// Identity is base-call plus Version plus ObjectID; class stays honest Rva.

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

#include "../../Include/GameLogic/AIInternalMoveToState.h"

class Rva00341930 : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_4C;
	unsigned int m_50;
};

// ?xfer@Rva00341930@@MAEXPAVXfer@@@Z
void Rva00341930::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	AIInternalMoveToState::xfer(xfer);
	XferObjectID(xfer, &m_4C);
	if (version.m_minimum >= 2) {
		*xfer == m_50;
	}
}
