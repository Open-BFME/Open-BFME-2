// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ClearanceTestingSlowDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C545, 84 bytes. Dedicated TU: the factory news 0x208, runs
// the pinned nullary ctor (0x483E25, sole caller is this factory), then feeds
// the new data plus the rowed chained parse proc (0x483C1A, pushed
// immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x204 pad).
// Recipe: GiantBirdSlowDeathBehaviorModuleDataFriendNew.cpp. Class identity
// is the rowed ClearanceTestingSlowDeathBehaviorModuleData::buildFieldParse
// proc (Clearance table 0xC49CB0 over the rowed SlowDeath base) pushed as the
// factory's proc immediate; the ctor fits the 0x208 news size; the rowed
// poolkey 0x483CF4 (ClearanceTestingSlowDeathBehavior) sits in the behavior
// cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ClearanceTestingSlowDeathBehaviorModuleData
{
public:
	ClearanceTestingSlowDeathBehaviorModuleData();
	virtual ~ClearanceTestingSlowDeathBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x208 - 4];
};

// ?friend_newModuleData@ClearanceTestingSlowDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ClearanceTestingSlowDeathBehaviorModuleData::friend_newModuleData(INI *ini)
{
	ClearanceTestingSlowDeathBehaviorModuleData *data = new ClearanceTestingSlowDeathBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ClearanceTestingSlowDeathBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
