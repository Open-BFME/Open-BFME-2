// cl: /MD
#include "../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
// ?canPlayerGarrison@ActionManager@@QAE_NPBVPlayer@@PBVObject@@W4CommandSourceType@@@Z
// @0x0041C21B 122B. Zero Hour's ActionManager::canPlayerGarrison: null
// guards, effectively-dead and structure tests, a garrisonable contain, then
// owner / neutral relationship and an empty contain. contextCommandForNewSelection
// (0x0030ECD6) calls it with TheActionManager (0x00E030E8) in ECX, as Zero Hour's
// SelectionInfo.cpp does; the body never reads this. Formerly rowed as the
// stdcall free function Rva0041C21BIsVisible.
// Evidence: callers 0x00261478 (36B, pushes [esi+8]/arg/[esi+0x10]) and 0x0030ECD6 (767B);
// rowed callees ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ and
// ?getRelationship@Player@@QBE?AW4Relationship@@PBVTeam@@@Z; virtual slots +0x10 (bool)
// and +0x114 (int(int)) on Object+0x250; flags Object+0x438 bit0 and [Object+4]+0x108 bit 0x80.

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2,
	RvaRel0 = 0,
	RvaRel1 = 1,
	RvaRelEnemies = 2
};

class Team;
class Object;
class Player
{
public:
	Relationship getRelationship(const Team *that) const;
	int getPlayerIndex() const { return m_playerIndex; }
	char m_pad00[0x54];
	int m_playerIndex; // +0x54
};

#include "../../Include/Common/TeamBFME2.h"

class ThingTemplate
{
public:
	unsigned char m_pre108[0x108];
	unsigned char m_kindOfBytes[0x20]; // +0x108; byte +0x109 bit 0x40
};

class VisIface
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual bool IsActive();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void d35();
	virtual void d36();
	virtual void d37();
	virtual void d38();
	virtual void d39();
	virtual void d40();
	virtual void d41();
	virtual void d42();
	virtual void d43();
	virtual void d44();
	virtual void d45();
	virtual void d46();
	virtual void d47();
	virtual void d48();
	virtual void d49();
	virtual void d50();
	virtual void d51();
	virtual void d52();
	virtual void d53();
	virtual void d54();
	virtual void d55();
	virtual void d56();
	virtual void d57();
	virtual void d58();
	virtual void d59();
	virtual void d60();
	virtual void d61();
	virtual void d62();
	virtual void d63();
	virtual void d64();
	virtual void d65();
	virtual void d66();
	virtual void d67();
	virtual void d68();
	virtual int CheckActive(int v);
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


class GameMessage
{
public:
	enum Type { MSG_ENTER_HINT = 175, MSG_CONTEST_HINT = 176, MSG_TYPE_193 = 193, MSG_TYPE_194 = 194 };
};
enum WeaponSlotType { PRIMARY_WEAPON=0 };
class Rva0041B8D2Obj;
class SpecialPowerTemplate;
struct Coord3D;
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

bool ActionManager::canPlayerGarrison(const Player *player, const Object *obj, CommandSourceType commandSource)
{
	if (player == 0 || obj == 0)
		return false;
	if ((obj->m_flags438 & 1) || ((obj->m_template->m_kindOfBytes[0] & 0x80) == 0))
		return false;
	VisIface *vis = obj->m_vis;
	if (vis == 0 || !vis->IsActive())
		return false;
	if (player == obj->getControllingPlayer())
		return true;
	if (player->getRelationship(obj->m_team) != NEUTRAL)
		return false;
	return vis->CheckActive(0) == 0;
}
