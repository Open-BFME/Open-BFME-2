// cl: /I. /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_DONT_FORCE_MSVC_LIB_NAME
// stlport
// The canonical declaration names STLport types; keep library selection with the link.
// ScriptActions members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv) and Zero Hour's ScriptActions.cpp; retail
// supplies the bytes. Use the registered BFME 2 class declaration.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"

class CommandButton;
class UpgradeTemplate;

// WB ScriptActions::doPlaySoundEffect @0x003BD5E0 (153B): look up the named
// event, create it only when found, assign the local player's index, and post it.
class AudioManager;
extern AudioManager *TheAudio;

class AudioEventInfoRef
{
public:
	~AudioEventInfoRef()
	{
		if (m_info)
			m_info->Release_Ref();
	}

	OpaqueRefCounted *m_info;
};

class ScriptActionsAudioView
{
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(0) AUDIO_SLOT(1) AUDIO_SLOT(2) AUDIO_SLOT(3) AUDIO_SLOT(4)
	AUDIO_SLOT(5) AUDIO_SLOT(6) AUDIO_SLOT(7) AUDIO_SLOT(8) AUDIO_SLOT(9)
	AUDIO_SLOT(10) AUDIO_SLOT(11) AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14)
	AUDIO_SLOT(15) AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24)
#undef AUDIO_SLOT
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event);
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29) AUDIO_SLOT(30)
	AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33) AUDIO_SLOT(34) AUDIO_SLOT(35)
	AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38) AUDIO_SLOT(39) AUDIO_SLOT(40)
	AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43) AUDIO_SLOT(44) AUDIO_SLOT(45)
	AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48) AUDIO_SLOT(49) AUDIO_SLOT(50)
	AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54) AUDIO_SLOT(55)
	AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59) AUDIO_SLOT(60)
	AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63) AUDIO_SLOT(64) AUDIO_SLOT(65)
	AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68) AUDIO_SLOT(69) AUDIO_SLOT(70)
	AUDIO_SLOT(71) AUDIO_SLOT(72) AUDIO_SLOT(73) AUDIO_SLOT(74)
#undef AUDIO_SLOT
	virtual AudioEventInfoRef findAudioEvent(const AsciiString &name);
};

class Rva0033F15DDwordSlot
{
public:
	void set(int value);
};

struct PlayerTeamNode;

class Player
{
public:
	unsigned char m_pad00[0x54];
	int m_playerIndex;
	AsciiString m_side; // +0x58
	int m_playerType;
	unsigned char m_pad60[0x32C - 0x60];
	PlayerTeamNode *m_playerTeamPrototypes;
	unsigned char m_pad330[0x738 - 0x330];
	class UnitRevivalTracker *getUnitRevivalTracker() { return (UnitRevivalTracker *)m_unitRevivalTracker; }
	unsigned char m_unitRevivalTracker[4];
	int rva002ABCF0(unsigned char flag, int *out);
	unsigned char rva002AA00C(class ThingTemplate *tmpl, int arg);
	bool rva00339() const { return ((const unsigned char *)this)[0x339] != 0; }
	int getPlayerType() const { return m_playerType; }
	void rva002ABA9B();
	int getPlayerIndex() const { return m_playerIndex; }
	int getMpStartIndex() const { return *(const int *)((const unsigned char *)this + 0x2E0); }
	void setUnitsShouldIdleOrResume(bool idle);
};

// 0x002ACEDF is rowed as Rva002ABFA0::rva002ACEDF (35B Player short-list
// append from Rva002ABFA0Remove.cpp); this TU calls it through a TU-local
// view so it resolves to the rowed body instead of the unrowed Player
// spelling (U on ScriptActions' unit).
class Rva002ABFA0
{
public:
	void rva002ACEDF(void *p);
};
class PlayerList
{
public:
	unsigned char m_pad00[0x10];
	Player *m_localPlayer;
	int m_playerCount;
	int getPlayerCount() const { return m_playerCount; }
	Player *getNthPlayer(int i);
	Player *getEachPlayerFromMask(int &mask);
	Player *getPlayerFromMask(int mask);
	int getPlayersWithRelationship(int srcPlayerIndex, unsigned int allowedRelationships, bool flag);
};
extern PlayerList *ThePlayerList;

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

class Waypoint;
class ScriptActionsTerrainView
{
public:
#define TERRAIN_SLOT(n) virtual void slot##n();
	TERRAIN_SLOT(0) TERRAIN_SLOT(1) TERRAIN_SLOT(2) TERRAIN_SLOT(3)
	TERRAIN_SLOT(4) TERRAIN_SLOT(5) TERRAIN_SLOT(6) TERRAIN_SLOT(7)
	TERRAIN_SLOT(8) TERRAIN_SLOT(9) TERRAIN_SLOT(10) TERRAIN_SLOT(11)
	TERRAIN_SLOT(12) TERRAIN_SLOT(13) TERRAIN_SLOT(14) TERRAIN_SLOT(15)
	TERRAIN_SLOT(16) TERRAIN_SLOT(17) TERRAIN_SLOT(18) TERRAIN_SLOT(19)
	TERRAIN_SLOT(20) TERRAIN_SLOT(21) TERRAIN_SLOT(22) TERRAIN_SLOT(23)
	TERRAIN_SLOT(24) TERRAIN_SLOT(25) TERRAIN_SLOT(26) TERRAIN_SLOT(27)
	TERRAIN_SLOT(28) TERRAIN_SLOT(29) TERRAIN_SLOT(30) TERRAIN_SLOT(31)
	TERRAIN_SLOT(32) TERRAIN_SLOT(33)
#undef TERRAIN_SLOT
	virtual Waypoint *getWaypointByName(const AsciiString &name);
	virtual void slot35();
	virtual Waypoint *getClosestWaypointOnPath(const struct Coord3D *pos, const AsciiString &label);
};

void ScriptActions::doPlaySoundEffect(const AsciiString &sound)
{
	AudioEventInfoRef info = reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->findAudioEvent(sound);
	if (!info.m_info)
		return;
	BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4 *>(&info), 0);
	Player *localPlayer = ThePlayerList->m_localPlayer;
	reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(localPlayer->m_playerIndex);
	reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->addAudioEvent(&event);
}

