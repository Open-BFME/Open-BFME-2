// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME1 FX particle module parser transferred to the BFME2 parser-table
// address.  The body is intentionally kept separate from the factory TU so
// each exported parser has an independently verifiable boundary.

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};
extern const int g_emptyFieldParseTable[4];

class INI
{
public:
    void initFromINI(void *what, const FieldParse *parseTable);
    static void Rva00563EA8_ParseEventFX(INI *ini, void *instance, void *store, const void *userData);
    static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
    static void parseBool(INI *ini, void *instance, void *store, const void *userData);
    static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
    static void parseGameClientRandomVariable(INI *ini, void *instance, void *store, const void *userData);
    static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
    static void parseInt(INI *ini, void *instance, void *store, const void *userData);
    static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C1B6D8 (.rdata): the particle rotation names the
// RenderObjectUpdate table (0x00C6C710) parses through INI::parseIndexList,
// six names and the NULL sentinel; the string data that follows ends it.
extern const char *const g_00C1B6D8[] = {
    "NONE", "ROTATION_OFF", "ROTATE_X", "ROTATE_Y", "ROTATE_Z", "ROTATE_V", 0
};

namespace FXParticleSystem { extern const char *ParticleShaderTypeNames[]; }
// Retail VA 0x00C6C230 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00C6C230[] = {
	{ "Speed", &INI::parseGameClientRandomVariable, 0, 0xC },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6CA20 (.rdata): 4 field records and a zero sentinel.
extern const FieldParse g_00C6CA20[] = {
	{ "FramesPerRow", &INI::parseInt, 0, 0xC },
	{ "TotalFrames", &INI::parseInt, 0, 0x10 },
	{ "DetailTexture", &INI::parseAsciiString, 0, 0x14 },
	{ "SpeedMultiplier", &INI::parseReal, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6C390 (.rdata): 2 field records and a zero sentinel.
extern const FieldParse g_00C6C390[] = {
	{ "Speed", &INI::parseGameClientRandomVariable, 0, 0xC },
	{ "OtherSpeed", &INI::parseGameClientRandomVariable, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6C8E0 (.rdata): 15 field records and a zero sentinel.
extern const FieldParse g_00C6C8E0[] = {
	{ "MultiRenderObjects", &INI::parseBool, 0, 0x14 },
	{ "RenderGroup1", &INI::parseAsciiString, 0, 0x18 },
	{ "NumObjects1", &INI::parseInt, 0, 0x1C },
	{ "Percent1", &INI::parseReal, 0, 0x20 },
	{ "Shader1", &INI::parseIndexList, FXParticleSystem::ParticleShaderTypeNames, 0x24 },
	{ "RenderGroup2", &INI::parseAsciiString, 0, 0x28 },
	{ "NumObjects2", &INI::parseInt, 0, 0x2C },
	{ "Percent2", &INI::parseReal, 0, 0x30 },
	{ "Shader2", &INI::parseIndexList, FXParticleSystem::ParticleShaderTypeNames, 0x34 },
	{ "RenderGroup3", &INI::parseAsciiString, 0, 0x38 },
	{ "NumObjects3", &INI::parseInt, 0, 0x3C },
	{ "Percent3", &INI::parseReal, 0, 0x40 },
	{ "Shader3", &INI::parseIndexList, FXParticleSystem::ParticleShaderTypeNames, 0x44 },
	{ "SinkOnTerrainCollision", &INI::parseBool, 0, 0xC },
	{ "SinkRate", &INI::parseReal, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6C1B0 (.rdata): 3 field records and a zero sentinel.
extern const FieldParse g_00C6C1B0[] = {
	{ "X", &INI::parseGameClientRandomVariable, 0, 0xC },
	{ "Y", &INI::parseGameClientRandomVariable, 0, 0x18 },
	{ "Z", &INI::parseGameClientRandomVariable, 0, 0x24 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6BEB0 (.rdata): 5 field records and a zero sentinel.
extern const FieldParse g_00C6BEB0[] = {
	{ "IsHollow", &INI::parseBool, 0, 0xC },
	{ "Radius", &INI::parseReal, 0, 0x10 },
	{ "RadiusRate", &INI::parseReal, 0, 0x14 },
	{ "Length", &INI::parseReal, 0, 0x18 },
	{ "Offset", &INI::parseCoord3D, 0, 0x1C },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6BCD0 (.rdata): 2 field records and a zero sentinel.
extern const FieldParse g_00C6BCD0[] = {
	{ "IsHollow", &INI::parseBool, 0, 0xC },
	{ "HalfSize", &INI::parseCoord3D, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6BB6C (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00C6BB6C[] = {
	{ "IsHollow", &INI::parseBool, 0, 0xC },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6C710 (.rdata): 13 field records and a zero sentinel.
extern const FieldParse g_00C6C710[] = {
	{ "StartSizeX", &INI::parseGameClientRandomVariable, 0, 0xC },
	{ "StartSizeY", &INI::parseGameClientRandomVariable, 0, 0x18 },
	{ "StartSizeZ", &INI::parseGameClientRandomVariable, 0, 0x24 },
	{ "SizeRateX", &INI::parseGameClientRandomVariable, 0, 0x30 },
	{ "SizeRateY", &INI::parseGameClientRandomVariable, 0, 0x3C },
	{ "SizeRateZ", &INI::parseGameClientRandomVariable, 0, 0x48 },
	{ "SizeDampingX", &INI::parseGameClientRandomVariable, 0, 0x54 },
	{ "SizeDampingY", &INI::parseGameClientRandomVariable, 0, 0x60 },
	{ "SizeDampingZ", &INI::parseGameClientRandomVariable, 0, 0x6C },
	{ "AngleZ", &INI::parseGameClientRandomVariable, 0, 0x78 },
	{ "AngularRateZ", &INI::parseGameClientRandomVariable, 0, 0x84 },
	{ "AngularDamping", &INI::parseGameClientRandomVariable, 0, 0x90 },
	{ "Rotation", &INI::parseIndexList, g_00C1B6D8, 0x9C },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6C128 (.rdata): 4 field records and a zero sentinel.
extern const FieldParse g_00C6C128[] = {
	{ "Xoffset", &INI::parseGameClientRandomVariable, 0, 0x10 },
	{ "Yoffset", &INI::parseGameClientRandomVariable, 0, 0x1C },
	{ "Zoffset", &INI::parseGameClientRandomVariable, 0, 0x28 },
	{ "CellEmissionChance", &INI::parseReal, 0, 0x34 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6C008 (.rdata): 11 field records and a zero sentinel.
extern const FieldParse g_00C6C008[] = {
	{ "StartPoint", &INI::parseCoord3D, 0, 0x10 },
	{ "EndPoint", &INI::parseCoord3D, 0, 0x1C },
	{ "Amplitude1", &INI::parseGameClientRandomVariable, 0, 0x28 },
	{ "Frequency1", &INI::parseGameClientRandomVariable, 0, 0x34 },
	{ "Phase1", &INI::parseGameClientRandomVariable, 0, 0x40 },
	{ "Amplitude2", &INI::parseGameClientRandomVariable, 0, 0x4C },
	{ "Frequency2", &INI::parseGameClientRandomVariable, 0, 0x58 },
	{ "Phase2", &INI::parseGameClientRandomVariable, 0, 0x64 },
	{ "Amplitude3", &INI::parseGameClientRandomVariable, 0, 0x70 },
	{ "Frequency3", &INI::parseGameClientRandomVariable, 0, 0x7C },
	{ "Phase3", &INI::parseGameClientRandomVariable, 0, 0x88 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6BBD8 (.rdata): 3 field records and a zero sentinel.
extern const FieldParse g_00C6BBD8[] = {
	{ "IsHollow", &INI::parseBool, 0, 0xC },
	{ "StartPoint", &INI::parseCoord3D, 0, 0x10 },
	{ "EndPoint", &INI::parseCoord3D, 0, 0x1C },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6C294 (.rdata): 2 field records and a zero sentinel.
extern const FieldParse g_00C6C294[] = {
	{ "Radial", &INI::parseGameClientRandomVariable, 0, 0xC },
	{ "Normal", &INI::parseGameClientRandomVariable, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6C608 (.rdata): 5 field records and a zero sentinel.
extern const FieldParse g_00C6C608[] = {
	{ "OffsetX", &INI::parseGameClientRandomVariable, 0, 0xC },
	{ "OffsetY", &INI::parseGameClientRandomVariable, 0, 0x18 },
	{ "OffsetZ", &INI::parseGameClientRandomVariable, 0, 0x24 },
	{ "MultiChance", &INI::parseReal, 0, 0x30 },
	{ "TileTexture", &INI::parseBool, 0, 0x34 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6CB68 (.rdata): 5 field records and a zero sentinel.
extern const FieldParse g_00C6CB68[] = {
	{ "HeightOffset", &INI::parseGameClientRandomVariable, 0, 0x14 },
	{ "EventFX", &INI::Rva00563EA8_ParseEventFX, 0, 0x10 },
	{ "OrientFXToTerrain", &INI::parseBool, 0, 0x20 },
	{ "PerParticle", &INI::parseBool, 0, 0x8 },
	{ "KillAfterEvent", &INI::parseBool, 0, 0x9 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6CAC0 (.rdata): 4 field records and a zero sentinel.
extern const FieldParse g_00C6CAC0[] = {
	{ "EventTime", &INI::parseGameClientRandomVariable, 0, 0x14 },
	{ "EventFX", &INI::Rva00563EA8_ParseEventFX, 0, 0x10 },
	{ "PerParticle", &INI::parseBool, 0, 0x8 },
	{ "KillAfterEvent", &INI::parseBool, 0, 0x9 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6BDB4 (.rdata): 2 field records and a zero sentinel.
extern const FieldParse g_00C6BDB4[] = {
	{ "IsHollow", &INI::parseBool, 0, 0xC },
	{ "Radius", &INI::parseReal, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

namespace FXParticleSystem
{
class PointEmissionVolumeModuleTemplate
{
public:
    void parse(INI *ini);
};

// ?parse@PointEmissionVolumeModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void PointEmissionVolumeModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, g_00C6BB6C);
}
}

namespace FXParticleSystem
{

#define FX_PARTICLE_PARSER(CLASS, TABLE)                                      \
class CLASS                                                                  \
{                                                                            \
public:                                                                      \
    void parse(INI *ini);                                                    \
};                                                                           \
void CLASS::parse(INI *ini)                                                  \
{                                                                            \
    ini->initFromINI(this, reinterpret_cast<const FieldParse *>(TABLE));     \
}

FX_PARTICLE_PARSER(LineEmissionVolumeModuleTemplate, g_00C6BBD8)
FX_PARTICLE_PARSER(BoxEmissionVolumeModuleTemplate, g_00C6BCD0)
FX_PARTICLE_PARSER(SphereEmissionVolumeModuleTemplate, g_00C6BDB4)
FX_PARTICLE_PARSER(CylinderEmissionVolumeModuleTemplate, g_00C6BEB0)
FX_PARTICLE_PARSER(LightningEmissionModuleTemplate, g_00C6C008)
FX_PARTICLE_PARSER(OrthoEmissionVelocityModuleTemplate, g_00C6C1B0)
FX_PARTICLE_PARSER(SphericalEmissionVelocityModuleTemplate, g_00C6C230)
FX_PARTICLE_PARSER(CylindricalEmissionVelocityModuleTemplate, g_00C6C294)
FX_PARTICLE_PARSER(OutwardEmissionVelocityModuleTemplate, g_00C6C390)
FX_PARTICLE_PARSER(StreakDrawModuleTemplate, g_emptyFieldParseTable)
FX_PARTICLE_PARSER(QuadDrawModuleTemplate, g_emptyFieldParseTable)
FX_PARTICLE_PARSER(ButterflyDrawModuleTemplate, g_emptyFieldParseTable)
FX_PARTICLE_PARSER(LightningDrawModuleTemplate, g_00C6C608)
FX_PARTICLE_PARSER(RenderObjectUpdateModuleTemplate, g_00C6C710)
FX_PARTICLE_PARSER(RenderObjectDrawModuleTemplate, g_00C6C8E0)
FX_PARTICLE_PARSER(LifeEventModuleTemplate, g_00C6CAC0)
FX_PARTICLE_PARSER(TerrainCollisionModuleTemplate, g_00C6CB68)
FX_PARTICLE_PARSER(TerrainFireEmissionModuleTemplate, g_00C6C128)
FX_PARTICLE_PARSER(GpuDrawModuleTemplate, g_00C6CA20)

#undef FX_PARTICLE_PARSER
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?parse@HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z=?parse@SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z")

// Native 55CAAC..55CAEF scales a random unit vector into its return storage.
// BFME1 968ca36c: PointEmissionVolumeVelocity.cpp supplies the return-by-value
// shape; the original BFME2 method name and unused argument types are unknown.
#include "../../../Libraries/Include/Lib/Coord3D.h"
Coord3D *__cdecl Rva003AFA64FillUnitVector(Coord3D *out);

struct Rva0055CAACVector
{
	Rva0055CAACVector() {}
	__forceinline Rva0055CAACVector(const Rva0055CAACVector &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	float x, y, z;
};

Rva0055CAACVector __stdcall Rva0055CAAC(unsigned int, float scale, unsigned int)
{
	Rva0055CAACVector direction;
	Rva003AFA64FillUnitVector(reinterpret_cast<Coord3D *>(&direction));
	Rva0055CAACVector result;
	result.x = direction.x * scale;
	result.y = direction.y * scale;
	result.z = direction.z * scale;
	return result;
}

// Native 55CAEF..55CB45: RET12 and two local XYZ records passed to
// View vtable slot 11. The second endpoint is two units higher in Z;
// retail uses the double-precision constant at VA00BC34F8.
class View;
extern View *TheTacticalView;
struct Rva0055CAEFPoint { float x, y, z; };
struct Rva0055CAEFView
{
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10();
    virtual void s11(const Rva0055CAEFPoint *, const Rva0055CAEFPoint *, unsigned);
};

void __stdcall Rva0055CAEFDraw(float x, float y, float z)
{
    Rva0055CAEFPoint first = {x, y, z};
    Rva0055CAEFPoint second = {x, y, static_cast<float>(z + 2.0)};
    reinterpret_cast<Rva0055CAEFView *>(TheTacticalView)->s11(&first, &second, 0xCCAAFFFF);
}
