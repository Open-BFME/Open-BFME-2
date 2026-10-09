// ?validateTeam@PlayerList@@QAEPAVTeam@@VAsciiString@@PAVMapObject@@@Z
// partial score=0.87 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// NEAR draft (score ~0.87, 715B vs 717B) for retail 0x002A851D (717B).
// Identity: PlayerList::validateTeam (BFME 1 / ZH PlayerList.cpp; sits among the
// PlayerList rows 0x002A79A9..0x002A7F2A; the sole caller 0x00245011 passes
// ThePlayerList (0x009FEEE8) in ecx, an AsciiString by value and the current
// map object from BfmeTheMapObjectListHolder; the fallback is
// getNeutralPlayer()->getDefaultTeam() = m_players[0] (+0x18) -> +0x2EC).
// BFME 2 adds the "Plyr<faction>/<team>" lookup through SidesList sides
// (playerFaction "Faction..." == suffix) and the TeamsInfoRec id chain at
// SidesList +0xF50 (16-byte entries: next id word at +0 and Dict at +0xC).
// Remaining differences: stack slot packing (retail puts playerSuffix in the
// tie temporary's second word -0x34 and factionName/playerName/teamName at
// -0x2C/-0x28/-0x24; this body packs playerSuffix at -0x2C), the side Dict
// pointer (retail mov esi,eax ... add esi,4; here lea esi,[eax+4]) and the
// base/index order of the TeamsInfo entry addressing ([esi+eax+0xC] /
// [esi+ecx]). Control flow EH states calls and frame size already match.
#include "ascii_string.h"

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
	TeamsInfoEntry *m_entries;	// +0x0C
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
	Team *rva003A40F5(const AsciiString &name);
	Team *findTeam(const AsciiString &owner, const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

struct Rva0019B780Key
{
	AsciiString first;
	AsciiString second;
};
Rva0019B780Key __cdecl Rva00194810(const AsciiString &name);

class Rva0036CA00Str;
class Rva000DF920
{
public:
	Rva000DF920(AsciiString &a, AsciiString &b) : m_00(&a), m_04(&b) {}
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
	Player *m_players[20];	// +0x18
};

Team *PlayerList::validateTeam(AsciiString owner, MapObject *mapObject)
{
	Team *t = TheTeamFactory->rva003A40F5(owner);
	if (t)
		return t;

	AsciiString playerPart;
	Rva000DF920(playerPart, owner) = reinterpret_cast<const Rva0036CA00Str *>(&Rva00194810(owner));
	if (((const StringBase<char> *)&playerPart)->startsWith("Plyr", 4)) {
		AsciiString playerSuffix(playerPart, 4, playerPart.getLength() - 4);
		for (Int i = 0; i < TheSidesList->getNumSides(); ++i) {
			Dict *sideDict = TheSidesList->getSideInfo(i)->getDict();
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
							Team *team;
							{
								AsciiString teamName = teamDict->getAsciiString(TheKey_teamName.key(), &exists);
								team = TheTeamFactory->findTeam(teamOwner, teamName);
							}
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
