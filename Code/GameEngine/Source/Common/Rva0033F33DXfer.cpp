// cl: /MD
//
// ?xfer@AIBackAwayAndCowerState@@MAEXPAVXfer@@@Z retail 0x0034027D 30B slot 3.
// Evidence: vtable 0x00810EE0 slot 3; Version1 via rowed 0x000053EE;
// member +0x20 via Xfer slot 0x30 (Snapshot); ctor 0x0033F33D m_20 zero;
// dtor 0x003401E4 member delete.
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

#include "../../Include/Common/StateMachineClass.h"

class AIBackAwayAndCowerState : public State
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	StateMachine *m_20;
};

void AIBackAwayAndCowerState::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == *m_20;
}
