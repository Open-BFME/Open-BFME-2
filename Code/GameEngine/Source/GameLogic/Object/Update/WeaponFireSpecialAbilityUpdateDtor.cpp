// cl: /O1 /DNDEBUG /MD /GX /arch:SSE

// ??1WeaponFireSpecialAbilityUpdate@@UAE@XZ @0x0049256B 106B
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Update/WeaponFireSpecialAbilityUpdateDestructorThunk.cpp
// (4 vtables +0/+0xC/+0x10/+0x20, delete heap ptr, base dtor). BFME2 retail:
// same 4 slots (0xC4E090/0xC4D640/0xC4E080/0xC4E05C), heap Weapon* at +0x88
// (base 0x88, not 0xE8), delete via virtual deleteInstance slot0 with 0
// return-fed to rowed operator delete 0x2FD60, clear to zero, then pinned
// base ??1Rva0044EF5E at 0x00451F45. Shape follows FireWeaponWhenDamagedBehaviorDtor
// at 0x00482551 and FireWeaponCollideDtor at 0x004BB6A7.
// Caller: ??_G at 0x004927B4.

class Thing;
class ModuleData;

class Weapon
{
public:
	virtual void *deleteInstance(int flags);
};

class WFS_RootBase
{
public:
	virtual ~WFS_RootBase();

private:
	unsigned char m_pad[8];
};

class WFS_Iface1
{
public:
	virtual void slot();
};

class WFS_Iface2
{
public:
	virtual void slot();

private:
	unsigned char m_pad[0xC];
};

class WFS_Iface3
{
public:
	virtual void slot();
};

class Rva0044EF5E : public WFS_RootBase, public WFS_Iface1, public WFS_Iface2, public WFS_Iface3
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();

private:
	unsigned char m_pad[0x64];
};

class WeaponFireSpecialAbilityUpdate : public Rva0044EF5E
{
public:
	WeaponFireSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~WeaponFireSpecialAbilityUpdate();

private:
	Weapon *m_weapon;
};

WeaponFireSpecialAbilityUpdate::~WeaponFireSpecialAbilityUpdate()
{
	void *toDelete;
	if (m_weapon != 0)
		toDelete = m_weapon->deleteInstance(0);
	else
		toDelete = 0;
	::operator delete(toDelete);
	m_weapon = 0;
}
