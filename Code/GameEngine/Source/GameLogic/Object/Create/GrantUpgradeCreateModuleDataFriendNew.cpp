// cl: /GX /DNDEBUG /MD

// ?friend_newModuleData@GrantUpgradeCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00250B41, 81 bytes. Dedicated TU: the factory news 0x20, runs the
// declared-only nullary ctor (pinned at 0x4B90E1, sole caller is this
// factory), then feeds the new data plus the class parse proc (rowed at
// 0x4B8FF0, pushed immediate, UpgradeToGrant table 0x00C594A0 per the BFME1
// GrantUpgradeCreate donor) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x1C pad).
// Recipe: SupplyTruckAIUpdateModuleDataFriendNew.cpp. Class identity is the
// rowed GrantUpgradeCreateModuleData::buildFieldParse proc pushed as the
// factory's proc immediate; the ctor installs vtable 0x00C594E0 and fits the
// 0x20 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class GrantUpgradeCreateModuleData
{
public:
	GrantUpgradeCreateModuleData();
	virtual ~GrantUpgradeCreateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x20 - 4];
};

// ?friend_newModuleData@GrantUpgradeCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GrantUpgradeCreateModuleData::friend_newModuleData(INI *ini)
{
	GrantUpgradeCreateModuleData *data = new GrantUpgradeCreateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GrantUpgradeCreateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
