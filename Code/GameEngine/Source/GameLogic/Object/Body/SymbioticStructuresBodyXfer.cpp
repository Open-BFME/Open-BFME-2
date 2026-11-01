// cl: /DNDEBUG /MD
//
// ?xfer@SymbioticStructuresBody@@MAEXPAVXfer@@@Z, retail 0x004C0A76, 54 bytes.
// Slot 3 of the vftable 0x00C5B830 whose slot-2 name getter returns
// "SymbioticStructuresBody" (the rowed dtor 0x004C0A4C installs it).
// Version1, the rowed ActiveBody::xfer 0x004BF1E8, then outside a light-CRC
// pass the ObjectID at +0x104 (rowed XferObjectID). Member name not
// recovered.

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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class ActiveBody
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x104 - 0x04];
};

class SymbioticStructuresBody : public ActiveBody
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_104;
};

// ?xfer@SymbioticStructuresBody@@MAEXPAVXfer@@@Z @0x004C0A76
void SymbioticStructuresBody::xfer(Xfer *xfer)
{
	xfer->Version1();
	ActiveBody::xfer(xfer);
	if (!xfer->IsLightCRC())
		XferObjectID(xfer, &m_104);
}
