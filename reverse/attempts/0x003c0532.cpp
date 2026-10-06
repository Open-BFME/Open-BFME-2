// ?doResetMusicScripting@ScriptActions@@IAEX_N@Z
// partial score=0.95 date=2026-10-06
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
	void doResetMusicScripting(bool enable);
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
	AUDIO_SLOT(36) AUDIO_SLOT(37)
#undef AUDIO_SLOT
	// Slot 0x98; WB's debug vtable has it at 0x9c. Name not established.
	virtual void musicSlot38(int a, int b, int c);
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(39) AUDIO_SLOT(40)
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
	unsigned char m_pad58[0x32C - 0x58];
	PlayerTeamNode *m_playerTeamPrototypes;
};

class PlayerList
{
public:
	unsigned char m_pad00[0x10];
	Player *m_localPlayer;
	Player *getEachPlayerFromMask(int &mask);
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
	// Script flag lookup by name (0x0020881A); returns the flag's storage.
	void *rva0020881A(AsciiString name);
	class Object *getUnitNamed(const AsciiString &unitName);
};
extern ScriptEngine *g_Va009FE16C;

enum ObjectID { INVALID_OBJECT_ID = 0 };

class Object
{
public:
	unsigned char m_pad00[0x74];
	ObjectID m_objectID;
	Player *getControllingPlayer() const;
	void rva0028ECA8(int index, float value, int arg);
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

// WB ScriptActions::doResetMusicScripting @0x003C0532 (88B): tell TheAudio
// (slot 0x98) the inverted flag, then set the music-script init flag if the
// map links the music scripts.
void ScriptActions::doResetMusicScripting(bool enable)
{
	ScriptActionsAudioView *audio = reinterpret_cast<ScriptActionsAudioView *>(TheAudio);
	audio->musicSlot38(0, 0, !enable);
	char flagName[] = "/___MusicScript_Init";
	bool *flag = (bool *)g_Va009FE16C->rva0020881A(flagName);
	if (flag)
		*flag = true;
}
