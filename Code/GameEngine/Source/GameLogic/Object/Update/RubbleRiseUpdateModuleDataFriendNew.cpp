// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RubbleRiseUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002566F6, 84 bytes. Dedicated TU: the factory news 0xD8, runs
// the pinned nullary ctor (0x256653, sole caller is this factory), then feeds
// the new data plus the rowed double-add parse proc (0x4A5486, pushed
// immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0xD4 pad).
// Recipe: GiantBirdSlowDeathBehaviorModuleDataFriendNew.cpp. Class identity
// is the rowed RubbleRiseUpdateModuleData::buildFieldParse proc (RubbleRise
// delay table 0xC52960 over the Die getter) pushed as the factory's proc
// immediate; the ctor fits the 0xD8 news size; the rowed poolkey 0x4A4C82
// (RubbleRiseUpdate) sits in the update cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RubbleRiseUpdateModuleData
{
public:
	RubbleRiseUpdateModuleData();
	virtual ~RubbleRiseUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD8 - 4];
};

// ?friend_newModuleData@RubbleRiseUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RubbleRiseUpdateModuleData::friend_newModuleData(INI *ini)
{
	RubbleRiseUpdateModuleData *data = new RubbleRiseUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RubbleRiseUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
