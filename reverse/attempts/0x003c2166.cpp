// ?rva003C2166@ScriptActions@@IAEXABVAsciiString@@H0@Z
// partial score=0.96 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
// WB ScriptActions::doFlashSpellStoreButton; target is the guarded index-0
// forwarding sibling of matched index-1 and index-2 wrappers at 0x003BD444
// and 0x003BD459.
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
	void rva003C2166(const AsciiString &teamName, int count, const AsciiString &objectTypeName);
	void doSetUnitReferenceToHomeBaseOfPlayer(const AsciiString &playerName,
		const AsciiString &unitReference, bool flag);
};

class Rva002D381D
{
public:
	void rva002D381D(int seconds);
};

extern class Rva002D3627Host *TheRva002D3627Host;

#define TheSpellStoreTimer (*(Rva002D381D **)&TheRva002D3627Host)

void ScriptActions::doFlashSpellStoreButton(int seconds)
{
	if (seconds >= 0)
		TheSpellStoreTimer->rva002D381D(seconds);
}

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

// WB ScriptActions::doPlayerForceEmotion @0x003C37C0 (206B), matched to
// WorldBuilder's 409B body. The WB body bounds the emotion to [0, 12), gets a
// player mask from Parameter's +0x10 string, and walks each selected player's
// team prototypes, team instances, and team members. Retail uses the rowed
// mask, team-member iterator, and Object emotion forwarders.
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
extern ScriptEngine *g_Va009FE16C;

enum ObjectID { INVALID_OBJECT_ID = 0 };

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}

	float x, y, z;
};

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
	void updateUpgradeModules();
	int getIndicatorColor() const;
	int getNightIndicatorColor() const;
	void rva0028BAC0();
	void rva0028DCC4();
	Object *getContainedBy() const { return *(Object *const *)((const unsigned char *)this + 0x274); }
	class AIUpdateInterface *getAIUpdateInterface() const { return *(AIUpdateInterface *const *)((const unsigned char *)this + 0x258); }
};

void ScriptActions::doSoundPlayFromNamed(const AsciiString &sound,
	const AsciiString &unitName)
{
	Object *unit = g_Va009FE16C->getUnitNamed(unitName);
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
	bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
};

template<class OBJCLASS>
class Rva001705A0DlinkIterator
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
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

void ScriptActions::doPlayerForceEmotion(Parameter *player,
	EmotionType emotion, float duration)
{
	if (emotion < 0 || emotion >= 12)
		return;

	int mask = g_Va009FE16C->rva00357475(player->getString(), 0);
	while (mask != 0) {
		Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (!thePlayer)
			continue;

		for (PlayerTeamNode *it = thePlayer->m_playerTeamPrototypes->m_next;
			it != thePlayer->m_playerTeamPrototypes; it = it->m_next) {
			TeamPrototype *prototype = it->m_value;
			for (DLINK_ITERATOR<Team> teams = prototype->iterate_TeamInstanceList();
				!teams.done(); teams.advance()) {
				Team *team = teams.cur();
				if (!team)
					continue;

				DLINK_ITERATOR<Object> members = team->iterate_TeamMemberList();
				for (; !members.done();
					((Rva001705A0DlinkIterator<Object> *)&members)->advance()) {
					Object *obj = members.cur();
					if (!obj)
						continue;
					obj->rva0028ECA8(emotion, duration, 0);
				}
			}
		}
	}
}

// WB ScriptActions::doSetUnitReferenceToHomeBaseOfPlayer @0x003BCE69 (146B):
// over every player the name selects, take each player's candidate object
// and keep the one the unnamed comparator 0x002AA497 ranks first, then bind
// the unit reference to it.
int __cdecl rva002AA497(int a, int b);

