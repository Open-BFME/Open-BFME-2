// cl: /DNDEBUG /MD
//
// ?isWeaponSlotOnTurret@TurretAI@@QBE_NW4WeaponSlotType@@@Z,
// retail 0x004D81D7, 21 bytes. Dedicated TU.
// Single-mask test: the data at +8 carries the allowed-slot mask at +0x4C;
// the neg/sbb/neg tail is MSVC's bool normalization of the masked test.

typedef bool Bool;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_COUNT = 6
};

enum TurretStateType
{
	TURRETAI_IDLE,
	TURRETAI_IDLESCAN,
	TURRETAI_AIM,
	TURRETAI_FIRE,
	TURRETAI_RECENTER,
	TURRETAI_HOLD,
	NUM_TURRETAI_STATES
};

struct TurretStateMachine
{
	virtual void m_v0();
	virtual void m_v1();
	virtual void m_v2();
	virtual void m_v3();
	virtual void m_v4();
	virtual void m_v5();
	virtual void m_v6();
	virtual void m_v7();
	virtual void setState(int state);
};

struct TurretData
{
	char m_pad[8];
	float m_naturalAngle;
	float m_naturalPitch;
	char m_pad2[0x4C - 0x10];
	unsigned m_slotMask;
};

class GameLogic
{
	char m_pad[0x40];
	unsigned m_frame;

public:
	unsigned getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

class TurretAI
{
	char m_pad[8];
	TurretData *m_data;
	char m_gap[8];
	TurretStateMachine *m_stateMachine;
	float m_angle;
	float m_pitch;
	char m_gap2[0x34 - 0x20];
	unsigned m_sleepUntil;
	char m_gap3[4];
	Bool m_enabled;

public:
	Bool isWeaponSlotOnTurret(WeaponSlotType wslot) const;
	void recenterTurret();
	void setTurretEnabled(Bool enabled);
	Bool isTurretInNaturalPosition() const;
};

// ?isWeaponSlotOnTurret@TurretAI@@QBE_NW4WeaponSlotType@@@Z
Bool TurretAI::isWeaponSlotOnTurret(WeaponSlotType wslot) const
{
	return (m_data->m_slotMask & (1 << wslot)) != 0;
}

// ?recenterTurret@TurretAI@@QAEXXZ, retail 0x004D8298, 11 bytes.
// The state machine lives at +0x14; setState is vtable slot 8 and
// TURRETAI_RECENTER is 4, matching the push-4 plus call-[eax+0x20] shape.
void TurretAI::recenterTurret()
{
	m_stateMachine->setState(TURRETAI_RECENTER);
}

// ?setTurretEnabled@TurretAI@@QAEX_N@Z, retail 0x004D82D6, 32 bytes.
// Verbatim ZH logic: on the disabled-to-enabled transition, wake up by
// stamping m_sleepUntil (+0x34) with TheGameLogic->getFrame() (inlined
// [edx+0x40] read); m_enabled lives at +0x3C.
void TurretAI::setTurretEnabled(Bool enabled)
{
	if (enabled && !m_enabled)
	{
		m_sleepUntil = TheGameLogic->getFrame();
	}
	m_enabled = enabled;
}

// ?isTurretInNaturalPosition@TurretAI@@QBE_NXZ, retail 0x004D82A3, 39 bytes.
// BFME2 dropped ZH's under-construction early-out; the body is a pure
// SSE float comparison of the data natural angle/pitch (+8/+0xC) against
// the live angle/pitch (+0x18/+0x1C). The &&-returns-true spelling emits
// retail's jp-false block order via the ucomiss parity trick.
Bool TurretAI::isTurretInNaturalPosition() const
{
	if (m_data->m_naturalAngle == m_angle && m_data->m_naturalPitch == m_pitch)
	{
		return true;
	}
	return false;
}
