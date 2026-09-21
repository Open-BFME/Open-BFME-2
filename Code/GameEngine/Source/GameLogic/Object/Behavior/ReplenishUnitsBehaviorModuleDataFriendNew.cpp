// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ReplenishUnitsBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C5D1, 84 bytes. Dedicated TU: the factory news 0x13C, runs the
// pinned nullary ctor (0x4841CC, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x484598, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x138 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// ReplenishUnitsBehaviorModuleData::buildFieldParse proc (double-add of own
// Replenish table 0xC4A150 plus the rowed 0x4CE29D getter table) pushed as
// the factory's proc immediate; the pinned ctor fits the 0x13C news size;
// the rowed poolkey 0x4841AD (ReplenishUnitsBehavior) ends where the ctor
// begins. The ctor row supersedes its pin when its load-split wall falls.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ReplenishUnitsBehaviorModuleData
{
public:
	ReplenishUnitsBehaviorModuleData();
	virtual ~ReplenishUnitsBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x13C - 4];
};

// ?friend_newModuleData@ReplenishUnitsBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ReplenishUnitsBehaviorModuleData::friend_newModuleData(INI *ini)
{
	ReplenishUnitsBehaviorModuleData *data = new ReplenishUnitsBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ReplenishUnitsBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
