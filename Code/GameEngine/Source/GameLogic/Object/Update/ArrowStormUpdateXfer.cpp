// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?xfer@ArrowStormUpdate@@MAEXPAVXfer@@@Z, retail 0x00490C9B, 111 bytes.
// Slot 3 of the vftable 0x00C4D700 whose slot-2 name getter returns
// "ArrowStormUpdate" (the rowed dtor 0x004907C0 installs it). The rowed
// SpecialAbilityUpdate::xfer 0x0044F996 first, the light-CRC out, Version1,
// the ObjectID list at +0x88 (pinned xferSTLObjectIDList 0x00331F2D), an
// ObjectID at +0x8C, an int at +0x90, a bool at +0x98 and an int at +0x94.
// Member names not recovered.

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

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_previous;
	ObjectID m_value;
};

class BridgeBehaviorObjectIDList
{
public:
	void push_back(const ObjectID &value);
	BridgeBehaviorObjectIDNode *m_node;
};

Xfer *xferSTLObjectIDList(Xfer *xfer, BridgeBehaviorObjectIDList *list);

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class ArrowStormUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	BridgeBehaviorObjectIDList m_88;
	ObjectID m_8C;
	int m_90;
	int m_94;
	bool m_98;
};

// ?xfer@ArrowStormUpdate@@MAEXPAVXfer@@@Z @0x00490C9B
void ArrowStormUpdate::xfer(Xfer *xfer)
{
	SpecialAbilityUpdate::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	xfer->Version1();
	xferSTLObjectIDList(xfer, &m_88);
	XferObjectID(xfer, &m_8C);
	*xfer == m_90;
	*xfer == m_98;
	*xfer == m_94;
}
