// ?validateSides@SidesList@@QAE_NXZ
// partial score=0.99 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?validateSides@SidesList@@QAE_NXZ, retail 0x0032E02B, 1097 bytes.
//
// Identity (target): WorldBuilder's debug twin SidesList::validateSides
// (wb 0xa855a0) aligns call for call, and SidesList::writeSidesDataChunk
// (0x0032E542) calls it before writing. The shape is ZH GeneralsMD
// SidesList::validateSides: make sure a neutral side exists, give every side
// its singleton "team<player>", repair the ally and enemy lists, then fix up
// the team table.
//
// BFME2 changes read off retail: the neutral test is the side's
// Rva00329EE9 predicate (empty playerName); the side's team is found through
// the owner/name joined key and must also have a non-zero id; a wrong owner is
// repaired with TeamsInfoRec::renameTeam; teams named like a side are
// released (restarting the walk), and teams that are not overridden but have
// no owning side, or are owned by themselves, are renamed to no owner.
//
// Layout (target): sides count at +0x3C (SidesList_getSideInfo.cpp), the
// side's Dict at +4 (SidesList_sidesInfo.cpp), TeamsInfoRec at +0xF44 with its
// 16-byte entries at +0xC (SidesListTeamsInfoRecMoveTeams.cpp): the list
// links at +0/+2, overriddenByID at +6 and the team Dict at +0xC.

#include "ascii_string.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

class StaticNameKey
{
public:
	NameKeyType key() const;			// 0x00148F5E
	operator NameKeyType() const { return key(); }

private:
	mutable NameKeyType m_key;
	const char *m_name;
};

extern const StaticNameKey TheKey_playerName;	// VA 0x00DBDE24
extern const StaticNameKey TheKey_teamName;		// VA 0x00DBD9F4
extern const StaticNameKey TheKey_teamOwner;	// VA 0x00DBD9FC

class Rva00148F5ECache
{
public:
	NameKeyType get();					// 0x00148F5E

private:
	NameKeyType m_key;
	const char *m_name;
};

extern Rva00148F5ECache TheKey_teamIsSingleton;	// VA 0x00DBDA04
extern Rva00148F5ECache TheKey_playerAllies;	// VA 0x00DBDE54
extern Rva00148F5ECache TheKey_playerEnemies;	// VA 0x00DBDE4C

class Dict
{
public:
	Dict(int numPairsToPreAllocate);	// 0x00313581
	~Dict() { releaseData(); }
	bool getBool(int key, bool *exists = 0) const;	// 0x00313198
	AsciiString getAsciiString(int key, bool *exists = 0) const;	// 0x0031359F
	void setBool(int key, bool value);	// 0x003136F6
	void setAsciiString(int key, const AsciiString &value);	// 0x0031375A

private:
	void releaseData();					// 0x0031339C
	void *m_data;
};

class TeamsInfo
{
public:
	Dict *getDict() { return &m_dict; }

public:
	Dict m_dict;
};

class TeamsInfoEntry
{
public:
	short m_next;
	short m_previous;
	short m_overridesID;
	short m_overriddenByID;			// +6
	void *m_indexIt;
	TeamsInfo m_info;				// +0xC
};

class TeamsInfoVector
{
public:
	typedef unsigned int size_type;
	TeamsInfoEntry *begin() { return m_start; }
	TeamsInfoEntry &operator[](size_type n) { return *(begin() + n); }
	TeamsInfoEntry &raw(size_type n) { return *(m_start + n); }

	TeamsInfoEntry *m_start;
	TeamsInfoEntry *m_finish;
	TeamsInfoEntry *m_endOfStorage;
};

class TeamsInfoRec
{
public:
	void renameTeam(int id, const AsciiString &owner, const AsciiString &name);	// 0x0032D223
	int addTeam(const Dict *d);		// 0x0032DA4E
	void bfmeRelease(int id);		// 0x0032C26D
	TeamsInfo *getTeamInfo(int id) { return &m_entries[id].m_info; }
	int getNextTeamID(int id) { return m_entries[id].m_next; }
	bool isFinal(int id) { return m_entries[id].m_overriddenByID == 0; }

	char m_index[0xC];
	TeamsInfoVector m_entries;		// +0xC
};

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }

private:
	void *m_pBuildList;
	Dict m_dict;					// +4
};

