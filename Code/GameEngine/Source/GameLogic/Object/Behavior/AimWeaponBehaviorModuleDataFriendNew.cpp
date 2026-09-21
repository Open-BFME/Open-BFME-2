// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AimWeaponBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024B0F7, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// pinned nullary ctor (0x45B1DD, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x45B215, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x14 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// AimWeaponBehaviorModuleData::buildFieldParse proc (Aim table 0xC41948)
// pushed as the factory's proc immediate; the pinned ctor fits the 0x18
// news size; the rowed poolkey 0x45B198 (AimWeaponBehavior) ends where the
// ctor begins. The ctor row supersedes its pin when its 0.98 bank lands.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AimWeaponBehaviorModuleData
{
public:
	AimWeaponBehaviorModuleData();
	virtual ~AimWeaponBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@AimWeaponBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AimWeaponBehaviorModuleData::friend_newModuleData(INI *ini)
{
	AimWeaponBehaviorModuleData *data = new AimWeaponBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AimWeaponBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
