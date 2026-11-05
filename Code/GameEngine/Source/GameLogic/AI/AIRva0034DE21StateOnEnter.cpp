// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP=
//
// ?onEnter@Rva0034DE21@@UAE?AW4StateReturnType@@XZ, retail 0x0034DE21
// (189 bytes). An AIInternalMoveToState-derived onEnter (it tail-calls the
// rowed base AIInternalMoveToState::onEnter 0x0034C146) that no retail or
// WorldBuilder code references: no vtable slot and no call site in either
// image so the class name is unknown. WorldBuilder twin 0x00E16F80 (string
// evidence). Body (target evidence):
//  - asks the pathfinder (TheAI +0x10) through the forward 0x002EF3D9 which
//    calls Pathfinder::_GetOverlapUnits (WB name of 0x002EC8C3) with the
//    owner and a 16-pointer buffer;
//  - with no overlap: snaps the owner to its own position through the pinned
//    Object::rva0028ACEE with the rowed layer getter rva0028B511 and when the
//    rowed Object::GetGoalPosition fills the position copies it to the AI
//    (+0x258) field +0x180 and clears AI +0x3B0; returns STATE_FAILURE;
//  - otherwise takes the owner position as the state goal (+0x20) and
//    sets adjusts-destination (+0x48) with the numbered CritterDesync log
//    "setAdjustDestination(TRUE) 37" (string 0x008146D0) before the base
//    onEnter.
// Layout as in the sibling AIMoveAndEvacuateState unit: machine +0x18 and
// owner +0x14; object position +0x38 and AI +0x258.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;


#include <stdio.h>
extern "C" FILE *theLogicRandomLogFile;
extern unsigned char g_00E03745;

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../Object/object.h"

// Retail 0x002EF3D9: forwards (object, object position, buffer) to
// Pathfinder::_GetOverlapUnits.
class Rva002EF3D9Host
{
public:
	int rva002EF3D9(char *record, int arg);
};

class AI
{
public:
	Rva002EF3D9Host *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Rva002EF3D9Host *m_pathfinder; // +0x10
};

extern AI *TheAI;

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"


class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
protected:
	__forceinline void setAdjustsDestination(Bool b)
	{
		if (g_00E03745)
		{
			FILE *log = theLogicRandomLogFile;
			if (log)
				fprintf(log, "CritterDesync: setAdjustDestination(TRUE) 37");
		}
		m_adjustsDestination = b;
	}
	// LINK: same-body helper under a TU-unique name (identical inlined
	// bytes). This TU's setAdjustsDestination copy loses to the first-in-order
	// copy (no retail address); the onEnter call below inlines it but still
	// emits the loser COMDAT. Rebinding there emits only this unique
	// (trivially kept) copy. No flags touched.
	__forceinline void bfme_set_adjusts_destination(Bool b)
	{
		if (g_00E03745)
		{
			FILE *log = theLogicRandomLogFile;
			if (log)
				fprintf(log, "CritterDesync: setAdjustDestination(TRUE) 37");
		}
		m_adjustsDestination = b;
	}
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
};

class Rva0034DE21 : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType Rva0034DE21::onEnter()
{
	Object *obj = getMachineOwner();
	Object *overlaps[16];
	if (!TheAI->pathfinder()->rva002EF3D9((char *)obj, (int)overlaps))
	{
		Coord3D pos;
		pos.x = obj->getPosition()->x;
		pos.y = obj->getPosition()->y;
		pos.z = obj->getPosition()->z;
		obj->rva0028ACEE((int)&pos, obj->rva0028B511());
		if (obj->GetGoalPosition(&pos))
		{
			AIUpdateInterface *ai = obj->getAI();
			ai->m_field180 = pos;
			ai->m_field3B0 = false;
		}
		return STATE_FAILURE;
	}
	m_goalPosition = *obj->getPosition();
	bfme_set_adjusts_destination(true);
	return AIInternalMoveToState::onEnter();
}
