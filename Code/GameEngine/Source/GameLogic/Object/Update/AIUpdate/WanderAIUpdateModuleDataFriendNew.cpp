// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@WanderAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024F248, 81 bytes. Dedicated TU: the factory news 0x74, runs the
// pinned ctor (0x24F1CD, frameless body over base 0x26E5D7), then feeds the
// new data plus the class parse proc (pinned chained link at 0x24F1F2,
// pushed immediate, base proc plus table 0x00BEF580 holding WildBeast at
// +0x64 plus ConditionForEntry at +0x68 plus Selectable at +0x6C plus
// WanderDistance at +0x70) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x70 pad).
// Recipe: SpecialEnemySenseUpdateModuleDataFriendNew.cpp. Class identity is
// the retail registrar at 0x25A193 pairing behavior WanderAIUpdate with this
// factory (plus behavior factory 0x24F20D); no ZH/BFME1 donor exists.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class WanderAIUpdateModuleData
{
public:
	WanderAIUpdateModuleData();
	virtual ~WanderAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x74 - 4];
};

// ?friend_newModuleData@WanderAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WanderAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	WanderAIUpdateModuleData *data = new WanderAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WanderAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
