// cl: /DNDEBUG /MD
//
// ?buildFieldParse@RiderChangeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0047E477, 119 bytes. Chained on the rowed SiegeEngineContain base
// proc at 0x47B9F5, then the own Rider table at 0xDC9CA0 (Rider1-8 via the
// rowed parseRiderInfo at 0x47E3E1, ScuttleDelay via parseDurationUnsignedInt,
// ScuttleStatus via parseIndexList plus the ModelCondition bit names,
// KillRiderWhenVehicleDies via parseBool) through the rowed
// MultiIniFieldParse::add at 0x2BC6E. BFME1 donor is Transport-based; BFME2
// chains through SiegeEngine. Row supersedes the parse pin.

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *m_name;
	INIFieldParseProc m_parser;
	const void *m_userData;
	int m_offset;
};

class INI
{
public:
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class SiegeEngineContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

extern const char *const ModelConditionNames[];

class ModelConditionFlags
{
public:
	__forceinline static const char **getBitNames()
	{
		return (const char **)(unsigned int)ModelConditionNames;
	}
};

class RiderChangeContainModuleData
{
public:
	static void parseRiderInfo(INI *ini, void *instance, void *store, const void *userData);
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@RiderChangeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0047E477
void RiderChangeContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SiegeEngineContainModuleData::buildFieldParse(parse);

	static const FieldParse dataFieldParse[] =
	{
		{ "Rider1", &RiderChangeContainModuleData::parseRiderInfo, 0, 0x1B8 },
		{ "Rider2", &RiderChangeContainModuleData::parseRiderInfo, 0, 0x1D0 },
		{ "Rider3", &RiderChangeContainModuleData::parseRiderInfo, 0, 0x1E8 },
		{ "Rider4", &RiderChangeContainModuleData::parseRiderInfo, 0, 0x200 },
		{ "Rider5", &RiderChangeContainModuleData::parseRiderInfo, 0, 0x218 },
		{ "Rider6", &RiderChangeContainModuleData::parseRiderInfo, 0, 0x230 },
		{ "Rider7", &RiderChangeContainModuleData::parseRiderInfo, 0, 0x248 },
		{ "Rider8", &RiderChangeContainModuleData::parseRiderInfo, 0, 0x260 },
		{ "ScuttleDelay", &INI::parseDurationUnsignedInt, 0, 0x278 },
		{ "ScuttleStatus", &INI::parseIndexList, (const void *)ModelConditionFlags::getBitNames(), 0x27C },
		{ "KillRiderWhenVehicleDies", &INI::parseBool, 0, 0x280 },
		{ 0, 0, 0, 0 }
	};
	parse.add(dataFieldParse, 0);
}
