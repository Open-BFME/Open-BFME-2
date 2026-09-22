// cl: /O1 /DNDEBUG /MD
//
// ?buildFieldParse@TransportAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x002638FF (17 bytes). Single-table leaf: registers the Turret-led
// AIUpdate combat table 0x00BF9378 (Turret at +0x14 plus MoodAttackCheckRate
// at +0x18 plus AutoAcquireEnemiesWhenIdle at +0x1C plus StopChaseDistance at
// +0x20 plus StandGround at +0x24 plus CanAttackWhileContained at +0x25 plus
// HoldGroundCloseRangeDistance at +0x28 plus AttackPriority at +0x44) with
// MultiIniFieldParse::add (pinned at 0x2BC6E). The pushed table is an
// absolute VA literal (UnitCrateCollide precedent). Class identity is the
// retail registrar at 0x25A14C pairing behavior TransportAIUpdate with
// ModuleData factory 0x24BDF2 (plus behavior factory 0x24F192); no ZH/BFME1
// donor exists. WanderAIUpdateModuleData derives from this class (its chained
// proc calls this proc as base).

class MultiIniFieldParse;

struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class TransportAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@TransportAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
void TransportAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF9378), 0);
}

class WorkerAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@WorkerAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0024EEBB (27 bytes): base-table call above plus the Worker table
// at 0x00BEF4B0 (MaxBoxes at +0x64 plus SupplyCenterActionDelay at +0x68 plus
// SupplyWarehouseActionDelay at +0x6C plus SupplyWarehouseScanDistance at
// +0x70 plus HarvestTrees at +0x74 plus HarvestActivationRange at +0x78 plus
// HarvestPreparationTime at +0x7C plus HarvestActionTime at +0x80). All eight
// fields match BFME1's WorkerAIUpdateModuleData table verbatim at identical
// offsets. The owning factory at 0x0024EF11 pushes this proc's VA.
void WorkerAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEF4B0), 0);
}

class DeployStyleAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DeployStyleAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0024D1CB (27 bytes): base-table call above plus the DeployStyle
// table at 0x00BEECB0 (UnpackTime at +0x64 plus PackTime at +0x68 plus
// ResetTurretBeforePacking at +0x6C plus TurretsFunctionOnlyWhenDeployed at
// +0x6D plus TurretsMustCenterBeforePacking at +0x6E plus MustDeployToAttack
// at +0x6F plus DeployedAttributeModifier at +0x70). Five of seven fields
// match BFME1's DeployStyleAIUpdateModuleData table verbatim at identical
// offsets (votes 5/3); BFME2 appends MustDeployToAttack plus
// DeployedAttributeModifier. The owning factory at 0x0025517E pushes this
// proc's VA (unique image-wide).
void DeployStyleAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEECB0), 0);
}

class AssaultTransportAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@AssaultTransportAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0024D248 (27 bytes): base-table call above plus the
// AssaultTransport table at 0x00BEED74 (MembersGetHealedAtLifeRatio at +0x64
// plus ClearRangeRequiredToContinueAttackMove at +0x68). Both fields match
// BFME1's AssaultTransportAIUpdateModuleData table verbatim at identical
// offsets (votes 2/2). The owning factory at 0x0024D29E pushes this proc's
// VA (unique image-wide); the behavior side (AssaultTransportAIUpdate pool
// key plus name getter) is rowed in its own file-unit.
void AssaultTransportAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEED74), 0);
}

class AnimalAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@AnimalAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0024BE7A (27 bytes): base-table call above plus the AnimalAI table
// at 0x00BEEB88 (FleeRange at +0x64 plus FleeDistance at +0x68 plus
// WanderPercentage at +0x6C matching the ctor stores 0x14/0x64/0x32 at
// 0x24BE43). The owning factory at 0x0024BED0 pushes this proc VA (unique
// image-wide); the rowed AnimalAIUpdate pool key (0x47EC1A) names the family.
void AnimalAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEEB88), 0);
}

class WanderAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@WanderAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0024F1F2 (27 bytes): base-table call above plus the Wander table
// at 0x00BEF580 (WildBeast at +0x64 plus ConditionForEntry at +0x68 plus
// Selectable at +0x6C plus WanderDistance at +0x70). The owning factory at
// 0x0024F248 calls the rowed ctor at 0x24F1CD and pushes this proc VA
// (unique image-wide). Row supersedes the pin.
void WanderAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00BEF580), 0);
}
