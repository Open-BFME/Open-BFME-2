// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// AIDockState::onExit, retail 0x00341723 (77 bytes): slot 5 of vtable
// 0x00C11368, whose slot-2 name getter returns AIDockState.
// Donor: BFME1 game/GameEngine/Source/GameLogic/AI/AIDockState.cpp
// (open-bfme-1 068db38bb4), the Zero Hour AIStates.cpp onExit: halt the dock
// machine (vslot 15), delete it, clear it, then reset the AI's
// can-path-through-units byte and ignoreObstacle(NULL).
// BFME2 deltas (target evidence): the dock machine is at +0x20 (BFME1 +0x24),
// the owner at machine+0x14, the AI at Object+0x258 and its byte at +0x3BA.
// The deletion is a global-scope delete: retail calls vslot 0 with flag 0
// (destroy only) and then ::operator delete on its result, passing NULL when
// the pointer is NULL, which ::delete on a virtual-destructor class emits.
// AIDockState::update, retail 0x00341770 (38 bytes), slot 6: the Zero Hour body
// (setCanPathThroughUnits(true) on the AI, then the dock machine's
// updateStateMachine, vslot 4, with sleeps converted to continue).
// The same address is also slot 6 of the AIHarvestState vtable 0x00C113B8,
// whose other slots are its own (BFME1 derives AIHarvestState from State), so
// the two identical update bodies are folded there; the name here is the
// AIDockState one, whose Zero Hour source this is.
class DockUpdateInterface;
class Object;
#include "../Object/object.h"
#include "../../../Include/Common/StateMachineClass.h"
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
#include "Common/Snapshot.h"
#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../Include/Common/BfmeXfer.h"
#include "../../../Include/Common/StateMachine.h"
#define IS_STATE_SLEEP(ret) ((int)(ret) > 0)
inline StateReturnType CONVERT_SLEEP_TO_CONTINUE(StateReturnType s)
{
	return IS_STATE_SLEEP(s) ? STATE_CONTINUE : s;
}


class AIDockMachine : public Snapshot
{
public:
	AIDockMachine(Object *owner);
	virtual ~AIDockMachine();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
	virtual StateReturnType updateStateMachine();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();
	virtual StateReturnType setState(int id);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(Object *goalObject);
	virtual void halt();
private:
	unsigned char m_machinePad[0x40 - sizeof(Snapshot)];
};

class AIDockState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	Object *getMachineOwner() { return m_machine->getOwner(); }
protected:
	virtual void xfer(Xfer *xfer);
private:
	AIDockMachine *m_dockMachine; // +0x20
	bool m_afterDockMachine; // +0x24
};
void AIDockState::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	xfer->Version1();

	bool hasMachine = m_dockMachine != 0;
	*xfer == hasMachine;

	if (hasMachine && m_dockMachine == 0)
		m_dockMachine = new AIDockMachine(getMachineOwner());

	if (hasMachine)
		*xfer == (Snapshot &)*m_dockMachine;

	*xfer == m_afterDockMachine;
}
StateReturnType AIDockState::onEnter()
{
	Object *dockWithMe = m_machine->getGoalObject();
	if (!dockWithMe)
		return STATE_FAILURE;
	if (!dockWithMe->getDockUpdateInterface())
		return STATE_FAILURE;

	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai)
		ai->ignoreObstacle(dockWithMe);

	m_dockMachine = new AIDockMachine(getMachineOwner());
	m_dockMachine->setGoalObject(dockWithMe);
	return m_dockMachine->initDefaultState();
}
void AIDockState::onExit(StateExitType status)
{
	if (m_dockMachine)
	{
		m_dockMachine->halt();
		::delete m_dockMachine;
		m_dockMachine = 0;
	}
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	if (ai)
	{
		ai->m_field3BA = false;
		ai->ignoreObstacle(0);
	}
}
StateReturnType AIDockState::update()
{
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai)
	{
		ai->m_field3BA = true;
	}
	return CONVERT_SLEEP_TO_CONTINUE(m_dockMachine->updateStateMachine());
}