// The neutral-side predicate, rowed under its address name.
class Rva00329EE9
{
public:
	bool rva00329EE9() const;		// 0x00329EE9
};

// SidesList's team lookup by joined key, rowed under an address-era owner.
class Rva0019C520Owner
{
public:
	int forward(AsciiString name, int index);	// 0x0032D7DB
};

AsciiString Rva0032B389Join(const AsciiString &a, const AsciiString &b);	// 0x0032B389

class SidesList
{
public:
	bool validateSides();
	int getNumSides() { return m_numSides; }
	SidesInfo *getSideInfo(int side);	// 0x002035BA
	SidesInfo *findSideInfo(AsciiString name, int *index = 0);	// 0x0032B0A9
	bool validateAllyEnemyList(const AsciiString &tname, AsciiString &allies);	// 0x0032B2A5
	int rva0032DE04(const AsciiString &playerTemplate);	// 0x0032DE04, addPlayerByTemplate

private:
	char m_pad[0x3C];
	int m_numSides;					// +0x3C
	char m_pad2[0xF44 - 0x40];
	TeamsInfoRec m_teamrec;			// +0xF44
};

bool SidesList::validateSides()
{
	bool modified = false;
	int i;

	int neutral = -1;
	int numSides = m_numSides;
	for (i = 0; i < numSides; i++) {
		if (((const Rva00329EE9 *)getSideInfo(i))->rva00329EE9()) {
			neutral = i;
			break;
		}
	}
	if (neutral == -1) {
		rva0032DE04(AsciiString::TheEmptyString);
		modified = true;
	}

	for (i = 0; i < getNumSides(); i++) {
		Dict *pdict = getSideInfo(i)->getDict();
		AsciiString pname = pdict->getAsciiString(TheKey_playerName);
		AsciiString tname("team");
		tname.concat(pname);
		int index;
		Dict *ti = (Dict *)((Rva0019C520Owner *)this)->forward(Rva0032B389Join(pname, tname), (int)&index);
		if (ti != 0 && index != 0) {
			if (ti->getAsciiString(TheKey_teamOwner) != pname) {
				m_teamrec.renameTeam(index, pname, ti->getAsciiString(TheKey_teamName));
				modified = true;
			}
			if (!ti->getBool(TheKey_teamIsSingleton.get())) {
				ti->setBool(TheKey_teamIsSingleton.get(), true);
				modified = true;
			}
		} else {
			Dict d(0);
			d.setAsciiString(TheKey_teamName, tname);
			d.setAsciiString(TheKey_teamOwner, pname);
			d.setBool(TheKey_teamIsSingleton.get(), true);
			m_teamrec.addTeam(&d);
			modified = true;
		}
		AsciiString allies = pdict->getAsciiString(TheKey_playerAllies.get());
		AsciiString enemies = pdict->getAsciiString(TheKey_playerEnemies.get());
		if (validateAllyEnemyList(pname, allies)) {
			pdict->setAsciiString(TheKey_playerAllies.get(), allies);
			modified = true;
		}
		if (validateAllyEnemyList(pname, enemies)) {
			pdict->setAsciiString(TheKey_playerEnemies.get(), enemies);
			modified = true;
		}
	}

restart:
	for (i = m_teamrec.m_entries.raw(0).m_next; i != 0; ) {
		int next = m_teamrec.m_entries[i].m_next;
		Dict *tdict = m_teamrec.m_entries.raw(i).m_info.getDict();
		AsciiString tname = tdict->getAsciiString(TheKey_teamName);
		if (findSideInfo(tname) != 0) {
			m_teamrec.bfmeRelease(i);
			modified = true;
			goto restart;
		}
		i = next;
	}

	for (i = m_teamrec.m_entries.raw(0).m_next; i != 0; i = m_teamrec.m_entries.raw(i).m_next) {
		if (m_teamrec.m_entries.raw(i).m_overriddenByID != 0)
			continue;
		Dict *tdict = m_teamrec.m_entries.raw(i).m_info.getDict();
		AsciiString tname = tdict->getAsciiString(TheKey_teamName);
		AsciiString towner = tdict->getAsciiString(TheKey_teamOwner);
		if (findSideInfo(towner) == 0 || towner == tname) {
			m_teamrec.renameTeam(i, AsciiString::TheEmptyString, tname);
			modified = true;
		}
	}
	return modified;
}
