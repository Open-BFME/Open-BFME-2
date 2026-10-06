// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RunOffMapBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00254F24, 81 bytes. Dedicated TU: the factory news 0x1C, runs the
// declared-only ctor (pinned at 0x254ECE, EH body with vtable 0xBF3298 and
// the rowed-proc table layout), then feeds the new data plus the class parse
// proc (rowed at 0x46216A, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x18 pad). Recipe:
// DumbProjectileBehaviorModuleDataFriendNew.cpp. Class identity is retail's
// own INI table at 0x00C42F70 (RunToLocation/RequiresSpecificTrigger/
// RunOffMapWaypointName/DieOnMap) plus the RunOffMapBehavior pool key.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RunOffMapBehaviorModuleData
{
public:
	RunOffMapBehaviorModuleData();
	virtual ~RunOffMapBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@RunOffMapBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RunOffMapBehaviorModuleData::friend_newModuleData(INI *ini)
{
	RunOffMapBehaviorModuleData *data = new RunOffMapBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RunOffMapBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
