// cl: /Ireference/shims/bfme2_ascii
//
// ?findSideInfo@SidesList@@QAEPAVSidesInfo@@VAsciiString@@PAH@Z @0x0032B0A9 150B
// SidesList::findSideInfo: linear search of m_sides for the entry whose dict
// playerName matches. Donor: BFME1 SidesList.cpp findSideInfo (ZH identical).
// BFME2 differences from retail bytes: playerName key comes from the NameKey
// cache at 0x00DBDE24 via rowed get 0x00148F5E, dict at SidesInfo+0x04
// (SidesList+0x44, 0x60 stride, count at +0x3C), compare via rowed
// StringBase<char>::compare 0x000069D6 with bool materialization, temps via
// rowed releaseBuffer 0x00036410. /G7 for imul scaling of the return pointer.
// The shared comparison declaration preserves the native nonthrowing call.
// AsciiString::compare(const char *) is declared throw() in the canonical
// shim so retail's state-0 call schedule reproduces at this site too.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get(void); // 0x00148F5E
	operator NameKeyType() { return get(); }
	NameKeyType key;
	const char *name;
};

class StaticNameKey;
extern const StaticNameKey TheKey_playerName;
// VA 0x00DBD9F4 is the ledger global StaticNameKey TheKey_teamName.
class StaticNameKey;
extern const StaticNameKey TheKey_teamName;

#include "../../../Include/Common/Dict.h"

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }

private:
	void *m_pBuildList;
	Dict m_dict;
	unsigned char m_pad[0x60 - 8];
};

class TeamsInfo
{
public:
	Dict *getDict() { return &m_dict; }

private:
	Dict m_dict;
};

class SidesList
{
public:
	SidesInfo *findSideInfo(AsciiString name, int *index = 0);
	SidesInfo *findSkirmishSideInfo(AsciiString name, int *index = 0);
	bool isPlayerDefaultTeam(TeamsInfo *t);
	bool validateAllyEnemyList(const AsciiString &tname, AsciiString &allies);

private:
	unsigned char m_pad[0x3C];
	int m_numSides;
	SidesInfo m_sides[20];
	int m_numSkirmishSides;				// +0x7C0
	SidesInfo m_skirmishSides[20];		// +0x7C4
};

SidesInfo *SidesList::findSideInfo(AsciiString name, int *index)
{
	for (int i = 0; i < m_numSides; i++) {
		if (m_sides[i].getDict()->getAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get()) == name) {
			if (index)
				*index = i;
			return &m_sides[i];
		}
	}
	return 0;
}

// ?findSkirmishSideInfo@SidesList@@QAEPAVSidesInfo@@VAsciiString@@PAH@Z
// @0x0032B13F 162B. Donor: ZH SidesList.cpp findSkirmishSideInfo; the same
// search over the skirmish sides (count +0x7C0, array +0x7C4, 0x60 stride)
// that directly follow m_sides in retail.
SidesInfo *SidesList::findSkirmishSideInfo(AsciiString name, int *index)
{
	for (int i = 0; i < m_numSkirmishSides; i++) {
		if (m_skirmishSides[i].getDict()->getAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get()) == name) {
			if (index)
				*index = i;
			return &m_skirmishSides[i];
		}
	}
	return 0;
}

// ?isPlayerDefaultTeam@SidesList@@QAE_NPAVTeamsInfo@@@Z @0x0032B1E1 196B.
// Donor: ZH SidesList.cpp isPlayerDefaultTeam ("teamfoo" with a player
// "foo"); retail compares through the rowed StringBase compare(const char *)
// at 0x000069B1 instead of strcmp. The named volatile rest feeds retail's
// operand order; the shared nonthrowing compare declaration keeps the call's
// EH state at retail's 0.
bool SidesList::isPlayerDefaultTeam(TeamsInfo *teamsInfo)
{
	AsciiString tname = teamsInfo->getDict()->getAsciiString(((Rva00148F5ECache &)TheKey_teamName).get());
	if (tname.startsWith("team"))
	{
		const char * volatile rest = tname.str() + 4;
		for (int j = 0; j < m_numSides; j++)
		{
			AsciiString pname = m_sides[j].getDict()->getAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get());
			if (pname.compare(rest) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

// ?validateAllyEnemyList@SidesList@@QAE_NABVAsciiString@@AAV2@@Z @0x0032B2A5
// 228B. Donor: ZH SidesList.cpp validateAllyEnemyList, unchanged; retail
// calls findSideInfo above and the rowed StringBase compare, nextToken and
// concat bodies. Drops the side's own name and unknown players from a
// space-separated ally/enemy list.
bool SidesList::validateAllyEnemyList(const AsciiString &tname, AsciiString &allies)
{
	bool modified = false;

	AsciiString str, newstr, token;

	str = allies;
	newstr.clear();
	while (str.nextToken(&token))
	{
		if (token == tname)
		{
			modified = true;
			continue;	// no allies/enemies with self
		}

		SidesInfo *si = findSideInfo(token);
		if (!si)
		{
			modified = true;
			continue;	// player not found.
		}

		if (!newstr.isEmpty())
			reinterpret_cast<StringBase<char> *>(&newstr)->concat(" ");
		newstr.concat(token);
	}

	allies = newstr;
	return modified;
}
