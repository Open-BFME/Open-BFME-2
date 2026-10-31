// cl: /Ireference/shims/bfme2_ascii /MD /GX
#include "../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
// ABI repair: retail 29C823 and named WB DBA3A0 dispatch through TheActionManager.
// The unused manager this is still part of the calling convention. Existing
// return representations are preserved. No additional name or pin is introduced.
// ?Rva0041CE27Check@ActionManager@@QAE_NPAVObject@@0H@Z @0x0041CE27 114B: enemy-relationship plus upgrade-template gated check; callers 0x0029CA95 and 0x0041D356
#include "ascii_string.h"

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2,
	RvaRel0 = 0,
	RvaRel1 = 1,
	RvaRelEnemies = 2
};

class ThingTemplate
{
public:
	unsigned char m_pre108[0x108];
	unsigned char m_kindOfBytes[0x20]; // +0x108; byte +0x109 bit 0x40
};

enum SpecialPowerType { SPECIAL_INVALID = 0 };
class SpecialAbilityUpdate;
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

class SpecialPowerTemplate;
class SpecialPowerStore {
public:
    const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString s);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class Rva0049C6E1 {
public:
    bool rva0049C6E1(Object *obj);
};

class ActionManager;
class GameMessage
{
public:
	enum Type { MSG_ENTER_HINT = 175, MSG_CONTEST_HINT = 176, MSG_TYPE_193 = 193, MSG_TYPE_194 = 194 };
};
class DrawableList;
template<int N> class NativeSlots : public NativeSlots<N-1> { public: virtual void gap(char (*)[N]) = 0; };
template<> class NativeSlots<0> {};
class InGameUI : public NativeSlots<73>
{
public:
	virtual const DrawableList *slot124();
};
extern InGameUI *TheInGameUI;

enum WeaponSlotType { PRIMARY_WEAPON=0 };
class Rva0041B8D2Obj;
struct Coord3D;
class Player;
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

bool ActionManager::Rva0041CE27Check(Object *object, Object *target, int)
{
    if (object == 0)
        return false;
    if (target == 0)
        return false;
    if (object->getRelationship(target) != RvaRelEnemies)
        return false;
    if (target->m_258 == 0)
        return false;
    if ((target->m_template->m_kindOfBytes[0] & 4) != 0)
        return false;
    const SpecialPowerTemplate *specialPowerTemplate = TheSpecialPowerStore->findSpecialPowerTemplate("SpecialAbilityGiveUpgrade");
    if (specialPowerTemplate == 0)
        return false;
    void *slot = object->findSpecialAbilityUpdate((SpecialPowerType)(0x33));
    if (slot != 0)
        return ((Rva0049C6E1 *)slot)->rva0049C6E1(target);
    return false;
}

// ?rva0041CE06@ActionManager@@QAE?AW4Type@GameMessage@@PBVObject@@@Z @0x0041CE06 33B
// Leaf forwarding InGameUI drawable list to getEnterMessage. Evidence:
// callers 0x0042A6F2, callees TheInGameUI slot124 getEnterMessage,
// prev/next ActionManager files.
GameMessage::Type ActionManager::rva0041CE06(const Object *obj)
{
	const DrawableList *draws = TheInGameUI->slot124();
	return getEnterMessage(obj, draws);
}
