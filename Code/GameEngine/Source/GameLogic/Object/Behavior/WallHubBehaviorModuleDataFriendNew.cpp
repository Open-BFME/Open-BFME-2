// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@WallHubBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024A94C, 81 bytes. Dedicated TU: the factory news 0x3C, runs the
// pinned nullary ctor (0x453020, sole raw caller is this factory at 0x24A96D),
// then feeds the new data plus the rowed parse proc (0x452DEF, pushed
// immediate 0x852DEF) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x38 pad). Recipe:
// SlaveWatcherBehaviorModuleDataFriendNew.cpp. Class identity is the rowed
// WallHubBehaviorModuleData::buildFieldParse proc (table 0xC3FED8:
// SegmentTemplateName@8/DefaultSegmentTemplateName@18/HubCapTemplateName@14/
// CliffCapTemplateName@1C/ShoreCapTemplateName@20/BorderCapTemplateName@24/
// ElevatedSegmentTemplateName@28/StaggeredBuildFactor@38/BuilderRadius@2C/
// MaxBuildoutDistance@30/Options@34) pushed as the factory's proc immediate;
// the rowed WallHubBehavior pool key 0x452DCD sits in the same cluster; the
// ctor installs vtable 0xC3FF98 and fits the 0x3C news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class WallHubBehaviorModuleData
{
public:
	WallHubBehaviorModuleData();
	virtual ~WallHubBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x3C - 4];
};

// ?friend_newModuleData@WallHubBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WallHubBehaviorModuleData::friend_newModuleData(INI *ini)
{
	WallHubBehaviorModuleData *data = new WallHubBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WallHubBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
