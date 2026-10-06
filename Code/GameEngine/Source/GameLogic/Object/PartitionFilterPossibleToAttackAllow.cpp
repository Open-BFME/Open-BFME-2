// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// ?allow@PartitionFilterPossibleToAttack@@UAE_NPAVObject@@@Z RVA 0x00260FD0 37B.
// Evidence: retail pushes [ecx+0xc] then arg then [ecx+0x10] with this=[ecx+8]
// into 3-arg getAbleToAttackSpecificObject pin at 0x0028D051; caller 0x00350E4F
// builds vtable 0x7F91B0 with +8=source +0xc=2 +0x10=0; BFME1 donor
// PartitionManager.cpp BfmePossibleToAttackFilter; BFME2 base is 8B so +8/+0xc/+0x10.
typedef bool Bool;

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

class Object
{
public:
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType t, const Object *target, CommandSourceType commandSource) const;
};

class PartitionFilterPossibleToAttack
{
public:
	virtual Bool allow(Object *objOther);
private:
	int m_pad04;
	const Object *m_obj;
	CommandSourceType m_commandSource;
	AbleToAttackType m_attackType;
};

Bool PartitionFilterPossibleToAttack::allow(Object *objOther)
{
	CanAttackResult result = m_obj->getAbleToAttackSpecificObject(m_attackType, objOther, m_commandSource);
	if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
	{
		return true;
	}
	return false;
}