// WB ScriptActions::doPlaySoundEffectAt @0x003BD679 (182B): resolve the named
// waypoint and event, then post the event at Waypoint's +0x0C position.
void ScriptActions::doPlaySoundEffectAt(const AsciiString &sound,
	const AsciiString &waypointName)
{
	Waypoint *way = reinterpret_cast<ScriptActionsTerrainView *>(TheTerrainLogic)->getWaypointByName(waypointName);
	if (!way)
		return;
	AudioEventInfoRef info = reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->findAudioEvent(sound);
	if (!info.m_info)
		return;
	way = reinterpret_cast<Waypoint *>(reinterpret_cast<unsigned char *>(way) + 0x0C);
	BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4 *>(&info),
		*reinterpret_cast<const BfmeEventPositionView *>(way), 0);
	reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(
		ThePlayerList->m_localPlayer->m_playerIndex);
	reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->addAudioEvent(&event);
}

// WB ScriptActions::doSpeechPlay @0x003BD7E2 (162B): post the named event for
// the local player and set its uninterruptable flag from allowOverlap.
void ScriptActions::doSpeechPlay(const AsciiString &speechName, bool allowOverlap)
{
	AudioEventInfoRef info = reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->findAudioEvent(speechName);
	if (!info.m_info)
		return;
	BfmeAudioEventPrefix136 speech(*reinterpret_cast<const OpaqueRefElement4 *>(&info), 0);
	Player *localPlayer = ThePlayerList->m_localPlayer;
	reinterpret_cast<Rva0033F15DDwordSlot *>(&speech)->set(localPlayer->m_playerIndex);
	speech.m_b4A = !allowOverlap;
	reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->addAudioEvent(&speech);
}

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	unsigned char m_pad[0x10];
	AsciiString m_string;
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

enum ObjectID { INVALID_OBJECT_ID = 0 };

#include "Code/Libraries/Include/Lib/Coord3D.h"

// BFME 2 copies a position field by field here (the fork's view gave Coord3D
// a member-wise copy constructor; the canonical header is data-only).
static __forceinline void copyCoord3D(Coord3D &to, const Coord3D *from)
{
	to.x = from->x;
	to.y = from->y;
	to.z = from->z;
}

class Drawable;

class Thing
{
public:
	void setOrientation(float angle);
	void setPosition(const Coord3D *pos);
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
 bool rva002922D9(const CommandButton *);
 void rva00297000(const CommandButton *, Object *, int, int);
 void doCommandButtonAtPosition(const CommandButton *, const Coord3D *, int, int);
 bool affectedByUpgrade(const UpgradeTemplate *) const;
 bool hasUpgrade(const UpgradeTemplate *) const;
 void rva00293077(const void *);
 const ThingTemplate *getTemplate() const { return m_template; }
	unsigned char m_pad00[0x04];
	const class ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_objectID;
	unsigned char m_pad78[0x88 - 0x78];
	AsciiString m_name;
	unsigned char m_pad8C[0x80];
	class ModelConditionFlags {
	public:
		unsigned int test(unsigned int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
		void set(unsigned int bit) { m_words[bit >> 5] |= 1U << (bit & 0x1f); }
		void clear(unsigned int bit) { m_words[bit >> 5] &= ~(1U << (bit & 0x1f)); }
	private:
		unsigned int m_words[19];
	} m_modelConditionFlags;
	unsigned char m_pad158[0x250 - 0x158];
	class ScriptActionsContainView *m_contain;
	unsigned char m_pad254[0x438 - 0x254];
	unsigned char m_privateStatus;
	Player *getControllingPlayer() const;
	void forceEmotion(int index, float value, int arg);
	void setName(const AsciiString &name) { m_name = name; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	const Coord3D *getPosition() const { return &m_position; }
	__forceinline bool isKindOf(int t) const;
	ScriptActionsContainView *getContain() const { return m_contain; }
	void rva0028FC18();
	void *rva0028BCF4() const;
	void *rva0028C197() const;
	void updateUpgradeModules();
	void doSpecialPowerAtObject(const class SpecialPowerTemplate *power, Object *target, unsigned flags, bool arg);
	int getIndicatorColor() const;
	int getNightIndicatorColor() const;
	void rva0028BAC0();
	void rva0028DCC4();
	void rva0028AE6D();
	__forceinline void setModelConditionState(unsigned int bit) {
		if (m_modelConditionFlags.test(bit) == 0) {
			m_modelConditionFlags.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(unsigned int bit) {
		if (m_modelConditionFlags.test(bit) != 0) {
			m_modelConditionFlags.clear(bit);
			rva0028AE6D();
		}
	}
protected:
	friend class ScriptActions;
	class Module *findModule(enum NameKeyType key) const;
public:
	Object *getContainedBy() const { return *(Object *const *)((const unsigned char *)this + 0x274); }
	class AIUpdateInterface *getAIUpdateInterface() const { return *(AIUpdateInterface *const *)((const unsigned char *)this + 0x258); }
};

void ScriptActions::doSoundPlayFromNamed(const AsciiString &sound,
	const AsciiString &unitName)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit)
		return;
	AudioEventInfoRef info = reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->findAudioEvent(sound);
	if (!info.m_info)
		return;
	BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4 *>(&info),
		unit->m_objectID);
	Player *owner = unit->getControllingPlayer();
	if (owner)
		reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(owner->m_playerIndex);
	reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->addAudioEvent(&event);
}

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// The Object member-function pointer in BFME's DLINK_ITERATOR is 20 bytes;
// Team's iterator above carries an 8-byte pointer-to-member function.
template<>
class DLINK_ITERATOR<Object>
{
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();	// rowed 0x00263526 (virtual-inheritance GetNextFunc)
	bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	class TeamPrototype *m_value;
};

#include "../../../Include/Common/MemoryPoolObject.h"

class Team;

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva0039E5B9(struct Coord3D *pos);
 Coord3D *rva0039DA2A(Coord3D *) const;
	void getTeamAsAIGroup(class AIGroup *group);
	class Object *rva0039E8EB();
	void setControllingPlayer(Player *newController);
	int rva0039DD12(int (*func)(class Object *, void *), void *userData) const;
	bool hasAnyObjects(bool ignoreBuildings);
	class Object *rva0039E968(int kindOf);
	bool rva0039E8FF(int val);
	Player *getControllingPlayer() const;
	void rva003A1AA3(const class ThingTemplate *tmpl, class ObjectTypes *types, int count, float radius);
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList,
			&Team::dlink_next_TeamInstanceList);
	}

