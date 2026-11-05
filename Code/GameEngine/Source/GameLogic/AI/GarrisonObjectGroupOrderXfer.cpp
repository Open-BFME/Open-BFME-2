// cl: /MD
// ?xfer@GarrisonObjectGroupOrder@@UAEXPAVXfer@@@Z @0x00546D15 65B evidence: slot 3 of 0x0086A3C4 GarrisonObjectGroupOrder dtor in Rva00548948Derived; base GroupOrder xfer rowed 0x00548AC2 then xferVersion 1-1 then XferObjectID rowed 0x003060B2 for this+0x18 then Xfer slot 0x60 virtual for this+0x1c.
// Proven slot 3 keeps real name xfer; owner GarrisonObjectGroupOrder via vtable.
// Built against the approved TU's class view (GarrisonObjectGroupOrder.cpp):
// the base GroupOrder xfer is reached through the canonical GroupOrder.h, as
// the twin AttackObjectGroupOrder.cpp does.
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum CanEnterType
{
	CHECK_CAPACITY = 0
};

class Drawable;

class Object;

#include "../../../Include/GameLogic/Module/AIUpdate.h"


class Object
{
public:
	Drawable *getDrawable() const;
	ObjectID getID() const { return m_id; }
	char m_pad0[0x38];
	Coord3D m_position; // +0x38
	char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_flags438; // +0x438 bit0
};

class BFMEActionManager
{
public:
	bool canEnterObject(const Object *obj, const Object *objectToEnter, CommandSourceType commandSource,
		CanEnterType mode, bool passThrough, bool *outFlag);
};

class ActionManager;

extern ActionManager *TheActionManager;

extern GameLogic *TheGameLogic;

class Xfer;

// Retail vftable 0x00C6A3C4: slot 3 is xfer (0x00546D15) and slot 4 the
// garrison step 0x00546DD4, as in the twin AttackObjectGroupOrder.cpp.
class GarrisonObjectGroupOrder
{
public:
	virtual ~GarrisonObjectGroupOrder();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual void rva00546DD4(ObjectID id);
	virtual bool rva00546E2E(ObjectID id);
	virtual void slot06();
	virtual void slot07();
	virtual Coord3D *rva00546D7C(int dummy);
	virtual void slot09();
	virtual void slot10();
	virtual bool rva00546DA5(int *outID, void *out);
private:
	char m_pad04[0x18 - 4];
	ObjectID m_targetID; // +0x18
	Coord3D m_pos; // +0x1C
};

typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef unsigned int UnsignedInt;
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

void GarrisonObjectGroupOrder::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	reinterpret_cast<GroupOrder *>(this)->GroupOrder::xfer(xfer);
	*xfer == version;
	XferObjectID(xfer, &m_targetID);
	*xfer == reinterpret_cast<Coord3DBase &>(m_pos);
}
