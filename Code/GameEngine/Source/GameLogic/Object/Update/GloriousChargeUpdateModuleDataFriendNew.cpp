// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@GloriousChargeUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024F61B, 84 bytes. Dedicated TU: the factory news 0xD4, runs
// the pinned ctor (0x4AD4F2, frameless body over the Rva0044EB54 base with
// the BonusRadius float plus the SpeechDuration and UpdateInterval zeros),
// then feeds the new data plus the class parse proc (rowed chained link at
// 0x4AD51D, pushed immediate) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0xD0 pad). Recipe: BaseUpgradeModuleDataFriendNew.cpp. Class identity is
// the rowed GloriousChargeUpdateModuleData::buildFieldParse proc (Rva0044EB54
// base proc plus table 0x008550C8 holding BonusRadius at +0xC8 plus
// SpeechDuration at +0xCC plus UpdateInterval at +0xD0) pushed as the
// factory's proc immediate; the GloriousChargeUpdate pool key at 0x4AD5CE
// sits in the same cluster and the ctor ends where the proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class GloriousChargeUpdateModuleData
{
public:
	GloriousChargeUpdateModuleData();
	virtual ~GloriousChargeUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD4 - 4];
};

// ?friend_newModuleData@GloriousChargeUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GloriousChargeUpdateModuleData::friend_newModuleData(INI *ini)
{
	GloriousChargeUpdateModuleData *data = new GloriousChargeUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GloriousChargeUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