private:
	unsigned char m_pad[0x334];
	Team *m_dlinkhead_TeamInstanceList;
};

class ThingTemplate
{
public:
 bool rva003BE11C94() const { return (((const unsigned char *)this)[0x113] & 0x40) != 0; }
 bool isEquivalentTo(const ThingTemplate *) const;
	int rva0033B479() const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	class Object *newObject(const ThingTemplate *tmplate, class Team *team,
		const struct CreateMask *mask, ObjectID flag);
};
extern ThingFactory *TheThingFactory;

// WB/ZH ScriptActions::doIdleAllPlayerUnits @0x003BBB7E (114B) and
// doResumeSupplyTruckingForIdleUnits @0x003BBBF0 (113B), identified by their
// WorldBuilder DEBUG_LOG strings. BFME2 resolves the name to a player mask
// and applies the setting to every selected player; with no match it falls
// back to every human player, as Zero Hour does.
enum { PLAYER_HUMAN = 0 };

void ScriptActions::doIdleAllPlayerUnits(const AsciiString &playerName)
{
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (!mask) {
		for (int i = 0; i < ThePlayerList->getPlayerCount(); ++i) {
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->getPlayerType() == PLAYER_HUMAN)
				player->setUnitsShouldIdleOrResume(true);
		}
	} else {
		while (mask) {
			Player *player = ThePlayerList->getEachPlayerFromMask(mask);
			if (player)
				player->setUnitsShouldIdleOrResume(true);
		}
	}
}

void ScriptActions::doResumeSupplyTruckingForIdleUnits(const AsciiString &playerName)
{
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (!mask) {
		for (int i = 0; i < ThePlayerList->getPlayerCount(); ++i) {
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->getPlayerType() == PLAYER_HUMAN)
				player->setUnitsShouldIdleOrResume(false);
		}
	} else {
		while (mask) {
			Player *player = ThePlayerList->getEachPlayerFromMask(mask);
			if (player)
				player->setUnitsShouldIdleOrResume(false);
		}
	}
}


struct ScriptWaypointView
{
	unsigned char m_pad00[0x0C];
	Coord3D m_location;
	const Coord3D *getLocation() const { return &m_location; }
};

// WB ScriptActions::doSetUnitReference @0x003C2019 (99B): either hand the
// parameter's string to the script engine's reference setter 0x00208A09, or
// resolve the parameter to a unit and bind the reference to it.
void ScriptActions::doSetUnitReference(const AsciiString &reference, Parameter *unit, bool byName)
{
	if (byName) {
		TheScriptEngine->rva00208A09(reference, unit->getString());
	} else {
		Object *theObj = TheScriptEngine->getUnitNamed(unit);
		if (theObj) {
			TheScriptEngine->rva00208968(reference, theObj);
			TheScriptEngine->addObjectToCache(theObj, reference);
		}
	}
}

// WB/ZH ScriptActions::doTeamFollowWaypoints @0x003BF39F (304B). BFME2 adds a
// second flag selecting a third AIGroup path command (0x0036FB57) and passes
// each command a trailing 0.
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};

class AIGroup
{
public:
	void groupMoveToPosition(Rva00372571Params *params, int source);
	void groupIdle(CommandSourceType cmdSource);
	bool getCenter(Coord3D *pos);
	void groupAttackMoveToPosition(const Coord3D *pos, int maxShots, CommandSourceType cmdSource);
	void rva0036F9FE(const Waypoint *way, CommandSourceType cmdSource, int mode);
	void rva0036FB57(const Waypoint *way, CommandSourceType cmdSource, int mode);
};

class Rva0036FAF8
{
public:
	void rva0036FAF8(const Waypoint *way, CommandSourceType cmdSource, int mode);
};

struct ScriptActionsAIData
{
	unsigned char m_pad[0x5C];
	float m_5C;
};

class AI
{
public:
	AIGroup *createGroup();
	const ScriptActionsAIData *getAiData() const { return m_aiData; }

private:
	unsigned char m_pad00[0x18];
	ScriptActionsAIData *m_aiData;
};
extern AI *TheAI;

void ScriptActions::doTeamFollowWaypoints(const AsciiString &teamName,
	const AsciiString &waypointPathLabel, bool asTeam, bool flag)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;
	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;
	theTeam->getTeamAsAIGroup(theGroup);
	int count = 0;
	Coord3D pos;
	pos.x = pos.y = pos.z = 0;
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done();
		iter.advance()) {
		Object *obj = iter.cur();
		Coord3D objPos;
		copyCoord3D(objPos, obj->getPosition());
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z;
		count++;
	}
	if (count == 0)
		return;
	pos.x /= count;
	pos.y /= count;
	pos.z /= count;
	Waypoint *way = reinterpret_cast<ScriptActionsTerrainView *>(TheTerrainLogic)->getClosestWaypointOnPath(&pos, waypointPathLabel);
	if (!way)
		return;
	if (flag)
		theGroup->rva0036FB57(way, CMD_FROM_SCRIPT, 0);
	else if (asTeam)
		((Rva0036FAF8 *)theGroup)->rva0036FAF8(way, CMD_FROM_SCRIPT, 0);
	else
		theGroup->rva0036F9FE(way, CMD_FROM_SCRIPT, 0);
}

// WB ScriptActions::doTeamAttackMoveFollowWaypoints @0x003BF4CF (303B): the
// same team-centre path search as doTeamFollowWaypoints, issuing the path
// commands in attack-move mode (trailing 1).
void ScriptActions::doTeamAttackMoveFollowWaypoints(const AsciiString &teamName,
	const AsciiString &waypointPathLabel, bool asTeam, bool flag)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;
	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;
	theTeam->getTeamAsAIGroup(theGroup);
	int count = 0;
	Coord3D pos;
	pos.x = pos.y = pos.z = 0;
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done();
		iter.advance()) {
		Object *obj = iter.cur();
		Coord3D objPos;
		copyCoord3D(objPos, obj->getPosition());
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z;
		count++;
	}
	if (count == 0)
		return;
	pos.x /= count;
	pos.y /= count;
	pos.z /= count;
	Waypoint *way = reinterpret_cast<ScriptActionsTerrainView *>(TheTerrainLogic)->getClosestWaypointOnPath(&pos, waypointPathLabel);
	if (!way)
		return;
	if (flag)
		theGroup->rva0036FB57(way, CMD_FROM_SCRIPT, 1);
	else if (asTeam)
		((Rva0036FAF8 *)theGroup)->rva0036FAF8(way, CMD_FROM_SCRIPT, 1);
	else
		theGroup->rva0036F9FE(way, CMD_FROM_SCRIPT, 1);
}

