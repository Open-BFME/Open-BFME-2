// cl: /MD /Ireference/shims/moduledata
//
// ?xfer@GiantBirdAttackMoveToState@@MAEXPAVXfer@@@Z, retail 0x0036788E, 72 bytes.
//
// Slot 3 (offset 0xC) of vtable 0x00817548 (GiantBirdAttackMoveToState; dtor in
// Rva0036783FDtor.cpp). Version1 via rowed 0x000053EE then base
// Rva0055CA8A::xfer via rowed 0x0055CA8A then IsLightCRC guard then int at
// +0x2C via Xfer slot 0x7C then Snapshot at +0x28 via slot 0x30 then
// CommandSourceType at +0x24 via rowed XferCommandSourceType 0x00305C02.
// Layout: State base 0x20 plus bool at +0x20 (base xfer) plus ints at +0x24
// and +0x2C plus Snapshot pointer at +0x28. Precedent Rva00367647Xfer.cpp
// (int 0x7C bool 0x90) and Rva0055CA8AXfer.cpp (State plus m_20).
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
class DamageInfo;

#include "../../Include/Common/BfmeXfer.h"

#include "Common/Snapshot.h"

class StateMachine;

#include "../../Include/Common/StateMachine.h"

class Rva0055CA8A : public State
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	bool m_20;
};

class GiantBirdAttackMoveToState : public Rva0055CA8A
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_24;
	Snapshot *m_28;
	int m_2C;
};

void XferCommandSourceType(Xfer *xfer, int *value);

void GiantBirdAttackMoveToState::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva0055CA8A::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_2C;
	*xfer == *m_28;
	XferCommandSourceType(xfer, &m_24);
}
