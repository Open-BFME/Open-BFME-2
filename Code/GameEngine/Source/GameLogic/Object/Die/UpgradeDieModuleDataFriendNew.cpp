// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@UpgradeDieModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00255103, 81 bytes. Dedicated TU: the factory news 0x3C, runs the
// rowed nullary ctor (0x2550ED, frameless over the pinned SEH base), then
// feeds the new data plus the class parse proc (rowed at 0x253B56, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x38 pad).
// Recipe: ReflectDamageModuleDataFriendNew.cpp. Class identity is the rowed
// UpgradeDieModuleData::buildFieldParse proc (single UpgradeToRemove field
// at +0x38 per the BFME1 UpgradeDie donor) pushed as the factory's proc
// immediate; the ctor installs vtable 0x00BF33C0 and fits the 0x3C news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class UpgradeDieModuleData
{
public:
	UpgradeDieModuleData();
	virtual ~UpgradeDieModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x3C - 4];
};

// ?friend_newModuleData@UpgradeDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *UpgradeDieModuleData::friend_newModuleData(INI *ini)
{
	UpgradeDieModuleData *data = new UpgradeDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, UpgradeDieModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
