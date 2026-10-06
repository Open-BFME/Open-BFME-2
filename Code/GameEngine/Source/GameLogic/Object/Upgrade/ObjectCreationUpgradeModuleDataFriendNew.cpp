// cl: /GX /DNDEBUG /MD

// ?friend_newModuleData@ObjectCreationUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024FFAC, 84 bytes. Dedicated TU: the factory news 0x154, runs the
// declared-only nullary ctor (pinned at 0x4B425B, sole caller is this
// factory), then feeds the new data plus the class parse proc (rowed at
// 0x4B4084, pushed immediate, UpgradeObject table 0x00C57708 per the BFME1
// ObjectCreationUpgrade donor) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x150 pad). Recipe: GrantUpgradeCreateModuleDataFriendNew.cpp. Class
// identity is the rowed ObjectCreationUpgradeModuleData::buildFieldParse proc
// pushed as the factory's proc immediate; the ctor installs vtable 0x00C577C8
// and fits the 0x154 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ObjectCreationUpgradeModuleData
{
public:
	ObjectCreationUpgradeModuleData();
	virtual ~ObjectCreationUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x154 - 4];
};

// ?friend_newModuleData@ObjectCreationUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ObjectCreationUpgradeModuleData::friend_newModuleData(INI *ini)
{
	ObjectCreationUpgradeModuleData *data = new ObjectCreationUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ObjectCreationUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
