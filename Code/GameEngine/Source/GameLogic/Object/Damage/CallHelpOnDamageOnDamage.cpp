// cl: /DNDEBUG /MD /EHsc
//
// CallHelpOnDamage::onDamage (0x004BB547, slot 0 of its DamageModuleInterface
// vftable 0x00859FD0, the +0x10 subobject; deleting dtor 0x004BB4B5 heads the
// primary vftable). Field names are the module data's INI table at 0x00859F70.
// On a listed damage type once CallDelay has passed: every object of the
// owner's player (0x00260E2A) that ValidObjects (0x002614EC) and 0x0026185B
// accept within CallRadius (BFME2's partition filter chain, the view
// AIStructureCreepTactic.cpp documents) gets AI command 0x003C7653 at the
// attacker (MoveToAttacker, when 0x00049DC5 finds it) or the owner.
class Object;
class Player;

#include "../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD04, allow 0x00260E2A, slot 2 0x00260E1E: +0x08 a player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

// vftable 0x00C59EA8, allow 0x0026185B: +0x08 a flag.
class Rva0026185BFilter : public Rva000421C8
{
public:
	Rva0026185BFilter(bool flag) : m_flag(flag) {}
	virtual bool allow(Object *obj);
	bool m_flag;
};


#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

#include "../../../Common/GameLogicObjectLookupView.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 1
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

// What precedes the AICommandInterface subobject (+0x20).
class Rva004BB547AIBase
{
public:
	virtual void rva004BB547AIBaseAnchor();
private:
	char m_pad04[0x1C];
};


#include "../object.h"

extern GameLogic *TheGameLogic;

struct DamageInfo
{
	char m_pad00[0x08];
	ObjectID m_sourceID;	// +0x08
	char m_pad0C[0x10 - 0x0C];
	int m_damageType;	// +0x10
};

class ModuleData;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/DamageModuleClass.h"

class BfmeFixedStorage0004543D;

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);
private:
	int m_x;
};

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	virtual ~UpdateModuleData();
private:
	int m_gap04;
};

class MultiIniFieldParse;

class CallHelpOnDamageModuleData : public UpdateModuleData
{
public:
	CallHelpOnDamageModuleData();
	virtual ~CallHelpOnDamageModuleData();
	unsigned m_mask;			// +0x08 DamageTypes
	float m_callRadius;		// +0x0C CallRadius
	int m_callDelay;			// +0x10 CallDelay
	bool m_moveToAttacker;		// +0x14 MoveToAttacker
	Rva003623E5Filter m_validObjects;	// +0x18 ValidObjects
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class CallHelpOnDamage : public DamageModule
{
public:
	CallHelpOnDamage(Thing *thing, const ModuleData *moduleData);
	virtual ~CallHelpOnDamage();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onDamage(DamageInfo *damageInfo);
private:
	const CallHelpOnDamageModuleData *getCallHelpOnDamageModuleData() const
	{
		return (const CallHelpOnDamageModuleData *)m_moduleData;
	}
	unsigned m_nextCallFrame;	// +0x14
};

void CallHelpOnDamage::onDamage(DamageInfo *damageInfo)
{
	const CallHelpOnDamageModuleData *data = getCallHelpOnDamageModuleData();
	if (!(data->m_mask & (1 << (damageInfo->m_damageType - 1))))
		return;
	unsigned now = TheGameLogic->getFrame();
	if (now <= m_nextCallFrame)
		return;

	Object *target;
	if (!data->m_moveToAttacker || (target = TheGameLogic->findObjectByID(damageInfo->m_sourceID)) == 0)
		target = m_object;

	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(getObject()->getPosition(), data->m_callRadius, 1,
		Rva00260E2AFilter(m_object->getControllingPlayer())
			.link(&Rva002614ECFilter(&data->m_validObjects, m_object->getControllingPlayer(), true))
			->link(&Rva0026185BFilter(true)), 0);
	Object *other;
	while ((other = hits.next()) != 0) {
		AIUpdateInterface *ai = other->getAIUpdateInterface();
		if (ai)
			ai->rva003C7653(target, CMD_FROM_PLAYER);
	}
	m_nextCallFrame = now + data->m_callDelay;
}
