// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CaveContainModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00257714, 84 bytes (the 0x0025770D triage hit is an interior pad
// plus jump; the true body starts at the mov-eax plus __EH_prolog head).
// Dedicated TU: the factory news 0x9C, runs the pinned ctor (0x466D37,
// frameless body over the pinned opaque base 0x465124 with the CaveIndex
// clear at +0x98), then feeds the new data plus the class parse proc (rowed
// base-call link at 0x24B77C, pushed immediate, OpenContain base proc plus
// table 0x00BEEAC8 holding CaveIndex at +0x98) to INI::initFromINIMultiProc
// (rowed at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog
// resolve via their rows. The TU-local class keeps only size and
// virtuality (vptr plus 0x98 pad). Recipe:
// WorkerAIUpdateModuleDataFriendNew.cpp. Class identity is the 1/1
// field-name-plus-offset match to BFME1's CaveContainModuleData table at
// the identical offset plus the rowed CaveContain pool key; the proc-VA
// push is unique image-wide and the ctor has a single ModuleData caller
// (this factory; the TimeForFullHeal factory shares the fold).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CaveContainModuleData
{
public:
	CaveContainModuleData();
	virtual ~CaveContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x9C - 4];
};

// ?friend_newModuleData@CaveContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CaveContainModuleData::friend_newModuleData(INI *ini)
{
	CaveContainModuleData *data = new CaveContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CaveContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
