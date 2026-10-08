// ?computePath@AIAttackMeleeApproachState@@MAE_NXZ
// partial score=0.6 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc
//
// Small computePath (slot 17), onExit (slot 5) and other overrides of AI
// states, each named by its vtable's own slot-2 name getter (the state's name
// literal). BFME 2 logs a numbered "CritterDesync" line from computePath
// when the desync log is on (g_00E03745, file g_00DFEFF0):
//
//  - AIMoveAndTightenState::computePath 0x00340158 (34 bytes; 0x00C124D8,
//    whose constructor 0x00342843 builds on AIInternalMoveToState directly):
//    "ComputePath4", then keeps the existing path (true).
//  - AIMoveAwayAndCowerState::computePath 0x003403DC (53 bytes; 0x00C12FF0)
//    and AIBackAwayState::computePath 0x0034042C (53 bytes; 0x00C13050):
//    "ComputePath8" / "ComputePath9", then spend one of the repath tries at
//    +0x4C (Zero Hour's m_okToRepathTimes) or fail.
//  - AIPickUpCrateState::computePath 0x00345B5F (42 bytes; 0x00C128D0) and
//    AIFollowPathState::computePath 0x00345B89 (42 bytes; 0x00C12BC8):
//    "ComputePath30" / "ComputePath31", then the base
//    AIInternalMoveToState::computePath (pinned 0x003441F7) as a tail call.
//  - AIWaitUntilFinishedFiringState::onExit 0x00341391 (16 bytes;
//    0x00C11120): releases the owner's weapon lock (pinned
//    Object::releaseWeaponLock, LOCKED_TEMPORARILY); no base call.
//  - AIAttackMeleeSquishState::onExit 0x003497C7 (31 bytes; 0x00C12868):
//    base onExit, then object status 0x1C cleared.
//  - AIMoveAwayAndCowerState::onExit 0x00347F48 (46 bytes): base onExit,
//    then AI slot 142 with 0.
//  - AIBackAwayState::onExit 0x00347FFE (80 bytes): base onExit, then
//    model-condition bit 65 cleared (notifying through the rowed
//    Object::rva0028AE6D), AI slot 142 with 0 and the AI byte +0x3C8 cleared.
//  - AIBackAwayState::onEnter 0x0034CC00 (314 bytes; slot 4 of 0x00C13050):
//    "setAdjustDestination(FALSE) 16", fails without a goal or an AI, calls
//    AI slot 142 with 9. Without the AI byte +0x3C8 the state is done at
//    once (+0x54); otherwise it allows one repath, arms the path-end retarget
//    (+0x50) that AIBackAwayState::update consumes, calls the rowed
//    Object::rva0028AD32 and requests a path 40 units from the goal along
//    the normalized goal-to-owner offset (rowed Coord3D::normalize,
//    AIUpdateInterface::requestPath), then the pinned base onEnter. The
//    scaled offset is a member-wise copy so /arch:SSE batches its stores.
//
//  - AIWaitUntilFinishedFiringState::update 0x0034133E (83 bytes): fails
//    without a current weapon (rowed Object::getCurrentWeapon); continues
//    while the weapon's frame (+0x2C) plus its template delay (+0x78, when
//    not negative) is ahead of TheGameLogic's frame or its rowed
//    Weapon::getStatus is 5; then succeeds for a negative delay, else fails.
//  - AIMoveToStateSA::onEnter 0x0034C8C5 (207 bytes; slot 4 of 0x00C11F00):
//    Zero Hour's AIMoveToState::onEnter with "setAdjustDestination" log
//    lines 4/5: adjust on, off again when the goal object is the AI's
//    ignored obstacle (pinned getter 0x0006E009, +0x164), goal position from
//    the goal object or the machine, the pinned base onEnter, then AI slot
//    136 when +0x50 is set and the AI is moving (pinned isMoving).
//  - AIMoveToStateSA::update 0x00347A51 (91 bytes; 0x00C11F00): while +0x50
//    is set, fails once TheGameLogic's frame passes +0x4C and otherwise
//    clears condition bit 61 and continues; else follows the machine goal
//    object's position and runs the pinned AIInternalMoveToState::update.
//  - AIGoingIdleState::onEnter 0x00341E48 (40 bytes; 0x00C11798): pokes the
//    owner's StancesBehavior module (rowed Object::findModule with the
//    StancesBehavior key, pinned member 0x0045F235) and fails.
//  - AIAttackMeleeEngageState::computePath 0x003457AC (905 bytes;
//    "ComputePath26"). Donor: BFME 1's matched
//    AIAttackMeleeEngageState_computePath (0x00177A90), whose call order and
//    strings carry over. Target evidence: the AI word +0x16C fails at once,
//    the state's waiting flag is +0x49, the approach timestamp +0x54 is
//    throttled by the int at 0x009BA4E4, the victim position caches at +0x58
//    and +0x6C/+0x70/+0x71 hold the retry frame, retry flag and "no
//    engagement spot". The "masiwar" traces print only when GameLogic +0x1B4
//    is positive. Pathfinder::adjustToPossibleDestination (0x002F287A) is
//    named from the donor's same call; 0x002F23A6, 0x002CB35C and the
//    fallback 0x003449C5 stay address-named.
//
// The meaning of the status, condition and AI bytes is not recovered.

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
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponStatus
{
	WEAPON_STATUS_BFME_5 = 5
};

