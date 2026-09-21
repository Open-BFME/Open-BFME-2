// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@CastleUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025585A, 52 bytes. Dedicated TU: the factory news 0x120, runs
// the pinned ctor (0x255836, frameless over the OpenContain base with the
// folded vtable and Upgrade zero plus WallUpgradeRadius float-zero; banked
// partial 0.97, row pending schedule lever), then feeds the new data plus
// the rowed class parse proc (0x4B6847, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its pin. Recipe:
// RadarUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// CastleUpgrade proc (Upgrade base proc 0x4CE29D plus table 0x008588C4
// holding Upgrade at +0x118 plus WallUpgradeRadius at +0x11C matching the
// ctor stores) pushed as the factory's proc immediate; the CastleUpgrade
// pool key at 0x4B682C ends where that proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CastleUpgradeModuleData
{
public:
	CastleUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120];
};

// ?friend_newModuleData@CastleUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CastleUpgradeModuleData::friend_newModuleData(INI *ini)
{
	CastleUpgradeModuleData *data = new CastleUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CastleUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
