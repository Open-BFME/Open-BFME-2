// cl: /O1 /GX /DNDEBUG /MD
//
// friend_newModuleData data factories for Damage modules. Each one's identity is
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

class HordeTransportContainDamageModuleData
{
public:
	HordeTransportContainDamageModuleData();
	virtual ~HordeTransportContainDamageModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x8 - 4];
};

// ?friend_newModuleData@HordeTransportContainDamageModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeTransportContainDamageModuleData::friend_newModuleData(INI *ini)
{
	HordeTransportContainDamageModuleData *data = new HordeTransportContainDamageModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HordeTransportContainDamageModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class CallHelpOnDamageModuleData
{
public:
	CallHelpOnDamageModuleData();
	virtual ~CallHelpOnDamageModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@CallHelpOnDamageModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CallHelpOnDamageModuleData::friend_newModuleData(INI *ini)
{
	CallHelpOnDamageModuleData *data = new CallHelpOnDamageModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CallHelpOnDamageModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
