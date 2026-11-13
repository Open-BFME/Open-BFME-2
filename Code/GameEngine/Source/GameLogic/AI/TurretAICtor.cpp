// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/iniexception
//
// ??0TurretAI@@QAE@PAVObject@@PBVTurretAIData@@W4WhichTurretType@@@Z retail
// 0x004D85B6..0x004D86B1 (251 bytes EH RET 0x0C). The only caller is at
// 0x0026ED1D. It stores the TurretAI vtables 0x00C60D78 (+0) and 0x00C60D64 (+4)
// that the rowed dtor 0x004D86C1 and deleting dtor 0x004D8974 restore. The
// +4 notify base's own vtable 0x00C078DC is stored first. Retail EH map
// 0x00D43234 has two states: the Snapshot-style base (0x0049B47C) and the
// new-expression cleanup (operator delete).
// Shape follows Zero Hour / Open-BFME-1 TurretAI::TurretAI (donor
// game/GameEngine/Source/GameLogic/AI/TurretAI_ctor_Thunk.cpp at
// 9cbfb551fe20dae985f91f2319d8997287b6a705). Fields are data +8 / turret +0x0C /
// owner +0x10 / machine +0x14 / enabled = !data+0x64 / firesWhileTurning =
// data+0x65 / continuousFireExpirationFrame +0x30 = -1. Retail has no
// sound member and no null-data check. It throws INIException(3 / "TurretAI
// MUST specify controlled weapon slots!") when data+0x4C is zero. The
// natural angle and pitch (data +8/+0xC) are read through Real getters as
// movss. The machine is built with plain new (0x40 bytes / rowed
// TurretStateMachine ctor 0x004D7CE6 with name key 0xA503DF7E) and started
// through its slot 7 (initDefaultState). WB 0x0134FED0 is the same body
// with the debug null-data check and the 0x48-byte machine.
// The base and notify-interface views repeat TurretAIDtor.cpp so both
// units emit identical vtable COMDATs; the class view is the TU's.
// The INIException shim by path, so the unit composes the same beside
// any include order.
#include "../../../../../reference/shims/iniexception/Common/INIException.h"

// The base is the canonical Snapshot (vtable 0x00BBB554): retail unwind
// funclets destroy it through the folded Snapshot destructor 0x0049B47C.
#include "../../../Include/Common/StateMachine.h"
#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// TurretAI.cpp TU view (one spelling in every file of the TU). The
// constructor 0x004D85B6 stores the Snapshot table 0x00BBB554 and then
// 0x00C60D78 at +0x00 and 0x00C60D64 at +0x04. 0x00C60D78 holds the deleting
// destructor 0x004D8974, loadPostProcess 0x004D80D4, the "TurretAI" name
// getter 0x004D86BB and xfer 0x004D7FAD (Snapshot's slots); 0x00C60D64 holds
// notifyFired 0x004D81D2 (+0x37 from the +0x04 base is +0x3B) and
// notifyNewVictimChosen 0x004D8B3F (ecx-4 before setTurretTargetObject).
// Field names follow the constructor, xfer 0x004D7FAD and the target setters.
class Team;
class Object;
class Xfer;
class Weapon;
class AIUpdateInterface;
class TurretAI;
struct Coord3D;
struct EmitVtableTag;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_COUNT = 6
};

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_MAIN = 0,
	TURRET_ALT,
	MAX_TURRETS
};

enum WeaponChoiceCriteria
{
	WEAPON_CHOICE_CRITERIA_5 = 5
};

