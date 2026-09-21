// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@LargeGroupAudioUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024F362, 81 bytes. Dedicated TU: the factory news 0x20, runs the
// declared-only ctor (pinned at 0x4ABED8, sole raw caller, vtable 0xC549F8,
// TimeBetweenUpdatesMin/Variation/UnitWeight/Key stores over table 0xC54868),
// then feeds the new data plus the class parse proc (rowed at 0x4AB800,
// pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x1C pad).
// Recipe: RebuildHoleBehaviorModuleDataFriendNew.cpp. Class identity is
// retail's own TimeBetweenUpdates-led INI table at 0x00C54868 (landed
// buildFieldParse row) beside the rowed LargeGroupAudioUpdate pool key
// (0x4AB897).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class LargeGroupAudioUpdateModuleData
{
public:
	LargeGroupAudioUpdateModuleData();
	virtual ~LargeGroupAudioUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x20 - 4];
};

// ?friend_newModuleData@LargeGroupAudioUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LargeGroupAudioUpdateModuleData::friend_newModuleData(INI *ini)
{
	LargeGroupAudioUpdateModuleData *data = new LargeGroupAudioUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, LargeGroupAudioUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
