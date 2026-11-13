#pragma once
// Native AIAttackState shared view: State at +0, five-slot secondary interface at +0x20,
// attack machine +0x24, parameters +0x28, team +0x2C, position +0x30, string +0x3C,
// flags through +0x49 and machine kind at +0x4C. Complete extent: 0x50 bytes.
// The existing secondary-base label and neutral slot identifiers are retained;
// its original name is not recovered. Slot1 propagates the goal to both machines.
#include "../Common/StateMachine.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3DInline.h"

class AttackExitConditionsInterface;
class Team;

class NotifyWeaponFiredInterface
{
public:
    virtual void notifyFired() = 0;
    virtual void bfmeGoFAC(void *) = 0;
    virtual bool slot2(int) = 0;
    virtual unsigned char slot3() const = 0;
    virtual void *slot4() const = 0;
};

class AIAttackState : public State, public NotifyWeaponFiredInterface
{
public:
	virtual ~AIAttackState();	// rowed out of line; this view must not emit its own
	AIAttackState(StateMachine *machine, bool follow, bool attackingObject, bool forceAttacking,
		AttackExitConditionsInterface *attackParameters);
	virtual bool isAttack() const;
	virtual void notifyFired() {}
    virtual void bfmeGoFAC(void *goal);
    virtual bool slot2(int) { return true; }
    virtual unsigned char slot3() const { return m_isAttackingObject; }
    virtual void *slot4() const { return const_cast<Coord3D *>(&m_originalVictimPos); }

private:
	StateMachine *m_attackMachine;
	AttackExitConditionsInterface *m_attackParameters;
	Team *m_victimTeam;
	Coord3D m_originalVictimPos;
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
protected:
	// retail slot 3: the rowed ?xfer@AIAttackState@@MAEXPAVXfer@@@Z
	virtual void xfer(Xfer *xfer);
public:
	// retail vftable slot: the rowed override
	virtual StateReturnType update();
public:
	// retail vftable slot: the rowed override
	virtual void onExit(StateExitType);
};

