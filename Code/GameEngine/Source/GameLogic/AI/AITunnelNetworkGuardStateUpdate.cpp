// cl: /DNDEBUG /MD
// platformsdk
//
// AITunnelNetworkGuardState::update, retail 0x00346487 (74 bytes): slot 6 of
// vtable 0x00C11850, whose slot-2 name getter returns AITunnelNetworkGuardState
// (slot 3 is the rowed xfer 0x00341FF4). Ported from Zero Hour's
// GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// BFME2 layout (target evidence): guard machine +0x20 (updateStateMachine is
// its vslot 4, +0x10), machine lock byte +0x38, owner template +4 with the
// PROJECTILE kind bit at byte +0x10B mask 0x02; isOutOfAmmo is the rowed
// Object::isOutOfAmmo.
#include <windows.h>
typedef bool Bool;
#include "../../../Include/Common/ThingTemplate.h"
class Object
{
public:
	Bool isOutOfAmmo() const;
	Bool isKindOfProjectile() const { return (((unsigned char)(m_template->m_kindof[0] >> 24) & 0x02) != 0); }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
};
#include "../../../Include/Common/StateMachineClass.h"
class AITNGuardMachine : public StateMachine
{
};
class AITunnelNetworkGuardState : public State
{
public:
	virtual StateReturnType update();
private:
	AITNGuardMachine *m_guardMachine; // +0x20
};

StateReturnType AITunnelNetworkGuardState::update()
{
	if (m_guardMachine == NULL)
	{
		return STATE_FAILURE; // We actually already exited.
	}

	// if all of our weapons are out of ammo, can't attack.
	// (this can happen for units which never auto-reload, like the Raptor)
	Object* owner = getMachineOwner();
	if (owner->isOutOfAmmo() && !owner->isKindOfProjectile())
	{
		return STATE_FAILURE;
	}

	getMachine()->m_locked = true;	// Retail inlines lock here: we don't want to switch out of guard during the update.
	StateReturnType ret = m_guardMachine->updateStateMachine();
	getMachine()->m_locked = false;
	return ret;
}
