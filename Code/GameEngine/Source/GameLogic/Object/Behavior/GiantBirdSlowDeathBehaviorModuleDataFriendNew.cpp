// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@GiantBirdSlowDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024B5D1, 84 bytes. Dedicated TU: the factory news 0x1C4, runs
// the rowed nullary ctor (0x461F7F, sole caller is this factory), then feeds
// the new data plus the rowed chained parse proc (0x461E3D, pushed
// immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x1C0 pad).
// Recipe: SlowDeathBehaviorModuleDataFriendNew.cpp. Class identity is the
// rowed GiantBirdSlowDeathBehaviorModuleData::buildFieldParse proc (Crash
// table 0xC42D08 over the rowed SlowDeath base) pushed as the factory's
// proc immediate; the ctor fits the 0x1C4 news size; the rowed poolkey
// 0x461EA0 (GiantBirdSlowDeathBehavior) sits in the behavior cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class GiantBirdSlowDeathBehaviorModuleData
{
public:
	GiantBirdSlowDeathBehaviorModuleData();
	virtual ~GiantBirdSlowDeathBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C4 - 4];
};

// ?friend_newModuleData@GiantBirdSlowDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GiantBirdSlowDeathBehaviorModuleData::friend_newModuleData(INI *ini)
{
	GiantBirdSlowDeathBehaviorModuleData *data = new GiantBirdSlowDeathBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GiantBirdSlowDeathBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
