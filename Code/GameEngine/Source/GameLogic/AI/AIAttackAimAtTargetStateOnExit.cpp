// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AIAttackAimAtTargetState::onExit, retail 0x0034A508 (104 bytes): slot 5 of
// vtable 0x00C11008, whose slot-2 name getter returns AIAttackAimAtTargetState
// (slot 3 is the rowed xfer 0x00341237). Ported from Zero Hour's
// GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// BFME2 differences (target evidence): after ZH's setLocomotorGoalNone (AI
// vslot 136, +0x220) the AI also restores the normal locomotor set (AI vslot
// 142, +0x238, as in the AIWanderInPlaceState bodies) when the owner
// template's Real at +0x53C (unnamed) is below 360; the aiming status is
// cleared through the rowed Object::setStatus(25, false).
// Layout: m_canTurnInPlace +0x21, m_setLocomotor +0x22, AI +0x258.
typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_IS_AIMING_WEAPON = 25
};
enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0
};
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class AIUpdateInterface : public VSlots<136>
{
public:
	virtual void setLocomotorGoalNone() = 0;
	virtual void slot137() = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual Bool chooseLocomotorSet(LocomotorSetType wst) = 0;
};
class ThingTemplate
{
public:
	Real getUnknown53C() const { return m_unknown53C; }
private:
	unsigned char m_pad00[0x53C];
	Real m_unknown53C; // +0x53C
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	void setStatus(ObjectStatusTypes bit, bool set);
	void clearStatus(ObjectStatusTypes bit) { setStatus(bit, false); }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x258 - 0x08];
	AIUpdateInterface *m_ai; // +0x258
};
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
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIAttackAimAtTargetState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x21 - 0x1C];
	Bool m_canTurnInPlace; // +0x21
	Bool m_setLocomotor; // +0x22
};

void AIAttackAimAtTargetState::onExit( StateExitType status )
{
	AIUpdateInterface* sourceAI = getMachineOwner()->getAI();
	// contained by AIAttackState, so no separate timer
	if (m_canTurnInPlace)
	{
		// Tell the ai we are done moving, if we set the locomotor goal.
		if (sourceAI && m_setLocomotor)
			sourceAI->setLocomotorGoalNone();
	}

	if (sourceAI && getMachineOwner()->getTemplate()->getUnknown53C() < 360.0f)
		sourceAI->chooseLocomotorSet(LOCOMOTORSET_NORMAL);

	getMachineOwner()->clearStatus( OBJECT_STATUS_IS_AIMING_WEAPON );
}
