// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Retail 0x00220820 forwards the second argument's dword at +4 to the first.
// The callee is the rowed Object::releaseWeaponLock.
enum WeaponLockType { WEAPONLOCK_UNUSED1005 };
class Object
{
public:
	void releaseWeaponLock(WeaponLockType lock);
};

class BfmeItem1005
{
public:
	void bfmeDoD1005(int value);
};

struct Rva00220820Pair
{
	int first;
	int second;
};

void __cdecl rva00220820Forward(BfmeItem1005 *receiver, const Rva00220820Pair *value)
{
	((Object *)receiver)->releaseWeaponLock((WeaponLockType)value->second);
}
