// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// ModelConditionInfo FieldParse procs from the W3DModelDraw condition-state
// table at VA 0x00BCAB20 (BFME 2 layout).
//
// ModelConditionInfo::parseRealRange 0x000B2D5E (53B): Zero Hour's
// W3DModelDraw.cpp static for AnimationSpeedFactorRange (0x00BCA5B0), min/max
// speed factors at +0x24/+0x28 (class-scoped here for a unique ledger name).
//
// TurretArtAngle 0x000B6E9E / TurretArtPitch 0x000B6EBE (32B each): BFME 2
// keeps the turrets in a vector (end pointer at +0xD4); the proc parses into
// the last entry's art angle / pitch, which sit at +0x08/+0x0C of Zero Hour's
// 0x18-byte TurretInfo (retail: end - 0x10 / end - 0x0C).
//
// The Shadow* rows (Shadow 0x00BCAC00 builds the sub-record at +0xDC through
// the rowed Rva000B9AFF_ParseShadowEvent) parse into that sub-record: when it
// exists, the store is rebased from the condition info onto it.
//   0x000B2D93 ShadowSizeX/SizeY/OffsetX/OffsetY  parseReal
//   0x000B2DBB ShadowTexture                      parseAsciiString
//   0x000B2DE3 ShadowOverrideLODVisibility        parseBool
// Names of the BFME 2 procs stay address-derived.

#define NULL 0

typedef float Real;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	Real scanReal(const char *token);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseAngleReal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B2D93_ParseShadowReal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B2DBB_ParseShadowAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B2DE3_ParseShadowBool(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B6E9E_ParseTurretArtAngle(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B6EBE_ParseTurretArtPitch(INI *ini, void *instance, void *store, const void *userData);
};

struct TurretInfo
{
	int m_turretAngleNameKey;
	int m_turretPitchNameKey;
	Real m_turretArtAngle;
	Real m_turretArtPitch;
	int m_turretAngleBone;
	int m_turretPitchBone;
};

struct TurretInfoVector
{
	TurretInfo *m_start;
	TurretInfo *m_finish;
	TurretInfo *m_endOfStorage;
	TurretInfo &back() { return *(m_finish - 1); }
};

class ModelConditionInfo
{
public:
	static void parseRealRange(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_00[0x24];
	Real m_animMinSpeedFactor;			// +0x24
	Real m_animMaxSpeedFactor;			// +0x28
	unsigned char m_unreconstructed_2C[0xD0 - 0x2C];
	TurretInfoVector m_turrets;			// +0xD0
	void *m_unreconstructed_DC;			// +0xDC shadow sub-record
};

// ?parseRealRange@ModelConditionInfo@@SAXPAVINI@@PAX1PBX@Z
void ModelConditionInfo::parseRealRange(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;

	const char *token = ini->getNextToken();
	self->m_animMinSpeedFactor = ini->scanReal(token);
	token = ini->getNextToken();
	self->m_animMaxSpeedFactor = ini->scanReal(token);
}

// ?Rva000B2D93_ParseShadowReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva000B2D93_ParseShadowReal(INI *ini, void *instance, void *store, const void *userData)
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	if (self->m_unreconstructed_DC)
		INI::parseReal(ini, NULL, (char *)store + ((char *)self->m_unreconstructed_DC - (char *)self), userData);
}

// ?Rva000B2DBB_ParseShadowAsciiString@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva000B2DBB_ParseShadowAsciiString(INI *ini, void *instance, void *store, const void *userData)
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	if (self->m_unreconstructed_DC)
		INI::parseAsciiString(ini, NULL, (char *)store + ((char *)self->m_unreconstructed_DC - (char *)self), userData);
}

// ?Rva000B2DE3_ParseShadowBool@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva000B2DE3_ParseShadowBool(INI *ini, void *instance, void *store, const void *userData)
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	if (self->m_unreconstructed_DC)
		INI::parseBool(ini, NULL, (char *)store + ((char *)self->m_unreconstructed_DC - (char *)self), userData);
}

// ?Rva000B6E9E_ParseTurretArtAngle@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva000B6E9E_ParseTurretArtAngle(INI *ini, void *instance, void * /*store*/, const void *userData)
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	INI::parseAngleReal(ini, instance, &self->m_turrets.back().m_turretArtAngle, userData);
}

// ?Rva000B6EBE_ParseTurretArtPitch@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva000B6EBE_ParseTurretArtPitch(INI *ini, void *instance, void * /*store*/, const void *userData)
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	INI::parseAngleReal(ini, instance, &self->m_turrets.back().m_turretArtPitch, userData);
}
