// cl: /DNDEBUG /MD
//
// ?xfer@AnimalAIUpdate@@MAEXPAVXfer@@@Z, retail 0x0047EBAF, 107 bytes.
// Slot 3 of the vftable 0x00C47B98 whose slot-2 name getter returns
// "AnimalAIUpdate" (installed by the rowed dtor 0x0047EB78 and the rowed
// ctor 0x0047ECA8). Version(1,1) through Xfer slot 0x28, the ObjectID at
// +0x3E8 through the rowed XferObjectID, a bool at +0x3F8 (slot 0x90), a
// Coord3D at +0x3EC (slot 0x60), a bool at +0x3F9, then the rowed
// AIUpdateInterface::xfer 0x00267EDD. Member names not recovered.

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

#include "../../../../../Include/Common/BfmeXfer.h"

#include "../../../../../Include/Common/XferVersion.h"

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class AIUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
private:
	char m_unrecovered04[0x3E8 - 0x04];
};

class AnimalAIUpdate : public AIUpdateInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_3E8;
	Coord3DBase m_3EC;
	bool m_3F8;
	bool m_3F9;
};

// ?xfer@AnimalAIUpdate@@MAEXPAVXfer@@@Z @0x0047EBAF
void AnimalAIUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;

	XferObjectID(xfer, &m_3E8);
	*xfer == m_3F8;
	*xfer == m_3EC;
	*xfer == m_3F9;

	AIUpdateInterface::xfer(xfer);
}
