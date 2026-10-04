// cl: /O1 /DNDEBUG /MD
//
// CivilianSpawnUpdateModuleData file-unit (parse first; the ctor remains
// pinned for a follow-up).
//
// ?buildFieldParse@CivilianSpawnUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0047F9C3, 17 bytes. Single-table parse proc (table 0x00C48478)
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
	static void parseAsciiStringVector(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
// Retail VA 0x00C48478 (.rdata): 4 field records and a zero sentinel.
extern const FieldParse g_00C48478[] = {
	{ "SpawnDelayTime", &INI::parseDurationUnsignedInt, 0, 0x8 },
	{ "MaximumDistance", &INI::parseInt, 0, 0x10 },
	{ "RunToFilter", &iniParseObjectFilter, 0, 0xC },
	{ "Civilian", &INI::parseAsciiStringVector, 0, 0x14 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class CivilianSpawnUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CivilianSpawnUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0047F9C3
void CivilianSpawnUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00C48478, 0);
}
