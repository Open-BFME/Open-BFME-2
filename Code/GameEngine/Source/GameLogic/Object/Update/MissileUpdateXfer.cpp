// cl: /DNDEBUG /MD
//
// ?xfer@MissileUpdate@@MAEXPAVXfer@@@Z, retail 0x004A796A, 284 bytes.
// Slot 3 of ??_7MissileUpdate 0x00C5362C (slot-2 name getter returns
// "MissileUpdate"; installed by the rowed ctor 0x004A75B9). Version(1,1),
// the pinned BezierProjectileBehavior::xfer 0x0045CA8E, then the members in
// retail's order: Coord3Ds at +0xA0 and +0xB8 (the latter zeroed on load),
// an unsigned int at +0x8C, ObjectIDs at +0x90 and +0x94, a bool at +0xCD,
// an unsigned int at +0x98, a float at +0x9C, bools at +0xCE and +0xCC, a
// Coord3D at +0xAC, an unsigned int at +0xC4, and four raw bytes each at
// +0x88 and +0xC8 (Xfer slot 0x24). Member names not recovered.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
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

#include "../../../../../Libraries/Include/Lib/Coord3DInline.h"
#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class BezierProjectileBehavior
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x88 - 0x04];
};

class MissileUpdate : public BezierProjectileBehavior
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_88;
	unsigned int m_frame;
	ObjectID m_90; // +0x90 (launcher)
	ObjectID m_94; // +0x94 (victim)
	unsigned int m_98;
	float m_9C;
	Coord3D m_velA; // +0xA0
	Coord3D m_prevPos; // +0xAC
	Coord3D m_velB; // +0xB8
	unsigned int m_C4;
	int m_C8;
	bool m_CC;
	bool m_CD;
	bool m_CE;
};

// ?xfer@MissileUpdate@@MAEXPAVXfer@@@Z @0x004A796A
void MissileUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;

	BezierProjectileBehavior::xfer(xfer);

	*xfer == asBase(m_velA);
	*xfer == asBase(m_velB);
	if (xfer->IsLoading())
		m_velB.zero();
	*xfer == m_frame;
	XferObjectID(xfer, &m_90);
	XferObjectID(xfer, &m_94);
	*xfer == m_CD;
	*xfer == m_98;
	*xfer == m_9C;
	*xfer == m_CE;
	*xfer == m_CC;
	*xfer == asBase(m_prevPos);
	*xfer == m_C4;
	xfer->XferRawBytes(&m_88, sizeof(m_88));
	xfer->XferRawBytes(&m_C8, sizeof(m_C8));
}
