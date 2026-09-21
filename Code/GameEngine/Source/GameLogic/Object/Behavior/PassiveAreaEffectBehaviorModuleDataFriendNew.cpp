// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@PassiveAreaEffectBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C724, 81 bytes. Dedicated TU: the factory news 0x38, runs
// the rowed nullary ctor (0x484DF4, sole caller is this factory), then feeds
// the new data plus the rowed single-table parse proc (0x48490E, pushed
// immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x34 pad).
// Recipe: ClearanceTestingSlowDeathBehaviorModuleDataFriendNew.cpp. Class
// identity is the rowed PassiveAreaEffectBehaviorModuleData::buildFieldParse
// proc (EffectRadius-led table 0xC4A388) pushed as the factory's proc
// immediate; the ctor fits the 0x38 news size; the rowed poolkey 0x484ADD
// (PassiveAreaEffectBehavior) sits in the behavior cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class PassiveAreaEffectBehaviorModuleData
{
public:
	PassiveAreaEffectBehaviorModuleData();
	virtual ~PassiveAreaEffectBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x38 - 4];
};

// ?friend_newModuleData@PassiveAreaEffectBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PassiveAreaEffectBehaviorModuleData::friend_newModuleData(INI *ini)
{
	PassiveAreaEffectBehaviorModuleData *data = new PassiveAreaEffectBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PassiveAreaEffectBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
