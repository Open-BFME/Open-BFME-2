// cl: /MD
// ?xfer@AIGuardState@@MAEXPAVXfer@@@Z @0x00341D9B 97B: AIGuardState xfer slot 3.
// IsLightCRC early-out via slot 0x10 then Version1 via rowed 0x000053EE then bool has=(m_20!=0) via slot 0x90 then lazy create via m_machine slot 0x28 then Snapshot via slot 0x30.
// Precedent Rva0033F33D Snapshot via slot 0x30 plus bool via slot 0x90 shape.
// Vtable 0x00811740 slot 3.
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
	virtual void c08(); virtual void c09();
	virtual Snapshot *createSnapshot();
};
#include "../../Include/Common/StateMachine.h"
#include "../../Include/Common/StateMachineClass.h"
class AIGuardState : public State
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Snapshot *m_20;
};
void AIGuardState::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	bool hasSnapshot = (m_20 != 0);
	*xfer == hasSnapshot;
	if (hasSnapshot) {
		if (m_20 == 0)
			m_20 = (Snapshot *)m_machine->slot10();
		if (hasSnapshot)
			*xfer == *m_20;
	}
}
