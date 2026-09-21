// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@RadarUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00254741, 52 bytes. Dedicated TU: the factory news 0x11C, runs
// the rowed ctor (0x2546D2, frameless over the OpenContain base with the
// folded vtable and DisableProof false), then feeds the new data plus the
// rowed class parse proc (0x4B476C, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its pin. Recipe:
// GeometryUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// RadarUpgrade proc (Upgrade base proc 0x4CE29D plus table 0x008578D0
// holding DisableProof at +0x118 matching the ctor store) pushed as the
// factory's proc immediate; the RadarUpgrade pool key at 0x4B4727 ends
// where that proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RadarUpgradeModuleData
{
public:
	RadarUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x11C];
};

// ?friend_newModuleData@RadarUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RadarUpgradeModuleData::friend_newModuleData(INI *ini)
{
	RadarUpgradeModuleData *data = new RadarUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RadarUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
