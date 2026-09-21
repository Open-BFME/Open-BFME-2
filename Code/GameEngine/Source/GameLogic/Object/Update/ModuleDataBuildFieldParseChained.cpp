// cl: /O1 /DNDEBUG /MD
//
// Chained ModuleData::buildFieldParse procs: each calls its base-class
// buildFieldParse, then registers its own FieldParse table with
// MultiIniFieldParse::add (pinned at 0x2BC6E). Bodies:
// ?buildFieldParse@Rva0044EB54@@SAXAAVMultiIniFieldParse@@@Z, retail
// 0x0044ED95, 11 bytes (field SpecialPowerTemplate; base shared by the
// SpecialAbility family below; attached to the already-pinned Rva0044EB54
// entity, no new class invented);
// ?buildFieldParse@DockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x005896C1, 11 bytes (field NumberApproachPositions; adjacent to
// the ledger-named DockUpdateModuleData ctor pin at 0x5896B0);
// ?buildFieldParse@SpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004CD389, 27 bytes (field Radius);
// ?buildFieldParse@SupplyCenterProductionExitUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004CD918, 27 bytes (field Radius);
// ?buildFieldParse@SpyVisionUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004CCD64, 27 bytes (field TriggerFX);
// ?buildFieldParse@SupplyWarehouseDockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004A7D3A, 27 bytes (field StartingBoxes; follows a jump-table
// pad, address-taken by its factory at 0x24F02F).
// ?buildFieldParse@DelayedDeathBodyModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C159E, 27 bytes (chained on the pinned RespawnUpdate base proc
// at 0x4C12D0, then table 0x00C5BAE8 holding DelayedDeathTime at +0x6C plus
// ImmortalUntilDeathTime at +0x70 plus InvulnerableFX at +0x74 plus
// DoHealthCheck at +0x78 plus DelayedDeathPrerequisiteUpgrade at +0x7C,
// matching the ctor stores; factory at 0x251622 pushes this proc).
// Provenance: the ZH MAKE_STANDARD_MODULE_DATA_MACRO_ABC macro passes
// clsmd::buildFieldParse to INI::initFromINIMultiProc, and each landed
// friend_newModuleData factory pushes its class proc immediate.

class MultiIniFieldParse;

struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class Rva0044EB54
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SpecialAbilityUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SupplyCenterProductionExitUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SpyVisionUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SupplyWarehouseDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class RespawnUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class DelayedDeathBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void Rva0044EB54::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C3F7F8), 0);
}

void DockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C702CC), 0);
}

void SpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5FAE0), 0);
}

void SupplyCenterProductionExitUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5FB9C), 0);
}

void SpyVisionUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva0044EB54::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5F810), 0);
}

void SupplyWarehouseDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5370C), 0);
}

void DelayedDeathBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	RespawnUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5BAE8), 0);
}
