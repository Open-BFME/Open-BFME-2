// cl: /DNDEBUG /MD
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
typedef bool Bool;
#define NULL 0
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};
class ThingTemplate
{
public:
	Bool isKindOfProjectile() const { return (m_kindOf[3] & 0x02) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[4]; // +0x108 (PROJECTILE: byte +0x10B mask 0x02)
};
class Object
{
public:
	Bool isOutOfAmmo() const;
	Bool isKindOfProjectile() const { return m_template->isKindOfProjectile(); }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
};
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType updateStateMachine();
	Object *getOwner() const { return m_owner; }
	void lock(const char *msg) { m_locked = true; }
	void unlock() { m_locked = false; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x38 - 0x18];
	Bool m_locked; // +0x38
};
class AITNGuardMachine : public StateMachine
{
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
class AITunnelNetworkGuardState : public State
{
public:
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
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

	getMachine()->lock("AITunnelNetworkGuardState::update");	// We don't want to switch out of guard during the update.
	StateReturnType ret = m_guardMachine->updateStateMachine();
	getMachine()->unlock();
	return ret;
}
