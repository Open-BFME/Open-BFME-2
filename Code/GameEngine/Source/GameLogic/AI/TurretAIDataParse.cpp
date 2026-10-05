// cl: /O1 /DNDEBUG /MD
//
// TurretAIData FieldParse procs from Zero Hour's TurretAI.cpp with the BFME 2
// six-slot layout: m_turretFireAngleSweep[6] at +0x10 and
// m_turretSweepSpeedModifier[6] at +0x28 (retail scales the slot index into
// those bases). Target evidence: the TurretAIData FieldParse table maps
// TurretFireAngleSweep (0x00C60C00) -> 0x004D7F36, TurretSweepSpeedModifier
// (0x00C60C10) -> 0x004D7F69 and ControlledWeaponSlots (0x00C60C20, store
// +0x4C) -> 0x004D7EF9. The slot index goes through the member scanIndexList
// (explicit null seps) over the VA 0x00DBC284 slot-name table.

#define NULL 0

typedef float Real;
typedef unsigned int UnsignedInt;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	int scanIndexList(const char *token, const char *const *names);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAngleReal(INI *ini, void *instance, void *store, const void *userData);
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	WEAPONSLOT_COUNT = 6
};

extern const char *TheWeaponSlotTypeNames[];

class TurretAIData
{
public:
	static void parseTurretSweep(INI *ini, void *instance, void *store, const void *userData);
	static void parseTurretSweepSpeed(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_00[0x10];
	Real m_turretFireAngleSweep[WEAPONSLOT_COUNT];		// +0x10
	Real m_turretSweepSpeedModifier[WEAPONSLOT_COUNT];	// +0x28
};

// ?parseTWS@@YAXPAVINI@@PAX1PBX@Z
void parseTWS(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	UnsignedInt *tws = (UnsignedInt *)store;
	const char *token = ini->getNextToken();
	while (token != NULL)
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
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	INI::parseAngleReal(ini, instance, &self->m_turretFireAngleSweep[wslot], NULL);
}

// ?parseTurretSweepSpeed@TurretAIData@@SAXPAVINI@@PAX1PBX@Z
void TurretAIData::parseTurretSweepSpeed(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	TurretAIData *self = (TurretAIData *)instance;
	WeaponSlotType wslot = (WeaponSlotType)ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
	INI::parseReal(ini, instance, &self->m_turretSweepSpeedModifier[wslot], NULL);
}
