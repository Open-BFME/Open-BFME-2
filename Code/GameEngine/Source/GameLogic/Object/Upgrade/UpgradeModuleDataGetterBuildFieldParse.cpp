// cl: /O1 /DNDEBUG /MD
//
// Upgrade ModuleData::buildFieldParse procs with a shared-table-getter head:
// each registers the base upgrade table through the shared table getter
// (rowed at 0x4CE29D, returns 0x00C5FEA0) at extraOffset 8, then registers
// its own FieldParse table with MultiIniFieldParse::add (rowed at 0x2DEB5)
// at extraOffset 0. Bodies:
// ?buildFieldParse@CommandSetUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B3A90, 34 bytes (own table 0x00C572C0 holding CommandSet at
// +0x118; factory at 0x255698 pushes this proc; the CommandSetUpgrade pool
// key at 0x4B3A4B ends where this proc begins).
// ?buildFieldParse@RadarUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B476C, 34 bytes (own table 0x00C578D0 holding DisableProof at
// +0x118; factory at 0x254741 pushes this proc; the RadarUpgrade pool key at
// 0x4B4727 ends where this proc begins).
// ?buildFieldParse@StatusBitsUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B493E, 34 bytes (own table 0x00C57984 holding StatusToSet at
// +0x118 plus StatusToClear at +0x128; factory at 0x25479D pushes this proc;
// the StatusBitsUpgrade pool key at 0x4B48F9 ends where this proc begins).
// ?buildFieldParse@AttributeModifierUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B671E, 34 bytes (own table 0x00C58818 holding AttributeModifier
// at +0x118; factory at 0x255802 pushes this proc; the AttributeModifierUpgrade
// pool key at 0x4B6703 ends where this proc begins).
// ?buildFieldParse@DoCommandUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B4C0C, 34 bytes (own table 0x00C57BC4 holding
// GetUpgradeCommandButtonName at +0x118 plus RemoveUpgradeCommandButtonName at
// +0x11C; factory at 0x2557B5 pushes this proc; the DoCommandUpgrade pool key
// at 0x4B4BF1 ends where this proc begins).
// ?buildFieldParse@CastleUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B6847, 34 bytes (own table 0x00C588C4 holding Upgrade at +0x118
// plus WallUpgradeRadius at +0x11C; factory at 0x25585A pushes this proc; the
// CastleUpgrade pool key at 0x4B682C ends where this proc begins).
// Provenance: the getter-head shape (push 8, call getter, add, add table)
// reproduces retail exactly; the pushed table address is a masked DIR32 so
// the TU keeps an opaque table. Recipe:
// AIUpdate/ChinookAIUpdateBuildFieldParse.cpp for the Rva004CE29DGet call.

class MultiIniFieldParse;

struct FieldParse
{
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

int Rva004CE29DGet();

class CommandSetUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class RadarUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class StatusBitsUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class AttributeModifierUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class DoCommandUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class CastleUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

static const FieldParse s_commandSetTable;

static const FieldParse s_radarTable;

static const FieldParse s_statusBitsTable;

static const FieldParse s_attributeModifierTable;

static const FieldParse s_doCommandTable;

static const FieldParse s_castleTable;

// ?buildFieldParse@CommandSetUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void CommandSetUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(&s_commandSetTable, 0);
}

// ?buildFieldParse@RadarUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void RadarUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(&s_radarTable, 0);
}

// ?buildFieldParse@StatusBitsUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void StatusBitsUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(&s_statusBitsTable, 0);
}

// ?buildFieldParse@AttributeModifierUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void AttributeModifierUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(&s_attributeModifierTable, 0);
}

// ?buildFieldParse@DoCommandUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void DoCommandUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(&s_doCommandTable, 0);
}

// ?buildFieldParse@CastleUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void CastleUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(&s_castleTable, 0);
}
