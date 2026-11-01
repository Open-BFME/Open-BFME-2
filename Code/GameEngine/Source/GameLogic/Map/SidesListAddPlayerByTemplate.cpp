// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
#include "ascii_string.h"
#include "unicode_string.h"
//
// ?addPlayerByTemplate@SidesList@@QAEHABVAsciiString@@@Z
// retail 0x0032DE04, 527 bytes. SidesList::addPlayerByTemplate shape from ZH
// GeneralsMD SidesList.cpp (Plyr/Faction/PlyrCivilian/team/addTeam/addSide):
// builds playerName/display/isHuman from template, team dict then side dict.
// BFME2 changes read off retail: team dict first then side dict, returns
// addSide index, Dict(0) ctor, neutral display is UTF-16 "Neutral", name empty is
// g_Rva0107301CEmptyString. Callees all rowed. Layout: TeamsInfoRec at +0xF44
// as in SidesList_sidesInfo.cpp, addTeam/addSide rowed.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva00148F5ECache
{
public:
	NameKeyType get(void); // 0x00148F5E
	operator NameKeyType() { return get(); }
	NameKeyType key;
	const char *name;
};

// Use the existing const StaticNameKey owners through the retail lazy-cache
// view. get() reads/writes the key at +0 and reads the name pointer at +4.
class StaticNameKey;
extern const StaticNameKey TheKey_teamName;
extern const StaticNameKey TheKey_teamOwner;
extern Rva00148F5ECache TheKey_teamIsSingleton;
class StaticNameKey;
extern const StaticNameKey TheKey_playerName;
extern Rva00148F5ECache TheKey_playerFaction;

// Native initializers are eight-byte {0, name} caches. Their strings and
// each code reference are independently verified in reverse/data_rows.csv.
Rva00148F5ECache TheKey_playerIsHuman = { NAMEKEY_INVALID, "playerIsHuman" };
Rva00148F5ECache TheKey_playerDisplayName = { NAMEKEY_INVALID, "playerDisplayName" };
Rva00148F5ECache TheKey_playerAllies = { NAMEKEY_INVALID, "playerAllies" };
Rva00148F5ECache TheKey_playerEnemies = { NAMEKEY_INVALID, "playerEnemies" };
// RVA 0x009BDE9C: {0, "playerAIType"} between TheKey_playerIsPreorder and
// TheKey_playerFactionIcon; its readers spell it through this cache view.
Rva00148F5ECache TheKey_playerAIType = { NAMEKEY_INVALID, "playerAIType" };
extern const unsigned short SidesListNeutralDisplayName[8] = {
	'N', 'e', 'u', 't', 'r', 'a', 'l', 0
};

class Dict
{
public:
	Dict(int numPairsToPreAllocate);
	~Dict() { releaseData(); }
	void clear();
	void setAsciiString(int key, const AsciiString &value);
	void setBool(int key, bool value);
	void setUnicodeString(int key, const UnicodeString &value);
private:
	void releaseData();
	void *m_data;
};

class TeamsInfoRec
{
public:
	int addTeam(const Dict *d);
};

class SidesList
{
public:
	int addSide(const Dict *d);
	int addPlayerByTemplate(const AsciiString &playerTemplate);
private:
	char m_pad[0xF44];
	TeamsInfoRec m_teams;
};

int SidesList::addPlayerByTemplate(const AsciiString &playerTemplate)
{
	AsciiString playerName;
	UnicodeString playerDisplayName;
	bool isHuman;

	if (playerTemplate.isEmpty()) {
		((StringBase<char> *)&playerName)->set("");
		playerDisplayName.set(SidesListNeutralDisplayName);
		isHuman = false;
	} else {
		((StringBase<char> *)&playerName)->set("Plyr");
		if (playerTemplate.startsWith("Faction"))
			((StringBase<char> *)&playerName)->concat(playerTemplate.str() + 7);
		else
			((StringBase<char> *)&playerName)->concat(*(const StringBase<char> *)&playerTemplate);
		playerDisplayName.translate(playerName);
		isHuman = true;
		if (playerName.compare("PlyrCivilian") == 0)
			isHuman = false;
	}

	Dict d(0);
	AsciiString teamName;
	((StringBase<char> *)&teamName)->set("team");
	((StringBase<char> *)&teamName)->concat(*(const StringBase<char> *)&playerName);

	d.clear();
	d.setAsciiString(((Rva00148F5ECache *)&TheKey_teamName)->get(), teamName);
	d.setAsciiString(((Rva00148F5ECache *)&TheKey_teamOwner)->get(), playerName);
	d.setBool(TheKey_teamIsSingleton.get(), true);
	m_teams.addTeam(&d);

	d.clear();
	d.setAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get(), playerName);
	d.setBool(TheKey_playerIsHuman.get(), isHuman);
	d.setUnicodeString(TheKey_playerDisplayName.get(), playerDisplayName);
	d.setAsciiString(TheKey_playerFaction.get(), playerTemplate);
	d.setAsciiString(TheKey_playerAllies.get(), AsciiString::TheEmptyString);
	d.setAsciiString(TheKey_playerEnemies.get(), AsciiString::TheEmptyString);

	return addSide(&d);
}
