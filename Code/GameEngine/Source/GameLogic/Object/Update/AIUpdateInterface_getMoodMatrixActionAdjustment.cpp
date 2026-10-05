// cl: /O1 /DNDEBUG /MD
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

class BfmeObject
{
public:
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

class AIUpdateInterface
{
public:
	BfmeObject *getObject() const { return m_object; }
	UnsignedInt getMoodMatrixValue() const;
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	void *m_vtable;
	unsigned char m_pad04[4];
	BfmeObject *m_object;
};

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
