// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /O1 /G7 /arch:SSE
// AIAttackState::~AIAttackState, retail 0x0034B178 (113 bytes, EH; the opaque
// pin ??1Rva0034B178 stays). Destructor-only view of the class
// Rva0034B0DDFinish.cpp builds (State base with its dtor out of line at
// 0x0049B47C, NotifyWeaponFiredInterface at +0x20, attack machine at +0x24,
// locked weapon name at +0x3C). ZH AIAttackState::~AIAttackState halts and
// deleteInstance()s the attack machine; retail reloads the pointer after the
// halt() call (vslot 15) and calls the machine's slot 0 with flag 0, handing
// its return to operator delete, so slot 0 is modelled as destroy(flag).
#include "ascii_string.h"

void __cdecl operator delete(void *block);

class StateMachine
{
public:
	virtual void *destroy(int flag);
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void halt();
};
class AttackExitConditionsInterface;
class Team;
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
private:
	unsigned char m_head[0x1c];
};
class NotifyWeaponFiredInterface
{
public:
	virtual void notifyFired() = 0;
};
class AIAttackState : public State, public NotifyWeaponFiredInterface
{
public:
	virtual ~AIAttackState();
	virtual void notifyFired();
private:
	StateMachine *m_attackMachine;
	AttackExitConditionsInterface *m_attackParameters;
	Team *m_victimTeam;
	float m_originalVictimPos[3];
	AsciiString m_lockedWeaponOnEnter;
	bool m_follow;
	bool m_isAttackingObject;
	bool m_isForceAttacking;
	unsigned char m_pad47;
	unsigned int m_bfmeAttackState48;
	bool m_bfmeAttackState4C;
	bool m_bfmeAttackState4D;
	unsigned char m_pad4E[2];
	unsigned int m_attackMachineType;
};

AIAttackState::~AIAttackState()
{
	if (m_attackMachine)
	{
		m_attackMachine->halt();
		operator delete(m_attackMachine ? m_attackMachine->destroy(0) : 0);
		m_attackMachine = 0;
	}
}
