// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DualWeaponBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024B06E, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// rowed nullary ctor (0x45AE25, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x45AE44, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x14 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// DualWeaponBehaviorModuleData::buildFieldParse proc (SwitchWeapon table
// 0xC41858) pushed as the factory's proc immediate; the ctor installs the
// folded vtable 0x00C4ED70 and fits the 0x18 news size; the rowed poolkey
// 0x45ADE0 (DualWeaponBehavior) ends where the ctor begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DualWeaponBehaviorModuleData
{
public:
	DualWeaponBehaviorModuleData();
	virtual ~DualWeaponBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@DualWeaponBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DualWeaponBehaviorModuleData::friend_newModuleData(INI *ini)
{
	DualWeaponBehaviorModuleData *data = new DualWeaponBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DualWeaponBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
