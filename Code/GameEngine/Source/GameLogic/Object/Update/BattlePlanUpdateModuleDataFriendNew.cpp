// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@BattlePlanUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E237, 84 bytes. Dedicated TU: the factory news 0xA8, runs the
// declared-only ctor (pinned at 0x49780A, donor-backed BattlePlanUpdate body
// banked as a 0.88 partial against MSVC7.1 scheduling walls), then feeds the
// new data plus the class parse proc (present-unmatched at 0x49861A, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0xA4 pad). Recipe:
// BoredUpdateModuleDataFriendNew.cpp. Class identity is the BFME1
// BattlePlanUpdate donor (BattlePlanUpdate.cpp ctor plus 30-field table at
// 0x00C4FF58) in the BattlePlanUpdate file-unit. The same-named proc row at
// 0x4CBBB4 covers a single SoundUpgrade field and is left for fleet consensus.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BattlePlanUpdateModuleData
{
public:
	BattlePlanUpdateModuleData();
	virtual ~BattlePlanUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xA8 - 4];
};

// ?friend_newModuleData@BattlePlanUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BattlePlanUpdateModuleData::friend_newModuleData(INI *ini)
{
	BattlePlanUpdateModuleData *data = new BattlePlanUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BattlePlanUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
