// cl: /O1 /DNDEBUG /MD
//
// ?buildFieldParse@W3DTreeDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x000CED03 (17 bytes: a single MultiIniFieldParse::add of the class
// table at 0x00BCCFE8 with offset 0). The table runs ModelName, TextureName,
// MoveOutwardTime, MoveInwardTime, MoveOutwardDistanceFactor, DarkeningFactor,
// ToppleFX, BounceFX, StumpName, KillWhenFinishedToppling, DoTopple,
// InitialVelocityPercent, InitialAccelPercent, BounceVelocityPercent,
// MinimumToppleSpeed, SinkDistance, SinkTime, MorphTree, MorphTime, MorphFX,
// TaintedTree, FadeRate, FadeTarget, FadeDistance (25 entries plus terminator,
// class size 0x64). The two-phase ModuleData factory at retail 0x00064C0B
// pushes this proc's address before calling INI::initFromINIMultiProc, which
// names the class; the BFME1 W3DTreeDraw donor
// (reference/open-bfme-1/.../Draw/W3DTreeDraw.cpp:90) registers the same
// ModelName/TextureName/MoveOutwardTime/MoveInwardTime spine plus the topple
// block, with BFME2 extending it by Morph/Fade/Tainted entries.

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
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void parsePositiveNonZeroReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00BCCFE8 (.rdata): 24 field records and a zero sentinel.
extern const FieldParse g_00BCCFE8[] = {
	{ "ModelName", &INI::parseAsciiString, 0, 0x8 },
	{ "TextureName", &INI::parseAsciiString, 0, 0xC },
	{ "MoveOutwardTime", &INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "MoveInwardTime", &INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "MoveOutwardDistanceFactor", &INI::parseReal, 0, 0x18 },
	{ "DarkeningFactor", &INI::parseReal, 0, 0x1C },
	{ "ToppleFX", &INI::parseFXList, 0, 0x20 },
	{ "BounceFX", &INI::parseFXList, 0, 0x24 },
	{ "StumpName", &INI::parseAsciiString, 0, 0x28 },
	{ "KillWhenFinishedToppling", &INI::parseBool, 0, 0x3C },
	{ "DoTopple", &INI::parseBool, 0, 0x3D },
	{ "InitialVelocityPercent", &INI::parsePercentToReal, 0, 0x2C },
	{ "InitialAccelPercent", &INI::parsePercentToReal, 0, 0x30 },
	{ "BounceVelocityPercent", &INI::parsePercentToReal, 0, 0x34 },
	{ "MinimumToppleSpeed", &INI::parsePositiveNonZeroReal, 0, 0x38 },
	{ "SinkDistance", &INI::parsePositiveNonZeroReal, 0, 0x44 },
	{ "SinkTime", &INI::parseDurationUnsignedInt, 0, 0x40 },
	{ "MorphTree", &INI::parseAsciiString, 0, 0x48 },
	{ "MorphTime", &INI::parseDurationUnsignedInt, 0, 0x4C },
	{ "MorphFX", &INI::parseFXList, 0, 0x50 },
	{ "TaintedTree", &INI::parseBool, 0, 0x54 },
	{ "FadeRate", &INI::dup_002EF72, 0, 0x58 },
	{ "FadeTarget", &INI::dup_002EF72, 0, 0x5C },
	{ "FadeDistance", &INI::parseReal, 0, 0x60 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class W3DTreeDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void W3DTreeDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00BCCFE8, 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?W3DTreeDrawModuleDataParse@@YAXAAVMultiIniFieldParse@@@Z=?buildFieldParse@W3DTreeDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z")
