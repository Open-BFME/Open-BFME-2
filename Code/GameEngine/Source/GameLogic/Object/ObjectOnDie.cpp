// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?onDie@Object@@QAEXPAUDamageInfo@@@Z -- retail 0x00298517..0x00298835 (798 bytes).
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

struct DamageInfo
{
	char pad00[0x08];
	ObjectID m_sourceID;	// +0x08
	char pad0C[0x1C - 0x0C];
	int m_deathType;	// +0x1C
};

class Rva00265254
{
public:
	unsigned int m_bits[19];
};

struct Rva0028F59A : public Rva00265254
{
	Rva0028F59A(int unused, int bit);
};

struct ObjectStatusBits
{
	unsigned int m_bits[4];
	__forceinline unsigned int test(int bit) const { return m_bits[bit >> 5] & (1u << (bit & 31)); }
	__forceinline void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	__forceinline void clear(int bit) { m_bits[bit >> 5] &= ~(1u << (bit & 31)); }
};

class ThingTemplate
{
public:
	__forceinline unsigned int isKindOf(int bit) const { return m_kindOf[bit >> 5] & (1u << (bit & 31)); }

	char pad000[0x108];
	unsigned int m_kindOf[7];	// +0x108
	char pad124[0x574 - 0x124];
	int m_evaOwnUnitLost;	// +0x574
	int m_evaAllyUnitLost;	// +0x578
	int m_evaEnemyUnitLost;	// +0x57C
};

class DieModuleInterface
{
public:
	virtual void onDie(DamageInfo *damageInfo) = 0;
};

class Rva002985C6Interface
{
public:
	virtual void vf000(); virtual void vf004(); virtual void vf008(); virtual void vf00C();
	virtual void vf010(); virtual void vf014(); virtual void vf018(); virtual void vf01C();
	virtual void vf020(); virtual void vf024(); virtual void vf028(); virtual void vf02C();
	virtual void vf030(); virtual void vf034(); virtual void vf038(); virtual void vf03C();
	virtual void vf040(); virtual void vf044(); virtual void vf048(); virtual void vf04C();
	virtual void vf050(); virtual void vf054(); virtual void vf058(); virtual void vf05C();
	virtual void vf060(); virtual void vf064(); virtual void vf068(); virtual void vf06C();
	virtual void vf070(); virtual void vf074(); virtual void vf078(); virtual void vf07C();
	virtual void vf080(); virtual void vf084(); virtual void vf088(); virtual void vf08C();
	virtual void vf090(); virtual void vf094(); virtual void vf098(); virtual void vf09C();
	virtual void vf0A0(); virtual void vf0A4(); virtual void vf0A8(); virtual void vf0AC();
	virtual void vf0B0(); virtual void vf0B4(); virtual void vf0B8(); virtual void vf0BC();
	virtual void vf0C0(); virtual void vf0C4(); virtual void vf0C8(); virtual void vf0CC();
	virtual void vf0D0(); virtual void vf0D4(); virtual void vf0D8(); virtual void vf0DC();
	virtual void vf0E0(); virtual void vf0E4(); virtual void vf0E8(); virtual void vf0EC();
	virtual void vf0F0(); virtual void vf0F4(); virtual void vf0F8(); virtual void vf0FC();
	virtual void vf100(); virtual void vf104(); virtual void vf108(); virtual void vf10C();
	virtual void vf110(); virtual void vf114(); virtual void vf118(); virtual void vf11C();
	virtual void vf120(); virtual void vf124(); virtual void vf128(); virtual void vf12C();
	virtual void vf130(); virtual void vf134(); virtual void vf138(); virtual void vf13C();
	virtual void vf140(); virtual void vf144(); virtual void vf148(); virtual void vf14C();
	virtual void vf150(); virtual void vf154(); virtual void vf158(); virtual void vf15C();
	virtual void vf160(); virtual void vf164(); virtual void vf168(); virtual void vf16C();
	virtual void vf170(); virtual void vf174(); virtual void vf178(); virtual void vf17C();
	virtual void vf180(); virtual void vf184(); virtual void vf188(); virtual void vf18C();
	virtual void vf190(); virtual void vf194(); virtual void vf198(); virtual void vf19C();
	virtual void vf1A0(); virtual void vf1A4(); virtual void vf1A8(); virtual void vf1AC();
	virtual void vf1B0(); virtual void vf1B4(); virtual void vf1B8(); virtual void vf1BC();
	virtual void vf1C0(); virtual void vf1C4(); virtual void vf1C8(); virtual void vf1CC();
	virtual void vf1D0(); virtual void vf1D4(); virtual void vf1D8(); virtual void vf1DC();
	virtual void vf1E0(); virtual void vf1E4(); virtual void vf1E8(); virtual void vf1EC();
	virtual void vf1F0(); virtual void vf1F4(); virtual void vf1F8(); virtual void vf1FC();
	virtual void vf200(); virtual void vf204(); virtual void vf208(); virtual void vf20C();
	virtual void vf210(); virtual void vf214(); virtual void vf218(); virtual void vf21C();
	virtual void vf220(); virtual void vf224(); virtual void vf228(); virtual void vf22C();
	virtual void vf230(); virtual void vf234(); virtual void vf238(); virtual void vf23C();
	virtual void vf240(); virtual void vf244(); virtual void vf248();
	virtual void onOwnerDied();	// +0x24C
};

