// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// PlayerList::validateTeam, retail 0x002A851D..0x002A87EA (717 bytes).
// Identity lead: BFME1/Zero Hour PlayerList::validateTeam; target loader 0x244D56
// passes ThePlayerList, a by-value owner string, and its current MapObject.
// Target behavior: look up a qualified team, then resolve Plyr<Faction> through
// SidesList and its team-id chain; fall back to neutral player's default team.
// WB 0xD23F00 confirms the split, nested string lifetimes, and reuse of t.
// In particular teamName must remain alive through the return test. Retail
// hoists its cleanup before that test; an artificial shorter source scope
// changes four stack homes despite producing the same instruction sequence.
// Layout facts: target accesses +0x18 player[0], +0x2EC default team, +0x3C
// side count, and +0xF44 team record; rowed TeamsInfoRec siblings establish
// vector<16-byte entry> at record+0x0C, next-id at entry+0, Dict at entry+0x0C.
// BfmeWordEL/BfmePairEL preserve the rowed splitter's structural spellings;
// the pair adapter owns two AsciiStrings and uses the existing pair cleanup.
#include "ascii_string.h"
#include <vector>

typedef int Int;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

extern Rva00148F5ECache TheKey_playerFaction;
extern const StaticNameKey TheKey_playerName;
extern const StaticNameKey TheKey_teamOwner;
extern const StaticNameKey TheKey_teamName;

class Dict
{
public:
	AsciiString getAsciiString(NameKeyType key, Bool *exists = 0) const;
private:
	void *m_data;
};

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }
private:
	char m_pad00[4];
	Dict m_dict;	// +0x04
};

struct TeamsInfoEntry
{
	short m_next;	// +0x00
	char m_pad02[0x0c - 0x02];
	Dict m_dict;	// +0x0C
};

class TeamsInfoRec
{
public:
	Int getFirstTeamID() const { return m_entries[0].m_next; }
	Int getNextTeamID(Int id) const { return m_entries[id].m_next; }
	Dict *getTeamDict(Int id) { return &m_entries[id].m_dict; }
private:
	char m_pad00[0x0c];
	_STL::vector<TeamsInfoEntry> m_entries;	// +0x0C
};

class SidesList
{
public:
	Int getNumSides() const { return m_numSides; }
	SidesInfo *getSideInfo(Int i);
	TeamsInfoRec *getTeamInfo() { return &m_teamRec; }
private:
	char m_pad00[0x3c];
	Int m_numSides;			// +0x3C
	char m_pad40[0xf44 - 0x40];
	TeamsInfoRec m_teamRec;		// +0xF44
};
extern SidesList *TheSidesList;

class Team;
class TeamFactory
{
public:
	void clear();
	void initFromSides(SidesList *sides);
	Team *findTeam(const AsciiString &name);
	Team *findTeam(const AsciiString &owner, const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

class BfmeWordEL
{
	void *m_data;
};

struct BfmePairEL : _STL::pair<const AsciiString, AsciiString> {};
BfmePairEL __cdecl Rva00194810(const BfmeWordEL &name);
typedef _STL::pair<const AsciiString, AsciiString> (__cdecl *Rva00194810Pair)(const BfmeWordEL &name);

class Rva0036CA00Str;
class Rva000DF920
{
public:
	Rva000DF920(AsciiString &asciiString, AsciiString &b) : m_00(&asciiString), m_04(&b) {}
	Rva000DF920 &operator=(const Rva0036CA00Str *pair);
private:
	AsciiString *m_00;
	AsciiString *m_04;
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	char m_pad00[0x2ec];
	Team *m_defaultTeam;	// +0x2EC
};

class MapObject;

class PlayerList
{
public:
	Player *getNeutralPlayer() const { return m_players[0]; }
	Team *validateTeam(AsciiString owner, MapObject *mapObject);
private:
	char m_pad00[0x14];
	Int m_playerCount;	// +0x14
	Player *m_players[1];	// +0x18; only the first slot is observed here
};

Team *PlayerList::validateTeam(AsciiString owner, MapObject *mapObject)
{
	Team *team = TheTeamFactory->findTeam(owner);
	if (team)
		return team;

	AsciiString playerPart;
	Rva000DF920(playerPart, owner) = reinterpret_cast<const Rva0036CA00Str *>(&reinterpret_cast<Rva00194810Pair>(&Rva00194810)((const BfmeWordEL&)owner));
	if (((const StringBase<char> *)&playerPart)->startsWith("Plyr", 4)) {
		AsciiString playerSuffix(playerPart, 4, playerPart.getLength() - 4);
		for (Int i = 0; i < TheSidesList->getNumSides(); ++i) {
			Dict *sideDict = (Dict *)((char *)TheSidesList->getSideInfo(i) + 4);
			Bool exists;
			AsciiString faction = sideDict->getAsciiString(TheKey_playerFaction.get(), &exists);
			if (exists && ((const StringBase<char> *)&faction)->startsWith("Faction", 7)) {
				AsciiString factionName(faction, 7, faction.getLength() - 7);
				if (factionName.compare(playerSuffix) == 0) {
					AsciiString playerName = sideDict->getAsciiString(TheKey_playerName.key());
					for (Int id = TheSidesList->getTeamInfo()->getFirstTeamID(); id != 0; id = TheSidesList->getTeamInfo()->getNextTeamID(id)) {
						Dict *teamDict = TheSidesList->getTeamInfo()->getTeamDict(id);
						AsciiString teamOwner = teamDict->getAsciiString(TheKey_teamOwner.key(), &exists);
						if (teamOwner.compare(playerName) == 0) {
							AsciiString teamName = teamDict->getAsciiString(TheKey_teamName.key(), &exists);
							team = TheTeamFactory->findTeam(teamOwner, teamName);
							if (team)
								return team;
						}
					}
				}
			}
		}
	}
	return getNeutralPlayer()->getDefaultTeam();
}
