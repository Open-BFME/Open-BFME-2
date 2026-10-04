// cl: /O1 /DNDEBUG /MD
//
// W3DStreakDrawModuleData file-unit (parse first; the ctor at 0xD0520
// remains pinned for a follow-up).
//
// ?buildFieldParse@W3DStreakDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000D0726, 17 bytes. Single-table parse proc (table 0x00BCDB60)
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
	static void dup_002EF72(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseRGBColor(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

void Rva000D06C6Parse(INI *ini, void *instance, void *store, const void *userData);
// Retail VA 0x00BCDB60 (.rdata): 7 field records and a zero sentinel.
extern const FieldParse g_00BCDB60[] = {
	{ "Length", &INI::parseReal, 0, 0x8 },
	{ "Width", &INI::parseReal, 0, 0xC },
	{ "Additive", &INI::parseBool, 0, 0x10 },
	{ "Color", &INI::parseRGBColor, 0, 0x14 },
	{ "Texture", &INI::parseAsciiString, 0, 0x24 },
	{ "NumSegments", &INI::dup_002EF72, 0, 0x20 },
	{ "WeatherTexture", &Rva000D06C6Parse, 0, 0x28 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class W3DStreakDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@W3DStreakDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000D0726
void W3DStreakDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00BCDB60, 0);
}
