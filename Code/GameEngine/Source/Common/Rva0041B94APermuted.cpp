// cl: /MD
extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier, _ReadWriteBarrier)
#include "../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
// ABI repair: retail 29C823 and named WB DBA3A0 dispatch through TheActionManager.
// The unused manager this is still part of the calling convention. Existing
// return representations are preserved. No additional name or pin is introduced.
//
// ?Rva0041B94AGet@ActionManager@@QAE_NPAVObject@@0H@Z, retail 0x0041b94a, 102 bytes. Banked partial (score 0.96) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Object pair helper via rowed rva002931F5 rva0028C197 and provider slot28.
// Evidence: callees rva002931F5 0x002931F5 row ObjectRva002931F5.cpp rva0028C197 0x0028C197 row ObjectRva0028C197.cpp virtual slot28 at 0x70; callers 0x00264746 0x0029CA25 0x00346177 0x0041D464; prev next GameEngineDeletingBaseDerived.cpp same flags; ret 0xC for three stack arguments; ActionManager this in ECX.
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2,
	RvaRel0 = 0,
	RvaRel1 = 1,
	RvaRelEnemies = 2
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_0 = 0,
	OBJECT_STATUS_1 = 1,
	OBJECT_STATUS_2 = 2
};
enum ObjectID
{
	OBJECTID_INVALID = 0
};
enum SpecialPowerType { SPECIAL_INVALID = 0 };
#include "../../../Libraries/Include/Lib/Coord3D.h"
class ThingTemplate;
class VisIface;
class Team;
class SpawnBehaviorInterface;
class BfmeContainModule;
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;
class Player;
class SpecialAbilityUpdate;
enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE,
	ATTACKRESULT_INVALID_SHOT,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING,
	ATTACKRESULT_POSSIBLE
};
enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0,
	ATTACK_TYPE_FLAG_10 = 0x10
};
class Object
{
public:
	virtual ~Object();
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos38;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	char m_pad78[0x250 - 0x78];
	VisIface *m_vis;
	char m_pad254[0x258 - 0x254];
	int m_258;
	char m_pad25C[0x304 - 0x25C];
	Team *m_team;
	char m_pad308[0x438 - 0x308];
	unsigned char m_flags438; // +0x438 bit0
public:
	bool isEffectivelyDead() const
	{
		return (*(const unsigned char *)((const char *)this + 0x438) & 1) != 0;
	}
public:
	bool testStatus( ObjectStatusTypes bit ) const;
public:
	bool rva002931BA();
public:
	bool isAbleToAttack() const;
public:
	CanAttackResult getAbleToAttackSpecificObject( AbleToAttackType attackType,
		const Object *target, CommandSourceType commandSource ) const;
public:
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
public:
	BfmeContainModule *getContain() const
	{
		return *(BfmeContainModule **)((const char *)this + 0x250);
	}
public:
	Object *rva002931F5(bool checkProducer);
public:
	void *rva0028C1A9() const;
public:
	bool hasSpecialPower(SpecialPowerType type) const;
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *specialPowerTemplate) const;
public:
	void *rva0028BD5D(int i) const;
