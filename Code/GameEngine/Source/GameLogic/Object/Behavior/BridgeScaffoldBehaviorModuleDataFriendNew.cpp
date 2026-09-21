// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "BridgeBehavior" (addModule
// pairs the name with this factory); formerly misnamed BridgeScaffoldBehaviorModuleData.
//
// ?friend_newModuleData@BridgeBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x0024AC3B, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// pinned nullary ctor (0x457FF1, sole raw caller is this factory at 0x24AC5C),
// then feeds the new data plus the rowed parse proc (0x458268, pushed
// immediate 0x858268) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x14 pad). Recipe:
// SlaveWatcherBehaviorModuleDataFriendNew.cpp. Class identity is the rowed
// BridgeBehaviorModuleData::buildFieldParse proc (table 0xC40B20:
// LateralScaffoldSpeed@8/VerticalScaffoldSpeed@C/BridgeDieFX@10/
// BridgeDieOCL@14) pushed as the factory's proc immediate; the rowed
// BridgeScaffoldBehavior pool key 0x4583E7 sits in the same cluster; the
// ctor installs vtable 0xC40A10 and fits the 0x18 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BridgeBehaviorModuleData
{
public:
	BridgeBehaviorModuleData();
	virtual ~BridgeBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@BridgeBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BridgeBehaviorModuleData::friend_newModuleData(INI *ini)
{
	BridgeBehaviorModuleData *data = new BridgeBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BridgeBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