void ScriptActions::doSetUnitReferenceToHomeBaseOfPlayer(const AsciiString &playerName,
	const AsciiString &unitReference, bool flag)
{
	int mask = g_Va009FE16C->rva00357475(playerName, 0);
	Object *best = 0;
	int bestKey = 0;
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player)
			continue;
		int key;
		Object *candidate = (Object *)player->rva002ABCF0(flag, &key);
		if (!key)
			continue;
		if (!bestKey || rva002AA497(bestKey, key) < 0) {
			bestKey = key;
			best = candidate;
		}
	}
	if (best) {
		g_Va009FE16C->rva00208968(unitReference, best);
		g_Va009FE16C->addObjectToCache(best, unitReference);
	}
}

// WB ScriptActions::doSetCounterToThreatFinderThreat @0x003C5E10 (267B):
// set the named counter to the named threat finder's threat level for the
// player's enemies or allies, or log a script warning if no such finder.
struct ScriptCounter
{
	int value;
};

struct ThreatInfo
{
	ThreatInfo();
	float m_threat;
	unsigned char m_rest[0x40];
};

class ThreatFinder
{
public:
	ThreatInfo getThreatForPlayer(Player *player, int relation, Player *other);
};

// ThreatFinderManager's by-name lookup is ICF-folded with ArmorStore's
// (0x0041F474): both are a NameKey hash_map find.
class ArmorStore
{
public:
	const class ArmorTemplate *rva0041F474(const AsciiString &name) const;
};
class ThreatFinderManager;
extern ThreatFinderManager *TheThreatFinderManager;

void ScriptActions::doSetCounterToThreatFinderThreat(const AsciiString &counterName,
	const AsciiString &threatFinderName, const AsciiString &relation,
	const AsciiString &playerName)
{
	ScriptCounter *counter = g_Va009FE16C->bfmeCounter(counterName);
	if (!counter)
		return;
	int mask = g_Va009FE16C->rva00357475(playerName, 0);
	if (!mask)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player)
		return;
	int relationType;
	if (relation.compare("Enemies") == 0)
		relationType = 0;
	else if (relation.compare("Allies") == 0)
		relationType = 1;
	else
		return;
	ThreatFinder *finder = (ThreatFinder *)((const ArmorStore *)TheThreatFinderManager)->rva0041F474(threatFinderName);
	if (finder) {
		counter->value = (int)finder->getThreatForPlayer(player, relationType, 0).m_threat;
	} else {
		AsciiString msg = "WARNING - Threat Finder not found during script execution: ";
		msg.concat(threatFinderName);
		msg.concat(".");
		g_Va009FE16C->AppendDebugMessage(msg, false);
	}
}

// WB ScriptActions::doCreateUnitRevivalEntry @0x003C62F4 (323B): build a
// revival record for the named template, take its experience values from
// the requested level (or the template default with level -1 or no such
// level) and hand it to the player's revival tracker (Player +0x738).
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

struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}

	void *m_list;
	void *m_iter;
};

class ExperienceLevelStore
{
public:
	ExperienceLevelHandle rva00288E21(const ThingTemplate *tmpl, int level) const;
	int GetRequiredExperience(ExperienceLevelHandle level) const;
	int GetLevelRank(ExperienceLevelHandle level) const;
};
extern ExperienceLevelStore *TheExperienceLevelStore;

struct Rva002E2D10Record
{
	Rva002E2D10Record(const ThingTemplate *tmpl);
	~Rva002E2D10Record();

	unsigned char m_pad00[8];
	float m_requiredExperience;
	int m_rank;
	int m_rank2;
	unsigned char m_pad14[0xD8 - 0x14];
};

class UnitRevivalTracker
{
public:
	void addRevivableUnit(const Rva002E2D10Record &item, Player *player);
};

