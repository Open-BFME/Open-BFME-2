// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ToppleUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024F0B8, 81 bytes. Dedicated TU: the factory news 0x2C, runs the
// declared-only nullary ctor (pinned at 0x4A8173, sole caller is this
// factory), then feeds the new data plus the class parse proc (rowed at
// 0x4A81F0, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x28 pad). Recipe: StealthUpdateModuleDataFriendNew.cpp. Class identity is
// the rowed ToppleUpdateModuleData::buildFieldParse proc (ToppleFX plus
// BounceFX plus StumpName plus KillWhenStartToppling per the ZH ToppleUpdate
// donor) pushed as the factory's proc immediate; the ctor installs vtable
// 0x00C538A0 and fits the 0x2C news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ToppleUpdateModuleData
{
public:
	ToppleUpdateModuleData();
	virtual ~ToppleUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x2C - 4];
};

// ?friend_newModuleData@ToppleUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ToppleUpdateModuleData::friend_newModuleData(INI *ini)
{
	ToppleUpdateModuleData *data = new ToppleUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ToppleUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
