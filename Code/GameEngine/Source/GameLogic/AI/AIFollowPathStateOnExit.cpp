// cl: /DNDEBUG /MD
//
// AIFollowPathState::onExit, retail 0x00349D92 (131 bytes): slot 5 of vtable
// 0x00C12BC8, whose slot-2 name getter returns AIFollowPathState. Ported from
// Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference): base onExit, then
// setCanPathThroughUnits(false), precise-z off and goal path index -1.
// BFME2 additions (target evidence): the AI's out-of-line +0x164 setter
// (pinned AIUpdateInterface::rva00262FEB, the body ICF-shared with
// ParticleEmitterDefClass::Set_Burst_Size) is called with 0 after the
// path-through flag; afterwards, unless the owner template's kind byte +0x115
// has mask 0x20, object status 90 is cleared through the rowed setStatus, and
// the current locomotor entry from the rowed Object::rva0028AC4E gets -1.0
// at +0x2C (both unnamed).
// Layout: AI +0x258 with goal path index +0x194, current locomotor +0x1F0
// (flags +0x44, USE_PRECISE_Z_POS bit 3) and can-path-through-units +0x3BA.
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
	OBJECT_STATUS_BFME_90 = 90
};
class Locomotor
{
public:
	enum LocoFlag
	{
		IS_BRAKING = 0,
		ALLOW_INVALID_POSITION,
		MAINTAIN_POS_IS_VALID,
		PRECISE_Z_POS
	};
	void setUsePreciseZPos(Bool b)
	{
		if (b)
			m_flags |= (1 << PRECISE_Z_POS);
		else
			m_flags &= ~(1 << PRECISE_Z_POS);
	}
private:
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};
class AIUpdateInterface
{
public:
	void setCanPathThroughUnits(Bool b) { m_canPathThroughUnits = b; }
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	void friend_setCurrentGoalPathIndex(int index) { m_currentGoalPathIndex = index; }
	void rva00262FEB(int value);
private:
	unsigned char m_pad000[0x194];
	int m_currentGoalPathIndex; // +0x194
	unsigned char m_pad198[0x1F0 - 0x198];
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3BA - 0x1F4];
	Bool m_canPathThroughUnits; // +0x3BA
};
struct Rva0028AC4EEntry
{
	unsigned char m_pad00[0x2C];
	Real m_bfme2C; // +0x2C
};
class ThingTemplate
{
public:
	Bool testKindByte115() const { return (m_kindOf[1] & 0x20) != 0; }
private:
	unsigned char m_pad00[0x114];
	unsigned char m_kindOf[4]; // +0x114
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	void setStatus(ObjectStatusTypes status, bool set);
	const Rva0028AC4EEntry *rva0028AC4E() const;
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
class AIInternalMoveToState : public State
{
public:
	virtual void onExit(StateExitType status);
};
class AIFollowPathState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIFollowPathState::onExit( StateExitType status )
{
	AIInternalMoveToState::onExit( status );

	// turn off precision-z-pos when we exit, just in case.
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!ai) return;
	ai->setCanPathThroughUnits(false);
	ai->rva00262FEB(0);
	if (ai->getCurLocomotor())
		ai->getCurLocomotor()->setUsePreciseZPos(false);

	//Assign this value to the AIUpdateInterface so object's can access this value while
	//determine which waypoints to plot in the waypoint renderer.
	ai->friend_setCurrentGoalPathIndex( -1 );

	Object *obj = getMachineOwner();
	if (!obj->getTemplate()->testKindByte115())
		obj->setStatus(OBJECT_STATUS_BFME_90, false);
	if (obj->rva0028AC4E())
		const_cast<Rva0028AC4EEntry *>(obj->rva0028AC4E())->m_bfme2C = -1.0f;
}
