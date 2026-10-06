// cl: /DNDEBUG /MD
//
// AIAttackApproachTargetState::onExit, retail 0x0034894C (166 bytes): slot 5
// of vtable 0x00C12610, whose slot-2 name getter returns
// AIAttackApproachTargetState. Ported from Zero Hour's
// GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): base onExit (the rowed
// AIInternalMoveToState::onExit 0x003473A4), ignoreObstacle(NULL) (rowed
// 0x00268D88), precise-z off for a projectile (template kind byte +0x10B
// mask 2), the snap to the goal when doing ground movement (AI slot 137)
// within PATHFIND_CELL_SIZE_F^2 / 8 (12.5, .rdata 0x00C139F8) through the
// rowed Thing::setPosition, and m_isInitialApproach (+0x6F) cleared.
// BFME 2 addition (target evidence): AI slot 136 is called last inside the
// AI block. BFME 2 sums dy*dy first.
//
// AIAttackApproachTargetState::update, retail 0x003488AF (157 bytes): slot 6
// of the same vtable. Zero Hour's body over the pinned private
// updateInternal (0x00348356): keep following a mobile owner's live,
// non-immobile victim (template kind byte +0x108 mask 4; the pinned
// Object::isMobile), and on the initial approach aim the current weapon's
// turret (rowed getWhichTurretForCurWeapon and setTurretTargetObject, pinned
// getNextMoodTarget) at a mood target. BFME 2 drops the owner null test and
// sets the AI byte +0x3C7 after aiming.
//
// AIAttackApproachTargetState00C12678: the class of vtable 0x00C12678, which
// shares the approach name getter 0x00342972 ("AIAttackApproachTargetState")
// but has its own xfer (0x00340623), onEnter and smaller layout, so it is a
// BFME 2 variant of the approach state, not a subclass (its name is
// address-derived; the relation is inference). Its onExit (slot 5,
// 0x00348AFE, 166 bytes) is the approach onExit with the initial-approach flag
// at +0x61; its update (slot 6, 0x00348AAB, 83 bytes) is Zero Hour's pursue
// shape (no follow block) over its own private updateInternal (pinned,
// 0x003489F2), aiming without force-attack and setting +0x3C7.

typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum WhichTurretType
{
	TURRET_INVALID = -1
};
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
#define PATHFIND_CELL_SIZE_F 10.0f

struct Coord3D
{
	Real x, y, z;
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

template <int N> class AIApproachAISlots : public AIApproachAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIApproachAISlots<0>
{
};

class Object;
class Weapon;

class AIUpdateInterface : public AIApproachAISlots<136>
{
public:
	virtual void rva003489E2Slot136() = 0;
	virtual Bool isDoingGroundMovement() const = 0;
	void ignoreObstacle(const Object *obj);
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	WhichTurretType getWhichTurretForCurWeapon() const;
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	void setTurretTargetObject(WhichTurretType tur, Object *o, Bool isForceAttacking);
private:
	unsigned char m_pad004[0x1F0 - 0x04];
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3B2 - 0x1F4];
public:
	Bool m_3b2; // +0x3B2
private:
	unsigned char m_pad3B3[0x3C7 - 0x3B3];
public:
	Bool m_bfmeFlag3C7; // +0x3C7
};

class ThingTemplate
{
public:
	Bool isKindOfProjectile() const { return (m_kindOf[3] & 2) != 0; }
	Bool isKindOfImmobile() const { return (m_kindOf[0] & 4) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[4]; // +0x108
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	void setPosition(const Coord3D *pos);
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	Bool isKindOfProjectile() const { return getTemplate()->isKindOfProjectile(); }
	Bool isMobile() const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	unsigned char m_pad044[0x258 - 0x44];
	AIUpdateInterface *m_ai; // +0x258
};

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	char rva002CB902(Object *source, void *pos, float extra, int flag) const;
	char m_pad00[4];
	Rva002C9400ByteField *m_field4; // +0x04
};

class GameLogic
{
public:
	unsigned char m_pad00[0x1B4];
	int m_1B4; // +0x1B4
};

extern GameLogic *TheGameLogic;
extern "C" void *theLogicRandomLogFile;
extern "C" void __cdecl fprintf(void *stream, const char *format, ...);

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
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
	virtual Bool computePath();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual Bool computePath();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
};

class AIAttackApproachTargetState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	StateReturnType updateInternal( void );
	unsigned char m_pad2C[0x6C - 0x2C];
	Bool m_follow; // +0x6C
	Bool m_isAttackingObject; // +0x6D
	Bool m_stopIfInRange; // +0x6E
	Bool m_isInitialApproach; // +0x6F
	Bool m_isForceAttacking; // +0x70
};

