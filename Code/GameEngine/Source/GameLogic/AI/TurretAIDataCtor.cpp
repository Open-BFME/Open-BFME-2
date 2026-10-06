// cl: /DNDEBUG /MD
//
// ?TurretAIData ctor, retail 0x004D7E6C, 141B.
// TurretAIData nullary ctor: turn/pitch defaults, 6-wide sweep/speed loop,
// zeroed pitch/idle/ground, 9999999 intervals, weaponSlots 0,
// recenter = LogicFramesPerSecond*2 (=10), flags 0, PI deflections.
//
// Identity/layout/provenance (target evidence, not bytes alone):
// - Boundary [0x4D7E6C,0x4D7EF9) 141B single ret C3; pred ends C3, succ
//   0x4D7EF9 is rowed parseTWS (61B). Disassembled in-lane via pefile+capstone.
// - Layout 0x70 proven by FieldParse table 0x00C60B90 (20 rec, dumped in
//   TurretAIParseSweep.cpp) + retail lea/loop: turnRate +0, pitchRate +4,
//   naturalAngle +8, naturalPitch +0xC, sweep[6] +0x10, speed[6] +0x28,
//   firePitch +0x40, minPitch +0x44, groundUnitPitch +0x48, weaponSlots +0x4C,
//   minIdleScanAngle +0x50, maxIdleScanAngle +0x54, minInterval +0x58,
//   maxInterval +0x5C, recenter +0x60, initiallyDisabled +0x64,
//   firesWhileTurning +0x65, allowsPitch +0x66, maxDeflCW +0x68, maxDeflACW +0x6C.
//   Array width 6 proven by ctor loop push 6 / pop edx at 0x8D7E82/0x8D7E91
//   storing 0.0f at [ecx-0x18] and 1.0f at [ecx] from eax+0x28.
// - ABI: thiscall nullary ret C3, frameless (mov eax,ecx, no ebp frame).
// - Reference-first: BFME1 TurretAI.cpp:202-224 TurretAIData ctor at 6583b3c1
//   (turn/pitch 0.01f, 0.0 naturals, WEAPONSLOT_COUNT+1 loop, zero pitch,
//   9999999 intervals, recenter 10, false flags) is donor shape; same-name
//   hit does not prove identity, table+loop+stores do. BFME2 deltas
//   (evidence-backed): WEAPONSLOT_COUNT 5->6 wide (retail loop 6, 5 names
//   +NULL at 0xDBC284), recenter via LogicFramesPerSecond*2 (retail
//   mov ecx,[0xDBA4E4=5] + add ecx,ecx), maxDeflCW/ACW = PI (retail
//   movss xmm0,[0xBC7468=3.1415927f], 72 image refs), groundUnitPitch single
//   store ordered after idle angles per retail 40,44,50,54,48 sequence.
// - Providers: DEFAULT 0.01f unique (1 image ref, TU-local literal),
//   1.0f shared (1927 refs, literal folds), PI shared (72 refs, literal),
//   LogicFramesPerSecond int 5 at 0xDBA4E4 (365 refs, extern g_Va00DBA4E4).
//   No calls, no pins; DIR32 slots patched per docs/matching.md.
// - Flags from AI SSE siblings (/O1 /DNDEBUG /MD /arch:SSE); /O1 gives
//   push-6 size loop. Donor rev 6583b3c1 reused read-only, no fetch.

// Retained native FieldParse evidence (VA0xC60B90;20x16B records):
// idx0 TurnRate off0 parserVA7389DD;idx1 PitchRate off4 sameparser;
// idx2 NaturalAngle off8;idx3 NaturalPitch off12;idx4 FirePitch off64;
// idx5 MinPhysicalPitch off68;idx6 GroundPitch off72;
// idx7 Sweep procVA8D7F36 off0;idx8 Speed procVA8D7F69 off0;
// idx9 ControlledWeaponSlots procVA8D7EF9 off76;
// idx10 AllowsPitch off102;idx11/12 IdleAngles off80/84;
// idx13/14 IdleIntervals off88/92;idx15 Recenter off96;
// idx16 InitiallyDisabled off100;idx17 FiresWhileTurning off101;
// idx18/19 DeflectionAngles off104/108;terminatorVA0xC60CD0.
// Names tableVA0xDBC284 bytes:9408c0008808c0007c08c0007008c0006808c00000000000
// gives PRIMARY SECONDARY TERTIARY QUATERNARY QUINARY NULL.
// Native target stores groundUnitPitch once; donor stores it twice.

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

extern int g_Va00DBA4E4;
#define LogicFramesPerSecond g_Va00DBA4E4

enum { WEAPONSLOT_COUNT = 5 };

const Real DEFAULT_TURN_RATE = 0.01f;
const Real DEFAULT_PITCH_RATE = 0.01f;

class TurretAIData
{
public:
	Real m_turnRate; // +0x00
	Real m_pitchRate; // +0x04
	Real m_naturalTurretAngle; // +0x08
	Real m_naturalTurretPitch; // +0x0C
	Real m_turretFireAngleSweep[WEAPONSLOT_COUNT + 1]; // +0x10 (6)
	Real m_turretSweepSpeedModifier[WEAPONSLOT_COUNT + 1]; // +0x28 (6)
	Real m_firePitch; // +0x40
	Real m_minPitch; // +0x44
	Real m_groundUnitPitch; // +0x48
	UnsignedInt m_turretWeaponSlots; // +0x4C
	Real m_minIdleScanAngle; // +0x50
	Real m_maxIdleScanAngle; // +0x54
	UnsignedInt m_minIdleScanInterval; // +0x58
	UnsignedInt m_maxIdleScanInterval; // +0x5C
	UnsignedInt m_recenterTime; // +0x60
	bool m_initiallyDisabled; // +0x64
	bool m_firesWhileTurning; // +0x65
	bool m_isAllowsPitch; // +0x66
	Real m_maxDeflectionCW; // +0x68
	Real m_maxDeflectionACW; // +0x6C
	TurretAIData();
};

// ??0TurretAIData@@QAE@XZ @0x004D7E6C
TurretAIData::TurretAIData()
{
	m_turnRate = DEFAULT_TURN_RATE;
	m_pitchRate = DEFAULT_PITCH_RATE;
	m_naturalTurretAngle = 0.0f;
	m_naturalTurretPitch = 0.0f;
	for (Int slotIndex = 0; slotIndex < WEAPONSLOT_COUNT + 1; ++slotIndex)
	{
		m_turretFireAngleSweep[slotIndex] = 0.0f;
		m_turretSweepSpeedModifier[slotIndex] = 1.0f;
	}
	m_firePitch = 0.0f;
	m_minPitch = 0.0f;
	m_minIdleScanAngle = 0.0f;
	m_maxIdleScanAngle = 0.0f;
	m_groundUnitPitch = 0.0f;
	m_turretWeaponSlots = 0;
	m_minIdleScanInterval = 9999999;
	m_maxIdleScanInterval = 9999999;
	m_recenterTime = LogicFramesPerSecond * 2;
	m_initiallyDisabled = false;
	m_firesWhileTurning = false;
	m_isAllowsPitch = false;
	m_maxDeflectionCW = 3.1415927f;
	m_maxDeflectionACW = 3.1415927f;
}