// WB ScriptActions::doPlaySoundEffectAtTeam @0x003BE8DC (255B): play the
// named event at the team's first member, or at the object a horde's inner
// container nominates (contain slot 0x7C, then its slot 0x110), for the
// local player.
class ThingTemplate;
class ScriptActionsKindOfView
{
public:
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad[0x108];
	unsigned char m_kindOf[0x20];
};

__forceinline bool Object::isKindOf(int t) const
{
	return ((const ScriptActionsKindOfView *)m_template)->isKindOf(t);
}

class ScriptActionsHordeView
{
public:
#define HORDE_SLOT(n) virtual void slot##n();
	HORDE_SLOT(0) HORDE_SLOT(1) HORDE_SLOT(2) HORDE_SLOT(3) HORDE_SLOT(4) HORDE_SLOT(5)
	HORDE_SLOT(6) HORDE_SLOT(7) HORDE_SLOT(8) HORDE_SLOT(9) HORDE_SLOT(10) HORDE_SLOT(11)
	HORDE_SLOT(12) HORDE_SLOT(13) HORDE_SLOT(14) HORDE_SLOT(15) HORDE_SLOT(16) HORDE_SLOT(17)
	HORDE_SLOT(18) HORDE_SLOT(19) HORDE_SLOT(20) HORDE_SLOT(21) HORDE_SLOT(22) HORDE_SLOT(23)
	HORDE_SLOT(24) HORDE_SLOT(25) HORDE_SLOT(26) HORDE_SLOT(27) HORDE_SLOT(28) HORDE_SLOT(29)
	HORDE_SLOT(30) HORDE_SLOT(31) HORDE_SLOT(32) HORDE_SLOT(33) HORDE_SLOT(34) HORDE_SLOT(35)
	HORDE_SLOT(36) HORDE_SLOT(37) HORDE_SLOT(38) HORDE_SLOT(39) HORDE_SLOT(40) HORDE_SLOT(41)
	HORDE_SLOT(42) HORDE_SLOT(43) HORDE_SLOT(44) HORDE_SLOT(45) HORDE_SLOT(46) HORDE_SLOT(47)
	HORDE_SLOT(48) HORDE_SLOT(49) HORDE_SLOT(50) HORDE_SLOT(51) HORDE_SLOT(52) HORDE_SLOT(53)
	HORDE_SLOT(54) HORDE_SLOT(55) HORDE_SLOT(56) HORDE_SLOT(57) HORDE_SLOT(58) HORDE_SLOT(59)
	HORDE_SLOT(60) HORDE_SLOT(61) HORDE_SLOT(62) HORDE_SLOT(63) HORDE_SLOT(64) HORDE_SLOT(65)
	HORDE_SLOT(66) HORDE_SLOT(67)
#undef HORDE_SLOT
	virtual Object *slot68(); // 0x110
};

class ScriptActionsContainView
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n();
	CONTAIN_SLOT(0) CONTAIN_SLOT(1) CONTAIN_SLOT(2) CONTAIN_SLOT(3) CONTAIN_SLOT(4)
	CONTAIN_SLOT(5) CONTAIN_SLOT(6) CONTAIN_SLOT(7) CONTAIN_SLOT(8) CONTAIN_SLOT(9)
	CONTAIN_SLOT(10) CONTAIN_SLOT(11) CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14)
	CONTAIN_SLOT(15) CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23) CONTAIN_SLOT(24)
	CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27) CONTAIN_SLOT(28) CONTAIN_SLOT(29)
	CONTAIN_SLOT(30)
#undef CONTAIN_SLOT
	virtual ScriptActionsHordeView *slot31(); // 0x7C
};

void ScriptActions::doPlaySoundEffectAtTeam(const AsciiString &sound, const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;
	Object *obj = theTeam->rva0039E8EB();
	if (!obj)
		return;
	if (obj->isKindOf(0x6D)) {
		ScriptActionsContainView *contain = obj->getContain();
		if (contain) {
			ScriptActionsHordeView *horde = contain->slot31();
			if (horde) {
				Object *member = horde->slot68();
				if (member)
					obj = member;
			}
		}
	}
	AudioEventInfoRef info = reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->findAudioEvent(sound);
	if (!info.m_info)
		return;
	BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4 *>(&info),
		obj->m_objectID);
	reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(ThePlayerList->m_localPlayer->m_playerIndex);
	reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->addAudioEvent(&event);
}

// WB/ZH ScriptActions::doForceObjectSelection @0x003C5AB8 (431B). BFME2 picks
// the newest team member of the named template as Zero Hour does, but only
// selects it (a 0x3E9 message carrying true and its id, then the in-game UI
// slot 0x108 with its drawable) when the local player controls it, and plays
// the sound whether or not the event was found.
class GameMessage
{
public:
	void appendBooleanArgument(bool arg);
	void appendObjectIDArgument(ObjectID arg);
};

class MessageStream
{
public:
#define STREAM_SLOT(n) virtual void slot##n();
	STREAM_SLOT(0) STREAM_SLOT(1) STREAM_SLOT(2) STREAM_SLOT(3) STREAM_SLOT(4)
	STREAM_SLOT(5) STREAM_SLOT(6) STREAM_SLOT(7) STREAM_SLOT(8) STREAM_SLOT(9)
	STREAM_SLOT(10) STREAM_SLOT(11) STREAM_SLOT(12) STREAM_SLOT(13) STREAM_SLOT(14)
	STREAM_SLOT(15) STREAM_SLOT(16) STREAM_SLOT(17)
#undef STREAM_SLOT
	virtual GameMessage *appendMessage(int type); // slot 0x48
};
extern MessageStream *TheMessageStream;

