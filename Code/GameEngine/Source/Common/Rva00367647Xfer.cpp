// cl: /MD
// ?xfer@Rva00367647@@MAEXPAVXfer@@@Z @0x00367675 45B
// Slot 3 (offset 0xC) of vtable 0x00817478 (class of ??0Rva00367647@@QAE@PAVStateMachine@@_N@Z).
// Version1 via rowed 0x000053EE then int at +0x20 via Xfer slot 0x7C then bool at +0x24 via Xfer slot 0x90.
// Layout from Rva00367647Ctor.cpp (State base 0x20 plus int 0 at +0x20 plus bool at +0x24).
// Precedent Rva0033F33DXfer.cpp plus FiringTrackerXfer.cpp slot mapping (int 0x7C bool 0x90).
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

class StateMachine;

#include "../../Include/Common/StateMachine.h"

class Rva00367647 : public State
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_20;
	bool m_24;
};

void Rva00367647::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_20;
	*xfer == m_24;
}
