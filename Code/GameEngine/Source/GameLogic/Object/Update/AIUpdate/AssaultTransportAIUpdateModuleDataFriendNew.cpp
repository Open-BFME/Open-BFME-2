// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AssaultTransportAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D29E, 81 bytes. Dedicated TU: the factory news 0x6C, runs the
// pinned ctor (0x24D221, frameless body over the pinned Transport base
// 0x26E5D7 with heal-ratio stores at +0x64 and +0x68), then feeds the new
// data plus the class parse proc (rowed base-call link at 0x24D248, pushed
// immediate, Transport base proc plus table 0x00BEED74 holding
// MembersGetHealedAtLifeRatio at +0x64 plus ClearRangeRequiredToContinueAttackMove
// at +0x68) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x68 pad).
// Recipe: WorkerAIUpdateModuleDataFriendNew.cpp. Class identity is the 2/2
// field-name-plus-offset match to BFME1's AssaultTransportAIUpdateModuleData
// table at identical offsets; the proc-VA push is unique image-wide and the
// ctor has a single raw caller (this factory).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AssaultTransportAIUpdateModuleData
{
public:
	AssaultTransportAIUpdateModuleData();
	virtual ~AssaultTransportAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x6C - 4];
};

// ?friend_newModuleData@AssaultTransportAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AssaultTransportAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	AssaultTransportAIUpdateModuleData *data = new AssaultTransportAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AssaultTransportAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