void ScriptActions::doCreateUnitRevivalEntry(const AsciiString &templateName,
	const AsciiString &playerName, int level)
{
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(templateName);
	if (!tmpl)
		return;
	int mask = g_Va009FE16C->rva00357475(playerName, 0);
	Player *player = ThePlayerList->getEachPlayerFromMask(mask);
	if (!player)
		return;
	UnitRevivalTracker *tracker = player->getUnitRevivalTracker();
	if (!tracker)
		return;
	Rva002E2D10Record entry(tmpl);
	if (level != -1) {
		ExperienceLevelHandle handle = TheExperienceLevelStore->rva00288E21(tmpl, level);
		if (handle.m_list) {
			entry.m_requiredExperience = (float)TheExperienceLevelStore->GetRequiredExperience(handle);
			entry.m_rank = TheExperienceLevelStore->GetLevelRank(handle);
			entry.m_rank2 = TheExperienceLevelStore->GetLevelRank(handle);
		} else {
			entry.m_rank = tmpl->rva0033B479();
		}
	} else {
		entry.m_rank = tmpl->rva0033B479();
	}
	tracker->addRevivableUnit(entry, player);
}

// WB/ZH ScriptActions::doIdleAllPlayerUnits @0x003BBB7E (114B) and
// doResumeSupplyTruckingForIdleUnits @0x003BBBF0 (113B), identified by their
// WorldBuilder DEBUG_LOG strings. BFME2 resolves the name to a player mask
// and applies the setting to every selected player; with no match it falls
// back to every human player, as Zero Hour does.
enum { PLAYER_HUMAN = 0 };

void ScriptActions::doIdleAllPlayerUnits(const AsciiString &playerName)
{
	int mask = g_Va009FE16C->rva00357475(playerName, 0);
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
	int mask = g_Va009FE16C->rva00357475(playerName, 0);
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

// WB/ZH ScriptActions::doCreateObject @0x003C4EC3 (479B). BFME2 differs from
// Zero Hour in looking up the old unit by value (0x00358752), creating no
// missing team, passing a zeroed create mask to the four-argument newObject,
// naming the cache entry with an empty string, and ending with the object
// member 0x0028FC18 instead of the blast-crater footprint.
class Team;
#include <string.h>

struct CreateMask
{
	CreateMask() { memset(m_bits, 0, sizeof(m_bits)); }

	unsigned int m_bits[4];
};


class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);
};

void ScriptActions::doCreateObject(const AsciiString &objectName, const AsciiString &thingName,
	const AsciiString &teamName, Coord3D *pos, float angle)
{
	Object *pOldObj = 0;
	if (objectName != AsciiString::TheEmptyString) {
		pOldObj = ((Rva00358752Opaque *)g_Va009FE16C)->lookupUnitByValue(objectName);
		if (pOldObj && !pOldObj->isEffectivelyDead()) {
			AsciiString str = "WARNING - Object with name ";
			str.concat(objectName);
			str.concat(" already exists. Failed Create.");
			g_Va009FE16C->AppendDebugMessage(str, false);
			return;
		}
	}
	Team *theTeam = g_Va009FE16C->getTeamNamed(teamName, true);
	if (!theTeam) {
		g_Va009FE16C->AppendDebugMessage("***WARNING - Team not found:***", false);
		g_Va009FE16C->AppendDebugMessage(teamName, true);
		return;
	}
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(thingName);
	if (thingTemplate) {
		Object *obj = TheThingFactory->newObject(thingTemplate, theTeam, &CreateMask(), false);
		if (obj) {
			if (objectName != AsciiString::TheEmptyString) {
				obj->setName(objectName);
				if (pOldObj || g_Va009FE16C->didUnitExist(objectName))
					g_Va009FE16C->rva00357960(objectName, obj);
				else
					g_Va009FE16C->addObjectToCache(obj, "");
			}
			obj->setOrientation(angle);
			obj->setPosition(pos);
			obj->rva0028FC18();
		}
	}
}

