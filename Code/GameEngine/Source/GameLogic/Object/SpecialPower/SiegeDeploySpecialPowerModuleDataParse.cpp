// cl: /O1 /DNDEBUG /MD
//
// SiegeDeploySpecialPowerModuleData parse-unit.
//
// ?buildFieldParse@SiegeDeploySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004C569F, 27 bytes. Chained on the Rva005890EDBase proc at
// 0x5890ED, then the own table at 0x00C5DBD8 (LowerDelay, RaiseDelay,
// EvacuatePassengersOnDeploy, EvacuateCrewOnDeploy, SkipAdjustPosition,
// WallSearchDistance, AwayFromWallWaitDist, ExtraWallDistance), through
// the rowed MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes
// this proc VA; ModuleFactory registers it under "SiegeDeploySpecialPower".
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
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C5DBD8 (.rdata): 8 field records and a zero sentinel.
extern const FieldParse g_00C5DBD8[] = {
	{ "LowerDelay", &INI::parseDurationUnsignedInt, 0, 0x18 },
	{ "RaiseDelay", &INI::parseDurationUnsignedInt, 0, 0x1C },
	{ "EvacuatePassengersOnDeploy", &INI::parseBool, 0, 0x20 },
	{ "EvacuateCrewOnDeploy", &INI::parseBool, 0, 0x21 },
	{ "SkipAdjustPosition", &INI::parseBool, 0, 0x22 },
	{ "WallSearchDistance", &INI::parseReal, 0, 0x24 },
	{ "AwayFromWallWaitDist", &INI::parseReal, 0, 0x28 },
	{ "ExtraWallDistance", &INI::parseReal, 0, 0x2C },
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

class SiegeDeploySpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@SiegeDeploySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004C569F
void SiegeDeploySpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva005890EDBase::buildFieldParse(parse);
	parse.add(g_00C5DBD8, 0);
}
