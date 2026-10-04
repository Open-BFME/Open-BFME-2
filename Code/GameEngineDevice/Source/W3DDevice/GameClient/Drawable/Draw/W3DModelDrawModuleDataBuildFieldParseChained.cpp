// cl: /O1 /DNDEBUG /MD
//
// Chained W3D draw ModuleData::buildFieldParse procs: each calls its
// base-class buildFieldParse, then registers its own FieldParse table with
// MultiIniFieldParse::add (rowed at 0x2BC6E). The base
// (W3DModelDrawModuleData::buildFieldParse, rowed at 0xC9240) is declared
// here but defined in W3DModelDrawModuleDataBuildFieldParse.cpp, so the base
// call stays an out-of-line E8 exactly like retail. Bodies:
// ?buildFieldParse@W3DSupplyDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x000CAE28, 27 bytes (field SupplyBonePrefix at 0x188; donor
// reference: BFME1 W3DSupplyDraw.cpp keeps the same single-field table).
// ?buildFieldParse@W3DTruckDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x000CB133, 27 bytes (table 0xBCC358: Dust, DirtSpray,
// PowerslideSpray plus tire/cab/trailer bones through CabRotationMultiplier
// at 0x1DC; donor reference: BFME1 W3DTruckDrawModuleData_buildFieldParse.cpp
// describes the same table).

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
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseVelocityReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00BCBED8 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00BCBED8[] = {
	{ "SupplyBonePrefix", &INI::parseAsciiString, 0, 0x188 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00BCCAD0 (.rdata): 5 field records and a zero sentinel.
extern const FieldParse g_00BCCAD0[] = {
	{ "TreadDebrisLeft", &INI::parseAsciiString, 0, 0x188 },
	{ "TreadDebrisRight", &INI::parseAsciiString, 0, 0x18C },
	{ "TreadAnimationRate", &INI::parseVelocityReal, 0, 0x190 },
	{ "TreadPivotSpeedFraction", &INI::parseReal, 0, 0x194 },
	{ "TreadDriveSpeedFraction", &INI::parseReal, 0, 0x198 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00BCBB28 (.rdata): 4 field records and a zero sentinel.
extern const FieldParse g_00BCBB28[] = {
	{ "LeftFrontFootBone", &INI::parseAsciiString, 0, 0x188 },
	{ "RightFrontFootBone", &INI::parseAsciiString, 0, 0x18C },
	{ "LeftRearFootBone", &INI::parseAsciiString, 0, 0x190 },
	{ "RightRearFootBone", &INI::parseAsciiString, 0, 0x194 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00BCC358 (.rdata): 26 field records and a zero sentinel.
extern const FieldParse g_00BCC358[] = {
	{ "Dust", &INI::parseAsciiString, 0, 0x188 },
	{ "DirtSpray", &INI::parseAsciiString, 0, 0x18C },
	{ "PowerslideSpray", &INI::parseAsciiString, 0, 0x190 },
	{ "LeftFrontTireBone", &INI::parseAsciiString, 0, 0x194 },
	{ "RightFrontTireBone", &INI::parseAsciiString, 0, 0x198 },
	{ "LeftRearTireBone", &INI::parseAsciiString, 0, 0x19C },
	{ "RightRearTireBone", &INI::parseAsciiString, 0, 0x1A0 },
	{ "MidLeftFrontTireBone", &INI::parseAsciiString, 0, 0x1A4 },
	{ "MidRightFrontTireBone", &INI::parseAsciiString, 0, 0x1A8 },
	{ "MidLeftRearTireBone", &INI::parseAsciiString, 0, 0x1AC },
	{ "MidRightRearTireBone", &INI::parseAsciiString, 0, 0x1B0 },
	{ "MidLeftMidTireBone", &INI::parseAsciiString, 0, 0x1B4 },
	{ "MidRightMidTireBone", &INI::parseAsciiString, 0, 0x1B8 },
	{ "LeftFrontTireBone2", &INI::parseAsciiString, 0, 0x1BC },
	{ "RightFrontTireBone2", &INI::parseAsciiString, 0, 0x1C0 },
	{ "LeftRearTireBone2", &INI::parseAsciiString, 0, 0x1C4 },
	{ "RightRearTireBone2", &INI::parseAsciiString, 0, 0x1C8 },
	{ "MidLeftMidTireBone2", &INI::parseAsciiString, 0, 0x1CC },
	{ "MidRightMidTireBone2", &INI::parseAsciiString, 0, 0x1D0 },
	{ "TireRotationMultiplier", &INI::parseReal, 0, 0x1E8 },
	{ "PowerslideRotationAddition", &INI::parseReal, 0, 0x1EC },
	{ "CabBone", &INI::parseAsciiString, 0, 0x1D4 },
	{ "TrailerBone", &INI::parseAsciiString, 0, 0x1D8 },
	{ "CabRotationMultiplier", &INI::parseReal, 0, 0x1DC },
	{ "TrailerRotationMultiplier", &INI::parseReal, 0, 0x1E0 },
	{ "RotationDamping", &INI::parseReal, 0, 0x1E4 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class W3DModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class W3DSupplyDrawModuleData : public W3DModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void W3DSupplyDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	W3DModelDrawModuleData::buildFieldParse(parse);
	parse.add(g_00BCBED8, 0);
}

class W3DTruckDrawModuleData : public W3DModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void W3DTruckDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	W3DModelDrawModuleData::buildFieldParse(parse);
	parse.add(g_00BCC358, 0);
}

class W3DTankDrawModuleData : public W3DModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void W3DTankDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	W3DModelDrawModuleData::buildFieldParse(parse);
	parse.add(g_00BCCAD0, 0);
}

class W3DQuadrupedDrawModuleData : public W3DModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void W3DQuadrupedDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	W3DModelDrawModuleData::buildFieldParse(parse);
	parse.add(g_00BCBB28, 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?W3DSupplyDrawModuleDataParse@@YAXAAVMultiIniFieldParse@@@Z=?buildFieldParse@W3DSupplyDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z")
#pragma comment(linker, "/alternatename:?W3DTruckDrawModuleDataParse@@YAXAAVMultiIniFieldParse@@@Z=?buildFieldParse@W3DTruckDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z")
#pragma comment(linker, "/alternatename:?W3DTankDrawModuleDataParse@@YAXAAVMultiIniFieldParse@@@Z=?buildFieldParse@W3DTankDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z")
#pragma comment(linker, "/alternatename:?W3DQuadrupedDrawModuleDataParse@@YAXAAVMultiIniFieldParse@@@Z=?buildFieldParse@W3DQuadrupedDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z")
