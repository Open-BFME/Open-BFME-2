// cl: /O1 /GX /DNDEBUG /MD
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

class FakePathfindPortalBehaviourModuleData
{
public:
	FakePathfindPortalBehaviourModuleData();
	virtual ~FakePathfindPortalBehaviourModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x11C - 4];
};

// ?friend_newModuleData@FakePathfindPortalBehaviourModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FakePathfindPortalBehaviourModuleData::friend_newModuleData(INI *ini)
{
	FakePathfindPortalBehaviourModuleData *data = new FakePathfindPortalBehaviourModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FakePathfindPortalBehaviourModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class MineshaftPortalBehaviourModuleData
{
public:
	MineshaftPortalBehaviourModuleData();
	virtual ~MineshaftPortalBehaviourModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x11C - 4];
};

// ?friend_newModuleData@MineshaftPortalBehaviourModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *MineshaftPortalBehaviourModuleData::friend_newModuleData(INI *ini)
{
	MineshaftPortalBehaviourModuleData *data = new MineshaftPortalBehaviourModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, MineshaftPortalBehaviourModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class CreateObjectDieIfEldestKindofModuleData
{
public:
	CreateObjectDieIfEldestKindofModuleData();
	virtual ~CreateObjectDieIfEldestKindofModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x50 - 4];
};

// ?friend_newModuleData@CreateObjectDieIfEldestKindofModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CreateObjectDieIfEldestKindofModuleData::friend_newModuleData(INI *ini)
{
	CreateObjectDieIfEldestKindofModuleData *data = new CreateObjectDieIfEldestKindofModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CreateObjectDieIfEldestKindofModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class DelayedWeaponSetUpgradeUpdateModuleData
{
public:
	DelayedWeaponSetUpgradeUpdateModuleData();
	virtual ~DelayedWeaponSetUpgradeUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x8 - 4];
};

// ?friend_newModuleData@DelayedWeaponSetUpgradeUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DelayedWeaponSetUpgradeUpdateModuleData::friend_newModuleData(INI *ini)
{
	DelayedWeaponSetUpgradeUpdateModuleData *data = new DelayedWeaponSetUpgradeUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DelayedWeaponSetUpgradeUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class GiantBirdAIUpdateModuleData
{
public:
	GiantBirdAIUpdateModuleData();
	virtual ~GiantBirdAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x84 - 4];
};

// ?friend_newModuleData@GiantBirdAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GiantBirdAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	GiantBirdAIUpdateModuleData *data = new GiantBirdAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GiantBirdAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class DelayedLuaEventUpdateModuleData
{
public:
	DelayedLuaEventUpdateModuleData();
	virtual ~DelayedLuaEventUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x8 - 4];
};

// ?friend_newModuleData@DelayedLuaEventUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DelayedLuaEventUpdateModuleData::friend_newModuleData(INI *ini)
{
	DelayedLuaEventUpdateModuleData *data = new DelayedLuaEventUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DelayedLuaEventUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class DamageFieldUpdateModuleData
{
public:
	DamageFieldUpdateModuleData();
	virtual ~DamageFieldUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@DamageFieldUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DamageFieldUpdateModuleData::friend_newModuleData(INI *ini)
{
	DamageFieldUpdateModuleData *data = new DamageFieldUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DamageFieldUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class SiegeAIUpdateModuleData
{
public:
	SiegeAIUpdateModuleData();
	virtual ~SiegeAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x64 - 4];
};

// ?friend_newModuleData@SiegeAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	SiegeAIUpdateModuleData *data = new SiegeAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SiegeAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class CommandButtonHuntUpdateModuleData
{
public:
	CommandButtonHuntUpdateModuleData();
	virtual ~CommandButtonHuntUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x10 - 4];
};

// ?friend_newModuleData@CommandButtonHuntUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CommandButtonHuntUpdateModuleData::friend_newModuleData(INI *ini)
{
	CommandButtonHuntUpdateModuleData *data = new CommandButtonHuntUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CommandButtonHuntUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class CivilianSpawnUpdateModuleData
{
public:
	CivilianSpawnUpdateModuleData();
	virtual ~CivilianSpawnUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x20 - 4];
};

// ?friend_newModuleData@CivilianSpawnUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CivilianSpawnUpdateModuleData::friend_newModuleData(INI *ini)
{
	CivilianSpawnUpdateModuleData *data = new CivilianSpawnUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CivilianSpawnUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class RepairDockUpdateModuleData
{
public:
	RepairDockUpdateModuleData();
	virtual ~RepairDockUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x14 - 4];
};

// ?friend_newModuleData@RepairDockUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RepairDockUpdateModuleData::friend_newModuleData(INI *ini)
{
	RepairDockUpdateModuleData *data = new RepairDockUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RepairDockUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class ArrowStormUpdateModuleData
{
public:
	ArrowStormUpdateModuleData();
	virtual ~ArrowStormUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xE0 - 4];
};

// ?friend_newModuleData@ArrowStormUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ArrowStormUpdateModuleData::friend_newModuleData(INI *ini)
{
	ArrowStormUpdateModuleData *data = new ArrowStormUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ArrowStormUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class ModelConditionSpecialAbilityUpdateModuleData
{
public:
	ModelConditionSpecialAbilityUpdateModuleData();
	virtual ~ModelConditionSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD8 - 4];
};

// ?friend_newModuleData@ModelConditionSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ModelConditionSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	ModelConditionSpecialAbilityUpdateModuleData *data = new ModelConditionSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ModelConditionSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class ToggleMountedSpecialAbilityUpdateModuleData
{
public:
	ToggleMountedSpecialAbilityUpdateModuleData();
	virtual ~ToggleMountedSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xE0 - 4];
};

