// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@WeaponFireSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024DB56, 84 bytes. Dedicated TU: the factory news 0xDC, runs the
// pinned nullary ctor (0x4926CA, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x24DB00, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0xD8 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// WeaponFireSpecialAbilityUpdateModuleData::buildFieldParse proc (chained on
// the Rva0044EB54 base plus SpecialWeapon table 0xBEF0A8) pushed as the
// factory's proc immediate; the pinned ctor fits the 0xDC news size; the
// rowed poolkey 0x492685 (WeaponFireSpecialAbilityUpdate) ends where the
// ctor begins. The ctor row supersedes its pin when its xor/vtable wall falls.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class WeaponFireSpecialAbilityUpdateModuleData
{
public:
	WeaponFireSpecialAbilityUpdateModuleData();
	virtual ~WeaponFireSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xDC - 4];
};

// ?friend_newModuleData@WeaponFireSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponFireSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	WeaponFireSpecialAbilityUpdateModuleData *data = new WeaponFireSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WeaponFireSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
