// ?rva003C4751@ScriptActions@@IAEXPAVParameter@@@Z
// partial score=0.97 date=2026-10-10
// ?rva003C4751@ScriptActions@@IAEXPAVParameter@@@Z
// partial score=0.97 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc /arch:SSE
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

class Rva002D381D
{
public:
	void rva002D381D(int seconds);
};

extern class Rva002D3627Host *TheRva002D3627Host;

#define TheSpellStoreTimer (*(Rva002D381D **)&TheRva002D3627Host)


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


// WB ScriptActions::doPlaySoundEffectAt @0x003BD679 (182B): resolve the named
// waypoint and event, then post the event at Waypoint's +0x0C position.

// WB ScriptActions::doSpeechPlay @0x003BD7E2 (162B): post the named event for
// the local player and set its uninterruptable flag from allowOverlap.

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
	bool operator==(const Coord3D &that);
	float length() const;
	void sub(const Coord3D *that) { x -= that->x; y -= that->y; z -= that->z; }

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
	__forceinline bool isKindOf(int t) const { return (((const unsigned char *)m_template)[0x108 + (t >> 3)] & (1 << (t & 7))) != 0; }
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
	void advance();
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


// WB ScriptActions::doSetUnitReferenceToHomeBaseOfPlayer @0x003BCE69 (146B):
// over every player the name selects, take each player's candidate object
// and keep the one the unnamed comparator 0x002AA497 ranks first, then bind
// the unit reference to it.
int __cdecl rva002AA497(int a, int b);


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


// WB/ZH ScriptActions::doIdleAllPlayerUnits @0x003BBB7E (114B) and
// doResumeSupplyTruckingForIdleUnits @0x003BBBF0 (113B), identified by their
// WorldBuilder DEBUG_LOG strings. BFME2 resolves the name to a player mask
// and applies the setting to every selected player; with no match it falls
// back to every human player, as Zero Hour does.
enum { PLAYER_HUMAN = 0 };



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


// WB ScriptActions::doSetUnitReference @0x003C2019 (99B): either hand the
// parameter's string to the script engine's reference setter 0x00208A09, or
// resolve the parameter to a unit and bind the reference to it.

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


// WB ScriptActions::doTeamAttackMoveFollowWaypoints @0x003BF4CF (303B): the
// same team-centre path search as doTeamFollowWaypoints, issuing the path
// commands in attack-move mode (trailing 1).

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


// WB/ZH ScriptActions::doTeamMoveToSkirmishApproachPath @0x003BF1FF (416B):
// from the team's centre, take the closest waypoint on the enemy's numbered
// approach path and move the team there through the BFME2 group move
// (0x00372571, a 0x20-byte argument block).

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


// ?doTransferTeamToPlayer@ScriptActions@@IAEXABVAsciiString@@0@Z present-unmatched
// (244B, size-exact; the second member's AI pointer lands in eax where retail
// reuses edi. Kept because it is updateTeamAndPlayerStuff's only caller.)

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
	ObjectID m_objectToExecOn;
	AsciiString m_objectName;
	AsciiString m_scriptName;
	Script *m_scriptToExecuteSequentially;
	int m_18;
	int m_timesToLoop;
	unsigned char m_pad20[0x2C - 0x20];
};


// WB 0x01014560 unnamed ScriptActions member @0x003C20CA (85B), the team
// sibling of doSetUnitReference: set a team reference either by the
// parameter's name (0x00208BCD) or to the team it names (0x00208B2C).

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


// WB 0x0100E030 unnamed ScriptActions member @0x003C0E87 (130B): pass a value
// to the named unit's SupplyWarehouseDockUpdate (Rva004A7D55 0x004A7F78).
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva004A7D55
{
public:
	void rva004A7F78(int value);
};


// WB/ZH ScriptActions::doUnitStartSequentialScript @0x003C0A6B (217B): the
// unit form of doTeamStartSequentialScript, recording the unit's id.

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
	virtual bool hasUpgrade(const void *upgrade); // 0xB4
	HM_SLOT(46) HM_SLOT(47) HM_SLOT(48) HM_SLOT(49) HM_SLOT(50) HM_SLOT(51) HM_SLOT(52)
	HM_SLOT(53) HM_SLOT(54) HM_SLOT(55) HM_SLOT(56) HM_SLOT(57) HM_SLOT(58) HM_SLOT(59)
	HM_SLOT(60) HM_SLOT(61) HM_SLOT(62) HM_SLOT(63) HM_SLOT(64) HM_SLOT(65) HM_SLOT(66)
	HM_SLOT(67)
#undef HM_SLOT
	virtual Object *getTarget(); // 0x110
};

void ScriptActions::rva003C4751(Parameter *teamParam)
{
	Team *theTeam = g_Va009FE16C->getTeamNamed(teamParam->getString(), false);
	if (!theTeam)
		return;
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate("SpecialAbilityGiveUpgrade");
	if (!power)
		return;
	Object *giver = theTeam->rva0039E968(0x33);
	if (!giver)
		return;
	void *upgrade = TheUpgradeCenterLookup->rva0026F0F0((unsigned char *)giver + 0x284);
	if (!upgrade)
		return;
	Player *player = giver->getControllingPlayer();
	if (!player)
		return;
	Object *best = 0;
	float bestDist = 3.4028235e+38f;
	Coord3D giverPos = *giver->getPosition();
	Coord3D diff;
	for (PlayerTeamNode *it = player->m_playerTeamPrototypes->m_next;
		it != player->m_playerTeamPrototypes; it = it->m_next) {
		for (DLINK_ITERATOR<Team> teams = it->m_value->iterate_TeamInstanceList();
			!teams.done(); teams.advance()) {
			Team *team = teams.cur();
			if (!team || theTeam == team)
				continue;
			if (!team->rva0039E8FF(upgrade))
				continue;
			for (DLINK_ITERATOR<Object> members = team->iterate_TeamMemberList(); !members.done();
				members.advance()) {
				Object *obj = members.cur();
				if (!obj->isKindOf(0x6D))
					continue;
				ScriptActionsHordeModuleView *module = (ScriptActionsHordeModuleView *)obj->rva0028C197();
				if (!module || module->hasUpgrade(upgrade))
					continue;
				Coord3D memberPos = *obj->getPosition();
				diff == giverPos;
				diff.sub(&memberPos);
				float dist = diff.length();
				Object *target = module->getTarget();
				if (target) {
					if (!best) {
						bestDist = dist;
						best = target;
					} else if (dist < bestDist) {
						bestDist = dist;
						best = target;
					}
				}
			}
		}
	}
	if (best)
		giver->rva0028E01F(power, best, 0x40000, 0);
}
