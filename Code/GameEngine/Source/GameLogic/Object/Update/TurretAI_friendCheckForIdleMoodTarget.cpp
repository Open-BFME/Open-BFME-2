// cl: /DNDEBUG /MD
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
	unsigned int getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	virtual void _slot000();
	virtual void _slot001();
	virtual void _slot002();
	virtual void _slot003();
	virtual void _slot004();
	virtual void _slot005();
	virtual void _slot006();
	virtual void _slot007();
	virtual void _slot008();
	virtual void _slot009();
	virtual void _slot010();
	virtual void _slot011();
	virtual void _slot012();
	virtual void _slot013();
	virtual void _slot014();
	virtual void _slot015();
	virtual void _slot016();
	virtual void _slot017();
	virtual void _slot018();
	virtual void _slot019();
	virtual void _slot020();
	virtual void _slot021();
	virtual void _slot022();
	virtual void _slot023();
	virtual void _slot024();
	virtual void _slot025();
	virtual void _slot026();
	virtual void _slot027();
	virtual void _slot028();
	virtual void _slot029();
	virtual void _slot030();
	virtual void _slot031();
	virtual void _slot032();
	virtual void _slot033();
	virtual void _slot034();
	virtual void _slot035();
	virtual void _slot036();
	virtual void _slot037();
	virtual void _slot038();
	virtual void _slot039();
	virtual void _slot040();
	virtual void _slot041();
	virtual void _slot042();
	virtual void _slot043();
	virtual void _slot044();
	virtual void _slot045();
	virtual void _slot046();
	virtual void _slot047();
	virtual void _slot048();
	virtual void _slot049();
	virtual void _slot050();
	virtual void _slot051();
	virtual void _slot052();
	virtual void _slot053();
	virtual void _slot054();
	virtual void _slot055();
	virtual void _slot056();
	virtual void _slot057();
	virtual void _slot058();
	virtual void _slot059();
	virtual void _slot060();
	virtual void _slot061();
	virtual void _slot062();
	virtual void _slot063();
	virtual void _slot064();
	virtual void _slot065();
	virtual void _slot066();
	virtual void _slot067();
	virtual void _slot068();
	virtual void _slot069();
	virtual void _slot070();
	virtual void _slot071();
	virtual void _slot072();
	virtual void _slot073();
	virtual void _slot074();
	virtual void _slot075();
	virtual void _slot076();
	virtual void _slot077();
	virtual void _slot078();
	virtual void _slot079();
	virtual void _slot080();
	virtual void _slot081();
	virtual void _slot082();
	virtual void _slot083();
	virtual void _slot084();
	virtual void _slot085();
	virtual void _slot086();
	virtual void _slot087();
	virtual void _slot088();
	virtual void _slot089();
	virtual void _slot090();
	virtual void _slot091();
	virtual void _slot092();
	virtual void _slot093();
	virtual void _slot094();
	virtual void _slot095();
	virtual void _slot096();
	virtual void _slot097();
	virtual void _slot098();
	virtual void _slot099();
	virtual void _slot100();
	virtual void _slot101();
	virtual void _slot102();
	virtual void _slot103();
	virtual void _slot104();
	virtual void _slot105();
	virtual void _slot106();
	virtual void _slot107();
	virtual void _slot108();
	virtual void _slot109();
	virtual void _slot110();
	virtual void _slot111();
	virtual void _slot112();
	virtual void _slot113();
	virtual void _slot114();
	virtual void _slot115();
	virtual void _slot116();
	virtual void _slot117();
	virtual void _slot118();
	virtual void _slot119();
	virtual void _slot120();
	virtual void _slot121();
	virtual void _slot122();
	virtual void _slot123();
	virtual void _slot124();
	virtual void _slot125();
	virtual void _slot126();
	virtual void _slot127();
	virtual void _slot128();
	virtual void addTargeter(int id, Bool add);
};

class Object
{
public:
	// Retail inlines this +0x258 load; suppress the surplus external copy.
	__declspec(dllimport) __forceinline AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
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