class BehaviorModuleInterface
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual void vf10(); virtual void vf14(); virtual void vf18();
	virtual DieModuleInterface *getDie();	// +0x1C
	virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
	virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
	virtual void vf40(); virtual void vf44(); virtual void vf48();
	virtual Rva002985C6Interface *getRva002985C6();	// +0x4C
};

class BehaviorModule
{
public:
	char pad00[0x0C];
	BehaviorModuleInterface m_interface;	// +0x0C
};

class ContainModuleInterface
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
	virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
	virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
	virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C();
	virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
	virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
	virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7C();
	virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8C();
	virtual void vf90(); virtual void vf94(); virtual void vf98(); virtual void vf9C();
	virtual void vfA0();
	virtual void removeFromContain(Object *obj, bool exposeStealthUnits);	// +0xA4
};

class Rva00275376
{
public:
	void rva002752F8();
};

class Player
{
public:
	Relationship getRelationship(const Team *that) const;

	char pad00[0x54];
	int m_playerIndex;	// +0x54
};

class PlayerList
{
public:
	char pad00[0x10];
	Player *m_local;	// +0x10
};

class Team
{
public:
	void notifyTeamOfObjectDeath(Object *obj);
};

struct Rva002D76C6Owner;
class Radar
{
public:
	void removeObject(Rva002D76C6Owner *obj);
};

class CreateAHeroManager
{
public:
	void UnbindHeroFromObjectAndUpdate(Object *obj);
};

struct VictoryDeathInfo;
class VictorySystem;
class VictorySystemGridUpdateView
{
public:
	void rva004050CE(Object *obj, const VictoryDeathInfo *info);
};

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMap(Object *obj);
};

class AI
{
public:
	char pad00[0x10];
	Pathfinder *m_pathfinder;	// +0x10
};

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
class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int eventType, void *obj, BfmeDelayedLuaEventList *list);
};

struct SearchArg0042638E;
class EmotionSystem;
class Rva0042638E
{
public:
	bool rva0042638E(const SearchArg0042638E *arg);
};

class Eva
{
public:
	void rva001DE2DA(int eventType, const Coord3D *pos, int playerIndex);
};

class InGameUI
{
public:
	virtual void vf000(); virtual void vf004(); virtual void vf008(); virtual void vf00C();
	virtual void vf010(); virtual void vf014(); virtual void vf018(); virtual void vf01C();
	virtual void vf020(); virtual void vf024(); virtual void vf028(); virtual void vf02C();
	virtual void vf030(); virtual void vf034(); virtual void vf038(); virtual void vf03C();
	virtual void vf040(); virtual void vf044(); virtual void vf048(); virtual void vf04C();
	virtual void vf050(); virtual void vf054(); virtual void vf058(); virtual void vf05C();
	virtual void vf060(); virtual void vf064(); virtual void vf068(); virtual void vf06C();
	virtual void vf070(); virtual void vf074(); virtual void vf078(); virtual void vf07C();
	virtual void vf080(); virtual void vf084(); virtual void vf088(); virtual void vf08C();
	virtual void vf090(); virtual void vf094(); virtual void vf098(); virtual void vf09C();
	virtual void vf0A0(); virtual void vf0A4(); virtual void vf0A8(); virtual void vf0AC();
	virtual void vf0B0(); virtual void vf0B4(); virtual void vf0B8(); virtual void vf0BC();
	virtual void vf0C0(); virtual void vf0C4(); virtual void vf0C8(); virtual void vf0CC();
	virtual void vf0D0(); virtual void vf0D4(); virtual void vf0D8(); virtual void vf0DC();
	virtual void vf0E0(); virtual void vf0E4(); virtual void vf0E8(); virtual void vf0EC();
	virtual void vf0F0(); virtual void vf0F4(); virtual void vf0F8(); virtual void vf0FC();
	virtual void vf100(); virtual void vf104(); virtual void vf108(); virtual void vf10C();
	virtual void vf110(); virtual void vf114(); virtual void vf118(); virtual void vf11C();
	virtual void vf120(); virtual void vf124(); virtual void vf128(); virtual void vf12C();
	virtual void vf130(); virtual void vf134(); virtual void vf138(); virtual void vf13C();
	virtual void vf140(); virtual void vf144(); virtual void vf148(); virtual void vf14C();
	virtual void vf150(); virtual void vf154(); virtual void vf158(); virtual void vf15C();
	virtual void vf160(); virtual void vf164(); virtual void vf168(); virtual void vf16C();
	virtual void vf170(); virtual void vf174(); virtual void vf178(); virtual void vf17C();
	virtual void vf180(); virtual void vf184(); virtual void vf188(); virtual void vf18C();
	virtual void vf190(); virtual void vf194(); virtual void vf198(); virtual void vf19C();
	virtual void vf1A0(); virtual void vf1A4();
	virtual void removeIdleWorker(Object *obj, int playerIndex);	// +0x1A8
};

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

