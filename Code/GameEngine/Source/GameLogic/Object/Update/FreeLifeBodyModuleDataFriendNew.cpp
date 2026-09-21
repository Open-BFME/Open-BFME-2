// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@FreeLifeBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002516B1, 84 bytes. Dedicated TU: the factory news 0x88, runs
// the pinned ctor (0x4C1B3B, frameless body over the RespawnUpdate base with
// the FreeLife stores), then feeds the new data plus the class parse proc
// (rowed chained link at 0x4C184B, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x84 pad). Recipe:
// BaseUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// FreeLifeBodyModuleData::buildFieldParse proc (RespawnUpdate base proc plus
// table 0x0085BD38 holding FreeLifeHealthPercent at +0x6C plus FreeLifeTime
// at +0x70 plus FreeLifeInvincible at +0x74 plus FreeLifeAnimAndDuration at
// +0x78 plus FreeLifePrerequisiteUpgrade at +0x84) pushed as the factory's
// proc immediate; the FreeLifeBody pool key at 0x4C18AA sits in the same
// cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FreeLifeBodyModuleData
{
public:
	FreeLifeBodyModuleData();
	virtual ~FreeLifeBodyModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x88 - 4];
};

// ?friend_newModuleData@FreeLifeBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FreeLifeBodyModuleData::friend_newModuleData(INI *ini)
{
	FreeLifeBodyModuleData *data = new FreeLifeBodyModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FreeLifeBodyModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