// ?friend_newModuleData@ToggleMountedSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ToggleMountedSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	ToggleMountedSpecialAbilityUpdateModuleData *data = new ToggleMountedSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ToggleMountedSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class ToggleHiddenSpecialAbilityUpdateModuleData
{
public:
	ToggleHiddenSpecialAbilityUpdateModuleData();
	virtual ~ToggleHiddenSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xCC - 4];
};

// ?friend_newModuleData@ToggleHiddenSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ToggleHiddenSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	ToggleHiddenSpecialAbilityUpdateModuleData *data = new ToggleHiddenSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ToggleHiddenSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class ToggleDeploySpecialAbilityUpdateModuleData
{
public:
	ToggleDeploySpecialAbilityUpdateModuleData();
	virtual ~ToggleDeploySpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD0 - 4];
};

// ?friend_newModuleData@ToggleDeploySpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ToggleDeploySpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	ToggleDeploySpecialAbilityUpdateModuleData *data = new ToggleDeploySpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ToggleDeploySpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class TeleportSpecialAbilityUpdateModuleData
{
public:
	TeleportSpecialAbilityUpdateModuleData();
	virtual ~TeleportSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD8 - 4];
};

// ?friend_newModuleData@TeleportSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TeleportSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	TeleportSpecialAbilityUpdateModuleData *data = new TeleportSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, TeleportSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class HeroModeSpecialAbilityUpdateModuleData
{
public:
	HeroModeSpecialAbilityUpdateModuleData();
	virtual ~HeroModeSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD4 - 4];
};

// ?friend_newModuleData@HeroModeSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HeroModeSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	HeroModeSpecialAbilityUpdateModuleData *data = new HeroModeSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HeroModeSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class WeaponSetSpecialAbilityUpdateModuleData
{
public:
	WeaponSetSpecialAbilityUpdateModuleData();
	virtual ~WeaponSetSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD0 - 4];
};

// ?friend_newModuleData@WeaponSetSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponSetSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	WeaponSetSpecialAbilityUpdateModuleData *data = new WeaponSetSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WeaponSetSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class ScaleWallSpecialAbilityUpdateModuleData
{
public:
	ScaleWallSpecialAbilityUpdateModuleData();
	virtual ~ScaleWallSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xCC - 4];
};

// ?friend_newModuleData@ScaleWallSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ScaleWallSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	ScaleWallSpecialAbilityUpdateModuleData *data = new ScaleWallSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ScaleWallSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class FlingPassengerSpecialAbilityUpdateModuleData
{
public:
	FlingPassengerSpecialAbilityUpdateModuleData();
	virtual ~FlingPassengerSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD8 - 4];
};

// ?friend_newModuleData@FlingPassengerSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FlingPassengerSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	FlingPassengerSpecialAbilityUpdateModuleData *data = new FlingPassengerSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FlingPassengerSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class DozerAIUpdateModuleData
{
public:
	DozerAIUpdateModuleData();
	virtual ~DozerAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x70 - 4];
};

// ?friend_newModuleData@DozerAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DozerAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	DozerAIUpdateModuleData *data = new DozerAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DozerAIUpdateModuleData::buildFieldParse);
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

class StructureCollapseUpdateModuleData
{
public:
	StructureCollapseUpdateModuleData();
	virtual ~StructureCollapseUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xFC - 4];
};

