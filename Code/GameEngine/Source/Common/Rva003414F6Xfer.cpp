// cl: /MD
// ?xfer@AIAttackSquadState@@MAEXPAVXfer@@@Z @0x003414F6 97B: AIAttackSquadState xfer slot 3.
// IsLightCRC early-out via slot 0x10 then Version1 via rowed 0x000053EE then bool has=(m_20!=0) via slot 0x90 then lazy create via m_machine slot 0x24 then Snapshot via slot 0x30.
// Precedent Rva0033F33D Snapshot via slot 0x30 plus bool via slot 0x90 shape.
// Vtable 0x008112C0 slot 3.
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
#include "../../Include/Common/BfmeXfer.h"
class StateMachine;
class SnapshotCreator
{
public:
	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
	virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
	virtual void c08();
	virtual Snapshot *createSnapshot();
};
#include "../../Include/Common/StateMachine.h"
#include "../../Include/Common/StateMachineClass.h"
class AIAttackSquadState : public State
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Snapshot *m_20;
};
void AIAttackSquadState::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	bool has = (m_20 != 0);
	*xfer == has;
	if (has) {
		if (m_20 == 0)
			m_20 = (Snapshot *)m_machine->slot09();
		if (has)
			*xfer == *m_20;
	}
}
