// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ProneUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E918, 81 bytes. Dedicated TU: the factory news 0x0C, runs the
// declared-only ctor (rowed at 0x49FEDF, single ratio default), then feeds
// the new data plus the class parse proc (rowed at 0x49FEF5, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x08 pad). Recipe:
// SupplyWarehouseDockUpdateModuleDataFriendNew.cpp. Class identity is
// retail's own one-entry INI table at 0x00C51964 joined to the Zero Hour
// ProneUpdate donor (DamageToFramesRatio, parseReal).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ProneUpdateModuleData
{
public:
	ProneUpdateModuleData();
	virtual ~ProneUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x0C - 4];
};

// ?friend_newModuleData@ProneUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ProneUpdateModuleData::friend_newModuleData(INI *ini)
{
	ProneUpdateModuleData *data = new ProneUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ProneUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
