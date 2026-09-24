// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@ArmorUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002545DB, 52 bytes. Dedicated TU: the factory news 0x120, runs
// the rowed ctor (0x254556, frameless over the OpenContain base with the
// folded vtable and KillArmorUpgrade/IgnoreArmorUpgrade/ArmorSetFlag
// stores), then feeds the new data plus the class parse proc (0x254580,
// pinned buildFieldParse over table 0x00DBA870) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its pin. Recipe:
// RadarUpgradeModuleDataFriendNew.cpp (/GX- keeps the factory frameless).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ArmorUpgradeModuleData
{
public:
	ArmorUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120];
};

// ?friend_newModuleData@ArmorUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ArmorUpgradeModuleData::friend_newModuleData(INI *ini)
{
	ArmorUpgradeModuleData *data = new ArmorUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ArmorUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
