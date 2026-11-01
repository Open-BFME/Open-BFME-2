// cl: /GX /DNDEBUG /MD
// Split from UpdateModuleDataFriendNew.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// friend_newModuleData data factories for Update modules. Each one's identity is
// ModuleFactory's addModule registration, which pushes the module name with
// this factory. Every factory news its data class, runs the declared-only ctor
// and passes the class parse proc to INI::initFromINIMultiProc; both callees
// are pinned at the addresses the retail factory calls and pushes.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DynamicPortalBehaviourModuleData
{
public:
	DynamicPortalBehaviourModuleData();
	virtual ~DynamicPortalBehaviourModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x15C - 4];
};

// ?friend_newModuleData@DynamicPortalBehaviourModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DynamicPortalBehaviourModuleData::friend_newModuleData(INI *ini)
{
	DynamicPortalBehaviourModuleData *data = new DynamicPortalBehaviourModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DynamicPortalBehaviourModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class FadeAndDieOrnamentUpdateModuleData
{
public:
	FadeAndDieOrnamentUpdateModuleData();
	virtual ~FadeAndDieOrnamentUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x38 - 4];
};

// ?friend_newModuleData@FadeAndDieOrnamentUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FadeAndDieOrnamentUpdateModuleData::friend_newModuleData(INI *ini)
{
	FadeAndDieOrnamentUpdateModuleData *data = new FadeAndDieOrnamentUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FadeAndDieOrnamentUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

// Registration SpecialAbilityUpdate (0x00259DD9) pushes this data factory with
// the rowed SpecialAbilityUpdate::friend_newModuleInstance 0x0024A847. Its
// 0xC8 data is built by the ctor at 0x0044EB54 alone (it stores the final
// vtable 0x00C3F2A8; the ledger keeps it as the opaque Rva0044EB54, which 26
// *SpecialAbilityUpdate / special-power module data ctors call as their base)
// and parsed by 0x0044ED95; both are pinned under this class as aliases.
