// cl: /O1 /DNDEBUG /MD
// stlport
//
// ?setTurretTargetObject@TurretAI@@QAEXPAVObject@@_N@Z, retail 0x004D8791 (151 bytes).
// ?setTurretTargetPosition@TurretAI@@QAEXPBUCoord3D@@@Z, retail 0x004D8828 (132 bytes).
//
// TurretAI target-select pair ported from Open-BFME-1
// Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp (setTurretTargetObject
// + setTurretTargetPosition) with BFME2 divergences: the
// getOwner()->getAI()->areTurretsLinked() gate is GONE (retail nulls the
// target unconditionally when !victim/dead/off-turret); isEffectivelyDead
// and getTeam inline to +0x438-bit0 and +0x304 loads; getCurrentStateID
// inlines to the machine+4 pointer chase with INVALID 999999 fallback.
// Callees isOwnersCurWeaponOnTurret 0x4D8762 and removeSelfAsTargeter
// 0x4D825F are rowed in sibling TUs; state-machine setGoalObject (slot 14)
// and setState (slot 8) are virtual; setGoalPosition 0x262224 is pinned.

class Object;
class Team;
struct Coord3D;

class Object
{
public:
	bool isEffectivelyDead() const { return (m_deadByte & 1) != 0; }
	Team* getTeam() const { return m_team; }
	char m_pad00[0x304];
	Team* m_team;
	char m_pad308[0x438 - 0x308];
	unsigned char m_deadByte;
};

class TurretState
{
public:
	char m_pad00[4];
	int m_id;
};

class TurretStateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(int state);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(Object* obj);
	void setGoalPosition(const Coord3D* pos);
	int getCurrentStateID() const;
	TurretState* m_state;
};

inline int TurretStateMachine::getCurrentStateID() const
{
	if (m_state)
		return m_state->m_id;
	return 999999;
}

enum TurretTargetType
{
	TARGET_NONE = 0,
	TARGET_OBJECT = 1,
	TARGET_POSITION = 2
};

enum TurretStateID
{
	TURRETAI_AIM = 2,
	TURRETAI_FIRE = 3,
	TURRETAI_HOLD = 5
};

class TurretAI
{
	void removeSelfAsTargeter();
public:
	void setTurretTargetObject(Object* victim, bool forceAttacking);
	void setTurretTargetPosition(const struct Coord3D* pos);
	bool isOwnersCurWeaponOnTurret() const;
	char m_pad00[0x10];
	Object* m_owner;
	class TurretStateMachine* m_machine;
	char m_pad18[0x28 - 0x18];
	Team* m_victimInitialTeam;
	int m_target;
	char m_pad30[0x3E - 0x30];
	bool m_isForceAttacking;
	bool m_targetWasSetByIdleMood;
};

struct Coord3D
{
	float m_x;
	float m_y;
	float m_z;
};

void TurretAI::setTurretTargetObject(Object* victim, bool forceAttacking)
{
	if (!victim || victim->isEffectivelyDead() || !isOwnersCurWeaponOnTurret())
		victim = 0;

	if (!victim)
		removeSelfAsTargeter();

	m_machine->setGoalObject(victim);
	m_target = victim ? TARGET_OBJECT : TARGET_NONE;
	m_targetWasSetByIdleMood = false;
	m_isForceAttacking = forceAttacking;

	int sid = m_machine->getCurrentStateID();
	if (victim)
	{
		if (sid != TURRETAI_AIM && sid != TURRETAI_FIRE)
			m_machine->setState(TURRETAI_AIM);
		m_victimInitialTeam = victim->getTeam();
	}
	else
	{
		if (sid == TURRETAI_AIM || sid == TURRETAI_FIRE)
			m_machine->setState(TURRETAI_HOLD);
		m_victimInitialTeam = 0;
	}
}

void TurretAI::setTurretTargetPosition(const Coord3D* pos)
{
	if (!pos || !isOwnersCurWeaponOnTurret())
		pos = 0;

	removeSelfAsTargeter();

	m_machine->setGoalObject(0);
	if (pos)
		m_machine->setGoalPosition(pos);
	m_target = pos ? TARGET_POSITION : TARGET_NONE;
	m_targetWasSetByIdleMood = false;

	int sid = m_machine->getCurrentStateID();
	if (pos)
	{
		if (sid != TURRETAI_AIM && sid != TURRETAI_FIRE)
			m_machine->setState(TURRETAI_AIM);
		m_victimInitialTeam = 0;
	}
	else
	{
		if (sid == TURRETAI_AIM || sid == TURRETAI_FIRE)
			m_machine->setState(TURRETAI_HOLD);
		m_victimInitialTeam = 0;
	}
}
