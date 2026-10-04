// cl: /O1 /DNDEBUG /MD
//
// RepairDockUpdateModuleData parse-unit.
//
// ?buildFieldParse@RepairDockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004A1170, 27 bytes. Chained on the rowed
// DockUpdateModuleData base proc at 0x5896C1, then the own table
// at 0x00C51C10, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "RepairDockUpdate". Row supersedes the parse pin.

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
	static void parseDurationReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C51C10 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00C51C10[] = {
	{ "TimeForFullHeal", &INI::parseDurationReal, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class RepairDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@RepairDockUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004A1170
void RepairDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00C51C10, 0);
}
