// cl: /DNDEBUG /MD
//
// Made002CCBCA slots 5 and 6, retail 0x0050B7D2 (113 bytes) and 0x0050B843
// (112 bytes). Identity: slots 5/6 of the vtable 0x00864DFC (VA 0x00C64DFC) that
// the matched Made002CCBCA ctor 0x0050B8B3 installs (the HordeAttack nugget
// built by parseHordeAttackNugget; base Rva00507823); names by address, the
// class keeps its placeholder name. Both look the target Object up by the
// ObjectID at +8 of the first argument, fetch an interface from slot 31 of the
// Object +0x250 interface, lock the weapon slot stored at +0x12C temporarily
// unless it is 5 (the ctor default) through Object::setWeaponLock 0x00290B24,
// and forward (value, +0x128 flag as 0/1) to slot 1 (0x0050B7D2) or slot 0
// (0x0050B843) of that interface. The +0x250 pointer is read once into a local
// (retail mov/test, not a re-read of the member).

enum ObjectID
{
	INVALID_ID = 0
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};
// Interface returned by slot 31 of the Object +0x250 interface; slots 0 and 1
// take (int, int).
class Rva0050B7D2Target
{
public:
	virtual void rva0050B7D2Slot0(int a, int b) = 0;
	virtual void rva0050B7D2Slot1(int a, int b) = 0;
};
template <int N> class Rva0050B7D2Slots : public Rva0050B7D2Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0050B7D2Slots<0>
{
};
// The Object +0x250 interface: slots 0..30 placeholders, slot 31 below.
class Rva0050B7D2Iface : public Rva0050B7D2Slots<31>
{
public:
	virtual Rva0050B7D2Target *rva0050B7D2Slot31() = 0;
};
class Object
{
public:
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
	unsigned char m_pad000[0x250];
	Rva0050B7D2Iface *m_250; // +0x250
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
struct Rva0050B7D2Arg
{
	int m_00;
	int m_04;
	ObjectID m_08; // +0x08
};
class Rva00507823
{
public:
	virtual ~Rva00507823();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void rva0050B7D2(const Rva0050B7D2Arg *arg, int value);
	virtual void rva0050B843(const Rva0050B7D2Arg *arg, int value);
private:
	char m_pad04[0x128 - 4];
};
class Made002CCBCA : public Rva00507823
{
public:
	virtual void rva0050B7D2(const Rva0050B7D2Arg *arg, int value);
	virtual void rva0050B843(const Rva0050B7D2Arg *arg, int value);
private:
	unsigned char m_128; // +0x128
	char m_pad129[3];
	int m_12c; // +0x12C
};
void Made002CCBCA::rva0050B7D2(const Rva0050B7D2Arg *arg, int value)
{
	Object *object = TheGameLogic->findObjectByID(arg->m_08);
	if (!object)
		return;
	Rva0050B7D2Iface *iface = object->m_250;
	if (iface)
	{
		int flag = 0;
		if (m_128)
			flag = 1;
		Rva0050B7D2Target *target = iface->rva0050B7D2Slot31();
		if (target)
		{
			int slot = m_12c;
			if (slot != 5)
				object->setWeaponLock((WeaponSlotType)slot, LOCKED_TEMPORARILY);
			target->rva0050B7D2Slot1(value, flag);
		}
	}
}
void Made002CCBCA::rva0050B843(const Rva0050B7D2Arg *arg, int value)
{
	Object *object = TheGameLogic->findObjectByID(arg->m_08);
	if (!object)
		return;
	Rva0050B7D2Iface *iface = object->m_250;
	if (iface)
	{
		int flag = 0;
		if (m_128)
			flag = 1;
		Rva0050B7D2Target *target = iface->rva0050B7D2Slot31();
		if (target)
		{
			int slot = m_12c;
			if (slot != 5)
				object->setWeaponLock((WeaponSlotType)slot, LOCKED_TEMPORARILY);
			target->rva0050B7D2Slot0(value, flag);
		}
	}
}