struct Coord3D
{
	Real x, y, z;
	Real length() const;
	void normalize();
	void set(Real ax, Real ay, Real az)
	{
		x = ax;
		y = ay;
		z = az;
	}
	Coord3D &operator*=(Real scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}
	Coord3D &operator+=(const Coord3D &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
};
// Retail copies the direction member-wise (three movss loads, no movsd block
// copy) and keeps x apart from the in-place y/z scaling; only a user-written
// copy constructor reproduces that register shape. The shipped type is not
// known, so this TU-local view carries just that constructor.
struct MemberwiseCoord3D : public Coord3D
{
	MemberwiseCoord3D(const Coord3D &other) { x = other.x; y = other.y; z = other.z; }
};

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
	int getBfmeDebugLevel() const { return m_bfmeDebugLevel; }
private:
	unsigned char m_pad00[0x40];
	unsigned int m_frame; // +0x40
	unsigned char m_pad44[0x1B4 - 0x44];
	int m_bfmeDebugLevel; // +0x1B4, gates the "masiwar" traces
};
extern GameLogic *TheGameLogic;

struct WeaponTemplateView
{
	unsigned char m_pad00[0x78];
	int m_bfmeDelay78; // +0x78
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	const WeaponTemplateView *m_template04() const { return m_template; }
	unsigned int m_bfmeFrame2C() const { return m_frame; }
private:
	unsigned char m_pad00[0x04];
	const WeaponTemplateView *m_template; // +0x04
	unsigned char m_pad08[0x2C - 0x08];
	unsigned int m_frame; // +0x2C
};

class StancesBehavior
{
public:
	void rva0045F235();
};

NameKeyType Rva0045EE2CGet();
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_1C = 0x1C
};
enum WeaponLockType
{
	NOT_LOCKED,
	LOCKED_TEMPORARILY
};

extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
		if (log != 0)
			fprintf(log, text);
	}
}

template <int N> class AIComputePathAISlots : public AIComputePathAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIComputePathAISlots<0>
{
};

enum ObjectID
{
	INVALID_ID = 0
};

class LocomotorSet
{
};

class AIUpdateInterface : public AIComputePathAISlots<136>
{
public:
	virtual void rva0034C988Slot136() = 0;
	virtual void slot137() = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void rva00347F6BSlot142(int value) = 0;
	ObjectID getIgnoredObstacleID() const;
	Bool isMoving() const;
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	Bool rva00263C06(Coord3D *destination, Bool flag);
	void *getPath() const { return m_path; }
	Bool isWaitingForPath() const { return m_waitingForPath; }
	unsigned char m_pad004[0x140 - 0x04];
	void *m_path; // +0x140
	unsigned char m_pad144[0x16C - 0x144];
	int m_bfmeBlocked16C; // +0x16C; positive fails computePath at once
	unsigned char m_pad170[0x1CC - 0x170];
	LocomotorSet m_locomotorSet; // +0x1CC
	unsigned char m_pad1CD[0x3B1 - 0x1CD];
	Bool m_waitingForPath; // +0x3B1
	unsigned char m_pad3B2[0x3C8 - 0x3B2];
	Bool m_bfmeFlag3C8; // +0x3C8
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Module;

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

// KindOf bits named from retail's KindOf name table (0x00DBBE18).
enum KindOfType
{
	KINDOF_SIEGE_TOWER = 93,
	KINDOF_WALL_UPGRADE = 150
};
class ThingTemplate
{
public:
	__forceinline unsigned int isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 0x1f)); }
