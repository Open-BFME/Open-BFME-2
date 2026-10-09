// ?rva0032FF91@SidesList@@QAEXXZ
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?rva0032FF91@SidesList@@QAEXXZ
// retail 0x0032FF91..0x00330440 (1199 bytes) thiscall no arguments, EH frame.
//
// BFME2's skirmish preparation of the map's sides (the role of Zero Hour's
// SidesList::prepareForMP_or_Skirmish in SidesList.cpp, rewritten). WorldBuilder
// twin 0x00A83E10 (unnamed; strings evidence "PlyrCivilian" "PlyrCreeps"
// "SkirmishHuman" "FactionCivilian" "Multiplayer_Human" "team") has the same
// statement order. Target evidence: builds a scratch SidesList (pinned ctor
// 0x0032EE24 / dtor 0x0032EC63) whose +0xF44 team record copies this one
// (rowed operator= 0x0032DDB3); moves every side whose playerName is set
// and is neither "PlyrCivilian" nor "PlyrCreeps" into the scratch list
// (rowed SidesInfo::swap 0x0032B070, pinned ScriptList 0x003B693A, rowed
// removeSide 0x0032D850) and marks the rest not human (rowed Dict::setBool
// 0x003136F6); splits the teams the same way by teamOwner (rowed removeTeam
// 0x0032C26D, out-of-line StringBase isEmpty 0x00001E2F); gives each moved
// side without a string playerAIType its faction template's AI type (rowed
// getType 0x0031317C, nameToKey 0x0009FA65, findPlayerTemplate 0x001FD31B,
// template +0x1B0); appends the "SkirmishHuman" side and its "team" entry
// (rowed Dict ctor/setters/clear, addSide 0x0032D076, addTeam 0x0032DA4E);
// runs the rowed 0x0032FEF5 and 0x0032C2C4 passes and the script pass again;
// then swaps the twenty sides and the team record into the skirmish slots
// at +0x7C4 (count +0x7C0) and +0xF60.
#include "ascii_string.h"
#include "unicode_string.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);	// 0x0009FA65
};
extern NameKeyGenerator *TheNameKeyGenerator;

class StaticNameKey
{
public:
	NameKeyType key() const;			// 0x00148F5E
	operator NameKeyType() const { return key(); }

private:
	mutable NameKeyType m_key;
	const char *m_name;
};

// The same lazily-keyed name cache under its non-const ledger spelling.
class Rva00148F5ECache
{
public:
	NameKeyType get();					// 0x00148F5E
	operator NameKeyType() { return get(); }

private:
	NameKeyType m_key;
	const char *m_name;
};

extern const StaticNameKey TheKey_playerName;		// VA 0x00DBDE24
extern const StaticNameKey TheKey_teamOwner;		// VA 0x00DBD9FC
extern const StaticNameKey TheKey_teamName;			// VA 0x00DBD9F4
extern Rva00148F5ECache TheKey_playerIsHuman;		// VA 0x00DBDE2C
extern Rva00148F5ECache TheKey_playerDisplayName;	// VA 0x00DBDE3C
extern Rva00148F5ECache TheKey_playerFaction;		// VA 0x00DBDE44
extern Rva00148F5ECache TheKey_playerEnemies;		// VA 0x00DBDE4C
extern Rva00148F5ECache TheKey_playerAllies;		// VA 0x00DBDE54
extern Rva00148F5ECache TheKey_playerAIType;		// VA 0x00DBDE9C
extern Rva00148F5ECache TheKey_teamIsSingleton;		// VA 0x00DBDA04

class Dict
{
public:
	enum DataType { DICT_NONE = -1, DICT_BOOL = 0, DICT_INT, DICT_REAL, DICT_ASCIISTRING };
	Dict(int numPairsToPreAllocate);	// 0x00313581
	~Dict() { releaseData(); }
	DataType getType(int key) const;	// 0x0031317C
	AsciiString getAsciiString(int key, bool *exists = 0) const;	// 0x0031359F
	void setBool(int key, bool value);	// 0x003136F6
	void setAsciiString(int key, const AsciiString &value);	// 0x0031375A
	void setUnicodeString(int key, const UnicodeString &value);	// 0x00313781
	void clear();						// 0x00313574

private:
	void releaseData();					// 0x0031339C
	void *m_data;
};

class PlayerTemplate
{
public:
	const AsciiString &getDefaultAIType() const { return m_defaultAIType; }

private:
	char m_pad000[0x1B0];
	AsciiString m_defaultAIType;		// +0x1B0
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;	// 0x001FD31B
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

class ScriptList
{
public:
	void rva003B693A();					// 0x003B693A
};

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }
	void swap(SidesInfo *other);		// 0x0032B070

	void *m_pBuildList;					// +0x00
	Dict m_dict;						// +0x04
	ScriptList m_scripts;				// +0x08
	char m_pad09[0x60 - 0x09];
};

struct TeamsInfoEntry
{
	short m_next;
	short m_previous;
	short m_reserved;
	short m_free;
	int m_generation;
	Dict m_dict;						// +0x0C
};

