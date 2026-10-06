// cl: /DNDEBUG /MD
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

class CostModifierUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SpellRechargeModifierUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class ArmorUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ArmorUpgrade own table (retail VA 0x00DBA870, 16-byte entries
// {label, parse, userData, offset} per the landed RiderChange precedent).
// Target facts from read-only image dump: entry0 label "KillArmorUpgrade"
// (VA 0x00BF2468), parser VA 0x0042E850, userData 0, offset 0x118; entry1
// label "IgnoreArmorUpgrade" (VA 0x00BF2454), parser 0x0042E850, userData 0,
// offset 0x119; entry2 label "ArmorSetFlag" (VA 0x00BF2444), parser
// 0x0042EC4E, userData 0 in-image (patched once to 0x00DBAA40), offset 0
// in-image (patched once to 0x11C); entry3 zero in-image (re-zeroed once).
// Parser identities are rowed providers, not shapes: 0x0042E850 is
// INI::parseBool (28B via getNextToken 0x0042DF97 + scanBool 0x0042D14A) and
// 0x0042EC4E is INI::parseIndexList (32B via getNextToken 0x0042DF97 +
// scanIndexList 0x0042BD39), both declared below with their genuine
// (INI*, void*, void*, const void*) ABI. Entry2 userData is the
// VeterancyLevel name list at VA 0x00DBAA40 (21 string pointers + null;
// VETERAN/ELITE/HERO first), whose sole definition is VeterancyLevelNames
// in INI_VeterancyLevelToken.cpp, used here as extern. Offsets match the
// matched ctor 0x00254556 stores (bools +0x118/+0x119, int +0x11C).
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct ArmorUpgradeFieldParse
{
	const char *m_name;
	INIFieldParseProc m_parser;
	const void *m_userData;
	unsigned int m_offset;
};

class INI
{
public:
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiStringVector(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004B60D5_ParsePercentage(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(class INI *ini, void *instance, void *store, const void *userData);

struct BaselineFieldParse
{
	const char *m_name;
	INIFieldParseProc m_parser;
	const void *m_userData;
	unsigned int m_offset;
};

extern const char *VeterancyLevelNames[];

static unsigned int s_armorTableReady = 0;
static ArmorUpgradeFieldParse s_armorTable[4] = {
	{ "KillArmorUpgrade", &INI::parseBool, 0, 0x118 },
	{ "IgnoreArmorUpgrade", &INI::parseBool, 0, 0x119 },
	{ "ArmorSetFlag", &INI::parseIndexList, 0, 0 },
	{ 0, 0, 0, 0 }
};

// Baseline8 typed tables (codex-verifier-r10 target_tables inventory; labels,
// offsets and callbacks retail-real, every callback a rowed provider).
// CommandSet 0x00C572C0 32B: CommandSet@0x118 via rowed parseAsciiString 0x2F11E.
static BaselineFieldParse s_commandSetTable[2] = {
	{ "CommandSet", &INI::parseAsciiString, 0, 0x118 },
	{ 0, 0, 0, 0 }
};

// Radar 0x00C578D0 32B: DisableProof@0x118 via rowed parseBool 0x2E850.
static BaselineFieldParse s_radarTable[2] = {
	{ "DisableProof", &INI::parseBool, 0, 0x118 },
	{ 0, 0, 0, 0 }
};

static const FieldParse s_statusBitsTable;

// AttributeModifier 0x00C58818 32B: AttributeModifier@0x118 via rowed 0x2F11E.
static BaselineFieldParse s_attributeModifierTable[2] = {
	{ "AttributeModifier", &INI::parseAsciiString, 0, 0x118 },
	{ 0, 0, 0, 0 }
};

// DoCommand 0x00C57BC4 48B: GetUpgradeCommandButtonName@0x118 +
// RemoveUpgradeCommandButtonName@0x11C, both via rowed parseAsciiString 0x2F11E.
static BaselineFieldParse s_doCommandTable[3] = {
	{ "GetUpgradeCommandButtonName", &INI::parseAsciiString, 0, 0x118 },
	{ "RemoveUpgradeCommandButtonName", &INI::parseAsciiString, 0, 0x11C },
	{ 0, 0, 0, 0 }
};

// Castle 0x00C588C4 48B: Upgrade@0x118 via rowed 0x2F11E +
// WallUpgradeRadius@0x11C via rowed parseReal 0x2EFC0.
static BaselineFieldParse s_castleTable[3] = {
	{ "Upgrade", &INI::parseAsciiString, 0, 0x118 },
	{ "WallUpgradeRadius", &INI::parseReal, 0, 0x11C },
	{ 0, 0, 0, 0 }
};

// CostModifier 0x00C582D8 128B: 7 real fields + terminator, all callbacks rowed
// (ObjectFilter 0x361CA5, Percentage 0x4B60D5, UpgradeDiscount/StartsActive/
// Slaughter 0x2E850, ApplyToTheseUpgrades 0x2F196, LabelForPalantirString 0x2F11E).
static BaselineFieldParse s_costModifierTable[8] = {
	{ "ObjectFilter", &iniParseObjectFilter, 0, 0x118 },
	{ "Percentage", &INI::Rva004B60D5_ParsePercentage, 0, 0x11C },
	{ "UpgradeDiscount", &INI::parseBool, 0, 0x128 },
	{ "ApplyToTheseUpgrades", &INI::parseAsciiStringVector, 0, 0x130 },
	{ "StartsActive", &INI::parseBool, 0, 0x129 },
	{ "Slaughter", &INI::parseBool, 0, 0x12A },
	{ "LabelForPalantirString", &INI::parseAsciiString, 0, 0x12C },
	{ 0, 0, 0, 0 }
};

// SpellRecharge 0x00C58460 64B: Percentage@0x118 via rowed 0x4B60D5 +
// StartsActive@0x124 via rowed 0x2E850 + LabelForPalantirString@0x128 via rowed 0x2F11E.
static BaselineFieldParse s_spellRechargeTable[4] = {
	{ "Percentage", &INI::Rva004B60D5_ParsePercentage, 0, 0x118 },
	{ "StartsActive", &INI::parseBool, 0, 0x124 },
	{ "LabelForPalantirString", &INI::parseAsciiString, 0, 0x128 },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@CommandSetUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void CommandSetUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(&s_commandSetTable), 0);
}

// ?buildFieldParse@RadarUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void RadarUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(&s_radarTable), 0);
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
	parse.add(reinterpret_cast<const FieldParse *>(&s_attributeModifierTable), 0);
}

// ?buildFieldParse@DoCommandUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void DoCommandUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(&s_doCommandTable), 0);
}

// ?buildFieldParse@CastleUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
void CastleUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(&s_castleTable), 0);
}

