// cl: /O1 /DNDEBUG /MD
//
// HealContainModuleData parse-unit (see ContainModuleDataFriendNew.cpp for
// the owner, which registers this proc with initFromINIMultiProc).
//
// ?buildFieldParse@HealContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00466AD0, 27 bytes. Chained on the rowed OpenContainModuleData
// base proc at 0x46523D, then the own table at 0x00C43D24, through the
// rowed MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes this
// proc VA; ModuleFactory registers it under "HealContain".
// Row supersedes the parse pin.

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
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C43D24 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00C43D24[] = {
	{ "TimeForFullHeal", &INI::parseDurationUnsignedInt, 0, 0x98 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class OpenContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class HealContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@HealContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00466AD0
void HealContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	OpenContainModuleData::buildFieldParse(parse);
	parse.add(g_00C43D24, 0);
}
