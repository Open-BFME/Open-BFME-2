// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AudioLoopUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00250798, 84 bytes. Dedicated TU: the factory news 0x154, runs
// the pinned ctor (0x4B7C00, EH body), then feeds the new data plus the class
// parse proc (pinned double-chained link at 0x4B7C86, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x150 pad). Recipe:
// BaseUpgradeModuleDataFriendNew.cpp. Class identity is the pinned
// AudioLoopUpgradeModuleData::buildFieldParse proc (two base procs plus
// table 0x00C58D98 holding SoundToPlay plus KillAfterMS plus KillOnDeath)
// pushed as the factory's proc immediate; the AudioLoopUpgrade pool key at
// 0x4B7BE0 sits in the same retail cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AudioLoopUpgradeModuleData
{
public:
	AudioLoopUpgradeModuleData();
	virtual ~AudioLoopUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x154 - 4];
};

// ?friend_newModuleData@AudioLoopUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AudioLoopUpgradeModuleData::friend_newModuleData(INI *ini)
{
	AudioLoopUpgradeModuleData *data = new AudioLoopUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AudioLoopUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