// WB/ZH ScriptActions::createUnitOnTeamAt @0x003C50A2 (658B). BFME2 accepts
// an object type as the location as well as a waypoint: with no such
// waypoint, the closest object of that template to the team's centre
// (Team 0x0039E5B9, PartitionManager::getClosestObject over a template
// filter) is used. As in doCreateObject the old unit is looked up by value,
// a missing team is not created and the object ends with 0x0028FC18.
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00C1FDEC, allow 0x00261750 (Zero Hour's PartitionFilterThing).
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *tmpl, bool match) : m_template(tmpl), m_match(match) {}
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template;
	bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc, Rva000421C8 *filters);
};
extern PartitionManager *ThePartitionManager;

struct ScriptWaypointView
{
	unsigned char m_pad00[0x0C];
	Coord3D m_location;
	const Coord3D *getLocation() const { return &m_location; }
};

void ScriptActions::createUnitOnTeamAt(const AsciiString &unitName, const AsciiString &objType,
	const AsciiString &teamName, const AsciiString &waypoint)
{
	Object *pOldObj = ((Rva00358752Opaque *)g_Va009FE16C)->lookupUnitByValue(unitName);
	if (pOldObj && !pOldObj->isEffectivelyDead()) {
		AsciiString str = "WARNING - Object with name ";
		str.concat(unitName);
		str.concat(" already exists. Failed Create.");
		g_Va009FE16C->AppendDebugMessage(str, false);
		return;
	}
	Team *theTeam = g_Va009FE16C->getTeamNamed(teamName, true);
	if (!theTeam) {
		g_Va009FE16C->AppendDebugMessage("***WARNING - Team not found:***", false);
		g_Va009FE16C->AppendDebugMessage(teamName, true);
		return;
	}
	ScriptWaypointView *way = (ScriptWaypointView *)
		reinterpret_cast<ScriptActionsTerrainView *>(TheTerrainLogic)->getWaypointByName(waypoint);
	Object *foundObject = 0;
	if (!way) {
		const ThingTemplate *objectTemplate = TheThingFactory->findTemplate(waypoint);
		if (objectTemplate) {
			Coord3D pos;
			theTeam->rva0039E5B9(&pos);
			Rva00261750Filter thingFilter(objectTemplate, true);
			foundObject = ThePartitionManager->getClosestObject(&pos, 1000000.0f, 0, &thingFilter);
		}
	}
	if (!way && !foundObject) {
		g_Va009FE16C->AppendDebugMessage("***WARNING - Waypoint/Object type not found:***", false);
		g_Va009FE16C->AppendDebugMessage(waypoint, true);
		return;
	}
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(objType);
	if (!thingTemplate)
		return;
	Object *obj = TheThingFactory->newObject(thingTemplate, theTeam, &CreateMask(), false);
	if (!obj)
		return;
	if (unitName != AsciiString::TheEmptyString) {
		obj->setName(unitName);
		if (pOldObj || g_Va009FE16C->didUnitExist(unitName))
			g_Va009FE16C->rva00357960(unitName, obj);
		else
			g_Va009FE16C->addObjectToCache(obj, "");
	}
	const Coord3D *pos;
	if (way)
		pos = way->getLocation();
	else if (foundObject)
		pos = foundObject->getPosition();
	obj->setPosition(pos);
	obj->rva0028FC18();
}

