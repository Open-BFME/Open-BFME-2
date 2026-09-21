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

static const FieldParse s_commandSetTable;

static const FieldParse s_radarTable;

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
