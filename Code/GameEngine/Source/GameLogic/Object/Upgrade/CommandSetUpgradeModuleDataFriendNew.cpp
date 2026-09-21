// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CommandSetUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00255698, 84 bytes. Dedicated TU: the factory news 0x11C, runs
// the rowed EH ctor (0x255652, over the OpenContain base with the
// compiler-emitted vtable and the CommandSet string assignment), then feeds
// the new data plus the rowed class parse proc (0x4B3A90, pushed immediate)
// to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. Recipe:
// GeometryUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// CommandSetUpgrade proc (Upgrade base proc 0x4CE29D plus table 0x008572C0
// holding CommandSet at +0x118 matching the ctor member) pushed as the
// factory's proc immediate; the CommandSetUpgrade pool key at 0x4B3A4B ends
// where that proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CommandSetUpgradeModuleData
{
public:
	CommandSetUpgradeModuleData();
	virtual ~CommandSetUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x11C - 4];
};

// ?friend_newModuleData@CommandSetUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CommandSetUpgradeModuleData::friend_newModuleData(INI *ini)
{
	CommandSetUpgradeModuleData *data = new CommandSetUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CommandSetUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
