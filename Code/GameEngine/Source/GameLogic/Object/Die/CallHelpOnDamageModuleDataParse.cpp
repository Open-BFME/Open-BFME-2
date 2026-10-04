// cl: /O1 /DNDEBUG /MD
//
// CallHelpOnDamageModuleData parse-unit (the ctor lives in
// CallHelpOnDamageCtor.cpp).
//
// ?buildFieldParse@CallHelpOnDamageModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004BB41B, 33 bytes. Double-table parse proc (tables 0x00C6BB18
// and 0x00C59F70) through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "CallHelpOnDamage". Row supersedes the parse pin.

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
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseDamageTypeFlags(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
// Retail VA 0x00C59F70 (.rdata): 5 field records and a zero sentinel.
extern const FieldParse g_00C59F70[] = {
	{ "DamageTypes", &INI::parseDamageTypeFlags, 0, 0x8 },
	{ "CallRadius", &INI::parseReal, 0, 0xC },
	{ "CallDelay", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "MoveToAttacker", &INI::parseBool, 0, 0x14 },
	{ "ValidObjects", &iniParseObjectFilter, 0, 0x18 },
	{ 0, 0, 0, 0 }
};
extern const int g_emptyFieldParseTable[4];

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class CallHelpOnDamageModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CallHelpOnDamageModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004BB41B
void CallHelpOnDamageModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
	parse.add(g_00C59F70, 0);
}
