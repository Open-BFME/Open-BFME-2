// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "StancesBehavior" (addModule
// pairs the name with this factory); formerly misnamed StanceTemplateUpdateModuleData.
//
// ?friend_newModuleData@StancesBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x0024B3B4, 81 bytes. Dedicated TU: the factory news 0xC, runs the
// pinned nullary ctor (0x254C8E, 12-byte inline installing the folded vtable
// 0x00C4ED70 plus zero at +8), then feeds the new data plus the class parse
// proc (rowed at 0x45ED8C, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 8 pad). Recipe:
// SlotToLockUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// StancesBehaviorModuleData::buildFieldParse proc (table 0x00C424B0 whose
// first field is StanceTemplate) pushed as the factory's proc immediate; the
// ctor installs vtable 0x00C4ED70 and fits the 0xC news size. The pinned ctor
// body is ICF-folded across three same-size factories (0x24AF5C plus this one
// plus 0x2509CE, each pushing its own proc); the pin names the SlotToLock use
// and documents the share.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class StancesBehaviorModuleData
{
public:
	StancesBehaviorModuleData();
	virtual ~StancesBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xC - 4];
};

// ?friend_newModuleData@StancesBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StancesBehaviorModuleData::friend_newModuleData(INI *ini)
{
	StancesBehaviorModuleData *data = new StancesBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StancesBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
