// cl: /O1 /G7 /DNDEBUG /MD
// ?getMoodMatrixValue@AIUpdateInterface@@QBEIXZ @0x00264F5E 154B (Ghidra
// FUN_00664f5e): the Zero Hour AIUpdate.cpp body at the pinned address, with
// BFME 2's sixth attitude (-3) mapped to 0x2000; attitude read via the
// out-of-line getter 0x00264EB6, state machine +0x30, valid locomotor
// surfaces +0x1dc, main turret AI +0x20c, Player type +0x5c.
// ?getMoodMatrixActionAdjustment@AIUpdateInterface@@QBEIW4MoodMatrixAction@@@Z @0x00264FF8 331B. BFME1 donor game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_getMoodMatrixActionAdjustment.cpp plus ZH AIUpdate.cpp. Retail kindof at +0x108 (+0x10c word1) direct without override walk. Evidence: pin getMoodMatrixValue 0x00264F5E plus caller TurretAI friend_checkForIdleMoodTarget 0x004D88BE plus donor enums.
typedef unsigned int UnsignedInt;

enum KindOfType
{
	KINDOF_INFANTRY = 8,
	KINDOF_IGNORED_IN_GUI = 47
};

class BfmeThingTemplate
{
public:
	unsigned char m_pad00[0x108];
	UnsignedInt m_kindof[6];
};

class Player
{
public:
	int getPlayerType() const { return m_playerType; }
private:
	unsigned char m_pad00[0x5c];
	int m_playerType;
};

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool isKindOf(KindOfType kind) const
	{
		return (m_template->m_kindof[(UnsignedInt)kind >> 5] & (1UL << ((UnsignedInt)kind & 31))) != 0;
	}
	void *m_vtable;
	BfmeThingTemplate *m_template;
};

enum MoodMatrixAction
{
	MM_Action_Idle,
	MM_Action_Move,
	MM_Action_Attack,
	MM_Action_AttackMove
};

enum MoodMatrixParameter
{
	MM_Controller_Player = 0x00000001,
	MM_Controller_AI = 0x00000002,
	MM_UnitType_NonTurreted = 0x00000010,
	MM_UnitType_Turreted = 0x00000020,
	MM_UnitType_Air = 0x00000040,
	MM_Mood_Sleep = 0x00000100,
	MM_Mood_Passive = 0x00000200,
	MM_Mood_Normal = 0x00000400,
	MM_Mood_Alert = 0x00000800,
	MM_Mood_Aggressive = 0x00001000,
	MM_Mood_Unreconstructed = 0x00002000,
	MM_Mood_Bitmask = 0x00001f00
};

enum MoodActionAdjustment
{
	MAA_Action_Ok = 0x00000001,
	MAA_Action_To_Idle = 0x00000002,
	MAA_Action_To_AttackMove = 0x00000004,
	MAA_Affect_Range_IgnoreAll = 0x00000010,
	MAA_Affect_Range_WaitForAttack = 0x00000020,
	MAA_Affect_Range_Alert = 0x00000040,
	MAA_Affect_Range_Aggressive = 0x00000080
};

// BFME 2 adds a sixth attitude below AI_SLEEP; getMoodMatrixValue maps it to
// MM_Mood_Unreconstructed and getMoodMatrixActionAdjustment treats it there.
enum AttitudeType
{
	AI_UNRECONSTRUCTED = -3,
	AI_SLEEP = -2,
	AI_PASSIVE = -1,
	AI_NORMAL = 0,
	AI_ALERT = 1,
	AI_AGGRESSIVE = 2
};

enum LocomotorSurfaceType
{
	LOCOMOTORSURFACE_AIR = 8
};

class StateMachine;
class TurretAI;

class LocomotorSet
{
public:
	int getValidSurfaces() const { return m_validLocomotorSurfaces; }
private:
	int m_validLocomotorSurfaces;
};

class AIUpdateInterface
{
public:
	Object *getObject() const { return m_object; }
	StateMachine *getStateMachine() const { return m_stateMachine; }
	const LocomotorSet &getLocomotorSet() const { return m_locomotorSet; }
	AttitudeType getAttitude() const;
	UnsignedInt getMoodMatrixValue() const;
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	void *m_vtable;
	unsigned char m_pad04[4];
	Object *m_object;
	unsigned char m_pad0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_pad34[0x1DC - 0x34];
	LocomotorSet m_locomotorSet;
	unsigned char m_pad1E0[0x20C - 0x1E0];
	TurretAI *m_turretAI[1];
};