private:
	unsigned char m_pad00[0x108];
	unsigned int m_kindOf[7]; // +0x108
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	const Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0) const;
	Module *findModule(NameKeyType key) const;
	void setStatus(ObjectStatusTypes status, Bool set);
	void releaseWeaponLock(WeaponLockType lockType);
	void rva0028AE6D();
	void rva0028AD32();
	void rva0028C2DD(Coord3D *pos) const;
	void rva0028ACDC(const Coord3D *pos);
	Real getGeometryRadiusB8() const { return m_geometryRadiusB8; }
	__forceinline unsigned int isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	int rva0028B511() const;
	__forceinline void clearModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0xB8 - 0x78];
	Real m_geometryRadiusB8; // +0xB8 (geometry info +0xA8, its +0x10)
	unsigned char m_pad0BC[0x10C - 0xBC];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - (0x10C + sizeof(Rva0010CBits))];
	AIUpdateInterface *m_ai; // +0x258
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
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
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
protected:
	virtual Bool computePath();
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	virtual Bool computePath();
	void setAdjustsDestination(Bool b) { m_adjustDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustDestination; // +0x48
	Bool m_waitingForPath; // +0x49
	unsigned char m_pad4A[0x4C - 0x4A];
};

class AIMoveAndTightenState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIMoveAndTightenState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath4");
	return true;
}

class AIMoveAwayAndCowerState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
protected:
	virtual Bool computePath();
private:
	int m_okToRepathTimes; // +0x4C
};

Bool AIMoveAwayAndCowerState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath8");
	if (m_okToRepathTimes > 0)
	{
		m_okToRepathTimes--;
		return true;
	}
	return false;
}

void AIMoveAwayAndCowerState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Object *owner = getMachineOwner();
	if (owner && owner->getAI())
		owner->getAI()->rva00347F6BSlot142(0);
}

class AIBackAwayState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
protected:
	virtual Bool computePath();
private:
	int m_okToRepathTimes; // +0x4C
	Bool m_retargetToPathEnd; // +0x50
	unsigned char m_pad51[0x54 - 0x51];
	Bool m_done; // +0x54
};

StateReturnType AIBackAwayState::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 16");
	setAdjustsDestination(false);
	Object *owner = getMachineOwner();
	Object *goal = getMachine()->getGoalObject();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (goal == 0 || ai == 0)
		return STATE_FAILURE;
	ai->rva00347F6BSlot142(9);
	if (ai->m_bfmeFlag3C8)
	{
		m_okToRepathTimes = 1;
		m_retargetToPathEnd = true;
		m_done = false;
		owner->rva0028AD32();

		// Back away 40 units from the goal along the goal-to-owner direction.
		Coord3D dest;
		Coord3D dir;
		Real ox = owner->getPosition()->x;
		Real oy = owner->getPosition()->y;
		Real oz = owner->getPosition()->z;
		dest.x = ox;
		dest.y = oy;
		dest.z = oz;
		dir.x = ox - goal->getPosition()->x;
		dir.y = oy - goal->getPosition()->y;
		dir.z = oz - goal->getPosition()->z;
		dir.normalize();
		Coord3D offset;
		offset.x = dir.x;
		offset.y = dir.y;
		offset.z = dir.z;
		offset.x *= 40.0f;
		offset.y *= 40.0f;
		offset.z *= 40.0f;
		dest.x += offset.x;
		dest.y += offset.y;
		dest.z += offset.z;
		ai->requestPath(&dest, true);
		return AIInternalMoveToState::onEnter();
	}
	m_retargetToPathEnd = false;
	m_done = true;
	return STATE_CONTINUE;
}

Bool AIBackAwayState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath9");
	if (m_okToRepathTimes > 0)
	{
		m_okToRepathTimes--;
		return true;
	}
	return false;
}

void AIBackAwayState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Object *owner = getMachineOwner();
	if (!owner)
		return;
	owner->clearModelConditionBit(65);
	if (owner->getAI())
	{
		owner->getAI()->rva00347F6BSlot142(0);
		owner->getAI()->m_bfmeFlag3C8 = false;
	}
}

class AIPickUpCrateState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIPickUpCrateState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath30");
	return AIInternalMoveToState::computePath();
}

class AIFollowPathState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
};

Bool AIFollowPathState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath31");
	return AIInternalMoveToState::computePath();
}

class AIWaitUntilFinishedFiringState : public State
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

