// ?getAbleToAttackSpecificObject@WeaponSet@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@1W4CommandSourceType@@@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /Oy- /DNDEBUG /MD /GX- /Oi-
// ?getAbleToAttackSpecificObject@WeaponSet@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@1W4CommandSourceType@@@Z @0x002C83FC 856B
// Evidence: unlock lane; caller 0x0028D14A (Object::getAbleToAttackSpecificObject 0x0028D051) forwards
// attackType/source/victim/commandSource; final forward to pinned WeaponSet::getAbleToUseWeaponAgainstTarget
// 0x002C7907 with victim+0x38; BFME1 donor WeaponSetGetAbleToAttackSpecificObject.cpp (4-arg form).

typedef int Int;
typedef unsigned int UnsignedInt;
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

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_1A = 0x1A,
	OBJECT_STATUS_1B = 0x1B,
	OBJECT_STATUS_25 = 0x25,
	OBJECT_STATUS_33 = 0x33,
	OBJECT_STATUS_3C = 0x3C
};

enum KindOfType
{
	KINDOF_CE = 0xCE
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

struct Coord3D
{
	float x, y, z;
};

class Team;
class Player;
class Object;
class Rva00373EC6;
class Rva002CA9CA;
class WeaponSet;

class Team
{
public:
	Relationship getRelationship(const Team *that) const;
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
	char m_pad00[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);
};

extern PlayerList *ThePlayerList; // ?ThePlayerList@@3PAVPlayerList@@A

class AIInner
{
public:
	char m_pad[0xBC];
	Bool m_flagBC;
};

class AIOuter
{
public:
	char m_pad[0x18];
	AIInner *m_inner18; // +0x18
};

class AI : public AIOuter
{
};

extern AI *TheAI; // ?TheAI@@3PAVAI@@A

class Rva00373EC6
{
public:
	char m_pad[0x38];
	Int m_disguisedPlayerIndex; // +0x38
	Int m_disguised; // +0x3C
};

class Rva002CA9CA
{
public:
	bool rva002CA9CA(int id, const void *arg);
};

class Weapon
{
public:
	char m_pad[4];
	Rva002CA9CA *m_template; // +0x04
};

class ThingTemplate
{
public:
	char m_pad00[0x108];
	unsigned char m_byte108; // +0x108
	char m_pad109[0x10C - 0x109];
	union
	{
		UnsignedInt m_dword10C; // +0x10C
		struct
		{
			char m_sub10C[2];
			unsigned char m_byte10E; // +0x10E
		} m_sub10CBytes;
	};
	union
	{
		UnsignedInt m_dword110; // +0x110
		struct
		{
			char m_sub110[3];
			unsigned char m_byte113; // +0x113
		} m_sub110Bytes;
	};
	char m_pad114[0x119 - 0x114];
	unsigned char m_byte119; // +0x119
	char m_pad11A[0x130 - 0x11A];
	UnsignedInt m_dword130; // +0x130
};

class ContainModuleInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
	virtual void v40(); virtual void v44(); virtual void v48();
	virtual const Player *getApparentControllingPlayer(const Player *observingPlayer) const;
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	Bool rva002943B2(const Player *viewer);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Relationship getRelationship(const Object *that) const;
	Bool isKindOf(KindOfType kind) const;

private:
	void *m_vptr; // +0x00
	ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	char m_pad44[0x94 - 0x44];
	unsigned char m_destroyed94; // +0x94 (low byte of status bits)
	char m_pad95[0x130 - 0x95];
	UnsignedInt m_flags130; // +0x130
	char m_pad134[0x250 - 0x134];
	ContainModuleInterface *m_contain250; // +0x250
	char m_pad254[0x274 - 0x254];
	const Object *m_containedBy274; // +0x274
	char m_pad278[0x304 - 0x278];
	Team *m_team304; // +0x304
	char m_pad308[0x437 - 0x308];
	unsigned char m_scriptStatus437; // +0x437
	unsigned char m_privateStatus438; // +0x438
	unsigned char m_field439; // +0x439
	friend class WeaponSet;
};

class WeaponSet
{
public:
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType, const Object *source, const Object *victim, CommandSourceType commandSource) const;
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *source, const Object *victim, const Coord3D *pos, CommandSourceType commandSource) const;
};

static Bool isForcedAttack(AbleToAttackType t) { return (((Int)t) & 1) != 0; }