UnsignedInt AIUpdateInterface::getMoodMatrixValue() const
{
	UnsignedInt returnVal = 0;
	// seems like a weird way to get my controlling object, but I don't see another
	if (!getStateMachine())
	{
		return returnVal;
	}

	const Object *owner = getObject();
	Player *player = owner->getControllingPlayer();

	if (!player)
	{
		return returnVal;
	}

	if (player->getPlayerType() == PLAYER_HUMAN)
	{
		returnVal |= MM_Controller_Player;
		// Human units don't have a mood.
	}
	else
	{
		returnVal |= MM_Controller_AI;
		switch (getAttitude())
		{
			case AI_UNRECONSTRUCTED:	returnVal |= MM_Mood_Unreconstructed; break;
			case AI_SLEEP:			returnVal |= MM_Mood_Sleep; break;
			case AI_PASSIVE:		returnVal |= MM_Mood_Passive; break;
			case AI_NORMAL:			returnVal |= MM_Mood_Normal; break;
			case AI_ALERT:			returnVal |= MM_Mood_Alert; break;
			case AI_AGGRESSIVE:	returnVal |= MM_Mood_Aggressive; break;
			default:
				returnVal |= MM_Mood_Normal;
				break;
		}
	}

	if (getLocomotorSet().getValidSurfaces() & LOCOMOTORSURFACE_AIR)
	{
		returnVal |= MM_UnitType_Air;
	}
	else
	{
		if (m_turretAI[0] != 0)
		{
			returnVal |= MM_UnitType_Turreted;
		}
		else
		{
			returnVal |= MM_UnitType_NonTurreted;
		}
	}

	return returnVal;
}

UnsignedInt AIUpdateInterface::getMoodMatrixActionAdjustment(MoodMatrixAction action) const
{
	BfmeThingTemplate *tmpl = getObject()->m_template;
	if ((tmpl->m_kindof[0] & 0x100) != 0 && (tmpl->m_kindof[1] & 0x8000) != 0) {
		return MAA_Action_Ok;
	}
	UnsignedInt moodMatrix = getMoodMatrixValue();
	UnsignedInt returnVal = 0;
	if (moodMatrix & MM_Controller_Player) {
		returnVal = MAA_Action_Ok;
		return returnVal;
	}
	returnVal = MAA_Action_Ok;
	switch (action) {
	case MM_Action_Idle: {
		switch (moodMatrix & MM_Mood_Bitmask) {
		case MM_Mood_Sleep: returnVal = MAA_Action_Ok | MAA_Affect_Range_IgnoreAll; break;
		case MM_Mood_Passive: returnVal = MAA_Action_Ok | MAA_Affect_Range_WaitForAttack; break;
		case MM_Mood_Normal: returnVal = MAA_Action_Ok; break;
		case MM_Mood_Alert: returnVal = MAA_Action_Ok | MAA_Affect_Range_Alert; break;
		case MM_Mood_Aggressive: returnVal = MAA_Action_Ok | MAA_Affect_Range_Aggressive; break;
		}
		break;
	}
	case MM_Action_Move: {
		switch (moodMatrix & MM_Mood_Bitmask) {
		case MM_Mood_Sleep: returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll; break;
		case MM_Mood_Passive: returnVal = MAA_Action_Ok | MAA_Affect_Range_WaitForAttack; break;
		case MM_Mood_Normal: returnVal = MAA_Action_Ok; break;
		case MM_Mood_Alert: returnVal = MAA_Action_To_AttackMove | MAA_Affect_Range_Alert; break;
		case MM_Mood_Aggressive: returnVal = MAA_Action_To_AttackMove | MAA_Affect_Range_Aggressive; break;
		}
		break;
	}
	case MM_Action_Attack: {
		switch (moodMatrix & MM_Mood_Bitmask) {
		case MM_Mood_Sleep: returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll; break;
		case MM_Mood_Passive: returnVal = MAA_Action_Ok; break;
		case MM_Mood_Normal: returnVal = MAA_Action_Ok; break;
		case MM_Mood_Alert: returnVal = MAA_Action_Ok; break;
		case MM_Mood_Aggressive: returnVal = MAA_Action_Ok; break;
		case MM_Mood_Unreconstructed: returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll; break;
		}
		break;
	}
	case MM_Action_AttackMove: {
		switch (moodMatrix & MM_Mood_Bitmask) {
		case MM_Mood_Sleep: returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll; break;
		case MM_Mood_Passive: returnVal = MAA_Action_Ok; break;
		case MM_Mood_Normal: returnVal = MAA_Action_Ok; break;
		case MM_Mood_Alert: returnVal = MAA_Action_Ok | MAA_Affect_Range_Alert; break;
		case MM_Mood_Aggressive: returnVal = MAA_Action_Ok | MAA_Affect_Range_Aggressive; break;
		case MM_Mood_Unreconstructed: returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll; break;
		}
		break;
	}
	}
	return returnVal;
}
