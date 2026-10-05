// cl: /O1 /DNDEBUG /MD
//
// ?rva003412DB@Rva003412DB@@QAE?AW4StateReturnType@@XZ @0x003412DB 94B.
//
// Goal-object validation returning STATE_CONTINUE (0) or STATE_FAILURE
// (-2): with a goal, fail fast on its +0x438 bit0, else query the owner's
// +0x250 interface (slot 31) and its +0x148/+0x14c predicates; without a
// goal use the +0x14c predicate alone. The machine (this+0x18) supplies the
// goal via rowed getGoalObject 0x004D7726 and the owner at +0x14.
//
// Evidence: StateReturnType values proven by the xor-eax/push-minus-2
// epilogue; far-slot virtuals via the VSlots stair (AIDockStates pattern);
// the inverted returns (CONTINUE in the arms, FAILURE at the tail) are what
// reproduce retail's je-fail tail -- the De Morgan-equivalent all-FAILURE
// arms fold it branchless or flip its polarity. Interface and member names
// past the proven slots/flags carry no identity claim.
typedef bool Bool;
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
class Object;
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class XInterface : public VSlots<82>
{
public:
	virtual Bool slot82(Object *o) = 0;
	virtual Bool slot83() = 0;
};
class Owner250Interface : public VSlots<31>
{
public:
	virtual XInterface *slot31() = 0;
};
class Object
{
public:
	char m_pad00[0x250];
	Owner250Interface *m_250owner; // +0x250
	char m_pad254[0x438 - 0x254];
	unsigned char m_flag438; // +0x438 bit0 tested
};
class StateMachine
{
public:
	Object *getGoalObject();
	char m_pad00[0x14];
	Object *m_owner; // +0x14
};
class Rva003412DB
{
public:
	StateReturnType rva003412DB();
	char m_pad00[0x18];
	StateMachine *m_machine; // +0x18
};

StateReturnType Rva003412DB::rva003412DB()
{
	Object *goal = m_machine->getGoalObject();
	Object *owner = m_machine->m_owner;
	if (goal != 0) {
		if ((goal->m_flag438 & 1) != 0)
			return STATE_FAILURE;
		if (owner->m_250owner->slot31()->slot82(goal))
			return STATE_CONTINUE;
	} else {
		if (owner->m_250owner->slot31()->slot83())
			return STATE_CONTINUE;
	}
	return STATE_FAILURE;
}
