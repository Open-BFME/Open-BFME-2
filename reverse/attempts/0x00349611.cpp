// ?rva00349611@Rva00349611@@QAE?AW4StateReturnType@@XZ
// partial score=0.93 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00349611@Rva00349611@@QAE?AW4StateReturnType@@XZ retail
// 0x00349611..0x003497C2 (433 bytes thiscall no args; returns the
// StateReturnType its only caller the slot thunk 0x003497C2 forwards with
// a jmp). An AI attack-approach updateInternal in the shape of Zero Hour's
// AIAttackApproachTargetState::updateInternal and of the matched sibling
// AIAttackPursueTargetState::updateInternal 0x0034939E: on a destroyed goal
// (TurretStateMachine 0x004D7ADD) it notifies the AI (vtable +0x240) and
// clears the victim; else it clears owner status 0x1C and for a live goal
// that is not status 0x33 and passes 0x002943B2 either switches the machine
// (vtable +0x20 state 0xE9) when the owner answers 0x0029493F (victim 2)
// and 0x0028CECF or succeeds in weapon range (0x002CB933) when the
// pathfinder check 0x002ED313 holds or the AI +0x140 is clear; otherwise it
// sets the victim and with +0x140 clear copies the victim position to the
// goal (+0x50) and succeeds inside the AI data +0x90 plus +0x94 of the 2D
// distance; then the CritterDesync ComputePath20 log and computePath
// (vtable +0x44) and AIInternalMoveToState::update 0x00347460. The pinned
// void spelling cannot return the state; the class name stays address-derived.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

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

class Pathfinder
{
public:
	Bool rva002ED313(Object *obj);
};

struct Rva00349611AIData
{
	unsigned char m_pad00[0x90];
	Real m_90; // +0x90
	Real m_94; // +0x94
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

class Weapon
{
public:
	Bool isWithinAttackRange(const Object *source, const Object *target, Real extra, int flag) const;
};

class AIUpdateInterface;

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, Bool set);
	Player *getControllingPlayer() const;
	Bool rva002943B2(const Player *p);
	Bool rva0029493F(Object *victim, int mode);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }

	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai; // +0x258
};

class Rva0028CECFOwner
{
public:
	Bool rva0028CECF();
};

class TurretStateMachine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual StateReturnType setState(int newStateID); // +0x20

	Bool rva004D7ADD();
	Object *getGoalObject();
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};

template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};

class AIUpdateInterface : public AIUpdateSlots<144>
{
public:
	virtual void notifyVictimIsDead() = 0; // +0x240
	void setCurrentVictim(const Object *victim);
	unsigned char m_pad04[0x140 - 0x04];
	int m_140; // +0x140
};

enum StateExitType
{
	EXIT_NORMAL = 0
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
	virtual void slot07();
	virtual Bool isIdle() const;
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual Bool computePath(); // +0x44
public:
	unsigned char m_pad04[0x18 - 0x04];
	TurretStateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual Bool computePath();

	unsigned char m_pad1C[0x50 - 0x1C];
	Coord3D m_goalPosition; // +0x50
};

class Rva00349611 : public AIInternalMoveToState
{
public:
	StateReturnType rva00349611();
};

StateReturnType Rva00349611::rva00349611()
{
	Object *source = m_machine->m_owner;
	AIUpdateInterface *ai = source->getAI();
	if (m_machine->rva004D7ADD())
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
		if (source->rva0029493F(victim, 2) && reinterpret_cast<Rva0028CECFOwner *>(source)->rva0028CECF())
		{
			m_machine->setState(0xe9);
			return STATE_CONTINUE;
		}
		const Weapon *weapon = source->getCurrentWeapon(0);
		if (weapon && weapon->isWithinAttackRange(source, victim, 0.0f, 1))
		{
			Bool inRange = TheAI->m_pathfinder->rva002ED313(source);
			if (ai->m_140 == 0)
				inRange = true;
			if (inRange)
				return STATE_SUCCESS;
		}
		ai->setCurrentVictim(victim);
		if (ai->m_140 == 0)
		{
			Coord3D *goal = &m_goalPosition;
			*goal = *victim->getPosition();
			Coord3D delta = { source->getPosition()->x - goal->x, source->getPosition()->y - goal->y, 0.0f };
			const Rva00349611AIData *data = TheAI->m_aiData;
			if (delta.length() < data->m_90 + data->m_94)
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
