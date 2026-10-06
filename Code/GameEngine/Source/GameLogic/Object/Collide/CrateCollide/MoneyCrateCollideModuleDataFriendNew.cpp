// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@MoneyCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00256310, 81 bytes. Dedicated TU: the factory news 0x60, runs the
// pinned ctor (0x2562FA, frameless body over the rowed CrateCollide base
// 0x4BC657 clearing +0x5C under the folded vtable 0x00BF3AC0 shared with the
// VeterancyCrate sibling), then feeds the new data plus the class parse proc
// (pinned chained link at 0x251168, pushed immediate, base CrateCollide proc
// plus table 0x00BEFABC holding MoneyProvided at +0x5C) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x5C pad). Recipe:
// SpecialEnemySenseUpdateModuleDataFriendNew.cpp. Class identity is the
// MoneyProvided table joined to the ZH MoneyCrateCollide.h donor (BFME2
// drops the ZH upgrade-boost list; the table carries MoneyProvided only);
// ctor, proc and factory are triple-contiguous at 0x2562FA.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class MoneyCrateCollideModuleData
{
public:
	MoneyCrateCollideModuleData();
	virtual ~MoneyCrateCollideModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x60 - 4];
};

// ?friend_newModuleData@MoneyCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *MoneyCrateCollideModuleData::friend_newModuleData(INI *ini)
{
	MoneyCrateCollideModuleData *data = new MoneyCrateCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, MoneyCrateCollideModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