enum CommandSourceType
{
	CMD_FROM_PLAYER,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

// Object as the TU's bodies read it: id +0x74, AI +0x258, team +0x304 and
// the effectively-dead bit at +0x438.
#include "../Object/object.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// TurretAIData, 0x70 bytes as TurretAIData::TurretAIData (0x004D7E6C) fills it.
class INI;
class MultiIniFieldParse;
class TurretAIData
{
public:
	TurretAIData();
	static void parseTurretSweep(INI *ini, void *instance, void *store, const void *userData);
	static void parseTurretSweepSpeed(INI *ini, void *instance, void *store, const void *userData);
	static void buildFieldParse(MultiIniFieldParse &p);
	float m_turnRate; // +0x00
	float m_pitchRate; // +0x04
	float m_naturalTurretAngle; // +0x08
	float m_naturalTurretPitch; // +0x0C
	float m_turretFireAngleSweep[WEAPONSLOT_COUNT]; // +0x10
	float m_turretSweepSpeedModifier[WEAPONSLOT_COUNT]; // +0x28
	float m_firePitch; // +0x40
	float m_minPitch; // +0x44
	float m_groundUnitPitch; // +0x48
	unsigned int m_turretWeaponSlots; // +0x4C
	float m_minIdleScanAngle; // +0x50
	float m_maxIdleScanAngle; // +0x54
	unsigned int m_minIdleScanInterval; // +0x58
	unsigned int m_maxIdleScanInterval; // +0x5C
	unsigned int m_recenterTime; // +0x60
	bool m_initiallyDisabled; // +0x64
	bool m_firesWhileTurning; // +0x65
	bool m_isAllowsPitch; // +0x66
	char m_pad67[0x1];
	float m_maxDeflectionCW; // +0x68
	float m_maxDeflectionACW; // +0x6C
};

enum TurretStateType
{
	TURRETAI_IDLE = 0,
	TURRETAI_IDLESCAN = 1,
	TURRETAI_AIM = 2,
	TURRETAI_FIRE = 3,
	TURRETAI_RECENTER = 4,
	TURRETAI_HOLD = 5
};

enum { INVALID_STATE_ID = 999999 };

enum TurretTargetType
{
	TARGET_NONE = 0,
	TARGET_OBJECT = 1,
	TARGET_POSITION = 2
};

// StateMachine as the turret machine's table 0x00C609C8 shows it: Snapshot's
// slots 0-3, updateStateMachine 4 (0x004D7321), clear 5, resetToDefaultState
// 6, initDefaultState 7 (0x004D770F), setState 8, isInAttackState 11
// (0x002621B8), isInBusyState 12 (0x004D7309), 13 (0x004D7395) and the goal
// object setter 14; the current state at +0x04. setGoalPosition is 0x00262224.
#include "../../../Include/Common/StateMachineClass.h"

// The 0x40-byte turret machine (vtable 0x00C609C8); getGoalObject is 0x004D7726.
#include "../../../Include/GameLogic/Module/TurretStateMachine.h"

#include "../../../Include/Common/TurretAINotifyBase.h"

class TurretAI : public Snapshot, public TurretAINotifyBase
{
public:
	TurretAI(Object *owner, const TurretAIData *data, WhichTurretType tur);
	TurretAI(EmitVtableTag *);
protected:
	virtual ~TurretAI();
public:
	virtual void loadPostProcess();
	virtual void notifyFired();
	virtual void notifyNewVictimChosen(Object *victim);
	float getTurretFireAngleSweepForWeaponSlot(WeaponSlotType slot) const;
	float getTurretSweepSpeedModifierForWeaponSlot(WeaponSlotType slot) const;
	void setTurretTargetObject(Object *victim, bool forceAttacking);
	void setTurretTargetPosition(const Coord3D *pos);
	bool isOwnersCurWeaponOnTurret() const;
	bool isWeaponSlotOnTurret(WeaponSlotType wslot) const;
	void recenterTurret();
	void setTurretEnabled(bool enabled);
	bool isTurretInNaturalPosition() const;
	void friend_checkForIdleMoodTarget();
	Object *getOwner() const { return m_owner; }
	void rva004D82F6();
	UpdateSleepTime updateTurretAI();
	void friend_notifyStateMachineChanged() { m_sleepUntil = TheGameLogic->getFrame(); }
	float getNaturalTurretAngle() const { return m_data->m_naturalTurretAngle; }
	float getNaturalTurretPitch() const { return m_data->m_naturalTurretPitch; }
protected:
	virtual void xfer(Xfer *xfer);
private:
	void removeSelfAsTargeter();
	void startRotOrPitchSound();
	void stopRotOrPitchSound() { rva004D82F6(); }
	const TurretAIData *m_data;					// +0x08
	WhichTurretType m_whichTurret;				// +0x0C
	Object *m_owner;							// +0x10
	TurretStateMachine *m_turretStateMachine;	// +0x14
	float m_angle;								// +0x18
	float m_pitch;								// +0x1C
	unsigned int m_audio20;						// +0x20
	unsigned int m_enableSweepUntil;			// +0x24
	Team *m_victimInitialTeam;					// +0x28
	int m_target;								// +0x2C
	unsigned int m_continuousFireExpirationFrame;		// +0x30
	unsigned int m_sleepUntil;					// +0x34
	bool m_playRotSound;						// +0x38
	bool m_playPitchSound;						// +0x39
	bool m_positiveSweep;						// +0x3A
	bool m_didFire;								// +0x3B
	bool m_enabled;								// +0x3C
	bool m_firesWhileTurning;					// +0x3D
	bool m_isForceAttacking;					// +0x3E
	bool m_targetWasSetByIdleMood;				// +0x3F
protected:
	virtual const char *GetSnapshotName() const;	// primary slot 2: retail 0x004D86BB
};
// End of the TurretAI.cpp TU view.

TurretAI::TurretAI(Object *owner, const TurretAIData *data, WhichTurretType tur) :
	m_data(data),
	m_whichTurret(tur),
	m_owner(owner),
	m_turretStateMachine(0),
	m_audio20(1),
	m_enableSweepUntil(0),
	m_victimInitialTeam(0),
	m_target(0),
	m_sleepUntil(0),
	m_playRotSound(false),
	m_playPitchSound(false),
	m_positiveSweep(true),
	m_didFire(false),
	m_enabled(!data->m_initiallyDisabled),
	m_firesWhileTurning(data->m_firesWhileTurning),
	m_isForceAttacking(false),
	m_targetWasSetByIdleMood(false)
{
	m_continuousFireExpirationFrame = -1;
	if (m_data->m_turretWeaponSlots == 0)
		throw INIException(3, "TurretAI MUST specify controlled weapon slots!");
	m_angle = getNaturalTurretAngle();
	m_pitch = getNaturalTurretPitch();
	m_turretStateMachine = new TurretStateMachine(this, m_owner, 0xA503DF7E);
	m_turretStateMachine->initDefaultState();
}

// ?notifyFired@TurretAI@@UAEXXZ retail 0x004D81D2 (5B): Zero Hour's
// NotifyWeaponFiredInterface::notifyFired override, m_didFire = TRUE. It is
// slot 0 of the interface vtable 0x00C60D64 the ctor installs at +4, so it
// runs with ECX at that subobject and sets +0x3B through [ecx+0x37].
void TurretAI::notifyFired()
{
	m_didFire = true;
}
