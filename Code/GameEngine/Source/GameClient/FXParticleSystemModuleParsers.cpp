// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME1 FX particle module parser transferred to the BFME2 parser-table
// address.  The body is intentionally kept separate from the factory TU so
// each exported parser has an independently verifiable boundary.

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../Include/Common/INI/FieldParse.h"
extern const int g_emptyFieldParseTable[4];

#include "../../Include/Common/INI/INI.h"

// Retail VA 0x00C1B6D8 (.rdata): the particle rotation names the
// RenderObjectUpdate table (0x00C6C710) parses through INI::parseIndexList,
// six names and the NULL sentinel; the string data that follows ends it.
// Retail exports it as ?RotationTypeNames@FXParticleSystem@@3QBQBDB (reverse/exports.csv).
namespace FXParticleSystem {
extern const char *const RotationTypeNames[] = {
    "NONE", "ROTATION_OFF", "ROTATE_X", "ROTATE_Y", "ROTATE_Z", "ROTATE_V", 0
};
}

namespace FXParticleSystem { extern const char *const ParticleShaderTypeNames[]; }
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
	{ "Rotation", &INI::parseIndexList, FXParticleSystem::RotationTypeNames, 0x9C },
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

// Retail exports 1834/1835 name the EventFX parser of these two templates;
// both static members are defined in INI_Rva00563EA8ParseEventFX.cpp and fold
// at 0x00563EA8.
namespace FXParticleSystem
{
class LifeEventModuleTemplate
{
public:
    void parse(INI *ini);
    static void parseEventFXListName(INI *ini, void *instance, void *store, const void *userData);
};

class TerrainCollisionModuleTemplate
{
public:
    void parse(INI *ini);
    static void parseEventFXListName(INI *ini, void *instance, void *store, const void *userData);
};
}

// Retail VA 0x00C6CB68 (.rdata): 5 field records and a zero sentinel.
extern const FieldParse g_00C6CB68[] = {
	{ "HeightOffset", &INI::parseGameClientRandomVariable, 0, 0x14 },
	{ "EventFX", &FXParticleSystem::TerrainCollisionModuleTemplate::parseEventFXListName, 0, 0x10 },
	{ "OrientFXToTerrain", &INI::parseBool, 0, 0x20 },
	{ "PerParticle", &INI::parseBool, 0, 0x8 },
	{ "KillAfterEvent", &INI::parseBool, 0, 0x9 },
	{ 0, 0, 0, 0 }
};

