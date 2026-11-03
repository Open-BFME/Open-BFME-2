// cl: /MD
// ?xfer@GarrisonObjectGroupOrder@@UAEXPAVXfer@@@Z @0x00546D15 65B evidence: slot 3 of 0x0086A3C4 GarrisonObjectGroupOrder dtor in Rva00548948Derived; base GroupOrder xfer rowed 0x00548AC2 then xferVersion 1-1 then XferObjectID rowed 0x003060B2 for this+0x18 then Xfer slot 0x60 virtual for this+0x1c.
// Proven slot 3 keeps real name xfer; owner GarrisonObjectGroupOrder via vtable.
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	OBJECTID_0 = 0
};


class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Libraries/Include/Lib/Coord3DBase.h"
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};


extern void __cdecl XferObjectID(Xfer *xfer, enum ObjectID *id);

#include "../../../Include/GameLogic/GroupOrder.h"

class GarrisonObjectGroupOrder : public GroupOrder
{
public:
	virtual void xfer(Xfer *xfer);
private:
	enum ObjectID m_18;
	Coord3DBase m_1c;
};

void GarrisonObjectGroupOrder::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	GroupOrder::xfer(xfer);
	*xfer == version;
	XferObjectID(xfer, &m_18);
	*xfer == m_1c;
}
