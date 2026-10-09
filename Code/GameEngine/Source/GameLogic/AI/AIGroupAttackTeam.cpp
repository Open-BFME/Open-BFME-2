// cl: /ICode/Libraries/Include/Lib /ICode/GameEngine/Include/GameLogic /O1 /G7 /arch:SSE /EHs /DNDEBUG /MD /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AIGroup::groupAttackTeam (?groupAttackTeam@AIGroup@@QAEXPBVTeam@@HW4CommandSourceType@@@Z),
// retail 0x0036FF33, 65 bytes, plus
// AIGroup::groupHunt (?groupHunt@AIGroup@@QAEXW4CommandSourceType@@@Z),
// retail 0x0037008E, 50 bytes.
// ZH donor GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIGroup.cpp
// groupAttackTeam plus BFME2 layout Object+0x258 AIUpdate plus +0x20 command
// subobject plus MSVC list at AIGroup+0x00 (head at +0x04). Caller 0x003BED59 does
// getTeamNamed twice plus createGroup plus getTeamAsAIGroup plus this call
// with Team plus 0x7fffffff plus source 1 which is ZH doAttack TEAM_ATTACK_TEAM.
// groupHunt forwards aiHunt to each member; caller 0x003BF8F8 builds an AIGroup
// and calls with source 1; ZH groupHunt plus BFME1 ForwardedOrders groupHunt
// at 0x00156270 plus rowed aiHunt at 0x002AE657 prove the identity.
//
// ?rva0036DDCD@AIGroup@@QAEXH@Z @ 0x0036DDCD 37B
// AIGroup broadcast: forward one int arg to rva0028C20F on every member.
// Evidence: same begin/end loop shape as setAttitude just above in this TU,
// callee rva0028C20F row, caller 0x003790B4, ret 4 single-int forward.
//
// AIGroup::setWeaponLockForGroup, retail 0x0036DD45 (136 bytes), between
// setAttitude and rva0036DDCD as in retail. Zero Hour AIGroup.cpp plus the BFME1
// donor AIGroup_setWeaponLockForGroup.cpp (same member-list walk over the
// matched Object::setWeaponLock 0x00290B24 returning whether any member locked;
// the BFME addition refreshes the current weapon when the template flag is set
// and its status computes non-zero). BFME2 deltas: the template flag sits at
// +0x16A and the refresh goes through the matched Weapon::computeStatus /
// cacheStatus; callers 0x00377EC3..0x00379094.
//
// AIGroup::rva0036DBBA (99 bytes) and AIGroup::rva0036DC1D (41 bytes), retail
// 0x0036DBBA / 0x0036DC1D in the same AIGroup block (member-list walks like the
// rows above; names by address). The first maps a type code (0x438, 0x44C..0x44F)
// to the model condition 0x72 / 0xB8..0xBB and times it on every member through
// the matched Object::setSpecialModelConditionState 0x0028AEB2 (its first
// argument is unused; single caller 0x003799FF); the second times the given
// condition on every member.

#include <list>
#include <vector>
#include <string.h>
#include "Coord3D.h"
#include "ContainmentListView.h"

typedef int Int;
enum ObjectID { INVALID_ID=0 };
namespace _STL {
 template<> vector<ObjectID>::iterator vector<ObjectID>::erase(iterator,iterator);
 template<> void vector<ObjectID>::push_back(const ObjectID&);
}


enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum AttitudeType {}; // opaque order enum, passed through as int (BFME1 donor)

class Team;
class Object;

enum CanAttackResult { ATTACKRESULT_POSSIBLE_AFTER_MOVING=2, ATTACKRESULT_POSSIBLE=3 };
enum AbleToAttackType { ATTACK_NEW_TARGET=0, ATTACK_NEW_TARGET_FORCED=1 };
class Rva0036FF74Contain {
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual bool allowedToFire();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual Rva0036AE51ListView items();
};
class SpawnBehaviorInterface { public:
 virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
 virtual void attack(const Coord3D*,int,CommandSourceType);
};
class Player;
class UpgradeTemplate { public: unsigned int pad; int type; };
class UpgradeCenter { public: bool rva0026F11A(Player*,const UpgradeTemplate*,Object*,bool); };
extern UpgradeCenter *TheUpgradeCenter;
class Rva0036DE89Production { public:
 virtual void v0(); virtual int canQueue(const UpgradeTemplate*); virtual void v2(); virtual void queue(const UpgradeTemplate*);
};
class AICommandInterface
{
public:
	void aiAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType cmdSource);
	void aiHunt(CommandSourceType cmdSource);
	void rva0036EC1D(Object*,CommandSourceType);
	void aiAttackPosition(const Coord3D *, int, CommandSourceType);
 void aiForceAttackObject(Object*,int,CommandSourceType);
 void rva0026C2D9(Object*,int,CommandSourceType);
 void rva0036EFF5(Object*,CommandSourceType);
};