// Retail VA 0x00C6CAC0 (.rdata): 4 field records and a zero sentinel.
extern const FieldParse g_00C6CAC0[] = {
	{ "EventTime", &INI::parseGameClientRandomVariable, 0, 0x14 },
	{ "EventFX", &FXParticleSystem::LifeEventModuleTemplate::parseEventFXListName, 0, 0x10 },
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

// Module key/name strings the ModuleTag<CATEGORY, KEY, NAME, ...> registrations
// take by address (FXParticleSystemModules.cpp, FXParticleSystemFactories.cpp).
// Retail lays each KEY, NAME pointer pair out in .rdata beside that module's
// FieldParse table above, followed by the two strings they point at.
namespace FXParticleSystem
{
extern const char *const POINT_EMISSION_VOLUME_MODULE_KEY = "PointEmissionVolume";	// RVA 0x0086BB2C
extern const char *const POINT_EMISSION_VOLUME_MODULE_NAME = "Point Emission Volume";	// RVA 0x0086BB30
extern const char *const LINE_EMISSION_VOLUME_MODULE_KEY = "LineEmissionVolume";	// RVA 0x0086BB8C
extern const char *const LINE_EMISSION_VOLUME_MODULE_NAME = "Line Emission Volume";	// RVA 0x0086BB90
extern const char *const BOX_EMISSION_VOLUME_MODULE_KEY = "BoxEmissionVolume";	// RVA 0x0086BC94
extern const char *const BOX_EMISSION_VOLUME_MODULE_NAME = "Box Emission Volume";	// RVA 0x0086BC98
extern const char *const SPHERE_EMISSION_VOLUME_MODULE_KEY = "SphereEmissionVolume";	// RVA 0x0086BD7C
extern const char *const SPHERE_EMISSION_VOLUME_MODULE_NAME = "Sphere Emission Volume";	// RVA 0x0086BD80
extern const char *const CYLINDER_EMISSION_VOLUME_MODULE_KEY = "CylinderEmissionVolume";	// RVA 0x0086BE64
extern const char *const CYLINDER_EMISSION_VOLUME_MODULE_NAME = "Cylinder Emission Volume";	// RVA 0x0086BE68
extern const char *const LIGHTNING_EMISSION_MODULE_KEY = "LightningEmission";	// RVA 0x0086BF90
extern const char *const LIGHTNING_EMISSION_MODULE_NAME = "Lightning Emission";	// RVA 0x0086BF94
extern const char *const TERRAIN_FIRE_EMISSION_MODULE_KEY = "TerrainFireEmission";	// RVA 0x0086C0C8
extern const char *const TERRAIN_FIRE_EMISSION_MODULE_NAME = "Terrain Fire Emission";	// RVA 0x0086C0CC
extern const char *const ORTHO_EMISSION_VELOCITY_MODULE_KEY = "OrthoEmissionVelocity";	// RVA 0x0086C178
extern const char *const ORTHO_EMISSION_VELOCITY_MODULE_NAME = "Ortho Emission Velocity";	// RVA 0x0086C17C
extern const char *const SPHERICAL_EMISSION_VELOCITY_MODULE_KEY = "SphericalEmissionVelocity";	// RVA 0x0086C1F0
extern const char *const SPHERICAL_EMISSION_VELOCITY_MODULE_NAME = "Spherical Emission Velocity";	// RVA 0x0086C1F4
extern const char *const CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY = "CylindricalEmissionVelocity";	// RVA 0x0086C250
extern const char *const CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME = "Cylindrical Emission Velocity";	// RVA 0x0086C254
extern const char *const OUTWARD_EMISSION_VELOCITY_MODULE_KEY = "OutwardEmissionVelocity";	// RVA 0x0086C348
extern const char *const OUTWARD_EMISSION_VELOCITY_MODULE_NAME = "Outward Emission Velocity";	// RVA 0x0086C34C
extern const char *const STREAK_DRAW_MODULE_KEY = "StreakDraw";	// RVA 0x0086C540
extern const char *const STREAK_DRAW_MODULE_NAME = "Streak Draw";	// RVA 0x0086C544
extern const char *const QUAD_DRAW_MODULE_KEY = "QuadDraw";	// RVA 0x0086C560
extern const char *const QUAD_DRAW_MODULE_NAME = "Quad Draw";	// RVA 0x0086C564
extern const char *const BUTTERFLY_DRAW_MODULE_KEY = "ButterflyDraw";	// RVA 0x0086C580
extern const char *const BUTTERFLY_DRAW_MODULE_NAME = "Butterfly Draw";	// RVA 0x0086C584
extern const char *const LIGHTNING_DRAW_MODULE_KEY = "LightningDraw";	// RVA 0x0086C5B0
extern const char *const LIGHTNING_DRAW_MODULE_NAME = "Lightning Draw";	// RVA 0x0086C5B4
extern const char *const RENDEROBJECT_UPDATE_MODULE_KEY = "RenderObjectUpdate";	// RVA 0x0086C668
extern const char *const RENDEROBJECT_UPDATE_MODULE_NAME = "RenderObject Update";	// RVA 0x0086C66C
extern const char *const RENDEROBJECT_DRAW_MODULE_KEY = "RenderObjectDraw";	// RVA 0x0086C7F4
extern const char *const RENDEROBJECT_DRAW_MODULE_NAME = "RenderObject Draw";	// RVA 0x0086C7F8
extern const char *const GPU_DRAW_MODULE_KEY = "GpuDraw";	// RVA 0x0086C9E8
extern const char *const GPU_DRAW_MODULE_NAME = "Gpu Draw";	// RVA 0x0086C9EC
extern const char *const LIFE_EVENT_MODULE_KEY = "LifeEvent";	// RVA 0x0086CA70
extern const char *const LIFE_EVENT_MODULE_NAME = "Life Event";	// RVA 0x0086CA74
extern const char *const TERRAIN_COLLISION_MODULE_KEY = "TerrainCollision";	// RVA 0x0086CB14
extern const char *const TERRAIN_COLLISION_MODULE_NAME = "Terrain Collision";	// RVA 0x0086CB18
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY = "HemisphericalEmissionVelocity";	// RVA 0x0086CBC8
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME = "Hemispherical Emission Velocity";	// RVA 0x0086CBCC
}

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

#define FX_PARTICLE_PARSE(CLASS, TABLE)                                       \
void CLASS::parse(INI *ini)                                                  \
{                                                                            \
    ini->initFromINI(this, reinterpret_cast<const FieldParse *>(TABLE));     \
}

#define FX_PARTICLE_PARSER(CLASS, TABLE)                                      \
class CLASS                                                                  \
{                                                                            \
public:                                                                      \
    void parse(INI *ini);                                                    \
};                                                                           \
FX_PARTICLE_PARSE(CLASS, TABLE)

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
FX_PARTICLE_PARSE(LifeEventModuleTemplate, g_00C6CAC0)
FX_PARTICLE_PARSE(TerrainCollisionModuleTemplate, g_00C6CB68)
FX_PARTICLE_PARSER(TerrainFireEmissionModuleTemplate, g_00C6C128)
FX_PARTICLE_PARSER(GpuDrawModuleTemplate, g_00C6CA20)

#undef FX_PARTICLE_PARSER
#undef FX_PARTICLE_PARSE
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
