// ?rva00349611@Rva00349611@@QAE?AW4StateReturnType@@XZ
// cl: /O1 /ICode/Libraries/Include/Lib /G7 /arch:SSE /DNDEBUG /MD
//
// Target identity: C12800 vtable slot6 thunk 003497C2 forwards to this complete
// 00349611..003497C2 433-byte body; slot2 getter 00342AD0 returns C12848,
// proving the owner AIAttackMeleeApproachState. Method spelling remains neutral.
// The base goal is +20 and derived previous-victim position is +50, supported
// by the owner's matched neighbours and retail reads/writes, not donor layout.
// ZH AIAttackApproachTargetState::updateInternal guides purpose/control flow;
// target victim/status/weapon/pathfinder spine and +90/+94 distance thresholds
// are independently read from retail. Copy/sub into scalar XYZ then constructing
// the 2D local restores all native coordinate and AIData load scheduling.
// Volatile access view for the +90 read preserves native FLD90/FADD94.
// This records observed load order rather than a donor storage qualifier.
// No pin or retail method-name claim.
#include "Coord3D.h"

struct ApproachCoordCopy:Coord3D{__forceinline ApproachCoordCopy(float X,float Y,float Z){x=X;y=Y;z=Z;} __forceinline ApproachCoordCopy(const Coord3D&p){x=p.x;y=p.y;z=p.z;} __forceinline void sub(const Coord3D*p){x-=p->x;y-=p->y;z-=p->z;}};
typedef bool Bool;
typedef float Real;


enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

enum ObjectStatusTypes
{
	STATUS_1C = 0x1c,
	STATUS_33 = 0x33
};

class Object;
class Player;

#include "../../../Include/GameLogic/AIPathfind.h"

struct Rva00349611AIData
{
	unsigned char m_pad00[0x90];
	volatile Real m_meleeApproachTolerance; // +0x90
	Real m_meleeApproachDist; // +0x94
};

class AI
{
public:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	Rva00349611AIData *m_aiData; // +0x18
};

extern class AI *TheAI;
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" void __cdecl fprintf(void *stream, const char *format, ...);

#include "../../../Include/GameLogic/Weapon.h"

class AIUpdateInterface;

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, Bool set);
	Player *getControllingPlayer() const;
	Bool rva002943B2(const Player *p);
	Bool rva0029493F(Object *victim, int mode);
	Bool rva0028CECF();	// 0x0028CECF (rowed)
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getObservedAI() const { return m_ai; }

	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai; // +0x258
};

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"

template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};

#include "../../../Include/GameLogic/Module/AIUpdate.h"



#include "../../../Include/GameLogic/AIInternalMoveToState.h"

class Rva00349611 : public AIInternalMoveToState
{
public:
	StateReturnType rva00349611();
	int m_lastRepathFrame; // +0x4C
	Coord3D m_prevVictimPos; // +0x50
	int m_cellX,m_cellY; // +0x5C,+0x60
};

StateReturnType Rva00349611::rva00349611()
{
	Object *source = m_machine->m_owner;
	AIUpdateInterface *ai = source->getObservedAI();
	if (m_machine->isGoalObjectDestroyed())
	{
		ai->notifyVictimIsDead();
		ai->setCurrentVictim(0);
		return STATE_FAILURE;
	}
	source->setStatus(STATUS_1C, false);

	StateReturnType code = STATE_FAILURE;
	Object *victim = m_machine->getGoalObject();
	if (victim)
	{
		if (victim->testStatus(STATUS_33))
			return STATE_FAILURE;
		if (victim->rva002943B2(source->getControllingPlayer()))
			return STATE_FAILURE;
		if (source->rva0029493F(victim, 2) && source->rva0028CECF())
		{
			m_machine->setState(0xe9);
			return STATE_CONTINUE;
		}
		const Weapon *weapon = source->getCurrentWeapon(0);
		if (weapon && weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
		{
			Bool inRange = TheAI->m_pathfinder->rva002ED313(source);
			if (ai->m_path == 0)
				inRange = true;
			if (inRange)
				return STATE_SUCCESS;
		}
		ai->setCurrentVictim(victim);
		if (ai->m_path == 0)
		{
			Coord3D *goal = &m_prevVictimPos;
			*goal = *victim->getPosition();
			ApproachCoordCopy raw(*source->getPosition());raw.sub(goal);float dx=raw.x,dy=raw.y;const Rva00349611AIData*data=TheAI->m_aiData;ApproachCoordCopy delta(dx,dy,0.0f);if (delta.length() < data->m_meleeApproachTolerance + data->m_meleeApproachDist)
				return STATE_SUCCESS;
		}
		if (g_00E03745)
		{
			void *log = theLogicRandomLogFile;
			if (log != 0)
				fprintf(log, "CritterDesync: ComputePath20");
		}
		if (!computePath())
			return STATE_FAILURE;
		code = AIInternalMoveToState::update();
		if (code != STATE_CONTINUE)
			return STATE_SUCCESS;
	}
	return code;
}
