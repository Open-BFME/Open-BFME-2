// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@StealthUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024EC60, 84 bytes. Dedicated TU: the factory news 0xC8, runs the
// declared-only nullary ctor (pinned at 0x37588B, sole caller is this
// factory), then feeds the new data plus the class parse proc (rowed at
// 0x373F2C, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0xC4 pad). Recipe: OCLUpdateModuleDataFriendNew.cpp. Class identity is
// retail's own INI table at 0x00C18210 (StealthDelay plus MoveThresholdSpeed
// plus StealthForbiddenConditions per ZH StealthUpdate.cpp) beside the rowed
// StealthUpdate bodies (isDisguised plus pool key plus name).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class StealthUpdateModuleData
{
public:
	StealthUpdateModuleData();
	virtual ~StealthUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xC8 - 4];
};

// ?friend_newModuleData@StealthUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StealthUpdateModuleData::friend_newModuleData(INI *ini)
{
	StealthUpdateModuleData *data = new StealthUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StealthUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