// ?friend_newModuleData@StructureCollapseUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StructureCollapseUpdateModuleData::friend_newModuleData(INI *ini)
{
	StructureCollapseUpdateModuleData *data = new StructureCollapseUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StructureCollapseUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class AnimalAIUpdateModuleData
{
public:
	AnimalAIUpdateModuleData();
	virtual ~AnimalAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x80 - 4];
};

// ?friend_newModuleData@AnimalAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AnimalAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	AnimalAIUpdateModuleData *data = new AnimalAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AnimalAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class WorkerAIUpdateModuleData
{
public:
	WorkerAIUpdateModuleData();
	virtual ~WorkerAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x94 - 4];
};

// ?friend_newModuleData@WorkerAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WorkerAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	WorkerAIUpdateModuleData *data = new WorkerAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WorkerAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class RespawnUpdateModuleData
{
public:
	RespawnUpdateModuleData();
	virtual ~RespawnUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120 - 4];
};

// ?friend_newModuleData@RespawnUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RespawnUpdateModuleData::friend_newModuleData(INI *ini)
{
	RespawnUpdateModuleData *data = new RespawnUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RespawnUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class SpecialDisguiseUpdateModuleData
{
public:
	SpecialDisguiseUpdateModuleData();
	virtual ~SpecialDisguiseUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xE0 - 4];
};

// ?friend_newModuleData@SpecialDisguiseUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpecialDisguiseUpdateModuleData::friend_newModuleData(INI *ini)
{
	SpecialDisguiseUpdateModuleData *data = new SpecialDisguiseUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SpecialDisguiseUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class StatusBitsUpgradeIfEldestKindofModuleData
{
public:
	StatusBitsUpgradeIfEldestKindofModuleData();
	virtual ~StatusBitsUpgradeIfEldestKindofModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x13C - 4];
};

// ?friend_newModuleData@StatusBitsUpgradeIfEldestKindofModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StatusBitsUpgradeIfEldestKindofModuleData::friend_newModuleData(INI *ini)
{
	StatusBitsUpgradeIfEldestKindofModuleData *data = new StatusBitsUpgradeIfEldestKindofModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StatusBitsUpgradeIfEldestKindofModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class PillageModuleData
{
public:
	PillageModuleData();
	virtual ~PillageModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x14 - 4];
};

// ?friend_newModuleData@PillageModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PillageModuleData::friend_newModuleData(INI *ini)
{
	PillageModuleData *data = new PillageModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PillageModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class TransitionDamageFXModuleData
{
public:
	TransitionDamageFXModuleData();
	virtual ~TransitionDamageFXModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1040 - 4];
};

// ?friend_newModuleData@TransitionDamageFXModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TransitionDamageFXModuleData::friend_newModuleData(INI *ini)
{
	TransitionDamageFXModuleData *data = new TransitionDamageFXModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, TransitionDamageFXModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class PorcupineFormationBodyModuleData
{
public:
	PorcupineFormationBodyModuleData();
	virtual ~PorcupineFormationBodyModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x70 - 4];
};

// ?friend_newModuleData@PorcupineFormationBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PorcupineFormationBodyModuleData::friend_newModuleData(INI *ini)
{
	PorcupineFormationBodyModuleData *data = new PorcupineFormationBodyModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PorcupineFormationBodyModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class ProductionSpeedBonusModuleData
{
public:
	ProductionSpeedBonusModuleData();
	virtual ~ProductionSpeedBonusModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x90 - 4];
};

// ?friend_newModuleData@ProductionSpeedBonusModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ProductionSpeedBonusModuleData::friend_newModuleData(INI *ini)
{
	ProductionSpeedBonusModuleData *data = new ProductionSpeedBonusModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ProductionSpeedBonusModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class WoundArrowUpdateModuleData
{
public:
	WoundArrowUpdateModuleData();
	virtual ~WoundArrowUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD0 - 4];
};

// ?friend_newModuleData@WoundArrowUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WoundArrowUpdateModuleData::friend_newModuleData(INI *ini)
{
	WoundArrowUpdateModuleData *data = new WoundArrowUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WoundArrowUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class FellBeastSwoopPowerModuleData
{
public:
	FellBeastSwoopPowerModuleData();
	virtual ~FellBeastSwoopPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD0 - 4];
};

// ?friend_newModuleData@FellBeastSwoopPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FellBeastSwoopPowerModuleData::friend_newModuleData(INI *ini)
{
	FellBeastSwoopPowerModuleData *data = new FellBeastSwoopPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FellBeastSwoopPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