// WB ScriptActions::doSetUnitReference @0x003C2019 (99B): either hand the
// parameter's string to the script engine's reference setter 0x00208A09, or
// resolve the parameter to a unit and bind the reference to it.
void ScriptActions::doSetUnitReference(const AsciiString &reference, Parameter *unit, bool byName)
{
	if (byName) {
		g_Va009FE16C->rva00208A09(reference, unit->getString());
	} else {
		Object *theObj = g_Va009FE16C->getUnitNamed(unit);
		if (theObj) {
			g_Va009FE16C->rva00208968(reference, theObj);
			g_Va009FE16C->addObjectToCache(theObj, reference);
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
	Team *theTeam = g_Va009FE16C->getTeamNamed(teamName, false);
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
		((Rva001705A0DlinkIterator<Object> *)&iter)->advance()) {
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
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
	Team *theTeam = g_Va009FE16C->getTeamNamed(teamName, false);
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
		((Rva001705A0DlinkIterator<Object> *)&iter)->advance()) {
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
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
	Team *theTeam = g_Va009FE16C->getTeamNamed(teamName, false);
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
	Team *team = g_Va009FE16C->getTeamNamed(teamName, false);
	if (!team)
		return;
	Object *bestGuess = 0;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done();
		((Rva001705A0DlinkIterator<Object> *)&iter)->advance()) {
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
		Coord3D pos = *bestGuess->getPosition();
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
	Object *theUnit = g_Va009FE16C->getUnitNamed(unitName);
	if (!theUnit)
		return;
	Player *player = theUnit->getControllingPlayer();
	if (!player || !player->rva00339())
		return;
	if (player != g_Va009FE16C->getCurrentPlayer())
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
	Team *theTeam = g_Va009FE16C->getTeamNamed(teamName, false);
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
		((Rva001705A0DlinkIterator<Object> *)&iter)->advance()) {
		Object *obj = iter.cur();
		Coord3D objPos = *obj->getPosition();
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
	Player *enemyPlayer = g_Va009FE16C->getSkirmishEnemyPlayer();
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

// Zero Hour's updateTeamAndPlayerStuff @0x003BA83F (91B): BFME2 first lets
// the radar (0x002D7FAE) refresh the object, and redraws the drawable
// (vtable slot 0x34) after recolouring it. It answers 1 to the team walk.
class Drawable
{
public:
	void setIndicatorColor(int color);
#define DRAW_SLOT(n) virtual void slot##n();
	DRAW_SLOT(0) DRAW_SLOT(1) DRAW_SLOT(2) DRAW_SLOT(3) DRAW_SLOT(4) DRAW_SLOT(5)
	DRAW_SLOT(6) DRAW_SLOT(7) DRAW_SLOT(8) DRAW_SLOT(9) DRAW_SLOT(10) DRAW_SLOT(11)
	DRAW_SLOT(12)
#undef DRAW_SLOT
	virtual void slot13(); // 0x34
};

class Radar
{
public:
	void rva002D7FAE(Object *obj);
};
extern Radar *TheRadar;

struct GlobalData
{
	unsigned char m_pad[0x134];
	int m_timeOfDay;
};
extern GlobalData *TheGlobalData;

enum { TIME_OF_DAY_NIGHT = 4 };

static int updateTeamAndPlayerStuff(Object *obj, void *userData)
{
	if (obj) {
		TheRadar->rva002D7FAE(obj);
		obj->updateUpgradeModules();
		Drawable *draw = obj->getDrawable();
		if (draw) {
			if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
				draw->setIndicatorColor(obj->getNightIndicatorColor());
			else
				draw->setIndicatorColor(obj->getIndicatorColor());
			draw->slot13();
		}
	}
	return 1;
}

// WB/ZH ScriptActions::doTransferTeamToPlayer @0x003C90DD (244B). BFME2
// resolves the player through a name mask, and after the transfer refreshes
// every member and the horde holding it (0x0028BAC0, 0x0028DCC4) and idles
// them (CMD_FROM_AI) before the script engine notes the frame (0x002039B6).
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_command;
};

class Rva002039B6Host
{
public:
	void rva002039B6();
};

static __forceinline void refreshTransferredObject(Object *obj)
{
	obj->rva0028BAC0();
	obj->rva0028DCC4();
	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (ai)
		ai->m_command.aiIdle((CommandSourceType)2);
}

// ?doTransferTeamToPlayer@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
// (244B, size-exact; the second member's AI pointer lands in eax where retail
// reuses edi. Kept because it is updateTeamAndPlayerStuff's only caller.)
void ScriptActions::doTransferTeamToPlayer(const AsciiString &teamName, const AsciiString &playerName)
{
	Team *theTeam = g_Va009FE16C->getTeamNamed(teamName, false);
	int mask = g_Va009FE16C->rva00357475(playerName, 0);
	Player *playerDest = ThePlayerList->getEachPlayerFromMask(mask);
	if (!(theTeam && playerDest))
		return;
	theTeam->setControllingPlayer(playerDest);
	theTeam->rva0039DD12(updateTeamAndPlayerStuff, 0);
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done();
		((Rva001705A0DlinkIterator<Object> *)&iter)->advance()) {
		Object *obj = iter.cur();
		AIUpdateInterface *ai;
		Object *horde = obj->getContainedBy();
		if (horde && horde->isKindOf(0x6D)) {
			horde->rva0028BAC0();
			horde->rva0028DCC4();
			ai = horde->getAIUpdateInterface();
			if (ai)
				ai->m_command.aiIdle((CommandSourceType)2);
		}
		obj->rva0028BAC0();
		obj->rva0028DCC4();
		ai = obj->getAIUpdateInterface();
		if (ai)
			ai->m_command.aiIdle((CommandSourceType)2);
	}
	((Rva002039B6Host *)g_Va009FE16C)->rva002039B6();
}

// WB/ZH ScriptActions::doTeamStartSequentialScript @0x003C0B44 (250B). BFME2
// looks the script up with a second, out string (0x00357130), allocates the
// SequentialScript with plain new (0x2C bytes, ctor 0x0020479E), records both
// names in it, and releases it with ::delete after the engine copies it.
class Script;

class SequentialScript
{
public:
	SequentialScript();
	virtual ~SequentialScript();

	Team *m_teamToExecOn;
	int m_08;
	AsciiString m_objectName;
	AsciiString m_scriptName;
	Script *m_scriptToExecuteSequentially;
	int m_18;
	int m_timesToLoop;
	unsigned char m_pad20[0x2C - 0x20];
};

void ScriptActions::doTeamStartSequentialScript(const AsciiString &teamName,
	const AsciiString &scriptName, int loopVal)
{
	Team *team = g_Va009FE16C->getTeamNamed(teamName, false);
	if (!team)
		return;
	AsciiString objectName;
	Script *script = g_Va009FE16C->rva00357130(scriptName, &objectName);
	if (!script)
		return;
	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;
	team->getTeamAsAIGroup(theGroup);
	theGroup->groupIdle(CMD_FROM_SCRIPT);
	SequentialScript *seqScript = new SequentialScript;
	seqScript->m_teamToExecOn = team;
	seqScript->m_objectName = objectName;
	seqScript->m_scriptName = scriptName;
	seqScript->m_scriptToExecuteSequentially = script;
	seqScript->m_timesToLoop = loopVal;
	g_Va009FE16C->appendSequentialScript(seqScript);
	::delete seqScript;
}

// WB 0x01014560 unnamed ScriptActions member @0x003C20CA (85B), the team
// sibling of doSetUnitReference: set a team reference either by the
// parameter's name (0x00208BCD) or to the team it names (0x00208B2C).
void ScriptActions::rva003C20CA(const AsciiString &reference, Parameter *team, bool byName)
{
	if (byName)
		g_Va009FE16C->rva00208BCD(reference, team->getString());
	else
		g_Va009FE16C->rva00208B2C(reference, g_Va009FE16C->getTeamNamed(team->getString(), false));
}

// WB 0x01014D40 unnamed ScriptActions member @0x003C2166 (125B): hand the
// team's 0x003A1AA3 the template and object-type list of one name, a count,
// and a radius - the AI data's +0x5C when the team has members, else 1e6.
void ScriptActions::rva003C2166(const AsciiString &teamName, int count, const AsciiString &objectTypeName)
{
	Team *team = g_Va009FE16C->getTeamNamed(teamName, true);
	if (!team)
		return;
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(objectTypeName);
	ObjectTypes *types = g_Va009FE16C->getObjectTypes(objectTypeName);
	team->rva003A1AA3(tmpl, types, count,
		team->hasAnyObjects(false) ? TheAI->getAiData()->m_5C : 1000000.0f);
}