class InGameUI
{
public:
#define UI_SLOT(n) virtual void slot##n();
	UI_SLOT(0) UI_SLOT(1) UI_SLOT(2) UI_SLOT(3) UI_SLOT(4) UI_SLOT(5) UI_SLOT(6)
	UI_SLOT(7) UI_SLOT(8) UI_SLOT(9) UI_SLOT(10) UI_SLOT(11) UI_SLOT(12) UI_SLOT(13)
	UI_SLOT(14) UI_SLOT(15) UI_SLOT(16) UI_SLOT(17) UI_SLOT(18) UI_SLOT(19) UI_SLOT(20)
	UI_SLOT(21) UI_SLOT(22) UI_SLOT(23) UI_SLOT(24) UI_SLOT(25) UI_SLOT(26) UI_SLOT(27)
	UI_SLOT(28) UI_SLOT(29) UI_SLOT(30) UI_SLOT(31) UI_SLOT(32) UI_SLOT(33) UI_SLOT(34)
	UI_SLOT(35) UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39) UI_SLOT(40) UI_SLOT(41)
	UI_SLOT(42) UI_SLOT(43) UI_SLOT(44) UI_SLOT(45) UI_SLOT(46) UI_SLOT(47) UI_SLOT(48)
	UI_SLOT(49) UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53) UI_SLOT(54) UI_SLOT(55)
	UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59) UI_SLOT(60) UI_SLOT(61) UI_SLOT(62)
	UI_SLOT(63) UI_SLOT(64) UI_SLOT(65)
#undef UI_SLOT
	virtual void selectDrawable(Drawable *draw); // slot 0x108
};
extern InGameUI *TheInGameUI;

class View
{
public:
#define VIEW_SLOT(n) virtual void slot##n();
	VIEW_SLOT(0) VIEW_SLOT(1) VIEW_SLOT(2) VIEW_SLOT(3) VIEW_SLOT(4) VIEW_SLOT(5)
	VIEW_SLOT(6) VIEW_SLOT(7) VIEW_SLOT(8) VIEW_SLOT(9) VIEW_SLOT(10) VIEW_SLOT(11)
	VIEW_SLOT(12) VIEW_SLOT(13) VIEW_SLOT(14) VIEW_SLOT(15) VIEW_SLOT(16) VIEW_SLOT(17)
	VIEW_SLOT(18) VIEW_SLOT(19) VIEW_SLOT(20) VIEW_SLOT(21) VIEW_SLOT(22) VIEW_SLOT(23)
#undef VIEW_SLOT
	virtual void moveCameraTo(const Coord3D *pos, int frames, int shutter, bool orient,
		float easeIn, float easeOut); // slot 0x60
};
extern View *TheTacticalView;

struct ScriptActionsTemplateNameView
{
	unsigned char m_pad[0x64];
	AsciiString m_name;
	const AsciiString &getName() const { return m_name; }
};

void ScriptActions::doForceObjectSelection(const AsciiString &teamName, const AsciiString &objectType,
	bool centerInView, const AsciiString &audioToPlay)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	Object *bestGuess = 0;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done();
		iter.advance()) {
		Object *obj = iter.cur();
		const ScriptActionsTemplateNameView *tmpl = (const ScriptActionsTemplateNameView *)obj->m_template;
		if (tmpl && tmpl->getName() == objectType) {
			if (bestGuess == 0 || obj->m_objectID < bestGuess->m_objectID)
				bestGuess = obj;
		}
	}
	if (!(bestGuess && bestGuess->getDrawable()))
		return;
	Player *localPlayer = ThePlayerList->m_localPlayer;
	if (bestGuess->getControllingPlayer() == localPlayer) {
		GameMessage *msg = TheMessageStream->appendMessage(0x3E9);
		msg->appendBooleanArgument(true);
		msg->appendObjectIDArgument(bestGuess->m_objectID);
		TheInGameUI->selectDrawable(bestGuess->getDrawable());
	}
	AudioEventInfoRef info = reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->findAudioEvent(audioToPlay);
	BfmeAudioEventPrefix136 audioEvent(*reinterpret_cast<const OpaqueRefElement4 *>(&info), 0);
	reinterpret_cast<Rva0033F15DDwordSlot *>(&audioEvent)->set(ThePlayerList->m_localPlayer->m_playerIndex);
	reinterpret_cast<ScriptActionsAudioView *>(TheAudio)->addAudioEvent(&audioEvent);
	if (centerInView) {
		Coord3D pos;
		copyCoord3D(pos, bestGuess->getPosition());
		TheTacticalView->moveCameraTo(&pos, 0, 0, false, 0.0f, 0.0f);
	}
}

// WB ScriptActions::doBuildBuildingOnFoundation @0x003BCF2F (154B): when the
// named unit belongs to the current script player (with its +0x339 flag set)
// and that player may build the template (0x002AA00C), ask the unit's
// foundation behaviour (0x0028BCF4, vtable slot 0x1C) to build it at the
// unit's position.
class ScriptActionsFoundationView
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6();
	virtual void build(const ThingTemplate *tmpl, const Coord3D *pos, float angle,
		Player *owner, int a, int b); // slot 0x1C
};

void ScriptActions::doBuildBuildingOnFoundation(const AsciiString &buildingType, const AsciiString &unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit)
		return;
	Player *player = theUnit->getControllingPlayer();
	if (!player || !player->rva00339())
		return;
	if (player != TheScriptEngine->getCurrentPlayer())
		return;
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(buildingType);
	if (!tmpl)
		return;
	if (!player->rva002AA00C((ThingTemplate *)tmpl, 0))
		return;
	ScriptActionsFoundationView *pFoundation = (ScriptActionsFoundationView *)theUnit->rva0028BCF4();
	if (pFoundation)
		pFoundation->build(tmpl, theUnit->getPosition(), 0.0f, theUnit->getControllingPlayer(), 0, 0);
}

