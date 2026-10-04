// cl: /O1 /DNDEBUG /MD
//
// GiantBirdAIUpdateModuleData parse-unit.
//
// ?buildFieldParse@GiantBirdAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00368182, 27 bytes. Chained on the rowed
// TransportAIUpdateModuleData base proc at 0x2638FF, then the own table
// at 0x00C178D8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "GiantBirdAIUpdate". Row supersedes the parse pin.

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
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

extern const char *TheLocomotorSetNames[];
// Retail VA 0x00C178D8 (.rdata): 8 field records and a zero sentinel.
extern const FieldParse g_00C178D8[] = {
	{ "AttackLocomotorType", &INI::parseIndexList, TheLocomotorSetNames, 0x64 },
	{ "ReturnForAmmoLocomotorType", &INI::parseIndexList, TheLocomotorSetNames, 0x68 },
	{ "GrabTossTimeTrigger", &INI::parseReal, 0, 0x6C },
	{ "GrabTossHeightTrigger", &INI::parseReal, 0, 0x70 },
	{ "FollowThroughDistance", &INI::parseReal, 0, 0x74 },
	{ "FollowThroughCheckStep", &INI::parseReal, 0, 0x78 },
	{ "FollowThroughGradient", &INI::parseReal, 0, 0x7C },
	{ "TossFX", &INI::parseFXList, 0, 0x80 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class TransportAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class GiantBirdAIUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@GiantBirdAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00368182
void GiantBirdAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00C178D8, 0);
}
