// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@LevelGrantSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00251A72, 84 bytes. Dedicated TU: the factory news 0xD8, runs
// the rowed ctor (0x4C2AA0, EH body over the Rva0044EB54 base with the
// Experience plus RadiusEffect zeros and the AcceptanceFilter member and
// the LevelFX zero), then feeds the new data plus the class parse proc
// (rowed chained link at 0x4C2AF3, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0xD4 pad). Class identity is
// the rowed LevelGrantSpecialPowerModuleData::buildFieldParse proc (Rva
// base proc plus table 0x0085C8D0 holding Experience at +0xC8 plus
// RadiusEffect at +0xCC plus AcceptanceFilter at +0xD0 plus LevelFX at
// +0xD4) pushed as the factory's proc immediate; the LevelGrantSpecialPower
// pool key at 0x4C2BC1 sits in the same cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class LevelGrantSpecialPowerModuleData
{
public:
	LevelGrantSpecialPowerModuleData();
	virtual ~LevelGrantSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD8 - 4];
};

// ?friend_newModuleData@LevelGrantSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LevelGrantSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	LevelGrantSpecialPowerModuleData *data = new LevelGrantSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, LevelGrantSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
