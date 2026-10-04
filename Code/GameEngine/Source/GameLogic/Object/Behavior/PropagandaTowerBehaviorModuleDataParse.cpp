// cl: /O1 /DNDEBUG /MD
//
// PropagandaTowerBehaviorModuleData file-unit (parse first; the ctor
// remains pinned for a follow-up). Distinct TU name because
// PropagandaTowerBehaviorModuleDataCtor.cpp already holds the
// DetachableRiderUpdateModuleData ctor at 0x4AEAB7.
//
// ?buildFieldParse@PropagandaTowerBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004819BE, 17 bytes. Single-table parse proc (table 0x00C49368)
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
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C49368 (.rdata): 7 field records and a zero sentinel.
extern const FieldParse g_00C49368[] = {
	{ "Radius", &INI::parseReal, 0, 0x8 },
	{ "DelayBetweenUpdates", &INI::parseDurationUnsignedInt, 0, 0xC },
	{ "HealPercentEachSecond", &INI::parsePercentToReal, 0, 0x10 },
	{ "UpgradedHealPercentEachSecond", &INI::parsePercentToReal, 0, 0x1C },
	{ "PulseFX", &INI::parseFXList, 0, 0x14 },
	{ "UpgradeRequired", &INI::parseAsciiString, 0, 0x18 },
	{ "UpgradedPulseFX", &INI::parseFXList, 0, 0x20 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class PropagandaTowerBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@PropagandaTowerBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004819BE
void PropagandaTowerBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00C49368, 0);
}
