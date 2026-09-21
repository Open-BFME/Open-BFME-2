// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@SubObjectsUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025780C, 52 bytes. Dedicated TU: the factory news 0x154, runs
// the pinned ctor (0x257768, sole caller is this factory), then feeds the
// new data plus the rowed double-add parse proc (0x4B52EB, pushed
// immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new resolves via its row. The TU-local class keeps
// only size (0x154 pad, no virtuals: /GX- for the frameless shape).
// Recipe: StatusBitsUpgradeModuleDataFriendNew.cpp. Class identity is the
// rowed SubObjectsUpgradeModuleData::buildFieldParse proc (Upgrade getter
// 0x4CE29D plus SubObjects table 0xC57D38) pushed as the factory's proc
// immediate; the ctor fits the 0x154 news size; the rowed poolkey 0x4B4D1E
// (SubObjectsUpgrade) sits in the upgrade cluster. A ModuleFactory-side
// registrar at 0x25A6CF pushes this factory VA alongside the pool string.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SubObjectsUpgradeModuleData
{
public:
	SubObjectsUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x154];
};

// ?friend_newModuleData@SubObjectsUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SubObjectsUpgradeModuleData::friend_newModuleData(INI *ini)
{
	SubObjectsUpgradeModuleData *data = new SubObjectsUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SubObjectsUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
