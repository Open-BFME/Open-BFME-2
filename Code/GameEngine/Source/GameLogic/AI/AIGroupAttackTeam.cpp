// cl: /O1 /DNDEBUG /MD
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
#include <string.h>

typedef int Int;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum AttitudeType {}; // opaque order enum, passed through as int (BFME1 donor)

class Team;
class Object;

class AICommandInterface
{
public:
	void aiAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType cmdSource);
	void aiHunt(CommandSourceType cmdSource);
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
	void setWeaponSetFlag(WeaponSetType wst);
	void rva0028C20F(int x);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
	void releaseWeaponLock(WeaponLockType lockType);
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
	char m_pad[0x04];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x258 - 0x08];
	AIUpdateInterface *m_ai;
};

class AIGroup
{
public:
	void groupAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType cmdSource);
	void groupHunt(CommandSourceType cmdSource);
	void rva0036DBBA(int unused, int type, unsigned int frames);
	void rva0036DC1D(ModelConditionFlagType mc, unsigned int frames);
	void setAttitude(AttitudeType tude);
	bool setWeaponLockForGroup(WeaponSlotType weaponSlot, WeaponLockType lockType);
	void rva0036DDCD(int x);
	void releaseWeaponLockForGroup(WeaponLockType lockType);
	void setWeaponSetFlag( WeaponSetType wst );

private:
	std::list<Object *> m_memberList;
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
