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
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum StateExitType
{
	EXIT_NORMAL = 0
};
#define IS_STATE_SLEEP(ret) ((int)(ret) > 0)
inline StateReturnType CONVERT_SLEEP_TO_CONTINUE(StateReturnType s)
{
	return IS_STATE_SLEEP(s) ? STATE_CONTINUE : s;
}
class DockUpdateInterface;
class Object;
class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obstacle);
	unsigned char m_pad[0x3BA];
	unsigned char m_canPathThroughUnits; // +0x3BA
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	DockUpdateInterface *getDockUpdateInterface();
	unsigned char m_objectFields00[0x258];
	AIUpdateInterface *m_ai; // +0x258
};
class StateMachine
{
public:
	virtual void slot00();
	Object *getOwner() { return m_owner; }
	Object *getGoalObject();
	unsigned char m_machineFields04[0x10];
	Object *m_owner; // +0x14
};
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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};


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
class State
{
public:
	virtual ~State();
protected:
	virtual void xfer(Xfer *xfer);
	unsigned char m_stateFields04[0x14];
	StateMachine *m_machine; // +0x18
	unsigned char m_stateFields1C[4];
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
		ai->m_canPathThroughUnits = 0;
		ai->ignoreObstacle(0);
	}
}
StateReturnType AIDockState::update()
{
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai)
	{
		ai->m_canPathThroughUnits = 1;
	}
	return CONVERT_SLEEP_TO_CONTINUE(m_dockMachine->updateStateMachine());
}
