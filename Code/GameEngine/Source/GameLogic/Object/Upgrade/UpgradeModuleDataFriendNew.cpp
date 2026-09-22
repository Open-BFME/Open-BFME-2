// cl: /O1 /GX /DNDEBUG /MD
//
// friend_newModuleData data factories for Upgrade modules. Each one's identity is
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

class CostModifierUpgradeModuleData
{
public:
	CostModifierUpgradeModuleData();
	virtual ~CostModifierUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x13C - 4];
};

// ?friend_newModuleData@CostModifierUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CostModifierUpgradeModuleData::friend_newModuleData(INI *ini)
{
	CostModifierUpgradeModuleData *data = new CostModifierUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CostModifierUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class SpellRechargeModifierUpgradeModuleData
{
public:
	SpellRechargeModifierUpgradeModuleData();
	virtual ~SpellRechargeModifierUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x12C - 4];
};

// ?friend_newModuleData@SpellRechargeModifierUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpellRechargeModifierUpgradeModuleData::friend_newModuleData(INI *ini)
{
	SpellRechargeModifierUpgradeModuleData *data = new SpellRechargeModifierUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SpellRechargeModifierUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
