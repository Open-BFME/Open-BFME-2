// cl: /O1 /DNDEBUG /MD
//
// SiegeDeployHordeSpecialPowerModuleData parse-unit.
//
// ?buildFieldParse@SiegeDeployHordeSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C636B, 27 bytes. Chained on the Rva005890EDBase proc at
// 0x5890ED, then the own table at 0x00C5DD44 (HordeDeploy), through the
// rowed MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes this
// proc VA; ModuleFactory registers it under "SiegeDeployHordeSpecialPower".
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
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C5DD44 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00C5DD44[] = {
	{ "HordeDeploy", &INI::parseBool, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class Rva005890EDBase
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class SiegeDeployHordeSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@SiegeDeployHordeSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004C636B
void SiegeDeployHordeSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva005890EDBase::buildFieldParse(parse);
	parse.add(g_00C5DD44, 0);
}
