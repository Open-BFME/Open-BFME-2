// cl: /O1 /DNDEBUG /MD
//
// AODHordeContainModuleData parse-unit.
//
// ?buildFieldParse@AODHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0047A3B0, 27 bytes. Chained on the rowed HordeContainModuleData
// base proc at 0x475927, then the own table at 0x00C467D8
// (FrequencyScale, FrequencyRandomness, AmplitudeScale, AmplitudeRandomness,
// StillAmplitude and the Z-axis siblings), through the rowed
// MultiIniFieldParse::add at 0x2BC6E. The owning factory pushes this proc
// VA; ModuleFactory registers it under "AODHordeContain". Row supersedes
// the parse pin.

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
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C467D8 (.rdata): 20 field records and a zero sentinel.
extern const FieldParse g_00C467D8[] = {
	{ "FrequencyScale", &INI::parseReal, 0, 0x274 },
	{ "FrequencyRandomness", &INI::parseReal, 0, 0x278 },
	{ "AmplitudeScale", &INI::parseReal, 0, 0x27C },
	{ "FrequencyRandomness", &INI::parseReal, 0, 0x278 },
	{ "AmplitudeRandomness", &INI::parseReal, 0, 0x280 },
	{ "StillAmplitude", &INI::parseReal, 0, 0x284 },
	{ "FrequencyScaleZ", &INI::parseReal, 0, 0x288 },
	{ "FrequencyRandomnessZ", &INI::parseReal, 0, 0x28C },
	{ "AmplitudeScaleZ", &INI::parseReal, 0, 0x290 },
	{ "FrequencyRandomnessZ", &INI::parseReal, 0, 0x28C },
	{ "AmplitudeRandomnessZ", &INI::parseReal, 0, 0x294 },
	{ "StillAmplitudeZ", &INI::parseReal, 0, 0x298 },
	{ "OathFulfilledZFactor", &INI::parseReal, 0, 0x29C },
	{ "LargeUnitHeightFactor", &INI::parseReal, 0, 0x2A0 },
	{ "LargeUnitMinHeight", &INI::parseReal, 0, 0x2A4 },
	{ "LargeUnitMaxHeight", &INI::parseReal, 0, 0x2A8 },
	{ "LargeUnitTimeout", &INI::parseDurationUnsignedInt, 0, 0x2AC },
	{ "LargeUnitTailOff", &INI::parseReal, 0, 0x2B0 },
	{ "ScatterSpeedFactor", &INI::parseReal, 0, 0x2B4 },
	{ "ScatterRandomness", &INI::parseReal, 0, 0x2B8 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class HordeContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class AODHordeContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@AODHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0047A3B0
void AODHordeContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	HordeContainModuleData::buildFieldParse(parse);
	parse.add(g_00C467D8, 0);
}