class AIUpdateInterface
{
public:
	void rva0026DE3B(int arg);
	char m_pad[0x20];
	AICommandInterface m_commands;
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum WeaponLockType
{
	NOT_LOCKED = 0
};

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};

class WeaponTemplate
{
public:
	char m_pad[0x16A];
	bool m_16A;
};

class Weapon
{
public:
	WeaponStatus computeStatus(bool *valid) const;
	void cacheStatus(WeaponStatus status) const;
	char m_pad00[4];
	const WeaponTemplate *m_template;
	char m_pad08[0x18 - 8];
	unsigned int m_18;
};

// WeaponSetFlags is BitFlags<117> in BFME 2 (0x10 bytes, zeroed with memset).
template <int Bits>
class BitFlags
{
public:
	BitFlags() { memset(m_words, 0, sizeof(m_words)); }
	void set(unsigned int i) { m_words[i >> 5] |= 1u << (i & 0x1F); }
private:
	unsigned int m_words[4];
};
typedef BitFlags<117> WeaponSetFlags;
enum WeaponSetType
{
	WEAPONSET_VETERAN = 0
};
class WeaponTemplateSet;
class ThingTemplate
{
public:
	const WeaponTemplateSet *findWeaponTemplateSet(const WeaponSetFlags &t) const;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const {return &m_pos;}
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
 int rva0028B38D() const;
 bool held() const {return (m_held[0]&8)!=0;}
 CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType,const Object*,CommandSourceType) const;
	bool rva00290D2B(const UpgradeTemplate*) const;
	bool rva002940B9(const UpgradeTemplate*);
	void *rva0028BC58(int);
	Object *rva002931F5(bool);
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType, const Object*, const Coord3D*, CommandSourceType) const;
	void setWeaponSetFlag(WeaponSetType wst);
	void rva0028C20F(int x);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
	void releaseWeaponLock(WeaponLockType lockType);
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
	char m_pad[0x04];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	char m_pad78[0x1C8 - 0x78];
 unsigned char m_held[0x250-0x1C8];
	Rva0036FF74Contain *m_contain;
	char m_pad254[4];
	AIUpdateInterface *m_ai;
};

enum IterOrderType {ITER_FASTEST, ITER_SORTED_NEAR_TO_FAR, ITER_SORTED_FAR_TO_NEAR};
class SimpleObjectIterator {public: SimpleObjectIterator(); virtual ~SimpleObjectIterator(); virtual int first(); virtual int next(); void insert(int,float); void sort(IterOrderType); private: char m_pad04[0x3C-4];};
struct Coord3DCopy: Coord3D {Coord3DCopy(const Coord3D &p){x=p.x;y=p.y;z=p.z;}};
class ActionManager {public: CanAttackResult getCanAttackObject(const Object*,const Object*,CommandSourceType,AbleToAttackType);};
extern ActionManager *TheActionManager;
class AIGroup
{
public:
	void groupAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType cmdSource);
	void groupHunt(CommandSourceType cmdSource);
	void rva0036DE89(const UpgradeTemplate*);
	void rva00370554(Object*,CommandSourceType);
	const _STL::vector<ObjectID>& getAllIDs() const;
	void groupAttackPosition(const Coord3D *, Int, CommandSourceType);
	void rva0036DBBA(int unused, int type, unsigned int frames);
	void rva0036DC1D(ModelConditionFlagType mc, unsigned int frames);
	void setAttitude(AttitudeType tude);
	bool setWeaponLockForGroup(WeaponSlotType weaponSlot, WeaponLockType lockType);
	void rva0036DDCD(int x);
	void releaseWeaponLockForGroup(WeaponLockType lockType);
	void setWeaponSetFlag( WeaponSetType wst );

private:
 void groupAttackObjectPrivate(bool,Object*,int,CommandSourceType);
	unsigned int m_pad00;
	std::list<Object *> m_memberList;
	char m_pad08[0x30 - 0x08];
	mutable _STL::vector<ObjectID> m_lastRequestedIDList;
};

void AIGroup::groupAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType cmdSource)
{
	if (!team) {
		return;
	}
	std::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai) {
			ai->m_commands.aiAttackTeam(team, maxShotsToFire, cmdSource);
		}
	}
}

