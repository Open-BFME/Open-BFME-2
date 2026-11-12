// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?onDie@Object@@QAEXPAVDamageInfo@@@Z -- retail 0x00298517..0x00298835 (798 bytes).
// Object level events run when an object dies. Identity: the WorldBuilder twin
// Object::onDie (Object.cpp; jkmcd onDie assertion) has the same call graph in
// the same order: hero unbind (template kind bit 190) / selfInflicted from the
// damage source ID (+0x08 against the ID at +0x74) / radar removal / die module
// walk of the behaviour list at +0x244 / victory system / container removal and
// the kill of the container (kind bit 55) / status bits 88 61 62 of the +0x10C
// bitset (inline Object.h helpers that call the 0x0028AE6D notifier) /
// pathfind map removal / drawable 0x002752F8 / 0x002930A9 / makeDirty / the
// Lua death event list / emotion system / team notification / EVA unit lost
// events from the template +0x574/+0x578/+0x57C / InGameUI idle worker slot
// 0x1A8 / attacker kind bit 165 status 0x47 / random death orientation /
// living world +0x464. Zero Hour and BFME 1 Object::onDie carry the same die
// module loop radar removal team notification and idle worker removal.
// Retail-specific: line 9015 of the bfme2patch103 Object.cpp path string.
#include "Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

enum KindOfType { KINDOF_INVALID = -1 };
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum DamageType { DAMAGE_NONE = 0 };
enum DeathType { DEATH_NONE = 0 };
enum Relationship { REL_ENEMIES = 0, REL_NEUTRAL = 1, REL_ALLIES = 2 };

class Object;
class Team;

#include "../../../Include/GameLogic/Damage.h"

class Rva00265254
{
public:
	Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);
	unsigned int m_bits[19]; // +0x00
};

struct Rva0028F59A : public Rva00265254
{
	Rva0028F59A(int unused, int bit);
};

// The Object member 0x001E42F2 that takes the bit set's words, rowed as
// Rva001E42F2::rva001E42F2.
#include "../../../Include/GameLogic/Module/Rva001E42F2.h"

struct ObjectStatusBits
{
	unsigned int m_bits[4];
	__forceinline unsigned int test(int bit) const { return m_bits[bit >> 5] & (1u << (bit & 31)); }
	// Imported-forceinline: inline everywhere, no COMDAT copy differing from
	// GenericObjectCreationNuggetDoStuffToObj.cpp's (first in link order).
	__declspec(dllimport) __forceinline void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	__forceinline void clear(int bit) { m_bits[bit >> 5] &= ~(1u << (bit & 31)); }
};

#include "../../../Include/Common/ThingTemplate.h"

class DieModuleInterface
{
public:
	virtual void onDie(DamageInfo *damageInfo) = 0;
};


#include "../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../Include/GameLogic/Module/ContainModule.h"

class Rva00275376
{
public:
	void rva002752F8();
};

#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/PlayerList.h"

#include "../../../Include/Common/TeamBFME2.h"

struct Rva002D76C6Owner;
#include "../../../Include/Common/Radar.h"

#include "../../../Include/GameLogic/CreateAHeroManager.h"

struct VictoryDeathInfo;
class VictorySystem;
class VictorySystemGridUpdateView
{
public:
	void rva004050CE(Object *obj, const VictoryDeathInfo *info);
};

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/AI.h"

// DelayedLuaEventList: ctor 0x000B6D8B and virtual dtor 0x000B6DD2 (slot 0 of its
// vftable 0x007C9CF0 is the scalar deleting dtor 0x000B6E0C); the vptr is the +0 word.
// BfmeDelayedLuaEventList is only the parameter tag of the 0x003360D2 row.
struct BfmeDelayedLuaEventList;
struct DelayedLuaEventList
{
	DelayedLuaEventList();
	virtual ~DelayedLuaEventList();
	char m_data[0x48];
};

class LuaScriptEngine;
#include "../../../Include/GameLogic/Module/BfmeObjectEventDispatch.h"

struct SearchArg0042638E;
class EmotionSystem;
class Rva0042638E
{
public:
	bool rva0042638E(const SearchArg0042638E *arg);
};

enum EvaEventID { EVA_EVENT_STUB = 0 };
#include "../../../Include/GameClient/Eva.h"

#include "../../../Include/GameClient/InGameUI.h"

class LivingWorldLogic;
class Rva002B25BFOwner
{
public:
	bool rva002B25BF(int id);
};

extern CreateAHeroManager *TheCreateAHeroManager;
extern Radar *TheRadar;
extern VictorySystem *TheVictorySystem;
extern AI *TheAI;
extern LuaScriptEngine *TheLuaScriptEngine;
extern EmotionSystem *TheEmotionSystem;
extern PlayerList *ThePlayerList;
extern Eva *TheEva;
extern InGameUI *TheInGameUI;
extern GameLogic *TheGameLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