public:
	Player *getControllingPlayer() const;
	void *rva0028C197() const;
	Relationship getRelationship(const Object *that) const;
	ObjectID getSoleHealingBenefactor() const;
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType type) const;
};
struct Provider28
{
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual bool slot28(Object *other);
};
class GameMessage
{
public:
	enum Type { MSG_ENTER_HINT = 175, MSG_CONTEST_HINT = 176, MSG_TYPE_193 = 193, MSG_TYPE_194 = 194 };
};
enum WeaponSlotType { PRIMARY_WEAPON=0 };
class Rva0041B8D2Obj;
class SpecialPowerTemplate;
struct Coord3D;
class Player;
class DrawableList;
class ActionManager
{
public:
	unsigned char Rva0041B8D2Check(Rva0041B8D2Obj*, Rva0041B8D2Obj*, int);
	CanAttackResult bfmeGetCanAttackContained( const Object *obj, const Object *objectToAttack, CommandSourceType commandSource, AbleToAttackType attackType );
	CanAttackResult getCanAttackObject( const Object *obj, const Object *objectToAttack, CommandSourceType commandSource, AbleToAttackType attackType );
	unsigned char canFireWeapon(const Object*,WeaponSlotType,CommandSourceType);
	unsigned char Rva0041BB87IsRelated(Object*, Object*, int);
	bool canDoSpecialPower(const Object *obj, const SpecialPowerTemplate *spTemplate, CommandSourceType commandSource, unsigned int commandOptions, bool checkSourceRequirements);
	bool rva0041BA61(const Object *obj);
	bool canOverrideSpecialPowerDestination(Object *obj, const Coord3D *pos, int idx, int unused);
	bool rva0041BAD2(const Object*,const Object*,CommandSourceType,WeaponSlotType);
	bool Rva0041B94AGet(Object*, Object*, int);
	bool canResumeConstructionOf(const Object *a, const Object *b, CommandSourceType);
	bool canPlayerGarrison(const Player *player, const Object *obj, CommandSourceType commandSource);
	bool rva0041C9C4(const Object *, const Coord3D *, const SpecialPowerTemplate *);
	bool Rva0041CE27Check(Object *, Object *, int);
	GameMessage::Type getEnterMessage(const Object *obj, const DrawableList *allDraws);
	GameMessage::Type rva0041CE06(const Object *obj);
	bool canDoSpecialPowerAtLocation(const Object *,const Coord3D *,CommandSourceType,const SpecialPowerTemplate *,const Object *,unsigned,bool);
	bool rva0041CC65(const SpecialPowerTemplate *,const Coord3D *);
	bool rva0041CA9E(const Coord3D *,const Coord3D *,const SpecialPowerTemplate *);
	bool rva0041CB10(const Coord3D *,const SpecialPowerTemplate *);
	bool validLocationForCastingOnObjectFilter(const Object *,const Coord3D *,const SpecialPowerTemplate *);
	bool validateLocationForForbiddenObjects(const Object *,const Coord3D *,const SpecialPowerTemplate *);
};

bool ActionManager::Rva0041B94AGet(Object *object, Object *target, int)
{
	if (object == 0 || target == 0)
		return false;
	const Object *aObj = object->rva002931F5(false);
	Object *bObj = target->rva002931F5(false);
	if (aObj == bObj)
		return false;
	if (!(aObj != 0 && bObj == 0))
	{
		const void *contain = bObj->rva0028C197();
		if (contain == 0)
			return false;
		if (((Provider28 *)contain)->slot28(object))
		{
			return true;
			_WriteBarrier();
		}
		_ReadWriteBarrier();
		return false;
	}
	else
	{
		void *contain = aObj->rva0028C197();
		if (contain == 0)
			return false;
		if (((Provider28 *)contain)->slot28(target))
		{
			return true;
			_WriteBarrier();
		}
		_ReadWriteBarrier();
		return false;
	}
}


// ICF twin of Rva0041B94AGet above (identical bytes at 0x0041B94A): the
// BFMEActionManager spelling called by AIUpdateInterfacePrivateCommands and
// ActionManagerSpecialPowerChecks. The manager this and the source argument
// are unused, so the enum/int and const/non-const differences do not reach
// codegen; the const_casts below compile away.
class BFMEActionManager
{
public:
	bool rva000C4080(const Object *a, const Object *b, CommandSourceType commandSource);
};

bool BFMEActionManager::rva000C4080(const Object *obj, const Object *target, CommandSourceType)
{
	if (obj == 0 || target == 0)
		return false;
	const Object *aObj = const_cast<Object *>(obj)->rva002931F5(false);
	Object *bObj = const_cast<Object *>(target)->rva002931F5(false);
	if (aObj == bObj)
		return false;
	if (!(aObj != 0 && bObj == 0))
	{
		const void *contain = bObj->rva0028C197();
		if (contain == 0)
			return false;
		if (((Provider28 *)contain)->slot28(const_cast<Object *>(obj)))
		{
			return true;
			_WriteBarrier();
		}
		_ReadWriteBarrier();
		return false;
	}
	else
	{
		void *contain = const_cast<Object *>(aObj)->rva0028C197();
		if (contain == 0)
			return false;
		if (((Provider28 *)contain)->slot28(const_cast<Object *>(target)))
		{
			return true;
			_WriteBarrier();
		}
		_ReadWriteBarrier();
		return false;
	}
}