// WB/ZH ScriptActions::doTeamMoveToSkirmishApproachPath @0x003BF1FF (416B):
// from the team's centre, take the closest waypoint on the enemy's numbered
// approach path and move the team there through the BFME2 group move
// (0x00372571, a 0x20-byte argument block).
void ScriptActions::doTeamMoveToSkirmishApproachPath(const AsciiString &teamName,
	const AsciiString &waypointPathLabel)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;
	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;
	theTeam->getTeamAsAIGroup(theGroup);
	int count = 0;
	Coord3D pos;
	pos.x = pos.y = pos.z = 0;
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done();
		iter.advance()) {
		Object *obj = iter.cur();
		Coord3D objPos;
		copyCoord3D(objPos, obj->getPosition());
		pos.x += objPos.x;
		pos.y += objPos.y;
		pos.z += objPos.z;
		count++;
	}
	if (count == 0)
		return;
	pos.x /= count;
	pos.y /= count;
	pos.z /= count;
	Player *enemyPlayer = TheScriptEngine->getSkirmishEnemyPlayer();
	if (!enemyPlayer)
		return;
	int mpNdx = enemyPlayer->getMpStartIndex() + 1;
	AsciiString pathLabel;
	pathLabel.format("%s%d", waypointPathLabel.str(), mpNdx);
	Waypoint *way = reinterpret_cast<ScriptActionsTerrainView *>(TheTerrainLogic)->getClosestWaypointOnPath(&pos, pathLabel);
	if (!way)
		return;
	Rva00372571Params params;
	params.m_14 = -1;
	params.m_pos = ((ScriptWaypointView *)way)->getLocation();
	params.m_04 = false;
	params.m_08 = 0;
	params.m_0C = 0;
	params.m_10 = 0;
	params.m_18 = 0;
	params.m_1C = false;
	theGroup->groupMoveToPosition(&params, CMD_FROM_SCRIPT);
}

// WB 0x01014560 unnamed ScriptActions member @0x003C20CA (85B), the team
// sibling of doSetUnitReference: set a team reference either by the
// parameter's name (0x00208BCD) or to the team it names (0x00208B2C).
void ScriptActions::rva003C20CA(const AsciiString &reference, Parameter *team, bool byName)
{
	if (byName)
		TheScriptEngine->rva00208BCD(reference, team->getString());
	else
		TheScriptEngine->rva00208B2C(reference, TheScriptEngine->getTeamNamed(team->getString(), false));
}

// WB 0x010181A0 unnamed ScriptActions member @0x003C606C (124B): for the
// player a parameter names, run Player 0x002ABA9B; without the flag, also
// hand Player 0x002ACEDF every KindOf-7 template (TheThingFactory list at
// +0x0C, linked through +0x484) whose side (+0x6C) is the player's (+0x58).
struct ScriptActionsTemplateListView
{
	unsigned char m_pad000[0x6C];
	AsciiString m_side;
	unsigned char m_pad070[0x108 - 0x70];
	unsigned char m_kindOf[0x484 - 0x108];
	ScriptActionsTemplateListView *m_next;
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }
};

void ScriptActions::rva003C606C(Parameter *playerParam, bool flag)
{
	int mask = TheScriptEngine->rva00357475(playerParam->getString(), 0);
	if (!mask)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player)
		return;
	if (flag) {
		player->rva002ABA9B();
	} else {
		ScriptActionsTemplateListView *tmpl = *(ScriptActionsTemplateListView **)((unsigned char *)TheThingFactory + 0x0C);
		player->rva002ABA9B();
		for (; tmpl; tmpl = tmpl->m_next) {
			if (tmpl->isKindOf(7) && tmpl->m_side == player->m_side)
				((Rva002ABFA0 *)player)->rva002ACEDF((void *)tmpl);
		}
	}
}

// WB 0x01014BA0 unnamed ScriptActions member @0x003C49AE (194B): when the
// first KindOf-0x33 member of one team has an upgrade (TheUpgradeCenter
// 0x0026F0F0 on its +0x284) the other team accepts (0x0039E8FF), fire the
// SpecialAbilityGiveUpgrade power from it at the other team's first member.
class SpecialPowerTemplate;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};
extern SpecialPowerStore *TheSpecialPowerStore;

class Rva0026F0F0
{
public:
	void *rva0026F0F0(const void *key);
};
class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;

void ScriptActions::rva003C49AE(Parameter *srcTeamParam, Parameter *dstTeamParam)
{
	Team *srcTeam = TheScriptEngine->getTeamNamed(srcTeamParam->getString(), false);
	Team *dstTeam = TheScriptEngine->getTeamNamed(dstTeamParam->getString(), false);
	if (!srcTeam || !dstTeam)
		return;
	Object *giver = srcTeam->rva0039E968(0x33);
	if (!giver)
		return;
	void *upgrade = ((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0((const void *)((char *)giver + 0x284));
	if (!upgrade)
		return;
	if (!dstTeam->rva0039E8FF((int)upgrade))
		return;
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate("SpecialAbilityGiveUpgrade");
	if (!power)
		return;
	giver->doSpecialPowerAtObject(power, dstTeam->rva0039E8EB(), 0x40000, 0);
}

// WB ScriptActions::doEnablePlanningMode @0x003BD424 (11B): forward the flag to
// the Palantir (WB asserts ThePalantir != NULL; the global at 0x009FF028 is the
// Palantir by that assert and the call into its SetPlanningModeEnabled).
class Palantir
{
public:
	void SetPlanningModeEnabled(unsigned char enabled);
};
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

void ScriptActions::doEnablePlanningMode(unsigned char enable)
{
	((Palantir *)theRadarWindowOverrideSource)->SetPlanningModeEnabled(enable);
}

static __declspec(noinline) void rva003C0CEE(Object *obj, int which, bool on)
{
	unsigned int bit;
	switch (which) {
	case 1:
		bit = 0xB8;
		break;
	case 2:
		bit = 0xB9;
		break;
	case 3:
		bit = 0xBA;
		break;
	case 4:
		bit = 0xBB;
		break;
	default:
		bit = 0xB8;
		break;
	}
	if (on)
		obj->setModelConditionState(bit);
	else
		obj->clearModelConditionState(bit);
}

void ScriptActions::rva003C0D6A(const AsciiString &unitName, int which, bool on)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (obj)
		rva003C0CEE(obj, which, on);
}

void ScriptActions::rva003C0D90(const AsciiString &teamName, int which, bool on)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (obj)
			rva003C0CEE(obj, which, on);
	}
}

// WB 0x010147A0 unnamed ScriptActions member @0x003C4751 (605B): the giving
// team's first KindOf-0x33 member fires SpecialAbilityGiveUpgrade at the
// nearest unit, nominated by a horde (KindOf 0x6D) member's 0x0028C197 module
// (slot 0x110) that lacks the upgrade (slot 0xB4), in any other team of the
// same player that accepts the upgrade. As in WorldBuilder the offset is
// built from a Coord3D compared (not assigned) with the giver's position.
class ScriptActionsHordeModuleView