StateReturnType AIWaitUntilFinishedFiringState::update()
{
	const Weapon *weapon = getMachineOwner()->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;
	int delay = weapon->m_template04()->m_bfmeDelay78;
	if (delay >= 0)
	{
		if (weapon->m_bfmeFrame2C() + delay > TheGameLogic->getFrame())
			return STATE_CONTINUE;
	}
	if (weapon->getStatus() == WEAPON_STATUS_BFME_5)
		return STATE_CONTINUE;
	if (weapon->m_template04()->m_bfmeDelay78 < 0)
		return STATE_SUCCESS;
	return STATE_FAILURE;
}

void AIWaitUntilFinishedFiringState::onExit(StateExitType status)
{
	getMachineOwner()->releaseWeaponLock(LOCKED_TEMPORARILY);
}

class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIAttackMeleeSquishState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	getMachineOwner()->setStatus(OBJECT_STATUS_BFME_1C, false);
}

class AIMoveToStateSA : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	unsigned int m_bfmeFrame4C; // +0x4C
	Bool m_bfmeFlag50; // +0x50
};

StateReturnType AIMoveToStateSA::onEnter()
{
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 4");
	setAdjustsDestination(true);

	// If we have a goal object and are trying to ignore it as an obstacle...
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (getMachine()->getGoalObject())
	{
		if (ai && getMachine()->getGoalObject()->getID() == ai->getIgnoredObstacleID())
		{
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 5");
			setAdjustsDestination(false);
		}
	}

	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();

	StateReturnType ret = AIInternalMoveToState::onEnter();
	if (m_bfmeFlag50 && ai && ai->isMoving())
		ai->rva0034C988Slot136();
	return ret;
}

StateReturnType AIMoveToStateSA::update()
{
	if (m_bfmeFlag50)
	{
		if (TheGameLogic->getFrame() > m_bfmeFrame4C)
			return STATE_FAILURE;
		getMachineOwner()->clearModelConditionBit(61);
		return STATE_CONTINUE;
	}
	Object *goal = getMachine()->getGoalObject();
	if (goal)
		m_goalPosition = *goal->getPosition();
	return AIInternalMoveToState::update();
}

class AIGoingIdleState : public State
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType AIGoingIdleState::onEnter()
{
	Object *owner = getMachineOwner();
	if (owner)
	{
		StancesBehavior *stances = (StancesBehavior *)owner->findModule(Rva0045EE2CGet());
		if (stances)
			stances->rva0045F235();
	}
	return STATE_FAILURE;
}

class Pathfinder
{
public:
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet,
		Coord3D *dest, const Coord3D *groupDest);
	Bool adjustToPossibleDestination(Object *obj, const LocomotorSet &locomotorSet,
		Coord3D *dest);
	Bool IsPointOnWall(int pos, Bool flag);
};

class AIData
{
public:
	unsigned char m_pad00[0x90];
	Real m_bfme90; // +0x90
	Real m_bfme94; // +0x94
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	const AIData *getAiData() const { return m_aiData; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	const AIData *m_aiData; // +0x18
};
extern AI *TheAI;

// Minimum frames between melee repaths (int global at 0x009BA4E4).
extern const int g_009BA4E4;

// Opaque callees, named by body address with their pinned signatures.
class Rva002CB35CObj
{
public:
	Bool rva002CB35C(int source, void *goalPos, void *victim, void *victimPos,
		Real extra, int flag);
};
class Rva002F23A6
{
public:
	Bool rva002F23A6(Object *source, int weapon, int locomotorSet, Coord3D *goalPos,
		Object *victim);
};
Bool rva00344EB2Gate(Object *source, Thing *victim);
Bool rva003449C5(Coord3D *goalPos, Object *source, Object *victim);

// Static helper from AIStates.cpp (rowed at 0x0033FA8E from
// AIAttackApproachTargetState_computePath_Bfme.cpp); VC7.1 passes its three
// pointers in registers, so callers only match with a definition in the TU.
static __declspec(noinline) Bool isSamePosition(const Coord3D *ourPos,
	const Coord3D *prevTargetPos, const Coord3D *curTargetPos)
{
	Coord3D diff;
	diff.x = curTargetPos->x - prevTargetPos->x;
	diff.y = curTargetPos->y - prevTargetPos->y;
	Coord3D toTarget;
	toTarget.x = curTargetPos->x - ourPos->x;
	toTarget.y = curTargetPos->y - ourPos->y;
	const float TOLERANCE_FACTOR = 1.0f / (10.0f * 10.0f);
	float toleranceSqr = (toTarget.x*toTarget.x+toTarget.y*toTarget.y) * TOLERANCE_FACTOR;
	if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
		return false;
	return true;
}

static __forceinline void debugTrace(const char *text)
{
	FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
	if (log != 0)
		fprintf(log, text);
}

class AIAttackMeleeEngageState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
	__forceinline void setGoalAlongDirection(const Coord3D *directionVector,
		Object *target, const Coord3D &goalPosition)
	{
		MemberwiseCoord3D direction(*directionVector);
		direction *= target->getGeometryRadiusB8() * 2.0f + 60.0f;
		m_goalPosition = goalPosition;
		m_goalPosition += direction;
	}
private:
	unsigned char m_pad4C[0x54 - 0x4C];
	unsigned int m_approachTimestamp; // +0x54
	Coord3D m_prevVictimPos; // +0x58
	unsigned char m_pad64[0x6C - 0x64];
	unsigned int m_retryFrame; // +0x6C
	Bool m_retryPending; // +0x70
	Bool m_noEngagementSpot; // +0x71
};

