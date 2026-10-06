// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AutoDepositUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00254152, 81 bytes. Dedicated TU: the factory news 0x24, runs the
// rowed nullary ctor (0x2540ED, sole caller is this factory; installs vtable
// 0x00BF1BC8), then feeds the new data plus the class parse proc (rowed at
// 0x254141, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x20 pad). Recipe: SupplyTruckAIUpdateModuleDataFriendNew.cpp. Class
// identity is the rowed AutoDepositUpdateModuleData::buildFieldParse proc
// (table 0x00BF1CC8: DepositTiming plus Upgrade plus DepositAmount plus
// InitialCaptureBonus plus UpgradeBonusPercent plus UpgradeMustBePresent plus
// GiveNoXP plus OnlyWhenGarrisoned) pushed as the factory's proc immediate.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AutoDepositUpdateModuleData
{
public:
	AutoDepositUpdateModuleData();
	virtual ~AutoDepositUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x24 - 4];
};

// ?friend_newModuleData@AutoDepositUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AutoDepositUpdateModuleData::friend_newModuleData(INI *ini)
{
	AutoDepositUpdateModuleData *data = new AutoDepositUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AutoDepositUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
