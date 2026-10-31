// cl: /MD
// ?setState@TurretStateMachine@@UAE?AW4StateReturnType@@H@Z, retail 0x004D8578, 62 bytes.
// Virtual slot 8 (offset 0x20) of vtable 0x008609C8 (VA 0x00C609C8), class
// TurretStateMachine (slot 2 returns "TurretStateMachine" at 0x00860A08).
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp
// TurretStateMachine::setState verbatim plus BFME2 layout deltas: current-state
// pointer at +0x04 (StateMachine base), StateID at State+0x04, TurretAI owner at
// +0x3C, friend_notifyStateMachineChanged inlined as m_sleepUntil (+0x34) =
// TheGameLogic->getFrame ([0x00DFE78C]+0x40). Single callee setState 0x004D7ACD
// already rowed in StateMachineGoal.cpp.

#include "../../Include/Common/StateMachine.h"
#include "GameLogicObjectLookupView.h"

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
class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	bool chooseBestWeaponForTarget(const Object *target, WeaponChoiceCriteria criteria, CommandSourceType cmdSource);
	// Retail inlines this +0x258 load; suppress the surplus external copy.
	__declspec(dllimport) __forceinline AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	AIUpdateInterface *getAI() const { return m_ai; }
	int getID() const { return m_id; }
	bool isEffectivelyDead() const { return (m_deadByte & 1) != 0; }
	Team *getTeam() const { return m_team; }
	char m_pad00[0x74];
	int m_id;							// +0x74
	char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai;			// +0x258
	char m_pad25C[0x304 - 0x25C];
	Team *m_team;						// +0x304
	char m_pad308[0x438 - 0x308];
	unsigned char m_deadByte;			// +0x438
};

// TurretAIData, 0x70 bytes as TurretAIData::TurretAIData (0x004D7E6C) fills it.
class TurretAIData
{
public:
	TurretAIData();
	float m_turnRate;									// +0x00
	float m_pitchRate;									// +0x04
	float m_naturalTurretAngle;							// +0x08
	float m_naturalTurretPitch;							// +0x0C
	float m_turretFireAngleSweep[WEAPONSLOT_COUNT];		// +0x10
	float m_turretSweepSpeedModifier[WEAPONSLOT_COUNT];	// +0x28
	float m_firePitch;									// +0x40
	float m_minPitch;									// +0x44
	float m_groundUnitPitch;							// +0x48
	unsigned int m_turretWeaponSlots;					// +0x4C
	float m_minIdleScanAngle;							// +0x50
	float m_maxIdleScanAngle;							// +0x54
	unsigned int m_minIdleScanInterval;					// +0x58
	unsigned int m_maxIdleScanInterval;					// +0x5C
	unsigned int m_recenterTime;						// +0x60
	bool m_initiallyDisabled;							// +0x64
	bool m_firesWhileTurning;							// +0x65
	bool m_isAllowsPitch;								// +0x66
	float m_maxDeflectionCW;							// +0x68
	float m_maxDeflectionACW;							// +0x6C
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
class StateMachine : public Snapshot
{
public:
	virtual ~StateMachine();
	virtual StateReturnType updateStateMachine();		// slot 4
	virtual void clear();								// slot 5
	virtual StateReturnType resetToDefaultState();		// slot 6
	virtual StateReturnType initDefaultState();			// slot 7
	virtual StateReturnType setState(int newStateID);	// slot 8
	virtual void slot9();
	virtual void slot10();
	virtual bool isInAttackState() const;				// slot 11
	virtual bool isInBusyState() const;					// slot 12
	virtual void rva004D7395();							// slot 13
	virtual void setGoalObject(Object *obj);			// slot 14
	void setGoalPosition(const Coord3D *pos);
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
public:
	State *m_currentState;								// +0x04
	char m_pad08[0x3C - 0x08];
};

// The 0x40-byte turret machine (vtable 0x00C609C8); getGoalObject is 0x004D7726.
class TurretStateMachine : public StateMachine
{
public:
	TurretStateMachine(TurretAI *tai, Object *obj, unsigned int nameKey);
	virtual ~TurretStateMachine();
	virtual void clear();								// slot 5
	virtual StateReturnType resetToDefaultState();		// slot 6
	virtual StateReturnType setState(int newStateID);	// slot 8
	Object *getGoalObject();
	int getCurrentStateID() const;					// current state's id, else INVALID_STATE_ID
	TurretAI *m_turretAI;								// +0x3C
};

class TurretAINotifyBase
{
public:
	virtual void notifyFired() = 0;
	virtual void notifyNewVictimChosen(Object *victim) = 0;
};

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
	void friend_notifyStateMachineChanged() { m_sleepUntil = TheGameLogic->getFrame(); }
	float getNaturalTurretAngle() const { return m_data->m_naturalTurretAngle; }
	float getNaturalTurretPitch() const { return m_data->m_naturalTurretPitch; }
protected:
	virtual void xfer(Xfer *xfer);
private:
	void removeSelfAsTargeter();
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
	int m_continuousFireExpirationFrame;		// +0x30
	unsigned int m_sleepUntil;					// +0x34
	bool m_playRotSound;						// +0x38
	bool m_playPitchSound;						// +0x39
	bool m_positiveSweep;						// +0x3A
	bool m_didFire;								// +0x3B
	bool m_enabled;								// +0x3C
	bool m_firesWhileTurning;					// +0x3D
	bool m_isForceAttacking;					// +0x3E
	bool m_targetWasSetByIdleMood;				// +0x3F
};
// End of the TurretAI.cpp TU view.

StateReturnType TurretStateMachine::setState(int newStateID)
{
	State *current = m_currentState;
	int oldID = current ? current->m_id : INVALID_STATE_ID;
	StateReturnType tmp = StateMachine::setState(newStateID);
	TurretAI *turret = m_turretAI;
	if (turret && oldID != newStateID)
		turret->friend_notifyStateMachineChanged();
	return tmp;
}

// ?resetToDefaultState@TurretStateMachine@@UAE?AW4StateReturnType@@XZ @0x004D855B 29B
// Retail vtable slot 6 (offset 0x18) of vtable 0x008609C8, class TurretStateMachine.
// BFME1 donor TurretAI.cpp resetToDefaultState verbatim plus BFME2 deltas (owner at
// +0x3C, notify inlined as m_sleepUntil (+0x34) = frame). Single callee reset 0x004D7A75.
StateReturnType TurretStateMachine::resetToDefaultState()
{
	StateReturnType tmp = StateMachine::resetToDefaultState();
	TurretAI *turret = m_turretAI;
	if (turret)
		turret->friend_notifyStateMachineChanged();
	return tmp;
}

// ?clear@TurretStateMachine@@UAEXXZ @0x004D853F 28B
// Retail vtable slot 5 (offset 0x14) of vtable 0x008609C8, class TurretStateMachine.
// BFME1 donor TurretAI.cpp clear verbatim plus BFME2 deltas (owner +0x3C, notify).
// Single callee clear 0x004D72C5 rowed in StateMachineGoal.cpp.
void TurretStateMachine::clear()
{
	StateMachine::clear();
	TurretAI *turret = m_turretAI;
	if (turret)
		turret->friend_notifyStateMachineChanged();
}