void AIGroup::groupHunt(CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai) {
			ai->m_commands.aiHunt(cmdSource);
		}
	}
}

void AIGroup::rva0036DBBA(int, int type, unsigned int frames)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		Object *obj = *i;
		switch (type) {
		case 0x438:
			obj->setSpecialModelConditionState((ModelConditionFlagType)0x72, frames);
			break;
		case 0x44C:
			obj->setSpecialModelConditionState((ModelConditionFlagType)0xB8, frames);
			break;
		case 0x44D:
			obj->setSpecialModelConditionState((ModelConditionFlagType)0xB9, frames);
			break;
		case 0x44E:
			obj->setSpecialModelConditionState((ModelConditionFlagType)0xBA, frames);
			break;
		case 0x44F:
			obj->setSpecialModelConditionState((ModelConditionFlagType)0xBB, frames);
			break;
		}
	}
}

void AIGroup::rva0036DC1D(ModelConditionFlagType mc, unsigned int frames)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		(*i)->setSpecialModelConditionState(mc, frames);
	}
}

void AIGroup::setAttitude(AttitudeType tude)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai) {
			ai->rva0026DE3B(tude);
		}
	}
}

bool AIGroup::setWeaponLockForGroup(WeaponSlotType weaponSlot, WeaponLockType lockType)
{
	bool any = false;
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		Object *object = *i;
		if (object) {
			const Weapon *weapon = object->getCurrentWeapon(0);
			if (object->setWeaponLock(weaponSlot, lockType))
				any = true;
			if (weapon && weapon->m_template->m_16A) {
				if (weapon->computeStatus(0)) {
					Weapon *current = const_cast<Weapon *>(object->getCurrentWeapon(0));
					current->m_18 = weapon->m_18;
					current->cacheStatus((WeaponStatus)1);
				}
			}
		}
	}
	return any;
}

void AIGroup::rva0036DDCD(int x)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i) {
		(*i)->rva0028C20F(x);
	}
}

// ?releaseWeaponLockForGroup@AIGroup@@QAEXW4WeaponLockType@@@Z
// AIGroup::releaseWeaponLockForGroup, retail 0x0036DDF2 (37 bytes), right
// after rva0036DDCD as in retail: Zero Hour's member-list walk over
// Object::releaseWeaponLock (0x0028D8B6).
void AIGroup::releaseWeaponLockForGroup(WeaponLockType lockType)
{
	std::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		(*i)->releaseWeaponLock(lockType);
	}
}

// ?setWeaponSetFlag@AIGroup@@QAEXW4WeaponSetType@@@Z
// AIGroup::setWeaponSetFlag, retail 0x0036DE17 (114 bytes), after
// releaseWeaponLockForGroup as in retail: Zero Hour's walk setting the weapon
// set flag on the members whose template has a weapon set for it
// (ThingTemplate::findWeaponTemplateSet 0x0033DCD1 on template +0x04; the
// rowed Object::setWeaponSetFlag 0x00290963).
void AIGroup::setWeaponSetFlag( WeaponSetType wst )
{
	std::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		Object *obj = (*i);
		//First check to see if our object even has the specified weaponset. It's very
		//likely that a selected group won't all have the same weaponset options, so
		//only set it for those members that have it.
		WeaponSetFlags flags;
		flags.set( wst );
		const WeaponTemplateSet* set = obj->getTemplate()->findWeaponTemplateSet( flags );
		if( set )
		{
			obj->setWeaponSetFlag( wst );
		}
	}
}

// ZH groupAttackPosition; native 0036FF74..0037008E RET12 proves caller ABI,
// position38, contain250, AI258, contain slots45/70, spawn slot4.
void AIGroup::groupAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
{
    Coord3D attackPos;
    if (pos) attackPos = *pos;
    for (std::list<Object *>::iterator i=m_memberList.begin(); i!=m_memberList.end(); ++i) {
        if (!pos) {
            const Coord3D *p=(*i)->getPosition();
            attackPos.x=p->x; attackPos.y=p->y; attackPos.z=p->z;
        }
        Rva0036FF74Contain *contain=(*i)->m_contain;
        if (contain && contain->allowedToFire()) {
            Rva0036AE51ListView items=contain->items();
            for (ContainmentList::const_iterator it=items.b->begin(); it!=items.b->end(); ++it) {
                Object *member=(Object *)containmentFirstWord(*it);
                CanAttackResult result=member->getAbleToUseWeaponAgainstTarget(ATTACK_NEW_TARGET,0,&attackPos,cmdSource);
                if (result==ATTACKRESULT_POSSIBLE || result==ATTACKRESULT_POSSIBLE_AFTER_MOVING) {
                    AIUpdateInterface *ai=member->m_ai;
                    if(ai) ai->m_commands.aiAttackPosition(&attackPos,maxShotsToFire,cmdSource);
                }
            }
        }
        SpawnBehaviorInterface *spawn=(*i)->getSpawnBehaviorInterface();
        if(spawn) spawn->attack(&attackPos,maxShotsToFire,cmdSource);
        AIUpdateInterface *ai=(*i)->m_ai;
        if(ai) ai->m_commands.aiAttackPosition(&attackPos,maxShotsToFire,cmdSource);
    }
}

