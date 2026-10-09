// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00343F8A@@YAXPAVRva00343F8A@@PAX@Z @0x00343F8A 38B.
//
// Goal-test dispatcher (cdecl): fetches the machine goal via rowed
// getGoalObject 0x004D7726 on the +0x18 StateMachine and routes the
// (state, opaque) pair to 0x00343DD8 when a goal exists, else to
// 0x0033FD98. The latter is rowed as a bool predicate in
// Rva0033FD98OutOfRange.cpp; this dispatcher discards its result.
// The state class mirrors only the proven +0x18 machine slot.
class Object;
class Weapon;
enum WeaponSlotType { PRIMARY = 0 };
enum CanAttackResult { RESULT_2 = 2, RESULT_3 = 3 };
enum AbleToAttackType { ATTACK_TYPE_0 = 0 };
enum CommandSourceType { COMMAND_SOURCE_0 = 0 };
class Object
{
public:
    const Weapon *getCurrentWeapon(WeaponSlotType *) const;
    bool isAbleToAttack() const;
    CanAttackResult getAbleToAttackSpecificObject(
        AbleToAttackType, const Object *, CommandSourceType) const;
};

class StateMachine
{
public:
	Object *getGoalObject();
    char unknown00[0x14];
    Object *owner;
};
class Rva00343F8A
{
public:
	char m_pad00[0x18];
	StateMachine *m_machine; // +0x18
};
void rva00343DD8(Rva00343F8A *st, void *arg);
bool rva0033FD98(Rva00343F8A *st, void *arg);

void rva00343F8A(Rva00343F8A *st, void *arg2)
{
	if (st->m_machine->getGoalObject() != 0)
		rva00343DD8(st, arg2);
	else
		rva0033FD98(st, arg2);
}

// Retail 33FDD6..33FDEB is an independent 21B cdecl wrapper after the
// rowed 62B predicate and before the distinct 33FDEB prologue. It forwards
// both stack arguments and inverts AL. The table at 813188 contains this
// callback with transition ID 601 and null user data. Original name unknown.
bool rva0033FDD6(Rva00343F8A *st, void *arg)
{
	return !rva0033FD98(st, arg);
}

// Retail33FDEB..33FE65 is a separate122B cdecl bool predicate after
// the 21B inversion wrapper; Ghidra groups all three bodies as205B.
// Both stack arguments are consumed: the state supplies machine+18 and
// owner+14; opaque data is the existing AbleToAttackType argument.
// Goal438 bit0, weapon-template16B and owner AI258/slot23C are independently
// measured access prefixes, with original field names left unknown.
// Declaration-only slot view; no instance or vtable is emitted here.
template<int N>
class ConditionAISlots : public ConditionAISlots<N-1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template<> class ConditionAISlots<0> {};
class ConditionAIView : public ConditionAISlots<143>
{
public:
    virtual CommandSourceType source() = 0;
};
struct ConditionOwnerView { char prefix[0x258]; ConditionAIView *ai; };
struct ConditionGoalView { char prefix[0x438]; unsigned char flags; };
struct ConditionWeaponTemplateView { char prefix[0x16b]; bool flag; };
struct ConditionWeaponView { char first[4]; ConditionWeaponTemplateView *info; };
bool rva0033FDEB(Rva00343F8A *state, void *data)
{
    StateMachine *machine = state->m_machine;
    Object *owner = machine->owner;
    Object *goal = machine->getGoalObject();
    if (!goal || (reinterpret_cast<ConditionGoalView *>(goal)->flags & 1))
    {
        const Weapon *weapon = owner->getCurrentWeapon(0);
        if (weapon && reinterpret_cast<const ConditionWeaponView *>(weapon)->info->flag)
            return false;
    }
    if (owner && goal)
    {
        CanAttackResult result;
        if (!owner->isAbleToAttack() ||
            ((result = owner->getAbleToAttackSpecificObject(
                static_cast<AbleToAttackType>(reinterpret_cast<unsigned>(data)), goal,
                reinterpret_cast<ConditionOwnerView *>(owner)->ai->source())) != RESULT_3
                && result != RESULT_2))
            return true;
    }
    return false;
}
