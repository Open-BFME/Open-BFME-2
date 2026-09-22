// cl: /O1 /DNDEBUG /MD
//
// ?friend_newModuleData@SlavedUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00255340, 49 bytes. Dedicated TU, frameless shape: the factory
// news 0x70, runs the declared-only ctor (pinned at 0x2552D7, sole raw E8
// caller) under a null-checked new, then feeds the new data plus the class
// parse proc (rowed at 0x2542E2, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its row. The TU-local class keeps only size
// (0x70 pad, no virtuals, so no vptr and no EH prolog). Class identity is
// the ZH SlavedUpdate table with BFME2 LeashRange (landed buildFieldParse
// row) beside the rowed SlavedUpdate pool key (0x4A1875).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SlavedUpdateModuleData
{
public:
	SlavedUpdateModuleData() throw();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x70];
};

// ?friend_newModuleData@SlavedUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlavedUpdateModuleData::friend_newModuleData(INI *ini)
{
	SlavedUpdateModuleData *data = new SlavedUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SlavedUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