#include "../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	void onDie(DamageInfo *damageInfo);

	bool rva00293926(KindOfType kind);
	void setStatus(ObjectStatusTypes status, bool set);
	void rva0028DAB9();
	void rva0028AE6D();
	void kill(DamageType damageType, DeathType deathType);
	bool testStatus(ObjectStatusTypes status) const;
	void rva002930A9(void *arg);
	void makeDirty();
	Player *getControllingPlayer() const;
	bool isKindOf(KindOfType kind) const;

	ObjectID getID() const { return m_id; }

	__forceinline void clearStatusBit(int bit)
	{
		if (m_statusBits.test(bit))
		{
			m_statusBits.clear(bit);
			rva0028AE6D();
		}
	}
	__forceinline void setStatusBit(int bit)
	{
		if (!m_statusBits.test(bit))
		{
			m_statusBits.set(bit);
			rva0028AE6D();
		}
	}

	char pad060[0x74 - 0x60];
	ObjectID m_id;	// +0x74
	char pad078[0x84 - 0x78];
	Rva00275376 *m_drawable;	// +0x84
	char pad088[0x10C - 0x88];
	ObjectStatusBits m_statusBits;	// +0x10C
	char pad11C[0x244 - 0x11C];
	BehaviorModule **m_behaviors;	// +0x244
	char pad248[0x250 - 0x248];
	ContainModuleInterface *m_contain;	// +0x250
	char pad254[0x260 - 0x254];
	void *m_radarData;	// +0x260
	char pad264[0x274 - 0x264];
	Object *m_containedBy;	// +0x274
	char pad278[0x304 - 0x278];
	Team *m_team;	// +0x304
	char pad308[0x464 - 0x308];
	int m_livingWorldID;	// +0x464
};

void Object::onDie(DamageInfo *damageInfo)
{
	if (rva00293926((KindOfType)0x45))
	{
		setStatus((ObjectStatusTypes)0x56, true);
		((Rva001E42F2 *)this)->rva001E42F2((const int *)Rva0028F59A(0, 0x45).m_bits);
	}

	if ((m_template->m_kindof[190 >> 5] & (1u << (190 & 31))))
		TheCreateAHeroManager->UnbindHeroFromObjectAndUpdate(this);

	bool selfInflicted = (damageInfo->m_sourceID == getID());

	if (m_radarData)
		TheRadar->removeObject((Rva002D76C6Owner *)this);

	for (BehaviorModule **behaviorModule = m_behaviors; *behaviorModule; ++behaviorModule)
	{
		DieModuleInterface *die = (*behaviorModule)->getDie();
		if (die)
			die->onDie(damageInfo);
		AIUpdateInterface *ai = (*behaviorModule)->getAIUpdateInterface();
		if (ai)
			ai->vslot147();
	}

	if (TheVictorySystem)
		((VictorySystemGridUpdateView *)TheVictorySystem)->rva004050CE(this, (const VictoryDeathInfo *)damageInfo);

	rva0028DAB9();

	Object *container = m_containedBy;
	if (container)
	{
		container->m_contain->removeFromContain(this, false);
		clearStatusBit(88);
		if ((m_template->m_kindof[55 >> 5] & (1u << (55 & 31))))
			container->kill((DamageType)8, (DeathType)0);
	}

	setStatusBit(62);
	clearStatusBit(61);

	if (!testStatus((ObjectStatusTypes)0x53))
		TheAI->m_pathfinder->RemoveObjectFromPathfindMap(this);

	Rva00275376 *draw = m_drawable;
	if (draw)
		draw->rva002752F8();

	rva002930A9(damageInfo);
	makeDirty();

	DelayedLuaEventList events;
	((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(1, this, (BfmeDelayedLuaEventList *)&events);

	if ((m_template->m_kindof[144 >> 5] & (1u << (144 & 31))) || (m_template->m_kindof[90 >> 5] & (1u << (90 & 31))))
		((Rva0042638E *)TheEmotionSystem)->rva0042638E((const SearchArg0042638E *)this);

	if (m_team)
		m_team->notifyTeamOfObjectDeath(this);

	if (!selfInflicted && damageInfo->m_deathType != 0x16)
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate)
		{
			int evaEvent;
			Player *controlling = getControllingPlayer();
			Player *local = ThePlayerList->m_local;
			if (controlling == local)
				evaEvent = thingTemplate->m_evaEventDieOwner;
			else if (local && local->getRelationship(m_team) == REL_ALLIES)
				evaEvent = thingTemplate->m_evaEventDieAlly;
			else
				evaEvent = thingTemplate->m_evaEventDieEnemy;
			if (evaEvent != -1)
				TheEva->reportEvaEvent((EvaEventID)evaEvent, getPosition(), 0);
		}
	}

	int playerIndex = getControllingPlayer()->m_playerIndex;
	TheInGameUI->removeIdleWorker(this, playerIndex);

	if ((m_template->m_kindof[8 >> 5] & (1u << (8 & 31))))
	{
		Object *killer = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
		if (killer && (killer->m_template->m_kindof[165 >> 5] & (1u << (165 & 31))))
			setStatus((ObjectStatusTypes)0x47, true);
	}

	if (testStatus((ObjectStatusTypes)0x26) && !isKindOf((KindOfType)0x220))
	{
		float angle = getOrientation();
		angle += GetGameLogicRandomValueReal(0.0f, 3.14159265359f,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Object.cpp",
			9015) - 3.14159265359f / 2.0f;
		setOrientation(angle);
	}

	int livingWorldID = m_livingWorldID;
	if (livingWorldID)
		((Rva002B25BFOwner *)TheLivingWorldLogic)->rva002B25BF(livingWorldID);
}
