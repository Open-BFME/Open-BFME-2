// cl: /DNDEBUG /MD
// AIMoveToAndEvacuateState::onEnter, retail 0x003500E6 (103 bytes): slot 4
// of vtable 0x00C12D50; subtracts owner position from the stored goal, calls
// Rva0033FA64Do(owner), then runs AIMoveToState::onEnter when length exceeds INV.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

inline Coord3D operator-(const Coord3D &a, const Coord3D &b)
{
	Coord3D result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

#include "../Object/object.h"

class Object0033FA64;
void Rva0033FA64Do(const Object0033FA64 *obj);

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"


#include "../../../Include/GameLogic/AIInternalMoveToState.h"

class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

class AIMoveToAndEvacuateState : public AIMoveToState
{
public:
	virtual StateReturnType onEnter();
};

extern "C" float INV;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

StateReturnType AIMoveToAndEvacuateState::onEnter()
{
	Object *owner = getMachineOwner();
	const Coord3D *pos = owner->getPosition();
	float goalX = m_goalPosition.x;
	float goalY = m_goalPosition.y;
	float goalZ = m_goalPosition.z;
	// Retail loads all three goal components before subtracting owner position.
	_ReadWriteBarrier();
	float dx = goalX - pos->x;
	float dy = goalY - pos->y;
	float dz = goalZ - pos->z;
	// Keep the three arithmetic results live until the target's grouped stores.
	_ReadWriteBarrier();
	Coord3D delta;
	delta.x = dx;
	delta.y = dy;
	delta.z = dz;
	Rva0033FA64Do((const Object0033FA64 *)owner);
	if (delta.length() > INV)
		return AIMoveToState::onEnter();
	return STATE_CONTINUE;
}
