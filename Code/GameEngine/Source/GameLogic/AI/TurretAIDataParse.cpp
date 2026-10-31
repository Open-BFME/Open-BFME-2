// cl: /DNDEBUG /MD
// platformsdk
//
// TurretAIData FieldParse procs from Zero Hour's TurretAI.cpp with the BFME 2
// six-slot layout: m_turretFireAngleSweep[6] at +0x10 and
// m_turretSweepSpeedModifier[6] at +0x28 (retail scales the slot index into
// those bases). Target evidence: the TurretAIData FieldParse table maps
// TurretFireAngleSweep (0x00C60C00) -> 0x004D7F36, TurretSweepSpeedModifier
// (0x00C60C10) -> 0x004D7F69 and ControlledWeaponSlots (0x00C60C20, store
// +0x4C) -> 0x004D7EF9. The slot index goes through the member scanIndexList
// (explicit null seps) over the VA 0x00DBC284 slot-name table.
//
// TurretAIData::buildFieldParse 0x004D7F9C (17B) adds the TurretAIData table
// at VA 0x00C60B90; AIUpdateModuleData::parseTurret hands it to
// initFromINIMultiProc.

typedef float Real;
typedef unsigned int UnsignedInt;

class INI;

struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	int scanIndexList(const char *token, const char *const *names);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAngleReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAngularVelocityReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};


extern const FieldParse g_00C60B90[];
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_COUNT = 6
};

extern const char *TheWeaponSlotTypeNames[];

class TurretAIData
{
public:
	static void parseTurretSweep(INI *ini, void *instance, void *store, const void *userData);
	static void parseTurretSweepSpeed(INI *ini, void *instance, void *store, const void *userData);
	static void buildFieldParse(MultiIniFieldParse &p);

	Real m_turnRate;									// +0x00
	Real m_pitchRate;									// +0x04
	Real m_naturalTurretAngle;							// +0x08
	Real m_naturalTurretPitch;							// +0x0C
	Real m_turretFireAngleSweep[WEAPONSLOT_COUNT];		// +0x10
	Real m_turretSweepSpeedModifier[WEAPONSLOT_COUNT];	// +0x28
};

// ?parseTWS@@YAXPAVINI@@PAX1PBX@Z
void parseTWS(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	UnsignedInt *tws = (UnsignedInt *)store;
	const char *token = ini->getNextToken();
	while (token != 0)
	{
		WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(token, TheWeaponSlotTypeNames);
		*tws |= (1 << wslot);
		token = ini->getNextTokenOrNull();
	}
}

// ?parseTurretSweep@TurretAIData@@SAXPAVINI@@PAX1PBX@Z
void TurretAIData::parseTurretSweep(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	TurretAIData *self = (TurretAIData *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(0), TheWeaponSlotTypeNames);
	INI::parseAngleReal(ini, instance, &self->m_turretFireAngleSweep[wslot], 0);
}

// ?parseTurretSweepSpeed@TurretAIData@@SAXPAVINI@@PAX1PBX@Z
void TurretAIData::parseTurretSweepSpeed(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	TurretAIData *self = (TurretAIData *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(0), TheWeaponSlotTypeNames);
	INI::parseReal(ini, instance, &self->m_turretSweepSpeedModifier[wslot], 0);
}

// The extra field parsers retail's TurretAIData table reaches on top of the ones
// this unit already declares, each an already-rowed body:
// INI::parseAngularVelocityReal (0x003389DD), INI::parseDurationUnsignedInt
// (0x00338B30), INI::parseBool (0x0002E850) and the free parseTWS (0x004D7EF9).
// Declared with the real INI* first argument so the table entries bind to those
// rowed symbols rather than a second spelling of them.
void parseTWS(INI *ini, void *instance, void *store, const void *userData);

// Retail VA 0x00C60B90 (.rdata, file offset 0x0085FB90): TurretAIData's twenty
// field records and the zero terminator, 336 bytes - the ledger's own bound for
// the table. The two rates and the two natural angles occupy the 0x10-byte head,
// the six-slot arrays at +0x10 / +0x28 are written through their slot-index
// parsers (offset 0; they scale the parsed slot index themselves, per the layout
// note above), and ControlledWeaponSlots lands on +0x4C immediately after those
// two arrays, with the remaining 0x50..0x70 span the idle-scan, recenter and
// deflection fields. Every parse target is a rowed, byte-matched body.
// Symbol ?g_00C60B90@@3QBUFieldParse@@B, transcribed below.
extern const FieldParse g_00C60B90[] =
{
	{ "TurretTurnRate",            &INI::parseAngularVelocityReal,        0, 0x00 },
	{ "TurretPitchRate",           &INI::parseAngularVelocityReal,        0, 0x04 },
	{ "NaturalTurretAngle",        &INI::parseAngleReal,                  0, 0x08 },
	{ "NaturalTurretPitch",        &INI::parseAngleReal,                  0, 0x0C },
	{ "FirePitch",                 &INI::parseAngleReal,                  0, 0x40 },
	{ "MinPhysicalPitch",          &INI::parseAngleReal,                  0, 0x44 },
	{ "GroundUnitPitch",           &INI::parseAngleReal,                  0, 0x48 },
	{ "TurretFireAngleSweep",      &TurretAIData::parseTurretSweep,       0, 0x00 },
	{ "TurretSweepSpeedModifier",  &TurretAIData::parseTurretSweepSpeed,  0, 0x00 },
	{ "ControlledWeaponSlots",     &parseTWS,                             0, 0x4C },
	{ "AllowsPitch",               &INI::parseBool,                       0, 0x66 },
	{ "MinIdleScanAngle",          &INI::parseAngleReal,                  0, 0x50 },
	{ "MaxIdleScanAngle",          &INI::parseAngleReal,                  0, 0x54 },
	{ "MinIdleScanInterval",       &INI::parseDurationUnsignedInt,        0, 0x58 },
	{ "MaxIdleScanInterval",       &INI::parseDurationUnsignedInt,        0, 0x5C },
	{ "RecenterTime",              &INI::parseDurationUnsignedInt,        0, 0x60 },
	{ "InitiallyDisabled",         &INI::parseBool,                       0, 0x64 },
	{ "FiresWhileTurning",         &INI::parseBool,                       0, 0x65 },
	{ "TurretMaxDeflectionCW",     &INI::parseAngleReal,                  0, 0x68 },
	{ "TurretMaxDeflectionACW",    &INI::parseAngleReal,                  0, 0x6C },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@TurretAIData@@SAXAAVMultiIniFieldParse@@@Z
void TurretAIData::buildFieldParse(MultiIniFieldParse &multiIniFieldParse)
{
	multiIniFieldParse.add(g_00C60B90, 0);
}
