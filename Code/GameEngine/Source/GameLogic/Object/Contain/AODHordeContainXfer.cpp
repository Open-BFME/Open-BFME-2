// cl: /DNDEBUG /MD
//
// ?xfer@AODHordeContain@@MAEXPAVXfer@@@Z, retail 0x0047B2FB, 99 bytes.
// Slot 3 of ??_7AODHordeContain 0x00C46D28 (installed by the rowed ctor
// 0x0047B3DB). Version1, the pinned HordeContain::xfer 0x00474EA8, the
// tracked large unit's ObjectID at +0x318 (rowed XferObjectID), the float
// at +0x334, the int at +0x31C, a refresh through the rowed
// refreshTrackedLargeUnit 0x0047B2AA while the ID is set, then the tracked
// position at +0x320. Names from the AODHordeContainRefresh view.

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

#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class HordeContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	unsigned char m_unrecovered04[0x30C - 0x04];
};

class AODHordeContain : public HordeContain
{
public:
	void refreshTrackedLargeUnit();

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_vectorPad[12];
	ObjectID m_trackedLargeUnit;
	unsigned int m_31C;
	Coord3DBase m_trackedPosition;
	float m_largeUnitHeightFactor;
	float m_largeUnitHeight;
	float m_334;
};

// ?xfer@AODHordeContain@@MAEXPAVXfer@@@Z @0x0047B2FB
void AODHordeContain::xfer(Xfer *xfer)
{
	xfer->Version1();
	HordeContain::xfer(xfer);

	XferObjectID(xfer, &m_trackedLargeUnit);
	*xfer == m_334;
	*xfer == m_31C;
	if (m_trackedLargeUnit != INVALID_ID)
		refreshTrackedLargeUnit();
	*xfer == m_trackedPosition;
}
