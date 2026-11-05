// cl: /DNDEBUG /MD
// ?xfer@Rva00493009@@MAEXPAVXfer@@@Z @0x00493009 151B. versioned xfer
// Version(1,3) via slot 0x28 plus BehaviorModule base via rowed 0x004C9C7D
// plus gated uint at +0x14 plus uints at +0x18/+0x20 plus int at +0x1c
// plus float at +0x24 plus bools at +0x28/+0x30 plus ObjectID at +0x2c
// via rowed XferObjectID 0x003060B2. Evidence: caller 0x004C449E.

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

class BehaviorModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00493009 : public BehaviorModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad04[0x10];

public:
	unsigned int m_14;
	unsigned int m_18;
	int m_1c;
	unsigned int m_20;
	float m_24;
	bool m_28;

private:
	unsigned char m_pad29[3];

public:
	ObjectID m_2c;
	bool m_30;
};

void Rva00493009::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	BehaviorModule::xfer(xfer);
	if (version.m_minimum >= 2) {
		*xfer == m_14;
	}
	*xfer == m_18;
	*xfer == m_1c;
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
	XferObjectID(xfer, &m_2c);
	if (version.m_minimum >= 3) {
		*xfer == m_30;
	}
}
