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
