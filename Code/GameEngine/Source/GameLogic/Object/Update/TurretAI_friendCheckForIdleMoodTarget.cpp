// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?friend_checkForIdleMoodTarget@TurretAI@@QAEXXZ, retail 0x004D88AC, 74 bytes.
// Dedicated TU. Zero Hour TurretAI::friend_checkForIdleMoodTarget verbatim:
// owner at +0x10, its AIUpdateInterface at Object +0x258, the idle mood
// adjustment (getMoodMatrixActionAdjustment(MM_Action_Idle) at 0x00264FF8)
// tested against MAA_Affect_Range_IgnoreAll (0x10), getNextMoodTarget(true,
// true), rowed setTurretTargetObject(enemy, FALSE), the owner's
// chooseBestWeaponForTarget (0x0028AF4A, the +0x330 WeaponSet forwarder) and
// the idle-mood flag at +0x3F. BFME 2 passes weapon-choice criterion 5 where
// Zero Hour's PREFER_MOST_DAMAGE is 0; the enum's BFME 2 names are unknown.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum MoodMatrixAction
{
	MM_Action_Idle
};

enum
{
	MAA_Affect_Range_IgnoreAll = 0x00000010
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

class Object;

class AIUpdateInterface
{
public:
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	Bool chooseBestWeaponForTarget(const Object *target, WeaponChoiceCriteria criteria, CommandSourceType cmdSource);

private:
	char m_pad[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

class TurretAI
{
public:
	void friend_checkForIdleMoodTarget();
	void setTurretTargetObject(Object *victim, Bool forceAttacking);

private:
	Object *getOwner() { return m_owner; }

	char m_pad00[0x10];
	Object *m_owner;                // +0x10
	char m_pad14[0x3F - 0x14];
	Bool m_targetWasSetByIdleMood;  // +0x3F
};

void TurretAI::friend_checkForIdleMoodTarget()
{
	Object *obj = getOwner();
	AIUpdateInterface *ai = obj->getAIUpdateInterface();

	UnsignedInt moodAdjust = ai->getMoodMatrixActionAdjustment(MM_Action_Idle);
	if (moodAdjust & MAA_Affect_Range_IgnoreAll)
		return;

	Object *enemy = ai->getNextMoodTarget(true, true);
	if (enemy)
	{
		setTurretTargetObject(enemy, false);
		obj->chooseBestWeaponForTarget(enemy, WEAPON_CHOICE_CRITERIA_5, CMD_FROM_AI);
		m_targetWasSetByIdleMood = true;
	}
}
