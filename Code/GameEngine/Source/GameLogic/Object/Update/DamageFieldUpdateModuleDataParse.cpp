// cl: /O1 /DNDEBUG /MD
//
// DamageFieldUpdateModuleData parse-unit.
//
// ?buildFieldParse@DamageFieldUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004910E7, 27 bytes. Chained on the rowed
// FireWeaponUpdateModuleData base proc at 0x48C0B4, then the own table
// at 0x00C4D8A8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "DamageFieldUpdate". Row supersedes the parse pin.

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
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
// Retail VA 0x00C4D8A8 (.rdata): 3 field records and a zero sentinel.
extern const FieldParse g_00C4D8A8[] = {
	{ "Radius", &INI::parseInt, 0, 0x10 },
	{ "ObjectFilter", &iniParseObjectFilter, 0, 0x14 },
	{ "RequiredUpgrade", &INI::parseAsciiString, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class FireWeaponUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class DamageFieldUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DamageFieldUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004910E7
void DamageFieldUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	FireWeaponUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00C4D8A8, 0);
}
