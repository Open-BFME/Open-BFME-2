// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DelayedDeathBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00251622, 84 bytes. Dedicated TU: the factory news 0x80, runs
// the rowed ctor (0x4C180A, frameless body over the RespawnUpdate base with
// the DelayedDeath stores), then feeds the new data plus the class parse
// proc (rowed chained link at 0x4C159E, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x7C pad). Recipe:
// FreeLifeBodyModuleDataFriendNew.cpp. Class identity is the rowed
// DelayedDeathBodyModuleData::buildFieldParse proc (RespawnUpdate base proc
// plus table 0x0085BAE8 holding DelayedDeathTime at +0x6C plus
// ImmortalUntilDeathTime at +0x70 plus InvulnerableFX at +0x74 plus
// DoHealthCheck at +0x78 plus DelayedDeathPrerequisiteUpgrade at +0x7C)
// pushed as the factory's proc immediate; the DelayedDeathBody pool key at
// 0x4C1642 sits in the same cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DelayedDeathBodyModuleData
{
public:
	DelayedDeathBodyModuleData();
	virtual ~DelayedDeathBodyModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x80 - 4];
};

// ?friend_newModuleData@DelayedDeathBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DelayedDeathBodyModuleData::friend_newModuleData(INI *ini)
{
	DelayedDeathBodyModuleData *data = new DelayedDeathBodyModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DelayedDeathBodyModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
