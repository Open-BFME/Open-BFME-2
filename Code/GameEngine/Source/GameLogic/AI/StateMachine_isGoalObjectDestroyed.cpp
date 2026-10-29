// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// ?isGoalObjectDestroyed@StateMachine@@QBE_NXZ at retail 0x004D7ADD (30B).
//
// Target facts: `cmp [ecx+0x20],0 / jne / xor al,al / ret`, then a call to
// 0x004D7726, null -> `mov al,1`, else `mov al,[eax+0x438] / and al,1`.
// +0x20 is StateMachine's m_goalObjectID: the matched
// StateMachine::internalSetGoalObject 0x004D7435 (StateMachineGoal.cpp) writes
// the goal object's id there, and 0x004D7726 (rowed as
// TurretStateMachine::getGoalObject, pinned as StateMachine::getGoalObject)
// looks that id up through TheGameLogic. Object +0x438 bit 0 is the
// effectively-dead status bit. The body sits in StateMachine.cpp's run
// 0x004D7127..0x004D7B0F, just before StateMachine::defineState 0x004D7B0F.
// Donor facts: Zero Hour and BFME 1 StateMachine.cpp define
// `Bool StateMachine::isGoalObjectDestroyed() const` as
// `if (m_goalObjectID == 0) return false; return getGoalObject() == NULL;`.
// BFME 2 also reports an effectively dead goal as destroyed.
// The const getGoalObject overload is the same body as the non-const one
// (identical-code folded at 0x004D7726), so the call goes through the
// non-const spelling the ledger resolves, as AIGuardStates.cpp does.

typedef bool Bool;
typedef unsigned int ObjectID;

class Object
{
public:
	Bool isEffectivelyDead() const { return m_effectivelyDead; }

private:
	unsigned char m_pad000[0x438];
	unsigned char m_effectivelyDead : 1; // +0x438 bit 0 of the private status byte
	unsigned char m_otherStatus : 7;
};

class StateMachine
{
public:
	Object *getGoalObject();
	Bool isGoalObjectDestroyed() const;

private:
	unsigned char m_pad00[0x20]; // +0x00..0x1F (vtable + members)
	ObjectID m_goalObjectID; // +0x20
};

Bool StateMachine::isGoalObjectDestroyed() const
{
	if (m_goalObjectID == 0)
		return false; // never had a goal object
	const Object *goal = const_cast<StateMachine *>(this)->getGoalObject();
	if (goal == 0)
		return true;
	return goal->isEffectivelyDead();
}
