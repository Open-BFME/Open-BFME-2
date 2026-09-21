// cl: /O1 /DNDEBUG /MD
//
// ?friend_newModuleData@LevelUpUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025469E, 52 bytes. Dedicated TU: the factory news 0x120, runs
// the rowed ctor (0x25467E, frameless over the rowed OpenContain base with
// vtable 0xBF24A0 plus LevelsToGain and LevelCap zeros), then feeds the new
// data plus the class parse proc (rowed double-add link at 0x4B3DA6, pushed
// immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new resolves via its row. The TU-local class keeps
// only size and virtuality (vptr plus 0x11C pad). Recipe:
// TemporarilyDefectUpdateModuleDataFriendNew.cpp (frameless 52B precedent).
// Class identity is the rowed LevelUpUpgradeModuleData::buildFieldParse proc
// (getter table plus table 0x00C574AC holding LevelsToGain at +0x118 plus
// LevelCap at +0x11C) pushed as the factory's proc immediate; the
// LevelUpUpgrade pool key at 0x4B3D61 sits in the same retail cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class LevelUpUpgradeModuleData
{
public:
	LevelUpUpgradeModuleData() throw();
	virtual ~LevelUpUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120 - 4];
};

// ?friend_newModuleData@LevelUpUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LevelUpUpgradeModuleData::friend_newModuleData(INI *ini)
{
	LevelUpUpgradeModuleData *data = new LevelUpUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, LevelUpUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