class Thing
{
public:
	void setOrientation(float angle);
	const ThingTemplate *getTemplate() const { return m_template; }
	float getOrientation() const { return m_orientation; }
	const Coord3D *getPosition() const { return &m_pos; }

	void *m_vtbl;	// +0x00
	const ThingTemplate *m_template;	// +0x04
	char pad08[0x38 - 0x08];
	Coord3D m_pos;	// +0x38
	float m_orientation;	// +0x44
};

class Object : public Thing
{
public:
	void onDie(DamageInfo *damageInfo);

	bool rva00293926(KindOfType kind);
	void setStatus(ObjectStatusTypes status, bool set);
	void rva001E42F2(const Rva00265254 &mask);
	void rva0028DAB9();
	void rva0028AE6D();
	void kill(DamageType damageType, DeathType deathType);
	bool testStatus(ObjectStatusTypes status) const;
	void rva002930A9(int arg);
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

	char pad048[0x74 - 0x48];
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
		rva001E42F2(Rva0028F59A(0, 0x45));
	}

	if (getTemplate()->isKindOf(190))
		TheCreateAHeroManager->UnbindHeroFromObjectAndUpdate(this);

	bool selfInflicted = (damageInfo->m_sourceID == getID());

	if (m_radarData)
		TheRadar->removeObject((Rva002D76C6Owner *)this);

	for (BehaviorModule **d = m_behaviors; *d; ++d)
	{
		DieModuleInterface *die = (*d)->m_interface.getDie();
		if (die)
			die->onDie(damageInfo);
		Rva002985C6Interface *other = (*d)->m_interface.getRva002985C6();
		if (other)
			other->onOwnerDied();
	}

	if (TheVictorySystem)
		((VictorySystemGridUpdateView *)TheVictorySystem)->rva004050CE(this, (const VictoryDeathInfo *)damageInfo);

	rva0028DAB9();

	Object *container = m_containedBy;
	if (container)
	{
		container->m_contain->removeFromContain(this, false);
		clearStatusBit(88);
		if (getTemplate()->isKindOf(55))
			container->kill((DamageType)8, (DeathType)0);
	}

	setStatusBit(62);
	clearStatusBit(61);

	if (!testStatus((ObjectStatusTypes)0x53))
		TheAI->m_pathfinder->RemoveObjectFromPathfindMap(this);

	Rva00275376 *draw = m_drawable;
	if (draw)
		draw->rva002752F8();

	rva002930A9((int)damageInfo);
	makeDirty();

	DelayedLuaEventList events;
	((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(1, this, (BfmeDelayedLuaEventList *)&events);

	if (getTemplate()->isKindOf(144) || getTemplate()->isKindOf(90))
		((Rva0042638E *)TheEmotionSystem)->rva0042638E((const SearchArg0042638E *)this);

	if (m_team)
		m_team->notifyTeamOfObjectDeath(this);

	if (!selfInflicted && damageInfo->m_deathType != 0x16)
	{
		const ThingTemplate *tmpl = getTemplate();
		if (tmpl)
		{
			int evaEvent;
			Player *controlling = getControllingPlayer();
			Player *local = ThePlayerList->m_local;
			if (controlling == local)
				evaEvent = tmpl->m_evaOwnUnitLost;
			else if (local && local->getRelationship(m_team) == REL_ALLIES)
				evaEvent = tmpl->m_evaAllyUnitLost;
			else
				evaEvent = tmpl->m_evaEnemyUnitLost;
			if (evaEvent != -1)
				TheEva->rva001DE2DA(evaEvent, getPosition(), 0);
		}
	}

	int playerIndex = getControllingPlayer()->m_playerIndex;
	TheInGameUI->removeIdleWorker(this, playerIndex);

	if (getTemplate()->isKindOf(8))
	{
		Object *killer = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
		if (killer && killer->getTemplate()->isKindOf(165))
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