void AIAttackApproachTargetState::onExit( StateExitType status )
{
	// contained by AIAttackState, so no separate timer
	AIInternalMoveToState::onExit( status );

	AIUpdateInterface *ai = getMachineOwner()->getAI();
	Object *obj = getMachineOwner();
	if (ai) {
		ai->ignoreObstacle(0);

		// urg. hacky. if we are a projectile, reset precise z-pos.
		if (getMachineOwner()->isKindOfProjectile())
		{
			if (ai && ai->getCurLocomotor())
				ai->getCurLocomotor()->setUsePreciseZPos(false);
		}
		if (ai->isDoingGroundMovement()) {
			Real dx = m_goalPosition.x-obj->getPosition()->x;
			Real dy = m_goalPosition.y-obj->getPosition()->y;
			if (dy*dy+dx*dx<PATHFIND_CELL_SIZE_F*PATHFIND_CELL_SIZE_F*0.125f)
			{
				// We are doing accurate ground movement, so make sure we end exactly at the goal.
				obj->setPosition(&m_goalPosition);
			}
		}
		ai->rva003489E2Slot136();
	}

	m_isInitialApproach = false;	// We only want to allow turreted things to fire at enemies during their
																// first approach
}

StateReturnType AIAttackApproachTargetState::update()
{
	// contained by AIAttackState, so no separate timer

	StateReturnType code = updateInternal();
	Object* source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();

	if (m_follow && m_isAttackingObject)
	{
		// Basically, if the object is alive, we continue, in case the target moves.
		Object* victim = getMachineGoalObject();
		if (victim && source->isMobile() && !victim->getTemplate()->isKindOfImmobile())
		{
			if (code != STATE_CONTINUE)
			{
				m_isInitialApproach = false;
			}
			// Object is still alive (and so are we)
			// It could move (and so can we), so just continue & keep checking.
			code = STATE_CONTINUE;
		}
	}

	if (m_isInitialApproach)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			Object *temporaryTarget = ai->getNextMoodTarget( true, false );
			if (temporaryTarget)
			{
				ai->setTurretTargetObject(tur, temporaryTarget, m_isForceAttacking);
				ai->m_bfmeFlag3C7 = true;
			}
		}
	}

	return code;
}

class AIAttackApproachTargetState00C12678 : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	StateReturnType updateInternal( void );
	unsigned char m_pad2C[0x60 - 0x2C];
	Bool m_stopIfInRange; // +0x60
	Bool m_isInitialApproach; // +0x61
	Bool m_62; // +0x62
};

void AIAttackApproachTargetState00C12678::onExit( StateExitType status )
{
	AIInternalMoveToState::onExit( status );

	AIUpdateInterface *ai = getMachineOwner()->getAI();
	Object *obj = getMachineOwner();
	if (ai) {
		ai->ignoreObstacle(0);

		if (getMachineOwner()->isKindOfProjectile())
		{
			if (ai && ai->getCurLocomotor())
				ai->getCurLocomotor()->setUsePreciseZPos(false);
		}
		if (ai->isDoingGroundMovement()) {
			Real dx = m_goalPosition.x-obj->getPosition()->x;
			Real dy = m_goalPosition.y-obj->getPosition()->y;
			if (dy*dy+dx*dx<PATHFIND_CELL_SIZE_F*PATHFIND_CELL_SIZE_F*0.125f)
			{
				obj->setPosition(&m_goalPosition);
			}
		}
		ai->rva003489E2Slot136();
	}

	m_isInitialApproach = false;
}

StateReturnType AIAttackApproachTargetState00C12678::update()
{
	StateReturnType code = updateInternal();
	Object* source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();

	if (m_isInitialApproach)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			Object *temporaryTarget = ai->getNextMoodTarget( true, false );
			if (temporaryTarget)
			{
				ai->setTurretTargetObject(tur, temporaryTarget, false);
				ai->m_bfmeFlag3C7 = true;
			}
		}
	}

	return code;
}

// ?updateInternal@AIAttackApproachTargetState00C12678@@AAE?AW4StateReturnType@@XZ @0x003489F2 185B
// Evidence: pinned name; gap between onExit 0x0034894C and update 0x00348AAB;
// retail position-attack branch (ZH AIStates.cpp updateInternal position part)
// with m_stopIfInRange at +0x60 from AI byte +0x3B2, force at +0x62,
// weapon contact bytefield at +0x04 (rowed 0x002C9400), TheGameLogic frame
// check at +0x1B4 with masiwar updateInternal [2] log, Coord3D range test
// via rowed 0x002CB902, computePath at slot 0x44 and tail to pinned base
// update 0x00347460.
StateReturnType AIAttackApproachTargetState00C12678::updateInternal()
{
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	m_stopIfInRange = (ai->m_3b2 == 0);
	if (m_62)
		m_stopIfInRange = true;
	Object *source = m_machine->m_owner;
	const Weapon *weapon = source->getCurrentWeapon(0);
	if (weapon != 0 && ((Rva002C9400ByteField *)weapon->m_field4)->get() != 0)
		m_stopIfInRange = false;
	if (TheGameLogic->m_1B4 > 0)
	{
		if (m_stopIfInRange && weapon != 0)
		{
			void *log = theLogicRandomLogFile;
			if (log != 0)
				fprintf(log, "masiwar called by AIAttackPositionApproachTargetState::updateInternal [2]");
		}
	}
	if (m_stopIfInRange && weapon != 0)
	{
		if (weapon->rva002CB902(source, (void *)&m_goalPosition, 0.0f, 1))
			return STATE_SUCCESS;
	}
	if (!computePath())
		return STATE_FAILURE;
	return AIInternalMoveToState::update();
}
