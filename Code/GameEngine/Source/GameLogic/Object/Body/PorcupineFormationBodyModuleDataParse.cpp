// cl: /O1 /DNDEBUG /MD
//
// PorcupineFormationBodyModuleData parse-unit.
//
// ?buildFieldParse@PorcupineFormationBodyModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C1FCB, 27 bytes. Chained on the rowed
// ActiveBodyModuleData base proc at 0x4BFDF6, then the own table
// at 0x00C5C2D8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "PorcupineFormationBodyModule". Row supersedes the parse pin.

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
	static void parseByte(INI *ini, void *instance, void *store, const void *userData);
	static void parseWeaponTemplate(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C5C2D8 (.rdata): 3 field records and a zero sentinel.
extern const FieldParse g_00C5C2D8[] = {
	{ "DamageWeaponTemplate", &INI::parseWeaponTemplate, 0, 0x64 },
	{ "CrushDamageWeaponTemplate", &INI::parseWeaponTemplate, 0, 0x68 },
	{ "CrusherLevelResisted", &INI::parseByte, 0, 0x6C },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class ActiveBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class PorcupineFormationBodyModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@PorcupineFormationBodyModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004C1FCB
void PorcupineFormationBodyModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	ActiveBodyModuleData::buildFieldParse(parse);
	parse.add(g_00C5C2D8, 0);
}
