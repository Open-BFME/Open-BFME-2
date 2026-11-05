// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// AIWanderInPlaceState::onEnter, retail 0x0034F2F7 (244 bytes), and
// AIWanderInPlaceState::update, retail 0x0034F3EB (282 bytes): slots 4 and 6
// of the AIWanderInPlaceState vtable 0x00C12AC8 (slot 5 is the rowed onExit
// 0x0034A364, slot 3 the rowed xfer 0x003411BD), adjacent in retail.
//
// Donor: Zero Hour AIStates.cpp AIWanderInPlaceState::onEnter/update. onEnter
// records the origin, picks the wander locomotor set (AI vslot 142), offsets
// the goal by random cells (AIStates.cpp lines 10700/10701), clears the timer
// (+0x5C) and sets the wait frames (+0x58) to 10 + (id & 7) before the base
// onEnter; retail clears the timer before the goal copy (the store sits ahead
// of the second conversion). Target facts for update:
// the base update and onEnter are the pinned AIInternalMoveToState bodies
// (0x00347460, 0x0034C146); a CAN_BE_REPULSED owner (template kind byte +0x10D
// bit 5) counts its timer (+0x5C) down and, at zero, reloads it from +0x58 and
// fails when TheAI finds a repulsor within the owner's vision range; a
// finished move picks a new goal around the origin (+0x4C) at random cell
// offsets of the current locomotor's wander radius, passing AIStates.cpp
// lines 10739/10740 to the random source, then re-enters the base move.
// Codegen: BFME 2's int cell size (imul 10, then cvtsi2ss); the goal's x and
// y are read into temporaries before either sum is stored, which is what lets
// retail compute both adds before the two stores.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;

#define PATHFIND_CELL_SIZE 10
#define PATHFIND_CELL_SIZE_F 10.0f

static __forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}
static __forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AISTATES_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp"
// Retail passes AIStates.cpp's own line numbers.
#define GameLogicRandomValueAt(low, high, line) GetGameLogicRandomValue(low, high, AISTATES_FILE, line)

#include "../../../Include/GameLogic/LocomotorClass.h"
#include "../../../Include/GameLogic/LocomotorTemplate.h"
enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_WANDER = 3
};
template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../Include/Common/ThingTemplate.h"
// The can-be-repulsed test reads kind-mask bit 45 (+0x108 byte 5, mask 0x20).
static __forceinline Bool isKindOfCanBeRepulsed(const ThingTemplate *tmpl)
{
	return (((const unsigned char *)tmpl->m_kindof)[5] & 0x20) != 0;
}
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	int getID() const { return m_id; }
	Real getVisionRange() const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	int m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
};
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;
#include "../../../Include/Common/StateMachineClass.h"
#include "../../../Include/GameLogic/AIInternalMoveToState.h"
class AIWanderInPlaceState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	Coord3D m_origin; // +0x4C
	Int m_waitFrames; // +0x58
	Int m_timer; // +0x5C
};

StateReturnType AIWanderInPlaceState::onEnter()
{
	m_origin = *getMachineOwner()->getPosition();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai)
		ai->chooseLocomotorSet(LOCOMOTORSET_WANDER);
	Int delta = 3;
	if (ai->getCurLocomotor())
		delta = REAL_TO_INT_FLOOR((ai->getCurLocomotor()->m_template->m_wanderAboutPointRadius / PATHFIND_CELL_SIZE_F) + 0.5f);
	Coord3D offset;
	offset.x = GameLogicRandomValueAt(-delta, delta, 10700) * PATHFIND_CELL_SIZE;
	offset.y = GameLogicRandomValueAt(-delta, delta, 10701) * PATHFIND_CELL_SIZE;
	m_timer = 0;
	m_goalPosition = m_origin;
	m_goalPosition.x += offset.x;
	m_goalPosition.y += offset.y;
	m_waitFrames = 10 + (getMachineOwner()->getID() & 0x7);
	StateReturnType ret = AIInternalMoveToState::onEnter();
	return ret;
}

StateReturnType AIWanderInPlaceState::update()
{
	StateReturnType status = AIInternalMoveToState::update();
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!ai)
		return STATE_FAILURE;
	if (isKindOfCanBeRepulsed(obj->getTemplate()))
	{
		m_timer--;
		if (m_timer < 0)
		{
			m_timer = m_waitFrames;
			Object *enemy = TheAI->findClosestRepulsor(getMachineOwner(), obj->getVisionRange());
			if (enemy)
				return STATE_FAILURE;
		}
	}
	if (status != STATE_CONTINUE)
	{
		Int delta = 3;
		if (ai->getCurLocomotor())
			delta = REAL_TO_INT_FLOOR((ai->getCurLocomotor()->m_template->m_wanderAboutPointRadius / PATHFIND_CELL_SIZE_F) + 0.5f);
		Coord3D offset;
		offset.x = GameLogicRandomValueAt(-delta, delta, 10739) * PATHFIND_CELL_SIZE;
		offset.y = GameLogicRandomValueAt(-delta, delta, 10740) * PATHFIND_CELL_SIZE;
		m_goalPosition = m_origin;
		Real gx = m_goalPosition.x;
		Real gy = m_goalPosition.y;
		m_goalPosition.x = gx + offset.x;
		m_goalPosition.y = gy + offset.y;
		AIInternalMoveToState::onEnter();
		return STATE_CONTINUE;
	}
	return STATE_CONTINUE;
}