// ?getAbleToAttackSpecificObject@WeaponSet@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@1W4CommandSourceType@@@Z @0x002C83FC
CanAttackResult WeaponSet::getAbleToAttackSpecificObject(AbleToAttackType attackType, const Object *source, const Object *victim, CommandSourceType commandSource) const
{
	if (!source ||
		!victim ||
		((source->m_privateStatus438 & 1) != 0) ||
		((victim->m_privateStatus438 & 1) != 0) ||
		((source->m_destroyed94 & 1) != 0) ||
		((victim->m_destroyed94 & 1) != 0) ||
		victim == source)
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus(OBJECT_STATUS_33))
		return ATTACKRESULT_NOT_POSSIBLE;

	Bool sameOwnerForceAttack = ((source->getControllingPlayer() == victim->getControllingPlayer()) && isForcedAttack(attackType));

	Int ignoring = 0;
	if (source->testStatus(OBJECT_STATUS_25))
		ignoring = 1;
	if (victim->m_field439 & ~ignoring)
		return ATTACKRESULT_NOT_POSSIBLE;

	if ((victim->m_template->m_sub10CBytes.m_byte10E & 0x40) != 0)
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus(OBJECT_STATUS_3C))
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus(OBJECT_STATUS_1A) && commandSource == CMD_FROM_AI)
		return ATTACKRESULT_NOT_POSSIBLE;

	Bool allowStealthToPreventAttacks = true;
	if (source->testStatus(OBJECT_STATUS_1B) || sameOwnerForceAttack)
		allowStealthToPreventAttacks = false;
	Bool forced = isForcedAttack(attackType);
	if (forced && ((victim->m_template->m_dword110 & 0x1000000) != 0))
	{
		Rva00373EC6 *update = ((Object *)victim)->rva0028F4BC();
		if (update && update->m_disguised != 0)
			allowStealthToPreventAttacks = false;
	}

	if (allowStealthToPreventAttacks && ((Object *)victim)->rva002943B2(source->getControllingPlayer()))
	{
		if ((victim->m_template->m_dword110 & 0x1000000) == 0)
		{
			return ATTACKRESULT_NOT_POSSIBLE;
		}
		else
		{
			Rva00373EC6 *update = ((Object *)victim)->rva0028F4BC();
			if (update && update->m_disguised != 0)
			{
				Player *ourPlayer = source->getControllingPlayer();
				Player *otherPlayer = ThePlayerList->getNthPlayer(update->m_disguisedPlayerIndex);
				if (ourPlayer && otherPlayer)
				{
					if (ourPlayer->getRelationship(otherPlayer->m_defaultTeam) != ENEMIES)
						return ATTACKRESULT_NOT_POSSIBLE;
				}
			}
		}
	}

	Bool reject = false;
	if ((victim->m_template->m_dword10C & 0x800000) != 0)
	{
		if ((victim->m_template->m_byte108 & 4) != 0)
		{
			if ((source->m_template->m_byte119 & 0x10) != 0)
			{
				if ((source->m_flags130 & 0x2000) != 0)
					reject = true;
			}
			const Weapon *weapon = source->getCurrentWeapon(0);
			if (weapon && weapon->m_template->rva002CA9CA(6, weapon))
				reject = true;
		}
	}

	Relationship r = reject ? ENEMIES : source->getRelationship(victim);

	if ((source->m_template->m_dword10C & 0x800000) != 0)
	{
		if (r == ALLIES)
			return ATTACKRESULT_NOT_POSSIBLE;
		if ((victim->m_template->m_byte108 & 0x80) == 0)
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	if (!(((victim->m_template->m_sub10CBytes.m_byte10E & 4) != 0) && r == NEUTRAL))
	{
		if (((victim->m_template->m_sub110Bytes.m_byte113 & 0x40) != 0) && TheAI->m_inner18->m_flagBC)
			r = ENEMIES;
		if (r != ENEMIES && !forced && !reject && commandSource == CMD_FROM_PLAYER && ((victim->m_scriptStatus437 & 0x10) == 0))
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	const Object *victimsContainer = victim->m_containedBy274;
	ContainModuleInterface *containerContain = victimsContainer ? victimsContainer->m_contain250 : 0;
	if (victim->testStatus(OBJECT_STATUS_3C))
	{
		if (!containerContain ||
			source->m_containedBy274 != victimsContainer ||
			!victim->testStatus(OBJECT_STATUS_25) ||
			!source->testStatus(OBJECT_STATUS_25))
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	if (source->isKindOf(KINDOF_CE))
	{
	}
	else if (!forced)
	{
		ContainModuleInterface *victimContain = victim->m_contain250;
		if (victimContain)
		{
			const Player *victimApparentController = victimContain->getApparentControllingPlayer(source->getControllingPlayer());
			if (victimApparentController)
			{
				Team *defTeam = victimApparentController->m_defaultTeam;
				Team *srcTeam = source->m_team304;
				if (srcTeam->getRelationship(defTeam) != ENEMIES)
				{
					if (commandSource == CMD_FROM_PLAYER && ((victim->m_scriptStatus437 & 0x10) == 0))
						return ATTACKRESULT_NOT_POSSIBLE;
				}
			}
		}
	}

	return getAbleToUseWeaponAgainstTarget(attackType, source, victim, &victim->m_position, commandSource);
}