class TeamsInfoRec
{
public:
	TeamsInfoRec &operator=(const TeamsInfoRec &that);	// 0x0032DDB3
	void swap(TeamsInfoRec *other);		// 0x0032B651
	int addTeam(const Dict *dict);		// 0x0032DA4E
	void removeTeam(int id);			// 0x0032C26D
	void rva0032C2C4();					// 0x0032C2C4
	int getFirstTeamID() const { return m_teams[0].m_next; }
	int getNextTeamID(int id) const { return m_teams[id].m_next; }
	Dict *getTeamInfo(int id) { return &m_teams[id].m_dict; }

private:
	char m_index[0x0C];
	TeamsInfoEntry *m_teams;			// +0x0C, vector start
	char m_rest[0x1C - 0x10];
};

class Rva0032FEF5
{
public:
	void rva0032FEF5();					// 0x0032FEF5
};

enum { MAX_PLAYER_COUNT = 20 };

class SidesList
{
public:
	SidesList();						// 0x0032EE24
	virtual ~SidesList();				// 0x0032EC63
	void rva0032FF91();
	int addSide(const Dict *dict);		// 0x0032D076
	void removeSide(int side);			// 0x0032D850

	char m_bases[0x3C - 4];
	int m_numSides;						// +0x3C
	SidesInfo m_sides[MAX_PLAYER_COUNT];	// +0x40
	int m_numSkirmishSides;				// +0x7C0
	SidesInfo m_skirmishSides[MAX_PLAYER_COUNT];	// +0x7C4
	TeamsInfoRec m_teamrec;				// +0xF44
	TeamsInfoRec m_skirmishTeamrec;		// +0xF60
	char m_rest[0x11B0 - 0xF7C];
};

void SidesList::rva0032FF91()
{
	SidesList newSides;
	newSides.m_teamrec = m_teamrec;

	for (int i = 0; i < m_numSides; )
	{
		AsciiString name = m_sides[i].getDict()->getAsciiString(TheKey_playerName);
		bool isCivilian = name.isEmpty() || name.compare("PlyrCivilian") == 0 || name.compare("PlyrCreeps") == 0;
		if (isCivilian)
		{
			m_sides[i].getDict()->setBool(TheKey_playerIsHuman, false);
			++i;
		}
		else
		{
			newSides.m_sides[newSides.m_numSides].swap(&m_sides[i]);
			newSides.m_sides[newSides.m_numSides].m_scripts.rva003B693A();
			newSides.m_numSides++;
			removeSide(i);
		}
	}

	int id = m_teamrec.getFirstTeamID();
	while (id != 0)
	{
		int next = m_teamrec.getNextTeamID(id);
		AsciiString owner = m_teamrec.getTeamInfo(id)->getAsciiString(TheKey_teamOwner);
		if (((const StringBase<char> *)&owner)->isEmpty() || owner.compare("PlyrCivilian") == 0 || owner.compare("PlyrCreeps") == 0)
			newSides.m_teamrec.removeTeam(id);
		else
			m_teamrec.removeTeam(id);
		id = next;
	}

	for (int j = 0; j < newSides.m_numSides; ++j)
	{
		Dict *dict = newSides.m_sides[j].getDict();
		if (dict->getType(TheKey_playerAIType) != Dict::DICT_ASCIISTRING)
		{
			AsciiString faction = dict->getAsciiString(TheKey_playerFaction);
			const PlayerTemplate *pt = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(faction));
			if (pt && !((const StringBase<char> *)&pt->getDefaultAIType())->isEmpty())
				dict->setAsciiString(TheKey_playerAIType, pt->getDefaultAIType());
		}
	}

	Dict d(0);
	d.setAsciiString(TheKey_playerName, AsciiString("SkirmishHuman"));
	d.setBool(TheKey_playerIsHuman, true);
	d.setUnicodeString(TheKey_playerDisplayName, UnicodeString::TheEmptyString);
	d.setAsciiString(TheKey_playerFaction, AsciiString("FactionCivilian"));
	d.setAsciiString(TheKey_playerEnemies, AsciiString::TheEmptyString);
	d.setAsciiString(TheKey_playerAllies, AsciiString::TheEmptyString);
	d.setAsciiString(TheKey_playerAIType, AsciiString("Multiplayer_Human"));
	newSides.addSide(&d);
	d.clear();

	AsciiString teamName("team");
	teamName += "SkirmishHuman";
	d.setAsciiString(TheKey_teamName, teamName);
	d.setAsciiString(TheKey_teamOwner, AsciiString("SkirmishHuman"));
	d.setBool(TheKey_teamIsSingleton, true);
	newSides.m_teamrec.addTeam(&d);

	((Rva0032FEF5 *)&newSides)->rva0032FEF5();
	for (int k = 0; k < newSides.m_numSides; ++k)
		newSides.m_sides[k].m_scripts.rva003B693A();
	newSides.m_teamrec.rva0032C2C4();

	m_numSkirmishSides = newSides.m_numSides;
	for (unsigned int n = 0; n < MAX_PLAYER_COUNT; ++n)
		m_skirmishSides[n].swap(&newSides.m_sides[n]);
	m_skirmishTeamrec.swap(&newSides.m_teamrec);
}
