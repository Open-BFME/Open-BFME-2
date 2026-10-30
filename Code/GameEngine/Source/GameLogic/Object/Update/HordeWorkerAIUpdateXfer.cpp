// cl: /DNDEBUG /MD
//
// ?xfer@HordeWorkerAIUpdate@@MAEXPAVXfer@@@Z, retail 0x0049AE07, 87 bytes.
// Slot 3 of ??_7HordeWorkerAIUpdate 0x00C508C8 (slot-2 name getter returns
// "HordeWorkerAIUpdate"; the rowed dtor 0x0049AC94 installs it). Version1,
// the rowed TransportAIUpdate::xfer 0x0049060D, three ObjectIDs at
// +0x3E8/+0x3EC/+0x3F0 and a bool at +0x3F4. Member names not recovered.

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
#include "../../../Common/GameLogicObjectLookupView.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class TransportAIUpdate
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x3E8 - 0x04];
};

class HordeWorkerAIUpdate : public TransportAIUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_3E8;
	ObjectID m_3EC;
	ObjectID m_3F0;
	bool m_3F4;
};

// ?xfer@HordeWorkerAIUpdate@@MAEXPAVXfer@@@Z @0x0049AE07
void HordeWorkerAIUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	TransportAIUpdate::xfer(xfer);
	XferObjectID(xfer, &m_3E8);
	XferObjectID(xfer, &m_3EC);
	XferObjectID(xfer, &m_3F0);
	*xfer == m_3F4;
}
