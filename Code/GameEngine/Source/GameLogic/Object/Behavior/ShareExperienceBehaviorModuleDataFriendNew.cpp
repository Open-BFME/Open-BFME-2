// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ShareExperienceBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024BFE5, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// pinned nullary ctor (0x47FE90, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x47FEDC, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x14 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// ShareExperienceBehaviorModuleData::buildFieldParse proc (Share table
// 0xC48740: Radius@8/DropOff@C/Percentage@10/ObjectFilter@14) pushed as the
// factory's proc immediate; the pinned ctor fits the 0x18 news size; the
// rowed poolkey 0x47FE4B (ShareExperienceBehavior) ends where the ctor
// begins. The ctor row supersedes its pin when its data-pointer wall falls.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ShareExperienceBehaviorModuleData
{
public:
	ShareExperienceBehaviorModuleData();
	virtual ~ShareExperienceBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@ShareExperienceBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ShareExperienceBehaviorModuleData::friend_newModuleData(INI *ini)
{
	ShareExperienceBehaviorModuleData *data = new ShareExperienceBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ShareExperienceBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
