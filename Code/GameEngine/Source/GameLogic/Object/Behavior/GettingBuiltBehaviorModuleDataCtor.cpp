// cl: /O1 /DNDEBUG /MD
//
// GettingBuiltBehaviorModuleData file-unit (parse first; the ctor at
// 0x45324E remains pinned for a follow-up).
//
// ?buildFieldParse@GettingBuiltBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00453396, 17 bytes. Single-table parse proc (table 0x00C402A0)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.

class MultiIniFieldParse;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseWeaponTemplate(INI *ini, void *instance, void *store, const void *userData);
};

void Rva00339900Parse(INI *ini, void *instance, void *store, const void *userData);
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
// Retail VA 0x00C402A0 (.rdata): 17 field records and a zero sentinel.
extern const FieldParse g_00C402A0[] = {
	{ "WorkerName", &INI::parseAsciiString, 0, 0x14 },
	{ "EvilWorkerName", &INI::parseAsciiString, 0, 0x18 },
	{ "TestFaction", &INI::parseBool, 0, 0x1C },
	{ "SpawnTimer", &INI::parseReal, 0, 0x20 },
	{ "RebuildWhenDead", &INI::parseBool, 0, 0x2C },
	{ "HealWeapon", &INI::parseWeaponTemplate, 0, 0x28 },
	{ "RebuildTimeSeconds", &INI::parseReal, 0, 0x24 },
	{ "SelfBuildingLoop", &Rva00339900Parse, 0, 0x8 },
	{ "SelfRepairFromDamageLoop", &Rva00339900Parse, 0, 0xC },
	{ "SelfRepairFromRubbleLoop", &Rva00339900Parse, 0, 0x10 },
	{ "PercentOfBuildCostToRebuildPristine", &INI::parsePercentToReal, 0, 0x30 },
	{ "PercentOfBuildCostToRebuildDamaged", &INI::parsePercentToReal, 0, 0x34 },
	{ "PercentOfBuildCostToRebuildReallyDamaged", &INI::parsePercentToReal, 0, 0x38 },
	{ "PercentOfBuildCostToRebuildRubble", &INI::parsePercentToReal, 0, 0x3C },
	{ "DisallowRebuildFilter", &iniParseObjectFilter, 0, 0x40 },
	{ "DisallowRebuildRange", &INI::parseReal, 0, 0x44 },
	{ "UseSpawnTimerWithoutWorker", &INI::parseBool, 0, 0x48 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class GettingBuiltBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@GettingBuiltBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00453396
void GettingBuiltBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00C402A0, 0);
}
