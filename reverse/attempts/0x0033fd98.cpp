// ?rva0033FD98@@YA_NPAVRva00343F8A@@PAX@Z
// partial score=0.93 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva0033FD98@@YA_NPAVRva00343F8A@@PAX@Z @0x0033FD98 61B.
// Goal-null test (cdecl, the else arm of the landed 0x343F8A dispatcher):
// fetches the current weapon via the rowed Object::getCurrentWeapon and
// probes it with the 0x2CB902 Weapon predicate over (self, mach+0x24, 0.0,
// 1), returning true only when the predicate reports false. The mach+0x24
// address is taken arithmetically (its true member type is unwitnessed);
// its null test is dead but byte-real.
class Object;
class Weapon;
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

class Weapon
{
public:
	char rva002CB902(Object *a, void *b, float range, int flags) const;
};

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
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

bool rva0033FD98(Rva00343F8A *st, void *arg)
{
	StateMachine *mach = st->m_machine;
	Object *self = mach->m_obj14;
	void *aux = (char *)mach + 0x24;
	const Weapon *weapon = self->getCurrentWeapon(0);
	if (weapon == 0 || aux == 0)
		return false;
	if (weapon->rva002CB902(self, aux, 0.0f, 1))
		return false;
	return true;
}