// ?buildFieldParse@CostModifierUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004B5CE9, 34 bytes: getter-head call above plus the CostModifier
// table (retail 0x00C582D8). The owning factory at 0x00250316 pushes this
// proc's VA (unique image-wide); ModuleFactory registers it under
// "CostModifierUpgrade". The CostModifierUpgrade pool key at 0x4B59B7 sits
// in the same cluster. Row supersedes the pin.
void CostModifierUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(&s_costModifierTable), 0);
}

// ?buildFieldParse@SpellRechargeModifierUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004B60FA, 34 bytes: getter-head call above plus the SpellRecharge
// table (retail 0x00C58460). The owning factory at 0x002503A2 pushes this
// proc's VA (unique image-wide); ModuleFactory registers it under
// "SpellRechargeModifierUpgrade". The SpellRechargeModifierUpgrade pool key
// at 0x4B5D38 sits in the same cluster. Row supersedes the pin.
void SpellRechargeModifierUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	parse.add(reinterpret_cast<const FieldParse *>(&s_spellRechargeTable), 0);
}

// ?buildFieldParse@ArmorUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x00254580, 91 bytes: getter-head over rowed 0x4CE29D at extraOffset
// 8 through rowed MultiIniFieldParse::add 0x2BC6E, then a one-time guarded
// patch of the own table (retail VA 0x00DBA870), then add of the own table at
// extraOffset 0. Guard is bit0 of a BSS word (retail VA 0x00DFE9BC,
// unmapped in-image): test/or-bit shape, so an unsigned-int flag with
// &1/|=1, not a bool. Patch stores entry2 userData = VeterancyLevelNames
// (retail VA 0x00DBAA40, sole definition in INI_VeterancyLevelToken.cpp)
// and entry2 offset 0x11C (m_armorSetFlag per the matched 42B ctor) plus an
// explicit zero of the terminator entry; source order matches the ascending
// store order. No ZH/BFME1 donor carries this proc (ZH ArmorUpgrade.cpp has
// no ModuleData parse; BFME1 donor has only ctor/friendNew/upgrade thunks),
// so the shape is target-derived from retail bytes. Factory 0x2545DB
// (matched 52B) pushes this proc; pin 5362 superseded by the row.
void ArmorUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
	if (!(s_armorTableReady & 1))
	{
		s_armorTableReady |= 1;
		s_armorTable[2].m_userData = VeterancyLevelNames;
		s_armorTable[2].m_offset = 0x11C;
		s_armorTable[3].m_name = 0;
		s_armorTable[3].m_parser = 0;
		s_armorTable[3].m_userData = 0;
		s_armorTable[3].m_offset = 0;
	}
	parse.add(reinterpret_cast<const FieldParse *>(&s_armorTable), 0);
}
