// cl: /O1 /GX /DNDEBUG /MD
//
// friend_newModuleData data factories for Behavior modules. Each one's identity is
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

class GettingBuiltBehaviorModuleData
{
public:
	GettingBuiltBehaviorModuleData();
	virtual ~GettingBuiltBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x4C - 4];
};

// ?friend_newModuleData@GettingBuiltBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GettingBuiltBehaviorModuleData::friend_newModuleData(INI *ini)
{
	GettingBuiltBehaviorModuleData *data = new GettingBuiltBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GettingBuiltBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class EnragedBehaviorModuleData
{
public:
	EnragedBehaviorModuleData();
	virtual ~EnragedBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xC - 4];
};

// ?friend_newModuleData@EnragedBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EnragedBehaviorModuleData::friend_newModuleData(INI *ini)
{
	EnragedBehaviorModuleData *data = new EnragedBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, EnragedBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class InstantDeathBehaviorModuleData
{
public:
	InstantDeathBehaviorModuleData();
	virtual ~InstantDeathBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x68 - 4];
};

// ?friend_newModuleData@InstantDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *InstantDeathBehaviorModuleData::friend_newModuleData(INI *ini)
{
	InstantDeathBehaviorModuleData *data = new InstantDeathBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, InstantDeathBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class ShipSlowDeathBehaviorModuleData
{
public:
	ShipSlowDeathBehaviorModuleData();
	virtual ~ShipSlowDeathBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x190 - 4];
};

// ?friend_newModuleData@ShipSlowDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ShipSlowDeathBehaviorModuleData::friend_newModuleData(INI *ini)
{
	ShipSlowDeathBehaviorModuleData *data = new ShipSlowDeathBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ShipSlowDeathBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class PropagandaTowerBehaviorModuleData
{
public:
	PropagandaTowerBehaviorModuleData();
	virtual ~PropagandaTowerBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x24 - 4];
};

// ?friend_newModuleData@PropagandaTowerBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PropagandaTowerBehaviorModuleData::friend_newModuleData(INI *ini)
{
	PropagandaTowerBehaviorModuleData *data = new PropagandaTowerBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PropagandaTowerBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class FireWeaponWhenDeadBehaviorModuleData
{
public:
	FireWeaponWhenDeadBehaviorModuleData();
	virtual ~FireWeaponWhenDeadBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x160 - 4];
};

// ?friend_newModuleData@FireWeaponWhenDeadBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireWeaponWhenDeadBehaviorModuleData::friend_newModuleData(INI *ini)
{
	FireWeaponWhenDeadBehaviorModuleData *data = new FireWeaponWhenDeadBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FireWeaponWhenDeadBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
