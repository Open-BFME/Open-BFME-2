// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Fresh target-backed corrections: invert owned3430A3 result; unsigned byte
// projection after a logical shift reproduces the native full-word flag read.
// Original entry-point name and flag meanings remain unproved.
// ?rva00343DD8@@YA_NPAX0@Z @0x00343DD8 269B.
// Goal-path test (cdecl, the taken arm of the landed 0x343F8A dispatcher):
// fetches the current weapon via the rowed Object::getCurrentWeapon, folds a
// per-slot flag byte through the vslot-137 predicate plus three +0x108/0x112
// quirk bits plus the +0x274 aux record, then OR-chains the Weapon predicates
// (rowed 0x47A699-shape bool, rowed byte get 0x2C9400, inverted flag compare,
// rowed isSignificantlyAboveTerrain) into the 0x3430A3 check, and finishes
// with the doubled rowed 0x2C95F0 guard plus isWithinAttackRange. The vslot
// call rides the established VSlots<137> template spelling.
class Object;
class Weapon;
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

template <int N>
class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <>
class VSlots<0>
{
};

class Rva00343DD8Slot : public VSlots<137>
{
public:
	virtual bool rva00343DD8Slot137() = 0;
};

struct Rva00343DD8Flags
{
	char m_pad[0x113];
};

struct Rva00343DD8Aux
{
	char m_pad00[4];
	Rva00343DD8Flags *m_flags; // +0x4
	char m_pad08[0x94 - 0x8];
	union {unsigned m_94; struct {unsigned low:6; unsigned flag6:1; unsigned high:25;};}; __forceinline unsigned char shifted() const { return m_94 >> 6; } // +0x94
};

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	bool isSignificantlyAboveTerrain() const;

	char m_pad00[4];
	Rva00343DD8Flags *m_flags4; // +0x4
	char m_pad08[0x258 - 0x8];
	Rva00343DD8Slot *m_slot258; // +0x258
	char m_pad25C[0x274 - 0x25c];
	Rva00343DD8Aux *m_aux274; // +0x274
};

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

class WeaponTemplate
{
public:
	bool isContactWeapon() const;
};

class Weapon
{
public:
	bool rva002C95F0() const;
	bool isWithinAttackRange(const Object *a, const Object *b, float range, int flags) const;

	char m_pad00[4];
	Rva002C9400ByteField *m_field4; // +0x4
};

class StateMachine
{
public:
	Object *getGoalObject();

	char m_pad00[0x14];
	Object *m_obj14; // +0x14
};

class Rva00343F8A
{
public:
	char m_pad00[0x18];
	StateMachine *m_machine; // +0x18
};

bool rva003430A3(Object*,Object*,Weapon*);

bool rva00343DD8(void *state, void *userData)
{
	Rva00343F8A *st = (Rva00343F8A *)state;
	StateMachine *mach = st->m_machine;
	Object *self = mach->m_obj14;
	Object *goal = mach->getGoalObject();
	const Weapon *weapon = self->getCurrentWeapon(0);
	if (goal == 0) return true;
	if (weapon != 0) {
		bool onGround = true;
		Rva00343DD8Slot *slot=self->m_slot258;
		bool viewBlocked=false;
		if(slot) onGround=slot->rva00343DD8Slot137();
		if ((self->m_flags4->m_pad[0x108] & 4) != 0)
			onGround = true;
		if ((self->m_flags4->m_pad[0x112] & 0x10) != 0)
			onGround = true;
		if (self->m_aux274 != 0) {
			if ((self->m_aux274->m_flags->m_pad[0x108] & 0x80) != 0
				|| (self->m_aux274->shifted() & 1) == 0)
				onGround = true;
		}
		if (!((const WeaponTemplate *)weapon->m_field4)->isContactWeapon()
			&& weapon->m_field4->get() == 0
			&& onGround
			&& !goal->isSignificantlyAboveTerrain())
			viewBlocked = !rva003430A3(self, goal, (Weapon*)weapon);
		if (!weapon->rva002C95F0() && viewBlocked) return true;
		if (!weapon->rva002C95F0() && !weapon->isWithinAttackRange(self,goal,0.0f,1)) return true;
	}
	return false;
}
