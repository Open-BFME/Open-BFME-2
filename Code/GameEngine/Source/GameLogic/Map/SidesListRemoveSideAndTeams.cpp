// cl: /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// ?removeSideAndTeams@SidesList@@QAEXH@Z, retail 0x0032D8C7, 221 bytes.
//
// Identity (target): WorldBuilder's debug twin SidesList::removeSideAndTeams
// (wb 0xa84b30, SidesList.cpp asserts 1349..1350, the same bounds as
// removeSide's) aligns call for call: the playerName key 0x00DBDE24 on the
// side's dict, the teamOwner key 0x00DBD9FC on each team's dict, the
// TeamsInfoRec release 0x0032C26D (WB TeamsInfoRec::removeTeam) and
// removeSide 0x0032D850 last. WB keeps getNextTeamID and getTeamInfo out of
// line (SidesList.h:132 and :197 asserts) and reads the first team id inline,
// so all three are class-body inlines here.
//
// Layout (target): the side dict at this+0x44+index*0x60 (SidesInfo +4) and
// the TeamsInfoRec at +0xF44 whose 16-byte entry vector starts at +0xF50, as
// in SidesListTeamsInfoRecAddTeam.cpp. The entries must be a real STLport
// vector: a hand-written pointer view folds base+id*16 into one register,
// where retail re-adds the base for each inline read.

#include <vector>
#include <map>

#include "ascii_string.h"

#include "../../../Include/Common/Dict.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

// The lazily keyed static name caches (TheKey_* in WorldBuilder).
class Rva00148F5ECache
{
public:
	NameKeyType get(void); // 0x00148F5E
	operator NameKeyType() { return get(); }
	NameKeyType key;
	const char *name;
};

class StaticNameKey;
extern const StaticNameKey TheKey_playerName;	// "playerName"
class StaticNameKey;
extern const StaticNameKey TheKey_teamOwner;	// "teamOwner"

class BfmeThingUBB
{
public:
	BfmeThingUBB();
	short m_next;
	short m_previous;
	short m_reserved;
	short m_free;
	int m_generation;
	Dict m_dict;
};

class TeamsInfoRec
{
public:
	void removeTeam(int index);	// 0x0032C26D, WB removeTeam
	int getFirstTeamID() const { return m_teams[0].m_next; }
	int getNextTeamID(int id) const { return m_teams[id].m_next; }
	Dict *getTeamInfo(int id) { return &m_teams[id].m_dict; }

private:
	std::map<std::pair<AsciiString, AsciiString>, int> m_map;
	std::vector<BfmeThingUBB> m_teams;
	short m_numActive;
	short m_freeHead;
};

#include "../../../Include/GameLogic/SidesInfo.h"

class SidesList
{
public:
	void removeSide(int index);	// 0x0032D850
	void removeSideAndTeams(int index);

private:
	char m_bases[0x3C];
	int m_numSides;
	SidesInfo m_sides[20];
	int m_numSkirmishSides;
	SidesInfo m_skirmishSides[20];
	TeamsInfoRec m_teamrec;
};

// Every team whose teamOwner is the side's playerName is released before the
// side itself is removed.
void SidesList::removeSideAndTeams(int index)
{
	Dict *dict = m_sides[index].getDict();
	bool exists;
	AsciiString name = dict->getAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get(), &exists);
	if (exists) {
		int nextID;
		for (int id = m_teamrec.getFirstTeamID(); id != 0; id = nextID) {
			nextID = m_teamrec.getNextTeamID(id);
			Dict *team = m_teamrec.getTeamInfo(id);
			AsciiString owner = team->getAsciiString(const_cast<Rva00148F5ECache &>(reinterpret_cast<const Rva00148F5ECache &>(TheKey_teamOwner)).get(), &exists);
			if (exists && owner.compare(name) == 0)
				m_teamrec.removeTeam(id);
		}
	}
	removeSide(index);
}
