// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DemoTrapUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E010, 81 bytes. Dedicated TU: the factory news 0x40, runs the
// declared-only ctor (rowed at 0x49597A, vtable plus detonation fields), then
// feeds the new data plus the class parse proc (rowed at 0x495AA9, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x3C pad).
// Recipe: ProneUpdateModuleDataFriendNew.cpp. Class identity is retail's own
// ten-entry INI table at 0x00C4EEC8 (landed buildFieldParse row) joined to
// the Zero Hour DemoTrapUpdate donor.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DemoTrapUpdateModuleData
{
public:
	DemoTrapUpdateModuleData();
	virtual ~DemoTrapUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x40 - 4];
};

// ?friend_newModuleData@DemoTrapUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DemoTrapUpdateModuleData::friend_newModuleData(INI *ini)
{
	DemoTrapUpdateModuleData *data = new DemoTrapUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DemoTrapUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
