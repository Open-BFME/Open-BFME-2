// cl: /O1 /GX /DNDEBUG /MD
//
// friend_newModuleData data factories for SpecialPower modules. Each one's identity is
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

class ActivateModuleSpecialPowerModuleData
{
public:
	ActivateModuleSpecialPowerModuleData();
	virtual ~ActivateModuleSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD4 - 4];
};

// ?friend_newModuleData@ActivateModuleSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ActivateModuleSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	ActivateModuleSpecialPowerModuleData *data = new ActivateModuleSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ActivateModuleSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class DeflectSpecialPowerModuleData
{
public:
	DeflectSpecialPowerModuleData();
	virtual ~DeflectSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@DeflectSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DeflectSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	DeflectSpecialPowerModuleData *data = new DeflectSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DeflectSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class SiegeDeploySpecialPowerModuleData
{
public:
	SiegeDeploySpecialPowerModuleData();
	virtual ~SiegeDeploySpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x30 - 4];
};

// ?friend_newModuleData@SiegeDeploySpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeDeploySpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	SiegeDeploySpecialPowerModuleData *data = new SiegeDeploySpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SiegeDeploySpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class SiegeDeployHordeSpecialPowerModuleData
{
public:
	SiegeDeployHordeSpecialPowerModuleData();
	virtual ~SiegeDeployHordeSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@SiegeDeployHordeSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeDeployHordeSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	SiegeDeployHordeSpecialPowerModuleData *data = new SiegeDeployHordeSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SiegeDeployHordeSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class PlayerUpgradeSpecialPowerModuleData
{
public:
	PlayerUpgradeSpecialPowerModuleData();
	virtual ~PlayerUpgradeSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x88 - 4];
};

// ?friend_newModuleData@PlayerUpgradeSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PlayerUpgradeSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	PlayerUpgradeSpecialPowerModuleData *data = new PlayerUpgradeSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PlayerUpgradeSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