{
 public:
#define HM_SLOT(n) virtual void slot##n();
 HM_SLOT(0) HM_SLOT(1) HM_SLOT(2) HM_SLOT(3) HM_SLOT(4) HM_SLOT(5) HM_SLOT(6)
 HM_SLOT(7) HM_SLOT(8) HM_SLOT(9) HM_SLOT(10) HM_SLOT(11) HM_SLOT(12) HM_SLOT(13)
 HM_SLOT(14) HM_SLOT(15) HM_SLOT(16) HM_SLOT(17) HM_SLOT(18) HM_SLOT(19) HM_SLOT(20)
 HM_SLOT(21) HM_SLOT(22) HM_SLOT(23) HM_SLOT(24) HM_SLOT(25) HM_SLOT(26) HM_SLOT(27)
 HM_SLOT(28) HM_SLOT(29) HM_SLOT(30) HM_SLOT(31) HM_SLOT(32) HM_SLOT(33) HM_SLOT(34)
 HM_SLOT(35) HM_SLOT(36) HM_SLOT(37) HM_SLOT(38) HM_SLOT(39) HM_SLOT(40) HM_SLOT(41)
 HM_SLOT(42) HM_SLOT(43) HM_SLOT(44)
 virtual bool hasUpgrade(const void *upgrade);
// 0xB4
 HM_SLOT(46) HM_SLOT(47) HM_SLOT(48) HM_SLOT(49) HM_SLOT(50) HM_SLOT(51) HM_SLOT(52)
 HM_SLOT(53) HM_SLOT(54) HM_SLOT(55) HM_SLOT(56) HM_SLOT(57) HM_SLOT(58) HM_SLOT(59)
 HM_SLOT(60) HM_SLOT(61) HM_SLOT(62) HM_SLOT(63) HM_SLOT(64) HM_SLOT(65) HM_SLOT(66)
 HM_SLOT(67)
#undef HM_SLOT
 virtual Object *getTarget();
// 0x110
 
}
;
void ScriptActions::rva003C4751(Parameter *teamParam)

{
 Team *theTeam = TheScriptEngine->getTeamNamed(teamParam->getString(), false);
 if (!theTeam)
 return;
 const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate("SpecialAbilityGiveUpgrade");
 if (!power)
 return;
 Object *giver = theTeam->rva0039E968(0x33);
 if (!giver)
 return;
 void *upgrade = ((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0((unsigned char *)giver + 0x284);
 if (!upgrade)
 return;
 Player *player = giver->getControllingPlayer();
 if (!player)
 return;
 
 {
  Object *best = 0;
  float bestDist = 3.4028235e+38f;
  // Keep the initial node value separate from the loop iterator: the
  // native copy completes giverPos before spilling the iterator home.
  PlayerTeamNode *first = player->m_playerTeamPrototypes->m_next;
  Coord3D giverPos;
  giverPos.x = giver->getPosition()->x;
  giverPos.y = giver->getPosition()->y;
  giverPos.z = giver->getPosition()->z;
  PlayerTeamNode *it = first;
  Coord3D diff;
  for (; it != player->m_playerTeamPrototypes; it = it->m_next) 
  {
   for (DLINK_ITERATOR<Team> teams = it->m_value->iterate_TeamInstanceList();
   !teams.done(); teams.advance()) 
   {
    Team *team = teams.cur();
    if (!team || theTeam == team)
    continue;
    if (!team->rva0039E8FF((int)upgrade))
    continue;
    Object *obj;
    for (DLINK_ITERATOR<Object> members = team->iterate_TeamMemberList(); (obj = members.cur()) != 0;
    members.advance()) 
    {
     _ReadWriteBarrier();
     if (!obj->isKindOf(0x6D))
     continue;
     ScriptActionsHordeModuleView *module = (ScriptActionsHordeModuleView *)obj->rva0028C197();
     if (!module || module->hasUpgrade(upgrade))
     continue;
     Coord3D memberPos;
     memberPos.x = obj->getPosition()->x;
     memberPos.y = obj->getPosition()->y;
     memberPos.z = obj->getPosition()->z;
     diff == giverPos;
     diff.x -= memberPos.x;
     diff.y -= memberPos.y;
     diff.z -= memberPos.z;
     float dist = diff.length();
     Object *target = module->getTarget();
     if (target) 
     {
      if (!best) 
      {
       best = target;
       bestDist = dist;
       
      }
      else if (dist < bestDist) 
      {
       best = target;
       bestDist = dist;
       
      }
      
     }
     
    }
    
   }
   
  }
  if (best)
  giver->doSpecialPowerAtObject(power, best, 0x40000, false);
  
 }
 
}


class UpgradeTemplate;
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};
struct Rva00045411BitSet
{
	unsigned m_bits[7];
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
template<int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;	// 0x0026F26D
};
class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();	// 0x003955DA
	Object *rva00397429(const AsciiString &name);	// 0x00397429
};
class ObjectTypes
{
public:
	unsigned int getListSize() const { return m_end - m_begin; }
	AsciiString getNthInList(unsigned int index) const;	// 0x002041AC
private:
	char m_pad00[8];
	AsciiString *m_begin;	// +0x08
	AsciiString *m_end;	// +0x0C
};

