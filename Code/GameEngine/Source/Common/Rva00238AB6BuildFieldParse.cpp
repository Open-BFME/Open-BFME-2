// cl: /O1 /DNDEBUG /MD
// ?buildFieldParse@Rva00238AB6@@SAXAAVMultiIniFieldParse@@@Z @0x00238AB6 17B single add table 0x00BED3E0 offset 0.
// Evidence: unlock lane single-table shape via rowed add 0x0002BC6E; caller 0x0004171A.
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
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00BED3E0 (.rdata): 15 field records and a zero sentinel.
extern const FieldParse g_00BED3E0[] = {
	{ "AudioRoot", &INI::parseAsciiString, 0, 0x50 },
	{ "SoundsFolder", &INI::parseAsciiString, 0, 0x4 },
	{ "MusicFolder", &INI::parseAsciiString, 0, 0x8 },
	{ "StreamingFolder", &INI::parseAsciiString, 0, 0xC },
	{ "AmbientStreamFolder", &INI::parseAsciiString, 0, 0x10 },
	{ "SoundsExtension", &INI::parseAsciiString, 0, 0x14 },
	{ "MusicScriptLibraryName", &INI::parseAsciiString, 0, 0x18 },
	{ "DefaultSoundVolume", &INI::parsePercentToReal, 0, 0x1C },
	{ "DefaultVoiceVolume", &INI::parsePercentToReal, 0, 0x20 },
	{ "DefaultMusicVolume", &INI::parsePercentToReal, 0, 0x24 },
	{ "DefaultMovieVolume", &INI::parsePercentToReal, 0, 0x2C },
	{ "DefaultAmbientVolume", &INI::parsePercentToReal, 0, 0x28 },
	{ "VoiceMoveToCampMaxCampnessAtStartPoint", &INI::dup_002EF72, 0, 0x44 },
	{ "VoiceMoveToCampMinCampnessAtEndPoint", &INI::dup_002EF72, 0, 0x48 },
	{ "MinDelayBetweenEnterStateVoiceMS", &INI::parseDurationUnsignedInt, 0, 0x4C },
	{ 0, 0, 0, 0 }
};
class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};
class Rva00238AB6
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};
void Rva00238AB6::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00BED3E0, 0);
}
