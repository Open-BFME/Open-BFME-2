// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@AutoHealBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025694B, 52 bytes. Dedicated TU: the factory news 0x160, runs
// the pinned nullary ctor (0x254DE7, sole raw caller image-wide is this
// factory), then feeds the new data plus the rowed double-add parse proc
// (0x256929, pushed immediate) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x15C pad). Class identity is the rowed
// AutoHealBehaviorModuleData::buildFieldParse proc (healing table 0xBF3CE0
// with StartsActive plus ButtonTriggered plus SingleBurst plus HealingAmount
// plus HealingDelay plus Radius plus KindOf entries) pushed as the factory's
// proc immediate; the ctor fits the 0x160 news size; the behavior side is
// rowed AutoHealBehavior with pool string AutoHealBehavior.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AutoHealBehaviorModuleData
{
public:
	AutoHealBehaviorModuleData();
	virtual ~AutoHealBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x160 - 4];
};

// ?friend_newModuleData@AutoHealBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AutoHealBehaviorModuleData::friend_newModuleData(INI *ini)
{
	AutoHealBehaviorModuleData *data = new AutoHealBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AutoHealBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