// ZH queueUpgrade semantic lead; native 0036DE89..0036DF14 RET4.
// BFME2 adds Object argument to affordability; removes canProduceUpgrade;
// production interface slots1/3 accept UpgradeTemplate, queue-full enum4.
void AIGroup::rva0036DE89(const UpgradeTemplate *upgrade)
{
 if (!upgrade) return;
 for (std::list<Object*>::iterator i=m_memberList.begin(); i!=m_memberList.end(); ++i) {
  Object *obj=*i;
  if (!TheUpgradeCenter->rva0026F11A(obj->getControllingPlayer(),upgrade,obj,false)) continue;
  if (upgrade->type==1) {
   if (obj->rva00290D2B(upgrade) || !obj->rva002940B9(upgrade)) continue;
  }
  Rva0036DE89Production *production=(Rva0036DE89Production*)obj->rva0028BC58(0);
  if (!production) continue;
  if (production->canQueue(upgrade)==4) continue;
  production->queue(upgrade);
 }
}
// ZH getAllIDs; native 0036F710..0036F757 reads ObjectID74 and vector30.
const _STL::vector<ObjectID>& AIGroup::getAllIDs() const
{
 m_lastRequestedIDList.clear();
 for(std::list<Object*>::const_iterator it=m_memberList.begin();it!=m_memberList.end();++it) {
  if(!*it) continue;
  m_lastRequestedIDList.push_back((*it)->getID());
 }
 return m_lastRequestedIDList;
}

// ZH groupAttackObjectPrivate; native36FD64..36FF33 RET16, WB EE7060.
void AIGroup::groupAttackObjectPrivate(bool forced,Object *victim,int shots,CommandSourceType source)
{
 if (!victim) return;
 Coord3DCopy victimPos=*victim->getPosition();
 SimpleObjectIterator *iter=new SimpleObjectIterator;
 for(std::list<Object*>::iterator i=m_memberList.begin();i!=m_memberList.end();++i) {
  Coord3DCopy unitPos=*(*i)->getPosition();
  if((*i)->held()) continue;
  float dx=unitPos.x-victimPos.x,dy=unitPos.y-victimPos.y;
  iter->insert((int)*i,dx*dx+dy*dy);
 }
 iter->sort(ITER_SORTED_NEAR_TO_FAR);
 for(Object *unit=(Object*)iter->first();unit;unit=(Object*)iter->next()) {
  Rva0036FF74Contain *contain=unit->m_contain;
  if(contain && contain->allowedToFire()) {
   Rva0036AE51ListView items=contain->items();
   for(ContainmentList::const_iterator i=items.b->begin();i!=items.b->end();++i) {
    Object *member=(Object*)containmentFirstWord(*i);
    CanAttackResult result=member->getAbleToAttackSpecificObject(forced?ATTACK_NEW_TARGET_FORCED:ATTACK_NEW_TARGET,victim,source);
    if(result==ATTACKRESULT_POSSIBLE || result==ATTACKRESULT_POSSIBLE_AFTER_MOVING) {
     AIUpdateInterface *ai=member->m_ai;
     if(ai) {
      if(forced) ai->m_commands.aiForceAttackObject(victim,shots,source);
      else ai->m_commands.rva0026C2D9(victim,shots,source);
     }
    }
   }
  }
  AIUpdateInterface *ai=unit->m_ai;
  if(ai && unit!=victim) {
   if((unsigned char)unit->rva0028B38D()) {
    CanAttackResult result=TheActionManager->getCanAttackObject(unit,victim,source,ATTACK_NEW_TARGET);
    if(result==ATTACKRESULT_POSSIBLE || result==ATTACKRESULT_POSSIBLE_AFTER_MOVING) ai->m_commands.rva0036EFF5(victim,source);
   } else if(forced) ai->m_commands.aiForceAttackObject(victim,shots,source);
   else ai->m_commands.rva0026C2D9(victim,shots,source);
  }
 }
}
