// cl: /DNDEBUG /MD
//
// AIMoveAndDeleteState::update, retail 0x0034A02D (158 bytes): slot 6 of
// vtable 0x00C12C88, whose slot-2 name getter returns AIMoveAndDeleteState;
// the Zero Hour AIStates.cpp update (effectively-dead check, locomotor
// allow-invalid-position on, one-time append of the ground-snapped goal to the
// AI path, pinned base update 0x00347460, destroy the owner when it ends).
// BFME2 layout (target evidence): private status +0x438, AI +0x258 with path
// +0x140, current locomotor +0x1F0 (flags +0x44) and waiting-for-path +0x3B1;
// goal +0x20 and append flag +0x4C; getGroundHeight is TerrainLogic vslot 6;
// appendNode is the rowed Path::appendNode with flags 0x7FFFFFFF.
typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};
enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
class Path
{
public:
	void appendNode(const Coord3D *pos, PathfindLayerEnum layer, int flags);
	void appendNode(const Coord3D *pos, PathfindLayerEnum layer) { appendNode(pos, layer, 0x7fffffff); }
};
class Locomotor
{
public:
	enum LocoFlag
	{
		ALLOW_INVALID_POSITION = 1
	};
	__declspec(dllimport) __forceinline void setAllowInvalidPosition(Bool allow) { setFlag(ALLOW_INVALID_POSITION, allow); }
private:
	void setFlag(LocoFlag f, Bool b)
	{
		if (b)
			m_flags |= (1 << f);
		else
			m_flags &= ~(1 << f);
	}
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};
class AIUpdateInterface
{
public:
	__declspec(dllimport) __forceinline Path *getPath() { return m_path; }
	Bool isWaitingForPath() const { return m_waitingForPath; }
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
private:
	unsigned char m_pad000[0x140];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x1F0 - 0x144];
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3B1 - 0x1F4];
	Bool m_waitingForPath; // +0x3B1
};
#include "../Object/object.h"
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
};
class AIMoveAndDeleteState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
private:
	unsigned char m_pad2C[0x4C - 0x2C];
	Bool m_appendGoalPosition; // +0x4C
};
StateReturnType AIMoveAndDeleteState::update()
{
	Object *obj = getMachine()->getOwner();
	if (obj->isEffectivelyDead())
	{
		return STATE_FAILURE;
	}
	// do movement
	AIUpdateInterface *ai = obj->getAI();
	if (ai->getCurLocomotor())
	{
		ai->getCurLocomotor()->setAllowInvalidPosition(true);
	}
	if (m_appendGoalPosition)
	{
		Path *thePath = ai->getPath();
		if (!ai->isWaitingForPath() && ai->getPath())
		{
			m_goalPosition.z = TheTerrainLogic->getGroundHeight(m_goalPosition.x, m_goalPosition.y);
			thePath->appendNode(&m_goalPosition, LAYER_GROUND);
			m_appendGoalPosition = false; // just did it.
		}
	}
	StateReturnType status = AIInternalMoveToState::update();
	if (status != STATE_CONTINUE)
	{
		Object *obj = getMachineOwner();
		TheGameLogic->destroyObject(obj);
	}
	return status;
}
