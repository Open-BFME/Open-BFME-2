// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AutoAbilityBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024AFE5, 81 bytes. Dedicated TU: the factory news 0x60, runs the
// pinned nullary ctor (0x45A2E7, sole raw caller is this factory), then feeds
// the new data plus the rowed parse proc (0x45A36E, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x5C pad). Recipe:
// OilSpillUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// AutoAbilityBehaviorModuleData::buildFieldParse proc (Scan table 0xC41690)
// pushed as the factory's proc immediate; the ctor fits the 0x60 news size;
// the rowed poolkey cluster (AutoAbilityBehavior) closes this vein beside
// the parked behavior ctor.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AutoAbilityBehaviorModuleData
{
public:
	AutoAbilityBehaviorModuleData();
	virtual ~AutoAbilityBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x60 - 4];
};

// ?friend_newModuleData@AutoAbilityBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AutoAbilityBehaviorModuleData::friend_newModuleData(INI *ini)
{
	AutoAbilityBehaviorModuleData *data = new AutoAbilityBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AutoAbilityBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
