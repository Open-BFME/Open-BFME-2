// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@DoCommandUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002557B5, 52 bytes. Dedicated TU: the factory news 0x120, runs
// the rowed ctor (0x255795, frameless over the OpenContain base with the
// folded vtable and two command-button zeros), then feeds the new data plus
// the rowed class parse proc (0x4B4C0C, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its pin. Recipe:
// RadarUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// DoCommandUpgrade proc (Upgrade base proc 0x4CE29D plus table 0x00857BC4
// holding GetUpgradeCommandButtonName at +0x118 plus
// RemoveUpgradeCommandButtonName at +0x11C matching the ctor stores)
// pushed as the factory's proc immediate; the DoCommandUpgrade pool key at
// 0x4B4BF1 ends where that proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DoCommandUpgradeModuleData
{
public:
	DoCommandUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120];
};

// ?friend_newModuleData@DoCommandUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DoCommandUpgradeModuleData::friend_newModuleData(INI *ini)
{
	DoCommandUpgradeModuleData *data = new DoCommandUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DoCommandUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
