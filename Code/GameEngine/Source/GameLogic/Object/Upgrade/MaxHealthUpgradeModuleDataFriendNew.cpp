// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@MaxHealthUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002504BA, 84 bytes. Dedicated TU: the factory news 0x120, runs
// the rowed ctor (0x4B62C4, frameless over the OpenContain base with the
// folded vtable and ChangeType zero plus AddMaxHealth float-zero), then
// feeds the new data plus the rowed class parse proc (0x4B62E8, pushed
// immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. Recipe:
// GeometryUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// MaxHealthUpgrade proc (Upgrade base proc 0x4CE29D plus table 0x008585DC
// holding AddMaxHealth at +0x118 plus ChangeType at +0x11C matching the
// ctor stores) pushed as the factory's proc immediate; the rowed
// MaxHealthUpgrade pool key at 0x4B627F ends where the ctor begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class MaxHealthUpgradeModuleData
{
public:
	MaxHealthUpgradeModuleData();
	virtual ~MaxHealthUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120 - 4];
};

// ?friend_newModuleData@MaxHealthUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *MaxHealthUpgradeModuleData::friend_newModuleData(INI *ini)
{
	MaxHealthUpgradeModuleData *data = new MaxHealthUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, MaxHealthUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