Bool AIAttackMeleeEngageState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath26");
	Bool forceRepath = false;
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai->m_bfmeBlocked16C > 0)
		return false;
	if (m_waitingForPath)
	{
		if (ai->getPath() || ai->isWaitingForPath())
			return true;
		m_waitingForPath = false;
	}
	if (!ai->getPath() && !ai->isWaitingForPath())
		forceRepath = true;
	if (!forceRepath && TheGameLogic->getFrame() - m_approachTimestamp < g_009BA4E4)
		return true;
	m_approachTimestamp = TheGameLogic->getFrame();

	if (getMachine()->getGoalObject())
	{
		Object *source = getMachineOwner();
		// if our victim's position hasn't changed, don't re-path
		if (!forceRepath && isSamePosition(source->getPosition(), &m_prevVictimPos,
			getMachine()->getGoalObject()->getPosition()))
			return true;
		const Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return false;

		Object *victim = getMachine()->getGoalObject();
		Coord3D victimPosition;
		victimPosition.x = victim->getPosition()->x;
		victimPosition.y = victim->getPosition()->y;
		victimPosition.z = victim->getPosition()->z;
		victim->rva0028C2DD(&victimPosition);
		m_prevVictimPos = victimPosition;
		if (rva00344EB2Gate(source, victim))
		{
			setGoalAlongDirection(victim->getUnitDirectionVector2D(), victim, victimPosition);
			TheAI->pathfinder()->adjustToPossibleDestination(source, ai->m_locomotorSet, &m_goalPosition);
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 34");
			setAdjustsDestination(false);
			ai->requestPath(&m_goalPosition, false);
			m_waitingForPath = ai->isWaitingForPath();
			if (ai->getPath())
				m_waitingForPath = false;
			return true;
		}
		if (TheGameLogic->getBfmeDebugLevel() > 0 && !forceRepath)
			debugTrace("masiwar called by AIAttackMeleeEngageState::computePath [1]");
		if (!forceRepath && ((Rva002CB35CObj *)weapon)->rva002CB35C((int)source,
			&m_goalPosition, victim, &m_prevVictimPos, 0.0f, 1))
			return true;
		if (TheGameLogic->getBfmeDebugLevel() > 0)
		{
			FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
			if (log != 0)
				fprintf(log, "AIAttackFireDuringApproachState::computePath[2] will call FindMeleeEngagmentLocation with %f,%f (m_goalPosition:%f,%f = m_prevVictimPosition:%f, %f;)",
					(double)m_goalPosition.x, (double)m_goalPosition.y,
					(double)m_goalPosition.x, (double)m_goalPosition.y,
					(double)m_prevVictimPos.x, (double)m_prevVictimPos.y);
		}
		m_goalPosition = m_prevVictimPos;
		m_noEngagementSpot = !((Rva002F23A6 *)TheAI->pathfinder())->rva002F23A6(source,
			(int)weapon, (int)&ai->m_locomotorSet, &m_goalPosition, victim);
		if (m_noEngagementSpot)
		{
			m_goalPosition = m_prevVictimPos;
			if (rva003449C5(&m_goalPosition, source, victim))
			{
				TheAI->pathfinder()->adjustDestination(source, ai->m_locomotorSet, &m_goalPosition, 0);
				ai->requestPath(&m_goalPosition, true);
				return true;
			}
			m_retryPending = true;
			m_retryFrame = TheGameLogic->getFrame() + g_009BA4E4 * 10;
			return true;
		}
		source->rva0028ACDC(&m_goalPosition);
		ai->requestPath(&m_goalPosition, true);
		m_waitingForPath = ai->isWaitingForPath();
		return true;
	}
	return false;
}

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class DynamicPortalBehaviour
{
public:
	static Module *rva004608E0(Object *obj);
	Bool rva00460DF6(Coord3D *pos);
};
class Rva0029493F
{
public:
	Bool rva0029493F(int victim, int mode);
};
class Rva004C5772CmpBoolField
{
public:
	Bool get() const;
};

