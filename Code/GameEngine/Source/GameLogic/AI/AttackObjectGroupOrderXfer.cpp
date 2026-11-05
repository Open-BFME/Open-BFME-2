// cl: /MD
// ?xfer@AttackObjectGroupOrder@@UAEXPAVXfer@@@Z @0x00546FC9 79B evidence: slot 3 of 0x0086A420 AttackObjectGroupOrder; base GroupOrder xfer rowed 0x00548AC2 then xferVersion 1-1 then XferObjectID rowed 0x003060B2 for +0x18 then Xfer slot 0x90 virtual for +0x1c then slot 0x60 for +0x20.
// Proven slot 3 keeps real name xfer; owner AttackObjectGroupOrder via vtable.
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

class Object;

class AttackObjectGroupOrder
{
public:
	virtual ~AttackObjectGroupOrder();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual void rva0054711A(ObjectID id);
	virtual bool Rva0054703E(int dummy);
	virtual void slot06();
	virtual void slot07();
	virtual Coord3D* Rva00547070(int dummy);
	virtual void slot09();
	virtual void slot10();
	virtual bool rva00547099(int *outID, void *out);
	static void rva005470F8(Object *obj, void *userData);
private:
	char m_pad04[0x18 - 4];
	ObjectID m_targetID; // +0x18
	bool m_b1C; // +0x1C
	char m_pad1D[3];
	Coord3D m_pos; // +0x20
};

void AttackObjectGroupOrder::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	reinterpret_cast<GroupOrder *>(this)->GroupOrder::xfer(xfer);
	*xfer == version;
	XferObjectID(xfer, &m_targetID);
	*xfer == m_b1C;
	*xfer == asBase(m_pos);
}
