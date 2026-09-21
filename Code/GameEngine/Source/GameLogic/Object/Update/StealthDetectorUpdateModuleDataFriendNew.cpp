// cl: /O1 /DNDEBUG /MD
//
// ?friend_newModuleData@StealthDetectorUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002553C5, 42 bytes. Dedicated TU, frameless shape: the factory
// news 0x70, runs the declared-only ctor (pinned at 0x255371) under a
// null-checked new, then feeds the new data plus the class parse proc (rowed
// at 0x4A2D82, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed
// at 0x2DEB5) when ini is non-null. Operator new resolves via its row. The
// TU-local class keeps only size (0x70 pad, no virtuals, so no vptr and no
// EH prolog). Class identity is retail's own DetectionRate-led INI table at
// 0x00C52188 (landed buildFieldParse row) beside the rowed
// StealthDetectorUpdate pool key (0x4A2C74).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class StealthDetectorUpdateModuleData
{
public:
	StealthDetectorUpdateModuleData() throw();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x70];
};

// ?friend_newModuleData@StealthDetectorUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StealthDetectorUpdateModuleData::friend_newModuleData(INI *ini)
{
	StealthDetectorUpdateModuleData *data = new StealthDetectorUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StealthDetectorUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
