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