// Native003C739D..003C75C2 and WB1017470 put upgrade/name application after the search loop.
void ScriptActions::rva003C739D(Parameter *castleName, Parameter *upgradeParm, Parameter *typeParm,
	Parameter *areaParm, Parameter *nameParm)
{
	Object *castle = TheScriptEngine->getUnitNamed(castleName);
	if (!castle)
		return;
	CastleBehavior *behavior = (CastleBehavior *)castle->findModule(CastleBehavior::rva0003955DA());
	if (!behavior)
		return;
	Object *center = behavior->rva00397429(areaParm->getString());
	if (!center)
		return;
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeParm->getString());
	if (!upgrade)
		return;
	const ThingTemplate *templ = 0;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(typeParm->getString());
	if (!types) {
		templ = TheThingFactory->findTemplate(typeParm->getString());
		if (!templ)
			return;
	}
	Object *obj = 0;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(center->getPosition(), 1000.0f, 0,
		Rva0004584D((const BfmeFixedStorage0004543D &)Rva00045411BitSet(0, 7), *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)
			.link(&Rva0026119DFilter()), 1);
	while ((obj = hits.next()) != 0) {
		if (!obj->affectedByUpgrade(upgrade))
			continue;
		if (obj->hasUpgrade(upgrade))
			continue;
		const ThingTemplate *objTemplate = obj->getTemplate();
		if (templ) {
			if (!templ->isEquivalentTo(objTemplate))
				continue;
		} else if (types) {
			bool matched = false;
			for (unsigned int i = 0; i < types->getListSize(); ++i) {
				const ThingTemplate *candidate = TheThingFactory->findTemplate(types->getNthInList(i));
				if (candidate && candidate->isEquivalentTo(objTemplate)) {
					matched = true;
					break;
				}
			}
			if (!matched)
				continue;
		}
		break;
	}
	if (!obj)
		return;
	obj->rva00293077(upgrade);
	AsciiString name = nameParm->getString();
	if (!name.isEmpty())
		TheScriptEngine->rva00208968(name, obj);
}

// ZH doSetBorderShroud supplies the purpose and unsigned-byte alpha contract.
// WB1005DC0 independently confirms the two branches and display virtual call;
// retail3BBB51 supplies alpha offsets BE8/BEA and display slot138.
class Display;
extern Display *TheDisplay;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct ScriptShroudAlphaView
{
 char pad[0xBE8];
 unsigned char clearAlpha, fogAlpha, shroudAlpha;
};
class ScriptShroudDisplayView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
 virtual void setBorderShroudLevel(unsigned char);
};
void ScriptActions::doSetBorderShroud(bool setting)
{
 if (setting)
  ((ScriptShroudDisplayView *)TheDisplay)->setBorderShroudLevel(((ScriptShroudAlphaView *)TheWritableGlobalData)->shroudAlpha);
 else
  ((ScriptShroudDisplayView *)TheDisplay)->setBorderShroudLevel(((ScriptShroudAlphaView *)TheWritableGlobalData)->clearAlpha);
}

// WB100B3C0 proves branch-local filter temporaries and the fallback return.
// Keeping the static helper and its callers together reproduces the native
// private object-in-ESI convention without a two-argument declaration.
// vftable 0x00C1FDEC, allow 0x00261750: +0x08 a thing template, +0x0C whether a match allows.
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *tmpl, bool match) : m_template(tmpl), m_match(match) {}
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template;
	bool m_match;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C1FE34, allow 0x002614BC: +0x08 the source object, +0x0C the command button,
// +0x10 whether a valid target allows, +0x14 the command source.
class Rva002614BCFilter : public Rva000421C8
{
public:
	Rva002614BCFilter(Object *source, const CommandButton *button, bool match, int cmdSource)
		: m_source(source), m_button(button), m_match(match), m_cmdSource(cmdSource) {}
	virtual bool allow(Object *obj);
	Object *m_source;
	const CommandButton *m_button;
	bool m_match;
	int m_cmdSource;
};

class CommandButton
{
public:
	bool isReady(const Object *obj) const;	// 0x0035B069
	bool rva003BDCCA() const { return (m_options >> 5) & 1; }
	char m_pad00[0x1C];
	unsigned int m_options;	// +0x1C
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);	// 0x0031BE3C
};
extern ControlBar *TheControlBar;

// Native 0x27F108 takes four 32-bit argument slots and returns a result word the caller only
// tests for zero (see Rva004389AENearbyCheck.cpp).
class BfmeThingCME
{
public:
	int rva0027F108(void *position, float radius, int flag, int unused);
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;


#define REALLY_FAR (100000 * 10.0f)
static __declspec(noinline) void rva003BE11C(Object *obj, const ThingTemplate *tmpl, const CommandButton *button)
{
	if (button->rva003BDCCA()) {
		Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva00261750Filter(tmpl, true).link(&Rva002611BFFilter(obj)));
		if (target)
			obj->doCommandButtonAtPosition(button, target->getPosition(), 1, 0);
	} else {
		Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva00261750Filter(tmpl, true).link(Rva002614BCFilter(obj, button, true, 1).link(&Rva002611BFFilter(obj))));
		if (!target) {
			if (tmpl->rva003BE11C94()) {
				int where = reinterpret_cast<BfmeThingCME *>(TheTerrainLogic)->rva0027F108(
					const_cast<Coord3D *>(obj->getPosition()), 10000000.0f, 1, 1);
				if (where)
					obj->doCommandButtonAtPosition(button, (const Coord3D *)where, 1, 0);
			}
			return;
		} else {
			obj->rva00297000(button, target, 1, 0);
		}
	}
}

void ScriptActions::rva003C42B9(Parameter *param, const AsciiString &a, const AsciiString &b)
{
	Object *unit = TheScriptEngine->getUnitNamed(param);
	if (unit == 0)
		return;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(b);
	const ThingTemplate *tmpl;
	if (types != 0) {
		Object *obj = rva003C24F0(unit->getPosition(), types, 0, false);
		if (obj == 0)
			return;
		tmpl = obj->m_template;
	} else {
		tmpl = TheThingFactory->findTemplate(b);
	}
	if (tmpl == 0)
		return;
	const CommandButton *button = TheControlBar->findCommandButton(a);
	if (button == 0)
		return;
	if (!button->isReady(unit))
		return;
	if (!unit->rva002922D9(button))
		return;
	rva003BE11C(unit, tmpl, button);
}


#undef REALLY_FAR

void ScriptActions::doTeamUseCommandButtonOnNearestObjectType(const AsciiString &teamName,
	const AsciiString &commandAbility, const AsciiString &objectType)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;
	const ThingTemplate *tmpl;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
	if (types) {
		Coord3D pos;
		Object *best = rva003C24F0(team->rva0039DA2A(&pos), types, 0, false);
		if (!best)
			return;
		tmpl = best->m_template;
	} else {
		tmpl = TheThingFactory->findTemplate(objectType);
	}
	if (!tmpl)
		return;
	// Keep the member walk in a sibling scope to the centroid temporary.
	// MSVC then shares their dead stack storage (retail 0x003C449C).
	{
		Object *member;
		DLINK_ITERATOR<Object> iter;
		for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			member = iter.cur();
			if (commandButton->isReady(member))
				rva003BE11C(member, tmpl, commandButton);
		}
	}
}
