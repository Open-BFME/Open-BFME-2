// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@LargeGroupBonusUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D43F, 81 bytes. Dedicated TU: the factory news 0x30, runs the
// declared-only ctor (pinned at 0x4901BD, sole raw caller, vtable 0xC4D2A8,
// HordeMemberFilter-led stores over table 0xC4D1A8), then feeds the new data
// plus the class parse proc (rowed at 0x4900A0, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x2C pad). Recipe:
// RebuildHoleBehaviorModuleDataFriendNew.cpp. Class identity is retail's own
// HordeMemberFilter-led INI table at 0x00C4D1A8 (landed buildFieldParse row)
// beside the rowed LargeGroupBonusUpdate pool key (0x48FFD4).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class LargeGroupBonusUpdateModuleData
{
public:
	LargeGroupBonusUpdateModuleData();
	virtual ~LargeGroupBonusUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x30 - 4];
};

// ?friend_newModuleData@LargeGroupBonusUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LargeGroupBonusUpdateModuleData::friend_newModuleData(INI *ini)
{
	LargeGroupBonusUpdateModuleData *data = new LargeGroupBonusUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, LargeGroupBonusUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
