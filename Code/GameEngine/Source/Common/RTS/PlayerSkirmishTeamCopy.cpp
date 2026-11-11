// cl: /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// BFME2 Player skirmish setup; reference ZH Player.cpp copy/qualify teams section.
// Native2AD25B..2AD4EC657B and WB C13D00 define BFME2 merge/discard behavior and team-name remapping.
#include "ascii_string.h"
#include <vector>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();

private:
	NameKeyType m_key;
	const char *m_name;
};

class StaticNameKey;
extern const StaticNameKey TheKey_playerName;
extern const StaticNameKey TheKey_teamOwner;
extern const StaticNameKey TheKey_teamName;

class Dict
{
public:
	Dict(const Dict &src) : m_data(src.m_data) { if (m_data) ++*(unsigned short *)m_data; }
	~Dict() { releaseData(); }
	AsciiString getAsciiString(int key, bool *exists = 0) const;
	void setAsciiString(int key, const AsciiString &value);

private:
	void releaseData();
	void *m_data;
};

#include "../../../Include/GameLogic/ScriptList.h"

struct BfmeSubGE;
#include "../../../Include/GameLogic/BfmeThingGE.h"

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }
	ScriptList *getScriptList() { return &m_scripts; }
	void setScriptList(ScriptList *list);

private:
	void *m_pBuildList;
	Dict m_dict;
	ScriptList m_scripts;
	char m_tail[0x60 - 0x54];
};

struct TeamsInfoEntry
{
	short m_next;
	short m_previous;
	short m_reserved;
	short m_free;
	int m_generation;
	Dict m_dict;
};

// Typed view of TeamsInfoRec's 16-byte entry vector at +0x0C, which keeps retail's shared vector address.
class SkirmishTeamEntries
{
public:
	int getFirstTeamID() const { return m_teams.front().m_next; }
	int getNextTeamID(int id) const { return m_teams[id].m_next; }
	Dict *getTeamInfo(int id) { return &m_teams[id].m_dict; }

private:
	_STL::vector<TeamsInfoEntry> m_teams;
};

class TeamsInfoRec
{
public:
	void removeTeam(int id);
	int addTeam(const Dict *dict);

	char m_index[0xC];
	SkirmishTeamEntries m_entries;
	short m_numActive;
	short m_freeHead;
};

class SidesList
{
public:
	SidesInfo *getSkirmishSideInfo(int ndx);
	SidesInfo *getSideInfo(int ndx);
	TeamsInfoRec *getTeams() { return &m_teamrec; }
	SkirmishTeamEntries *getSkirmishTeamEntries() { return &m_skirmishTeamrec.m_entries; }

	char m_pad[0x7C0];
	int m_numSkirmishSides;
	SidesInfo m_skirmishSides[20];
	TeamsInfoRec m_teamrec;
	TeamsInfoRec m_skirmishTeamrec;
};

extern SidesList *TheSidesList;

class Rva0019C520Owner
{
public:
	int forward(AsciiString name, int extra);
};

#include "../../../Include/Common/Rva000B3F84Pair.h"
struct AsciiStringRef
{
	const AsciiString *string;
};
struct AsciiStringPlusText : AsciiStringRef
{
	AsciiStringPlusText() {}
	Rva000B3F84Pair right;
};
struct Rva002226E5TextPlusString
{
	Rva002226E5TextPlusString() {}
	Rva000B3F84Pair left;
	AsciiStringRef right;
	operator AsciiString();
};
struct AptTextPlusStringPlusString : Rva002226E5TextPlusString
{
	AsciiStringRef third;
};
struct Rva0020F58E
{
	AsciiStringPlusText first;
	AsciiStringRef second;
	operator AsciiString();
};

Rva002226E5TextPlusString operator+(const char *left, const AsciiString &right);
AsciiStringPlusText operator+(const AsciiString &left, const char *right);
AptTextPlusStringPlusString operator+(const Rva002226E5TextPlusString &left, const AsciiString &right);
// Rowed with int parameters: compares a string with a text-plus-string node.
bool Rva002ACFC1Equal(int string, int node);

#include "../../../Include/Common/Player.h"

inline __declspec(noinline) SidesInfo *SidesList::getSkirmishSideInfo(int i) { return i >= 0 && i < m_numSkirmishSides ? &m_skirmishSides[i] : 0; }

// Visible copy of the rowed skirmish-side lookup (PlayerSkirmishNameFind.cpp), as in retail's unit.
inline __declspec(noinline) bool Player::rva002AC43F(int *index)
{
	int count = TheSidesList->m_numSkirmishSides;
	*index = 0;
	for (int i = 0; i < count; i++) {
		Dict *dict = TheSidesList->getSkirmishSideInfo(i)->getDict();
		AsciiString name = dict->getAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get());
		if (name.compare(m_playerName) == 0) {
			*index = i;
			return true;
		}
	}
	return false;
}

// Merges the skirmish side's scripts into this player's side and copies its teams to playerName.
// The owner test uses the returned owner string as compare receiver, as retail does.
void Player::rva002AD25B(const AsciiString &playerName)
{
	int skirmishIndex;
	if (!rva002AC43F(&skirmishIndex))
		return;
	{
		ScriptList scripts(*TheSidesList->getSkirmishSideInfo(skirmishIndex)->getScriptList());
		SidesInfo *side = TheSidesList->getSideInfo(m_playerIndex);
		((BfmeThingGE *)&scripts)->rva003B89A7((BfmeSubGE *)side->getScriptList());
		scripts.rva003B693A();
		side->setScriptList(&scripts);
	}
	// Now add teams.

	AsciiString originalPlayerName = TheSidesList->getSkirmishSideInfo(skirmishIndex)->getDict()->getAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get());
	for (int id = TheSidesList->getSkirmishTeamEntries()->getFirstTeamID(); id; id = TheSidesList->getSkirmishTeamEntries()->getNextTeamID(id)) {
		if (TheSidesList->getSkirmishTeamEntries()->getTeamInfo(id)->getAsciiString(((Rva00148F5ECache *)&TheKey_teamOwner)->get()) == originalPlayerName) {
			Dict teamDict(*TheSidesList->getSkirmishTeamEntries()->getTeamInfo(id));
			AsciiString teamName = teamDict.getAsciiString(((Rva00148F5ECache *)&TheKey_teamName)->get());
			if (Rva002ACFC1Equal((int)&teamName, (int)&static_cast<const Rva002226E5TextPlusString &>("team" + originalPlayerName)))
				teamDict.setAsciiString(((Rva00148F5ECache *)&TheKey_teamName)->get(), "team" + playerName);
			teamDict.setAsciiString(((Rva00148F5ECache *)&TheKey_teamOwner)->get(), playerName);
			int existingTeam;
			if (((Rva0019C520Owner *)TheSidesList)->forward(((Rva0020F58E *)&(*(const Rva002226E5TextPlusString *)&(playerName + "/") + teamName))->operator AsciiString(), (int)&existingTeam))
				TheSidesList->getTeams()->removeTeam(existingTeam);
			TheSidesList->getTeams()->addTeam(&teamDict);
		}
	}
}

typedef char TeamsInfoRecSizeCheck[sizeof(TeamsInfoRec) == 0x1C ? 1 : -1];
