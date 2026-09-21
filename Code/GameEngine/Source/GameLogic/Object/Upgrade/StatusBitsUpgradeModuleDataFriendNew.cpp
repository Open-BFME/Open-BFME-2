// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@StatusBitsUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025479D, 52 bytes. Dedicated TU: the factory news 0x138, runs
// the rowed ctor (0x254775, frameless over the OpenContain base with the
// folded vtable and the two bitset resets), then feeds the new data plus
// the rowed class parse proc (0x4B493E, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its pin. Recipe:
// RadarUpgradeModuleDataFriendNew.cpp (/GX- for the frameless shape).
// Class identity is the rowed StatusBitsUpgrade proc (Upgrade base proc
// 0x4CE29D plus table 0x00857984 holding StatusToSet at +0x118 plus
// StatusToClear at +0x128 matching the ctor stores) pushed as the
// factory's proc immediate; the StatusBitsUpgrade pool key at 0x4B48F9
// ends where that proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class StatusBitsUpgradeModuleData
{
public:
	StatusBitsUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x138];
};

// ?friend_newModuleData@StatusBitsUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StatusBitsUpgradeModuleData::friend_newModuleData(INI *ini)
{
	StatusBitsUpgradeModuleData *data = new StatusBitsUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StatusBitsUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
