// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RebuildHoleBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C433, 81 bytes. Dedicated TU: the factory news 0x14, runs the
// declared-only ctor (rowed at 0x48323E, vtable plus 0.1f HoleHealth plus
// WorkerObjectName and-zero), then feeds the new data plus the class parse
// proc (rowed at 0x483260, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x10 pad). Recipe:
// DemoTrapUpdateModuleDataFriendNew.cpp. Class identity is retail's own
// WorkerObjectName-led INI table at 0x00C49A10 (landed buildFieldParse row)
// beside the rowed RebuildHoleBehavior pool key (0x4832D7).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RebuildHoleBehaviorModuleData
{
public:
	RebuildHoleBehaviorModuleData();
	virtual ~RebuildHoleBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x14 - 4];
};

// ?friend_newModuleData@RebuildHoleBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RebuildHoleBehaviorModuleData::friend_newModuleData(INI *ini)
{
	RebuildHoleBehaviorModuleData *data = new RebuildHoleBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RebuildHoleBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
