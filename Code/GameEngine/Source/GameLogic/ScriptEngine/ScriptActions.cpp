// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ScriptActions members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv) and Zero Hour's ScriptActions.cpp; retail
// supplies the bytes. Only declared here: members other units row
// (doFlashSpellStoreButton, doPlayerForceEmotion,
// doSetUnitReferenceToHomeBaseOfPlayer, doCreateObject, 0x003C0E87), members
// recovered in other units (createUnitOnTeamAt,
// doSetCounterToThreatFinderThreat, doCreateUnitRevivalEntry and the two
// sequential-script starters) and members
// not yet matched (doTransferTeamToPlayer, 0x003C4751).
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "Common/BfmeAudioEventPrefix136.h"

enum EmotionType
{
	EMOTION_INVALID = -1
};

class Parameter;

class ScriptActions
{
public:
	void doFlashSpellStoreButton(int seconds);
protected:
	void doPlaySoundEffect(const AsciiString &sound);
	void doPlaySoundEffectAt(const AsciiString &sound, const AsciiString &waypoint);
	void doSoundPlayFromNamed(const AsciiString &sound, const AsciiString &unitName);
	void doSpeechPlay(const AsciiString &speechName, bool allowOverlap);
	void doPlayerForceEmotion(Parameter *player, EmotionType emotion,
		float duration);
	void doSetCounterToThreatFinderThreat(const AsciiString &counterName,
		const AsciiString &threatFinderName, const AsciiString &relation,
		const AsciiString &playerName);
	void doCreateUnitRevivalEntry(const AsciiString &templateName,
		const AsciiString &playerName, int level);
	void doIdleAllPlayerUnits(const AsciiString &playerName);
	void doResumeSupplyTruckingForIdleUnits(const AsciiString &playerName);
	void doCreateObject(const AsciiString &objectName, const AsciiString &thingName,
		const AsciiString &teamName, struct Coord3D *pos, float angle);
	void createUnitOnTeamAt(const AsciiString &unitName, const AsciiString &objType,
		const AsciiString &teamName, const AsciiString &waypoint);
	void doSetUnitReference(const AsciiString &reference, Parameter *unit, bool byName);
	void doTeamFollowWaypoints(const AsciiString &teamName,
		const AsciiString &waypointPathLabel, bool asTeam, bool flag);
	void doTeamAttackMoveFollowWaypoints(const AsciiString &teamName,
		const AsciiString &waypointPathLabel, bool asTeam, bool flag);
	void doPlaySoundEffectAtTeam(const AsciiString &sound, const AsciiString &teamName);
	void doForceObjectSelection(const AsciiString &teamName, const AsciiString &objectType,
		bool centerInView, const AsciiString &audioToPlay);
	void doBuildBuildingOnFoundation(const AsciiString &templateName, const AsciiString &unitName);
	void doTeamMoveToSkirmishApproachPath(const AsciiString &teamName,
		const AsciiString &waypointPathLabel);
	void doTransferTeamToPlayer(const AsciiString &teamName, const AsciiString &playerName);
	void doTeamStartSequentialScript(const AsciiString &teamName,
		const AsciiString &scriptName, int loopVal);
	void rva003C20CA(const AsciiString &reference, Parameter *team, bool byName);
	void rva003C606C(Parameter *playerParam, bool flag);
	void rva003C0E87(const AsciiString &unitName, int value);
	void doUnitStartSequentialScript(const AsciiString &unitName,
		const AsciiString &scriptName, int loopVal);
	void rva003C0F44(const AsciiString &teamName, int mode, int value);
	void rva003C49AE(Parameter *srcTeamParam, Parameter *dstTeamParam);
	void rva003C4751(Parameter *teamParam);
	void doSetUnitReferenceToHomeBaseOfPlayer(const AsciiString &playerName,
		const AsciiString &unitReference, bool flag);
};


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
	unsigned char m_pad58[0x5C - 0x58];
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
	void rva002ACEDF(const class ThingTemplate *tmpl);
	const AsciiString &getSide() const { return *(const AsciiString *)((const unsigned char *)this + 0x58); }
	int getPlayerIndex() const { return m_playerIndex; }
	int getMpStartIndex() const { return *(const int *)((const unsigned char *)this + 0x2E0); }
	void setUnitsShouldIdleOrResume(bool idle);
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

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
	void rva00208968(const AsciiString &name, class Object *obj);
	void AppendDebugMessage(const AsciiString &msg, bool b);
	void addObjectToCache(class Object *obj, const AsciiString &name);
	class Object *getUnitNamed(const AsciiString &unitName);
	class Object *getUnitNamed(Parameter *unit);
	Player *getCurrentPlayer();
	Player *getSkirmishEnemyPlayer();
	class Script *rva00357130(const AsciiString &scriptName, AsciiString *objectName);
	void appendSequentialScript(const class SequentialScript *seqScript);
	void rva00208A09(const AsciiString &reference, AsciiString name);
	void rva00208BCD(const AsciiString &reference, AsciiString name);
	void rva00208B2C(const AsciiString &reference, class Team *team);
	class ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
	class Team *getTeamNamed(AsciiString name, bool b);
	bool didUnitExist(const AsciiString &name);
	void rva00357960(const AsciiString &name, class Object *obj);