class AIAttackMeleeApproachState : public AIInternalMoveToState
{
protected:
	virtual Bool computePath();
private:
	unsigned int m_approachTimestamp; // +0x4C
	Coord3D m_prevVictimPos; // +0x50
};

Bool AIAttackMeleeApproachState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath18");
	Bool forceRepath = false;
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai->m_bfmeBlocked16C > 0)
		return false;

	if (m_waitingForPath)
		return true;
	if (!ai->getPath() && !ai->isWaitingForPath())
		forceRepath = true;
	else if (TheGameLogic->getFrame() - m_approachTimestamp < g_009BA4E4)
		return true;

	m_approachTimestamp = TheGameLogic->getFrame();
	if (getMachine()->getGoalObject())
	{
		Object *source = getMachineOwner();
		if (!forceRepath && isSamePosition(source->getPosition(), &m_prevVictimPos,
				getMachine()->getGoalObject()->getPosition()))
			return true;
		if (!source->getCurrentWeapon())
			return false;
		Object *victim = getMachine()->getGoalObject();
		Coord3D *prevPos = &m_prevVictimPos;
		*prevPos = *victim->getPosition();
		if (((Rva0029493F *)source)->rva0029493F((int)victim, 2))
		{
			m_goalPosition = *prevPos;
			ai->requestPath(&m_goalPosition, false);
			return true;
		}
		Coord3D delta;
		delta.x = source->getPosition()->x - prevPos->x;
		delta.y = source->getPosition()->y - prevPos->y;
		delta.z = 0.0f;
		delta.length();
		const AIData *data = TheAI->getAiData();
		if (delta.length() < data->m_bfme90 + data->m_bfme94)
			return false;
		if (victim->isKindOf(KINDOF_WALL_UPGRADE))
			return false;
		if (rva00344EB2Gate(source, victim))
		{
			const Coord3D *dir = victim->getUnitDirectionVector2D();
			Real scale = victim->getGeometryRadiusB8() * 2.0f + 60.0f;
			delta = *dir;
			delta *= scale;
			m_goalPosition = m_prevVictimPos;
			m_goalPosition += delta;
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 30");
			setAdjustsDestination(false);
			ai->requestPath(&m_goalPosition, false);
			m_waitingForPath = ai->isWaitingForPath();
			return false;
		}
		Module *siege = 0;
		Module *portal = 0;
		if (victim->isKindOf(KINDOF_SIEGE_TOWER) && source->rva0028B511() != 1)
		{
			static NameKeyType key_SiegeDeploySpecialPower =
				TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
			siege = victim->findModule(key_SiegeDeploySpecialPower);
			portal = DynamicPortalBehaviour::rva004608E0(victim);
			if (siege && !((Rva004C5772CmpBoolField *)siege)->get())
				siege = 0;
		}
		Bool throughPortal = false;
		if (siege && portal && ((DynamicPortalBehaviour *)portal)->rva00460DF6(&m_goalPosition))
		{
			delta = m_goalPosition;
			delta.x -= prevPos->x;
			delta.y -= prevPos->y;
			delta.z -= prevPos->z;
			throughPortal = true;
		}
		delta.normalize();
		Real radius = victim->getGeometryRadiusB8();
		m_goalPosition = m_prevVictimPos;
		delta *= radius;
		m_goalPosition += delta;
		if (throughPortal)
		{
			for (int i = 0; i < 10; ++i)
			{
				if (TheAI->pathfinder()->IsPointOnWall((int)&m_goalPosition, false))
					break;
				m_goalPosition += delta;
			}
		}
		if (!ai->rva00263C06(&m_goalPosition, throughPortal))
		{
			m_waitingForPath = ai->isWaitingForPath();
			return false;
		}
		m_waitingForPath = ai->isWaitingForPath();
		return true;
	}
	return false;
}