protected:
	friend class ScriptActions;
	struct ScriptCounter *bfmeCounter(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;

enum ObjectID { INVALID_OBJECT_ID = 0 };

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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
	unsigned char m_pad00[0x04];
	const class ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_objectID;
	unsigned char m_pad78[0x88 - 0x78];
	AsciiString m_name;
	unsigned char m_pad8C[0x250 - 0x8C];
	class ScriptActionsContainView *m_contain;
	unsigned char m_pad254[0x438 - 0x254];
	unsigned char m_privateStatus;
	Player *getControllingPlayer() const;
	void rva0028ECA8(int index, float value, int arg);
	void setName(const AsciiString &name) { m_name = name; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	const Coord3D *getPosition() const { return &m_position; }
	__forceinline bool isKindOf(int t) const;
	ScriptActionsContainView *getContain() const { return m_contain; }
	void rva0028FC18();
	void *rva0028BCF4() const;
	void *rva0028C197() const;
	void updateUpgradeModules();
	void rva0028E01F(const class SpecialPowerTemplate *power, Object *target, int flags, int arg);
	int getIndicatorColor() const;
	int getNightIndicatorColor() const;
	void rva0028BAC0();
	void rva0028DCC4();
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

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

class Team;

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva0039E5B9(struct Coord3D *pos);
	void getTeamAsAIGroup(class AIGroup *group);
	class Object *rva0039E8EB();
	void setControllingPlayer(Player *newController);
	int rva0039DD12(int (*func)(class Object *, void *), void *userData) const;
	bool hasAnyObjects(bool ignoreBuildings);
	class Object *rva0039E968(int kindOf);
	bool rva0039E8FF(const void *upgrade);
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
	int rva0033B479() const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	class Object *newObject(const ThingTemplate *tmplate, class Team *team,
		const struct CreateMask *mask, bool flag);
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
	void rva00372571(Rva00372571Params *params, int source);
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

void ScriptActions::doBuildBuildingOnFoundation(const AsciiString &templateName, const AsciiString &unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit)
		return;
	Player *player = theUnit->getControllingPlayer();
	if (!player || !player->rva00339())
		return;
	if (player != TheScriptEngine->getCurrentPlayer())
		return;
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(templateName);
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
	theGroup->rva00372571(&params, CMD_FROM_SCRIPT);
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
			if (tmpl->isKindOf(7) && tmpl->m_side == player->getSide())
				player->rva002ACEDF((const ThingTemplate *)tmpl);
		}
	}
}

// WB 0x0100F1D0 unnamed ScriptActions member @0x003C0F44 (166B): attack-move
// a team; in modes 3 and 4 toward the nearest shroud group of its enemies
// (TheShroudManager 0x00739820, relationship 4) from the group centre.
// Other modes leave the target as WorldBuilder's debug build initialised it.
class ShroudManager
{
public:
	void rva00739820(const Coord3D *from, int playerMask, int a, int value, Coord3D *out);
};
extern ShroudManager *TheShroudManager;

void ScriptActions::rva003C0F44(const AsciiString &teamName, int mode, int value)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;
	AIGroup *theGroup = TheAI->createGroup();
	theTeam->getTeamAsAIGroup(theGroup);
	Player *player = theTeam->getControllingPlayer();
	if (!player)
		return;
	Coord3D target;
	Coord3D center;
	theGroup->getCenter(&center);
	if (mode == 3 || mode == 4) {
		TheShroudManager->rva00739820(&center,
			ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(), 4, false),
			0, value, &target);
	}
	theGroup->groupAttackMoveToPosition(&target, 0x7FFFFFFF, CMD_FROM_SCRIPT);
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
extern Rva0026F0F0 *TheUpgradeCenterLookup;

void ScriptActions::rva003C49AE(Parameter *srcTeamParam, Parameter *dstTeamParam)
{
	Team *srcTeam = TheScriptEngine->getTeamNamed(srcTeamParam->getString(), false);
	Team *dstTeam = TheScriptEngine->getTeamNamed(dstTeamParam->getString(), false);
	if (!srcTeam || !dstTeam)
		return;
	Object *giver = srcTeam->rva0039E968(0x33);
	if (!giver)
		return;
	void *upgrade = TheUpgradeCenterLookup->rva0026F0F0((unsigned char *)giver + 0x284);
	if (!upgrade)
		return;
	if (!dstTeam->rva0039E8FF(upgrade))
		return;
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate("SpecialAbilityGiveUpgrade");
	if (!power)
		return;
	giver->rva0028E01F(power, dstTeam->rva0039E8EB(), 0x40000, 0);
}
